#include "re2c/base.h"

namespace re2c_submatch_38__rep_23_rep_19_rep_17 {

/*!rules:re2c:main
    aaa = ([a]{23} #t1)* ([a]{19} #t2)* ([a]{17} #t3)*;

    *        { return -1; }
    aaa [\n] {
        const char *p = YYTOKEN;
        p = print(count, YYTOKEN, p, t1);
        p = print(count, YYTOKEN, p, t2);
        p = print(count, YYTOKEN, p, t3);
        OUTC('\n');
        TLP_CLEAR();
        goto loop;
    }
*/

static const char *print(long& count, const char *tok, const char *start, const taglist_t *t) {
    if (!t) return start;

    const char *s = print(count, tok, start, t->pred);
    if (t->dist > 0) {
        const char *e = tok + t->dist;
        OUTS(s, e);
        OUTC('.');
        return e;
    } else {
        return s;
    }
}

/*!include:re2c "base.re" */

} // namespace re2c_submatch_38__rep_23_rep_19_rep_17
