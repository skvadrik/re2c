#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <algorithm>
#include <iosfwd>
#include <ostream>
#include <set>
#include <string>
#include <utility>
#include <valarray>
#include <vector>

#include "src/adfa/adfa.h"
#include "src/codegen/code.h"
#include "src/codegen/helpers.h"
#include "src/options/opt.h"
#include "src/debug/debug.h"
#include "src/dfa/tcmd.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/skeleton/skeleton.h"
#include "src/util/string_utils.h"


namespace re2c {

static void gen_fill_and_label(Output &output, CodeList *stmts, const DFA &dfa,
    const State *s);
static void emit_accept(Output &output, CodeList *stmts, const DFA &dfa,
    const accept_t &acc);
static void emit_rule(Output &output, CodeList *stmts, const DFA &dfa, size_t rule_idx);
static void gen_fintags(Output &output, CodeList *stmts, const DFA &dfa,
    const Rule &rule);
static bool endstate(const State *s);

static const char *gen_fill_label(Output &output, uint32_t index)
{
    const opt_t *opts = output.block().opts;
    Scratchbuf &o = output.scratchbuf;
    DASSERT(o.empty());
    return o.str(opts->yyfilllabel).u32(index).flush();
}

void emit_action(Output &output, const DFA &dfa, const State *s, CodeList *stmts)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const char *text;

    switch (s->action.type) {
    case Action::MATCH:
        if (!opts->eager_skip) {
            append(stmts, code_skip(alc));
        }
        gen_fill_and_label(output, stmts, dfa, s);
        if (!endstate(s)) {
            append(stmts, code_peek(alc));
        }
        break;
    case Action::INITIAL: {
        const size_t save = s->action.info.save;
        const bool backup = save != NOSAVE;
        const bool ul1 = s->label->used;

        if (ul1 && dfa.accepts.size() > 1 && backup) {
            text = o.str(opts->yyaccept).cstr(" = ").u64(save).flush();
            append(stmts, code_stmt(alc, text));
        }
        if (ul1 && !opts->eager_skip) {
            append(stmts, code_skip(alc));
        }
        append(stmts, code_nlabel(alc, dfa.initial_label));
        if (opts->dFlag) {
            text = o.str(opts->yydebug).cstr("(").label(*dfa.initial_label)
                .cstr(", *").str(opts->yycursor).cstr(")").flush();
            append(stmts, code_stmt(alc, text));
        }
        gen_fill_and_label(output, stmts, dfa, s);
        if (backup) {
            append(stmts, code_backup(alc));
        }
        if (!endstate(s)) {
            append(stmts, code_peek(alc));
        }
        break;
    }
    case Action::SAVE:
        if (dfa.accepts.size() > 1) {
            text = o.str(opts->yyaccept).cstr(" = ").u64(s->action.info.save).flush();
            append(stmts, code_stmt(alc, text));
        }
        if (!opts->eager_skip) {
            append(stmts, code_skip(alc));
        }
        append(stmts, code_backup(alc));
        gen_fill_and_label(output, stmts, dfa, s);
        append(stmts, code_peek(alc));
        break;
    case Action::MOVE:
        break;
    case Action::ACCEPT:
        emit_accept(output, stmts, dfa, *s->action.info.accepts);
        break;
    case Action::RULE:
        emit_rule(output, stmts, dfa, s->action.info.rule);
        break;
    }
}

static CodeList *emit_accept_binary(Output &output, const DFA &dfa, const accept_t &acc,
    size_t l, size_t r)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;

    CodeList *stmts = code_list(alc);
    if (l < r) {
        const size_t m = (l + r) >> 1;
        const char *if_cond = o.str(opts->yyaccept).cstr(r == l + 1 ? " == " : " <= ")
            .u64(m).flush();
        CodeList *if_then = emit_accept_binary(output, dfa, acc, l, m);
        CodeList *if_else = emit_accept_binary(output, dfa, acc, m + 1, r);
        append(stmts, code_if_then_else(alc, if_cond, if_then, if_else));
    }
    else {
        const CodeJump jump = {acc[l].first, acc[l].second, false, false, false};
        gen_goto(output, dfa, stmts, NULL, jump);
    }
    return stmts;
}

