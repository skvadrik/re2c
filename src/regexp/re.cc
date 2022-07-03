#include "src/parse/ast.h"
#include "src/options/opt.h"
#include "src/regexp/re.h"
#include "src/regexp/rule.h"
#include "src/util/check.h"

namespace re2c {

RE* re_nil(RESpec& spec) {
    RE* x = spec.alc.alloct<RE>(1);
    x->kind = RE::Kind::NIL;
    return x;
}

RE* re_sym(RESpec& spec, const Range* r) {
    RE* x = spec.alc.alloct<RE>(1);
    x->kind = RE::Kind::SYM;
    x->sym = r;
    return x;
}

RE* re_alt(RESpec& spec, RE* x, RE* y) {
    if (!x) return y;
    if (!y) return x;
    if (x->kind == RE::Kind::SYM && y->kind == RE::Kind::SYM) {
        return re_sym(spec, spec.rangemgr.add(x->sym, y->sym));
    }

    RE* z = spec.alc.alloct<RE>(1);
    z->kind = RE::Kind::ALT;
    z->alt.re1 = x;
    z->alt.re2 = y;
    return z;
}

RE* re_cat(RESpec& spec, RE* x, RE* y) {
    if (!x) return y;
    if (!y) return x;

    if (spec.opts->backward) std::swap(x, y);

    RE* z = spec.alc.alloct<RE>(1);
    z->kind = RE::Kind::CAT;
    z->cat.re1 = x;
    z->cat.re2 = y;
    return z;
}

RE* re_iter(RESpec& spec, RE* x, uint32_t n, uint32_t m) {
    RE* y = spec.alc.alloct<RE>(1);
    y->kind = RE::Kind::ITER;
    y->iter.re = x;
    y->iter.min = n;
    y->iter.max = m;
    return y;
}

RE* re_tag(RESpec& spec, size_t idx, bool neg) {
    RE* x = spec.alc.alloct<RE>(1);
    x->kind = RE::Kind::TAG;
    x->tag.idx = idx & 0x7FFFffff;
    DCHECK(idx == x->tag.idx);
    x->tag.neg = neg;
    return x;
}

} // namespace re2c
