#include "src/parse/ast.h"
#include "src/options/opt.h"
#include "src/debug/debug.h"
#include "src/regexp/re.h"
#include "src/regexp/rule.h"


namespace re2c {

RE *re_nil(RESpec &spec)
{
    RE *x = spec.alc.alloct<RE>(1);
    x->type = RE::NIL;
    return x;
}

RE *re_sym(RESpec &spec, const Range *r)
{
    RE *x = spec.alc.alloct<RE>(1);
    x->type = RE::SYM;
    x->sym = r;
    return x;
}

RE *re_alt(RESpec &spec, RE *x, RE *y)
{
    if (!x) return y;
    if (!y) return x;
    if (x->type == RE::SYM && y->type == RE::SYM) {
        return re_sym(spec, spec.rangemgr.add(x->sym, y->sym));
    }

    RE *z = spec.alc.alloct<RE>(1);
    z->type = RE::ALT;
    z->alt.re1 = x;
    z->alt.re2 = y;
    return z;
}

RE *re_cat(RESpec &spec, RE *x, RE *y)
{
    if (!x) return y;
    if (!y) return x;

    if (spec.opts->backward) std::swap(x, y);

    RE *z = spec.alc.alloct<RE>(1);
    z->type = RE::CAT;
    z->cat.re1 = x;
    z->cat.re2 = y;
    return z;
}

RE *re_iter(RESpec &spec, RE *x, uint32_t n, uint32_t m)
{
    RE *y = spec.alc.alloct<RE>(1);
    y->type = RE::ITER;
    y->iter.re = x;
    y->iter.min = n;
    y->iter.max = m;
    return y;
}

RE *re_tag(RESpec &spec, size_t idx, bool neg)
{
    RE *x = spec.alc.alloct<RE>(1);
    x->type = RE::TAG;
    x->tag.idx = idx & 0x7FFFffff;
    DASSERT(idx == x->tag.idx);
    x->tag.neg = neg;
    return x;
}

} // namespace re2c
