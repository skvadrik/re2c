#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <ostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "src/adfa/adfa.h"
#include "src/codegen/helpers.h"
#include "src/codegen/output.h"
#include "src/msg/location.h"
#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/options/syntax.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/skeleton/skeleton.h"
#include "src/util/check.h"
#include "src/util/string_utils.h"

namespace re2c {

bool endstate(const State* s) {
    // An 'end' state is a state which has no outgoing transitions on symbols. Usually 'end' states
    // are final states (not all final states are 'end' states), but sometimes it be initial
    // non-accepting state, e.g. in case of rule '[]'.
    DCHECK(s->go.span_count > 0);
    Action::Kind a = s->go.span[0].to->action.kind;
    return s->go.span_count == 1 && (a == Action::Kind::RULE || a == Action::Kind::ACCEPT);
}

static const char* gen_fill_label(Output& output, uint32_t index) {
    const opt_t* opts = output.block().opts;
    Scratchbuf& o = output.scratchbuf;
    DCHECK(o.empty());
    return o.str(opts->label_fill).u32(index).flush();
}

static void gen_peek(OutAllocator& alc, const State* s, CodeList* stmts) {
    // Do not generate YYPEEK statement in case `yych` is overwritten before it is used. This may
    // happen if there is a single transition which does not require matching on `yych` (one
    // exception is a transition to a move state, which doesn't have its own YYPEEK and relies on
    // the previous value of `yych`).
    bool omit_peek = s->go.span_count == 1 && s->go.span[0].to->action.kind != Action::Kind::MOVE;
    if (!omit_peek) append(stmts, code_peek(alc));
}

static void gen_state_set(Output& output, CodeList* stmts, const char* fillidx) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;

    o.str(opts->api_state_set);
    argsubst(o.stream(), opts->state_set_param, "state", true, fillidx);
    if (opts->state_set_naked) {
        append(stmts, code_text(alc, o.flush()));
    } else {
        o.cstr("(").cstr(fillidx).cstr(")");
        append(stmts, code_stmt(alc, o.flush()));
    }
}

static void gen_cond_set(Output& output, CodeList* stmts, const char* cond) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;

    o.str(opts->api_cond_set);
    argsubst(o.stream(), opts->cond_set_param, "cond", true, cond);
    if (opts->cond_set_naked) {
        append(stmts, code_text(alc, o.flush()));
    } else {
        o.cstr("(").cstr(cond).cstr(")");
        append(stmts, code_stmt(alc, o.flush()));
    }
}

static const char* gen_less_than(Scratchbuf& o, const opt_t* opts, size_t n) {
    if (opts->api == Api::CUSTOM) {
        o.str(opts->api_less_than);
        if (opts->api_style == ApiStyle::FUNCTIONS) {
            o.cstr("(").u64(n).cstr(")");
        } else {
            argsubst(o.stream(), opts->api_sigil, "len", true, n);
        }
    } else if (n == 1) {
        o.str(opts->api_limit).cstr(" <= ").str(opts->api_cursor);
    } else {
        o.cstr("(").str(opts->api_limit).cstr(" - ").str(opts->api_cursor).cstr(") < ").u64(n);
    }
    return o.flush();
}

static void gen_shift(
        Output& output, CodeList* stmts, int32_t shift, const std::string& tag, bool history) {
    if (shift == 0) return;

    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;
    const bool notag = tag.empty();

    o.str(notag ? opts->api_shift : (history ? opts->api_shift_mtag : opts->api_shift_stag));
    if (opts->api_style == ApiStyle::FUNCTIONS) {
        o.cstr("(");
        if (!notag) o.str(tag).cstr(", ");
        o.i32(shift).cstr(")");
        append(stmts, code_stmt(alc, o.flush()));
    } else {
        // Single-argument YYSHIFT allows short-form unnamed substitution, multi-argument
        // YYSHIFTSTAG / YYSHIFTMTAG require named placeholders.
        if (!notag) {
            argsubst(o.stream(), opts->api_sigil, "tag", false, tag);
        }
        argsubst(o.stream(), opts->api_sigil, "shift", notag, shift);
        append(stmts, code_text(alc, o.flush()));
    }
}

static void gen_settag(
        Output& output, CodeList* stmts, const std::string& tag, bool negative, bool history) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;

    const std::string& s = history
            ? (negative ? opts->api_mtag_neg : opts->api_mtag_pos)
            : (negative ? opts->api_stag_neg : opts->api_stag_pos);
    o.str(s);
    if (opts->api_style == ApiStyle::FUNCTIONS) {
        o.cstr("(").str(tag).cstr(")");
        append(stmts, code_stmt(alc, o.flush()));
    } else {
        argsubst(o.stream(), opts->api_sigil, "tag", true, tag);
        append(stmts, code_text(alc, o.flush()));
    }
}

static void gen_assign(
        Output& output, CodeList* stmts, const std::string& lhs, const std::string& rhs) {
    Scratchbuf& o = output.scratchbuf;
    o.str(lhs).cstr(" = ").str(rhs);
    append(stmts, code_stmt(output.allocator, o.flush()));
}

static void gen_assign_many(Output& output,
                            CodeList* stmts,
                            const std::vector<std::string>& many,
                            const std::string& rhs) {
    Scratchbuf& o = output.scratchbuf;
    for (const std::string& s : many) {
        o.str(s).cstr(" = ");
    }
    o.str(rhs);
    append(stmts, code_stmt(output.allocator, o.flush()));
}

static void gen_assign_many_to_first(
        Output& output, CodeList* stmts, const std::vector<std::string>& many) {
    if (many.size() <= 1) return;

    Scratchbuf& o = output.scratchbuf;
    for (size_t i = 1; i < many.size(); ++i) {
        o.str(many[i]).cstr(" = ");
    }
    o.str(many[0]);
    append(stmts, code_stmt(output.allocator, o.flush()));
}

static void gen_restore_ctx(Output& output, CodeList* stmts, const std::string& tag) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;
    const bool notag = tag.empty();

    o.str(notag ? opts->api_restore_ctx : opts->api_restore_tag);
    if (opts->api_style == ApiStyle::FUNCTIONS) {
        o.cstr("(").str(tag).cstr(")");
        append(stmts, code_stmt(alc, o.flush()));
    } else {
        if (!notag) {
            argsubst(o.stream(), opts->api_sigil, "tag", true, tag);
        }
        append(stmts, code_text(alc, o.flush()));
    }
}

static void gen_settags(Output& output, CodeList* tag_actions, const Adfa& dfa, tcid_t tcid) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;
    const bool generic = opts->api == Api::CUSTOM;
    const tcmd_t* cmd = dfa.tcpool[tcid];

    // single tag, backwards compatibility, use context marker
    if (cmd && dfa.oldstyle_ctxmarker) {
        if (generic) {
            o.str(opts->api_backup_ctx);
            if (opts->api_style == ApiStyle::FUNCTIONS) {
                o.cstr("()");
                append(tag_actions, code_stmt(alc, o.flush()));
            } else {
                append(tag_actions, code_text(alc, o.flush()));
            }
        } else {
            gen_assign(output, tag_actions, opts->api_ctxmarker, opts->api_cursor);
        }
        return;
    }

    for (const tcmd_t* p = cmd; p; p = p->next) {
        const tagver_t l = p->lhs, r = p->rhs, *h = p->history, *h0;
        const std::string le = vartag_expr(l, opts, dfa.mtagvers);
        const std::string re = vartag_expr(r, opts, dfa.mtagvers);
        std::string s;

        if (tcmd_t::iscopy(p)) {
            // "copy" command
            gen_assign(output, tag_actions, le, re);
        } else if (tcmd_t::isadd(p)) {
            // "save" command with history
            if (l != r) {
                gen_assign(output, tag_actions, le, re);
            }
            // history is reversed, so find its end and iterate back
            for (h0 = h; *h != TAGVER_ZERO; ++h);
            for (; h --> h0; ) {
                const bool negative = *h == TAGVER_BOTTOM;
                gen_settag(output, tag_actions, le, negative, true);
            }
        } else {
            // "save" command
            if (generic) {
                const bool negative = *h == TAGVER_BOTTOM;
                gen_settag(output, tag_actions, le, negative, false);
            } else {
                Scratchbuf o2(alc);
                for (const tcmd_t* q = p; q && tcmd_t::isset(q); p = q, q = q->next) {
                    Scratchbuf& x = q->history[0] == TAGVER_BOTTOM ? o : o2;
                    x.str(vartag_expr(q->lhs, opts, dfa.mtagvers)).cstr(" = ");
                }
                if (!o.empty()) {
                    o.cstr("NULL");
                    append(tag_actions, code_stmt(alc, o.flush()));
                }
                if (!o2.empty()) {
                    o2.str(opts->api_cursor);
                    append(tag_actions, code_stmt(alc, o2.flush()));
                }
            }
        }
    }
}

