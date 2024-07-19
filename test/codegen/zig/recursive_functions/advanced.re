// re2zig $INPUT -o $OUTPUT -cf --recursive-functions -Wno-nondeterministic-tags

const std = @import("std");

// Use a small buffer to cover the case when a lexeme doesn't fit.
// In real world use a larger buffer.
const bufsize = 100;
const none = std.math.maxInt(usize);
const mtag_root = none - 1;

/*!conditions:re2c*/

const State = struct {
    allocator: std.mem.Allocator,
    yyinput: [bufsize + 1]u8,
    yycursor: usize,
    yymarker: usize,
    yylimit: usize,
    token: usize,
    yycond: u32,
    yystate: i32,
    trie: *std.ArrayList(MtagElem),
    /*!stags:re2c format = "@@: usize,\n"; */
    /*!mtags:re2c format = "@@: usize,\n"; */
    l1: usize,
    l2: usize,
    f1: usize,
    f2: usize,
    p1: usize,
    p2: usize,
    p3: usize,
    p4: usize,
    yyaccept: u32,
};

const Status = enum {
    end,
    ready,
    waiting,
    bad_packet,
    big_packet,
};

// An m-tag tree is a way to store histories with an O(1) copy operation.
// Histories naturally form a tree, as they have common start and fork at some
// point. The tree is stored as an array of pairs (tag value, link to parent).
// An m-tag is represented with a single link in the tree (array index).
const MtagElem = struct {
    elem: usize, // tag value
    pred: usize, // index of the predecessor node or root
};

// Append a single value to an m-tag history.
fn add_mtag(trie: *std.ArrayList(MtagElem), mtag: usize, value: usize) !usize {
    try trie.append(MtagElem{.elem = value, .pred = mtag});
    return trie.items.len - 1;
}

// Recursively unwind tag histories and collect version components.
fn unwind(st: *State, x: usize, y: usize) !std.ArrayList([]const u8) {
    // Reached the root of the m-tag tree, stop recursion.
    if (x == mtag_root and y == mtag_root) {
        var ss = std.ArrayList([]const u8).init(st.allocator);
        return ss;
    }

    // Unwind history further.
    var ss = try unwind(st, st.trie.items[x].pred, st.trie.items[y].pred);

    // Get tag values. Tag histories must have equal length.
    std.debug.assert(x != mtag_root and y != mtag_root);
    var ex = st.trie.items[x].elem;
    var ey = st.trie.items[y].elem;

    if (ex != none and ey != none) {
        // Both tags are valid string indices, extract component.
        var s = try std.mem.Allocator.dupe(st.allocator, u8, st.yyinput[ex..ey]);
        try ss.append(s);
    } else {
        // Both tags are none (this corresponds to zero repetitions).
        std.debug.assert(ex == none and ey == none);
    }

    return ss;
}

fn s2n(str: []const u8) u32 { // convert a pre-parsed string to a number
    var n: u32 = 0;
    for (str) |c| { n = n * 10 + (c - 48); }
    return n;
}

fn fill(st: *State, file: anytype) Status {
    var used = st.yylimit - st.token;
    var free = bufsize - used;

    // Error: lexeme too long. In real life can reallocate a larger buffer.
    if (free < 1) return Status.big_packet;

    // Shift buffer contents (discard everything up to the current token).
    std.mem.copyBackwards(u8, st.yyinput[0..used], st.yyinput[st.token..st.yylimit]);
    st.yycursor -= st.token;
    st.yymarker = @subWithOverflow(st.yymarker, st.token)[0];
    st.yylimit -= st.token;
    // Tag variables need to be shifted like other input positions. The check
    // for NONE is only needed if some tags are nested inside of alternative or
    // repetition, so that they can have NONE value.
    /*!stags:re2c format = "if (st.@@ != none) st.@@ = @subWithOverflow(st.@@, st.token)[0];\n"; */
    st.token = 0;

    // Fill free space at the end of buffer with new data from file.
    st.yylimit += file.read(st.yyinput[st.yylimit..bufsize]) catch 0;
    st.yyinput[st.yylimit] = 0; // append sentinel symbol

    return Status.ready;
}

