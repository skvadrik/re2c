
#line 1 "cunroll.re"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define	ADDEQ	257
#define	ANDAND	258
#define	ANDEQ	259
#define	ARRAY	260
#define	ASM	261
#define	AUTO	262
#define	BREAK	263
#define	CASE	264
#define	CHAR	265
#define	CONST	266
#define	CONTINUE	267
#define	DECR	268
#define	DEFAULT	269
#define	DEREF	270
#define	DIVEQ	271
#define	DO	272
#define	DOUBLE	273
#define	ELLIPSIS	274
#define	ELSE	275
#define	ENUM	276
#define	EQL	277
#define	EXTERN	278
#define	FCON	279
#define	FLOAT	280
#define	FOR	281
#define	FUNCTION	282
#define	GEQ	283
#define	GOTO	284
#define	ICON	285
#define	ID	286
#define	IF	287
#define	INCR	288
#define	INT	289
#define	LEQ	290
#define	LONG	291
#define	LSHIFT	292
#define	LSHIFTEQ	293
#define	MODEQ	294
#define	MULEQ	295
#define	NEQ	296
#define	OREQ	297
#define	OROR	298
#define	POINTER	299
#define	REGISTER	300
#define	RETURN	301
#define	RSHIFT	302
#define	RSHIFTEQ	303
#define	SCON	304
#define	SHORT	305
#define	SIGNED	306
#define	SIZEOF	307
#define	STATIC	308
#define	STRUCT	309
#define	SUBEQ	310
#define	SWITCH	311
#define	TYPEDEF	312
#define	UNION	313
#define	UNSIGNED	314
#define	VOID	315
#define	VOLATILE	316
#define	WHILE	317
#define	XOREQ	318
#define	EOI	319

typedef unsigned int uint;
typedef unsigned char uchar;

#define	BSIZE	8192

#define	YYCTYPE		uchar
#define	YYCURSOR	cursor
#define	YYLIMIT		s->lim
#define	YYMARKER	s->ptr
#define	YYFILL(n)	{cursor = fill(s, cursor);}

#define	RET(i)	{s->cur = cursor; return i;}

typedef struct Scanner {
    int			fd;
    uchar		*bot, *tok, *ptr, *cur, *pos, *lim, *top, *eof;
    uint		line;
} Scanner;

uchar *fill(Scanner *s, uchar *cursor){
    if(!s->eof){
	uint cnt = s->tok - s->bot;
	if(cnt){
	    memcpy(s->bot, s->tok, s->lim - s->tok);
	    s->tok = s->bot;
	    s->ptr -= cnt;
	    cursor -= cnt;
	    s->pos -= cnt;
	    s->lim -= cnt;
	}
	if((s->top - s->lim) < BSIZE){
	    uchar *buf = (uchar*) malloc(((s->lim - s->bot) + BSIZE)*sizeof(uchar));
	    memcpy(buf, s->tok, s->lim - s->tok);
	    s->tok = buf;
	    s->ptr = &buf[s->ptr - s->bot];
	    cursor = &buf[cursor - s->bot];
	    s->pos = &buf[s->pos - s->bot];
	    s->lim = &buf[s->lim - s->bot];
	    s->top = &s->lim[BSIZE];
	    free(s->bot);
	    s->bot = buf;
	}
	if((cnt = read(s->fd, (char*) s->lim, BSIZE)) != BSIZE){
	    s->eof = &s->lim[cnt]; *(s->eof)++ = '\n';
	}
	s->lim += cnt;
    }
    return cursor;
}