static void gen_fintags(Output& output, CodeList* stmts, const Adfa& dfa, const Rule& rule) {
    const opt_t* opts = output.block().opts;
    const bool generic = opts->api == Api::CUSTOM;
    const std::vector<Tag>& tags = dfa.tags;
    const tagver_t* fins = dfa.finvers;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;
    std::vector<std::string> fintags;

    if (rule.ncap > 0) {
        o.cstr("yynmatch = ").u64(rule.ncap);
        append(stmts, code_stmt(alc, o.flush()));
    }

    CodeList* varops = code_list(alc);
    CodeList* fixops = code_list(alc);
    CodeList* trailops = code_list(alc);
    CodeList* fixpostops = code_list(alc);
    std::string negtag;

    for (size_t t = rule.ltag; t < rule.htag; ++t) {
        const Tag& tag = tags[t];

        // structural tag that is only needed for disambiguation
        if (fictive(tag)) continue;

        expand_fintags(tag, fintags);

        if (!fixed(tag)) {
            // variable tag
            const std::string expr = vartag_expr(fins[t], opts, dfa.mtagvers);
            if (trailing(tag)) {
                const bool notag = dfa.oldstyle_ctxmarker;
                if (generic) {
                    gen_restore_ctx(output, trailops, notag ? "" : expr);
                } else {
                    gen_assign(
                            output, trailops, opts->api_cursor, notag ? opts->api_ctxmarker : expr);
                }
            } else {
                gen_assign_many(output, varops, fintags, expr);
            }
        } else {
            DCHECK(!history(tag));

            // fixed tag that is based on either variable tag or cursor
            const int32_t dist = static_cast<int32_t>(tag.dist);
            const bool fixed_on_cursor = tag.base == Tag::RIGHTMOST;
            const std::string base = fixed_on_cursor
                    ? opts->api_cursor
                    : vartag_expr(fins[tag.base], opts, dfa.mtagvers);

            if (trailing(tag)) {
                DCHECK(tag.toplevel);
                if (generic) {
                    if (!fixed_on_cursor) {
                        gen_restore_ctx(output, trailops, base);
                    }
                    gen_shift(output, trailops, -dist, "", false /* unused */);
                } else {
                    if (!fixed_on_cursor) {
                        o.str(opts->api_cursor).cstr(" = ").str(base);
                        if (dist > 0) o.cstr(" - ").i32(dist);
                    } else if (dist > 0) {
                        o.str(opts->api_cursor).cstr(" -= ").i32(dist);
                    }
                    append(trailops, code_stmt(alc, o.flush()));
                }
            } else {
                DCHECK(!fintags.empty());
                const std::string& first = fintags[0];

                if (generic) {
                    if (fixed_on_cursor) {
                        gen_settag(output, fixops, first, false, false);
                        gen_shift(output, fixops, -dist, first, false);
                        gen_assign_many_to_first(output, fixops, fintags);
                    } else if (dist == 0) {
                        gen_assign_many(output, fixops, fintags, base);
                    } else if (tag.toplevel) {
                        gen_assign(output, fixops, first, base);
                        gen_shift(output, fixops, -dist, first, false);
                        gen_assign_many_to_first(output, fixops, fintags);
                    } else {
                        // Split operations in two parts. First, set all fixed tags to their base
                        // tag. Second, choose one of the base tags to store negative value (with
                        // generic API there is no NULL constant) and compare fixed tags against it
                        // before shifting. This must be done after all uses of that base tag.
                        if (negtag.empty()) negtag = base;
                        gen_assign(output, fixops, first, base);
                        const char* cond = o.str(first).cstr(" != ").str(negtag).flush();
                        CodeList* then = code_list(alc);
                        gen_shift(output, then, -dist, first, false);
                        append(fixpostops, code_if_then_else(alc, cond, then, nullptr));
                    }
                } else {
                    if (dist == 0) {
                        gen_assign_many(output, fixops, fintags, base);
                    } else if (tag.toplevel) {
                        gen_assign_many(
                                output, fixops, fintags, o.str(base).cstr(" - ").i32(dist).flush());
                    } else {
                        // If base tag is NULL, fixed tag is also NULL, otherwise it equals the
                        // value of the base tag plus offset.
                        gen_assign(output, fixops, first, base);
                        const char* cond = o.str(base).cstr(" != NULL").flush();
                        CodeList* then = code_list(alc);
                        append(then, code_stmt(alc, o.str(first).cstr(" -= ").i32(dist).flush()));
                        append(fixops, code_if_then_else(alc, cond, then, nullptr));
                        gen_assign_many_to_first(output, fixops, fintags);
                    }
                }
            }
        }
    }

    // Variable tags must be set before fixed tags which depend on them. Trailing context is updated
    // after all tags, because fixed tags may depend on the rightmost position.
    append(stmts, varops);
    append(stmts, fixops);
    append(stmts, trailops);

    if (!negtag.empty()) {
        // With generic API there is no explicit negative NULL value, so it is necessary to
        // materialize no-match value in a tag.
        DCHECK(opts->api == Api::CUSTOM);
        append(stmts, code_text(alc, o.cstr("/* materialize no-match value */").flush()));
        gen_settag(output, stmts, negtag, true, false);
        append(stmts, fixpostops);
    }
}

void expand_fintags(const Tag& tag, std::vector<std::string>& fintags) {
    fintags.clear();
    if (trailing(tag)) {
        // empty list
    } else if (!capture(tag)) {
        // named tag
        fintags.push_back(tag.name);
    } else {
        // capture tag, maps to a range of parentheses
        for (size_t i = tag.lsub; i <= tag.hsub; i += 2) {
            fintags.push_back("yypmatch[" + to_string(i) + "]");
        }
    }
}

static void gen_continue_yyloop(Output& output, CodeList* stmts, const char* next) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;

    buf.str(opts->var_state).cstr(" = ").cstr(next);
    append(stmts, code_stmt(alc, buf.flush()));

    buf.cstr("continue");
    if (!opts->label_loop.empty()) buf.cstr(" ").str(opts->label_loop);
    append(stmts, code_stmt(alc, buf.flush()));
}

static CodeList* gen_fill_falllback(
        Output& output, const Adfa& dfa, const State* from, const State* to) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;

    DCHECK(opts->fill_eof != NOEOF);

    tcid_t falltags;
    const State* fallback = fallback_state_with_eof_rule(dfa, opts, from, &falltags);

    if (from->go.tags != TCID0) {
        // Tags have been hoisted out of transitions into state (this means that tags on all
        // transitions coincide, including the fallback transition). Do not add duplicate tags to
        // fallback transition.
        DCHECK(from->go.tags == falltags);
        falltags = TCID0;
    }

    CodeList* fallback_trans = code_list(alc);
    if (fallback != to || opts->storable_state) {
        // tag actions on the fallback transition
        gen_settags(output, fallback_trans, dfa, falltags);

        // go to fallback state
        if (!opts->loop_switch) {
            buf.cstr("goto ").str(opts->label_prefix).label(*fallback->label);
            append(fallback_trans, code_stmt(alc, buf.flush()));
        } else {
            const char* next = buf.label(*fallback->label).flush();
            gen_continue_yyloop(output, fallback_trans, next);
        }
    } else {
        // Transition can be elided, because control flow "falls through" to an identical
        // transition. Tags and skip (if present) are elided as well, because the next transition
        // covers them.
    }
    return fallback_trans;
}

CodeList* gen_goto_after_fill(Output& output, const Adfa& dfa, const State* from, const State* to) {
    const opt_t* opts = output.block().opts;
    const bool eof_rule = opts->fill_eof != NOEOF;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;

    CodeList* goto_fill = code_list(alc);

    if (opts->storable_state && eof_rule) {
        // With storable state and end-of-input rule $ the initial state dispatch needs to handle
        // YYFILL failure: if there is still not enough input, it must follow the fallback
        // transition for the state that triggered YYFILL. Fallback transition is inlined in the
        // state dispatch (as opposed to jumping to the corresponding DFA transition) because Go
        // backend does not support jumping in the middle of a nested block.
        CodeList* fallback = gen_fill_falllback(output, dfa, from, to);
        const char* less_than = gen_less_than(o, opts, 1 /*need*/);
        append(goto_fill, code_if_then_else(alc, less_than, fallback, nullptr));
    }

    // Transition to YYFILL label from the initial state dispatch or after YYFILL on transition.
    if (opts->fill_enable) {
        State* s = from->fill_state;
        if (opts->loop_switch) {
            const char* next = o.u32(s->label->index).flush();
            gen_continue_yyloop(output, goto_fill, next);
        } else if (opts->storable_state || eof_rule) {
            const char* flabel = gen_fill_label(output, s->fill_label->index);
            append(goto_fill, code_stmt(alc, o.cstr("goto ").cstr(flabel).flush()));
        }
    }

    return goto_fill;
}

static void gen_fill(
        Output& output, CodeList* stmts, const Adfa& dfa, const State* from, const State* to) {
    const opt_t* opts = output.block().opts;
    const bool eof_rule = opts->fill_eof != NOEOF;
    const size_t need = eof_rule ? 1 : from->fill;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;

    CodeList* fill = code_list(alc);

    if (opts->fill_enable) {
        if (opts->storable_state) {
            gen_state_set(output, fill, o.u32(from->fill_state->fill_label->index).flush());
        }

        // With end-of-input rule $ there is no YYFILL argument and no parameter to replace.
        o.str(opts->api_fill);
        if (!eof_rule) {
            argsubst(o.stream(), opts->fill_param, "len", true, need);
        }
        if (opts->fill_param_enable) {
            o.cstr("(");
            if (!eof_rule) o.u64(need);
            o.cstr(")");
        }
        if (eof_rule && !opts->storable_state) {
            // End-of-input rule $ without a storable state: check YYFILL return value. If it
            // succeeds (returns zero) then go to YYFILL label and rematch.
            if (!opts->fill_naked) o.cstr(" == 0");
            const char* fill_check = o.flush();
            CodeList* goto_rematch = gen_goto_after_fill(output, dfa, from, to);
            append(fill, code_if_then_else(alc, fill_check, goto_rematch, nullptr));
        } else {
            // Otherwise don't check YYFILL return value: assume that it does not return on failure.
            append(fill, opts->fill_naked ? code_text(alc, o.flush()) : code_stmt(alc, o.flush()));
        }
    }

    if (eof_rule && !opts->storable_state) {
        append(fill, gen_fill_falllback(output, dfa, from, to));
    }

    if (opts->fill_check && fill->head) {
        const char* less_than = gen_less_than(o, opts, need);
        append(stmts, code_if_then_else(alc, less_than, fill, nullptr));
    } else {
        append(stmts, fill);
    }
}

