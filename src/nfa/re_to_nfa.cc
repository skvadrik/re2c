#include <stddef.h>
#include <stdint.h>
#include <vector>

#include "src/msg/msg.h"
#include "src/nfa/nfa.h"
#include "src/options/opt.h"
#include "src/parse/ast.h"
#include "src/regexp/regexp.h"
#include "src/regexp/tag.h"
#include "src/util/check.h"

// note [counted repetition and iteration expansion]
//
// It is more convenient to express zero-or-more iterations in terms of one-or-more iterations than
// vice versa, because the expansion `r+ ::= r r*` duplicates `r`, while `r* = r+ | <empty>` allows
// one to avoid duplication.
//
// Sometimes duplcation is unavoidable, like `r{n}` for `n` > 1 and `r{n,m}` for `n` < `m`. In such
// cases we duplicate `r` together with all tags; this may cause multiple (non-bottom) occurences of
// the same tag in the TNFA. Determinization must be careful to track multiple occurences of the
// same tag while building epsilon-closure (this matters for POSIX disambiguation strategy).
//
// We allow tags to apper only once in the original regular expression. This is not strictly
// necessary (putting the same tag in non-overlapping alternative branches may be handy), but it
// would allow to create very confusing regexps and the disambiguation strategy would behave
// strangely.