int scan(Scanner *s){
	uchar *cursor = s->cur;
std:
	s->tok = cursor;
#line 135 "cunroll.re"



#line 7 "<stdout>"
{
	YYCTYPE yych;
	unsigned int yyaccept;
	goto yy0;
yy1:	++YYCURSOR;
yy0:
	if((YYLIMIT - YYCURSOR) < 9) YYFILL(9);
	yych = *YYCURSOR;
	switch(yych){
	case 0x09:	case 0x0B:
	case 0x0C:	case ' ':	goto yy58;
	case 0x0A:	goto yy60;
	case '!':	goto yy34;
	case '"':	goto yy13;
	case '%':	goto yy24;
	case '&':	goto yy26;
	case '\'':	goto yy9;
	case '(':	goto yy46;
	case ')':	goto yy48;
	case '*':	goto yy22;
	case '+':	goto yy18;
	case ',':	goto yy42;
	case '-':	goto yy20;
	case '.':	goto yy11;
	case '/':	goto yy2;
	case '0':	goto yy6;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy8;
	case ':':	goto yy44;
	case ';':	goto yy36;
	case '<':	goto yy16;
	case '=':	goto yy32;
	case '>':	goto yy14;
	case '?':	goto yy56;
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
	case 'Z':	case '_':	case 'a':
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
	case 'z':	goto yy4;
	case '[':	goto yy50;
	case ']':	goto yy52;
	case '^':	goto yy28;
	case '{':	goto yy38;
	case '|':	goto yy30;
	case '}':	goto yy40;
	case '~':	goto yy54;
	default:	goto yy62;
	}
yy2:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '*':	goto yy183;
	case '=':	goto yy181;
	default:	goto yy3;
	}
yy3:
#line 200 "cunroll.re"
{ RET('/'); }
#line 118 "<stdout>"
yy4:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	case 'A':
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
	case 'Z':	case '_':	case 'a':
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
	case 'z':	goto yy164;
	default:	goto yy5;
	}
yy5:
#line 141 "cunroll.re"
{ RET(ID); }
#line 186 "<stdout>"
yy6:	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	switch(yych){
	case 'L':	case 'U':	case 'l':	case 'u':	goto yy140;
	case 'X':	case 'x':	goto yy157;
	default:	goto yy156;
	}
yy7:
#line 153 "cunroll.re"
{ RET(ICON); }
#line 197 "<stdout>"
yy8:	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	goto yy138;
yy9:	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	switch(yych){
	case 0x0A:	goto yy10;
	default:	goto yy128;
	}
yy10:
#line 219 "cunroll.re"
{
		printf("unexpected character: %c\n", *s->tok);
		goto std;
	    }
#line 213 "<stdout>"
yy11:	yyaccept = 2;
	yych = *(YYMARKER = ++YYCURSOR);
	switch(yych){
	case '.':	goto yy116;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy117;
	default:	goto yy12;
	}
yy12:
#line 193 "cunroll.re"
{ RET('.'); }
#line 233 "<stdout>"
yy13:	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	switch(yych){
	case 0x0A:	goto yy10;
	default:	goto yy106;
	}
yy14:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '=':	goto yy99;
	case '>':	goto yy101;
	default:	goto yy15;
	}
yy15:
#line 203 "cunroll.re"
{ RET('>'); }
#line 249 "<stdout>"
yy16:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '<':	goto yy95;
	case '=':	goto yy93;
	default:	goto yy17;
	}
yy17:
#line 202 "cunroll.re"
{ RET('<'); }
#line 259 "<stdout>"
yy18:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '+':	goto yy89;
	case '=':	goto yy91;
	default:	goto yy19;
	}
yy19:
#line 198 "cunroll.re"
{ RET('+'); }
#line 269 "<stdout>"
yy20:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '-':	goto yy85;
	case '=':	goto yy87;
	case '>':	goto yy83;
	default:	goto yy21;
	}
yy21:
#line 197 "cunroll.re"
{ RET('-'); }
#line 280 "<stdout>"
yy22:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '=':	goto yy81;
	default:	goto yy23;
	}
yy23:
#line 199 "cunroll.re"
{ RET('*'); }
#line 289 "<stdout>"
yy24:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '=':	goto yy79;
	default:	goto yy25;
	}
yy25:
#line 201 "cunroll.re"
{ RET('%'); }
#line 298 "<stdout>"
yy26:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '&':	goto yy75;
	case '=':	goto yy77;
	default:	goto yy27;
	}
