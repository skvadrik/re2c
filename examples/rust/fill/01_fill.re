// re2rust $INPUT -o $OUTPUT

use std::fs::File;
use std::io::{Read, Write};

const BUFSIZE: usize = 4096;

struct State {
    file: File,
    yyinput: [u8; BUFSIZE],
    yylimit: usize,
    yycursor: usize,
    yymarker: usize,
    token: usize,
    eof: bool,
}

#[derive(PartialEq)]
enum Fill { Ok, Eof, LongLexeme }

fn fill(st: &mut State) -> Fill {
    if st.eof { return Fill::Eof; }

    // Error: lexeme too long. In real life could reallocate a larger buffer.
    if st.token < 1 { return Fill::LongLexeme; }

    // Shift buffer contents (discard everything up to the current token).
    st.yyinput.copy_within(st.token..st.yylimit, 0);
    st.yylimit -= st.token;
    st.yycursor -= st.token;
    st.yymarker = st.yymarker.overflowing_sub(st.token).0; // may underflow if marker is unused
    st.token = 0;

    // Fill free space at the end of buffer with new data from file.
    match st.file.read(&mut st.yyinput[st.yylimit..BUFSIZE - 1]) { // -1 for sentinel
        Ok(n) => {
            st.yylimit += n;
            st.eof = n == 0; // end of file
            st.yyinput[st.yylimit] = 0; // append sentinel
        }
        Err(why) => panic!("cannot read from file: {}", why)
    }

    return Fill::Ok;
}

fn lex(yyrecord: &mut State) -> isize {
    let mut count: isize = 0;

    'lex: loop {
        yyrecord.token = yyrecord.yycursor;
    /*!re2c
        re2c:api = record;
        re2c:YYCTYPE = u8;
        re2c:YYFILL = "fill(yyrecord) == Fill::Ok";
        re2c:eof = 0;

        str = ['] ([^'\\] | [\\][^])* ['];

        *    { return -1; }
        $    { return count; }
        str  { count += 1; continue 'lex; }
        [ ]+ { continue 'lex; }
    */}
}

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
    let yylimit = BUFSIZE - 1;
    let mut st = State {
        file: file,
        // Sentinel (at `yylimit` offset) is set to null, which triggers YYFILL.
        yyinput: [0; BUFSIZE],
        yylimit: yylimit,
        yycursor: yylimit,
        yymarker: yylimit,
        token: yylimit,
        eof: false,
    };

    // Run the lexer.
    assert_eq!(lex(&mut st), count as isize);

    // Cleanup: remove input file.
    match std::fs::remove_file(fname) {
        Err(why) => panic!("cannot remove {}: {}", fname, why),
        Ok(_) => {}
    }
}
