#include "common.h"

static void prolog(Output *out);
static void epilog(Output *out);

typedef struct {
    char *buf, *p, *pe, *end;
} Input;

static void init_input(Input *in)
{
    in->buf = (char*) malloc(SIZE);
    in->p = in->pe = in->end = in->buf;
}

static void free_input(Input *in)
{
    free(in->buf);
}

static void lex(Input *in, Output *out);

int main(int argc, char **argv)
{
    PRE
    Input in;
    Output out;

    init_input(&in);
    init_output(&out);
    prolog(&out);

    while (1) {
        size_t space = SIZE - (in.end - in.buf);

        if (space == 0) {
            fprintf(stderr, "no space in buffer\n");
            break;
        }

        in.end += fread(in.end, 1, space, stdin);

        /* Find the last newline by searching backwards. */
        for (in.pe = in.end; in.pe > in.p && in.pe[-1] != '\n'; --in.pe);

        lex(&in, &out);

        /* If the buffer is not full, this is the end of input. */
        if (in.end < in.buf + SIZE) {
            if (in.pe != in.end) {
                fprintf(stderr, "text left at the end of buffer\n");
            }
            break;
        }

        /* Shift the remaining tail to the beginning of buffer. */
        size_t left = in.end - in.pe;
        memmove(in.buf, in.pe, left);
        in.p = in.buf;
        in.pe = in.end = in.buf + left;
    }

    epilog(&out);
    flush(&out);
    free_output(&out);
    free_input(&in);

    POST
    return 0;
}