static void gen_fill_and_label(Output& output, CodeList* stmts, const Adfa& dfa, const State* s) {
    const opt_t* opts = output.block().opts;

    if (opts->fill_enable && !endstate(s) && opts->fill_eof == NOEOF && s->fill > 0) {
        gen_fill(output, stmts, dfa, s, nullptr);
    }

    if (opts->fill_eof != NOEOF) {
        // If the end-of-input rule $ is used, the lexer may jump to the YYFILL label to rescan the
        // current input character. Generate tag operations before the label to avoid applying them
        // multiple times in the above scenario (re-application may produce incorrect results in
        // case of non-idempotent operations).
        gen_settags(output, stmts, dfa, s->go.tags);
    }

    if (s->fill_label != nullptr && !opts->loop_switch) {
        const char* flabel = gen_fill_label(output, s->fill_label->index);
        append(stmts, code_slabel(output.allocator, flabel));
    }
}

static void gen_goto(
        Output& output, const Adfa& dfa, CodeList* stmts, const State* from, const CodeJump& jump) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;

    if (jump.eof) {
        gen_fill(output, stmts, dfa, from, jump.to);
    }

    gen_settags(output, stmts, dfa, jump.tags);

    if (jump.skip) {
        append(stmts, code_skip(alc));
    }

    if (!jump.elide) {
        if (!opts->loop_switch) {
            o.cstr("goto ").str(opts->label_prefix).label(*jump.to->label);
            append(stmts, code_stmt(alc, o.flush()));
        } else if (jump.to->label->used) {
            const char* next = o.label(*jump.to->label).flush();
            gen_continue_yyloop(output, stmts, next);
        }
    } else {
        // Goto can be elided, because control flow "falls through" to the correct DFA state. This
        // usually happens for the last statement in a sequence of "linear if" statements.
    }
}

static const char* gen_cond(Output& output, const CodeCmp* cond) {
    const opt_t* opts = output.block().opts;
    Scratchbuf& buf = output.scratchbuf;

    bool dot = opts->target == Target::DOT;
    bool hex = opts->encoding.type() == Enc::Type::EBCDIC
            || strcmp(opts->eval_word_conf("char_literals"), "hexadecimal") == 0;

    buf.str(opts->var_char).cstr(" ").str(cond->cmp).cstr(" ");
    print_char_or_hex(buf.stream(), cond->val, opts->encoding.cunit_size(), hex, dot);
    return buf.flush();
}

static CodeList* gen_gosw(Output& output, const Adfa& dfa, const CodeGoSw* go, const State* from) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;

    const char* expr = o.str(opts->var_char).flush();

    CodeCases* cases = code_cases(alc);
    CodeCase* defcase = nullptr;
    for (const CodeGoCase* c = go->cases, *e = c + go->ncases; c < e; ++c) {
        CodeList* body = code_list(alc);
        gen_goto(output, dfa, body, from, c->jump);
        if (c == go->defcase) {
            defcase = code_case_default(alc, body);
        } else {
            append(cases, code_case_ranges(alc, body, c->ranges));
        }
    }
    append(cases, defcase);

    CodeList* stmts = code_list(alc);
    append(stmts, code_switch(alc, expr, cases));

    return stmts;
}

static CodeList* gen_goif(Output& output, const Adfa& dfa, const CodeGoIf* go, const State* from);

static CodeList* gen_goifb(
        Output& output, const Adfa& dfa, const CodeGoIfB* go, const State* from) {
    OutAllocator& alc = output.allocator;
    CodeList* stmts = code_list(alc);
    const char* if_cond = gen_cond(output, go->cond);
    CodeList* if_then = gen_goif(output, dfa, go->gothen, from);
    CodeList* if_else = gen_goif(output, dfa, go->goelse, from);
    append(stmts, code_if_then_else(alc, if_cond, if_then, if_else));
    return stmts;
}

static CodeList* gen_goifl(
        Output& output, const Adfa& dfa, const CodeGoIfL* go, const State* from) {
    OutAllocator& alc = output.allocator;
    CodeList* stmts = code_list(alc);
    for (uint32_t i = 0; i < go->nbranches; ++i) {
        const CodeGoIfL::Branch& b = go->branches[i];
        const CodeCmp* cond = b.cond;
        if (cond) {
            const char* if_cond = gen_cond(output, cond);
            CodeList* if_then = code_list(alc);
            gen_goto(output, dfa, if_then, from, b.jump);
            append(stmts, code_if_then_else(alc, if_cond, if_then, nullptr));
        } else {
            gen_goto(output, dfa, stmts, from, b.jump);
        }
    }
    return stmts;
}

static CodeList* gen_goif(Output& output, const Adfa& dfa, const CodeGoIf* go, const State* from) {
    return go->kind == CodeGoIf::Kind::BINARY
           ? gen_goifb(output, dfa, go->goifb, from)
           : gen_goifl(output, dfa, go->goifl, from);
}

static CodeList* gen_goswif(
        Output& output, const Adfa& dfa, const CodeGoSwIf* go, const State* from) {
    return go->kind == CodeGoSwIf::Kind::SWITCH
           ? gen_gosw(output, dfa, go->gosw, from)
           : gen_goif(output, dfa, go->goif, from);
}

static CodeList* gen_gobm(Output& output, const Adfa& dfa, const CodeGoBm* go, const State* from) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;

    bool need_compare = !opts->eval_bool_conf("implicit_bool_conversion");
    if (need_compare) o.cstr("(");
    o.str(bitmap_name(opts, dfa.cond)).cstr("[").u32(go->bitmap->offset).cstr("+")
            .str(opts->var_char).cstr("]").cstr(" & ").yybm_char(go->bitmap->mask, opts, 1);
    if (need_compare) o.cstr(") != 0");
    const char* elif_cond = o.flush();

    CodeList* if_else = code_list(alc);
    const CodeJump jump = {go->bitmap->state, TCID0, false, false, false};
    gen_goto(output, dfa, if_else, from, jump);

    CodeList* stmts = code_list(alc);
    if (go->hgo != nullptr) {
        if (need_compare) o.cstr("(");
        o.str(opts->var_char).cstr(" & ~0xFF");
        if (need_compare) o.cstr(") != 0");
        const char* if_cond = o.flush();
        CodeList* if_then = gen_goswif(output, dfa, go->hgo, from);
        append(stmts, code_if_then_elif(alc, if_cond, if_then, elif_cond, if_else));
    } else {
        append(stmts, code_if_then_else(alc, elif_cond, if_else, nullptr, false));
    }
    if (go->lgo != nullptr) {
        append(stmts, gen_goswif(output, dfa, go->lgo, from));
    }

    return stmts;
}

static CodeList* gen_gocp_table(Output& output, const CodeGoCpTable* go) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;

    const char** elems = alc.alloct<const char*>(CodeGoCpTable::TABLE_SIZE);
    for (uint32_t i = 0; i < CodeGoCpTable::TABLE_SIZE; ++i) {
        elems[i] = buf.cstr("&&").str(opts->label_prefix).u32(go->table[i]->label->index).flush();
    }

    opts->eval_code_conf(buf.stream(), "code:type_yytarget");
    const char* type = buf.flush();

    CodeList* stmts = code_list(alc);
    append(stmts, code_array(alc, opts->var_cgoto_table.c_str(),
            type, elems, CodeGoCpTable::TABLE_SIZE, /*tabulate*/ true));
    return stmts;
}

static CodeList* gen_gocp(Output& output, const Adfa& dfa, const CodeGoCp* go, const State* from) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;
    const char* text;

    CodeList* stmts = code_list(alc);

    CodeList* if_else = gen_gocp_table(output, go->table);
    text = o.cstr("goto *").str(opts->var_cgoto_table).cstr("[").str(opts->var_char).cstr("]")
            .flush();
    append(if_else, code_stmt(alc, text));

    if (go->hgo != nullptr) {
        text = o.str(opts->var_char).cstr(" & ~0xFF").flush();
        CodeList* if_then = gen_goswif(output, dfa, go->hgo, from);
        append(stmts, code_if_then_else(alc, text, if_then, if_else, false));
    } else {
        append(stmts, code_block(alc, if_else, CodeBlock::Kind::WRAPPED));
    }

    return stmts;
}

