# Generated by re2py
# re2py $INPUT -o $OUTPUT

def lex(yyinput):
    yycursor = 0

    yystate = 0
    while True:
        match yystate:
            case 0:
                yych = yyinput[yycursor]
                yycursor += 1
                if yych <= 0x30:
                    yystate = 1
                    continue
                if yych <= 0x39:
                    yystate = 2
                    continue
                yystate = 1
                continue
            case 1:
                return False
            case 2:
                yych = yyinput[yycursor]
                if yych <= 0x2F:
                    yystate = 3
                    continue
                if yych <= 0x39:
                    yycursor += 1
                    yystate = 2
                    continue
                yystate = 3
                continue
            case 3:
                x = 'useless single-quoted string  }'
                return True
            case _:
                raise "internal lexer error"


assert lex(b"1234\0")
