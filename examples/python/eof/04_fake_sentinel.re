# re2py $INPUT -o $OUTPUT

# expect a string without terminating null
def lex(str):
    cur = 0
    lim = len(str)
    count = 0

    while True: %{
        re2c:api = custom;
        re2c:define:YYPEEK = "str[cur] if cur < lim else 0";
        re2c:define:YYSKIP = "cur += 1";
        re2c:yyfill:enable = 0;
        re2c:indent:top = 2;

        *      { return -1 }
        [\x00] { return count }
        [ ]+   { break }
        [a-z]+ {
            count += 1
            break
        }
    %}

assert lex(b"") == 0
assert lex(b"one two three") == 3
assert lex(b"f0ur") == -1
