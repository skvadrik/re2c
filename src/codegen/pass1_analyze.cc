#include <stddef.h>
#include <stdint.h>

#include "src/adfa/adfa.h"
#include "src/codegen/output.h"
#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/dfa/tcmd.h"
#include "src/util/check.h"
#include "src/util/containers.h"

namespace re2c {

// All spans in b1 that lead to s1 are pairwise equal to that in b2 leading to s2
static bool matches(const CodeGo* go1, const State* s1, const CodeGo* go2, const State* s2) {
    const Span
    *b1 = go1->span, *e1 = &b1[go1->span_count],
     *b2 = go2->span, *e2 = &b2[go2->span_count];
    uint32_t lb1 = 0, lb2 = 0;

    for (;;) {
        for (; b1 < e1 && b1->to != s1; ++b1) {
            lb1 = b1->ub;
        }
        for (; b2 < e2 && b2->to != s2; ++b2) {
            lb2 = b2->ub;
        }
        if (b1 == e1) {
            return b2 == e2;
        }
        if (b2 == e2) {
            return false;
        }
        // Еags are forbidden: transitions on different symbols might go to the same state, but
        // they may have different tag sets.
        if (lb1 != lb2
                || b1->ub != b2->ub
                || b1->tags != TCID0
                || b2->tags != TCID0) {
            return false;
        }
        ++b1;
        ++b2;
    }
}

static void insert_bitmap(OutAllocator& alc, CodeBitmap* bitmap, const CodeGo* go, const State* s) {
    for (CodeBmState* b = bitmap->states->head; b; b = b->next) {
        if (matches(b->go, b->state, go, s)) return;
    }
    // bitmap list is constructed in reverse
    prepend(bitmap->states, code_bmstate(alc, go, s));
}

static CodeBmState* find_bitmap(const CodeBitmap* bitmap, const CodeGo* go, const State* s) {
    for (CodeBmState* b = bitmap->states->head; b; b = b->next) {
        if (b->state == s && matches(b->go, b->state, go, s)) return b;
    }
    return nullptr;
}

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
        OutAllocator& alc, const Span* spans, uint32_t span_count, bool skip, uint32_t eof) {
    CodeGoSw* go = alc.alloct<CodeGoSw>(1);
    go->cases = alc.alloct<CodeGoCase>(span_count);

    int64_t* ranges = alc.alloct<int64_t>(span_count * 2), *ranges_end = ranges;
    CodeGoCase* cases = go->cases, *c;
    const Span* span = spans, *endspan = span + span_count, *s;

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

    DCHECK(static_cast<uint32_t>(ranges_end - ranges) == 2 * span_count);
    go->ncases = static_cast<uint32_t>(cases - go->cases);

    // find default case
    DCHECK(span_count > 0);
    State* defstate = (endspan - 1)->to;
    for (c = go->cases; c < cases; ++c) {
        if (c->jump.to == defstate) {
            go->defcase = c;
            break;
        }
    }

    return go;
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
    // TODO: support transition elision in loop/switch and rec/func modes. This requires used-label
    // analysis before the start of code generation phase, because in some languages (Rust) there is
    // no fallthrough between cases and we can only elide a transition if we can elide the whole
    // case, which is only possible if there are no other transitions into this state (so its label
    // is unused).
    b.jump.elide = opts->code_model == CodeModel::GOTO_LABEL && !to;
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

    // In rec/func mode transition can only be elideed if there is a single branch.
    // Otherwise an IF/ELSE-IF.../ELSE is needed, where every branch ends in a tailcall
    // (in functional languages it is an expression and early returns are not possible).
    bool may_elide = opts->code_model != CodeModel::REC_FUNC || n == 1;

    for (;;) {
        if (n == 1 && s[0].to == next && may_elide) {
            add_branch(x, nullptr, nullptr, next, s[0], skip, eof, opts);
            break;
        } else if (n == 1) {
            add_branch(x, nullptr, s[0].to, next, s[0], skip, eof, opts);
            break;
        } else if (n == 2 && s[0].to == next && may_elide) {
            CodeCmp* cmp = code_cmp(alc, ">=", s[0].ub);
            add_branch(x, cmp, s[1].to, next, s[1], skip, eof, opts);
            add_branch(x, nullptr, nullptr, next, s[0], skip, eof, opts);
            break;
        } else if (n == 3
                && s[1].to == next
                && s[1].ub - s[0].ub == 1
                && s[2].to == s[0].to
                && s[2].tags == s[0].tags
                && may_elide) {
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
                           uint32_t span_count,
                           const Span* hspan,
                           uint32_t hspan_count,
                           const CodeBmState* bm,
                           State* next,
                           uint32_t eof,
                           const opt_t* opts) {
    CodeGoBm* x = alc.alloct<CodeGoBm>(1);
    x->bitmap = bm;
    x->hgo = nullptr;
    x->lgo = nullptr;

    Span* bspan = allocate<Span>(span_count); // temporary
    uint32_t bspan_count = unmap (bspan, span, span_count, bm->state);
    x->lgo = bspan_count == 0 ? nullptr
            : code_goswif(alc, bspan, bspan_count, next, false, eof, opts);
    // If there are any low spans, then next state for high spans must be NULL to trigger explicit
    // goto generation in linear `if`.
    x->hgo = hspan_count == 0 ? nullptr
            : code_goswif(alc, hspan, hspan_count, x->lgo ? nullptr : next, false, eof, opts);
    x->bitmap->state->label->used = true;
    operator delete(bspan);

    return x;
}

static CodeGoCpTable* code_gocp_table(OutAllocator& alc, const Span* span, uint32_t span_count) {
    CodeGoCpTable* x = alc.alloct<CodeGoCpTable>(1);
    x->table = alc.alloct<State*>(CodeGoCpTable::TABLE_SIZE);

    uint32_t c = 0;
    for (uint32_t i = 0; i < span_count; ++i) {
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
                           uint32_t span_count,
                           const Span* hspan,
                           uint32_t hspan_count,
                           State* next,
                           uint32_t eof,
                           const opt_t* opts) {
    CodeGoCp* x = alc.alloct<CodeGoCp>(1);
    x->hgo = hspan_count == 0 ? nullptr
            : code_goswif(alc, hspan, hspan_count, next, false, eof, opts);
    x->table = code_gocp_table(alc, span, span_count);
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

static void code_go(OutAllocator& alc, const Adfa& dfa, const opt_t* opts, State* from) {
    // Mark all states that are targets of `yyaccept` switch to as used.
    if (from->action.kind == Action::Kind::ACCEPT) {
        for (const AcceptTrans& a : *from->action.info.accepts) {
            a.state->label->used = true;
        }
    }

    CodeGo* go = &from->go;
    Span* span = go->span;

    if (go->span_count == 0) return;

    // With end-of-input rule $, mark states that are targets of fallback transitions as used.
    if (opts->fill_eof != NOEOF && !(go->span_count == 1 && from->next == span[0].to)) {
        State* f = fallback_state_with_eof_rule(dfa, opts, from, nullptr);
        if (f) f->label->used = true;
    }

    // In .dot format every node in the graph (a.k.a. DFA state) should be generated.
    if (opts->target == Target::DOT) from->label->used = true;

    // initialize high (wide) spans
    uint32_t hspan_count = 0;
    const Span* hspan = nullptr;
    for (uint32_t i = 0; i < go->span_count; ++i) {
        if (span[i].ub > 0x100) {
            hspan = &go->span[i];
            hspan_count = go->span_count - i;
            break;
        }
    }

    bool low_spans_have_tags = false;
    for (uint32_t i = 0; i < go->span_count - hspan_count; ++i) {
        if (go->span[i].tags != TCID0) {
            low_spans_have_tags = true;
            break;
        }
    }

    // initialize bitmaps
    uint32_t bitmap_count = 0;
    const CodeBmState* bm = nullptr;
    if (opts->bitmaps) {
        for (uint32_t i = 0; i < go->span_count; ++i) {
            State* s = go->span[i].to;
            if (!s->is_base) continue;

            const CodeBmState* b = find_bitmap(dfa.bitmap, go, s);
            if (b) {
                if (bm == nullptr) {
                    bm = b;
                }
                ++bitmap_count;
            }
        }
    }

    // only do EOF check in states that dispatch on symbol
    const uint32_t eof = from->go.span_count == 1 && !consume(from->go.span[0].to)
            ? NOEOF : opts->fill_eof;
    const uint32_t dspan_count = go->span_count - hspan_count - bitmap_count;
    const bool part_skip = opts->eager_skip && !go->skip;

    if (opts->target == Target::DOT) {
        go->kind = CodeGo::Kind::DOT;
        go->godot = code_gosw(alc, go->span, go->span_count, false, eof);
    } else if (opts->computed_gotos
               && !part_skip
               && dspan_count >= opts->computed_gotos_threshold
               && !low_spans_have_tags) {
        go->kind = CodeGo::Kind::CPGOTO;
        go->gocp = code_gocp(
                alc, go->span, go->span_count, hspan, hspan_count, from->next, eof, opts);
    } else if (opts->bitmaps && !part_skip && bitmap_count > 0) {
        go->kind = CodeGo::Kind::BITMAP;
        go->gobm = code_gobm(
                alc, go->span, go->span_count, hspan, hspan_count, bm, from->next, eof, opts);
        dfa.bitmap->used = true;
    } else {
        go->kind = CodeGo::Kind::SWITCH_IF;
        go->goswif = code_goswif(alc, go->span, go->span_count, from->next, part_skip, eof, opts);
    }
}

void init_go(CodeGo* go) {
    go->kind = CodeGo::Kind::EMPTY;
    go->span_count = 0;
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

// In rec-func mode we can precompute common YYFN parts.
// This should be done for each block (with block-level configurations YYFN and `fn:sep`)
// and once for the whole program (with whole-program configurations).
//
// This has to de done during the "analyze" pass because fallback transitions may be generated
// during this phase (in storable states mode).
LOCAL_NODISCARD(Ret gen_fn_common(OutAllocator& alc, CodeFnCommon** fn_common, const opt_t* opts)) {
    if (opts->code_model != CodeModel::REC_FUNC) return Ret::OK;

    const char* name, *param, *type;

    auto split = [&](const std::string& s) -> Ret {
        std::vector<std::string> parts;
        for (size_t p1 = 0;;) {
            size_t p2 = s.find(opts->fn_sep, p1);
            if (p2 == std::string::npos) {
                parts.push_back(s.substr(p1, s.length() - p1));
                break;
            } else {
                parts.push_back(s.substr(p1, p2 - p1));
                p1 = p2 + opts->fn_sep.length();
            }
        }
        name = copystr(parts[0], alc);
        type = parts.size() > 1 ? copystr(parts[1], alc) : nullptr;
        param = parts.size() > 2 ? copystr(parts[2], alc) : name;
        if (parts.size() > 3) {
            RET_FAIL(error("`define:YYFN` element '%s' has too many parts", s.c_str()));
        }
        return Ret::OK;
    };

    CodeFnCommon* f = alc.alloct<CodeFnCommon>(1);

    DCHECK(!opts->api_fn.empty());
    CHECK_RET(split(opts->api_fn[0]));
    f->name = name;
    f->type = type;

    f->params = code_params(alc);
    f->params_yych = code_params(alc);
    f->args = code_args(alc);
    f->args_yych = code_args(alc);

    for (size_t i = 1; i < opts->api_fn.size(); ++i) {
        CHECK_RET(split(opts->api_fn[i]));
        if (type == nullptr) {
            RET_FAIL(error("missing type in `define:YYFN` element '%s'", opts->api_fn[i].c_str()));
        }

        append(f->params, code_param(alc, param, type));
        append(f->params_yych, code_param(alc, param, type));

        append(f->args, code_arg(alc, name));
        append(f->args_yych, code_arg(alc, name));
    }

    append(f->params_yych, code_param(alc, opts->var_char.c_str(), opts->api_char_type.c_str()));
    append(f->args_yych, code_arg(alc, opts->var_char.c_str()));

    *fn_common = f;
    return Ret::OK;
}

LOCAL_NODISCARD(Ret codegen_analyze_block(Output& output)) {
    OutputBlock& block = output.block();
    Adfas& dfas = block.dfas;
    OutAllocator& alc = output.allocator;
    const opt_t* opts = block.opts;

    Code* code = block.code->head;
    if (code == nullptr || code->kind != CodeKind::DFAS) {
        return Ret::OK;
    } else if (dfas.empty()) {
        code->kind = CodeKind::EMPTY;
        return Ret::OK;
    }

    CHECK_RET(gen_fn_common(output.allocator, &block.fn_common, opts));

    const std::unique_ptr<Adfa>& first_dfa = *dfas.begin();

    for (const std::unique_ptr<Adfa>& dfa : dfas) {
        const bool first = (dfa == first_dfa);

        if (opts->bitmaps) {
            dfa->bitmap = code_bitmap(alc, std::min(dfa->upper_char, 256u));
            for (State* s = dfa->head; s; s = s->next) {
                if (s->is_base) {
                    DCHECK(s->next);
                    insert_bitmap(alc, dfa->bitmap, &s->next->go, s);
                }
            }
        }

        // Allocate labels for DFA states, but do not assign indices yet: they will be assigned
        // after the used label analysis only to the labels that are used.
        for (State* s = dfa->head; s; s = s->next) {
            s->label = new_label(alc, Label::NONE);
        }

        switch (opts->code_model) {
        case CodeModel::GOTO_LABEL:
            if (first) {
                if (opts->label_start_force) {
                    // User-enforced start label.
                    block.start_label = new_label(alc, output.label_counter++);
                    block.start_label->used = true;
                } else if (opts->storable_state) {
                    // Start label is needed with storable states: it points to the first state of
                    // a block (before condition dispatch if conditions are used).
                    block.start_label = new_label(alc, output.label_counter++);
                }
            }
            // Initial label points to the start of the DFA (after condition dispatch in `-c`).
            dfa->initial_label = new_label(alc, output.label_counter++);
            break;
        case CodeModel::LOOP_SWITCH:
            // First state label is always used, as there are no jumps in the middle of a case.
            dfa->head->label->used = true;
            // With loop/switch there are no labels, and each block has its own state switch where
            // all conditions are joined. Restart state counter from zero so that cases start from
            // zero. With skeleton conditions are separate.
            if (first || opts->target == Target::SKELETON) output.label_counter = 0;
            break;
        case CodeModel::REC_FUNC:
            // First state label is always used, as there are no jumps in the middle of a function.
            dfa->head->label->used = true;
            if (first) {
                if (!dfa->cond.empty()) {
                    // Condition dispatch is a separate function named after the start label.
                    block.start_label = new_label(alc, output.label_counter++);
                } else if (opts->storable_state) {
                    // No conditions => storable states use first state label as a start label.
                    block.start_label = dfa->head->label;
                }
            }
            break;
        }

        // Generate DFA transitions and perform used label analysis: for every transition mark its
        // destination state label as used.
        for (State* s = dfa->head; s; s = s->next) {
            code_go(alc, *dfa, opts, s);
        }

        // Assign label indices (only to the labels that are used).
        for (State* s = dfa->head; s; s = s->next) {
            if (s->label->used) s->label->index = output.label_counter++;
        }

        if (dfa->head->label->used && !opts->eager_skip) {
            dfa->initial_label->used = true;
        }

        if (!dfa->cond.empty()) {
            // In loop/switch or rec/func mode, condition numbers are the numeric indices of their
            // initial DFA state. Otherwise we do not assign explicit numbers, and conditions are
            // implicitly assigned consecutive numbers starting from zero.
            block.conds.push_back({dfa->cond,
                    opts->code_model == CodeModel::GOTO_LABEL ? 0 : dfa->head->label->index});
        }
    }

    // In loop/switch mode storable states occupy continuous index range after the last state index.
    // In goto/label and rec/func modes they use separate global enumeration that starts from zero.
    uint32_t& counter = opts->code_model == CodeModel::LOOP_SWITCH
            ? output.label_counter : output.fill_label_counter;
    for (const std::unique_ptr<Adfa>& dfa : dfas) {
        for (State* s = dfa->head; s; s = s->next) {
            if (s->fill_state == s) {
                s->fill_label = new_label(alc, counter++);

                if (opts->storable_state) {
                    block.fill_goto[s->fill_label->index] =
                            gen_goto_after_fill(output, *dfa, s, nullptr);
                }
            }
        }
    }

    return Ret::OK;
}

Ret codegen_analyze(Output& output) {
    CHECK_RET(gen_fn_common(output.allocator, &output.fn_common, output.total_opts));

    for (const blocks_t& bs : {output.cblocks, output.hblocks}) {
        for (OutputBlock* b : bs) {
            output.set_current_block(b);
            CHECK_RET(codegen_analyze_block(output));
        }
    }

    // Generate implicit condiiton enum in the header, if there is no explicit directive.
    const opt_t* opts = output.total_opts;
    if (!opts->header_file.empty() && opts->start_conditions && output.cond_enum_autogen) {
        output.header_mode(true);
        output.gen_stmt(code_newline(output.allocator));
        output.gen_stmt(code_fmt(output.allocator, CodeKind::COND_ENUM, nullptr, nullptr, nullptr));
        output.header_mode(false);
    }

    output.set_current_block(nullptr);
    return Ret::OK;
}

// C++11 requres outer decl for ODR-used static constexpr data members (not needed in C++17).
constexpr uint32_t Label::NONE;
constexpr uint32_t CodeGoCpTable::TABLE_SIZE;

} // end namespace re2c
