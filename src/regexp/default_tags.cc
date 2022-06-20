#include <stddef.h>
#include <algorithm>
#include <memory>
#include <vector>

#include "src/debug/debug.h"
#include "src/options/opt.h"
#include "src/regexp/re.h"
#include "src/regexp/tag.h"

namespace re2c {
namespace {

static RE* negative_tags(RESpec& spec, const size_t* stidx, const size_t* etidx) {
    RE* x = nullptr;

    // Add transitions for all negative tags (including nested ones). It allows to avoid tag
    // initialization and fixup at the end of match, at the cost of adding more tag actions.
    if (spec.opts->nested_negative_tags) {
        for (; stidx < etidx; ++stidx) {
            x = re_cat(spec, x, re_tag(spec, *stidx, true));
        }
    }

    // Add transition only for one top-level negative tag, and save the full range of negative tags
    // in this tag's metadata. This reduces the amount of tag actions at the cost of
    // post-processing. (This option is essential for TNFA simulation and causes significant speedup
    // on tests with many tags.)
    else if (stidx < etidx) {
        // POSIX syntax means that tags are defined by capturing parentheses. TNFA with raw tags is
        // possible, but we do not have any use cases yet.
        DASSERT(spec.opts->posix_syntax);
        // With POSIX syntax we must have at least two tags: opening and closing
        DASSERT(etidx - stidx > 1);

        size_t first = *stidx, stag, etag;
        if (!spec.opts->backward) {
            DASSERT(first % 2 == 0); // forward matching, 1st tag is opening
            stag = first;
        } else {
            DASSERT(first % 2 == 1); // backward matching, 1st tag is closing
            stag = first - 1;
        }
        etag = stag + 1;

        // the range of nested tags is contiguous, find its upper bound
        size_t last = first;
        for (const size_t* i = stidx; ++i < etidx;) {
            last = std::max(last, *i);
        }

        x = re_cat(spec, x, re_tag(spec, etag, true));
        spec.tags[etag].lnest = stag;
        spec.tags[etag].hnest = last + 1;
    }

    return x;
}

struct StackItem {
    // current RE
    RE* re;

    // Start of the subsequence of tags for the left/right sub-RE (null if the sub-RE has not been
    // traversed yet, ot if RE is not an alternative).
    size_t* ltag, *rtag;
};

} // anonymous namespace

// Fictive tags do not really need default counterparts: maximization can work without them based on
// version numbers. For now it does not seem like a useful optimization, but some day in the future
// it might change.
void insert_default_tags(RESpec& spec) {
    size_t* tags = new size_t[spec.tags.size()], *tag = tags;
    std::vector<StackItem> stack;

    std::vector<RE*>::reverse_iterator i_re;
    for (i_re = spec.res.rbegin(); i_re != spec.res.rend(); ++i_re) {
        stack.push_back({*i_re, nullptr, nullptr});
    }

    while (!stack.empty()) {
        StackItem i = stack.back();
        stack.pop_back();
        RE* re = i.re;

        if (re->kind == RE::Kind::ALT) {
            if (i.ltag == nullptr) {
                // collect tags from the left sub-RE and return to this RE
                stack.push_back({re, tag, nullptr});
                stack.push_back({re->alt.re1, nullptr, nullptr});
            } else if (i.rtag == nullptr) {
                // collect tags from the right sub-RE and return to this RE
                stack.push_back({re, i.ltag, tag});
                stack.push_back({re->alt.re2, nullptr, nullptr});
            } else {
                // both sub-RE traversed, add negative tags
                RE* x = negative_tags(spec, i.ltag, i.rtag);
                RE* y = negative_tags(spec, i.rtag, tag);

                // Decision to place negative tags before/after could be based on POSIX semantics,
                // not syntax. But strangely on some tests placing before results in better
                // performance. More benchmarks are needed to understand this (with AOT/JIT,
                // TNFA/TDFA).
                re->alt.re1 = re_cat(spec, re->alt.re1, y);
                re->alt.re2 = spec.opts->posix_syntax
                              ? re_cat(spec, x, re->alt.re2)
                              : re_cat(spec, re->alt.re2, x);
            }
        } else if (re->kind == RE::Kind::CAT) {
            stack.push_back({re->cat.re2, nullptr, nullptr});
            stack.push_back({re->cat.re1, nullptr, nullptr});
        } else if (re->kind == RE::Kind::ITER) {
            stack.push_back({re->iter.re, nullptr, nullptr});
        } else if (re->kind == RE::Kind::TAG) {
            *tag++ = re->tag.idx;
        }
    }

    delete[] tags;
}

} // namespace re2c
