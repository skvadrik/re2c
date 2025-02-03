// re2java $INPUT -o $OUTPUT -f

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.Pipe;

class Lexer {
    enum Status {
        END,
        READY,
        WAITING,
        BIG_PACKET,
        BAD_PACKET
    };

    // Use a small buffer to cover the case when a lexeme doesn't fit.
    // In real world use a larger buffer.
    public static final int BUFSIZE = 10;

    public static class State {
        Pipe.SourceChannel source;
        byte[] yyinput;
        int yycursor;
        int yymarker;
        int yylimit;
        int token;
        int yystate;
        int received;

        public State(Pipe pipe) {
            source = pipe.source();
            // Sentinel at `yylimit` offset is set to zero, which triggers YYFILL.
            yyinput = new byte[BUFSIZE + 1];
            yycursor = yymarker = yylimit = token = BUFSIZE;
            yystate = -1;
            received = 0;
        }
    }

    private static void log(String format, Object... args) {
        if (false) { System.out.printf(format + "\n", args); }
    }

    private static Status fill(State st) throws IOException {
        // Error: lexeme too long. In real life can reallocate a larger buffer.
        if (st.token < 1) { return Status.BIG_PACKET; }

        // Shift buffer contents (discard everything up to the current token).
        System.arraycopy(st.yyinput, st.token, st.yyinput, 0, st.yylimit - st.token); 
        st.yycursor -= st.token;
        st.yymarker -= st.token;
        st.yylimit -= st.token;
        st.token = 0;

        // Fill free space at the end of buffer with new data from file.
        ByteBuffer buffer = ByteBuffer.wrap(st.yyinput, st.yylimit, BUFSIZE - st.yylimit);
        int have = st.source.read(buffer);
        if (have != -1) st.yylimit += have; // -1 means that pipe is closed
        st.yyinput[st.yylimit] = 0; // append sentinel symbol

        return Status.READY;
    }

    private static Status lex(State yyrecord) {
        byte yych;
        loop: while (true) {
            yyrecord.token = yyrecord.yycursor;
            /*!re2c
                re2c:api = record;
                re2c:YYCTYPE = "byte";
                re2c:YYPEEK = "yyrecord.yyinput[yyrecord.yycursor]";
                re2c:YYFILL = "return Status.WAITING;";
                re2c:eof = 0;

                packet = [a-z]+[;];

                *      { return Status.BAD_PACKET; }
                $      { return Status.END; }
                packet { yyrecord.received += 1; continue loop; }
            */
        }
    }

    public static void test(String[] packets, Status expect) throws IOException {
        // Create a pipe.
        Pipe pipe = Pipe.open();
        Pipe.SinkChannel sink = pipe.sink();

        // Initialize lexer state
        Lexer.State st = new Lexer.State(pipe);

        // Main loop. The buffer contains incomplete data which appears packet by
        // packet. When the lexer needs more input it saves its internal state and
        // returns to the caller which should provide more input and resume lexing.
        int send = 0;
        Status status;
        while (true) {
            status = lex(st);

            if (status == Status.END) {
                log("done: got %d packets", st.received);
                break;
            } else if (status == Status.WAITING) {
                log("waiting...");

                if (send < packets.length) {
                    log("sent packet %d: %s", send, packets[send]);
                    ByteBuffer buffer = ByteBuffer.wrap(packets[send].getBytes());
                    sink.write(buffer);
                    send += 1;
                } else {
                    sink.close();
                }

                status = fill(st);
                if (status == Status.BIG_PACKET) {
                    log("error: packet too big");
                    break;
                }
                assert status == Status.READY;
            } else {
                assert status == Status.BAD_PACKET;
                log("error: ill-formed packet");
                break;
            }
        }

        // Check results.
        assert status == expect;
        if (status == Status.END) {
            assert send == st.received;
        }
    }

    public static void main(String []args) throws IOException {
        test(new String[]{}, Status.END);
        test(new String[]{"zero;", "one;", "two;", "three;", "four;"}, Status.END);
        test(new String[]{"zer0;"}, Status.BAD_PACKET);
        test(new String[]{"goooooooooogle;"}, Status.BIG_PACKET);
    }
};
