// re2v $INPUT -o $OUTPUT

import os
import strings

const bufsize = 4096

struct State {
    file     os.File
mut:
    yyinput  []u8
    yycursor int
    yymarker int
    yylimit  int
    token    int
    eof      bool
}

fn fill(mut st &State) int {
    if st.eof { return -1 } // unexpected EOF

    // Error: lexeme too long. In real life can reallocate a larger buffer.
    if st.token < 1 { return -2 }

    // Shift buffer contents (discard everything up to the current token).
    copy(mut &st.yyinput, st.yyinput[st.token..st.yylimit])
    st.yycursor -= st.token
    st.yymarker -= st.token
    st.yylimit -= st.token
    st.token = 0

    // Fill free space at the end of buffer with new data from file.
    pos := st.file.tell() or { 0 }
    if n := st.file.read_bytes_into(u64(pos), mut st.yyinput[st.yylimit..bufsize]) {
        st.yylimit += n
    }
    st.yyinput[st.yylimit] = 0 // append sentinel symbol

    // If read less than expected, this is the end of input.
    st.eof = st.yylimit < bufsize

    return 0
}

fn lex(mut yyrecord &State) int {
    mut count := 0
loop:
    yyrecord.token = yyrecord.yycursor
    /*!re2c
        re2c:api = record;
        re2c:eof = 0;
        re2c:YYFILL = "fill(mut yyrecord) == 0";

        str = ['] ([^'\\] | [\\][^])* ['];

        *    { return -1 }
        $    { return count }
        str  { count += 1; unsafe { goto loop } }
        [ ]+ { unsafe { goto loop } }
    */
}

fn main() {
    fname := "input"
    content := "'qu\0tes' 'are' 'fine: \\'' ";

    // Prepare input file: a few times the size of the buffer, containing
    // strings with zeroes and escaped quotes.
    mut fw := os.create(fname)!
    fw.write_string(strings.repeat_string(content, bufsize))!
    fw.close()
    count := 3 * bufsize // number of quoted strings written to file

    // Prepare lexer state: all offsets are at the end of buffer.
    mut fr := os.open(fname)!
    mut st := &State{
        file:     fr,
        // Sentinel at `yylimit` offset is set to zero, which triggers YYFILL.
        yyinput:  []u8{len: bufsize + 1},
        yycursor: bufsize,
        yymarker: bufsize,
        yylimit:  bufsize,
        token:    bufsize,
        eof:      false,
    }

    // Run the lexer.
    n := lex(mut st)
    if n != count { panic("expected $count, got $n") }

    // Cleanup: remove input file.
    fr.close()
    os.rm(fname)!
}
