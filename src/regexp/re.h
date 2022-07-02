#ifndef _RE2C_RE_RE_
#define _RE2C_RE_RE_

#include <stdint.h>
#include <vector>

#include "src/constants.h"
#include "src/regexp/tag.h"
#include "src/util/allocator.h"
#include "src/util/attribute.h"
#include "src/util/forbid_copy.h"
#include "src/util/range.h"

namespace re2c {

class Msg;
struct AstNode;
struct AstRule;
struct Rule;
struct opt_t;

struct RE {
    using alc_t = slab_allocator_t<4096, sizeof(void*)>;
    enum class Kind: uint32_t {NIL, SYM, ALT, CAT, ITER, TAG} kind;
    union {
        const Range* sym;
        struct {
            RE* re1;
            RE* re2;
        } alt;
        struct {
            RE* re1;
            RE* re2;
        } cat;
        struct {
            RE* re;
            uint32_t min;
            uint32_t max;
        } iter;
        tag_info_t tag;
    };
};

struct RESpec {
    RE::alc_t alc;
    RangeMgr& rangemgr;
    std::vector<RE*> res;
    std::vector<uint32_t> charset;
    std::vector<Tag> tags;
    std::vector<Rule> rules;
    const opt_t* opts;
    Msg& msg;

    RESpec(const opt_t* opts, Msg& msg, RangeMgr& rangemgr);
    Ret init(const std::vector<AstRule>& ast) NODISCARD;

    FORBID_COPY(RESpec);
};

void split_charset(RESpec& spec);
void find_fixed_tags(RESpec& spec);
void insert_default_tags(RESpec& spec);
void warn_nullable(const RESpec& spec, const std::string& cond);

RE* re_nil(RESpec& spec);
RE* re_sym(RESpec& spec, const Range* r);
RE* re_alt(RESpec& spec, RE* x, RE* y);
RE* re_cat(RESpec& spec, RE* x, RE* y);
RE* re_iter(RESpec& spec, RE* x, uint32_t n, uint32_t m);
RE* re_tag(RESpec& spec, size_t idx, bool neg);

} // namespace re2c

#endif // _RE2C_RE_RE_
