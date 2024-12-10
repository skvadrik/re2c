#include "re2c/base.h"

namespace re2c_submatch_31__rep_cat_13_11_7 {

/*!rules:re2c:main
    aaa = ([a]{13} #t1 [a]{11} #t2 [a]{7} #t3)*;

    *        { return -1; }
    aaa [\n] {
        print(count, in->tok, t1, t2, t3);
        OUTC('\n');
        taglistpool_clear(&in->tlp, in);
        goto loop;
    }
*/

static const char *print(long& count,
        const char *tok, const taglist_t *t1, const taglist_t *t2, const taglist_t *t3) {
    if (!t1) return tok;

    const char *p0 = print(count, tok, t1->pred, t2->pred, t3->pred);
    const char *p1 = tok + t1->dist;
    const char *p2 = tok + t2->dist;
    const char *p3 = tok + t3->dist;

    OUTS(p0, p1);
    OUTC('.');
    OUTS(p1, p2);
    OUTC('.');
    OUTS(p2, p3);
    OUTC(';');

    return p3;
}

/*!include:re2c "base.re" */

} // namespace re2c_submatch_31__rep_cat_13_11_7
