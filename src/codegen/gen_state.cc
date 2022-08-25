#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <iosfwd>
#include <ostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "src/adfa/adfa.h"
#include "src/codegen/code.h"
#include "src/codegen/helpers.h"
#include "src/options/opt.h"
#include "src/dfa/tcmd.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/skeleton/skeleton.h"
#include "src/util/check.h"
#include "src/util/string_utils.h"

namespace re2c {

static void gen_fill_and_label(Output& output, CodeList* stmts, const Adfa& dfa, const State* s);
static void emit_accept(
        Output& output, CodeList* stmts, const Adfa& dfa, const uniq_vector_t<AcceptTrans>& acc);
static void emit_rule(Output& output, CodeList* stmts, const Adfa& dfa, size_t rule_idx);
static void gen_fintags(Output& output, CodeList* stmts, const Adfa& dfa, const Rule& rule);
static const char* gen_less_than(Scratchbuf& o, const opt_t* opts, size_t n);

static const char* gen_fill_label(Output& output, uint32_t index) {
    const opt_t* opts = output.block().opts;
    Scratchbuf& o = output.scratchbuf;
    DCHECK(o.empty());
    return o.str(opts->label_fill).u32(index).flush();
}

static bool endstate(const State* s) {
    // An 'end' state is a state which has no outgoing transitions on symbols. Usually 'end' states
    // are final states (not all final states are 'end' states), but sometimes it be initial
    // non-accepting state, e.g. in case of rule '[]'.
    DCHECK(s->go.nspans > 0);
    Action::Kind a = s->go.span[0].to->action.kind;
    return s->go.nspans == 1 && (a == Action::Kind::RULE || a == Action::Kind::ACCEPT);
}

static void gen_peek(OutAllocator& alc, const State* s, CodeList* stmts) {
    // Do not generate YYPEEK statement in case `yych` is overwritten before it is used. This may
    // happen if there is a single transition which does not require matching on `yych` (one
    // exception is a transition to a move state, which doesn't have its own YYPEEK and relies on
    // the previous value of `yych`).
    bool omit_peek = s->go.nspans == 1 && s->go.span[0].to->action.kind != Action::Kind::MOVE;
    if (!omit_peek) append(stmts, code_peek(alc));
}

void emit_action(Output& output, const Adfa& dfa, const State* s, CodeList* stmts) {
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

void emit_accept(
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

        CodeList* table = code_list(alc);
        text = o.cstr("static void *").str(opts->var_cgoto_table).cstr("[").u64(nacc).cstr("] = {")
                .flush();
        append(block, code_text(alc, text));
        for (const AcceptTrans& a : acc) {
            text = o.cstr("&&").str(opts->label_prefix).label(*a.state->label).cstr(",").flush();
            append(table, code_text(alc, text));
        }
        append(block, code_block(alc, table, CodeBlock::Kind::INDENTED));
        append(block, code_stmt(alc, "}"));

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

void emit_rule(Output& output, CodeList* stmts, const Adfa& dfa, size_t rule_idx) {
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
    const char* next_cond = o.str(opts->cond_enum_prefix).cstr(cond).flush();
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
        append(stmts, code_line_info_input(alc, semact->loc));
        append(stmts, code_text(alc, o.cstr(semact->text).flush()));
        append(stmts, code_line_info_output(alc));
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

static void gen_fill(
        Output& output, CodeList* stmts, const Adfa& dfa, const State* from, const State* to) {
    const opt_t* opts = output.block().opts;
    const bool eof_rule = opts->fill_eof != NOEOF;
    const uint32_t fillidx = output.block().fill_index - 1;
    const size_t need = eof_rule ? 1 : from->fill;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;

    // YYLESSTHAN
    const char* less_than = gen_less_than(o, opts, need);

    // Transition to YYFILL label from the initial state dispatch.
    CodeList* goto_fill = code_list(alc);
    if (!opts->loop_switch) {
        const char* flabel = gen_fill_label(output, fillidx);
        append(goto_fill, code_stmt(alc, o.cstr("goto ").cstr(flabel).flush()));
    } else {
        const char* next = o.u32(output.block().fill_state).flush();
        gen_continue_yyloop(output, goto_fill, next);
    }

    CodeList* fill = code_list(alc);

    if (opts->storable_state) {
        gen_state_set(output, eof_rule ? fill : stmts, o.u32(fillidx).flush());
    }

    if (opts->fill_enable) {
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
            append(fill, code_if_then_else(alc, o.flush(), goto_fill, nullptr));
        } else {
            // Otherwise don't check YYFILL return value: assume that it does not return on failure.
            append(fill, opts->fill_naked ? code_text(alc, o.flush()) : code_stmt(alc, o.flush()));
        }
    }

    if (eof_rule) {
        CodeList* fallback = gen_fill_falllback(output, dfa, from, to);
        if (opts->storable_state) {
            // With storable state and end-of-input rule $ the initial state dispatch needs to
            // handle YYFILL failure: if there is still not enough input, it must follow the
            // fallback transition for the state that triggered YYFILL. Fallback transition is
            // inlined in the state dispatch (as opposed to jumping to the corresponding DFA
            // transition) because Go backend does not support jumping in the middle of a nested
            // block.
            prepend(goto_fill, code_if_then_else(alc, less_than, fallback, nullptr));
        } else {
            append(fill, fallback);
        }
    }
    if (opts->storable_state) {
        output.block().fill_goto[fillidx] = goto_fill;
    }

    if (opts->fill_check && fill->head) {
        CodeList* check_fill = code_list(alc);
        append(check_fill, code_if_then_else(alc, less_than, fill, nullptr));
        fill = check_fill;
    }

    append(stmts, fill);
}

void gen_fill_and_label(Output& output, CodeList* stmts, const Adfa& dfa, const State* s) {
    const opt_t* opts = output.block().opts;

    const bool need_fill = opts->fill_enable && !endstate(s);
    const bool need_fill_on_trans = need_fill && opts->fill_eof != NOEOF;
    const bool need_fill_in_state = need_fill && opts->fill_eof == NOEOF && s->fill > 0;
    const bool need_fill_label = need_fill_on_trans || (need_fill_in_state && opts->storable_state);

    if (need_fill_label) {
        ++output.block().fill_index;
        output.block().fill_state = s->label->index;
    }

    if (need_fill_in_state) {
        gen_fill(output, stmts, dfa, s, nullptr);
    }

    if (opts->fill_eof != NOEOF) {
        // If the end-of-input rule $ is used, the lexer may jump to the YYFILL label to rescan the
        // current input character. Generate tag operations before the label to avoid applying them
        // multiple times in the above scenario (re-application may produce incorrect results in
        // case of non-idempotent operations).
        gen_settags(output, stmts, dfa, s->go.tags);
    }

    if (need_fill_label && !opts->loop_switch) {
        const char* flabel = gen_fill_label(output, output.block().fill_index - 1);
        append(stmts, code_slabel(output.allocator, flabel));
    }
}

void gen_goto(
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

void gen_settags(Output& output, CodeList* tag_actions, const Adfa& dfa, tcid_t tcid) {
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

void gen_fintags(Output& output, CodeList* stmts, const Adfa& dfa, const Rule& rule) {
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

const char* gen_less_than(Scratchbuf& o, const opt_t* opts, size_t n) {
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

} // namespace re2c
