/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define YYMAXFILL 7

static const size_t SIZE = 4096;

typedef struct {
    FILE *file;
    char *buf;
    char *lim;
    char *cur;
    char *mar;
    char *tok;
    char *yyt1;
char *yyt10;
char *yyt11;
char *yyt12;
char *yyt13;
char *yyt2;
char *yyt3;
char *yyt4;
char *yyt5;
char *yyt6;
char *yyt7;
char *yyt8;
char *yyt9;

    int eof;
} input_t;

static void init_input(input_t *in, const char *fname)
{
    in->file = fopen(fname, "r");
    in->buf = (char*) malloc(SIZE + YYMAXFILL);
    in->lim = in->buf + SIZE;
    in->cur = in->lim;
    in->mar = in->lim;
    in->tok = in->lim;
    in->yyt1 = 0;
in->yyt10 = 0;
in->yyt11 = 0;
in->yyt12 = 0;
in->yyt13 = 0;
in->yyt2 = 0;
in->yyt3 = 0;
in->yyt4 = 0;
in->yyt5 = 0;
in->yyt6 = 0;
in->yyt7 = 0;
in->yyt8 = 0;
in->yyt9 = 0;

    in->eof = 0;
}

static void free_input(input_t *in)
{
    free(in->buf);
    fclose(in->file);
}

static int fill(input_t *in, size_t need)
{
    size_t free;

    if (in->eof) return 1;

    free = in->tok - in->buf;
    if (free < need) return 2;

    memmove(in->buf, in->tok, in->lim - in->tok);
    in->lim -= free;
    in->cur -= free;
    in->mar -= free;
    in->tok -= free;
    if (in->yyt1) in->yyt1 -= free;
if (in->yyt10) in->yyt10 -= free;
if (in->yyt11) in->yyt11 -= free;
if (in->yyt12) in->yyt12 -= free;
if (in->yyt13) in->yyt13 -= free;
if (in->yyt2) in->yyt2 -= free;
if (in->yyt3) in->yyt3 -= free;
if (in->yyt4) in->yyt4 -= free;
if (in->yyt5) in->yyt5 -= free;
if (in->yyt6) in->yyt6 -= free;
if (in->yyt7) in->yyt7 -= free;
if (in->yyt8) in->yyt8 -= free;
if (in->yyt9) in->yyt9 -= free;

    in->lim += fread(in->lim, 1, free, in->file);
    if (in->lim < in->buf + SIZE) {
        in->eof = 1;
        memset(in->lim, 0, YYMAXFILL);
        in->lim += YYMAXFILL;
    }
    return 0;
}