yy27:
#line 194 "cunroll.re"
{ RET('&'); }
#line 308 "<stdout>"
yy28:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '=':	goto yy73;
	default:	goto yy29;
	}
yy29:
#line 204 "cunroll.re"
{ RET('^'); }
#line 317 "<stdout>"
yy30:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '=':	goto yy71;
	case '|':	goto yy69;
	default:	goto yy31;
	}
yy31:
#line 205 "cunroll.re"
{ RET('|'); }
#line 327 "<stdout>"
yy32:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '=':	goto yy67;
	default:	goto yy33;
	}
yy33:
#line 188 "cunroll.re"
{ RET('='); }
#line 336 "<stdout>"
yy34:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '=':	goto yy65;
	default:	goto yy35;
	}
yy35:
#line 195 "cunroll.re"
{ RET('!'); }
#line 345 "<stdout>"
yy36:	++YYCURSOR;
	goto yy37;
yy37:
#line 183 "cunroll.re"
{ RET(';'); }
#line 351 "<stdout>"
yy38:	++YYCURSOR;
	goto yy39;
yy39:
#line 184 "cunroll.re"
{ RET('{'); }
#line 357 "<stdout>"
yy40:	++YYCURSOR;
	goto yy41;
yy41:
#line 185 "cunroll.re"
{ RET('}'); }
#line 363 "<stdout>"
yy42:	++YYCURSOR;
	goto yy43;
yy43:
#line 186 "cunroll.re"
{ RET(','); }
#line 369 "<stdout>"
yy44:	++YYCURSOR;
	goto yy45;
yy45:
#line 187 "cunroll.re"
{ RET(':'); }
#line 375 "<stdout>"
yy46:	++YYCURSOR;
	goto yy47;
yy47:
#line 189 "cunroll.re"
{ RET('('); }
#line 381 "<stdout>"
yy48:	++YYCURSOR;
	goto yy49;
yy49:
#line 190 "cunroll.re"
{ RET(')'); }
#line 387 "<stdout>"
yy50:	++YYCURSOR;
	goto yy51;
yy51:
#line 191 "cunroll.re"
{ RET('['); }
#line 393 "<stdout>"
yy52:	++YYCURSOR;
	goto yy53;
yy53:
#line 192 "cunroll.re"
{ RET(']'); }
#line 399 "<stdout>"
yy54:	++YYCURSOR;
	goto yy55;
yy55:
#line 196 "cunroll.re"
{ RET('~'); }
#line 405 "<stdout>"
yy56:	++YYCURSOR;
	goto yy57;
yy57:
#line 206 "cunroll.re"
{ RET('?'); }
#line 411 "<stdout>"
yy58:	++YYCURSOR;
	yych = *YYCURSOR;
	goto yy64;
yy59:
#line 209 "cunroll.re"
{ goto std; }
#line 417 "<stdout>"
yy60:	++YYCURSOR;
	goto yy61;
yy61:
#line 212 "cunroll.re"
{
		if(cursor == s->eof) RET(EOI);
		s->pos = cursor; s->line++;
		goto std;
	    }
#line 427 "<stdout>"
yy62:	yych = *++YYCURSOR;
	goto yy10;
yy63:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	goto yy64;
yy64:	switch(yych){
	case 0x09:	case 0x0B:
	case 0x0C:	case ' ':	goto yy63;
	default:	goto yy59;
	}
yy65:	++YYCURSOR;
	goto yy66;
yy66:
#line 182 "cunroll.re"
{ RET(NEQ); }
#line 445 "<stdout>"
yy67:	++YYCURSOR;
	goto yy68;
yy68:
#line 181 "cunroll.re"
{ RET(EQL); }
#line 451 "<stdout>"
yy69:	++YYCURSOR;
	goto yy70;
yy70:
#line 178 "cunroll.re"
{ RET(OROR); }
#line 457 "<stdout>"
yy71:	++YYCURSOR;
	goto yy72;
