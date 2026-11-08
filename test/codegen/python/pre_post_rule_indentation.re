# re2py $INPUT -o $OUTPUT

def lex(yyinput):
    yycursor = 0
/*!re2c
        re2c:yyfill:enable = 0;
        re2c:indent:top = 1;

        !pre_rule {
            n = 0
            n += 1
        }

        number = [1-9][0-9]*;

        number {
            return n == 1
        }
        * {
            return False
        }

        !post_rule {
            n -= 1
            assert n == 0
        }
*/

assert lex(b"1\0")
