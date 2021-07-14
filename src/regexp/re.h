#ifndef _RE2C_RE_RE_
#define _RE2C_RE_RE_

#include <valarray>

#include "src/regexp/tag.h"
#include "src/util/c99_stdint.h"
#include "src/util/forbid_copy.h"
#include "src/util/range.h"
#include "src/util/slab_allocator.h"


namespace re2c {

struct AST;
struct ASTRule;
struct Msg;
struct Rule;
struct opt_t;

struct RE {
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

struct RESpec {
    RE::alc_t alc;
    RangeMgr &rangemgr;
    std::vector<RE*> res;
    std::vector<uint32_t> &charset;
    std::vector<Tag> &tags;
    std::valarray<Rule> &rules;
    const opt_t *opts;
    Msg &msg;

    RESpec(const std::vector<ASTRule> &ast, const opt_t *o, Msg &msg, RangeMgr &rm);
    FORBID_COPY(RESpec);
};

void split_charset(RESpec &spec);
void find_fixed_tags(RESpec &spec);
void insert_default_tags(RESpec &spec);
void warn_nullable(const RESpec &spec, const std::string &cond);

RE *re_nil(RESpec &spec);
RE *re_sym(RESpec &spec, const Range *r);
RE *re_alt(RESpec &spec, RE *x, RE *y);
RE *re_cat(RESpec &spec, RE *x, RE *y);
RE *re_iter(RESpec &spec, RE *x, uint32_t n, uint32_t m);
RE *re_tag(RESpec &spec, size_t idx, bool neg);

} // namespace re2c

#endif // _RE2C_RE_RE_
