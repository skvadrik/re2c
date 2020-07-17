// re2c $INPUT -o $OUTPUT -ci
#include <assert.h>
#include <string.h>


/*!types:re2c */

int lex(const char* cur)
{
    const char* lim;
    const char* mrk;

    char yych;

    int condition = yycinit;

    lim = cur + strlen(cur);
loop:
    mrk = cur;

    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:define:YYLIMIT  = lim;
        re2c:define:YYCURSOR = cur;
        re2c:define:YYMARKER = mrk;
        re2c:variable:yych  = yych;
        re2c:yych:emit = 0;
        re2c:define:YYGETCONDITION = 'condition';
        re2c:define:YYGETCONDITION:naked = 1;
        re2c:define:YYSETCONDITION = 'condition = @@;';
        re2c:define:YYSETCONDITION:naked = 1;
        re2c:yyfill:enable = 0;
        re2c:eof = 0;

        <init> *                                        { return -1; }
        <init> $                                        { return  0; }

        <init> [/][/] .*                                { goto loop; }
        <init> [/][*]                   :=> comment

        <init> [ \t]+                                   { goto loop; }

        <init, comment> [\n]+                           { goto loop; }

        <comment> [^*\n]+ [*]*          :=> comment
        <comment> [^*\n]* [*]+          :=> comment
        <comment> [^*\n]* [*]+ [/]       => init        { goto loop; }

        <comment> *                     :=> comment
        <comment> $                                     { return -1; }
    */
}


int main(void)
{
    assert(!lex("/* hello, */ // world !"));

    return 0;
}