static void gen_godot(
        Output& output, const Adfa& dfa, const CodeGoSw* go, const State* from, CodeList* stmts) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;
    const std::string& prefix = opts->tags_prefix;
    const uint32_t n = go->ncases;
    const char* text;

    if (n == 1) {
        text = o.label(*from->label).cstr(" -> ").label(*go->cases[0].jump.to->label).flush();
        append(stmts, code_text(alc, text));
    } else {
        for (const CodeGoCase* c = go->cases, *e = c + go->ncases; c < e; ++c) {
            o.label(*from->label).cstr(" -> ").label(*c->jump.to->label).cstr(" [label=\"");

            const Enc& enc = opts->encoding;
            const int64_t* ranges = c->ranges->elems;
            for (uint32_t i = 0; i < c->ranges->size; ++i) {
                print_span(o.stream(),
                           static_cast<uint32_t>(ranges[2 * i]),
                           static_cast<uint32_t>(ranges[2 * i + 1]),
                           enc.cunit_size(),
                           enc.type() == Enc::Type::EBCDIC,
                           true);
            }

            const tcmd_t* cmd = dfa.tcpool[c->jump.tags];
            for (const tcmd_t* p = cmd; p; p = p->next) {
                o.cstr("<").str(vartag_name(p->lhs, prefix, dfa.mtagvers));
                if (tcmd_t::iscopy(p)) {
                    o.cstr("~").str(vartag_name(p->rhs, prefix, dfa.mtagvers));
                }
                o.cstr(">");
            }

            text = o.cstr("\"]").flush();
            append(stmts, code_text(alc, text));
        }
    }
}

static void gen_go(Output& output, const Adfa& dfa, const CodeGo* go, const State* from, CodeList* stmts) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;

    if (go->kind == CodeGo::Kind::DOT) {
        gen_godot(output, dfa, go->godot, from, stmts);
        return;
    }

    DCHECK(consume(from) || go->tags == TCID0);
    if (opts->fill_eof == NOEOF) {
        // With the end-of-input rule $ tag operations *must* be generated before YYFILL label.
        // Without the $ rule the are no strict requirements, but generating them here (after YYFILL
        // label) allows to fuse skip and peek into one statement.
        gen_settags(output, stmts, dfa, go->tags);
    }

    if (go->skip) {
        append(stmts, code_skip(alc));
    }

    if (go->kind == CodeGo::Kind::SWITCH_IF) {
        append(stmts, gen_goswif(output, dfa, go->goswif, from));
    } else if (go->kind == CodeGo::Kind::BITMAP) {
        append(stmts, gen_gobm(output, dfa, go->gobm, from));
    } else if (go->kind == CodeGo::Kind::CPGOTO) {
        append(stmts, gen_gocp(output, dfa, go->gocp, from));
    }
}

static CodeList* emit_accept_binary(Output& output,
                                    const Adfa& dfa,
                                    const uniq_vector_t<AcceptTrans>& acc,
                                    size_t l,
                                    size_t r) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;

    CodeList* stmts = code_list(alc);
    if (l < r) {
        const size_t m = (l + r) >> 1;
        const char* if_cond = o.str(opts->var_accept).cstr(r == l + 1 ? " == " : " <= ").u64(m)
                .flush();
        CodeList* if_then = emit_accept_binary(output, dfa, acc, l, m);
        CodeList* if_else = emit_accept_binary(output, dfa, acc, m + 1, r);
        append(stmts, code_if_then_else(alc, if_cond, if_then, if_else));
    } else {
        const CodeJump jump = {acc[l].state, acc[l].tags, false, false, false};
        gen_goto(output, dfa, stmts, nullptr, jump);
    }
    return stmts;
}

static void gen_restore(Output& output, CodeList* stmts) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;
    const char* text;

    if (opts->api == Api::DEFAULT) {
        text = o.str(opts->api_cursor).cstr(" = ").str(opts->api_marker).flush();
        append(stmts, code_stmt(alc, text));
    } else if (opts->api_style == ApiStyle::FUNCTIONS) {
        text = o.str(opts->api_restore).cstr("()").flush();
        append(stmts, code_stmt(alc, text));
    } else {
        text = o.str(opts->api_restore).flush();
        append(stmts, code_text(alc, text));
    }
}

static void emit_accept(
        Output& output, CodeList* stmts, const Adfa& dfa, const uniq_vector_t<AcceptTrans>& acc) {
    const opt_t* opts = output.block().opts;
    const size_t nacc = acc.size();
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;
    const char* text;

    if (nacc == 0) return;

    gen_restore(output, stmts);

    // only one possible 'yyaccept' value: unconditional jump
    if (nacc == 1) {
        const CodeJump jump = {acc[0].state, acc[0].tags, false, false, false};
        gen_goto(output, dfa, stmts, nullptr, jump);
        return;
    }

    bool have_tags = acc.end() != std::find_if(
            acc.begin(), acc.end(), [](const AcceptTrans& a) { return a.tags != TCID0; });

    // jump table
    if (opts->cgoto && nacc >= opts->cgoto_threshold && !have_tags) {
        CodeList* block = code_list(alc);

        const char** elems = alc.alloct<const char*>(nacc);
        for (uint32_t i = 0; i < nacc; ++i) {
            elems[i] = o.cstr("&&").str(opts->label_prefix).u32(acc[i].state->label->index).flush();
        }
        opts->eval_code_conf(o.stream(), "code:type_yytarget");
        const char* type = o.flush();
        append(block, code_array(alc, opts->var_cgoto_table.c_str(), type, elems, nacc));

        text = o.cstr("goto *").str(opts->var_cgoto_table).cstr("[").str(opts->var_accept).cstr("]")
                .flush();
        append(block, code_stmt(alc, text));

        append(stmts, code_block(alc, block, CodeBlock::Kind::WRAPPED));
        return;
    }

    // nested ifs
    if (opts->nested_ifs || nacc == 2) {
        append(stmts, emit_accept_binary(output, dfa, acc, 0, nacc - 1));
        return;
    }

    // switch
    CodeCases* cases = code_cases(alc);
    for (uint32_t i = 0; i < nacc; ++i) {
        CodeList* case_body = code_list(alc);
        const CodeJump jump = {acc[i].state, acc[i].tags, false, false, false};
        gen_goto(output, dfa, case_body, nullptr, jump);
        if (i == nacc - 1) {
            append(cases, code_case_default(alc, case_body));
        } else {
            append(cases, code_case_number(alc, case_body, static_cast<int32_t>(i)));
        }
    }
    text = o.str(opts->var_accept).flush();
    append(stmts, code_switch(alc, text, cases));
}

static void gen_yydebug(Output& output, const Label* label, CodeList* stmts) {
    if (output.block().opts->debug) {
        // The label may be unused but still have a valid index (one such example is the initial label
        // in goto/label mode). It still needs an YYDEBUG statement.
        append(stmts, code_debug(output.allocator, label));
    }
}

class GenEnumElem : public RenderCallback {
    std::ostream& os;
    const std::string& type;
    const std::string& name;

  public:
    GenEnumElem(std::ostream& os, const std::string& type, const std::string& name)
        : os(os), type(type), name(name) {}

    void render_var(const char* var) override {
        if (strcmp(var, "type") == 0) {
            os << type;
        } else if (strcmp(var, "name") == 0) {
            os << name;
        } else {
            UNREACHABLE();
        }
    }

    FORBID_COPY(GenEnumElem);
};

const char* gen_cond_enum_elem(Scratchbuf& buf, const opt_t* opts, const std::string& name) {
    const std::string& cond = opts->cond_enum_prefix + name;
    GenEnumElem callback(buf.stream(), opts->api_cond_type, cond);
    opts->eval_code_conf(buf.stream(), "code:enum_elem", callback);
    return buf.flush();
}

static void emit_rule(Output& output, CodeList* stmts, const Adfa& dfa, size_t rule_idx) {
    const opt_t* opts = output.block().opts;
    const Rule& rule = dfa.rules[rule_idx];
    const SemAct* semact = rule.semact;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;

    gen_fintags(output, stmts, dfa, rule);

    if (opts->target == Target::SKELETON) {
        emit_skeleton_action(output, stmts, dfa, rule_idx);
        return;
    }

    // Condition in the semantic action is the one set with => or :=> rule.
    const char* cond = semact->cond == nullptr ? dfa.cond.c_str() : semact->cond;
    // Next condition is either the one specified in semantic action, or the current one.
    const char* next_cond = gen_cond_enum_elem(o, opts, cond);
    // Next state is normally -1 (the initial storable state corresponding to no YYFILL invocation),
    // but in the loop/switch mode conditions and storable states are both implemented via
    // `yystate`, so the next state is the next condition.
    const char* next_state = (!dfa.cond.empty() && opts->loop_switch) ? next_cond : "-1";

    if (opts->storable_state) {
        // Generate YYSETSTATE in the final state. This is needed because the user may enclose the
        // lexer in an outer loop that goes via YYGETSTATE switch (it may happen if `getstate:re2c`
        // is not used, which is the case in the loop/switch mode). The user would expect the next
        // iteration of the loop to start in the initial DFA state, so YYGETSTATE should return the
        // corresponding value.
        gen_state_set(output, stmts, next_state);
    }

    if (cond != dfa.cond && !(opts->loop_switch && opts->storable_state)) {
        // Omit YYSETCONDITION if the current condition is the same as the new one. Also omit it if
        // both storable state and conditions are used with loop/switch: only one of YYGETSTATE and
        // YYGETCONDITION can be used to initialize `yystate`, and it must be YYGETSTATE because the
        // lexer may be reentered after an YYFILL invocation. Therefore we use YYSETSTATE instead of
        // YYSETCONDITION in the final states in order to match YYGETSTATE in `yystate`
        // initialization.
        gen_cond_set(output, stmts, next_cond);
    }

    if (!semact->autogen) {
        // User-defined semantic action.
        if (!dfa.setup.empty()) append(stmts, code_text(alc, o.str(dfa.setup).flush()));
        if (opts->line_dirs) append(stmts, code_line_info_input(alc, semact->loc));
        append(stmts, code_text(alc, o.cstr(semact->text).flush()));
        if (opts->line_dirs) append(stmts, code_line_info_output(alc));
    } else if (opts->loop_switch) {
        // Autogenerated action for the :=> rule, loop/switch mode: set `yystate` to the initial
        // state of the next condition and continue to the head of the loop.
        gen_continue_yyloop(output, stmts, next_cond);
    } else {
        // Autogenerated action for the :=> rule, goto/label mode: emit `cond:goto` configuration
        // with `cond:goto@cond` replaced by the next condition label.
        o.str(opts->cond_goto);
        argsubst(o.stream(), opts->cond_goto_param, "cond", true, opts->cond_label_prefix + cond);
        append(stmts, code_text(alc, o.flush()));
    }
}