yy72:
#line 171 "cunroll.re"
{ RET(OREQ); }
#line 463 "<stdout>"
yy73:	++YYCURSOR;
	goto yy74;
yy74:
#line 170 "cunroll.re"
{ RET(XOREQ); }
#line 469 "<stdout>"
yy75:	++YYCURSOR;
	goto yy76;
yy76:
#line 177 "cunroll.re"
{ RET(ANDAND); }
#line 475 "<stdout>"
yy77:	++YYCURSOR;
	goto yy78;
yy78:
#line 169 "cunroll.re"
{ RET(ANDEQ); }
#line 481 "<stdout>"
yy79:	++YYCURSOR;
	goto yy80;
yy80:
#line 168 "cunroll.re"
{ RET(MODEQ); }
#line 487 "<stdout>"
yy81:	++YYCURSOR;
	goto yy82;
yy82:
#line 166 "cunroll.re"
{ RET(MULEQ); }
#line 493 "<stdout>"
yy83:	++YYCURSOR;
	goto yy84;
yy84:
#line 176 "cunroll.re"
{ RET(DEREF); }
#line 499 "<stdout>"
yy85:	++YYCURSOR;
	goto yy86;
yy86:
#line 175 "cunroll.re"
{ RET(DECR); }
#line 505 "<stdout>"
yy87:	++YYCURSOR;
	goto yy88;
yy88:
#line 165 "cunroll.re"
{ RET(SUBEQ); }
#line 511 "<stdout>"
yy89:	++YYCURSOR;
	goto yy90;
yy90:
#line 174 "cunroll.re"
{ RET(INCR); }
#line 517 "<stdout>"
yy91:	++YYCURSOR;
	goto yy92;
yy92:
#line 164 "cunroll.re"
{ RET(ADDEQ); }
#line 523 "<stdout>"
yy93:	++YYCURSOR;
	goto yy94;
yy94:
#line 179 "cunroll.re"
{ RET(LEQ); }
#line 529 "<stdout>"
yy95:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '=':	goto yy97;
	default:	goto yy96;
	}
yy96:
#line 173 "cunroll.re"
{ RET(LSHIFT); }
#line 538 "<stdout>"
yy97:	++YYCURSOR;
	goto yy98;
yy98:
#line 163 "cunroll.re"
{ RET(LSHIFTEQ); }
#line 544 "<stdout>"
yy99:	++YYCURSOR;
	goto yy100;
yy100:
#line 180 "cunroll.re"
{ RET(GEQ); }
#line 550 "<stdout>"
yy101:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '=':	goto yy103;
	default:	goto yy102;
	}
yy102:
#line 172 "cunroll.re"
{ RET(RSHIFT); }
#line 559 "<stdout>"
yy103:	++YYCURSOR;
	goto yy104;
yy104:
#line 162 "cunroll.re"
{ RET(RSHIFTEQ); }
#line 565 "<stdout>"
yy105:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	goto yy106;
yy106:	switch(yych){
	case 0x0A:	goto yy107;
	case '"':	goto yy109;
	case '\\':	goto yy108;
	default:	goto yy105;
	}
yy107:	YYCURSOR = YYMARKER;
	switch(yyaccept){
	case 0:	goto yy7;
	case 3:	goto yy119;
	case 2:	goto yy12;
	case 1:	goto yy10;
	}
yy108:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch(yych){
	case '"':	case '\'':	case '?':	case '\\':	case 'a':
	case 'b':	case 'f':	case 'n':	case 'r':	case 't':	case 'v':	goto yy105;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':	goto yy112;
	case 'x':	goto yy111;
	default:	goto yy107;
	}
yy109:	++YYCURSOR;
	goto yy110;
yy110:
#line 159 "cunroll.re"
{ RET(SCON); }
#line 607 "<stdout>"
yy111:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch(yych){
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':	goto yy114;
	default:	goto yy107;
	}
yy112:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	goto yy113;
yy113:	switch(yych){
	case 0x0A:	goto yy107;
	case '"':	goto yy109;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':	goto yy112;
	case '\\':	goto yy108;
	default:	goto yy105;
	}
