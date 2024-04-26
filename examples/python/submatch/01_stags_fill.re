# re2py $INPUT -o $OUTPUT

from collections import namedtuple
from enum import Enum
import os

NONE = -1
BUFSIZE = 4096

SemVer = namedtuple('SemVer', 'major minor patch')

class State:
    def __init__(self, fname):
        self.file = open(fname, "rb")
        self.buf = bytearray(BUFSIZE)
        self.lim = BUFSIZE - 1 # exclude terminating null
        self.cur = self.lim
        self.mar = self.lim
        self.tok = self.lim
        self.eof = False
        /*!stags:re2c format = "\n        self.@@ = NONE"; */

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
    if st.tok < 1:
        return Status.LONG_LEXEME

    # Shift buffer contents (discard everything up to the current token).
    st.buf = st.buf[st.tok:st.lim]
    st.cur -= st.tok;
    st.mar -= st.tok;
    st.lim -= st.tok;
    st.tok = 0;

    # Fill free space at the end of buffer with new data from file.
    bytes = st.file.read(BUFSIZE - st.lim - 1) # -1 for sentinel
    if not bytes:
        st.eof = True # end of file
    else:
        st.lim += len(bytes);
        st.buf += bytes

    st.buf += b'\0' # append sentinel

    return Status.OK

def lex(st, count):
    vers = []
    while True:
        st.tok = st.cur
        /*!re2c
            re2c:define:YYPEEK      = "st.buf[st.cur]";
            re2c:define:YYSKIP      = "st.cur += 1";
            re2c:define:YYBACKUP    = "st.mar = st.cur";
            re2c:define:YYRESTORE   = "st.cur = st.mar";
            re2c:define:YYSETSTAGP  = "@@{tag} = st.cur";
            re2c:define:YYSETSTAGN  = "@@{tag} = NONE";
            re2c:define:YYSHIFTSTAG = "@@{tag} += @@{shift}";
            re2c:define:YYLESSTHAN  = "st.cur >= st.lim";
            re2c:define:YYFILL      = "fill(st) == Status.OK";
            re2c:eof = 0;
            re2c:indent:top = 2;
            re2c:tags = 1;
            re2c:tags:expression = "st.@@";

            num = [0-9]+;

            num @t1 "." @t2 num @t3 ("." @t4 num)? [\n] {
                major = int(st.buf[st.tok:t1]);
                minor = int(st.buf[t2:t3]);
                patch = int(st.buf[t4:st.cur - 1]) if t4 != NONE else 0
                vers.append(SemVer(major, minor, patch))
                break
            }
            $ { return vers }
            * { return None }
        */

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