static void gen_restore(Output &output, CodeList *stmts)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const char *text;

    if (opts->input_api == INPUT_DEFAULT) {
        text = o.str(opts->yycursor).cstr(" = ").str(opts->yymarker).flush();
        append(stmts, code_stmt(alc, text));
    }
    else if (opts->api_style == API_FUNCTIONS) {
        text = o.str(opts->yyrestore).cstr("()").flush();
        append(stmts, code_stmt(alc, text));
    }
    else {
        text = o.str(opts->yyrestore).flush();
        append(stmts, code_text(alc, text));
    }
}

void emit_accept(Output &output, CodeList *stmts, const DFA &dfa, const accept_t &acc)
{
    const opt_t *opts = output.block().opts;
    const size_t nacc = acc.size();
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const char *text;

    if (nacc == 0) return;

    gen_restore(output, stmts);

    // only one possible 'yyaccept' value: unconditional jump
    if (nacc == 1) {
        const CodeJump jump = {acc[0].first, acc[0].second, false, false, false};
        gen_goto(output, dfa, stmts, NULL, jump);
        return;
    }

    bool have_tags = false;
    for (size_t i = 0; i < nacc; ++i) {
        if (acc[i].second != TCID0) {
            have_tags = true;
            break;
        }
    }

    // jump table
    if (opts->gFlag && nacc >= opts->cGotoThreshold && !have_tags) {
        CodeList *block = code_list(alc);

        CodeList *table = code_list(alc);
        text = o.cstr("static void *").str(opts->yytarget).cstr("[").u64(nacc)
            .cstr("] = {").flush();
        append(block, code_text(alc, text));
        for (uint32_t i = 0; i < nacc; ++i) {
            Label *l = acc[i].first->label;
            l->used = true;
            text = o.cstr("&&").str(opts->labelPrefix).label(*l).cstr(",").flush();
            append(table, code_text(alc, text));
        }
        append(block, code_block(alc, table, CodeBlock::INDENTED));
        append(block, code_stmt(alc, "}"));

        text = o.cstr("goto *").str(opts->yytarget).cstr("[").str(opts->yyaccept)
            .cstr("]").flush();
        append(block, code_stmt(alc, text));

        append(stmts, code_block(alc, block, CodeBlock::WRAPPED));
        return;
    }

    // nested ifs
    if (opts->sFlag || nacc == 2) {
        append(stmts, emit_accept_binary(output, dfa, acc, 0, nacc - 1));
        return;
    }

    // switch
    CodeCases *cases = code_cases(alc);
    for (uint32_t i = 0; i < nacc; ++i) {
        CodeList *case_body = code_list(alc);
        const CodeJump jump = {acc[i].first, acc[i].second, false, false, false};
        gen_goto(output, dfa, case_body, NULL, jump);
        if (i == nacc - 1) {
            append(cases, code_case_default(alc, case_body));
        }
        else {
            append(cases, code_case_number(alc, case_body, static_cast<int32_t>(i)));
        }
    }
    text = o.str(opts->yyaccept).flush();
    append(stmts, code_switch(alc, text, cases));
}