static void emit_action(Output& output, const Adfa& dfa, const State* s, CodeList* stmts) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;
    const char* text;

    switch (s->action.kind) {
    case Action::Kind::MATCH:
        if (!opts->eager_skip) {
            append(stmts, code_skip(alc));
        }
        gen_fill_and_label(output, stmts, dfa, s);
        gen_peek(alc, s, stmts);
        break;
    case Action::Kind::INITIAL: {
        const size_t save = s->action.info.save;
        const bool backup = save != NOSAVE;
        const bool ul1 = s->label->used;

        if (ul1 && dfa.accepts.size() > 1 && backup) {
            text = o.str(opts->var_accept).cstr(" = ").u64(save).flush();
            append(stmts, code_stmt(alc, text));
        }
        if (ul1 && !opts->eager_skip) {
            append(stmts, code_skip(alc));
        }
        append(stmts, code_nlabel(alc, dfa.initial_label));
        gen_yydebug(output, dfa.initial_label, stmts);
        gen_fill_and_label(output, stmts, dfa, s);
        if (backup) {
            append(stmts, code_backup(alc));
        }
        gen_peek(alc, s, stmts);
        break;
    }
    case Action::Kind::SAVE:
        if (dfa.accepts.size() > 1) {
            text = o.str(opts->var_accept).cstr(" = ").u64(s->action.info.save).flush();
            append(stmts, code_stmt(alc, text));
        }
        if (!opts->eager_skip) {
            append(stmts, code_skip(alc));
        }
        append(stmts, code_backup(alc));
        gen_fill_and_label(output, stmts, dfa, s);
        gen_peek(alc, s, stmts);
        break;
    case Action::Kind::MOVE:
        break;
    case Action::Kind::ACCEPT:
        emit_accept(output, stmts, dfa, *s->action.info.accepts);
        break;
    case Action::Kind::RULE:
        emit_rule(output, stmts, dfa, s->action.info.rule);
        break;
    }
}

static void emit_state(Output& output, const State* state, CodeList* stmts) {
    // If state label is unused, we should not generate it.
    // Nor can we emit an YYDEBUG statement, as there is no state number to pass to it.
    if (!state->label->used) return;

    if (!output.block().opts->loop_switch) {
        append(stmts, code_nlabel(output.allocator, state->label));
    }
    if (state->action.kind != Action::Kind::INITIAL) {
        gen_yydebug(output, state->label, stmts);
    }
}

static void gen_storable_state_cases(Output& output, CodeCases* cases) {
    OutputBlock& block = output.block();
    const opt_t* opts = block.opts;
    OutAllocator& alc = output.allocator;

    if (!opts->storable_state || !opts->loop_switch) return;

    // TODO: If `re2c:eof` is not used, some of these cases are redundant (they contain a single
    // transition to the DFA state that has the corresponding YYFILL invocation).
    for (const auto& i : block.fill_goto) {
        append(cases, code_case_number(alc, i.second, static_cast<int32_t>(i.first)));
    }

    // Prepare a single range [-1, 1) covering cases `yystate = -1` and `yystate = 0`.
    int64_t* ranges = alc.alloct<int64_t>(2), *ranges_end = ranges;
    *ranges_end++ = -1;
    *ranges_end++ = 1;

    // Replace the first case 0 with a case that covers both -1 and 0.
    CodeCase* first = cases->head;
    DCHECK(first->kind == CodeCase::Kind::NUMBER && first->number == 0);
    first->kind = CodeCase::Kind::RANGES;
    first->ranges = code_ranges(alc, VarType::INT, ranges, ranges_end);
}

void gen_dfa_as_blocks_with_labels(Output& output, const Adfa& dfa, CodeList* stmts) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;

    // If DFA has transitions into the initial state and --eager-skip option is not used, then the
    // initial state must have a YYSKIP statement that must be bypassed when first entering the DFA.
    // With --loop-switch that would be impossible, because there can be no transitions in the
    // middle of a state.
    DCHECK(!opts->loop_switch);
    if (dfa.initial_label->used) {
        buf.cstr("goto ").str(opts->label_prefix).label(*dfa.initial_label);
        append(stmts, code_stmt(alc, buf.flush()));
    }

    for (State* s = dfa.head; s; s = s->next) {
        emit_state(output, s, stmts);
        emit_action(output, dfa, s, stmts);
        gen_go(output, dfa, &s->go, s, stmts);
    }
}

void gen_dfa_as_switch_cases(Output& output, Adfa& dfa, CodeCases* cases) {
    OutAllocator& alc = output.allocator;

    DCHECK(output.block().opts->loop_switch);

    for (State* s = dfa.head; s; s = s->next) {
        CodeList* body = code_list(alc);

        // Emit current state.
        emit_state(output, s, body);
        emit_action(output, dfa, s, body);
        gen_go(output, dfa, &s->go, s, body);
        uint32_t label = s->label->index;
        DCHECK(label != Label::NONE);

        // As long as the following state has no incoming transitions (its label is unused),
        // generate it as a continuation of the current state. This avoids looping through the
        // `yystate` switch only to return to the next case.
        while (s->next && !s->next->label->used) {
            s = s->next;
            emit_state(output, s, body);
            emit_action(output, dfa, s, body);
            gen_go(output, dfa, &s->go, s, body);
        }

        append(cases, code_case_number(alc, body, static_cast<int32_t>(label)));
    }
}

void wrap_dfas_in_loop_switch(Output& output, CodeList* stmts, CodeCases* cases) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;

    DCHECK(opts->loop_switch);

    CodeList* loop = code_list(alc);
    gen_storable_state_cases(output, cases);
    if (opts->state_abort || opts->eval_bool_conf("abort_in_default_case")) {
        CodeList* abort = code_list(alc);
        append(abort, code_abort(alc));
        append(cases, code_case_default(alc, abort));
    }
    append(loop, code_switch(alc, opts->var_state.c_str(), cases));
    append(stmts, code_loop(alc, loop));
}

static std::string output_state_get(const opt_t* opts) {
    return opts->api_state_get + (opts->state_get_naked ? "" : "()");
}

static OutputBlock* find_block_with_name(Output& output, const char* name) {
    for (OutputBlock* b : output.cblocks) {
        if (b->name.compare(name) == 0) return b;
    }
    for (OutputBlock* b : output.hblocks) {
        if (b->name.compare(name) == 0) return b;
    }
    return nullptr;
}

static Ret find_blocks(
        Output& output, const BlockNameList* names, blocks_t& blocks, const char* directive) {
    blocks.clear();
    for (const BlockNameList* p = names; p; p = p->next) {
        OutputBlock* b = find_block_with_name(output, p->name);
        if (b) {
            blocks.push_back(b);
        } else {
            RET_FAIL(error("cannot find block '%s' listed in `%s` directive", p->name, directive));
        }
    }
    return Ret::OK;
}

static void gen_state_goto_cases(Output& output, CodeCases* cases, const OutputBlock* block) {
    OutAllocator& alc = output.allocator;
    for (const auto& i : block->fill_goto) {
        append(cases, code_case_number(alc, i.second, static_cast<int32_t>(i.first)));
    }
}

