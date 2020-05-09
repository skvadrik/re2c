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

#include "src/adfa/action.h"
#include "src/adfa/adfa.h"
#include "src/codegen/code.h"
#include "src/options/opt.h"
#include "src/debug/debug.h"
#include "src/dfa/tcmd.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/skeleton/skeleton.h"
#include "src/util/string_utils.h"


namespace re2c {

static CodeList *need(Output &output, size_t some);
static CodeList *gen_rescan_label(Output &output, const State *s);
static void emit_accept(Output &output, CodeList *stmts, const DFA &dfa, const accept_t &acc);
static void emit_rule(Output &output, CodeList *stmts, const DFA &dfa, size_t rule_idx);
static void gen_fintags(Output &output, CodeList *stmts, const DFA &dfa, const Rule &rule);
static Code *gen_on_eof(Output &output, const DFA &dfa, const State *from, const State *to);
static bool endstate(const State *s);

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
        append(stmts, need(output, s->fill));
        append(stmts, gen_rescan_label(output, s));
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
        append(stmts, need(output, s->fill));
        if (backup) {
            append(stmts, code_backup(alc));
        }
        append(stmts, gen_rescan_label(output, s));
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
        append(stmts, need(output, s->fill));
        append(stmts, gen_rescan_label(output, s));
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
        gen_goto(output, stmts, NULL, acc[l].first, dfa, acc[l].second, false, false);
    }
    return stmts;
}

static const char *gen_restore(Scratchbuf &o, const opt_t *opts)
{
    if (opts->input_api == INPUT_DEFAULT) {
        o.str(opts->yycursor).cstr(" = ").str(opts->yymarker);
    }
    else {
        o.str(opts->yyrestore);
        if (opts->decorate) o.cstr(" ()");
    }
    return o.flush();
}

void emit_accept(Output &output, CodeList *stmts, const DFA &dfa, const accept_t &acc)
{
    const opt_t *opts = output.block().opts;
    const size_t nacc = acc.size();
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const char *text;

    if (nacc == 0) return;

    text = gen_restore(o, opts);
    append(stmts, code_stmt(alc, text));

    // only one possible 'yyaccept' value: unconditional jump
    if (nacc == 1) {
        gen_goto(output, stmts, NULL, acc[0].first, dfa, acc[0].second, false, false);
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
        append(block, code_text(alc, "};"));

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
    const char *switch_expr = o.str(opts->yyaccept).flush();
    CodeCases *switch_cases = code_cases(alc);
    CodeList *case_stmts = code_list(alc);
    gen_goto(output, case_stmts, NULL, acc[nacc - 1].first, dfa, acc[nacc - 1].second,
        false, false);
    append(switch_cases, code_case_number(alc, case_stmts, 0));
    for (uint32_t i = 0; i < nacc - 1; ++i) {
        CodeList *case_body = code_list(alc);
        gen_goto(output, case_body, NULL, acc[i].first, dfa, acc[i].second, false, false);
        append(switch_cases, code_case_number(alc, case_body, static_cast<int32_t>(i)));
    }
    Code *cswitch = code_switch(alc, switch_expr, switch_cases, true);
    append(stmts, cswitch);
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
            s = opts->cond_set;
            strrreplace(s, opts->cond_set_arg, opts->condEnumPrefix + cond);
            o.str(s);
            if (!opts->cond_set_naked) {
                o.cstr("(").str(opts->condEnumPrefix).str(cond).cstr(");");
            }
            text = o.flush();
            append(stmts, code_text(alc, text));
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
            s = opts->condGoto;
            strrreplace(s, opts->condGotoParam, opts->condPrefix + cond);
            text = o.str(s).flush();
            append(stmts, code_text(alc, text));
        }
    }
}

