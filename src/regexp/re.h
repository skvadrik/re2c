#ifndef _RE2C_RE_RE_
#define _RE2C_RE_RE_

#include "src/parse/ast.h"
#include "src/options/opt.h"
#include "src/debug/debug.h"
#include "src/regexp/rule.h"
#include "src/util/c99_stdint.h"
#include "src/util/forbid_copy.h"
#include "src/util/range.h"
#include "src/util/slab_allocator.h"


namespace re2c {

struct RE
{
    typedef slab_allocator_t<4096, sizeof(void*)> alc_t;
    enum type_t {NIL, SYM, ALT, CAT, ITER, TAG} type;
    union {
        const Range *sym;
        struct {
            RE *re1;
            RE *re2;
        } alt;
        struct {
            RE *re1;
            RE *re2;
        } cat;
        struct {
            RE *re;
            uint32_t min;
            uint32_t max;
        } iter;
        tag_info_t tag;
    };
};

struct RESpec
{
    RE::alc_t alc;
    RangeMgr &rangemgr;
    std::vector<RE*> res;
    std::vector<uint32_t> &charset;
    std::vector<Tag> &tags;
    std::valarray<Rule> &rules;
    const opt_t *opts;
    Msg &msg;

    RESpec(const std::vector<ASTRule> &ast, const opt_t *o, Msg &msg
        , RangeMgr &rm);
    FORBID_COPY(RESpec);
};

void split_charset(RESpec &spec);
void find_fixed_tags(RESpec &spec);
void insert_default_tags(RESpec &spec);
void warn_nullable(const RESpec &spec, const std::string &cond);

inline RE *re_nil(RESpec &spec)
{
    RE *x = spec.alc.alloct<RE>(1);
    x->type = RE::NIL;
    return x;
}

inline RE *re_sym(RESpec &spec, const Range *r)
{
    RE *x = spec.alc.alloct<RE>(1);
    x->type = RE::SYM;
    x->sym = r;
    return x;
}

inline RE *re_alt(RESpec &spec, RE *x, RE *y)
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

inline RE *re_cat(RESpec &spec, RE *x, RE *y)
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

inline RE *re_iter(RESpec &spec, RE *x, uint32_t n, uint32_t m)
{
    RE *y = spec.alc.alloct<RE>(1);
    y->type = RE::ITER;
    y->iter.re = x;
    y->iter.min = n;
    y->iter.max = m;
    return y;
}

inline RE *re_tag(RESpec &spec, size_t idx, bool neg)
{
    RE *x = spec.alc.alloct<RE>(1);
    x->type = RE::TAG;
    x->tag.idx = idx & 0x7FFFffff;
    DASSERT(idx == x->tag.idx);
    x->tag.neg = neg;
    return x;
}

} // namespace re2c

#endif // _RE2C_RE_RE_