void emit_rule(Output &output, CodeList *stmts, const DFA &dfa, size_t rule_idx)
{
    const opt_t *opts = output.block().opts;
    const Rule &rule = dfa.rules[rule_idx];
    const SemAct *semact = rule.semact;
    const std::string &cond = semact->cond;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    std::string s;
    const char *text;

    gen_fintags(output, stmts, dfa, rule);

    if (opts->target == TARGET_SKELETON) {
        emit_skeleton_action(output, stmts, dfa, rule_idx);
    }
    else {
        if (!cond.empty() && dfa.cond != cond) {
            o.str(opts->cond_set);
            argsubst(o.stream(), opts->cond_set_arg, "cond", true,
                opts->condEnumPrefix + cond);
            if (opts->cond_set_naked) {
                append(stmts, code_text(alc, o.flush()));
            } else {
                o.cstr("(").str(opts->condEnumPrefix).str(cond).cstr(")");
                append(stmts, code_stmt(alc, o.flush()));
            }
        }
        if (!semact->autogen) {
            if (!dfa.setup.empty()) {
                text = o.str(dfa.setup).flush();
                append(stmts, code_text(alc, text));
            }
            append(stmts, code_line_info_input(alc, semact->loc));
            text = o.str(semact->text).flush();
            append(stmts, code_text(alc, text));
            append(stmts, code_line_info_output(alc));
        }
        else if (!cond.empty()) {
            o.str(opts->condGoto);
            argsubst(o.stream(), opts->condGotoParam, "cond", true,
                opts->condPrefix + cond);
            append(stmts, code_text(alc, o.flush()));
        }
    }
}

static void gen_setstate(Output &output, CodeList *stmts, uint32_t fillidx)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;

    o.str(opts->state_set);
    argsubst(o.stream(), opts->state_set_arg, "state", true, fillidx);
    if (opts->state_set_naked) {
        append(stmts, code_text(alc, o.flush()));
    } else {
        o.cstr("(").u32(fillidx).cstr(")");
        append(stmts, code_stmt(alc, o.flush()));
    }
}

static CodeList *gen_fill_falllback(Output &output, const DFA &dfa,
    const State *from, const State *to)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    const State *fallback;
    tcid_t falltags;

    DASSERT(opts->eof != NOEOF);
    if (from->action.type == Action::INITIAL) {
        // EOF in the initial state: EOF rule takes priority over any other rule.
        fallback = dfa.eof_state;
        falltags = TCID0;
    } else if (from->rule != Rule::NONE) {
        // EOF in accepting state: match the rule in this state.
        fallback = dfa.finstates[from->rule];
        falltags = from->rule_tags;
    } else {
        // EOF in a non-accepting state: fallback to default state.
        fallback = dfa.defstate;
        falltags = from->fall_tags;
    }

    if (opts->stadfa) {
        DASSERT(from->go.tags == from->stadfa_tags);

    } else if (from->go.tags != TCID0) {
        // Tags have been hoisted out of transitions into state (this means that
        // tags on all transitions coincide, including the fallback transition).
        // Do not add duplicate tags to fallback transition.
        DASSERT(from->go.tags == falltags);
        falltags = TCID0;
    }

    CodeList *fallback_trans = code_list(alc);
    if (fallback != to || opts->fFlag) {
        // tag actions on the fallback transition
        gen_settags(output, fallback_trans, dfa, falltags, false /* delayed */);

        // go to fallback state
        fallback->label->used = true;
        append(fallback_trans, code_stmt(alc, output.scratchbuf.cstr("goto ")
            .str(opts->labelPrefix).label(*fallback->label).flush()));
    }
    else {
        // Transition can be elided, because control flow "falls through" to an
        // identical transition. Tags and skip (if present) are elided as well,
        // because the next transition covers them.
    }
    return fallback_trans;
}