static int lex(input_t *in, long *count, long *total)
{
    const char
        *s1, *u1, *h1, *r1, *p1, *q1, *f1,
        *s2, *u2, *h2, *r2, *p2, *q2, *f2;
    long c, t;

    c = 0; t = 0;
loop:
    in->tok = in->cur;

{
	char yych;
	if ((in->lim - in->cur) < 7) if (fill(in, 7) != 0) return 2;
	yych = *in->cur;
	switch (yych) {
		case 0x00: goto yy1;
		case '\n': goto yy4;
		case '+':
		case '-':
		case '.':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
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
			in->yyt1 = in->cur;
			goto yy5;
		default: goto yy2;
	}
yy1:
	++in->cur;
	{ *count = c; *total = t; return 0; }
yy2:
	++in->cur;
yy3:
	{ return 1; }
yy4:
	++in->cur;
	{ goto loop; }
yy5:
	yych = *(in->mar = ++in->cur);
	switch (yych) {
		case '+':
		case '-':
		case '.':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case ':':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
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
		case 'z': goto yy7;
		default: goto yy3;
	}
yy6:
	++in->cur;
	if ((in->lim - in->cur) < 6) if (fill(in, 6) != 0) return 2;
	yych = *in->cur;
yy7:
	switch (yych) {
		case '+':
		case '-':
		case '.':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
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
		case 'z': goto yy6;
		case ':':
			in->yyt2 = in->cur;
			goto yy9;
		default: goto yy8;
	}
yy8:
	in->cur = in->mar;
	goto yy3;
yy9:
	yych = *++in->cur;
	switch (yych) {
		case '!':
		case '$':
		case '%':
		case '&':
		case '\'':
		case '(':
		case ')':
		case '*':
		case '+':
		case ',':
		case '-':
		case '.':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case ':':
		case ';':
		case '=':
		case '@':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
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
		case '~':
			in->yyt7 = NULL;
			in->yyt8 = NULL;
			in->yyt9 = NULL;
			in->yyt10 = NULL;
			in->yyt11 = NULL;
			in->yyt12 = in->cur;
			goto yy11;
		case '#':
			in->yyt3 = in->cur;
			in->yyt4 = NULL;
			in->yyt7 = NULL;
			in->yyt8 = NULL;
			in->yyt9 = NULL;
			in->yyt10 = NULL;
			in->yyt11 = NULL;
			in->yyt12 = in->cur;
			in->yyt13 = NULL;
			goto yy13;
		case '/':
			in->yyt7 = NULL;
			in->yyt8 = NULL;
			in->yyt9 = NULL;
			in->yyt10 = NULL;
			in->yyt11 = NULL;
			in->yyt12 = in->cur;
			goto yy14;
		case '?':
			in->yyt3 = in->cur;
			in->yyt7 = NULL;
			in->yyt8 = NULL;
			in->yyt9 = NULL;
			in->yyt10 = NULL;
			in->yyt11 = NULL;
			in->yyt12 = in->cur;
			goto yy15;
		default:
			in->yyt3 = in->cur;
			in->yyt4 = NULL;
			in->yyt5 = NULL;
			in->yyt6 = NULL;
			in->yyt7 = NULL;
			in->yyt8 = NULL;
			in->yyt9 = NULL;
			in->yyt10 = NULL;
			in->yyt11 = NULL;
			in->yyt12 = in->cur;
			in->yyt13 = NULL;
			goto yy10;
	}
yy10:
	s1 = in->yyt1;
	s2 = in->yyt2;
	u1 = in->yyt7;
	u2 = in->yyt8;
	h1 = in->yyt9;
	h2 = in->yyt10;
	r1 = in->yyt11;
	r2 = in->yyt11;
	p1 = in->yyt12;
	p2 = in->yyt3;
	q1 = in->yyt13;
	q2 = in->yyt4;
	f1 = in->yyt5;
	f2 = in->yyt6;
	{
#ifndef VERIFY
        c += 1;
        t += (s2 - s1) + (u2 - u1) + (h2 - h1)
            + (r2 - r1) + (p2 - p1) + (q2 - q1) + (f2 - f1);
#else
                printf("%.*s:", (int)(s2 - s1), s1);
        if (h1) printf("//");
        if (u1) printf("%.*s@", (int)(u2 - u1), u1);
        if (h1) printf("%.*s",  (int)(h2 - h1), h1);
        if (r1) printf(":%.*s", (int)(r2 - r1), r1);
                printf("%.*s",  (int)(p2 - p1), p1);
        if (q1) printf("?%.*s", (int)(q2 - q1), q1);
        if (f1) printf("#%.*s", (int)(f2 - f1), f1);
        printf("\n");
#endif
        goto loop;
    }
yy11:
	++in->cur;
	if ((in->lim - in->cur) < 3) if (fill(in, 3) != 0) return 2;
	yych = *in->cur;
yy12:
	switch (yych) {
		case '!':
		case '$':
		case '%':
		case '&':
		case '\'':
		case '(':
		case ')':
		case '*':
		case '+':
		case ',':
		case '-':
		case '.':
		case '/':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case ':':
		case ';':
		case '=':
		case '@':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
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
		case '~': goto yy11;
		case '#':
			in->yyt3 = in->cur;
			in->yyt4 = NULL;
			in->yyt13 = NULL;
			goto yy13;
		case '?':
			in->yyt3 = in->cur;
			goto yy15;
		default:
			in->yyt3 = in->cur;
			in->yyt4 = NULL;
			in->yyt5 = NULL;
			in->yyt6 = NULL;
			in->yyt13 = NULL;
			goto yy10;
	}
yy13:
	yych = *++in->cur;
	switch (yych) {
		case '!':
		case '$':
		case '%':
		case '&':
		case '\'':
		case '(':
		case ')':
		case '*':
		case '+':
		case ',':
		case '-':
		case '.':
		case '/':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case ':':
		case ';':
		case '=':
		case '?':
		case '@':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
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
		case '~':
			in->yyt5 = in->cur;
			goto yy16;
		default:
			in->yyt5 = in->cur;
			in->yyt6 = in->cur;
			goto yy10;
	}
yy14:
	yych = *++in->cur;
	switch (yych) {
		case '/': goto yy17;
		default: goto yy12;
	}
yy15:
	yych = *++in->cur;
	switch (yych) {
		case '!':
		case '$':
		case '%':
		case '&':
		case '\'':
		case '(':
		case ')':
		case '*':
		case '+':
		case ',':
		case '-':
		case '.':
		case '/':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case ':':
		case ';':
		case '=':
		case '?':
		case '@':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
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
		case '~':
			in->yyt13 = in->cur;
			goto yy18;
		case '#':
			in->yyt4 = in->cur;
			in->yyt13 = in->cur;
			goto yy13;
		default:
			in->yyt4 = in->cur;
			in->yyt5 = NULL;
			in->yyt6 = NULL;
			in->yyt13 = in->cur;
			goto yy10;
	}
yy16:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 2;
	yych = *in->cur;
	switch (yych) {
		case '!':
		case '$':
		case '%':
		case '&':
		case '\'':
		case '(':
		case ')':
		case '*':
		case '+':
		case ',':
		case '-':
		case '.':
		case '/':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case ':':
		case ';':
		case '=':
		case '?':
		case '@':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
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
		case '~': goto yy16;
		default:
			in->yyt6 = in->cur;
			goto yy10;
	}
yy17:
	yych = *++in->cur;
	switch (yych) {
		case '!':
		case '$':
		case '%':
		case '&':
		case '\'':
		case '(':
		case ')':
		case '*':
		case '+':
		case ',':
		case '-':
		case '.':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case ':':
		case ';':
		case '=':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
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
		case '~':
			in->yyt3 = in->cur;
			in->yyt7 = NULL;
			in->yyt8 = NULL;
			in->yyt9 = in->cur;
			goto yy19;
		case '[':
		case ']':
			in->yyt7 = NULL;
			in->yyt8 = NULL;
			in->yyt9 = in->cur;
			goto yy20;
		default: goto yy12;
	}
yy18:
	++in->cur;
	if ((in->lim - in->cur) < 2) if (fill(in, 2) != 0) return 2;
	yych = *in->cur;
	switch (yych) {
		case '!':
		case '$':
		case '%':
		case '&':
		case '\'':
		case '(':
		case ')':
		case '*':
		case '+':
		case ',':
		case '-':
		case '.':
		case '/':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case ':':
		case ';':
		case '=':
		case '?':
		case '@':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
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
		case '~': goto yy18;
		case '#':
			in->yyt4 = in->cur;
			goto yy13;
		default:
			in->yyt4 = in->cur;
			in->yyt5 = NULL;
			in->yyt6 = NULL;
			goto yy10;
	}
yy19:
	++in->cur;
	if ((in->lim - in->cur) < 4) if (fill(in, 4) != 0) return 2;
	yych = *in->cur;
	switch (yych) {
		case '!':
		case '$':
		case '%':
		case '&':
		case '\'':
		case '(':
		case ')':
		case '*':
		case '+':
		case ',':
		case '-':
		case '.':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case ':':
		case ';':
		case '=':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
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
		case '~': goto yy19;
		case '#':
			in->yyt3 = in->cur;
			in->yyt4 = NULL;
			in->yyt10 = in->cur;
			in->yyt11 = NULL;
			in->yyt12 = in->cur;
			in->yyt13 = NULL;
			goto yy13;
		case '/':
			in->yyt10 = in->cur;
			in->yyt11 = NULL;
			in->yyt12 = in->cur;
			goto yy11;
		case '?':
			in->yyt3 = in->cur;
			in->yyt10 = in->cur;
			in->yyt11 = NULL;
			in->yyt12 = in->cur;
			goto yy15;
		case '@':
			in->yyt4 = in->cur;
			in->yyt10 = in->cur;
			in->yyt11 = NULL;
			in->yyt12 = in->cur;
			goto yy21;
		case '[':
		case ']': goto yy20;
		default:
			in->yyt3 = in->cur;
			in->yyt4 = NULL;
			in->yyt5 = NULL;
			in->yyt6 = NULL;
			in->yyt10 = in->cur;
			in->yyt11 = NULL;
			in->yyt12 = in->cur;
			in->yyt13 = NULL;
			goto yy10;
	}
yy20:
	++in->cur;
	if ((in->lim - in->cur) < 3) if (fill(in, 3) != 0) return 2;
	yych = *in->cur;
	switch (yych) {
		case '!':
		case '$':
		case '%':
		case '&':
		case '\'':
		case '(':
		case ')':
		case '*':
		case '+':
		case ',':
		case '-':
		case '.':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case ':':
		case ';':
		case '=':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '[':
		case ']':
		case '_':
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
		case '~': goto yy20;
		case '#':
			in->yyt3 = in->cur;
			in->yyt4 = NULL;
			in->yyt10 = in->cur;
			in->yyt11 = NULL;
			in->yyt12 = in->cur;
			in->yyt13 = NULL;
			goto yy13;
		case '/':
		case '@':
			in->yyt10 = in->cur;
			in->yyt11 = NULL;
			in->yyt12 = in->cur;
			goto yy11;
		case '?':
			in->yyt3 = in->cur;
			in->yyt10 = in->cur;
			in->yyt11 = NULL;
			in->yyt12 = in->cur;
			goto yy15;
		default:
			in->yyt3 = in->cur;
			in->yyt4 = NULL;
			in->yyt5 = NULL;
			in->yyt6 = NULL;
			in->yyt10 = in->cur;
			in->yyt11 = NULL;
			in->yyt12 = in->cur;
			in->yyt13 = NULL;
			goto yy10;
	}
yy21:
	yych = *++in->cur;
	switch (yych) {
		case '!':
		case '$':
		case '%':
		case '&':
		case '\'':
		case '(':
		case ')':
		case '*':
		case '+':
		case ',':
		case '-':
		case '.':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case ':':
		case ';':
		case '=':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '[':
		case ']':
		case '_':
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
		case '~':
			in->yyt7 = in->yyt3;
			in->yyt8 = in->yyt4;
			in->yyt9 = in->cur;
			goto yy20;
		default: goto yy12;
	}
}

}

