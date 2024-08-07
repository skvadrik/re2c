/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -fi --recursive-functions
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG    1
#define LOG(...) if (DEBUG) fprintf(stderr, __VA_ARGS__);
#define BUFSIZE  10

typedef struct {
    FILE *file;
    char buf[BUFSIZE + 1], *lim, *cur, *mar, *tok;
    unsigned yyaccept;
    int state;
    unsigned int packets;
} Input;

static void init(Input *in, FILE *f) {
    in->file = f;
    in->cur = in->mar = in->tok = in->lim = in->buf + BUFSIZE;
    in->lim[0] = 0; // append sentinel symbol
    in->yyaccept = 0;
    in->state = -1;
    in->packets = 0;
}

typedef enum {END, READY, WAITING, BAD_PACKET, BIG_PACKET} Status;

static Status fill(Input *in) {
    const size_t shift = in->tok - in->buf;
    const size_t free = BUFSIZE - (in->lim - in->tok);

    if (free < 1) return BIG_PACKET;

    memmove(in->buf, in->tok, BUFSIZE - shift);
    in->lim -= shift;
    in->cur -= shift;
    in->mar -= shift;
    in->tok -= shift;

    const size_t read = fread(in->lim, 1, free, in->file);
    in->lim += read;
    in->lim[0] = 0; // append sentinel symbol

    return READY;
}


static Status yy0(Input* in);
static Status yy1(Input* in);
static Status yy2(Input* in);
static Status yy3(Input* in);
static Status yy4(Input* in);
static Status yy5(Input* in);
static Status yy6(Input* in);
static Status yy7(Input* in);
static Status lex(Input* in);

static Status yy0(Input* in) {
	char yych = *in->cur;
	switch (yych) {
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
			++in->cur;
			return yy3(in);
		default:
			if (in->lim <= in->cur) {
				in->state = 0;
				return WAITING;
			} else {
				++in->cur;
				return yy1(in);
			}
	}
}

static Status yy1(Input* in) {
	return yy2(in);
}

static Status yy2(Input* in) {
	in->state = -1;
	return BAD_PACKET;
}

static Status yy3(Input* in) {
	char yych = *(in->mar = in->cur);
	switch (yych) {
		case ';':
			++in->cur;
			return yy4(in);
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
			++in->cur;
			return yy5(in);
		default:
			if (in->lim <= in->cur) {
				in->state = 1;
				return WAITING;
			} else {
				return yy2(in);
			}
	}
}

static Status yy4(Input* in) {
	in->state = -1;
	++in->packets; in->tok = in->cur; return lex(in);
}

static Status yy5(Input* in) {
	char yych = *in->cur;
	switch (yych) {
		case ';':
			++in->cur;
			return yy4(in);
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
			++in->cur;
			return yy5(in);
		default:
			if (in->lim <= in->cur) {
				in->state = 2;
				return WAITING;
			} else {
				return yy6(in);
			}
	}
}

static Status yy6(Input* in) {
	in->cur = in->mar;
	return yy2(in);
}

static Status yy7(Input* in) {
	in->state = -1;
	return END;
}

static Status lex(Input* in) {
	switch (in->state) {
		case -1: return yy0(in);
		case 0:
			if (in->lim <= in->cur) return yy7(in);
			else return yy0(in);
		case 1:
			if (in->lim <= in->cur) return yy2(in);
			else return yy3(in);
		case 2:
			if (in->lim <= in->cur) return yy6(in);
			else return yy5(in);
		default: abort();
	}
}



void test(const char **packets, Status status) {
    const char *fname = "pipe";
    FILE *fw = fopen(fname, "w");
    FILE *fr = fopen(fname, "r");
    setvbuf(fw, NULL, _IONBF, 0);
    setvbuf(fr, NULL, _IONBF, 0);

    Input in;
    init(&in, fr);
    Status st;
    unsigned int send = 0;

    for (;;) {
        st = lex(&in);
        if (st == END) {
            LOG("done: got %u packets\n", in.packets);
            break;
        } else if (st == WAITING) {
            LOG("waiting...\n");
            if (*packets) {
                LOG("sent packet %u\n", send);
                fprintf(fw, "%s", *packets++);
                ++send;
            }
            st = fill(&in);
            LOG("queue: '%s'\n", in.buf);
            if (st == BIG_PACKET) {
                LOG("error: packet too big\n");
                break;
            }
            assert(st == READY);
        } else {
            assert(st == BAD_PACKET);
            LOG("error: ill-formed packet\n");
            break;
        }
    }

    LOG("\n");
    assert(st == status);
    if (st == END) assert(in.packets == send);

    fclose(fw);
    fclose(fr);
    remove(fname);
}

int main() {
    const char *packets1[] = {0};
    const char *packets2[] = {"zero;", "one;", "two;", "three;", "four;", 0};
    const char *packets3[] = {"zer0;", 0};
    const char *packets4[] = {"goooooooooogle;", 0};

    test(packets1, END);
    test(packets2, END);
    test(packets3, BAD_PACKET);
    test(packets4, BIG_PACKET);

    return 0;
}
