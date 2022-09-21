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

struct Regexp {
    enum class Kind: uint32_t {NIL, SYM, ALT, CAT, ITER, TAG} kind;
    union {
        const Range* sym;
        struct {
            Regexp* re1;
            Regexp* re2;
        } alt;
        struct {
            Regexp* re1;
            Regexp* re2;
        } cat;
        struct {
            Regexp* re;
            uint32_t min;
            uint32_t max;
        } iter;
        tag_info_t tag;
    };
};

struct RESpec {
    IrAllocator ir_alc;
    RangeMgr rangemgr;
    std::vector<Regexp*> res;
    std::vector<uint32_t> charset;
    std::vector<Tag> tags;
    std::vector<Rule> rules;
    const opt_t* opts;
    Msg& msg;

    RESpec(const opt_t* opts, Msg& msg);
    Ret init(const std::vector<AstRule>& ast) NODISCARD;

    FORBID_COPY(RESpec);
};

void split_charset(RESpec& spec);
void find_fixed_tags(RESpec& spec);
void insert_default_tags(RESpec& spec);
void warn_nullable(const RESpec& spec, const std::string& cond);

Regexp* re_nil(RESpec& spec);
Regexp* re_sym(RESpec& spec, const Range* r);
Regexp* re_alt(RESpec& spec, Regexp* x, Regexp* y);
Regexp* re_cat(RESpec& spec, Regexp* x, Regexp* y);
Regexp* re_iter(RESpec& spec, Regexp* x, uint32_t n, uint32_t m);
Regexp* re_tag(RESpec& spec, size_t idx, bool neg);

} // namespace re2c

#endif // _RE2C_RE_RE_
