# re2py $INPUT -o $OUTPUT -f

from enum import Enum
import os

# Use a small buffer to cover the case when a lexeme doesn't fit.
# In real world use a larger buffer.
BUFSIZE = 10
DEBUG = False

class State:
    def __init__(self, file):
        self.file = file
        self.buf = bytearray(BUFSIZE)
        self.lim = BUFSIZE - 1 # exclude terminating null
        self.cur = self.lim
        self.mar = self.lim
        self.tok = self.lim
        self.state = -1

class Status(Enum):
    END = 0
    READY = 1
    WAITING = 2
    BIG_PACKET = 3
    BAD_PACKET = 4

def fill(st):
    # Error: lexeme too long. In real life could reallocate a larger buffer.
    if st.tok < 1:
        return Status.BIG_PACKET

    # Shift buffer contents (discard everything up to the current token).
    st.buf = st.buf[st.tok:st.lim]
    st.cur -= st.tok;
    st.mar -= st.tok;
    st.lim -= st.tok;
    st.tok = 0;

    # Fill free space at the end of buffer with new data from file.
    bytes = st.file.read(BUFSIZE - st.lim - 1) # -1 for sentinel
    if bytes:
        st.lim += len(bytes);
        st.buf += bytes

    st.buf += b'\0' # append sentinel

    return Status.READY

def lex(st, recv):
    while True:
        st.tok = st.cur
        /*!re2c
            re2c:define:YYPEEK     = "st.buf[st.cur]";
            re2c:define:YYSKIP     = "st.cur += 1";
            re2c:define:YYBACKUP   = "st.mar = st.cur";
            re2c:define:YYRESTORE  = "st.cur = st.mar";
            re2c:define:YYLESSTHAN = "st.cur >= st.lim";
            re2c:define:YYGETSTATE = "st.state";
            re2c:define:YYSETSTATE = "st.state = @@";
            re2c:define:YYFILL     = "return Status.WAITING, recv";
            re2c:eof = 0;
            re2c:indent:top = 2;

            packet = [a-z]+[;];

            *      { return Status.BAD_PACKET, recv }
            $      { return Status.END, recv }
            packet {
                recv += 1
                break
            }
        */

def test(packets, expect):
    # Create a "socket" (open the same file for reading and writing).
    fname = "pipe"
    fw = open(fname, "wb")
    fr = open(fname, "rb")

    # Initialize lexer state
    st = State(fr)

    # Main loop. The buffer contains incomplete data which appears packet by
    # packet. When the lexer needs more input it saves its internal state and
    # returns to the caller which should provide more input and resume lexing.
    send = 0
    recv = 0
    while True:
        status, recv = lex(st, recv)

        if status == Status.END:
            if DEBUG: print("done: got {} packets".format(recv))
            break

        elif status == Status.WAITING:
            if DEBUG: print("waiting...");

            if send < len(packets):
                if DEBUG: print("sent packet {}: {}".format(send, packets[send]))
                fw.write(packets[send])
                fw.flush()
                send += 1

            status = fill(st)
            if DEBUG: print("queue: '{}', status: {}".format(st.buf, status))
            if status == Status.BIG_PACKET:
                if DEBUG: print("error: packet too big")
                break

            assert status == Status.READY

        else:
            assert status == Status.BAD_PACKET
            if DEBUG: print("error: ill-formed packet")
            break

    # Check results.
    assert status == expect
    if status == Status.END:
        assert recv == send

    # Cleanup: remove input file.
    fr.close()
    fw.close()
    os.remove(fname)

def main():
    test([], Status.END)
    test([b"zero;", b"one;", b"two;", b"three;", b"four;"], Status.END)
    test([b"zer0;"], Status.BAD_PACKET)
    test([b"goooooooooogle;"], Status.BIG_PACKET)

if __name__ == '__main__':
    main()
