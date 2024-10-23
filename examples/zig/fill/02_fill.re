// re2zig $INPUT -o $OUTPUT

const std = @import("std");

%{max %}
const bufsize = 4096;

const State = struct {
    yyinput: [bufsize + yymaxfill]u8,
    yycursor: usize,
    yymarker: usize,
    yylimit: usize,
    token: usize,
    eof: bool
};

fn fill(st: *State, need: usize, file: anytype) i32 {
    if (st.eof) { return -1; } // unexpected EOF

    // Error: lexeme too long. In real life can reallocate a larger buffer.
    if (st.token < need) { return -2; }

    // Shift buffer contents (discard everything up to the current token).
    std.mem.copyBackwards(
        u8, st.yyinput[0..st.yylimit - st.token], st.yyinput[st.token..st.yylimit]);
    st.yycursor -= st.token;
    st.yymarker = @subWithOverflow(st.yymarker, st.token)[0];
    st.yylimit -= st.token;
    st.token = 0;

    // Fill free space at the end of buffer with new data from file.
    st.yylimit += file.read(st.yyinput[st.yylimit..bufsize]) catch 0;

    // If read less than expected, this is the end of input.
    if (st.yylimit < bufsize) {
        st.eof = true;
        @memset(st.yyinput[st.yylimit..st.yylimit + yymaxfill], 0);
        st.yylimit += yymaxfill;
    }

    return 0;
}

fn lex(yyrecord: *State, file: anytype) i32 {
    var count: i32 = 0;
    loop: while (true) {
        yyrecord.token = yyrecord.yycursor;
        %{
            re2c:api = record;
            re2c:YYFILL = "{ if (fill(yyrecord, @@, file) != 0) return -2; }";

            str = ['] ([^'\\] | [\\][^])* ['];

            [\x00] {
                // Check that it is the sentinel, not some unexpected null.
                return if (yyrecord.token == yyrecord.yylimit - yymaxfill) count else -1;
            }
            str  { count += 1; continue :loop; }
            [ ]+ { continue :loop; }
            *    { return -1; }
        %}
    }
}

test {
    const fname = "input";
    const content = "'qu\x00tes' 'are' 'fine: \\'' " ** bufsize;
    const count = 3 * bufsize; // number of quoted strings written to file

    // Prepare input file: a few times the size of the buffer, containing
    // strings with zeroes and escaped quotes.
    var fw = try std.fs.cwd().createFile(fname, .{});
    try fw.writeAll(content);
    fw.close();

    // Prepare lexer state: all offsets are at the end of buffer.
    // This immediately triggers YYFILL, as the YYLESSTHAN condition is true.
    var fr = try std.fs.cwd().openFile(fname, .{ .mode = .read_only});
    // Normally file would be part of the state struct, but BufferedReader type is unclear.
    var br = std.io.bufferedReader(fr.reader());
    var st = State{
        .yyinput = undefined,
        .yycursor = bufsize,
        .yymarker = bufsize,
        .yylimit = bufsize,
        .token = bufsize,
        .eof = false,
    };
    @memset(st.yyinput[st.yylimit..st.yylimit + yymaxfill], 0); // zero-padding at the end

    // Run the lexer.
    try std.testing.expectEqual(lex(&st, &br), count);

    // Cleanup: remove input file.
    fr.close();
    try std.fs.cwd().deleteFile(fname);
}
