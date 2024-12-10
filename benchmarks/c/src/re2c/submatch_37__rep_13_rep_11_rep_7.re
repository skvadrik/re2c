#include "re2c/base.h"

namespace re2c_submatch_37__rep_13_rep_11_rep_7 {

/*!rules:re2c:main
    aaa = ([a]{13} #t1)* ([a]{11} #t2)* ([a]{7} #t3)*;

    *        { return -1; }
    aaa [\n] {
        const char *p = in->tok;
        p = print(count, in->tok, p, t1);
        p = print(count, in->tok, p, t2);
        p = print(count, in->tok, p, t3);
        OUTC('\n');
        taglistpool_clear(&in->tlp, in);
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

} // namespace re2c_submatch_37__rep_13_rep_11_rep_7
