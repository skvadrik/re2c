// re2c $INPUT -o $OUTPUT -f
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define DEBUG 0
#define LOG(...) if (DEBUG) fprintf(stderr, __VA_ARGS__);

// Use a small buffer to cover the case when a lexeme doesn't fit.
// In real world use a larger buffer.
#define BUFSIZE 10

typedef struct {
    FILE *file;
    char buf[BUFSIZE + 1], *lim, *cur, *mar, *tok;
    int state;
} State;

typedef enum {END, READY, WAITING, BAD_PACKET, BIG_PACKET} Status;

static Status fill(State *st) {
    const size_t shift = st->tok - st->buf;
    const size_t used = st->lim - st->tok;
    const size_t free = BUFSIZE - used;

    // Error: no space. In real life can reallocate a larger buffer.
    if (free < 1) return BIG_PACKET;

    // Shift buffer contents (discard already processed data).
    memmove(st->buf, st->tok, used);
    st->lim -= shift;
    st->cur -= shift;
    st->mar -= shift;
    st->tok -= shift;

    // Fill free space at the end of buffer with new data.
    const size_t read = fread(st->lim, 1, free, st->file);
    st->lim += read;
    st->lim[0] = 0; // append sentinel symbol

    return READY;
}

static Status lex(State *st, unsigned int *recv) {
    char yych;
    /*!getstate:re2c*/

    for (;;) {
        st->tok = st->cur;
    /*!re2c
        re2c:api:style = free-form;
        re2c:define:YYCTYPE = "char";
        re2c:define:YYCURSOR = "st->cur";
        re2c:define:YYMARKER = "st->mar";
        re2c:define:YYLIMIT = "st->lim";
        re2c:define:YYGETSTATE = "st->state";
        re2c:define:YYSETSTATE = "st->state = @@;";
        re2c:define:YYFILL = "return WAITING;";
        re2c:eof = 0;

        packet = [a-z]+[;];

        *      { return BAD_PACKET; }
        $      { return END; }
        packet { *recv = *recv + 1; continue; }
    */
    }
}

void test(const char **packets, Status expect) {
    // Create a "socket" (open the same file for reading and writing).
    const char *fname = "pipe";
    FILE *fw = fopen(fname, "w");
    FILE *fr = fopen(fname, "r");
    setvbuf(fw, NULL, _IONBF, 0);
    setvbuf(fr, NULL, _IONBF, 0);

    // Initialize lexer state: `state` value is -1, all pointers are at the end
    // of buffer.
    State st;
    st.file = fr;
    st.cur = st.mar = st.tok = st.lim = st.buf + BUFSIZE;
    // Sentinel (at YYLIMIT pointer) is set to zero, which triggers YYFILL.
    st.lim[0] = 0;
    st.state = -1;

    // Main loop. The buffer contains incomplete data which appears packet by
    // packet. When the lexer needs more input it saves its internal state and
    // returns to the caller which should provide more input and resume lexing.
    Status status;
    unsigned int send = 0, recv = 0;
    for (;;) {
        status = lex(&st, &recv);
        if (status == END) {
            LOG("done: got %u packets\n", recv);
            break;
        } else if (status == WAITING) {
            LOG("waiting...\n");
            if (*packets) {
                LOG("sent packet %u\n", send);
                fprintf(fw, "%s", *packets++);
                ++send;
            }
            status = fill(&st);
            LOG("queue: '%s'\n", st.buf);
            if (status == BIG_PACKET) {
                LOG("error: packet too big\n");
                break;
            }
            assert(status == READY);
        } else {
            assert(status == BAD_PACKET);
            LOG("error: ill-formed packet\n");
            break;
        }
    }

    // Check results.
    assert(status == expect);
    if (status == END) assert(recv == send);

    // Cleanup: remove input file.
    fclose(fw);
    fclose(fr);
    remove(fname);
}

int main() {
    const char *packets1[] = {0};
    const char *packets2[] = {"zero;", "one;", "two;", "three;", "four;", 0};
    const char *packets3[] = {"zer0;", 0};
    const char *packets4[] = {"looooooooooong;", 0};

    test(packets1, END);
    test(packets2, END);
    test(packets3, BAD_PACKET);
    test(packets4, BIG_PACKET);

    return 0;
}
