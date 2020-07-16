// re2c $INPUT -o $OUTPUT -i
#include <assert.h>                 //
                                    // C/C++ code
int lex(const char *YYCURSOR)       //
{
    /*!re2c                         // start of re2c block
    re2c:define:YYCTYPE = char;     // configuration
    re2c:yyfill:enable = 0;         // configuration
    re2c:flags:case-ranges = 1;     // configuration
                                    //
    ident = [a-zA-Z_][a-zA-Z_0-9]*; // named definition
                                    //
    ident { return 0; }             // normal rule
    *     { return 1; }             // default rule
    */
}                                   //
                                    //
int main()                          //
{                                   // C/C++ code
    assert(lex("_Zer0") == 0);      //
    return 0;                       //
}                                   //
