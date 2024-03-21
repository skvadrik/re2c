# re2py $INPUT -o $OUTPUT -s

def lex(str):
    cur = 0
    /*!re2c
        re2c:define:YYPEEK = "str[cur]";
        re2c:define:YYSKIP = "cur += 1";
        re2c:yyfill:enable = 0;
        re2c:indent:top = 1;

        number = [1-9][0-9]*;

        number { return True }
        *      { return False }
    */

assert lex(b"1234\0")