LOCAL_NODISCARD(Ret gen_state_goto(Output& output, Code* code)) {
    OutputBlock& block = output.block();
    // If this is a `use:re2c` block, this must be an autogenerated block-local state switch, so use
    // block-local options. Otherwise use global options accumulated across the whole file, as the
    // state switch may include states from a few different blocks and it is not clear which options
    // it should inherit.
    const opt_t* globopts = block.kind == InputBlock::USE ? block.opts : output.total_opts;

    if (globopts->target != Target::CODE) {
        code->kind = CodeKind::EMPTY;
        return Ret::OK;
    }

    // Loop/switch approach is handled differently (by appending special cases to the state switch).
    DCHECK(!globopts->loop_switch);

    Scratchbuf& o = output.scratchbuf;
    OutAllocator& alc = output.allocator;
    const char* text;

    // There are two possibilities:
    //
    // 1. A state switch with an explicit list of block names. This is the case of a user-defined
    //    `getstate:re2c:<name1>[:<name2>...]` directive or a `use:re2c` block (use blocks have a
    //    block-local state switch that is automatically generated at the beginning of the block,
    //    and they have a special autogenerated name, as they cannot have a user-defined one).
    //
    // 2. A global state switch without a list of block names. This is the case of a user-defined
    //    `getstate:re2c` without a name list, or a global state switch that is generated
    //    automatically if the user did not specify any explicit `getstate:re2c` directives. The
    //    global switch includes all blocks except `use:re2c` (if a block generates no code it does
    //    not contribute any cases to the state switch).
    //
    bool global = (code->fmt.block_names == nullptr);

    CodeCases* cases = code_cases(alc);
    const OutputBlock* bstart = nullptr;

    if (global) {
        // No block names are specified: generate a global switch. It includes all blocks except for
        // the `re2c:use` ones which have a local switch.
        for (const OutputBlock* b : *output.pblocks) {
            if (b->kind != InputBlock::USE) {
                gen_state_goto_cases(output, cases, b);

                // Use start label of the first non-use block that generates code.
                if (!bstart && b->start_label) bstart = b;
            }
        }
        if (!bstart || !bstart->start_label) {
            // This must be a user-defined directive: the automatic state switch is generated only
            // when processing the first block that has code.
            RET_FAIL(error("none of the blocks in `getstate:re2c` generate any code"));
        }
    } else {
        // Generate a switch for all specified named blocks.
        CHECK_RET(find_blocks(output, code->fmt.block_names, output.tmpblocks, "getstate:re2c"));
        for (const OutputBlock* b : output.tmpblocks) {
            if (!b->start_label) {
                RET_FAIL(error("block '%s' does not generate code, so it should not be listed in "
                               "`getstate:re2c` directive",
                               b->name.c_str()));
            }
            // Use start label of the first block on the list.
            if (!bstart) bstart = b;
            gen_state_goto_cases(output, cases, b);
        }
    }

    // This is the use that makes 2nd codegen pass for labels necessary.
    Label* lstart = bstart->start_label;
    lstart->used = true;

    CodeList* goto_start = code_list(alc);
    text = o.cstr("goto ").str(bstart->opts->label_prefix).u32(lstart->index).flush();
    append(goto_start, code_stmt(alc, text));

    if (globopts->state_abort) {
        // case -1: goto <start label>;
        prepend(cases, code_case_number(alc, goto_start, -1));

        // default: abort
        CodeList* abort = code_list(alc);
        append(abort, code_abort(alc));
        prepend(cases, code_case_default(alc, abort));
    } else {
        // default: goto <start label>;
        prepend(cases, code_case_default(alc, goto_start));
    }

    CodeList* stmts = code_list(alc);
    text = o.str(output_state_get(globopts)).flush();
    append(stmts, code_switch(alc, text, cases));

    if (globopts->state_next) {
        text = o.str(globopts->label_next).cstr(":").flush();
        append(stmts, code_textraw(alc, text));
    }

    code->kind = CodeKind::BLOCK;
    code->block.kind = CodeBlock::Kind::RAW;
    code->block.stmts = stmts;
    return Ret::OK;
}

void gen_tags(Scratchbuf& buf, const opt_t* opts, Code* code, const tagnames_t& tags) {
    DCHECK(code->kind == CodeKind::STAGS || code->kind == CodeKind::MTAGS);

    const char* fmt = code->fmt.format;
    const char* sep = code->fmt.separator;
    bool first = true;
    for (const std::string& tag : tags) {
        if (first) {
            first = false;
        } else if (sep != nullptr) {
            buf.cstr(sep);
        }
        if (fmt != nullptr) {
            std::ostringstream s(fmt);
            argsubst(s, opts->api_sigil, "tag", true, tag);
            buf.str(s.str());
        }
    }
    if (opts->line_dirs) {
        const std::string& s = buf.stream().str();
        if (!s.empty() && *s.rbegin() != '\n') buf.cstr("\n");
    }

    code->kind = CodeKind::RAW;
    code->raw.size = buf.stream().str().length();
    code->raw.data = buf.flush();
}

static void add_tags_from_blocks(const blocks_t& blocks, tagnames_t& tags, bool multival) {
    for (OutputBlock* b : blocks) {
        if (multival) {
            tags.insert(b->mtags.begin(), b->mtags.end());
        } else {
            tags.insert(b->stags.begin(), b->stags.end());
        }
    }
}

LOCAL_NODISCARD(Ret expand_tags_directive(Output& output, Code* code)) {
    DCHECK(code->kind == CodeKind::STAGS || code->kind == CodeKind::MTAGS);

    OutputBlock& block = output.block();
    Scratchbuf& buf = output.scratchbuf;
    const opt_t* opts = block.opts;

    if (opts->target != Target::CODE) {
        code->kind = CodeKind::EMPTY;
        return Ret::OK;
    }

    bool multival = (code->kind == CodeKind::MTAGS);

    tagnames_t tags;
    if (code->fmt.block_names == nullptr) {
        // Gather tags from all blocks in the output and header files.
        add_tags_from_blocks(output.cblocks, tags, multival);
        add_tags_from_blocks(output.hblocks, tags, multival);
    } else {
        // Gather tags from the blocks on the list.
        const char* directive = multival ? "mtags:re2c" : "stags:re2c";
        CHECK_RET(find_blocks(output, code->fmt.block_names, output.tmpblocks, directive));
        add_tags_from_blocks(output.tmpblocks, tags, multival);
    }
    gen_tags(buf, opts, code, tags);
    return Ret::OK;
}

static void gen_cond_enum(
        Scratchbuf& buf,
        OutAllocator& alc,
        Code* code,
        const opt_t* opts,
        const StartConds& conds) {
    DCHECK(opts->target == Target::CODE);

    if (conds.empty()) return;
    const StartCond* first_cond = &conds.front();

    if (code->fmt.format) {
        const char* fmt = code->fmt.format;
        const char* sep = code->fmt.separator;
        uint32_t cond_number = 0;
        for (const StartCond& cond : conds) {
            if (sep != nullptr && &cond != first_cond) {
                buf.cstr(sep);
            }
            std::ostringstream s(fmt);
            // The main substitution (the one allowing unnamed sigil) must go last, or else it will
            // erroneously substitute all the named ones.
            size_t cid = opts->loop_switch ? cond.number : cond_number;
            argsubst(s, opts->api_sigil, "num", false, cid);
            argsubst(s, opts->api_sigil, "cond", true, cond.name);
            buf.str(s.str());
            ++cond_number;
        }
        buf.cstr("\n");

        code->kind = CodeKind::RAW;
        code->raw.size = buf.stream().str().length();
        code->raw.data = buf.flush();
    } else {
        // prepare an array of enum member names
        const char** ids = alc.alloct<const char*>(conds.size()), **i = ids;
        for (const StartCond& cond : conds) *i++ = buf.str(cond.name).flush();
        // prepare an array of enum member numbers (only needed in loop/switch mode)
        uint32_t* nums = nullptr;
        if (opts->loop_switch) {
            uint32_t* j = nums = alc.alloct<uint32_t>(conds.size());
            for (const StartCond& cond : conds) *j++ = cond.number;
        }
        // construct enum code item in place of the old code item
        init_code_enum(code, opts->api_cond_type.c_str(), conds.size(), ids, nums);
    }
}

LOCAL_NODISCARD(Ret add_condition_from_block(
        const OutputBlock& block, StartConds& conds, StartCond cond)) {
    // Condition prefix is specific to the block that defines it. If a few blocks define conditions
    // with the same name, but a different prefix, they should have different enum entries.
    cond.name = block.opts->cond_enum_prefix + cond.name;

    for (const StartCond& c : conds) {
        if (c.name == cond.name) {
            if (c.number == cond.number) {
                // A duplicate condition, it's not an error but don't add it.
                return Ret::OK;
            } else {
                // An error: conditions with idetical names but different numbers.
                RET_FAIL(error("cannot generate condition enumeration: conditon '%s' has "
                               "different numbers in different blocks (use `re2c:condenumprefix` "
                               "configuration to set per-block prefix)",
                               cond.name.c_str()));
            }
        }
    }

    conds.push_back(cond);
    return Ret::OK;
}

LOCAL_NODISCARD(Ret add_conditions_from_blocks(const blocks_t& blocks, StartConds& conds)) {
    for (const OutputBlock* block : blocks) {
        for (const StartCond& cond : block->conds) {
            CHECK_RET(add_condition_from_block(*block, conds, cond));
        }
    }
    return Ret::OK;
}

LOCAL_NODISCARD(Ret expand_cond_enum(Output& output, Code* code)) {
    Scratchbuf& buf = output.scratchbuf;
    OutAllocator& alc = output.allocator;

    // Use global options accumulated across the whole file, as `types:re2c` may include conditions
    // from a few different blocks, and it is not clear which block's options it should inherit.
    const opt_t* globopts = output.total_opts;

    if (globopts->target != Target::CODE) {
        code->kind = CodeKind::EMPTY;
        return Ret::OK;
    }

    StartConds conds;
    if (code->fmt.block_names == nullptr) {
        // Gather conditions from all blocks in the output and header files.
        CHECK_RET(add_conditions_from_blocks(output.cblocks, conds));
        CHECK_RET(add_conditions_from_blocks(output.hblocks, conds));
    } else {
        // Gather conditions from the blocks on the list.
        CHECK_RET(find_blocks(output, code->fmt.block_names, output.tmpblocks, "types:re2c"));
        CHECK_RET(add_conditions_from_blocks(output.tmpblocks, conds));
    }

    // Do not generate empty condition enum. Some compilers or language standards allow it, but
    // generally it's more likely to indicate an error in user code.
    if (conds.empty()) {
        code->kind = CodeKind::EMPTY;
        return Ret::OK;
    }

    gen_cond_enum(buf, alc, code, globopts, conds);
    return Ret::OK;
}

