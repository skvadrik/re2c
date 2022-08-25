#include <stddef.h>
#include <stdint.h>

#include "src/adfa/adfa.h"
#include "src/codegen/code.h"
#include "src/options/opt.h"
#include "src/dfa/tcmd.h"
#include "src/util/check.h"
#include "src/util/containers.h"

namespace re2c {

static CodeGoIf* code_goif(OutAllocator& alc,
                           CodeGoIf::Kind kind,
                           const Span* sp,
                           uint32_t nsp,
                           State* next,
                           bool skip,
                           uint32_t eof,
                           const opt_t* opts);

static bool is_eof(uint32_t eof, uint32_t ub) {
    return eof != NOEOF && eof + 1 == ub;
}

static CodeGoSw* code_gosw(
        OutAllocator& alc, const Span* spans, uint32_t nspans, bool skip, uint32_t eof) {
    CodeGoSw* go = alc.alloct<CodeGoSw>(1);
    go->cases = alc.alloct<CodeGoCase>(nspans);

    int64_t* ranges = alc.alloct<int64_t>(nspans * 2), *ranges_end = ranges;
    CodeGoCase* cases = go->cases, *c;
    const Span* span = spans, *endspan = span + nspans, *s;

    for (; span < endspan; ++span) {
        State* to = span->to;
        const tcid_t tags  = span->tags;
        const bool eofcase = is_eof(eof, span->ub);

        // look for an existing case with the same destination state and tags
        for (c = go->cases; c < cases; ++c) {
            if (c->jump.to == to && c->jump.tags == tags) break;
        }

        if (c == cases) {
            // no such case found, add a new case
            ++cases;

            to->label->used = true;

            c->jump.to = to;
            c->jump.tags = span->tags;
            c->jump.skip = skip && consume(to);
            c->jump.eof = eofcase;
            c->jump.elide = false;

            // Collect ranges that have the current destination state and identical tags.
            int64_t* ranges_start = ranges_end;
            int64_t ub = span == spans ? 0 : (span - 1)->ub;
            for (s = span; s < endspan; ++s) {
                if (s->to == to && s->tags == tags) {
                    *ranges_end++ = ub;
                    *ranges_end++ = s->ub;
                }
                ub = s->ub;
            }
            c->ranges = code_ranges(alc, VarType::YYCTYPE, ranges_start, ranges_end);
        } else {
            // found a case that already contains this range
            c->jump.eof |= eofcase;
        }
    }

    DCHECK(static_cast<uint32_t>(ranges_end - ranges) == 2 * nspans);
    go->ncases = static_cast<uint32_t>(cases - go->cases);

    // find default case
    DCHECK(nspans > 0);
    State* defstate = (endspan - 1)->to;
    for (c = go->cases; c < cases; ++c) {
        if (c->jump.to == defstate) {
            go->defcase = c;
            break;
        }
    }

    return go;
}

static CodeCmp* code_cmp(OutAllocator& alc, const char* cmp, uint32_t val) {
    CodeCmp* x = alc.alloct<CodeCmp>(1);
    x->cmp = cmp;
    x->val = val;
    return x;
}

static CodeGoIfB* code_goifb(OutAllocator& alc,
                             const Span* s,
                             uint32_t n,
                             State* next,
                             bool skip,
                             uint32_t eof,
                             const opt_t* opts) {
    const uint32_t l = n / 2;
    const uint32_t h = n - l;
    CodeGoIf::Kind tkind = l > 4 ? CodeGoIf::Kind::BINARY : CodeGoIf::Kind::LINEAR;
    CodeGoIf::Kind ekind = h > 4 ? CodeGoIf::Kind::BINARY : CodeGoIf::Kind::LINEAR;

    CodeGoIfB* x = alc.alloct<CodeGoIfB>(1);
    x->cond = code_cmp(alc, "<=", s[l - 1].ub - 1);
    x->gothen = code_goif(alc, tkind, &s[0], l, next, skip, eof, opts);
    x->goelse = code_goif(alc, ekind, &s[l], h, next, skip, eof, opts);
    return x;
}

static void add_branch(CodeGoIfL* go,
                       const CodeCmp* cond,
                       State* to,
                       State* next,
                       const Span& sp,
                       bool skip,
                       uint32_t eof,
                       const opt_t* opts) {
    CodeGoIfL::Branch& b = go->branches[go->nbranches++];
    b.cond = cond;
    if (to) to->label->used = true;
    b.jump.to = to ? to : next;
    b.jump.tags = sp.tags;
    b.jump.skip = skip && consume(sp.to);
    b.jump.eof = is_eof(eof, sp.ub);
    // TODO: support transition elision with --loop-switch option. This requires used-label analysis
    // before the start of code generation phase, because in Rust there is no fallthrough between
    // cases and we can only elide a transition if we can elide the whole case, which is only
    // possible if there are no other transitions into this state (so its label is unused).
    b.jump.elide = !opts->loop_switch && !to;
}

static CodeGoIfL* code_goifl(OutAllocator& alc,
                             const Span* s,
                             uint32_t n,
                             State* next,
                             bool skip,
                             uint32_t eof,
                             const opt_t* opts) {
    CodeGoIfL* x = alc.alloct<CodeGoIfL>(1);
    x->nbranches = 0;
    x->branches = alc.alloct<CodeGoIfL::Branch>(n);
    x->def = eof == NOEOF ? nullptr : next;

    for (;;) {
        if (n == 1 && s[0].to == next) {
            add_branch(x, nullptr, nullptr, next, s[0], skip, eof, opts);
            break;
        } else if (n == 1) {
            add_branch(x, nullptr, s[0].to, next, s[0], skip, eof, opts);
            break;
        } else if (n == 2 && s[0].to == next) {
            CodeCmp* cmp = code_cmp(alc, ">=", s[0].ub);
            add_branch(x, cmp, s[1].to, next, s[1], skip, eof, opts);
            add_branch(x, nullptr, nullptr, next, s[0], skip, eof, opts);
            break;
        } else if (n == 3
                   && s[1].to == next
                   && s[1].ub - s[0].ub == 1
                   && s[2].to == s[0].to
                   && s[2].tags == s[0].tags) {
            CodeCmp* cmp = code_cmp(alc, "!=", s[0].ub);
            add_branch(x, cmp, s[0].to, next, s[0], skip, eof, opts);
            add_branch(x, nullptr, nullptr, next, s[1], skip, eof, opts);
            break;
        } else if (n >= 3
                   && s[1].ub - s[0].ub == 1
                   && s[2].to == s[0].to
                   && s[2].tags == s[0].tags) {
            CodeCmp* cmp = code_cmp(alc, "==", s[0].ub);
            add_branch(x, cmp, s[1].to, next, s[1], skip, eof, opts);
            n -= 2;
            s += 2;
        } else {
            CodeCmp* cmp = code_cmp(alc, "<=", s[0].ub - 1);
            add_branch(x, cmp, s[0].to, next, s[0], skip, eof, opts);
            n -= 1;
            s += 1;
        }
    }

    return x;
}

static CodeGoIf* code_goif(OutAllocator& alc,
                           CodeGoIf::Kind kind,
                           const Span* sp,
                           uint32_t nsp,
                           State* next,
                           bool skip,
                           uint32_t eof,
                           const opt_t* opts) {
    CodeGoIf* x = alc.alloct<CodeGoIf>(1);
    x->kind = kind;
    if (kind == CodeGoIf::Kind::BINARY) {
        x->goifb = code_goifb(alc, sp, nsp, next, skip, eof, opts);
    } else {
        x->goifl = code_goifl(alc, sp, nsp, next, skip, eof, opts);
    }
    return x;
}

static CodeGoSwIf* code_goswif(OutAllocator& alc, 
                               const Span* sp,
                               uint32_t nsp,
                               State* next,
                               bool skip,
                               uint32_t eof,
                               const opt_t* opts) {
    CodeGoSwIf* x = alc.alloct<CodeGoSwIf>(1);
    if ((!opts->nested_ifs && nsp > 2)
            || (nsp > 8 && (sp[nsp - 2].ub - sp[0].ub <= 3 * (nsp - 2)))) {
        x->kind = CodeGoSwIf::Kind::SWITCH;
        x->gosw = code_gosw(alc, sp, nsp, skip, eof);
    } else if (nsp > 5) {
        x->kind = CodeGoSwIf::Kind::IF;
        x->goif = code_goif(alc, CodeGoIf::Kind::BINARY, sp, nsp, next, skip, eof, opts);
    } else {
        x->kind = CodeGoSwIf::Kind::IF;
        x->goif = code_goif(alc, CodeGoIf::Kind::LINEAR, sp, nsp, next, skip, eof, opts);
    }
    return x;
}

// Find all spans that map to the given state. For each of them find upper adjacent span that maps
// to another state (if any, otherwize try the lower one). If the input contains a single span that
// maps to the given state, then the output contains zero spans.
static uint32_t unmap(Span* new_span, const Span* old_span, uint32_t old_nspans, const State* x) {
    uint32_t new_nspans = 0;
    for (uint32_t i = 0; i < old_nspans; ++i) {
        if (old_span[i].to != x) {
            if (new_nspans > 0
                    && new_span[new_nspans - 1].to == old_span[i].to
                    && new_span[new_nspans - 1].tags == old_span[i].tags) {
                new_span[new_nspans - 1].ub = old_span[i].ub;
            } else {
                new_span[new_nspans].to = old_span[i].to;
                new_span[new_nspans].ub = old_span[i].ub;
                new_span[new_nspans].tags = old_span[i].tags;
                ++new_nspans;
            }
        }
    }
    if (new_nspans > 0) {
        new_span[new_nspans - 1].ub = old_span[old_nspans - 1].ub;
    }
    return new_nspans;
}

static CodeGoBm* code_gobm(OutAllocator& alc,
                           const Span* span,
                           uint32_t nSpans,
                           const Span* hspan,
                           uint32_t hSpans,
                           const CodeBmState* bm,
                           State* next,
                           uint32_t eof,
                           const opt_t* opts) {
    CodeGoBm* x = alc.alloct<CodeGoBm>(1);
    x->bitmap = bm;
    x->hgo = nullptr;
    x->lgo = nullptr;

    Span* bspan = allocate<Span>(nSpans); // temporary
    uint32_t bSpans = unmap (bspan, span, nSpans, bm->state);
    x->lgo = bSpans == 0 ? nullptr : code_goswif(alc, bspan, bSpans, next, false, eof, opts);
    // If there are any low spans, then next state for high spans must be NULL to trigger explicit
    // goto generation in linear `if`.
    x->hgo = hSpans == 0 ? nullptr
             : code_goswif(alc, hspan, hSpans, x->lgo ? nullptr : next, false, eof, opts);
    x->bitmap->state->label->used = true;
    operator delete(bspan);

    return x;
}

static CodeGoCpTable* code_gocp_table(OutAllocator& alc, const Span* span, uint32_t nSpans) {
    CodeGoCpTable* x = alc.alloct<CodeGoCpTable>(1);
    x->table = alc.alloct<State*>(CodeGoCpTable::TABLE_SIZE);

    uint32_t c = 0;
    for (uint32_t i = 0; i < nSpans; ++i) {
        for(; c < span[i].ub && c < CodeGoCpTable::TABLE_SIZE; ++c) {
            State* to = span[i].to;
            x->table[c] = to;
            to->label->used = true;
        }
    }

    return x;
}

static CodeGoCp* code_gocp(OutAllocator& alc,
                           const Span* span,
                           uint32_t nSpans,
                           const Span* hspan,
                           uint32_t hSpans,
                           State* next,
                           uint32_t eof,
                           const opt_t* opts) {
    CodeGoCp* x = alc.alloct<CodeGoCp>(1);
    x->hgo = hSpans == 0 ? nullptr : code_goswif(alc, hspan, hSpans, next, false, eof, opts);
    x->table = code_gocp_table(alc, span, nSpans);
    return x;
}

State* fallback_state_with_eof_rule(
        const Adfa& dfa, const opt_t* opts, const State* state, tcid_t* ptags) {
    CHECK(opts->fill_eof != NOEOF);

    State* fallback = nullptr;
    tcid_t falltags = TCID0;

    if (state->action.kind == Action::Kind::INITIAL) {
        // End-of-input rule $ in the initial state takes priority over any other rule.
        fallback = dfa.eof_state;
        falltags = TCID0;
    } else if (state->rule != Rule::NONE) {
        // EOF in accepting state: match the rule in this state.
        fallback = dfa.finstates[state->rule];
        falltags = state->rule_tags;
    } else {
        // EOF in a non-accepting state: fallback to default state.
        fallback = dfa.defstate;
        falltags = state->fall_tags;
    }

    if (ptags) *ptags = falltags;
    return fallback;
}

void code_go(OutAllocator& alc, const Adfa& dfa, const opt_t* opts, State* from) {
    // Mark all states that are targets of `yyaccept` switch to as used.
    if (from->action.kind == Action::Kind::ACCEPT) {
        for (const AcceptTrans& a : *from->action.info.accepts) {
            a.state->label->used = true;
        }
    }

    CodeGo* go = &from->go;
    Span* span = go->span;

    if (go->nspans == 0) return;

    // With end-of-input rule $, mark states that are targets of fallback transitions as used.
    if (opts->fill_eof != NOEOF && !(go->nspans == 1 && from->next == span[0].to)) {
        State* f = fallback_state_with_eof_rule(dfa, opts, from, nullptr);
        if (f) f->label->used = true;
    }

    // In .dot format every node in the graph (a.k.a. DFA state) should be generated.
    if (opts->target == Target::DOT) from->label->used = true;

    // initialize high (wide) spans
    uint32_t hSpans = 0;
    const Span* hspan = nullptr;
    for (uint32_t i = 0; i < go->nspans; ++i) {
        if (span[i].ub > 0x100) {
            hspan = &go->span[i];
            hSpans = go->nspans - i;
            break;
        }
    }

    bool low_spans_have_tags = false;
    for (uint32_t i = 0; i < go->nspans - hSpans; ++i) {
        if (go->span[i].tags != TCID0) {
            low_spans_have_tags = true;
            break;
        }
    }

    // initialize bitmaps
    uint32_t nBitmaps = 0;
    const CodeBmState* bm = nullptr;
    if (opts->bitmaps) {
        for (uint32_t i = 0; i < go->nspans; ++i) {
            State* s = go->span[i].to;
            if (!s->isBase) continue;

            const CodeBmState* b = find_bitmap(dfa.bitmap, go, s);
            if (b) {
                if (bm == nullptr) {
                    bm = b;
                }
                ++nBitmaps;
            }
        }
    }

    // only do EOF check in states that dispatch on symbol
    const uint32_t eof = from->go.nspans == 1 && !consume(from->go.span[0].to)
            ? NOEOF : opts->fill_eof;
    const uint32_t dSpans = go->nspans - hSpans - nBitmaps;
    const bool part_skip = opts->eager_skip && !go->skip;

    if (opts->target == Target::DOT) {
        go->kind = CodeGo::Kind::DOT;
        go->godot = code_gosw(alc, go->span, go->nspans, false, eof);
    } else if (opts->cgoto
               && !part_skip
               && dSpans >= opts->cgoto_threshold
               && !low_spans_have_tags) {
        go->kind = CodeGo::Kind::CPGOTO;
        go->gocp = code_gocp(alc, go->span, go->nspans, hspan, hSpans, from->next, eof, opts);
    } else if (opts->bitmaps && !part_skip && nBitmaps > 0) {
        go->kind = CodeGo::Kind::BITMAP;
        go->gobm = code_gobm(alc, go->span, go->nspans, hspan, hSpans, bm, from->next, eof, opts);
        dfa.bitmap->used = true;
    } else {
        go->kind = CodeGo::Kind::SWITCH_IF;
        go->goswif = code_goswif(alc, go->span, go->nspans, from->next, part_skip, eof, opts);
    }
}

void init_go(CodeGo* go) {
    go->kind = CodeGo::Kind::EMPTY;
    go->nspans = 0;
    go->span = nullptr;
    go->tags = TCID0;
    go->skip = false;
}

bool consume(const State* s) {
    switch (s->action.kind) {
    case Action::Kind::RULE:
    case Action::Kind::MOVE:
    case Action::Kind::ACCEPT:
        return false;
    case Action::Kind::MATCH:
    case Action::Kind::INITIAL:
    case Action::Kind::SAVE:
        return true;
    }
    UNREACHABLE();
    return true;
}

// C++11 requres outer decl for ODR-used static constexpr data members (not needed in C++17).
constexpr uint32_t Label::NONE;
constexpr uint32_t CodeGoCpTable::TABLE_SIZE;

} // namespace re2c