yy114:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	goto yy115;
yy115:	switch(yych){
	case 0x0A:	goto yy107;
	case '"':	goto yy109;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':	goto yy114;
	case '\\':	goto yy108;
	default:	goto yy105;
	}
yy116:	yych = *++YYCURSOR;
	switch(yych){
	case '.':	goto yy125;
	default:	goto yy107;
	}
yy117:	yyaccept = 3;
	YYMARKER = ++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	goto yy118;
yy118:	switch(yych){
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy117;
	case 'E':	case 'e':	goto yy120;
	case 'F':	case 'L':	case 'f':	case 'l':	goto yy121;
	default:	goto yy119;
	}
yy119:
#line 156 "cunroll.re"
{ RET(FCON); }
#line 713 "<stdout>"
yy120:	yych = *++YYCURSOR;
	switch(yych){
	case '+':	case '-':	goto yy122;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy123;
	default:	goto yy107;
	}
yy121:	yych = *++YYCURSOR;
	goto yy119;
yy122:	yych = *++YYCURSOR;
	switch(yych){
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy123;
	default:	goto yy107;
	}
yy123:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	goto yy124;
yy124:	switch(yych){
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy123;
	case 'F':	case 'L':	case 'f':	case 'l':	goto yy121;
	default:	goto yy119;
	}
yy125:	++YYCURSOR;
	goto yy126;
yy126:
#line 161 "cunroll.re"
{ RET(ELLIPSIS); }
#line 769 "<stdout>"
yy127:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	goto yy128;
yy128:	switch(yych){
	case 0x0A:	goto yy107;
	case '\'':	goto yy130;
	case '\\':	goto yy129;
	default:	goto yy127;
	}
yy129:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch(yych){
	case '"':	case '\'':	case '?':	case '\\':	case 'a':
	case 'b':	case 'f':	case 'n':	case 'r':	case 't':	case 'v':	goto yy127;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':	goto yy132;
	case 'x':	goto yy131;
	default:	goto yy107;
	}
yy130:	yych = *++YYCURSOR;
	goto yy7;
yy131:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch(yych){
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':	goto yy134;
	default:	goto yy107;
	}
yy132:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	goto yy133;
yy133:	switch(yych){
	case 0x0A:	goto yy107;
	case '\'':	goto yy130;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':	goto yy132;
	case '\\':	goto yy129;
	default:	goto yy127;
	}
yy134:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	goto yy135;
yy135:	switch(yych){
	case 0x0A:	goto yy107;
	case '\'':	goto yy130;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':	goto yy134;
	case '\\':	goto yy129;
	default:	goto yy127;
	}
yy136:	yyaccept = 3;
	yych = *(YYMARKER = ++YYCURSOR);
	switch(yych){
	case 'E':	case 'e':	goto yy147;
	default:	goto yy146;
	}
