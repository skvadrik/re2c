// re2c $INPUT -o $OUTPUT --case-ranges -i

int lex(const char *YYCURSOR) {       // C/C++ code
/*!re2c
    re2c:define:YYCTYPE = char;       // configurations
    re2c:yyfill:enable  = 0;          //
                                      //
    alpha = [a-zA-Z];                 // named definitions
    ident = alpha (alpha | [0-9])*;   //
                                      //
    ident { return 0; }               // rules
    *     { return 1; }               //
*/
}                                     //
                                      //
int main() {                          // C/C++ code
    return lex("qwerty42");           //
}                                     //
