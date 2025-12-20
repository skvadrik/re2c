#include <stdio.h>

#ifdef REVERSED_CONDITION_ORDER
#    define yyca 1
#    define yycb 0
#else
#    define yyca 0
#    define yycb 1
#endif

int main()
{
    const char * YYCURSOR = "aaaa,bbb!";
    int c = yyca;
    for (;;) {
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;
        re2c:define:YYSETCONDITION = "c = @@;";
        re2c:define:YYSETCONDITION:naked = 1;
        re2c:define:YYGETCONDITION = c;
        re2c:define:YYGETCONDITION:naked = 1;

        <*> * { printf ("error\n"); break; }

        <a> "a"      { printf ("a"); continue; }
        <a> "," => b { printf (","); continue; }

        <b> "!" { printf ("!\n"); break; }
        <b> "b" { printf ("b"); continue; }
    */
    }
    return 0;
}
