#include "src/parse/ast.h"
#include "src/options/opt.h"
#include "src/regexp/regexp.h"
#include "src/regexp/rule.h"
#include "src/util/check.h"

namespace re2c {

Regexp* re_nil(RESpec& spec) {
    Regexp* x = spec.ir_alc.alloct<Regexp>(1);
    x->kind = Regexp::Kind::NIL;
    return x;
}

Regexp* re_sym(RESpec& spec, const Range* r) {
    Regexp* x = spec.ir_alc.alloct<Regexp>(1);
    x->kind = Regexp::Kind::SYM;
    x->sym = r;
    return x;
}

Regexp* re_alt(RESpec& spec, Regexp* x, Regexp* y) {
    if (!x) return y;
    if (!y) return x;
    if (x->kind == Regexp::Kind::SYM && y->kind == Regexp::Kind::SYM) {
        return re_sym(spec, spec.rangemgr.add(x->sym, y->sym));
    }

    Regexp* z = spec.ir_alc.alloct<Regexp>(1);
    z->kind = Regexp::Kind::ALT;
    z->alt.re1 = x;
    z->alt.re2 = y;
    return z;
}

Regexp* re_cat(RESpec& spec, Regexp* x, Regexp* y) {
    if (!x) return y;
    if (!y) return x;

    Regexp* z = spec.ir_alc.alloct<Regexp>(1);
    z->kind = Regexp::Kind::CAT;
    z->cat.re1 = x;
    z->cat.re2 = y;
    return z;
}

Regexp* re_iter(RESpec& spec, Regexp* x, uint32_t n, uint32_t m) {
    Regexp* y = spec.ir_alc.alloct<Regexp>(1);
    y->kind = Regexp::Kind::ITER;
    y->iter.re = x;
    y->iter.min = n;
    y->iter.max = m;
    return y;
}

Regexp* re_tag(RESpec& spec, size_t idx, bool neg) {
    Regexp* x = spec.ir_alc.alloct<Regexp>(1);
    x->kind = Regexp::Kind::TAG;
    x->tag.idx = idx & 0x7FFFffff;
    DCHECK(idx == x->tag.idx);
    x->tag.neg = neg;
    return x;
}

} // namespace re2c
