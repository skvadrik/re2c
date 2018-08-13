#include "src/util/c99_stdint.h"
#include <set>
#include <stack>
#include <vector>

#include "src/conf/opt.h"
#include "src/re/encoding/enc.h"
#include "src/re/re.h"
#include "src/util/range.h"

namespace re2c {

/* The original set of code units (charset) might be very large.
 * A common trick it is to split charset into disjoint character ranges
 * and choose a representative of each range (we choose lower bound).
 * The set of all representatives is the new (compacted) charset.
 * Don't forget to include zero and upper bound, even if they
 * do not explicitely apper in ranges.
 */
void split_charset(RESpec &spec)
{
    std::set<uint32_t> cs;
    std::stack<const RE*> todo;

    std::vector<RE*>::const_iterator
        i = spec.res.begin(),
        e = spec.res.end();
    for (; i != e; ++i) todo.push(*i);
    while (!todo.empty()) {
        const RE *re = todo.top();
        todo.pop();
        switch (re->type) {
            case RE::NIL: break;
            case RE::TAG: break;
            case RE::SYM:
                for (const Range *r = re->sym; r; r = r->next()) {
                    cs.insert(r->lower());
                    cs.insert(r->upper());
                }
                break;
            case RE::ALT:
                todo.push(re->alt.re2);
                todo.push(re->alt.re1);
                break;
            case RE::CAT:
                todo.push(re->cat.re2);
                todo.push(re->cat.re1);
                break;
            case RE::ITER:
                todo.push(re->iter.re);
                break;
        }
    }
    cs.insert(0);
    cs.insert(spec.opts->encoding.nCodeUnits());

    spec.charset.insert(spec.charset.end(), cs.begin(), cs.end());
}

} // namespace re2c
