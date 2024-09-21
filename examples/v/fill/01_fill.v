// Code generated by re2v, DO NOT EDIT.
//line "v/fill/01_fill.re":1
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
    
//line "v/fill/01_fill.v":53
    mut yych := 0
yyFillLabel0:
    yych = yyrecord.yyinput[yyrecord.yycursor]
    match yych {
        0x20 { unsafe { goto yy3 } }
        0x27 { unsafe { goto yy5 } }
        else {
            if yyrecord.yylimit <= yyrecord.yycursor {
                if fill(mut yyrecord) == 0 {
                    unsafe { goto yyFillLabel0 }
                }
                unsafe { goto yy10 }
            }
            unsafe { goto yy1 }
        }
    }
yy1:
    yyrecord.yycursor += 1
yy2:
//line "v/fill/01_fill.re":56
    return -1
//line "v/fill/01_fill.v":75
yy3:
    yyrecord.yycursor += 1
yyFillLabel1:
    yych = yyrecord.yyinput[yyrecord.yycursor]
    match yych {
        0x20 { unsafe { goto yy3 } }
        else {
            if yyrecord.yylimit <= yyrecord.yycursor {
                if fill(mut yyrecord) == 0 {
                    unsafe { goto yyFillLabel1 }
                }
            }
            unsafe { goto yy4 }
        }
    }
yy4:
//line "v/fill/01_fill.re":59
    unsafe { goto loop }
//line "v/fill/01_fill.v":94
yy5:
    yyrecord.yycursor += 1
    yyrecord.yymarker = yyrecord.yycursor
yyFillLabel2:
    yych = yyrecord.yyinput[yyrecord.yycursor]
    if yych >= 0x01 {
        unsafe { goto yy7 }
    }
    if yyrecord.yylimit <= yyrecord.yycursor {
        if fill(mut yyrecord) == 0 {
            unsafe { goto yyFillLabel2 }
        }
        unsafe { goto yy2 }
    }
yy6:
    yyrecord.yycursor += 1
yyFillLabel3:
    yych = yyrecord.yyinput[yyrecord.yycursor]
yy7:
    match yych {
        0x27 { unsafe { goto yy8 } }
        0x5C { unsafe { goto yy9 } }
        else {
            if yyrecord.yylimit <= yyrecord.yycursor {
                if fill(mut yyrecord) == 0 {
                    unsafe { goto yyFillLabel3 }
                }
                unsafe { goto yy11 }
            }
            unsafe { goto yy6 }
        }
    }
yy8:
    yyrecord.yycursor += 1
//line "v/fill/01_fill.re":58
    count += 1; unsafe { goto loop }
//line "v/fill/01_fill.v":131
yy9:
    yyrecord.yycursor += 1
yyFillLabel4:
    yych = yyrecord.yyinput[yyrecord.yycursor]
    if yych <= 0x00 {
        if yyrecord.yylimit <= yyrecord.yycursor {
            if fill(mut yyrecord) == 0 {
                unsafe { goto yyFillLabel4 }
            }
            unsafe { goto yy11 }
        }
        unsafe { goto yy6 }
    }
    unsafe { goto yy6 }
yy10:
//line "v/fill/01_fill.re":57
    return count
//line "v/fill/01_fill.v":149
yy11:
    yyrecord.yycursor = yyrecord.yymarker
    unsafe { goto yy2 }
//line "v/fill/01_fill.re":60

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