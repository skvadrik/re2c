/* re2c lesson_002, strip_002.s, (c) M. Boerger 2006 */
/*!ignore:re2c

- complexity
  . When two comments are only separated by whitespace we want to drop both.
  . When a comemnt is preceeded by a new line and followed by whitespace and a 
    new line then we can drop the trailing whitespace and new line.
    But we cannot simply use the following two rules:
	  "*" "/" WS* "/" "*" { continue; }
	  "*" "/" WS* NL      { continue; }
	The main problem is that WS* can get bigger then our buffer, so we need a 
	new scanner.
  . Meanwhile our scanner gets a bit more complex and we have to add two more 
    things. First the scanner code now uses a YYMARKER to store backtracking 
    information. And second we have a new rule that utilizes trailing contexts.
    Therefore we also need to add YYCTXMARKER.
- formatting
  . Until now we only used single line expression code and we always had the 
    opening { on the same line as the rule itself. If we have multiline rule
    code and care for formatting we can nolonger rely on re2c. Now we have 
    to indent the rule code ourself. Also we need to take care of the opening
    {. If we keep it on the same line as the rule then re2c will indent it 
    correctly and the emitted #line informations will be correct. If we place
    it on the next line then the #line directivy will also point to that line
    and not to the rule.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*!max:re2c */
#define	BSIZE	128

#if BSIZE < YYMAXFILL
# error BSIZE must be greater YYMAXFILL
#endif

#define	YYCTYPE		char
#define	YYCURSOR	s.cur
#define	YYLIMIT		s.lim
#define YYMARKER	s.mrk
#define YYCTXMARKER s.ctx
#define	YYFILL(n)	{ if ((res = fill(&s, n)) >= 0) break; }

typedef struct Scanner
{
	FILE		*fp;
	char		*cur, *tok, *lim, *eof, *ctx, *mrk;
	char 		buffer[BSIZE];
} Scanner;

int fill(Scanner *s, int len)
{
	if (!len)
	{
		s->tok = s->cur = s->lim = s->mrk = s->buffer;
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
			s->mrk -= cnt;
			s->ctx -= cnt;
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

void echo(Scanner *s)
{
	fwrite(s->tok, 1, s->cur - s->tok, stdout);
}

int scan(FILE *fp)
{
	int  res = 0;
	int  nlcomment = 0;
    Scanner s;

	if (!fp)
	{
		return 1; /* no file was opened */
	}

    s.fp = fp;
	
	fill(&s, 0);

	for(;;)
	{
		s.tok = s.cur;
/*!re2c
	re2c:indent:top = 2;
	
	NL			= "\r"? "\n" ;
	WS			= [\r\n\t ] ;
	ANY			= [^] ;

	"/" "/"		{ goto cppcomment; }
	NL / "/""*"	{ echo(&s); nlcomment = 1; continue; }
	"/" "*"		{ goto comment; }
	ANY			{ fputc(*s.tok, stdout); continue; }
*/
comment:
		s.tok = s.cur;
/*!re2c
	"*" "/"		{ goto commentws; }
	ANY			{ goto comment; }
*/
commentws:
		s.tok = s.cur;
/*!re2c
	NL? "/" "*"	{ goto comment; }
	NL			{
				if (!nlcomment)
				{
					echo(&s);
				}
				nlcomment = 0;
				continue;
			}
	WS			{ goto commentws; }
	ANY			{ echo(&s); nlcomment = 0; continue; }
*/
cppcomment:
		s.tok = s.cur;
/*!re2c
	NL			{ echo(&s); continue; }
	ANY			{ goto cppcomment; }
*/
	}

	if (fp != stdin)
	{
		fclose(fp); /* close only if not stdin */
	}
	return res; /* return result */
}

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		return scan(!strcmp(argv[1], "-") ? stdin : fopen(argv[1], "r"));
	}
	else
	{
		fprintf(stderr, "%s <expr>\n", argv[0]);
		return 1;
	}
}