CodeList *need(Output &output, size_t some)
{
    const opt_t *opts = output.block().opts;

    if (opts->eof != NOEOF || some == 0) return NULL;

    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    std::string s;
    const char *text;

    CodeList *stmts = code_list(alc);

    if (opts->fFlag) {
        strrreplace(s = opts->state_set, opts->state_set_arg, output.fill_index);
        o.str(s);
        if (!opts->state_set_naked) {
            o.cstr("(").u32(output.fill_index).cstr(");");
        }
        text = o.flush();
        append(stmts, code_text(alc, text));
    }

    if (opts->fill_use) {
        strrreplace(s = opts->fill, opts->fill_arg, some);
        o.str(s);
        if (!opts->fill_naked) {
            if (opts->fill_arg_use) {
                o.cstr("(").u64(some).cstr(")");
            }
            o.cstr(";");
        }
        text = o.flush();
        Code *yyfill = code_text(alc, text);

        if (opts->fill_check) {
            text = gen_lessthan(o, opts, some);
            CodeList *if_then = code_list(alc);
            append(if_then, yyfill);
            append(stmts, code_if_then_else(alc, text, if_then, NULL));
        }
        else {
            append(stmts, yyfill);
        }
    }

    if (opts->fFlag) {
        text = o.str(opts->yyfilllabel).u32(output.fill_index).flush();
        append(stmts, code_slabel(alc, text));
        ++output.fill_index;
    }

    return stmts;
}

CodeList *gen_rescan_label(Output &output, const State *s)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const char *text;

    CodeList *stmts = code_list(alc);
    if (opts->eof == NOEOF || !opts->fill_use || endstate(s)) {
        // no rescan label
    }
    else {
        text = o.str(opts->yyfilllabel).u32(output.fill_index).flush();
        append(stmts, code_slabel(alc, text));
        ++output.fill_index;
    }

    return stmts;
}

void gen_goto(Output &output, CodeList *stmts, const State *from, const State *to,
    const DFA &dfa, tcid_t tcid, bool skip, bool eof)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const char *text;

    if (eof) {
        append(stmts, gen_on_eof(output, dfa, from, to));
    }

    if (skip && !opts->lookahead) {
        append(stmts, code_skip(alc));
    }

    gen_settags(output, stmts, dfa, tcid, false /* delayed */);

    if (skip && opts->lookahead) {
        append(stmts, code_skip(alc));
    }

    if (to) {
        to->label->used = true;
        text = o.cstr("goto ").str(opts->labelPrefix).label(*to->label).flush();
        append(stmts, code_stmt(alc, text));
    }
}

Code *gen_on_eof(Output &output, const DFA &dfa, const State *from, const State *to)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const bool final = from->rule != Rule::NONE;
    const State *fallback = final ? dfa.finstates[from->rule] : dfa.defstate;
    const tcid_t falltags = final ? from->rule_tags : from->fall_tags;
    uint32_t fillidx = output.fill_index;
    const char *text;

    // check for the end of input
    const char *if_refill = gen_lessthan(o, opts, 1);

    CodeList *refill = code_list(alc);

    // check if refill is needed and invoke YYFILL()
    if (opts->fFlag) {
        --fillidx;

        // YYSETSTATE
        std::string s = opts->state_set;
        strrreplace(s, opts->state_set_arg, fillidx);
        o.str(s);
        if (!opts->state_set_naked) {
            o.cstr("(").u32(fillidx).cstr(");");
        }
        text = o.flush();
        append(refill, code_text(alc, text));

        // YYFILL invocation
        o.str(opts->fill);
        if (!opts->fill_naked) {
            if (opts->fill_arg_use) {
                o.cstr("()");
            }
            o.cstr(";");
        }
        text = o.flush();
        append(refill, code_text(alc, text));

        // yyeof label
        text = o.str(opts->labelPrefix).cstr("eof").u32(fillidx).flush();
        append(refill, code_slabel(alc, text));
        if (fallback == to) {
            // a label must be followed by a statement
            append(refill, code_stmt(alc, ""));
        }

    }
    else if (opts->fill_use) {
        // YYFILL invocation
        o.str(opts->fill);
        if (!opts->fill_naked) {
            if (opts->fill_arg_use) {
                o.cstr(" ()");
            }
            o.cstr(" == 0");
        }
        const char *if_yyfill = o.flush();

        // go to retry label (on YYFILL success)
        CodeList *rescan = code_list(alc);
        text = o.cstr("goto ").str(opts->yyfilllabel).u32(fillidx - 1).flush();
        append(rescan, code_stmt(alc, text));

        append(refill, code_if_then_else(alc, if_yyfill, rescan, NULL));
    }

    // refill failed
    if (from->action.type == Action::INITIAL) {
        // initial state: if accepting, go to eof state, else go to default state
        o.cstr("goto ").str(opts->labelPrefix);
        if (final) {
            fallback->label->used = true;
            o.label(*fallback->label);
        }
        else {
            o.cstr("eofrule").u64(output.blockid());
        }
        text = o.flush();
        append(refill, code_stmt(alc, text));
    }
    else if (fallback != to) {
        // tag actions on the fallback transition
        gen_settags(output, refill, dfa, falltags, false /* delayed */);

        // go to fallback state
        fallback->label->used = true;
        text = o.cstr("goto ").str(opts->labelPrefix).label(*fallback->label).flush();
        append(refill, code_stmt(alc, text));
    }

    return code_if_then_else(alc, if_refill, refill, NULL);
}

