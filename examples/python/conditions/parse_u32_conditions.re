# re2py $INPUT -o $OUTPUT -c

%{conditions %}

def parse_u32(yyinput):
    yycursor = 0
    yycond = YYC_INIT
    num = 0

    while True: %{
        re2c:yyfill:enable = 0;
        re2c:indent:top = 2;

        <INIT> '0b' / [01]        :=> BIN
        <INIT> "0"                :=> OCT
        <INIT> "" / [1-9]         :=> DEC
        <INIT> '0x' / [0-9a-fA-F] :=> HEX
        <INIT> * { return None }

        <BIN> [01] {
            num = num * 2 + (yyinput[yycursor - 1] - 48)
            break
        }
        <OCT> [0-7] {
            num = num * 8 + (yyinput[yycursor - 1] - 48)
            break
        }
        <DEC> [0-9] {
            num = num * 10 + (yyinput[yycursor - 1] - 48)
            break
        }
        <HEX> [0-9] {
            num = num * 16 + (yyinput[yycursor - 1] - 48)
            break
        }
        <HEX> [a-f] {
            num = num * 16 + (yyinput[yycursor - 1] - 87)
            break
        }
        <HEX> [A-F] {
            num = num * 16 + (yyinput[yycursor - 1] - 55)
            break
        }

        <BIN, OCT, DEC, HEX> * { return num }
    %}

assert parse_u32(b"\0") == None
assert parse_u32(b"1234567890\0") == 1234567890
assert parse_u32(b"0b1101\0") == 13
assert parse_u32(b"0x7Fe\0") == 2046
assert parse_u32(b"0644\0") == 420
assert parse_u32(b"9999999999\0") == 9999999999