/*!re2c
    re2c:api = record;
    re2c:eof = 0;
    re2c:tags = 1;
    re2c:tags:negative = "none";
    re2c:variable:yyrecord = st;
    re2c:define:YYCTYPE = u8;
    re2c:define:YYFN = ["lex;Status", "st;*State"];
    re2c:define:YYFILL = "return Status.waiting;";
    re2c:define:YYMTAGP = "@@ = add_mtag(st.trie, @@, st.yycursor) catch none;";
    re2c:define:YYMTAGN = "@@ = add_mtag(st.trie, @@, none) catch none;";

    crlf  = '\r\n';
    sp    = ' ';
    htab  = '\t';
    ows   = (sp | htab)*;
    digit = [0-9];
    alpha = [a-zA-Z];
    vchar = [\x1f-\x7e];
    tchar = [-!#$%&'*+.^_`|~] | digit | alpha;

    obs_fold            = #f1 crlf (sp | htab)+ #f2;
    obs_text            = [\x80-\xff];
    field_name          = tchar+;
    field_vchar         = vchar | obs_text;
    field_content       = field_vchar ((sp | htab)+ field_vchar)?;
    field_value_folded  = (field_content* obs_fold field_content*)+;
    header_field_folded = field_value_folded ows;
    token               = tchar+;
    qdtext
        = htab
        | sp
        | [\x21-\x5B\x5D-\x7E] \ '"'
        | obs_text;
    quoted_pair         = '\\' ( htab | sp | vchar | obs_text );
    quoted_string       = '"' ( qdtext | quoted_pair )* '"';
    parameter           = #p1 token #p2 '=' #p3 ( token | quoted_string ) #p4;
    media_type          = @l1 token '/' token @l2 ( ows ';' ows parameter )*;

    <media_type> media_type ows crlf {
        var mt = st.yyinput[st.l1..st.l2];
        std.log.debug("media type: {s}", .{mt});

        var pnames = unwind(st, st.p1, st.p2) catch null;
        std.log.debug("pnames: {any}", .{pnames});

        var pvals = unwind(st, st.p3, st.p4) catch null;
        std.log.debug("pvals: {any}", .{pvals});

        st.token = st.yycursor;
        return lex(st);
    }

    <header> header_field_folded crlf {
        var folds = unwind(st, st.f1, st.f2) catch null;
        std.log.debug("folds: {any}", .{folds});

        st.token = st.yycursor;
        return lex(st);
    }

    <*> * { return Status.bad_packet; }
    <*> $ { return Status.end; }
*/

fn run(expect: Status, packets: []const []const u8) !void {
    var arena = std.heap.ArenaAllocator.init(std.testing.allocator);
    defer arena.deinit();

    // Create a "pipe" (open the same file for reading and writing).
    const fname = "pipe";
    var fw = try std.fs.cwd().createFile(fname, .{});
    var fr = try std.fs.cwd().openFile(fname, .{ .mode = .read_only});

    // Initialize lexer state: `state` value is -1, all offsets are at the end
    // of buffer. Normally file would be part of the state, but BufferedReader
    // type is unclear.
    var br = std.io.bufferedReader(fr.reader());
    var mt = std.ArrayList(MtagElem).init(std.testing.allocator);
    defer mt.deinit();
    var st = State{
        .allocator = arena.allocator(),
        .yyinput = undefined,
        .yycursor = bufsize,
        .yymarker = bufsize,
        .yylimit = bufsize,
        .token = bufsize,
        .yycond = yycmedia_type,
        .yystate = -1,
        .trie = &mt,
        /*!stags:re2c format = '.@@ = none,\n'; */
        /*!mtags:re2c format = '.@@ = mtag_root,\n'; */
        .l1 = none,
        .l2 = none,
        .f1 = mtag_root,
        .f2 = mtag_root,
        .p1 = mtag_root,
        .p2 = mtag_root,
        .p3 = mtag_root,
        .p4 = mtag_root,
        .yyaccept = 0,
    };
    // Sentinel at `yylimit` offset is set to zero, which triggers YYFILL.
    st.yyinput[st.yylimit] = 0;

    // Main loop. The buffer contains incomplete data which appears packet by
    // packet. When the lexer needs more input it saves its internal state and
    // returns to the caller which should provide more input and resume lexing.
    var status = Status.ready;
    var send: usize = 0;
    while (true) {
        status = lex(&st);
        if (status == Status.end) {
            break;
        } else if (status == Status.waiting) {
            if (send < packets.len) {
                std.log.debug("sending packet {}", .{send});
                try fw.writeAll(packets[send]);
                send += 1;
            }
            status = fill(&st, &br);
            std.log.debug("filled buffer [{s}], status {}", .{st.yyinput, status});
            if (status != Status.ready) {
                break;
            }
        } else if (status == Status.bad_packet) {
            break;
        }
    }

    // Check results.
    try std.testing.expectEqual(status, expect);

    // Cleanup: remove input file.
    fw.close();
    fr.close();
    try std.fs.cwd().deleteFile(fname);
}

test {
    try run(Status.end,
        &[_][]const u8{"ap", "plication/j", "son;", " charset=\"", "utf\\\"-8\"\r", "\n", ""});
}
