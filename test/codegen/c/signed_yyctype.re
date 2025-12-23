// re2c $INPUT -o $OUTPUT -i
#include <assert.h>

/*!rules:re2c
    re2c:yyfill:enable = 0;

    [\xff] { return 0; }
    *      { return 1; }
*/

int lex_signed(const char* YYCURSOR) {
    /*!use:re2c
        re2c:define:YYCTYPE = "char"; // should be unsigned!
    */
}

int lex_unsigned(const char* YYCURSOR) {
    /*!use:re2c
        re2c:define:YYCTYPE = "unsigned char";
    */
}

int main() {
    assert(lex_signed("\xff") == 1); // error! lexer works incorrectly - '\xff' does not match
    assert(lex_unsigned("\xff") == 0);
    return 0;
}
