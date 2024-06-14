# re2py $INPUT -o $OUTPUT

from enum import Enum
import os

BUFSIZE = 4096
/*!max:re2c*/

class State:
    def __init__(self, fname):
        self.file = open(fname, "rb")
        self.str = bytearray(BUFSIZE)
        self.lim = BUFSIZE - YYMAXFILL
        self.cur = self.lim
        self.mar = self.lim
        self.tok = self.lim
        self.eof = False

    def __del__(self):
        self.file.close()

class Status(Enum):
    OK = 0
    EOF = 1
    LONG_LEXEME = 2

def fill(st, need):
    if st.eof:
        return Status.EOF

    # Error: lexeme too long. In real life could reallocate a larger buffer.
    if st.tok < need:
        return Status.LONG_LEXEME

    # Shift buffer contents (discard everything up to the current token).
    st.str = st.str[st.tok:st.lim]
    st.cur -= st.tok;
    st.mar -= st.tok;
    st.lim -= st.tok;
    st.tok = 0;

    # Fill free space at the end of buffer with new data from file.
    bytes = st.file.read(BUFSIZE - st.lim - 1) # -1 for sentinel
    if not bytes:
        st.eof = True # end of file
        st.lim += YYMAXFILL
        st.str += b"\0" * YYMAXFILL
    else:
        st.lim += len(bytes);
        st.str += bytes

    return Status.OK

def lex(yyrecord):
    count = 0
    while True:
        yyrecord.tok = yyrecord.cur
        /*!re2c
            re2c:api = record;
            re2c:define:YYFILL = "if fill(yyrecord, @@) != Status.OK: return -1";
            re2c:indent:top = 2;

            str = ['] ([^'\\] | [\\][^])* ['];

            [\x00] {
                # Check that it is the sentinel, not some unexpected null.
                return count if yyrecord.tok == yyrecord.lim - YYMAXFILL else -1
            }
            str {
                count += 1
                break
            }
            [ ]+ { break }
            *    { return -1 }
        */

def main():
    fname = "input"

    # Prepare input file.
    f = open(fname, "w")
    for i in range(BUFSIZE):
        f.write("'qu\0tes' 'are' 'fine: \\'' ")
    f.close()

    # Run lexer on the prepared file.
    st = State(fname)
    assert lex(st) == 3 * BUFSIZE

    # Cleanup.
    os.remove(fname)

if __name__ == '__main__':
    main()