static std::string output_cond_get(const opt_t* opts) {
    return opts->api_cond_get + (opts->cond_get_naked ? "" : "()");
}

// note [condition order]
//
// In theory re2c makes no guarantee about the order of conditions in the generated lexer. Users
// should define condition type YYCONDTYPE and use values of this type with YYGETCONDITION and
// YYSETCONDITION. This way code is independent of internal re2c condition numbering.
//
// However, it is possible to manually hardcode condition numbers and make re2c generate condition
// dispatch without explicit use of condition names (nested `if` statements with `-b` or computed
// `goto` table with `-g`). This code is syntactically valid (compiles), but unsafe:
//     - change of re2c options may break compilation
//     - change of internal re2c condition numbering may break runtime
//
// re2c has to preserve the existing numbering scheme.
//
// re2c warns about implicit assumptions about condition order, unless:
//     - condition type is defined with 'types:re2c' or '-t, --type-header'
//     - dispatch is independent of condition order: either it uses explicit condition names or
//       there's only one condition and dispatch shrinks to unconditional jump

static CodeList* gen_cond_goto_binary(Output& output, size_t lower, size_t upper) {
    OutputBlock& block = output.block();
    const opt_t* opts = block.opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;

    CodeList* stmts = code_list(alc);
    if (lower == upper) {
        buf.cstr("goto ").str(opts->cond_label_prefix).str(block.conds[lower].name);
        append(stmts, code_stmt(alc, buf.flush()));
    } else {
        const size_t middle = lower + (upper - lower + 1) / 2;
        CodeList* if_then = gen_cond_goto_binary(output, lower, middle - 1);
        CodeList* if_else = gen_cond_goto_binary(output, middle, upper);
        buf.str(output_cond_get(opts)).cstr(" < ").u64(middle);
        append(stmts, code_if_then_else(alc, buf.flush(), if_then, if_else));
    }
    return stmts;
}

static CodeList* gen_cond_goto(Output& output) {
    OutputBlock& block = output.block();
    const opt_t* opts = block.opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;
    const StartConds& conds = block.conds;
    bool warn_cond_ord = output.warn_condition_order;

    DCHECK(!opts->loop_switch);

    const size_t ncond = conds.size();
    CodeList* stmts = code_list(alc);
    const char* text;

    if (opts->target == Target::DOT) {
        for (const StartCond& cond : conds) {
            text = buf.cstr("0 -> ").str(cond.name).cstr(" [label=\"state=").str(cond.name)
                    .cstr("\"]").flush();
            append(stmts, code_text(alc, text));
        }
    } else {
        if (opts->cgoto) {
            text = buf.cstr("goto *").str(opts->var_cond_table).cstr("[")
                    .str(output_cond_get(opts)).cstr("]").flush();
            append(stmts, code_stmt(alc, text));
        } else if (opts->nested_ifs) {
            warn_cond_ord &= ncond > 1;
            append(stmts, gen_cond_goto_binary(output, 0, ncond - 1));
        } else {
            warn_cond_ord = false;

            CodeCases* ccases = code_cases(alc);
            for (const StartCond& cond : conds) {
                CodeList* body = code_list(alc);
                text = buf.cstr("goto ").str(opts->cond_label_prefix).str(cond.name).flush();
                append(body, code_stmt(alc, text));

                text = gen_cond_enum_elem(buf, opts, cond.name);
                append(ccases, code_case_string(alc, body, text));
            }
            if (opts->eval_bool_conf("abort_in_default_case")) {
                CodeList* abort = code_list(alc);
                append(abort, code_abort(alc));
                append(ccases, code_case_default(alc, abort));
            }
            text = buf.str(output_cond_get(opts)).flush();
            append(stmts, code_switch(alc, text, ccases));
        }

        // see note [condition order]
        warn_cond_ord &= opts->header_file.empty();
        if (warn_cond_ord) {
            output.msg.warn.condition_order(block.loc);
        }
    }

    return stmts;
}

static CodeList* gen_cond_table(Output& output) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;
    const StartConds& conds = output.block().conds;

    CodeList* code = code_list(alc);
    const char** elems = alc.alloct<const char*>(conds.size());
    for (size_t i = 0; i < conds.size(); ++i) {
        elems[i] = buf.cstr("&&").str(opts->cond_label_prefix).str(conds[i].name).flush();
    }
    opts->eval_code_conf(buf.stream(), "code:type_yytarget");
    const char* type = buf.flush();
    append(code, code_array(alc, opts->var_cond_table.c_str(), type, elems, conds.size()));
    return code;
}

static Code* gen_yystate_def(Output& output) {
    Scratchbuf& buf = output.scratchbuf;
    const opt_t* opts = output.block().opts;

    CHECK(opts->loop_switch);

    VarType type;
    const char* init;
    if (opts->storable_state) {
        // With storable state `yystate` should be initialized to YYGETSTATE. Since there is a
        // -1 case, `yystate` should have a signed type. If conditions are also used, YYGETSTATE
        // takes priority over YYGETCONDITION, because the lexer may be reentered after an YYFILL
        // invocation. In that case we use YYSETSTATE instead of YYSETCONDITION in the final states.
        type = VarType::INT;
        init = buf.str(output_state_get(opts)).flush();
    } else if (opts->start_conditions) {
        // Else with start conditions yystate should be initialized to YYGETCONDITION.
        type = VarType::UINT;
        init = buf.str(output_cond_get(opts)).flush();
    } else {
        // Else it should be the start DFA state (always case 0 with --loop-switch).
        type = VarType::UINT;
        init = "0";
    }
    return code_var(output.allocator, type, opts->var_state.c_str(), init);
}

static size_t max_among_blocks(const blocks_t& blocks, size_t max, CodeKind kind) {
    for (const OutputBlock* b : blocks) {
        max = std::max(max, kind == CodeKind::MAXFILL ? b->max_fill : b->max_nmatch);
    }
    return max;
}

LOCAL_NODISCARD(Ret gen_yymax(Output& output, Code* code)) {
    const opt_t* opts = output.block().opts;
    Scratchbuf& buf = output.scratchbuf;

    if (opts->target != Target::CODE) {
        code->kind = CodeKind::EMPTY;
        return Ret::OK;
    }

    CodeKind kind = code->kind;
    const char* dirname = kind == CodeKind::MAXFILL ? "max:re2c" : "maxnmatch:re2c";
    const char* varname = kind == CodeKind::MAXFILL ? "YYMAXFILL" : "YYMAXNMATCH";

    size_t max = 1;
    if (code->fmt.block_names == nullptr) {
        // Gather max value from all blocks in the output and header files.
        max = max_among_blocks(output.cblocks, max, kind);
        max = max_among_blocks(output.hblocks, max, kind);
    } else {
        // Maximum among the blocks listed in the directive.
        CHECK_RET(find_blocks(output, code->fmt.block_names, output.tmpblocks, dirname));
        max = max_among_blocks(output.tmpblocks, max, kind);
    }

    if (code->fmt.format) {
        buf.cstr(code->fmt.format);
        argsubst(buf.stream(), opts->api_sigil, "max", true, max);
        code->text = buf.flush();
        code->kind = CodeKind::TEXT;
    } else {
        init_code_const(code, VarType::UINT, varname, buf.u64(max).flush());
    }
    return Ret::OK;
}

std::string bitmap_name(const opt_t* opts, const std::string& cond) {
    return cond.empty()
            ? opts->var_bitmaps
            : opts->var_bitmaps + "_" + cond;
}

CodeList* gen_bitmap(Output& output, const CodeBitmap* bitmap, const std::string& cond) {
    if (!bitmap->states->head || !bitmap->used) return nullptr;

    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;

    static constexpr uint32_t WIDTH = 8;
    const uint32_t nchars = bitmap->nchars;
    uint32_t nmaps = 0;
    for (CodeBmState* b = bitmap->states->head; b; b = b->next) ++nmaps;

    uint32_t nelems = nchars * ((nmaps + WIDTH - 1) / WIDTH);
    const char** elems = alc.alloct<const char*>(nelems);
    uint32_t* tmpbuf = alc.alloct<uint32_t>(nelems); // temporary buffer for bitmap generation

    // Generate bitmaps in a temporary buffer and store them as table elements.
    uint32_t bmidx = 0;
    for (CodeBmState* b = bitmap->states->head; b; ++bmidx) {
        const uint32_t offset = bmidx * nchars;

        // For each state generate a table with one bit per character, denoting if there is a
        // transition on this charater to the destination state. Tables for up to 8 states are
        // overlayed and compressed in one bitmap.
        memset(tmpbuf, 0, nchars * sizeof(uint32_t));
        for (uint32_t mask = 0x80; mask && b; mask >>= 1, b = b->next) {
            b->offset = offset;
            b->mask = mask;

            uint32_t c = 0;
            const Span* span = b->go->span, *last = span + b->go->span_count;
            for (; span < last; ++span) {
                if (span->to == b->state) {
                    for (uint32_t u = std::min(span->ub, nchars); c < u; ++c) {
                        tmpbuf[c] |= mask;
                    }
                }
                c = span->ub;
            }
        }

        for (uint32_t i = 0; i < nchars; ++i) {
            if (opts->bitmaps_hex) {
                print_hex(buf.stream(), tmpbuf[i], opts->encoding.cunit_size());
            } else {
                buf.u32(tmpbuf[i]);
            }
            elems[bmidx * nchars + i] = buf.flush();
        }
    }

    const char *name = buf.str(bitmap_name(opts, cond)).flush();

    opts->eval_code_conf(buf.stream(), "code:type_yybm");
    const char* type = buf.flush();

    CodeList* stmts = code_list(alc);
    append(stmts, code_array(alc, name, type, elems, nelems, /*tabulate*/ true));
    return stmts;
}