int main(int argc, char **argv)
{
    long count, total;
    input_t in;
    init_input(&in, argv[1]);

    switch (lex(&in, &count, &total)) {
        case 0: fprintf(stderr, "ok, parsed %ld URIs, peeked %ld chars\n", count, total); break;
        case 1: fprintf(stderr, "syntax error\n"); break;
        case 2: fprintf(stderr, "yyfill failed\n"); break;
        default: fprintf(stderr, "panic!\n"); break;
    }

    free_input(&in);
    return 0;
}
tags/bench_uri_simple.re:99:8: warning: tag `u1` has 2nd degree of nondeterminism [-Wnondeterministic-tags]
tags/bench_uri_simple.re:99:8: warning: tag `u2` has 2nd degree of nondeterminism [-Wnondeterministic-tags]
tags/bench_uri_simple.re:99:8: warning: tag `h1` has 2nd degree of nondeterminism [-Wnondeterministic-tags]
tags/bench_uri_simple.re:99:8: warning: tag `h2` has 2nd degree of nondeterminism [-Wnondeterministic-tags]
tags/bench_uri_simple.re:99:8: warning: tag `r1` has 2nd degree of nondeterminism [-Wnondeterministic-tags]
tags/bench_uri_simple.re:99:8: warning: tag `r2` has 2nd degree of nondeterminism [-Wnondeterministic-tags]
tags/bench_uri_simple.re:99:8: warning: tag `p1` has 2nd degree of nondeterminism [-Wnondeterministic-tags]
