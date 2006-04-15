/* re2c lesson_001, calc_006, (c) M. Boerger 2006 */
/*!ignore:re2c

- avoiding YYFILL()
  . We use the inplace configuration re2c:yyfill to suppress generation of
    YYFILL() blocks. This of course means we no longer have to provide the
    macro.
  . We also drop the YYMARKER stuff since we know that re2c does not generate 
    it for this example.
  . Since re2c does no longer check for out of data situations we must do this.
    For that reason we first reintroduce our zero rule and second we need to
    ensure that the scanner does not take more than one bytes in one go.
    
    In the example suppose "0" is passed. The scanner reads the first "0" and
    then is in an undecided state. The scanner can earliest decide on the next 
    char what  the token is. In case of a zero the input ends and it was a 
    number, 0 to be precise. In case of a didit it is and the next character
    needs to be read. In case of any other character the scanner has found an 
    error with the any rule [^]. 
    
    Now the above shows that re2c may read two characters directly. But only if 
    the first is a "0". So we could easily check that if the first char is "0"
    another charcter is present.
    
    if (p[0] == '0' && p[1] == '\0') return 2;
    
    But instead of doing so in every loop we can optimize by taking into 
    account what we know from our input analysis. That is a problem can only
    arise when the second last character is a "0" and the last is any digit.
    
    if (l > 1 && s[l-2] == '0' && s[l-1] >= '0' && s[l-1] <= '9') return 2;
    
    However in this example the above check is only necessary if the input is 
    not terminated by a trailing zero check. In other words it would be used 
    when reading from a file and directly working on the read buffers. For 
    zero terminated string input the generated scanner will always find the 
    terminating zero.

- optimizing the generated code by using -s command line switch of re2c
  . This tells re2c to generate code that uses if statements rather 
    then endless switch/case expressions where appropriate. 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEBUG(stmt) stmt

int  stack[4];
int  depth = 0;

int push_num(const char *t, const char *l, int radix)
{
	int num = 0;
	
	if (depth >= sizeof(stack))
	{
		return 3;
	}

	--t;
	while(++t < l)
	{
		num = num * radix + (*t - '0');
	}
	DEBUG(printf("Num: %d\n", num));

	stack[depth++] = num;
	return 0;
}

int stack_add()
{
	if (depth < 2) return 4;
	
	--depth;
	stack[depth-1] = stack[depth-1] + stack[depth];
	return 0;
}

int stack_sub()
{
	if (depth < 2) return 4;

	--depth;
	stack[depth-1] = stack[depth-1] - stack[depth];
	return 0;
}

int scan(char *s, int l)
{
	char *p = s;
	char *t;
	int res = 0;
	
	#define YYCTYPE         char
	#define YYCURSOR        p
	
    if (l > 1 && s[l-2] == '0' && s[l-1] >= '0' && s[l-1] <= '9') return 2;

	while(!res)
	{
		t = p;
/*!re2c
	re2c:indent:top    = 2;
	re2c:yyfill:enable = 0;

	DIGIT	= [0-9] ;
	OCT		= "0" DIGIT+ ;
	INT		= "0" | ( [1-9] DIGIT* ) ;
	WS		= [ \t]+ ;

	WS		{ continue; }
	OCT		{ res = push_num(t, p, 8);	continue; }
	INT		{ res = push_num(t, p, 10); continue; }
	"+"		{ res = stack_add();		continue; }
	"-"		{ res = stack_sub();		continue; }
	"\000"  { res = depth == 1 ? 0 : 2;	continue; }
	[^]		{ res = 1; 					continue; }
*/
	}
	return res;
}

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		char *inp;
		int res = 0, argp = 0, len;
		
		while(!res && ++argp < argc)
		{
			inp = argv[argp];
			len = strlen(inp);
			if (inp[0] == '\"' && inp[len-1] == '\"')
			{
				++inp;
				len -=2;
			}
			res = scan(inp, len);
		}
		switch(res)
		{
		case 0:
			printf("Result: %d\n", stack[0]);
			return 0;
		case 1:
			fprintf(stderr, "Illegal character in input.\n");
			return 1;
		case 2:
			fprintf(stderr, "Premature end of input.\n");
			return 2;
		case 3:
			fprintf(stderr, "Stack overflow.\n");
			return 3;
		case 4:
			fprintf(stderr, "Stack underflow.\n");
			return 4;
		}
	}
	else
	{
		fprintf(stderr, "%s <expr>\n", argv[0]);
		return 0;
	}
}
