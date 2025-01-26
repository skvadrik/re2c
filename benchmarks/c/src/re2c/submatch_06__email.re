#include "re2c/base.h"

namespace re2c_submatch_06__email {

/*!rules:re2c:main
    char      = [a-z0-9!#$%&'*+/=?^_`{|}~-];
    before_at = char+ ([.] char+)*;
    az09      = [a-z0-9];
    az09dash  = [a-z0-9-]* [a-z0-9];
    after_at  = (az09 az09dash? [.])+ az09 az09dash?;
    email     = before_at [@] @p after_at [\n];
    skip      = [^\n\x00]* [\n];

    * { return -1; }
    email {
        OUTC(' ');
        OUTS(YYTOKEN, p - 1);
        OUTC(' ');
        OUTS(p, YYCURSOR - 1);
        OUTC('\n');
        goto loop;
    }
    skip { goto loop; }
*/

/*!include:re2c "base.re" */

} // namespace re2c_submatch_06_email
