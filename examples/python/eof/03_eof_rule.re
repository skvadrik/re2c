# re2py $INPUT -o $OUTPUT

# expect a null-terminated string
def lex(yyinput):
    yycursor = 0
    yylimit = len(yyinput) - 1 # terminating null not included
    count = 0

    while True: %{
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
    %}

def test(str, count):
    # termunating null not included in `lim`
    assert count == lex(str)

test(b"\0", 0);
test(b"'qu\0tes' 'are' 'fine: \\'' \0", 3);
test(b"'unterminated\\'\0", -1)
