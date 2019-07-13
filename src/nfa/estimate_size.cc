#include <stddef.h>
#include <vector>

#include "src/debug/debug.h"
#include "src/nfa/nfa.h"
#include "src/parse/ast.h"
#include "src/regexp/re.h"


namespace re2c {

static size_t estimate(const RE *re)
{
    switch (re->type) {
        case RE::NIL: return 0;
        case RE::SYM: return 1;
        case RE::TAG: return 1;
        case RE::ALT:
            return estimate(re->alt.re1)
                + estimate(re->alt.re2)
                + 1;
        case RE::CAT:
            return estimate(re->cat.re1)
                + estimate(re->cat.re2);
        case RE::ITER: {
            const size_t
                iter = estimate(re->iter.re),
                min = re->iter.min,
                max = re->iter.max;
            return max == AST::MANY
                ? iter * min + 1
                : iter * max + (max - min);
        }
    }
    return 0; /* unreachable */
}

size_t estimate_size(const std::vector<RE*> &res)
{
    const size_t nre = res.size();
    DASSERT(nre > 0);
    size_t size = nre - 1;
    for (size_t i = 0; i < nre; ++i) {
        size += estimate(res[i]) + 1;
    }
    return size;
}

} // namespace re2c
