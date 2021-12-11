// re2rust $INPUT -o $OUTPUT

use std::fs::File;
use std::io::{Read, Write};

const SIZE: usize = 4096;

struct State {
    file: File,
    buf: [u8; SIZE],
    lim: usize,
    cur: usize,
    mar: usize,
    tok: usize,
    eof: bool,
}

#[derive(PartialEq)]
enum Fill { Ok, Eof, LongLexeme }

fn fill(st: &mut State) -> Fill {
    if st.eof {
        return Fill::Eof;
    }

    let free = st.tok;
    if free < 1 {
        return Fill::LongLexeme;
    }

    // Shift buffer contents (discard everything up to current token).
    unsafe {
        let p = st.buf.as_mut_ptr();
        std::ptr::copy(p, p.offset(free as isize), st.lim - st.tok);
    }
    // Shift indices accordingly.
    st.lim -= free;
    st.cur -= free;
    st.mar = st.mar.overflowing_sub(free).0; // underflow ok if marker is unused
    st.tok -= free;
    // Fill free space at the end of buffer with new data from file.
    match st.file.read(&mut st.buf[st.lim..(st.lim + free)]) {
        Ok(n) => {
            st.lim += n;
            st.eof = n == 0; // end of file
        }
        Err(why) => panic!("cannot read from file: {}", why)
    }
    // Write sentinel after the last character read from file.
    st.buf[st.lim] = 0;

    return Fill::Ok;
}

fn lex(st: &mut State) -> isize {
    let mut count: isize = 0;

    'lex: loop {
        st.tok = st.cur;
    /*!re2c
        re2c:eof = 0;
        re2c:define:YYCTYPE    = u8;
        re2c:define:YYPEEK     = "*st.buf.get_unchecked(st.cur)";
        re2c:define:YYSKIP     = "st.cur += 1;";
        re2c:define:YYBACKUP   = "st.mar = st.cur;";
        re2c:define:YYRESTORE  = "st.cur = st.mar;";
        re2c:define:YYFILL     = "{ return -1; }";
        re2c:define:YYLESSTHAN = "st.cur + @@ > st.lim";
        re2c:define:YYFILL     = "fill(st) == Fill::Ok";

        *                           { return -1; }
        $                           { return count; }
        ['] ([^'\\] | [\\][^])* ['] { count += 1; continue 'lex; }
        [ ]+                        { continue 'lex; }
    */}
}

fn main() {
    let fname = "input";
    let mut file: File;

    // Create input file.
    file = match File::create(fname) {
        Err(why) => panic!("cannot open {}: {}", fname, why),
        Ok(file) => file,
    };

    // Prepare input file: a few times the size of the buffer, containing
    // strings with zeroes and escaped quotes.
    let mut count = 0;
    for _ in 0..SIZE {
        match file.write_all(b"'qu\0tes' 'are' 'fine: \\'' ") {
            Err(why) => panic!("cannot write to {}: {}", fname, why),
            Ok(_) => {}
        }
        count += 3;
    }

    // Reopen input file for reading.
    file = match File::open(fname) {
        Err(why) => panic!("cannot read file {}: {}", fname, why),
        Ok(file) => file,
    };

    // Prepare lexer state and fill buffer.
    let lim = SIZE - 1; // one left for the sentinel
    let mut st = State {
        file: file,
        buf: [0; SIZE],
        lim: lim,
        cur: lim,
        mar: lim,
        tok: lim,
        eof: false,
    };
    fill(&mut st);

    // Run the lexer.
    assert_eq!(lex(&mut st), count as isize);

    // Cleanup: remove input file.
    match std::fs::remove_file(fname) {
        Err(why) => panic!("cannot remove {}: {}", fname, why),
        Ok(_) => {}
    }
}
