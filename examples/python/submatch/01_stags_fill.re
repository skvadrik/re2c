# re2py $INPUT -o $OUTPUT

from collections import namedtuple
from enum import Enum
import os

BUFSIZE = 4096

SemVer = namedtuple('SemVer', 'major minor patch')

class State:
    def __init__(self, fname):
        self.file = open(fname, "rb")
        self.yyinput = bytearray(BUFSIZE)
        self.yylimit = BUFSIZE - 1 # exclude terminating null
        self.yycursor = self.yylimit
        self.yymarker = self.yylimit
        self.token = self.yylimit
        self.eof = False
        %{stags format = "\n        self.@@ = -1"; %}

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
    %{stags format = "\n    if st.@@ != -1: st.@@ -= st.token"; %}
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

def lex(st, count):
    vers = []
    while True:
        st.token = st.yycursor
    %{
        re2c:api = record;
        re2c:yyrecord = st;
        re2c:YYFILL = "fill(st) == Status.OK";
        re2c:eof = 0;
        re2c:indent:top = 2;
        re2c:tags = 1;

        num = [0-9]+;

        num @t1 "." @t2 num @t3 ("." @t4 num)? [\n] {
            major = int(st.yyinput[st.token:t1])
            minor = int(st.yyinput[t2:t3])
            patch = int(st.yyinput[t4:st.yycursor - 1]) if t4 != -1 else 0
            vers.append(SemVer(major, minor, patch))
            break
        }
        $ { return vers }
        * { return None }
    %}

def main():
    fname = "input"
    verstr = b"1.22.333\n"
    expect = [SemVer(1, 22, 333)] * BUFSIZE

    # Prepare input file.
    f = open(fname, "wb")
    for i in range(BUFSIZE):
        f.write(verstr)
    f.close()

    # Run lexer on the prepared file.
    st = State(fname)
    assert lex(st, 0) == expect

    # Cleanup.
    os.remove(fname)

if __name__ == '__main__':
    main()