static void gen_fill(Output &output, CodeList *stmts, const DFA &dfa,
    const State *from, const State *to)
{
    const opt_t *opts = output.block().opts;
    const bool eof_rule = opts->eof != NOEOF;
    const uint32_t fillidx = output.block().fill_index_end - 1;
    const size_t need = eof_rule ? 1 : from->fill;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;

    // YYLESSTHAN
    const char *lessthan = gen_lessthan(o, opts, need);

    // Transition to YYFILL label from the initial state dispatch.
    CodeList *goto_fill = code_list(alc);
    const char *flabel = gen_fill_label(output, fillidx);
    append(goto_fill, code_stmt(alc, o.cstr("goto ").cstr(flabel).flush()));

    CodeList *fill = code_list(alc);

    if (opts->fFlag) {
        gen_setstate(output, eof_rule ? fill : stmts, fillidx);
    }

    if (opts->fill_use) {
        // With EOF rule there is no YYFILL argument and no parameter to replace.
        o.str(opts->fill);
        if (!eof_rule) {
            argsubst(o.stream(), opts->fill_arg, "len", true, need);
        }
        if (opts->fill_arg_use) {
            o.cstr("(");
            if (!eof_rule) o.u64(need);
            o.cstr(")");
        }
        if (eof_rule && !opts->fFlag) {
            // EOF rule without storable state: check YYFILL return value. If it
            // succeeds (returns zero) then go to YYFILL label and rematch.
            if (!opts->fill_naked) o.cstr(" == 0");
            append(fill, code_if_then_else(alc, o.flush(), goto_fill, NULL));
        }
        else {
            // Otherwise don't check YYFILL return value: assume that it does
            // not return on failure.
            append(fill, opts->fill_naked
                ? code_text(alc, o.flush())
                : code_stmt(alc, o.flush()));
        }
    }

    if (eof_rule) {
        CodeList *fallback = gen_fill_falllback(output, dfa, from, to);
        if (opts->fFlag) {
            // With storable state and EOF rule the initial state dispatch needs to
            // handle YYFILL failure: if there is still not enough input, it must
            // follow the fallback transition for the state that triggered YYFILL.
            // Fallback transition is inlined in the state dispatch (as opposed to
            // jumping to the corresponding DFA transition) because Go backend does
            // not support jumping in the middle of a nested block.
            prepend(goto_fill, code_if_then_else(alc, lessthan, fallback, NULL));
        }
        else {
            append(fill, fallback);
        }
    }
    if (opts->fFlag) {
        output.block().fill_goto.push_back(goto_fill);
    }

    if (opts->fill_check && fill->head) {
        CodeList *check_fill = code_list(alc);
        append(check_fill, code_if_then_else(alc, lessthan, fill, NULL));
        fill = check_fill;
    }

    append(stmts, fill);
}

void gen_fill_and_label(Output &output, CodeList *stmts, const DFA &dfa, const State *s)
{
    const opt_t *opts = output.block().opts;

    const bool need_fill = opts->fill_use && !endstate(s);
    const bool need_fill_on_trans = need_fill && opts->eof != NOEOF;
    const bool need_fill_in_state = need_fill && opts->eof == NOEOF && s->fill > 0;
    const bool need_fill_label = need_fill_on_trans || (need_fill_in_state && opts->fFlag);

    if (need_fill_label) {
        ++output.block().fill_index_end;
    }

    if (need_fill_in_state) {
        gen_fill(output, stmts, dfa, s, NULL);
    }

    if (opts->eof != NOEOF) {
        // If the end-of-input rule $ is used, the lexer may jump to the YYFILL
        // label to rescan the current input character. Generate tag operations
        // before the label to avoid applying them multiple times in the above
        // scenario (re-application may produce incorrect results in case of
        // non-idempotent operations).
        gen_settags(output, stmts, dfa, s->go.tags, opts->stadfa /* delayed */);
    }

    if (need_fill_label) {
        const char *flabel = gen_fill_label(output, output.block().fill_index_end - 1);
        append(stmts, code_slabel(output.allocator, flabel));
    }
}

void gen_goto(Output &output, const DFA &dfa, CodeList *stmts, const State *from,
    const CodeJump &jump)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const char *text;

    if (jump.eof) {
        gen_fill(output, stmts, dfa, from, jump.to);
    }

    if (jump.skip && !opts->lookahead) {
        append(stmts, code_skip(alc));
    }

    gen_settags(output, stmts, dfa, jump.tags, false /* delayed */);

    if (jump.skip && opts->lookahead) {
        append(stmts, code_skip(alc));
    }

    if (!jump.elide) {
        jump.to->label->used = true;
        text = o.cstr("goto ").str(opts->labelPrefix).label(*jump.to->label).flush();
        append(stmts, code_stmt(alc, text));
    }
    else {
        // Goto can be elided, because control flow "falls through" to the
        // correct DFA state. This usually happens for the last statement in a
        // sequence of "linear if" statements.
    }
}

