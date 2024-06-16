// re2v $INPUT -o $OUTPUT

import os
import strings

/*!max:re2c*/
const bufsize = 4096

struct State {
    file os.File
mut:
    str  []u8
    cur  int
    tok  int
    lim  int
    eof  bool
}

fn fill(mut st &State, need int) int {
    if st.eof { return -1 } // unexpected EOF

    // Error: lexeme too long. In real life can reallocate a larger buffer.
    if st.tok < need { return -2 }

    // Shift buffer contents (discard everything up to the current token).
    copy(mut &st.str, st.str[st.tok..st.lim])
    st.cur -= st.tok
    st.lim -= st.tok
    st.tok = 0

    // Fill free space at the end of buffer with new data from file.
    pos := st.file.tell() or { 0 }
    if n := st.file.read_bytes_into(u64(pos), mut st.str[st.lim..bufsize]) {
        st.lim += n
    }

    // If read less than expected, this is the end of input.
    if st.lim < bufsize {
        st.eof = true
        for i := 0; i < yymaxfill; i += 1 { st.str[st.lim + i] = 0 }
        st.lim += yymaxfill
    }

    return 0
}

fn lex(mut yyrecord &State) int {
    mut count := 0
loop:
    yyrecord.tok = yyrecord.cur
    /*!re2c
        re2c:api = record;
        re2c:define:YYFILL = "r := fill(mut yyrecord, @@); if r != 0 { return r }";

        str = ['] ([^'\\] | [\\][^])* ['];

        [\x00] {
            // Check that it is the sentinel, not some unexpected null.
            return if yyrecord.tok == (yyrecord.lim - yymaxfill) { count } else { -1 }
        }
        str  { count += 1; unsafe { goto loop } }
        [ ]+ { unsafe { goto loop } }
        *    { return -1 }
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
    // This immediately triggers YYFILL, as the YYLESSTHAN condition is true.
    mut fr := os.open(fname)!
    mut st := &State{
        file: fr,
        str:  []u8{len: bufsize + yymaxfill},
        cur:  bufsize,
        tok:  bufsize,
        lim:  bufsize,
        eof:  false,
    }

    // Run the lexer.
    n := lex(mut st)
    if n != count { panic("expected $count, got $n") }

    // Cleanup: remove input file.
    fr.close()
    os.rm(fname)!
}
