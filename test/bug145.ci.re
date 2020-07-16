// re2c $INPUT -o $OUTPUT -ci
#include <stdio.h>

/*!types:re2c*/

int test(const char* str)
{
    const unsigned char* YYCURSOR = (const unsigned char*)str;
    const unsigned char* YYMARKER;
    const unsigned char *YYCTXMARKER;
    int c = yycinit;

    /*!re2c
        re2c:define:YYCTYPE = "unsigned char";
        re2c:yyfill:enable = 0;
        re2c:define:YYGETCONDITION = "c";
        re2c:define:YYGETCONDITION:naked = 1;
        re2c:define:YYSETCONDITION = "c = @@;";
        re2c:define:YYSETCONDITION:naked = 1;

        //<*>* { return 0; }
        <init>* { return 0; }
        <init>"A" :=> C2
        <C2>* { return 0; }
        <C2>"B" { return 1; }
    */
}

int main()
{
    printf("%d\n", test("AB"));
    return 0;
}