LOCAL_NODISCARD(Ret gen_block_code(Output& output, const Adfas& dfas, CodeList* program)) {
    OutputBlock& oblock = output.block();
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;
    const opt_t* opts = oblock.opts;

    // All conditions are named, so it suffices to check the first DFA.
    DCHECK(!dfas.empty());
    const bool is_cond_block = !dfas.front()->cond.empty();

    append(program, code_newline(alc)); // the following #line info must start at zero indent
    if (opts->line_dirs) append(program, code_line_info_output(alc));

    CodeList* code = code_list(alc);
    bool local_decls = false;

    if (!opts->storable_state && opts->char_emit) {
        local_decls = true;
        append(code, code_var(alc, VarType::YYCTYPE, opts->var_char.c_str(), nullptr));
    }
    if (!opts->storable_state && oblock.used_yyaccept) {
        local_decls = true;
        append(code, code_var(alc, VarType::UINT, opts->var_accept.c_str(), "0"));
    }

    if (opts->loop_switch) {
        // In the loop/switch mode append all DFA states as cases of the `yystate` switch.
        // Merge DFAs for different conditions together in one switch.
        local_decls = true;
        append(code, gen_yystate_def(output));

        CodeCases* cases = code_cases(alc);
        for (const std::unique_ptr<Adfa>& dfa : dfas) {
            gen_dfa_as_switch_cases(output, *dfa, cases);
        }
        wrap_dfas_in_loop_switch(output, code, cases);

    } else {
        // In the goto/label mode, generate DFA states as blocks of code preceded with labels,
        // and `goto` transitions between states.
        if (opts->cgoto && is_cond_block) {
            local_decls = true;
            append(code, gen_cond_table(output));
        }
        if (opts->bitmaps) {
            for (const std::unique_ptr<Adfa>& dfa : dfas) {
                CodeList* bitmap = gen_bitmap(output, dfa->bitmap, dfa->cond);
                if (bitmap) {
                    local_decls = true;
                    append(code, bitmap);
                }
            }
        }
        if (opts->storable_state) {
            if (oblock.kind == InputBlock::USE) {
                // For a use block, always generate a local state switch. Link the block to the
                // state switch by the autogenerated block name. Note that it is impossible for the
                // user to do so with a `getstate:re2c` directive, as use blocks do not have a
                // user-defined name and cannot be referenced.
                BlockNameList* p = nullptr;
                p = alc.alloct<BlockNameList>(1);
                p->name = copystr(oblock.name, alc);
                p->next = nullptr;
                Code* x = code_state_goto(alc, p);
                CHECK_RET(gen_state_goto(output, x));
                append(code, x);
            } else if (!output.state_goto) {
                // For a non-use block, generate a state switch only if it wasn't generated before.
                // Null block list means that the autogenerated state switch should include all
                // non-use blocks in the file.
                Code* x = code_state_goto(alc, nullptr);
                CHECK_RET(gen_state_goto(output, x));
                append(code, x);
                output.state_goto = true;
            }
        }
        if (!opts->label_start.empty()) {
            // User-defined start label that should be used by user-defined code.
            append(code, code_slabel(alc, buf.str(opts->label_start).flush()));
        }
        if (oblock.start_label) {
            // Numeric start label used by the generated code (user-defined one may not exist).
            append(code, code_nlabel(alc, oblock.start_label));
        }
        if (is_cond_block) {
            append(code, gen_cond_goto(output));
        }
        for (const std::unique_ptr<Adfa>& dfa : dfas) {
            if (is_cond_block) {
                if (opts->cond_div.length()) {
                    buf.str(opts->cond_div);
                    argsubst(buf.stream(), opts->cond_div_param, "cond", true, dfa->cond);
                    append(code, code_textraw(alc, buf.flush()));
                }
                buf.str(opts->cond_label_prefix).str(dfa->cond);
                append(code, code_slabel(alc, buf.flush()));
            }
            gen_dfa_as_blocks_with_labels(output, *dfa, code);
        }
    }

    // Wrap the block in braces, so that variable declarations have local scope.
    append(program, code_block(alc, code, local_decls ? CodeBlock::Kind::WRAPPED
            : opts->indent_top == 0 ? CodeBlock::Kind::INDENTED : CodeBlock::Kind::RAW));

    return Ret::OK;
}

static void gen_block_dot(Output& output, const Adfas& dfas, CodeList* code) {
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;

    append(code, code_text(alc, "digraph re2c {"));
    append(code, gen_cond_goto(output));

    for (const std::unique_ptr<Adfa>& dfa : dfas) {
        if (!dfa->cond.empty()) {
            buf.str(dfa->cond).cstr(" -> ").label(*dfa->head->label);
            append(code, code_text(alc, buf.flush()));
        }

        for (State* s = dfa->head; s; s = s->next) {
            if (s->action.kind == Action::Kind::ACCEPT) {
                uint32_t i = 0;
                for (const AcceptTrans& a: *s->action.info.accepts) {
                    buf.label(*s->label).cstr(" -> ").label(*a.state->label)
                            .cstr(" [label=\"yyaccept=").u32(i).cstr("\"]");
                    append(code, code_text(alc, buf.flush()));
                    ++i;
                }
            } else if (s->action.kind == Action::Kind::RULE) {
                const SemAct* semact = dfa->rules[s->action.info.rule].semact;
                if (!semact->autogen) {
                    buf.label(*s->label).cstr(" [label=\"")
                            .str(output.msg.filenames[semact->loc.file])
                            .cstr(":").u32(semact->loc.line).cstr("\"]");
                    append(code, code_text(alc, buf.flush()));
                }
            }
            gen_go(output, *dfa, &s->go, s, code);
        }
    }

    append(code, code_text(alc, "}"));
}

static void gen_block_skeleton(Output& output, const Adfas& dfas, CodeList* code) {
    for (const std::unique_ptr<Adfa>& dfa : dfas) {
        emit_skeleton(output, code, *dfa);
    }
}

LOCAL_NODISCARD(Ret codegen_generate_block(Output& output)) {
    OutputBlock& block = output.block();
    Adfas& dfas = block.dfas;
    const opt_t* opts = block.opts;

    for (Code* code = block.code->head; code != nullptr; code = code->next) {
        switch (code->kind) {
        case CodeKind::DFAS: {
            CodeList* program = code_list(output.allocator);
            if (opts->target == Target::DOT) {
                gen_block_dot(output, dfas, program);
            } else if (opts->target == Target::SKELETON) {
                gen_block_skeleton(output, dfas, program);
            } else {
                CHECK_RET(gen_block_code(output, dfas, program));
            }
            code->kind = CodeKind::BLOCK;
            code->block.kind = CodeBlock::Kind::RAW;
            code->block.stmts = program;
            break;
        }
        case CodeKind::STATE_GOTO:
            CHECK_RET(gen_state_goto(output, code));
            break;
        case CodeKind::STAGS:
        case CodeKind::MTAGS:
            CHECK_RET(expand_tags_directive(output, code));
            break;
        case CodeKind::COND_ENUM:
            CHECK_RET(expand_cond_enum(output, code));
            break;
        case CodeKind::MAXFILL:
        case CodeKind::MAXNMATCH:
            CHECK_RET(gen_yymax(output, code));
            break;
        default:
            // skip for now, leave the rest for the render phase
            break;
        }
    }

    return Ret::OK;
}

Ret codegen_generate(Output& output) {
    for (const blocks_t& bs : {output.cblocks, output.hblocks}) {
        for (OutputBlock* b : bs) {
            output.set_current_block(b);
            CHECK_RET(codegen_generate_block(output));
            b->dfas.clear(); // DFAs are no longer used after this phase
        }
    }
    output.set_current_block(nullptr);
    return Ret::OK;
}

std::string vartag_name(
        tagver_t ver, const std::string& prefix, const std::set<tagver_t>& mtagvers) {
    std::ostringstream s;
    s << prefix;
    // S-tags and m-tags should not overlap, so m-tags have an additional "m" prefix (note that tag
    // variables in different conditions may have identical numbers).
    if (mtagvers.find(ver) != mtagvers.end()) s << "m";
    s << ver;
    return s.str();
}

std::string vartag_expr(tagver_t ver, const opt_t* opts, const std::set<tagver_t>& mtagvers) {
    std::ostringstream os(opts->tags_expression);
    std::string name = vartag_name(ver, opts->tags_prefix, mtagvers);
    argsubst(os, opts->api_sigil, "tag", true, name);
    return os.str();
}

} // end namespace re2c
