// re2rust $INPUT -o $OUTPUT -fc --no-unsafe

use std::fs::File;
use std::io::{Read, Write};

const BUFSIZE: usize = 10;

/*!conditions:re2c*/

const DEBUG: bool = false;
macro_rules! log {
    ($($fmt:expr)? $(, $args:expr)*) => { if DEBUG { println!($($fmt)? $(, $args)*) } }
}

struct State {
    file: File,
    buf: [u8; BUFSIZE + 1],
    lim: usize,
    cur: usize,
    mar: usize,
    tok: usize,
    state: isize,
}

#[derive(Debug, PartialEq)]
enum Status {End, Ready, Waiting, BadPacket, BigPacket}

fn fill(st: &mut State) -> Status {
    let shift = st.tok;
    let used = st.lim - st.tok;
    let free = BUFSIZE - used;

    // Error: no space. In real life can reallocate a larger buffer.
    if free < 1 { return Status::BigPacket; }

    // Shift buffer contents (discard already processed data).
    unsafe {
        let p = st.buf.as_mut_ptr();
        std::ptr::copy(p, p.offset(shift as isize), used);
    }
    st.lim -= shift;
    st.cur -= shift;
    st.mar = st.mar.overflowing_sub(free).0; // underflow ok if marker is unused
    st.tok -= shift;

    // Fill free space at the end of buffer with new data.
    match st.file.read(&mut st.buf[st.lim..BUFSIZE]) {
        Ok(n) => st.lim += n,
        Err(why) => panic!("cannot read from file: {}", why)
    }
    st.buf[st.lim] = 0; // append sentinel symbol

    return Status::Ready;
}

fn lex(st: &mut State, nc: &mut isize, wc: &mut isize) -> Status {
    let mut yych: u8 = 0;
    'lex: loop {
        st.tok = st.cur;
    /*!re2c
        re2c:eof = 0;
        re2c:define:YYCTYPE = "u8";
        re2c:define:YYPEEK = "st.buf[st.cur]";
        re2c:define:YYSKIP = "st.cur += 1;";
        re2c:define:YYBACKUP = "st.mar = st.cur;";
        re2c:define:YYRESTORE = "st.cur = st.mar;";
        re2c:define:YYSHIFT = "st.cur = (st.cur as isize + @@) as usize;";
        re2c:define:YYLESSTHAN = "st.cur >= st.lim";
        re2c:define:YYGETSTATE = "st.state";
        re2c:define:YYSETSTATE = "st.state = @@;";
        re2c:define:YYFILL = "return Status::Waiting;";

        digit  = [0-9];
        letter = [a-z];
        space  = [ \t];

        <*> * { return Status::BadPacket; }
        <*> $ { return Status::End; }

        <INIT> "" / digit  :=> NUMBER
        <INIT> "" / letter :=> WORD
        <INIT> "" / space  :=> SPACES

        <SPACES> space+ => INIT{ continue 'lex; }

        <NUMBER> digit+  => SPACES { *nc += 1; continue 'lex; }
        <WORD>   letter+ => SPACES { *wc += 1; continue 'lex; }
    */}
}

fn test(packets: Vec<&[u8]>, expect: Status, expect_nc: isize, expect_wc: isize) {
    // Create a "socket" (open the same file for reading and writing).
    let fname = "pipe";
    let mut fw: File = match File::create(fname) {
        Err(why) => panic!("cannot open {}: {}", fname, why),
        Ok(file) => file,
    };
    let fr: File = match File::open(fname) {
        Err(why) => panic!("cannot read file {}: {}", fname, why),
        Ok(file) => file,
    };

    // Initialize lexer state: `state` value is -1, all offsets are at the end
    // of buffer, the character at `lim` offset is the sentinel (null).
    let mut state = State {
        file: fr,
        buf: [0; BUFSIZE + 1], // sentinel (at `lim` offset) is set to null
        cur: BUFSIZE,
        mar: BUFSIZE,
        tok: BUFSIZE,
        lim: BUFSIZE,
        state: -1,
    };

    // Main loop. The buffer contains incomplete data which appears packet by
    // packet. When the lexer needs more input it saves its internal state and
    // returns to the caller which should provide more input and resume lexing.
    let mut status;
    let mut send = 0;
    let mut nc = 0;
    let mut wc = 0;
    loop {
        status = lex(&mut state, &mut nc, &mut wc);
        if status == Status::End {
            log!("done: got {} numbers and {} words", nc, wc);
            break;
        } else if status == Status::Waiting {
            log!("waiting...");
            if send < packets.len() {
                log!("sent packet {}", send);
                match fw.write_all(packets[send]) {
                    Err(why) => panic!("cannot write to {}: {}", fname, why),
                    Ok(_) => send += 1,
                }
            }
            status = fill(&mut state);
            log!("queue: '{}'", String::from_utf8_lossy(&state.buf));
            if status == Status::BigPacket {
                log!("error: packet too big");
                break;
            }
            assert_eq!(status, Status::Ready);
        } else {
            assert_eq!(status, Status::BadPacket);
            log!("error: ill-formed packet");
            break;
        }
    }

    // Check results.
    assert_eq!(status, expect);
    if status == Status::End {
        assert_eq!(nc, expect_nc);
        assert_eq!(wc, expect_wc);
    }

    // Cleanup: remove input file.
    match std::fs::remove_file(fname) {
        Err(why) => panic!("cannot remove {}: {}", fname, why),
        Ok(_) => {}
    }
}

fn main() {
    test(vec![], Status::End, 0, 0);
    test(vec![b" zero one", b" ", b"123", b"4 tw", b"o  ", b"456789"], Status::End, 2, 3);
    test(vec![b"zer0"], Status::BadPacket, -1, -1);
    test(vec![b"tooooooloooooong"], Status::BigPacket, -1, -1);
}