static void gen_shift(Output &output, CodeList *stmts, int32_t shift,
    const std::string &tag, bool history)
{
    if (shift == 0) return;

    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const bool notag = tag.empty();

    o.str(notag ? opts->yyshift
        : history ? opts->yyshiftmtag : opts->yyshiftstag);
    if (opts->api_style == API_FUNCTIONS) {
        o.cstr("(");
        if (!notag) o.str(tag).cstr(", ");
        o.i32(shift).cstr(")");
        append(stmts, code_stmt(alc, o.flush()));
    } else {
        // Single-argument YYSHIFT allows short-form unnamed substitution,
        // multi-argument YYSHIFTSTAG / YYSHIFTMTAG require named placeholders.
        if (!notag) {
            argsubst(o.stream(), opts->api_sigil, "tag", false, tag);
        }
        argsubst(o.stream(), opts->api_sigil, "shift", notag, shift);
        append(stmts, code_text(alc, o.flush()));
    }
}

static void gen_settag(Output &output, CodeList *stmts, const std::string &tag,
    bool negative, bool history)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;

    const std::string &s = history
        ? (negative ? opts->yymtagn : opts->yymtagp)
        : (negative ? opts->yystagn : opts->yystagp);
    o.str(s);
    if (opts->api_style == API_FUNCTIONS) {
        o.cstr("(").str(tag).cstr(")");
        append(stmts, code_stmt(alc, o.flush()));
    } else {
        argsubst(o.stream(), opts->api_sigil, "tag", true, tag);
        append(stmts, code_text(alc, o.flush()));
    }
}

static void gen_assign(Output &output, CodeList *stmts, const std::string &lhs,
    const std::string &rhs)
{
    Scratchbuf &o = output.scratchbuf;
    o.str(lhs).cstr(" = ").str(rhs);
    append(stmts, code_stmt(output.allocator, o.flush()));
}

static void gen_assign_many(Output &output, CodeList *stmts,
    const std::vector<std::string> &many, const std::string &rhs)
{
    Scratchbuf &o = output.scratchbuf;
    for (size_t i = 0; i < many.size(); ++i) {
        o.str(many[i]).cstr(" = ");
    }
    o.str(rhs);
    append(stmts, code_stmt(output.allocator, o.flush()));
}

static void gen_assign_many_to_first(Output &output, CodeList *stmts,
    const std::vector<std::string> &many)
{
    if (many.size() <= 1) return;

    Scratchbuf &o = output.scratchbuf;
    for (size_t i = 1; i < many.size(); ++i) {
        o.str(many[i]).cstr(" = ");
    }
    o.str(many[0]);
    append(stmts, code_stmt(output.allocator, o.flush()));
}

static void gen_restorectx(Output &output, CodeList *stmts, const std::string &tag)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const bool notag = tag.empty();

    o.str(notag ? opts->yyrestorectx : opts->yyrestoretag);
    if (opts->api_style == API_FUNCTIONS) {
        o.cstr("(").str(tag).cstr(")");
        append(stmts, code_stmt(alc, o.flush()));
    } else {
        if (!notag) {
            argsubst(o.stream(), opts->api_sigil, "tag", true, tag);
        }
        append(stmts, code_text(alc, o.flush()));
    }
}

