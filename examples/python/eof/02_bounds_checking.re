# re2py $INPUT -o $OUTPUT

/*!max:re2c*/

def lex(str):
    cur = 0
    lim = len(str)
    count = 0

    while True:
    /*!re2c
        re2c:define:YYPEEK     = "str[cur]";
        re2c:define:YYSKIP     = "cur += 1;";
        re2c:define:YYLESSTHAN = "cur + @@ > lim";
        re2c:define:YYFILL     = "return -1";
        re2c:indent:top = 2;

        str = ['] ([^'\\] | [\\][^])* ['];

        [\x00] {
            # check that it is the sentinel, not some unexpected null
            return count if cur == lim - YYMAXFILL + 1 else -1
        }
        str {
            count += 1
            break
        }
        [ ]+ { break }
        *    { return -1 }
    */

def test(str, count):
    padded_str = str + (b"\0" * YYMAXFILL)
    assert lex(padded_str) == count

test(b"", 0)
test(b"'unterminated\\'", -1)
test(b"'qu\x00tes' 'are' 'fine: \\'' ", 3)
test(b"'unexpected \x00 null", -1)
