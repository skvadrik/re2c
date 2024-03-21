# re2py $INPUT -o $OUTPUT

class State:
    def __init__(self, str):
        self.str = str
        self.cur = 0
        self.mar = 0

/*!re2c // Common re2c definitions shared between all functions.
    re2c:yyfill:enable = 0;
    re2c:indent:top = 2;
    re2c:define:YYPEEK    = "st.str[st.cur]";
    re2c:define:YYSKIP    = "st.cur += 1";
    re2c:define:YYBACKUP  = "st.mar = st.cur";
    re2c:define:YYRESTORE = "st.cur = st.mar";
    re2c:define:YYSHIFT   = "st.cur += @@";
*/

def parse_u32(str):
    st = State(str)
    /*!local:re2c
        re2c:indent:top = 1;

        '0b' / [01]        { return parse_bin(st) }
        "0"                { return parse_oct(st) }
        "" / [1-9]         { return parse_dec(st) }
        '0x' / [0-9a-fA-F] { return parse_hex(st) }
        *                  { return None }
    */

def parse_bin(st):
    n = 0
    while True:
    /*!re2c
        [01] {
            n = n * 2 + (st.str[st.cur - 1] - 48)
            break
        }
        * { return n }
    */

def parse_oct(st):
    n = 0
    while True:
    /*!re2c
        [0-7] {
            n = n * 8 + (st.str[st.cur - 1] - 48)
            break
        }
        * { return n }
    */

def parse_dec(st):
    n = 0
    while True:
    /*!re2c
        [0-9] {
            n = n * 10 + (st.str[st.cur - 1] - 48)
            break
        }
        * { return n }
    */

def parse_hex(st):
    n = 0
    while True:
    /*!re2c
        [0-9] {
            n = n * 16 + (st.str[st.cur - 1] - 48)
            break
        }
        [a-f] {
            n = n * 16 + (st.str[st.cur - 1] - 87)
            break
        }
        [A-F] {
            n = n * 16 + (st.str[st.cur - 1] - 55)
            break
        }
        * { return n }
    */

assert parse_u32(b"\0") == None
assert parse_u32(b"1234567890\0") == 1234567890
assert parse_u32(b"0b1101\0") == 13
assert parse_u32(b"0x7Fe\0") == 2046
assert parse_u32(b"0644\0") == 420
assert parse_u32(b"9999999999\0") == 9999999999
