// Code generated by re2v, DO NOT EDIT.
// re2v $INPUT -o $OUTPUT -i

fn lex(yyinput string) {
    mut yycursor := 0
    mut yymarker := 0
    
    mut yych := 0
    yych = yyinput[yycursor]
    match yych {
        0x07 { unsafe { goto yy3 } }
        else { unsafe { goto yy1 } }
    }
yy1:
    yycursor += 1
yy2:
    
            _ := ['\a', '\b', '\f', '\n', '\r', '\t', '\v', '\\', '\'', '\"']
            panic("error!")

yy3:
    yycursor += 1
    yymarker = yycursor
    yych = yyinput[yycursor]
    match yych {
        0x08 { unsafe { goto yy4 } }
        else { unsafe { goto yy2 } }
    }
yy4:
    yycursor += 1
    yych = yyinput[yycursor]
    match yych {
        0x0C { unsafe { goto yy6 } }
        else { unsafe { goto yy5 } }
    }
yy5:
    yycursor = yymarker
    unsafe { goto yy2 }
yy6:
    yycursor += 1
    yych = yyinput[yycursor]
    match yych {
        0x0A { unsafe { goto yy7 } }
        else { unsafe { goto yy5 } }
    }
yy7:
    yycursor += 1
    yych = yyinput[yycursor]
    match yych {
        0x0D { unsafe { goto yy8 } }
        else { unsafe { goto yy5 } }
    }
yy8:
    yycursor += 1
    yych = yyinput[yycursor]
    match yych {
        0x09 { unsafe { goto yy9 } }
        else { unsafe { goto yy5 } }
    }
yy9:
    yycursor += 1
    yych = yyinput[yycursor]
    match yych {
        0x0B { unsafe { goto yy10 } }
        else { unsafe { goto yy5 } }
    }
yy10:
    yycursor += 1
    yych = yyinput[yycursor]
    match yych {
        0x5C { unsafe { goto yy11 } }
        else { unsafe { goto yy5 } }
    }
yy11:
    yycursor += 1
    yych = yyinput[yycursor]
    match yych {
        0x27 { unsafe { goto yy12 } }
        else { unsafe { goto yy5 } }
    }
yy12:
    yycursor += 1
    yych = yyinput[yycursor]
    match yych {
        0x22 { unsafe { goto yy13 } }
        else { unsafe { goto yy5 } }
    }
yy13:
    yycursor += 1
    return

}

fn main() {
    lex("\x07\x08\x0c\x0a\x0d\x09\x0b\\'\"\x00")
}
