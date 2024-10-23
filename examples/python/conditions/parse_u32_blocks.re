# re2py $INPUT -o $OUTPUT

class State:
    def __init__(self, str):
        self.yyinput = str
        self.yycursor = 0
        self.yymarker = 0

# Common re2c definitions shared between all functions.
%{
    re2c:api = record;
    re2c:yyrecord = st;
    re2c:yyfill:enable = 0;
    re2c:indent:top = 2;
%}

def parse_u32(str):
    st = State(str)
%{local
    re2c:indent:top = 1;

    '0b' / [01]        { return parse_bin(st) }
    "0"                { return parse_oct(st) }
    "" / [1-9]         { return parse_dec(st) }
    '0x' / [0-9a-fA-F] { return parse_hex(st) }
    *                  { return None }
%}

def parse_bin(st):
    n = 0
    while True: %{
        [01] {
            n = n * 2 + (st.yyinput[st.yycursor - 1] - 48)
            break
        }
        * { return n }
    %}

def parse_oct(st):
    n = 0
    while True: %{
        [0-7] {
            n = n * 8 + (st.yyinput[st.yycursor - 1] - 48)
            break
        }
        * { return n }
    %}

def parse_dec(st):
    n = 0
    while True: %{
        [0-9] {
            n = n * 10 + (st.yyinput[st.yycursor - 1] - 48)
            break
        }
        * { return n }
    %}

def parse_hex(st):
    n = 0
    while True: %{
        [0-9] {
            n = n * 16 + (st.yyinput[st.yycursor - 1] - 48)
            break
        }
        [a-f] {
            n = n * 16 + (st.yyinput[st.yycursor - 1] - 87)
            break
        }
        [A-F] {
            n = n * 16 + (st.yyinput[st.yycursor - 1] - 55)
            break
        }
        * { return n }
    %}

assert parse_u32(b"\0") == None
assert parse_u32(b"1234567890\0") == 1234567890
assert parse_u32(b"0b1101\0") == 13
assert parse_u32(b"0x7Fe\0") == 2046
assert parse_u32(b"0644\0") == 420
assert parse_u32(b"9999999999\0") == 9999999999
