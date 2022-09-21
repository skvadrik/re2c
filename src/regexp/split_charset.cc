#include <stdint.h>
#include <set>
#include <stack>
#include <vector>

#include "src/options/opt.h"
#include "src/encoding/enc.h"
#include "src/regexp/regexp.h"
#include "src/util/range.h"

namespace re2c {

// The original set of code units (charset) might be very large. A common trick it is to split
// charset into disjoint character ranges and choose a representative of each range (we choose the
// lower bound). The set of all representatives is the new (compacted) charset. Don't forget to
// include zero and upper bound, even if they do not explicitely apper in ranges.
//
void split_charset(RESpec& spec) {
    std::set<uint32_t> cs;
    std::stack<const Regexp*> todo;

    for (const Regexp* re : spec.res) {
        todo.push(re);
    }

    while (!todo.empty()) {
        const Regexp* re = todo.top();
        todo.pop();
        switch (re->kind) {
        case Regexp::Kind::NIL: break;
        case Regexp::Kind::TAG: break;
        case Regexp::Kind::SYM:
            for (const Range* r = re->sym; r; r = r->next()) {
                cs.insert(r->lower());
                cs.insert(r->upper());
            }
            break;
        case Regexp::Kind::ALT:
            todo.push(re->alt.re2);
            todo.push(re->alt.re1);
            break;
        case Regexp::Kind::CAT:
            todo.push(re->cat.re2);
            todo.push(re->cat.re1);
            break;
        case Regexp::Kind::ITER:
            todo.push(re->iter.re);
            break;
        }
    }

    const opt_t* opts = spec.opts;
    cs.insert(0);
    cs.insert(opts->encoding.cunit_count());
    if (opts->fill_eof != NOEOF) {
        cs.insert(opts->fill_eof);
        cs.insert(opts->fill_eof + 1);
    }

    spec.charset.insert(spec.charset.end(), cs.begin(), cs.end());
}

} // namespace re2c
