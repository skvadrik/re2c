# re2py $INPUT -o $OUTPUT

from enum import Enum
import os

BUFSIZE = 4096

class State:
    def __init__(self, fname):
        self.file = open(fname, "rb")
        self.yyinput = bytearray(BUFSIZE)
        self.yylimit = BUFSIZE - 1 # exclude terminating null
        self.yycursor = self.yylimit
        self.yymarker = self.yylimit
        self.token = self.yylimit
        self.eof = False

    def __del__(self):
        self.file.close()

class Status(Enum):
    OK = 0
    EOF = 1
    LONG_LEXEME = 2

def fill(st):
    if st.eof:
        return Status.EOF

    # Error: lexeme too long. In real life could reallocate a larger buffer.
    if st.token < 1:
        return Status.LONG_LEXEME

    # Shift buffer contents (discard everything up to the current token).
    st.yyinput = st.yyinput[st.token:st.yylimit]
    st.yycursor -= st.token;
    st.yymarker -= st.token;
    st.yylimit -= st.token;
    st.token = 0;

    # Fill free space at the end of buffer with new data from file.
    bytes = st.file.read(BUFSIZE - st.yylimit - 1) # -1 for sentinel
    if not bytes:
        st.eof = True # end of file
    else:
        st.yylimit += len(bytes);
        st.yyinput += bytes

    st.yyinput += b'\0' # append sentinel

    return Status.OK

def lex(yyrecord, count):
    while True:
        yyrecord.token = yyrecord.yycursor
    %{
        re2c:api = record;
        re2c:define:YYFILL = "fill(yyrecord) == Status.OK";
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

def main():
    fname = "input"

    # Prepare input file.
    f = open(fname, "w")
    for i in range(BUFSIZE):
        f.write("'qu\0tes' 'are' 'fine: \\'' ")
    f.close()

    # Run lexer on the prepared file.
    st = State(fname)
    assert lex(st, 0) == 3 * BUFSIZE

    # Cleanup.
    os.remove(fname)

if __name__ == '__main__':
    main()
