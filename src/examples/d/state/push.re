// re2d $INPUT -o $OUTPUT -f
module main;

import core.stdc.stdio;
import core.stdc.string;

// Use a small buffer to cover the case when a lexeme doesn't fit.
// In real world use a larger buffer.
enum BUFSIZE = 10;

struct State {
    FILE* file;
    char[BUFSIZE + 1] buffer;
    char* yylimit, yycursor, yymarker, token;
    int yystate;
};

enum Status {END, READY, WAITING, BAD_PACKET, BIG_PACKET};

private Status fill(ref State st) {
    const size_t shift = st.token - cast(char*)st.buffer;
    const size_t used = st.yylimit - st.token;
    const size_t free = BUFSIZE - used;

    // Error: no space. In real life can reallocate a larger buffer.
    if (free < 1) return Status.BIG_PACKET;

    // Shift buffer contents (discard already processed data).
    memmove(cast(void*)st.buffer, st.token, used);
    st.yylimit -= shift;
    st.yycursor -= shift;
    st.yymarker -= shift;
    st.token -= shift;

    // Fill free space at the end of buffer with new data.
    const size_t read = fread(st.yylimit, 1, free, st.file);
    st.yylimit += read;
    st.yylimit[0] = 0; // append sentinel symbol

    return Status.READY;
}

private Status lex(ref State yyrecord, uint* recv) {
    char yych;
    /*!getstate:re2c*/

    for (;;) {
        yyrecord.token = yyrecord.yycursor;
    /*!re2c
        re2c:api = record;
        re2c:YYCTYPE = char;
        re2c:YYFILL = "return Status.WAITING;";
        re2c:eof = 0;

        packet = [a-z]+[;];

        *      { return Status.BAD_PACKET; }
        $      { return Status.END; }
        packet { *recv = *recv + 1; continue; }
    */
    }
    assert(0); // unreachable
}

private void test(string[] packets, Status expect) {
    // Create a pipe (open the same file for reading and writing).
    const(char*) fname = "pipe";
    FILE* fw = fopen(fname, "w");
    FILE* fr = fopen(fname, "r");
    setvbuf(fw, null, _IONBF, 0);
    setvbuf(fr, null, _IONBF, 0);

    // Initialize lexer state: `state` value is -1, all pointers are at the end
    // of buffer.
    State st;
    st.file = fr;
    st.yycursor = st.yymarker = st.token = st.yylimit = cast(char*)st.buffer + BUFSIZE;
    // Sentinel (at YYLIMIT pointer) is set to zero, which triggers YYFILL.
    st.yylimit[0] = 0;
    st.yystate = -1;

    // Main loop. The buffer contains incomplete data which appears packet by
    // packet. When the lexer needs more input it saves its internal state and
    // returns to the caller which should provide more input and resume lexing.
    Status status;
    uint send = 0, recv = 0;
    for (;;) {
        status = lex(st, &recv);
        if (status == Status.END) {
            debug{printf("done: got %u packets\n", recv);}
            break;
        } else if (status == Status.WAITING) {
            debug{printf("waiting...\n");}
            if (send < packets.length) {
                debug{printf("sent packet %u\n", send);}
                fprintf(fw, "%s", cast(char*)packets[send]);
                ++send;
            }
            status = fill(st);
            debug{printf("queue: '%s'\n", cast(char*)st.buffer);}
            if (status == Status.BIG_PACKET) {
                debug{printf("error: packet too big\n");}
                break;
            }
            assert(status == Status.READY);
        } else {
            assert(status == Status.BAD_PACKET);
            debug{printf("error: ill-formed packet\n");}
            break;
        }
    }

    // Check results.
    assert(status == expect);
    if (status == Status.END) assert(recv == send);

    // Cleanup: remove input file.
    fclose(fw);
    fclose(fr);
    remove(fname);
}

void main() {
    string[] packets1 = [];
    string[] packets2 = ["zero;", "one;", "two;", "three;", "four;"];
    string[] packets3 = ["zer0;"];
    string[] packets4 = ["looooooooooong;"];

    test(packets1, Status.END);
    test(packets2, Status.END);
    test(packets3, Status.BAD_PACKET);
    test(packets4, Status.BIG_PACKET);
}
