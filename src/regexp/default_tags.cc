#include <stddef.h>
#include <algorithm>
#include <memory>
#include <vector>

#include "src/debug/debug.h"
#include "src/options/opt.h"
#include "src/regexp/re.h"
#include "src/regexp/tag.h"


namespace re2c {

static RE *negative_tags(RESpec &spec, const size_t *stidx, const size_t *etidx)
{
    RE *x = NULL;

    // DFA case: add transitions for all negative tags (including nested ones).
    // This allows to avoid tag initialization and fixup.
    if (spec.opts->dfa) {
        for (; stidx < etidx; ++stidx) {
            x = re_cat(spec, x, re_tag(spec, *stidx, true));
        }
    }

    // NFA case: add transition only for one top-level negative tag, and save
    // the full range of negative tags in this tag's metadata (it will be used
    // during NFA simulation). Adding all tags increases NFA size and causes
    // significant slowdonw on tests with a lot of tags.
    else if (stidx < etidx) {
        // POSIX syntax means that tags are defined by capturing parentheses
        // NFA with raw tags is possible, but we do not have any use cases yet
        DASSERT(spec.opts->posix_syntax);
        // With POSIX syntax we must have at least two tags: opening and closing
        DASSERT(etidx - stidx > 1);

        size_t first = *stidx, stag, etag;
        if (!spec.opts->backward) {
            DASSERT(first % 2 == 0); // forward matching, 1st tag is opening
            stag = first;
        }
        else {
            DASSERT(first % 2 == 1); // backward matching, 1st tag is closing
            stag = first - 1;
        }
        etag = stag + 1;

        // the range of nested tags is contiguous, find its upper bound
        size_t last = first;
        for (const size_t *i = stidx; ++i < etidx;) {
            last = std::max(last, *i);
        }

        x = re_cat(spec, x, re_tag(spec, etag, true));
        spec.tags[etag].lnest = stag;
        spec.tags[etag].hnest = last + 1;
    }

    return x;
}

// Fictive tags do not really need default counterparts:
// maximization can work without them based on version numbers.
// For now it does not seem like a useful optimization, but some day
// in future it might change.
static void insert_default_tags(RESpec &spec, RE *re, size_t *&tidx)
{
    switch (re->type) {
        case RE::NIL: break;
        case RE::SYM: break;
        case RE::ALT: {
            size_t *i;

            i = tidx;
            insert_default_tags(spec, re->alt.re1, tidx);
            RE *x = negative_tags(spec, i, tidx);

            i = tidx;
            insert_default_tags(spec, re->alt.re2, tidx);
            RE *y = negative_tags(spec, i, tidx);

            // Decision to place negative tags before/after could be based
            // on POSIX semantics, not syntax. But strangely on some tests
            // placing before results in better performance. More benchmarks
            // are needed to understand this (with AOT/JIT, TNFA/TDFA).
            re->alt.re1 = re_cat(spec, re->alt.re1, y);
            re->alt.re2 = spec.opts->posix_syntax
                ? re_cat(spec, x, re->alt.re2)
                : re_cat(spec, re->alt.re2, x);

            break;
        }
        case RE::CAT:
            insert_default_tags(spec, re->cat.re1, tidx);
            insert_default_tags(spec, re->cat.re2, tidx);
            break;
        case RE::ITER:
            insert_default_tags(spec, re->iter.re, tidx);
            break;
        case RE::TAG:
            *tidx++ = re->tag.idx;
            break;
    }
}

void insert_default_tags(RESpec &spec)
{
    size_t *tidx0 = new size_t[spec.tags.size()], *tidx = tidx0;
    std::vector<RE*>::iterator
        i = spec.res.begin(),
        e = spec.res.end();
    for (; i != e; ++i) {
        insert_default_tags(spec, *i, tidx);
    }
    delete[] tidx0;
}

} // namespace re2c