void gen_settags(Output &output, CodeList *tag_actions, const DFA &dfa, tcid_t tcid,
    bool delayed)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const bool generic = opts->input_api == INPUT_CUSTOM;
    const tcmd_t *cmd = dfa.tcpool[tcid];

    // single tag, backwards compatibility, use context marker
    if (cmd && dfa.oldstyle_ctxmarker) {
        DASSERT(!opts->stadfa);
        if (generic) {
            o.str(opts->yybackupctx);
            if (opts->api_style == API_FUNCTIONS) {
                o.cstr("()");
                append(tag_actions, code_stmt(alc, o.flush()));
            } else {
                append(tag_actions, code_text(alc, o.flush()));
            }
        } else {
            gen_assign(output, tag_actions, opts->yyctxmarker, opts->yycursor);
        }
        return;
    }

    for (const tcmd_t *p = cmd; p; p = p->next) {
        const tagver_t l = p->lhs, r = p->rhs, *h = p->history, *h0;
        const std::string le = vartag_expr(l, opts);
        const std::string re = vartag_expr(r, opts);
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
                if (delayed && !negative) {
                    gen_shift(output, tag_actions, -1, le, true);
                }
            }
        } else {
            // "save" command
            if (generic) {
                const bool negative = *h == TAGVER_BOTTOM;
                gen_settag(output, tag_actions, le, negative, false);
                if (delayed && !negative) {
                    gen_shift(output, tag_actions, -1, le, false);
                }
            } else {
                Scratchbuf o2(alc);
                for (const tcmd_t *q = p; q && tcmd_t::isset(q); p = q, q = q->next) {
                    Scratchbuf &x = q->history[0] == TAGVER_BOTTOM ? o : o2;
                    x.str(vartag_expr(q->lhs, opts)).cstr(" = ");
                }
                if (!o.empty()) {
                    o.cstr("NULL");
                    append(tag_actions, code_stmt(alc, o.flush()));
                }
                if (!o2.empty()) {
                    o2.str(opts->yycursor).cstr(delayed ? " - 1" : "");
                    append(tag_actions, code_stmt(alc, o2.flush()));
                }
            }
        }
    }
}

void gen_fintags(Output &output, CodeList *stmts, const DFA &dfa, const Rule &rule)
{
    const opt_t *opts = output.block().opts;
    const bool generic = opts->input_api == INPUT_CUSTOM;
    const std::vector<Tag> &tags = dfa.tags;
    const tagver_t *fins = dfa.finvers;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    std::vector<std::string> fintags;

    if (rule.ncap > 0) {
        o.cstr("yynmatch = ").u64(rule.ncap);
        append(stmts, code_stmt(alc, o.flush()));
    }

    CodeList *varops = code_list(alc);
    CodeList *fixops = code_list(alc);
    CodeList *fixtrailops = code_list(alc);
    CodeList *fixpostops = code_list(alc);
    std::string negtag;

    for (size_t t = rule.ltag; t < rule.htag; ++t) {
        const Tag &tag = tags[t];

        // structural tag that is only needed for disambiguation
        if (fictive(tag)) continue;

        expand_fintags(tag, fintags);

        if (!fixed(tag)) {
            // variable tag
            const std::string expr = vartag_expr(fins[t], opts);
            if (trailing(tag)) {
                const bool notag = dfa.oldstyle_ctxmarker;
                if (generic) {
                    gen_restorectx(output, varops, notag ? "" : expr);
                } else {
                    gen_assign(output, varops, opts->yycursor,
                        notag ? opts->yyctxmarker : expr);
                }
            } else {
                gen_assign_many(output, varops, fintags, expr);
            }
        } else {
            DASSERT(!history(tag));

            // fixed tag that is based on either variable tag or cursor
            const int32_t dist = static_cast<int32_t>(tag.dist);
            const bool fixed_on_cursor = tag.base == Tag::RIGHTMOST;
            const std::string base = fixed_on_cursor
                ? opts->yycursor : vartag_expr(fins[tag.base], opts);

            if (trailing(tag)) {
                DASSERT(tag.toplevel);
                if (generic) {
                    if (!fixed_on_cursor) {
                        gen_restorectx(output, fixtrailops, base);
                    }
                    gen_shift(output, fixtrailops, -dist, "", false /* unused */);
                } else {
                    if (!fixed_on_cursor) {
                        o.str(opts->yycursor).cstr(" = ").str(base);
                        if (dist > 0) o.cstr(" - ").i32(dist);
                    } else if (dist > 0) {
                        o.str(opts->yycursor).cstr(" -= ").i32(dist);
                    }
                    append(fixtrailops, code_stmt(alc, o.flush()));
                }
            } else {
                DASSERT(!fintags.empty());
                const std::string &first = fintags[0];

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
                        // Split operations in two parts. First, set all fixed tags to
                        // their base tag. Second, choose one of the base tags to store
                        // negative value (with generic API there is no NULL constant)
                        // and compare fixed tags against it before shifting. This must
                        // be done after all uses of that base tag.
                        if (negtag.empty()) negtag = base;
                        gen_assign(output, fixops, first, base);
                        const char *cond = o.str(first).cstr(" != ").str(negtag).flush();
                        CodeList *then = code_list(alc);
                        gen_shift(output, then, -dist, first, false);
                        append(fixpostops, code_if_then_else(alc, cond, then, NULL));
                    }
                } else {
                    if (dist == 0) {
                        gen_assign_many(output, fixops, fintags, base);
                    } else if (tag.toplevel) {
                        gen_assign_many(output, fixops, fintags,
                            o.str(base).cstr(" - ").i32(dist).flush());
                    } else {
                        // If base tag is NULL, fixed tag is also NULL, otherwise it
                        // equals the value of the base tag plus offset.
                        gen_assign(output, fixops, first, base);
                        const char *cond = o.str(base).cstr(" != NULL").flush();
                        CodeList *then = code_list(alc);
                        append(then, code_stmt(alc,
                            o.str(first).cstr(" -= ").i32(dist).flush()));
                        append(fixops, code_if_then_else(alc, cond, then, NULL));
                        gen_assign_many_to_first(output, fixops, fintags);
                    }
                }
            }
        }
    }

    append(stmts, varops);
    append(stmts, fixtrailops);
    append(stmts, fixops);

    if (!negtag.empty()) {
        // With generic API there is no explicit negative NULL value, so it is
        // necessary to materialize no-match value in a tag.
        DASSERT(opts->input_api == INPUT_CUSTOM);
        append(stmts, code_text(alc, o.cstr("/* materialize no-match value */").flush()));
        gen_settag(output, stmts, negtag, true, false);
        append(stmts, fixpostops);
    }
}

