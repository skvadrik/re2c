// re2zig $INPUT -o $OUTPUT -f

const std = @import("std");

const Status = enum {
    end,
    ready,
    waiting,
    bad_packet,
    big_packet
};

// Use a small buffer to cover the case when a lexeme doesn't fit.
// In real world use a larger buffer.
const bufsize = 10;

const State = struct {
    yyinput: [bufsize + 1]u8,
    yycursor: usize,
    yymarker: usize,
    yylimit: usize,
    token: usize,
    yystate: i32,
    received: usize,
};

fn fill(st: *State, file: anytype) Status {
    // Error: lexeme too long. In real life can reallocate a larger buffer.
    if (st.token < 1) { return Status.big_packet; }

    // Shift buffer contents (discard everything up to the current token).
    std.mem.copyBackwards(
        u8, st.yyinput[0..st.yylimit - st.token], st.yyinput[st.token..st.yylimit]);
    st.yycursor -= st.token;
    st.yymarker = @subWithOverflow(st.yymarker, st.token)[0];
    st.yylimit -= st.token;
    st.token = 0;

    // Fill free space at the end of buffer with new data from file.
    st.yylimit += file.read(st.yyinput[st.yylimit..bufsize]) catch 0;
    st.yyinput[st.yylimit] = 0; // append sentinel symbol

    return Status.ready;
}

fn lex(yyrecord: *State) Status {
    var yych: u8 = 0;
    loop: while (true) {
        yyrecord.token = yyrecord.yycursor;
        %{
            re2c:api = record;
            re2c:eof = 0;
            re2c:YYFILL = "return Status.waiting;";

            packet = [a-z]+[;];

            *      { return Status.bad_packet; }
            $      { return Status.end; }
            packet { yyrecord.received += 1; continue :loop; }
        %}
    }
}

fn run(expect: Status, packets: []const []const u8) !void {
    // Create a "pipe" (open the same file for reading and writing).
    const fname = "input";
    var fw = try std.fs.cwd().createFile(fname, .{});
    var fr = try std.fs.cwd().openFile(fname, .{ .mode = .read_only});

    // Initialize lexer state: `state` value is -1, all offsets are at the end
    // of buffer. Normally file would be part of the state, but BufferedReader
    // type is unclear.
    var br = std.io.bufferedReader(fr.reader());
    var st = State{
        .yyinput = undefined,
        .yycursor = bufsize,
        .yymarker = bufsize,
        .yylimit = bufsize,
        .token = bufsize,
        .yystate = -1,
        .received = 0,
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
    if (status == Status.end) { try std.testing.expectEqual(st.received, send); }

    // Cleanup: remove input file.
    fw.close();
    fr.close();
    try std.fs.cwd().deleteFile(fname);
}

test {
    try run(Status.end, &[_][]const u8{});
    try run(Status.end, &[_][]const u8{"zero;", "one;", "two;", "three;", "four;"});
    try run(Status.bad_packet, &[_][]const u8{"??;"});
    try run(Status.big_packet, &[_][]const u8{"looooooooooooong;"});
}