void gen_settags(Output &output, CodeList *tag_actions, const DFA &dfa, tcid_t tcid,
    bool delayed)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const bool generic = opts->input_api == INPUT_CUSTOM;
    const std::string &prefix = opts->tags_prefix;
    const std::string &expression = opts->tags_expression;
    const tcmd_t *cmd = dfa.tcpool[tcid];
    const char *text;

    // single tag, backwards compatibility, use context marker
    if (cmd && dfa.oldstyle_ctxmarker) {
        DASSERT(!opts->stadfa);
        if (generic) {
            o.str(opts->yybackupctx).cstr(" ()");
        }
        else {
            o.str(opts->yyctxmarker).cstr(" = ").str(opts->yycursor);
        }
        text = o.flush();
        append(tag_actions, code_stmt(alc, text));
        return;
    }

    for (const tcmd_t *p = cmd; p; p = p->next) {
        const tagver_t l = p->lhs, r = p->rhs, *h = p->history;
        const std::string le = vartag_expr(l, prefix, expression);
        const std::string re = vartag_expr(r, prefix, expression);

        if (tcmd_t::iscopy(p)) {
            // copy command
            text = o.str(le).cstr(" = ").str(re).flush();
            append(tag_actions, code_stmt(alc, text));
        }
        else if (tcmd_t::isadd(p)) {
            // save command with history
            if (l != r) {
                text = o.str(le).cstr(" = ").str(re).flush();
                append(tag_actions, code_stmt(alc, text));
            }
            // history is reversed, so use a statement sublist and prepend
            CodeList *actions = code_list(alc);
            for (; *h != TAGVER_ZERO; ++h) {
                const std::string &action = *h == TAGVER_BOTTOM ? opts->yymtagn
                    : delayed ? opts->yymtagpd : opts->yymtagp;
                if (opts->decorate) {
                    text = o.str(action).cstr(" (").str(le).cstr(")").flush();
                }
                else {
                    std::string s = action;
                    strrreplace(s, "@@", le);
                    text = o.str(s).flush();
                }
                prepend(actions, code_stmt(alc, text));
            }
            append(tag_actions, actions);
        }
        else if (generic) {
            // save command without history; generic API
            const std::string &action = *h == TAGVER_BOTTOM ? opts->yystagn
                : delayed ? opts->yystagpd : opts->yystagp;
            if (opts->decorate) {
                text = o.str(action).cstr(" (").str(le).cstr(")").flush();
            }
            else {
                std::string s = action;
                strrreplace(s, "@@", le);
                text = o.str(s).flush();
            }
            append(tag_actions, code_stmt(alc, text));
        }
        else {
            // save command without history; default API
            Scratchbuf o2(alc);
            for (const tcmd_t *q = p; q && tcmd_t::isset(q); p = q, q = q->next) {
                Scratchbuf &x = q->history[0] == TAGVER_BOTTOM ? o : o2;
                x.str(vartag_expr(q->lhs, prefix, expression)).cstr(" = ");
            }
            if (!o.empty()) {
                text = o.cstr("NULL").flush();
                append(tag_actions, code_stmt(alc, text));
            }
            if (!o2.empty()) {
                text = o2.str(opts->yycursor).cstr(delayed ? " - 1" : "").flush();
                append(tag_actions, code_stmt(alc, text));
            }
        }
    }
}

