#include "re2c/base.h"

namespace re2c_submatch_35__rep_alt_23_19_17 {

/*!rules:re2c:main
    aaa = (([a]{23} | [a]{19} | [a]{17}) #t)*;

    *        { return -1; }
    aaa [\n] {
        print(count, YYTOKEN, t);
        OUTC('\n');
        TLP_CLEAR();
        goto loop;
    }
*/

static const char *print(long& count, const char *tok, const taglist_t *t) {
    if (!t) return tok;

    const char *s = print(count, tok, t->pred);
    const char *e = tok + t->dist;
    OUTS(s, e);
    OUTC('.');
    return e;
}

/*!include:re2c "base.re" */

} // namespace re2c_submatch_35__rep_alt_23_19_17
