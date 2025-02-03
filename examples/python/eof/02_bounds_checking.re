# re2py $INPUT -o $OUTPUT

%{max %}

def lex(yyinput):
    yycursor = 0
    yylimit = len(yyinput)
    count = 0

    while True: %{
        re2c:YYFILL = "return -1";
        re2c:indent:top = 2;

        str = ['] ([^'\\] | [\\][^])* ['];

        [\x00] {
            # check that it is the sentinel, not some unexpected null
            return count if yycursor == yylimit - YYMAXFILL + 1 else -1
        }
        str {
            count += 1
            break
        }
        [ ]+ { break }
        *    { return -1 }
    %}

def test(str, count):
    padded_str = str + (b"\0" * YYMAXFILL)
    assert lex(padded_str) == count

test(b"", 0)
test(b"'unterminated\\'", -1)
test(b"'qu\x00tes' 'are' 'fine: \\'' ", 3)
test(b"'unexpected \x00 null", -1)
