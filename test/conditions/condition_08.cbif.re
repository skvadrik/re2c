#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	BSIZE	8192

/*!types:re2c */

typedef struct Scanner
{
	FILE			    *fp;
	unsigned char	    *cur, *tok, *lim, *eof;
	unsigned char 	    buffer[BSIZE];
	unsigned char       yych;
	enum ScanContition  cond;
	int                 state;
} Scanner;

int fill(Scanner *s, int len)
{
	if (!len)
	{
		s->cur = s->tok = s->lim = s->buffer;
		s->eof = 0;
	}
	if (!s->eof)
	{
		int got, cnt = s->tok - s->buffer;

		if (cnt > 0)
		{
			memcpy(s->buffer, s->tok, s->lim - s->tok);
			s->tok -= cnt;
			s->cur -= cnt;
			s->lim -= cnt;
		}
		cnt = BSIZE - cnt;
		if ((got = fread(s->lim, 1, cnt, s->fp)) != cnt)
		{
			s->eof = &s->lim[got];
		}
		s->lim += got;
	}
	else if (s->cur + len > s->eof)
	{
		return 0; /* not enough input data */
	}
	return -1;
}

void fputl(const char *s, size_t len, FILE *stream)
{
	while(len-- > 0)
	{
		fputc(*s++, stream);
	}
}

void scan(Scanner *s)
{
	fill(s, 0);

	for(;;)
	{
		s->tok = s->cur;
/*!re2c

re2c:define:YYCTYPE          = "unsigned char";
re2c:define:YYCURSOR         = s->cur;
re2c:define:YYLIMIT          = s->lim;
re2c:define:YYMARKER         = s->tok;
re2c:define:YYFILL@len       = #;
re2c:define:YYFILL:naked     = 1;
re2c:define:YYFILL           = "if(fill(s, #) >= 0) break;";
re2c:define:YYSETSTATE@state = #;
re2c:define:YYSETSTATE       = "s->state = #;";
re2c:define:YYGETSTATE       = "s->state";
re2c:define:YYGETSTATE:naked = 1;
re2c:define:YYGETCONDITION       = s->cond;
re2c:define:YYGETCONDITION:naked = 1;
re2c:define:YYCONDTYPE       = ScanContition;
re2c:variable:yych           = s->yych;
re2c:yych:emit               = 0;
re2c:indent:top              = 2;
re2c:condenumprefix          = EState;

<Normal>	"??("
			{
				fputc('[', stdout);
				continue;
			}
<Normal>	"??)"
			{
				fputc(']', stdout);
				continue;
			}
<Normal>	"??<"
			{
				fputc('{', stdout);
				continue;
			}
<Normal>	"??>"
			{
				fputc('}', stdout);
				continue;
			}
<Normal>	"??="
			{
				fputc('#', stdout);
				continue;
			}
<Normal>	"??/"
			{
				fputc('\\', stdout);
				continue;
			}
<Normal>	"??'"
			{
				fputc('^', stdout);
				continue;
			}
<Normal>	"??!"
			{
				fputc('|', stdout);
				continue;
			}
<Normal>	"??-"
			{
				fputc('~', stdout);
				continue;
			}
<Normal>	"/*"
			{
				s->cond = EStateComment;
				goto yyc_Comment;
			}
<Normal>	"//"
			{
				s->cond = EStateSkiptoeol;
				goto yyc_Skiptoeol;
			}
<Normal>	"'\\\"'"|"'\"'"
			{
				fputl("'\"'", 3, stdout);
				continue;
			}
<Normal>	'"'
			{
				fputc(*s->tok, stdout);
				s->state = EStateString;
				continue;
			}
<Normal>	[^]
			{
				fputc(*s->tok, stdout);
				continue;
			}
<Comment>	"*" "/"
			{
				s->cond = EStateNormal;
				continue;
			}
<Comment>	[^]
			{
				goto yyc_Comment;
			}
<Skiptoeol>	"??/" "\r"? "\n"
			{
				goto yyc_Skiptoeol;
			}
<Skiptoeol>	"\\" "\r"? "\n"
			{
				goto yyc_Skiptoeol;
			}
<Skiptoeol>	"\n"
			{
				s->cond = EStateNormal;
				continue;
			}
<Skiptoeol> [^]
			{
				goto yyc_Skiptoeol;
			}
<String>	'\\' .
			{
				fputl((const char*)s->tok, 2, stdout);
				continue;
			}
<String>	'"'
			{
				fputc(*s->tok, stdout);
				s->cond = EStateNormal;
				continue;
			}
<String>	[^]
			{
				fputc(*s->tok, stdout);
				continue;
			}
*/
	}
}

int main(int argc, char **argv)
{
	Scanner in;
	char c;

	if (argc != 2)
	{
		fprintf(stderr, "%s <file>\n", argv[0]);
		return 1;;
	}

	memset((char*) &in, 0, sizeof(in));

	if (!strcmp(argv[1], "-"))
	{
		in.fp = stdin;
	}
	else if ((in.fp = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "Cannot open file '%s'\n", argv[1]);
		return 1;
	}

 	in.cond = EStateNormal;
 	scan(&in);

	if (in.fp != stdin)
	{
		fclose(in.fp);
	}
	return 0;
}