void gen_fintags(Output &output, CodeList *stmts, const DFA &dfa, const Rule &rule)
{
    const opt_t *opts = output.block().opts;
    const bool generic = opts->input_api == INPUT_CUSTOM;
    const std::string &prefix = opts->tags_prefix;
    const std::string &expression = opts->tags_expression;
    const std::vector<Tag> &tags = dfa.tags;
    const tagver_t *fins = dfa.finvers;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const char *text;
    std::string expr;

    if (rule.ncap > 0) {
        text = o.cstr("yynmatch = ").u64(rule.ncap).flush();
        append(stmts, code_stmt(alc, text));
    }

    // variable tags
    for (size_t t = rule.ltag; t < rule.htag; ++t) {
        const Tag &tag = tags[t];

        // see note [fixed and variable tags]
        if (fictive(tag) || fixed(tag)) continue;

        expr = vartag_expr(fins[t], prefix, expression);
        if (!trailing(tag)) {
            o.str(tag_expr(tag, true)).cstr(" = ").str(expr);
        }
        else if (generic) {
            if (dfa.oldstyle_ctxmarker) {
                o.str(opts->yyrestorectx).cstr(" ()");
            }
            else {
                o.str(opts->yyrestoretag).cstr(" (").str(expr).cstr(")");
            }
        }
        else {
            if (dfa.oldstyle_ctxmarker) {
                o.str(opts->yycursor).cstr(" = ").str(opts->yyctxmarker);
            }
            else {
                o.str(opts->yycursor).cstr(" = ").str(expr);
            }
        }
        text = o.flush();
        append(stmts, code_stmt(alc, text));
    }

    // fixed tags
    for (size_t t = rule.ltag; t < rule.htag; ++t) {
        const Tag &tag = tags[t];

        // see note [fixed and variable tags]
        if (fictive(tag) || !fixed(tag)) continue;

        const size_t dist = tag.dist;
        const bool fixed_on_cursor = tag.base == Tag::RIGHTMOST;
        expr = fixed_on_cursor ? opts->yycursor
            : vartag_expr(fins[tag.base], prefix, expression);
        if (generic) {
            DASSERT(dist == 0);
            if (!trailing(tag)) {
                o.str(tag_expr(tag, true)).cstr(" = ").str(expr);
            }
            else if (!fixed_on_cursor) {
                DASSERT(!dfa.oldstyle_ctxmarker);
                o.str(opts->yyrestoretag).cstr(" (").str(expr).cstr(")");
            }
        }
        else {
            if (!trailing(tag)) {
                o.str(tag_expr(tag, true)).cstr(" = ").str(expr);
                if (dist > 0) o.cstr(" - ").u64(dist);
            }
            else if (!fixed_on_cursor) {
                o.str(opts->yycursor).cstr(" = ").str(expr);
                if (dist > 0) o.cstr(" - ").u64(dist);
            }
            else if (dist > 0) {
                o.str(opts->yycursor).cstr(" -= ").u64(dist);
            }
        }
        text = o.flush();
        append(stmts, code_stmt(alc, text));
    }
}

std::string tag_expr(const Tag &tag, bool lvalue)
{
    DASSERT(!trailing(tag));

    // named tag
    if (!capture(tag)) {
        return *tag.name;
    }

    // capture tag, maps to a range of parentheses
    std::string s = "yypmatch[" + to_string(tag.lsub) + "]";
    if (lvalue) {
        for (size_t i = tag.lsub + 2; i <= tag.hsub; i += 2) {
            s += " = yypmatch[" + to_string(i) + "]";
        }
    }
    return s;
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
        if (opts->decorate) {
            o.str(opts->yylessthan).cstr(" (").u64(n).cstr(")");
        }
        else {
            std::string s = opts->yylessthan;
            const char *arg = o.u64(n).flush();
            strrreplace(s, "@@", arg);
            o.str(s);
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
