// re2v $INPUT -o $OUTPUT

import os
import strings

const bufsize = 4096

struct State {
    file os.File
mut:
    buf  []u8
    cur  int
    mar  int
    tok  int
    lim  int
    eof  bool
}

fn fill(mut st &State) int {
    if st.eof { return -1 } // unexpected EOF

    // Error: lexeme too long. In real life can reallocate a larger buffer.
    if st.tok < 1 { return -2 }

    // Shift buffer contents (discard everything up to the current token).
    copy(mut &st.buf, st.buf[st.tok..st.lim])
    st.cur -= st.tok
    st.mar -= st.tok
    st.lim -= st.tok
    st.tok = 0

    // Fill free space at the end of buffer with new data from file.
    pos := st.file.tell() or { 0 }
    if n := st.file.read_bytes_into(u64(pos), mut st.buf[st.lim..bufsize]) {
        st.lim += n
    }
    st.buf[st.lim] = 0 // append sentinel symbol

    // If read less than expected, this is the end of input.
    st.eof = st.lim < bufsize

    return 0
}

fn lex(mut st &State) int {
    mut count := 0
loop:
    st.tok = st.cur
    /*!re2c
        re2c:eof = 0;
        re2c:define:YYCTYPE    = u8;
        re2c:define:YYPEEK     = "st.buf[st.cur]";
        re2c:define:YYSKIP     = "st.cur += 1";
        re2c:define:YYBACKUP   = "st.mar = st.cur";
        re2c:define:YYRESTORE  = "st.cur = st.mar";
        re2c:define:YYLESSTHAN = "st.lim <= st.cur";
        re2c:define:YYFILL     = "fill(mut st) == 0";

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
        file: fr,
        // Sentinel at `lim` offset is set to zero, which triggers YYFILL.
        buf:  []u8{len: bufsize + 1},
        cur:  bufsize,
        mar:  bufsize,
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
