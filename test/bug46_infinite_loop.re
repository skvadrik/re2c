// re2c $INPUT -o $OUTPUT 
#include <string.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    char* YYCURSOR = argv[1];
    char* YYLIMIT  = YYCURSOR + strlen(YYCURSOR);
    #define YYFILL(n) do { } while(0)

/*!re2c
re2c:define:YYCTYPE = "unsigned char";

""  { } /* dummy rule, must exist for the bug to occur; actual rule is not important */
*/

/* BUG BEGINS HERE */
/*!re2c
[^abc]* "a"? { printf("exit 0\n"); return 0; }
*/

    printf("exit 1\n");
    return 0;
}
