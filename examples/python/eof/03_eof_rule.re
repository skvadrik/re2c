# re2py $INPUT -o $OUTPUT

# expect a null-terminated string
def lex(str):
    cur = 0
    lim = len(str) - 1 # terminating null not included
    count = 0

    while True:
    /*!re2c
        re2c:define:YYPEEK     = "str[cur]";
        re2c:define:YYSKIP     = "cur += 1";
        re2c:define:YYBACKUP   = "mar = cur";
        re2c:define:YYRESTORE  = "cur = mar";
        re2c:define:YYLESSTHAN = "cur >= lim";
        re2c:yyfill:enable = 0;
        re2c:eof = 0;
        re2c:indent:top = 2;

        str = ['] ([^'\\] | [\\][^])* ['];

        *    { return -1 }
        $    { return count }
        [ ]+ { break }
        str  {
            count += 1
            break
        }
    */

def test(str, count):
    # termunating null not included in `lim`
    assert count == lex(str)

test(b"\0", 0);
test(b"'qu\0tes' 'are' 'fine: \\'' \0", 3);
test(b"'unterminated\\'\0", -1)