yy137:	yyaccept = 0;
	YYMARKER = ++YYCURSOR;
	if((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	goto yy138;
yy138:	switch(yych){
	case '.':	goto yy136;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy137;
	case 'E':	case 'e':	goto yy139;
	case 'L':	case 'U':	case 'l':	case 'u':	goto yy140;
	default:	goto yy7;
	}
yy139:	yych = *++YYCURSOR;
	switch(yych){
	case '+':	case '-':	goto yy142;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy143;
	default:	goto yy107;
	}
yy140:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	goto yy141;
yy141:	switch(yych){
	case 'L':	case 'U':	case 'l':	case 'u':	goto yy140;
	default:	goto yy7;
	}
yy142:	yych = *++YYCURSOR;
	switch(yych){
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy143;
	default:	goto yy107;
	}
yy143:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	goto yy144;
yy144:	switch(yych){
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy143;
	case 'F':	case 'L':	case 'f':	case 'l':	goto yy121;
	default:	goto yy119;
	}
yy145:	yyaccept = 3;
	YYMARKER = ++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	goto yy146;
yy146:	switch(yych){
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy145;
	case 'E':	case 'e':	goto yy151;
	case 'F':	case 'L':	case 'f':	case 'l':	goto yy121;
	default:	goto yy119;
	}
yy147:	yych = *++YYCURSOR;
	switch(yych){
	case '+':	case '-':	goto yy148;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy149;
	default:	goto yy107;
	}
yy148:	yych = *++YYCURSOR;
	switch(yych){
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy149;
	default:	goto yy107;
	}
yy149:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	goto yy150;
yy150:	switch(yych){
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy149;
	case 'F':	case 'L':	case 'f':	case 'l':	goto yy121;
	default:	goto yy119;
	}
yy151:	yych = *++YYCURSOR;
	switch(yych){
	case '+':	case '-':	goto yy152;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy153;
	default:	goto yy107;
	}
yy152:	yych = *++YYCURSOR;
	switch(yych){
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy153;
	default:	goto yy107;
	}
yy153:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	goto yy154;
yy154:	switch(yych){
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy153;
	case 'F':	case 'L':	case 'f':	case 'l':	goto yy121;
	default:	goto yy119;
	}
yy155:	yyaccept = 0;
	YYMARKER = ++YYCURSOR;
	if((YYLIMIT - YYCURSOR) < 4) YYFILL(4);
	yych = *YYCURSOR;
	goto yy156;
yy156:	switch(yych){
	case '.':	goto yy136;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy155;
	case 'E':	case 'e':	goto yy139;
	case 'L':	case 'U':	case 'l':	case 'u':	goto yy162;
	default:	goto yy7;
	}
yy157:	yych = *++YYCURSOR;
	switch(yych){
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':	goto yy158;
	default:	goto yy107;
	}
yy158:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	goto yy159;
yy159:	switch(yych){
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':	goto yy158;
	case 'L':	case 'U':	case 'l':	case 'u':	goto yy160;
	default:	goto yy7;
	}
yy160:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	goto yy161;
yy161:	switch(yych){
	case 'L':	case 'U':	case 'l':	case 'u':	goto yy160;
	default:	goto yy7;
	}
yy162:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	goto yy163;
yy163:	switch(yych){
	case 'L':	case 'U':	case 'l':	case 'u':	goto yy162;
	default:	goto yy7;
	}
yy164:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	case 'A':
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
	case 'Z':	case '_':	case 'a':
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
	case 'z':	goto yy166;
	default:	goto yy165;
	}
yy165:
#line 142 "cunroll.re"
{ RET(ID); }
#line 1237 "<stdout>"
yy166:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	case 'A':
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
	case 'Z':	case '_':	case 'a':
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
	case 'z':	goto yy168;
	default:	goto yy167;
	}
yy167:
#line 143 "cunroll.re"
{ RET(ID); }
#line 1305 "<stdout>"
yy168:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	case 'A':
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
	case 'Z':	case '_':	case 'a':
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
	case 'z':	goto yy170;
	default:	goto yy169;
	}
yy169:
#line 144 "cunroll.re"
{ RET(ID); }
#line 1373 "<stdout>"
yy170:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	case 'A':
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
	case 'Z':	case '_':	case 'a':
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
	case 'z':	goto yy172;
	default:	goto yy171;
	}
yy171:
#line 145 "cunroll.re"
{ RET(ID); }
#line 1441 "<stdout>"
yy172:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	case 'A':
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
	case 'Z':	case '_':	case 'a':
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
	case 'z':	goto yy174;
	default:	goto yy173;
	}
yy173:
#line 146 "cunroll.re"
{ RET(ID); }
#line 1509 "<stdout>"
yy174:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	case 'A':
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
	case 'Z':	case '_':	case 'a':
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
	case 'z':	goto yy176;
	default:	goto yy175;
	}
yy175:
#line 147 "cunroll.re"
{ RET(ID); }
#line 1577 "<stdout>"
yy176:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	case 'A':
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
	case 'Z':	case '_':	case 'a':
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
	case 'z':	goto yy178;
	default:	goto yy177;
	}
