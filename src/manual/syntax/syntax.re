/*!re2c re2c:flags:i = 1; */         // re2c block with configuration that turns off #line directives
                                     //
#include <stdio.h>                   //    C/C++ code
                                     //
/*!max:re2c*/                        // directive that defines YYMAXFILL (unused)
/*!re2c                              // start of re2c block
    digit  = [0-9];                  //   named definition of 'digit'
    number = digit+;                 //   named definition of 'number'
*/                                   // end of re2c block
                                     //
static int lex(const char *YYCURSOR) // YYCURSOR is defined as a function parameter
{                                    //
    const char *YYMARKER;            // YYMARKER is defined as a local variable
    /*!re2c                          // start of re2c block
    re2c:define:YYCTYPE = char;      //   configuration that defines YYCTYPE
    re2c:yyfill:enable  = 0;         //   configuration that turns off YYFILL
                                     //
    * { return 1; }                  //   default rule with its semantic action
                                     //
    number {                         //   a normal rule with its semantic action
        printf("number\n");          //     ... semantic action (continued)
        return 0;                    //     ... semantic action (continued)
    }                                //   end of semantic action
                                     //
    */                               // end of re2c block
}                                    //
                                     //
int main()                           //
{                                    //
    lex("1024");                     //    C/C++ code
    lex(";]");                       //
    return 0;                        //
}                                    //
