# re2py $INPUT -o $OUTPUT

# expect a null-terminated string
def lex(yyinput):
    yycursor = 0
    count = 0

    while True: %{
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

assert lex(b"\0") == 0
assert lex(b"one two three\0") == 3
assert lex(b"f0ur\0") == -1
