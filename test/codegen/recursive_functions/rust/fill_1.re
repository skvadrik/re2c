// re2rust $INPUT -o $OUTPUT --recursive-functions

use std::fs::File;
use std::io::{Read, Write};

const BUFSIZE: usize = 4096;

struct State {
    file: File,
    buf: [u8; BUFSIZE],
    lim: usize,
    cur: usize,
    mar: usize,
    tok: usize,
    eof: bool,
    count: isize
}

#[derive(PartialEq)]
enum Fill { Ok, Eof, LongLexeme }

fn fill(st: &mut State) -> Fill {
    if st.eof { return Fill::Eof; }

    // Error: lexeme too long. In real life could reallocate a larger buffer.
    if st.tok < 1 { return Fill::LongLexeme; }

    // Shift buffer contents (discard everything up to the current token).
    st.buf.copy_within(st.tok..st.lim, 0);
    st.lim -= st.tok;
    st.cur -= st.tok;
    st.mar = st.mar.overflowing_sub(st.tok).0; // may underflow if marker is unused
    st.tok = 0;

    // Fill free space at the end of buffer with new data from file.
    match st.file.read(&mut st.buf[st.lim..BUFSIZE - 1]) { // -1 for sentinel
        Ok(n) => {
            st.lim += n;
            st.eof = n == 0; // end of file
            st.buf[st.lim] = 0; // append sentinel
        }
        Err(why) => panic!("cannot read from file: {}", why)
    }

    return Fill::Ok;
}

fn lex_loop(st: &mut State) -> isize {
    st.tok = st.cur;
    return lex(st);
}

/*!re2c
    re2c:define:YYFN       = ["lex;isize", "_st;&mut State"];
    re2c:define:YYCTYPE    = u8;
    re2c:define:YYPEEK     = "*_st.buf.get_unchecked(_st.cur)";
    re2c:define:YYSKIP     = "_st.cur += 1;";
    re2c:define:YYBACKUP   = "_st.mar = _st.cur;";
    re2c:define:YYRESTORE  = "_st.cur = _st.mar;";
    re2c:define:YYLESSTHAN = "_st.cur >= _st.lim";
    re2c:define:YYFILL     = "fill(_st) == Fill::Ok";
    re2c:eof = 0;

    str = ['] ([^'\\] | [\\][^])* ['];

    *    { return -1; }
    $    { return _st.count; }
    str  { _st.count += 1; return lex_loop(_st); }
    [ ]+ { return lex_loop(_st); }
*/

fn main() {
    let fname = "input";
    let content = b"'qu\0tes' 'are' 'fine: \\'' ";

    // Prepare input file: a few times the size of the buffer, containing
    // strings with zeroes and escaped quotes.
    match File::create(fname) {
        Err(why) => panic!("cannot open {}: {}", fname, why),
        Ok(mut file) => match file.write_all(&content.repeat(BUFSIZE)) {
            Err(why) => panic!("cannot write to {}: {}", fname, why),
            Ok(_) => {}
        }
    };
    let count = 3 * BUFSIZE; // number of quoted strings written to file

    // Reopen input file for reading.
    let file = match File::open(fname) {
        Err(why) => panic!("cannot read file {}: {}", fname, why),
        Ok(file) => file,
    };

    // Initialize lexer state: all offsets are at the end of buffer.
    let lim = BUFSIZE - 1;
    let mut st = State {
        file: file,
        // Sentinel (at `lim` offset) is set to null, which triggers YYFILL.
        buf: [0; BUFSIZE],
        lim: lim,
        cur: lim,
        mar: lim,
        tok: lim,
        eof: false,
        count: 0
    };

    // Run the lexer.
    assert_eq!(lex_loop(&mut st), count as isize);

    // Cleanup: remove input file.
    match std::fs::remove_file(fname) {
        Err(why) => panic!("cannot remove {}: {}", fname, why),
        Ok(_) => {}
    }
}