namespace re2c {
namespace {

// On-stack information for computing approximate NFA size and depth.
struct DfsTnfaParams {
    const Regexp* re; // current sub-regexp
    uint32_t size;    // sub-NFA size (only for alternative and concatenation)
    uint32_t depth;   // sub-NFA depth (only for alternative and concatenation)
    uint8_t succ;     // index of the next sucessor to be visited
};

static void estimate_nfa_params(
    const Regexp* re0, std::vector<DfsTnfaParams>& stack, size_t* psize, size_t* pdepth) {

    // the estimated size and depth of the last sub-regexp visited by DFS
    uint32_t size = 0, depth = 0;

    stack.push_back({re0, 0, 0, 0});

    while (!stack.empty()) {
        const DfsTnfaParams i = stack.back();
        stack.pop_back();

        const Regexp* re = i.re;
        if (re->kind == Regexp::Kind::NIL) {
            size = depth = 0;
        } else if (re->kind == Regexp::Kind::SYM || re->kind == Regexp::Kind::TAG) {
            size = depth = 1;
        } else if (re->kind == Regexp::Kind::ALT) {
            if (i.succ == 0) {
                // recurse into the left sub-regexp
                stack.push_back({re, 0, 0, 1});
                stack.push_back({re->alt.re1, 0, 0, 0});
            } else if (i.succ == 1) {
                // recurse into the right sub-regexp
                stack.push_back({re, size, depth, 2});
                stack.push_back({re->alt.re2, 0, 0, 0});
            } else {
                // both sub-regexp visited, recursive return
                // (left one is on stack, right one was just visited by DFS)
                size = 1 + i.size + size;
                depth = 1 + std::max(i.depth, depth);
            }
        } else if (re->kind == Regexp::Kind::CAT) {
            if (i.succ == 0) {
                // recurse into the left sub-regexp
                stack.push_back({re, 0, 0, 1});
                stack.push_back({re->cat.re1, 0, 0, 0});
            } else if (i.succ == 1) {
                // recurse into the right sub-regexp
                stack.push_back({re, size, depth, 2});
                stack.push_back({re->cat.re2, 0, 0, 0});
            } else {
                // both sub-regexp visited, recursive return
                // (left one is on stack, right one was just visited by DFS)
                size = i.size + size;
                depth = i.depth + depth;
            }
        } else if (re->kind == Regexp::Kind::ITER) {
            if (i.succ == 0) {
                // recurse into the sub-regexp
                stack.push_back({re, 0, 0, 1});
                stack.push_back({re->iter.re, 0, 0, 0});
            } else {
                // sub-regexp visited, recursive return
                // formula is the same for size and depth (it reflects NFA construction)
                const uint32_t min = re->iter.min, max = re->iter.max;
                size = max == Ast::MANY ? size * min + 1 : size * max + (max - min);
                depth = max == Ast::MANY ? depth * min + 1 : depth * max + (max - min);
            }
        }
    }
    DCHECK(stack.empty());

    *psize = *psize + size + 1;
    *pdepth = std::max(*pdepth, static_cast<size_t>(depth));
}

// On-stack information for iterative DFS that computes NFA statistics.
struct DfsTnfaStats {
    TnfaState* state; // current NFA state
    uint32_t next;    // index of the next state to be visited
};

static uint32_t nfa_stats(TnfaState* root) {
    std::vector<DfsTnfaStats> stack;
    uint32_t topord = 0;
    uint32_t ncores = 0;

    stack.push_back({root, 0});

    while (!stack.empty()) {
        // Don't store references to stack as it may grow and get reallocated.
        TnfaState* state = stack.back().state;
        const uint32_t next = stack.back().next++;
        const size_t stack_size = stack.size();

        if (next == 0) {
            // Recursive enter: increase state in-degree.
            ++state->indeg;

            if (state->indeg > 1) {
                // In-degree was non-null => we have been here before, stop DFS.
                stack.pop_back();
                continue;
            }
        }

        switch (state->kind) {
        case TnfaState::Kind::ALT:
            if (next == 0) {
                stack.push_back({state->out1, 0});
            } else if (next == 1) {
                stack.push_back({state->out2, 0});
            }
            break;
        case TnfaState::Kind::TAG:
            if (next == 0) {
                stack.push_back({state->out1, 0});
            }
            break;
        case TnfaState::Kind::RAN:
            if (next == 0) {
                ++ncores;
                stack.push_back({state->out1, 0});
            }
            break;
        case TnfaState::Kind::FIN:
            ++ncores;
            break;
        }

        if (stack.size() == stack_size) {
            // No new states have been pushed on stack: all children have been visited and this is
            // the recursive return. Set topological index.
            state->topord = topord++;
            stack.pop_back();
        }
    }

    return ncores;
}

// On-stack information for converting regexp to NFA.
struct DfsReToTnfa {
    // Current sub-regexp is stored by value, as it is modified by the algorithm (e.g. repetition
    // counters are decreased as the repetition sub-regexp is unfolded).
    Regexp re;
    // Start state of the current sub-NFA under construction. It is needed for complex sub-regexp
    // like alternative and repetition that are visited multiple times on stack, as sub-NFA for
    // their parts are constructed.
    TnfaState* start;
    // End state of the current sub-NFA. It is passed top-down, which is necessary, because it gets
    // recorded in multiple NFA fragments (patching the end states when connecting the fragments
    // would require keeping a list of states to patch for each fragment).
    TnfaState* end;
};

static void one_re_to_nfa(
        Tnfa& nfa, const RESpec& spec, uint32_t rule, std::vector<DfsReToTnfa>& stack) {
    // Start state of the last constructed sub-NFA (available after the stack item for it has been
    // popped off stack and the preceding stack item is being processed).
    TnfaState* start = nullptr;

    DCHECK(stack.empty());
    stack.push_back({*spec.res[rule], nullptr, nfa.make_fin(rule)});

    while (!stack.empty()) {
        // Refs to top of stack are invalidated after popping or pushing anything (backing storage
        // for the stack may get reallocated).
        DfsReToTnfa& x = stack.back();
        Regexp& re = x.re;

        DCHECK(x.end != nullptr);

        switch (re.kind) {
        case Regexp::Kind::NIL:
            start = x.end;
            stack.pop_back();
            break;

        case Regexp::Kind::SYM:
            start = nfa.make_ran(rule, x.end, re.sym);
            stack.pop_back();
            break;

        case Regexp::Kind::TAG: {
            const Tag& tag = nfa.tags[re.tag.idx];
            start = (fixed(tag) && !capture(tag)) ? x.end : nfa.make_tag(rule, x.end, re.tag);
            stack.pop_back();
            break;
        }

        case Regexp::Kind::ALT:
            if (x.start == nullptr) {
                x.start = nfa.make_alt(rule, nullptr, nullptr);
                stack.push_back({*re.alt.re1, nullptr, x.end});
            } else if (x.start->out1 == nullptr) {
                x.start->out1 = start;
                stack.push_back({*re.alt.re2, nullptr, x.end});
            } else {
                x.start->out2 = start;
                start = x.start;
                stack.pop_back();
            }
            break;

        case Regexp::Kind::CAT:
            if (x.start == nullptr) {
                x.start = x.end; // needed only to distinguish the 1st and the 2nd visit
                stack.push_back({*re.cat.re2, nullptr, x.end});
            } else {
                // no need to revisit the parent node, replace it on stack with the child
                stack.back() = {*re.cat.re1, nullptr, start};
            }
            break;

        case Regexp::Kind::ITER:
            // see note [counted repetition and iteration expansion]
            if (re.iter.max == Ast::MANY) {
                // Unbounded repetition `r{n,}`, unfold as `r{n-1} r*`.
                if (x.start == nullptr) {
                    x.start = nfa.make_alt(rule, nullptr, x.end);
                    stack.push_back({*re.iter.re, nullptr, x.start});
                } else {
                    re.iter.max = re.iter.min -= 1;
                    x.start->out1 = start;
                }
            } else if (re.iter.min < re.iter.max) {
                // Bounded repetition `r{n,m}`, unfold as `r{n-1} r{1,m}` and further unfold
                // `r{1,m}` as `r{1,m-1} r | <empty>`.
                if (x.start == nullptr) {
                    start = x.end;
                } else {
                    --re.iter.max;
                    x.start->out1 = start;
                    start = x.start;

                    // POSIX: empty alternative first (speed up GOR1 by first exploring paths w/o
                    // optional empty repetitions). Leftmost greedy: non-empty alternative first.
                    if (spec.opts->captures_posix) {
                        std::swap(x.start->out1, x.start->out2);
                    }
                }
                if (re.iter.max != re.iter.min) {
                    x.start = nfa.make_alt(rule, nullptr, x.end);
                    stack.push_back({*re.iter.re, nullptr, start});
                }
            } else if (re.iter.min > 0) {
                // Bounded repetition `r{n}`, unfold as `r{n-1} r`.
                re.iter.max = re.iter.min -= 1;
                if (x.start == nullptr) {
                    start = x.start = x.end;
                }
                stack.push_back({*re.iter.re, nullptr, start});
            } else {
                stack.pop_back();
            }
            break;
        }
    }

    nfa.root = (nfa.root == nullptr) ? start : nfa.make_alt(rule, nfa.root, start);
}

} // anonymous namespace

Ret re_to_nfa(Tnfa& nfa, RESpec&& spec) {
    // Move ownership from regexp to TNFA.
    nfa.ir_alc = std::move(spec.ir_alc);
    nfa.charset = std::move(spec.charset);
    nfa.rules = std::move(spec.rules);
    nfa.tags = std::move(spec.tags);

    if (spec.res.empty()) return Ret::OK;

    // Estimate NFA size (the number of states) and depth (maximum length of a simple path). Do this
    // before the actual NFA construction to abort quickly if the limits are exceeded.
    std::vector<DfsTnfaParams> stack_nfa_params;
    size_t size = spec.res.size() - 1;
    size_t depth = 0;
    for (const Regexp* re : spec.res) {
        estimate_nfa_params(re, stack_nfa_params, &size, &depth);
    }
    if (size > MAX_NFA_STATES) {
        RET_FAIL(error("NFA has too many states"));
    } else if (depth > MAX_NFA_DEPTH) {
        RET_FAIL(error("NFA depth exceeds limits"));
    }

    nfa.nstates = 0;
    nfa.states = nfa.ir_alc.alloct<TnfaState>(size);

    std::vector<DfsReToTnfa> stack_re_to_nfa;
    for (size_t rule = 0; rule < spec.res.size(); ++rule) {
        one_re_to_nfa(nfa, spec, static_cast<uint32_t>(rule), stack_re_to_nfa);
    }
    DCHECK(nfa.nstates <= size);

    // In-degree and topological index are used by POSIX disambiguation; the number of core states
    // is used for both POSIX and leftmost.
    nfa.ncores = nfa_stats(nfa.root);

    return Ret::OK;
}

Tnfa::Tnfa()
    : states(nullptr),
      root(nullptr),
      nstates(0),
      ncores(0),
      ir_alc(),
      charset(),
      rules(),
      tags() {}

} // namespace re2c
