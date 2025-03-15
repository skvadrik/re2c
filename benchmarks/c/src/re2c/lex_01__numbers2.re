#include "re2c/base.h"

namespace re2c_lex_01__numbers2 {

/*!rules:re2c:main
    bin = [0][bB][01]+;
    oct = [0][0-7]*;
    dec = [1-9][0-9]*;
    hex = [0][xX][0-9a-fA-F]+;
    float = ([0-9]*[.][0-9]+ | [1-9][0-9]*) ([eE][+-]?[1-9][0-9]*)?;
    eol = [\n];

    // Multiply match length by base to make the actions artificially different.
    bin   eol { OUTX(YYTOKEN, YYCURSOR, 2);  goto loop; }
    oct   eol { OUTX(YYTOKEN, YYCURSOR, 8);  goto loop; }
    dec   eol { OUTX(YYTOKEN, YYCURSOR, 10); goto loop; }
    hex   eol { OUTX(YYTOKEN, YYCURSOR, 16); goto loop; }
    float eol { OUTX(YYTOKEN, YYCURSOR, 1);  goto loop; }
    *         { return -1; }
*/

/*!include:re2c "base.re" */

} // namespace re2c_lex_01__numbers2