void expand_fintags(const Tag &tag, std::vector<std::string> &fintags)
{
    fintags.clear();
    if (trailing(tag)) {
        // empty list
    } else if (!capture(tag)) {
        // named tag
        fintags.push_back(*tag.name);
    } else {
        // capture tag, maps to a range of parentheses
        for (size_t i = tag.lsub; i <= tag.hsub; i += 2) {
            fintags.push_back("yypmatch[" + to_string(i) + "]");
        }
    }
}

bool endstate(const State *s)
{
    // 'end' state is a state which has no outgoing transitions on symbols
    // usually 'end' states are final states (not all final states are 'end'
    // states), but sometimes 'end' state happens to be initial non-accepting
    // state, e.g. in case of rule '[]'
    DASSERT(s->go.nspans > 0);
    const Action::type_t &a = s->go.span[0].to->action.type;
    return s->go.nspans == 1 && (a == Action::RULE || a == Action::ACCEPT);
}

const char *gen_lessthan(Scratchbuf &o, const opt_t *opts, size_t n)
{
    if (opts->input_api == INPUT_CUSTOM) {
        o.str(opts->yylessthan);
        if (opts->api_style == API_FUNCTIONS) {
            o.cstr("(").u64(n).cstr(")");
        } else {
            argsubst(o.stream(), opts->api_sigil, "len", true, n);
        }
    }
    else if (n == 1) {
        o.str(opts->yylimit).cstr(" <= ").str(opts->yycursor);
    }
    else {
        o.cstr("(").str(opts->yylimit).cstr(" - ").str(opts->yycursor)
            .cstr(") < ").u64(n);
    }
    return o.flush();
}

} // namespace re2c