yy177:
#line 148 "cunroll.re"
{ RET(ID); }
#line 1645 "<stdout>"
yy178:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	goto yy179;
yy179:	switch(yych){
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	case 'A':
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
	case 'Z':	case '_':	case 'a':
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
	case 'z':	goto yy178;
	default:	goto yy180;
	}
yy180:
#line 149 "cunroll.re"
{ RET(ID); }
#line 1717 "<stdout>"
yy181:	++YYCURSOR;
	goto yy182;
yy182:
#line 167 "cunroll.re"
{ RET(DIVEQ); }
#line 1723 "<stdout>"
yy183:	++YYCURSOR;
	goto yy184;
yy184:
#line 138 "cunroll.re"
{ goto comment; }
#line 1729 "<stdout>"
}
#line 223 "cunroll.re"


comment:

#line 1733 "<stdout>"
{
	YYCTYPE yych;
	unsigned int yyaccept;
	goto yy185;
yy186:	++YYCURSOR;
yy185:
	if((YYLIMIT - YYCURSOR) < 8) YYFILL(8);
	yych = *YYCURSOR;
	switch(yych){
	case 0x0A:	goto yy189;
	case '*':	goto yy187;
	case '/':	goto yy193;
	default:	goto yy191;
	}
yy187:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '/':	goto yy208;
	default:	goto yy188;
	}
yy188:
#line 242 "cunroll.re"
{ goto comment; }
#line 1756 "<stdout>"
yy189:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '*':	case '/':	goto yy190;
	default:	goto yy194;
	}
yy190:
#line 229 "cunroll.re"
{
		if(cursor == s->eof) RET(EOI);
		s->tok = s->pos = cursor; s->line++;
		goto comment;
	    }
#line 1769 "<stdout>"
yy191:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '*':	case '/':	goto yy192;
	default:	goto yy194;
	}
yy192:
#line 234 "cunroll.re"
{ goto comment; }
#line 1778 "<stdout>"
yy193:	yych = *++YYCURSOR;
	goto yy188;
yy194:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '*':	case '/':	goto yy195;
	default:	goto yy196;
	}
yy195:
#line 235 "cunroll.re"
{ goto comment; }
#line 1789 "<stdout>"
yy196:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '*':	case '/':	goto yy197;
	default:	goto yy198;
	}
yy197:
#line 236 "cunroll.re"
{ goto comment; }
#line 1798 "<stdout>"
yy198:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '*':	case '/':	goto yy199;
	default:	goto yy200;
	}
yy199:
#line 237 "cunroll.re"
{ goto comment; }
#line 1807 "<stdout>"
yy200:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '*':	case '/':	goto yy201;
	default:	goto yy202;
	}
yy201:
#line 238 "cunroll.re"
{ goto comment; }
#line 1816 "<stdout>"
yy202:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '*':	case '/':	goto yy203;
	default:	goto yy204;
	}
yy203:
#line 239 "cunroll.re"
{ goto comment; }
#line 1825 "<stdout>"
yy204:	++YYCURSOR;
	switch((yych = *YYCURSOR)) {
	case '*':	case '/':	goto yy205;
	default:	goto yy206;
	}
yy205:
#line 240 "cunroll.re"
{ goto comment; }
#line 1834 "<stdout>"
yy206:	++YYCURSOR;
	goto yy207;
yy207:
#line 241 "cunroll.re"
{ goto comment; }
#line 1840 "<stdout>"
yy208:	++YYCURSOR;
	goto yy209;
yy209:
#line 227 "cunroll.re"
{ goto std; }
#line 1846 "<stdout>"
}
#line 243 "cunroll.re"

}

main(){
    Scanner in;
    int t;
    memset((char*) &in, 0, sizeof(in));
    in.fd = 0;
    while((t = scan(&in)) != EOI){
/*
	printf("%d\t%.*s\n", t, in.cur - in.tok, in.tok);
	printf("%d\n", t);
*/
    }
    close(in.fd);
}
