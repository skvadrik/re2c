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
#include "src/codegen/emit.h"
#include "src/codegen/go.h"
#include "src/codegen/input_api.h"
#include "src/codegen/label.h"
#include "src/codegen/output.h"
#include "src/options/opt.h"
#include "src/debug/debug.h"
#include "src/dfa/tcmd.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/skeleton/skeleton.h"
#include "src/util/string_utils.h"


namespace re2c {

static CodeStmts *need(Output &output, size_t some);
static CodeStmts *gen_rescan_label(Output &output, const State *s);
static void emit_accept(Output &output, CodeStmts *stmts, const DFA &dfa, const accept_t &acc);
static void emit_rule(Output &output, CodeStmts *stmts, const DFA &dfa, size_t rule_idx);
static void gen_fintags(Output &output, CodeStmts *stmts, const DFA &dfa, const Rule &rule);
static CodeStmt *gen_on_eof(Output &output, const DFA &dfa, const State *from, const State *to);

void emit_action(Output &output, const DFA &dfa, const State *s, CodeStmts *stmts)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;

    switch (s->action.type) {
    case Action::MATCH:
        if (!opts->eager_skip) {
            append_stmt(stmts, code_stmt_skip(alc));
        }
        append_stmts(stmts, need(output, s->fill));
        append_stmts(stmts, gen_rescan_label(output, s));
        if (!endstate(s)) {
            append_stmt(stmts, code_stmt_peek(alc));
        }
        break;
    case Action::INITIAL: {
        const Initial &init = *s->action.info.initial;
        const bool backup = init.save != Initial::NOSAVE;
        const bool ul1 = dfa.used_labels.count(s->label);

        if (ul1 && dfa.accepts.size() > 1 && backup) {
            o.str(opts->yyaccept).cstr(" = ").u64(init.save).cstr(";");
            append_stmt(stmts, code_stmt_text(alc, o.flush()));
        }
        if (ul1 && !opts->eager_skip) {
            append_stmt(stmts, code_stmt_skip(alc));
        }
        if (dfa.used_labels.count(init.label)) {
            o.str(opts->labelPrefix).label(init.label).cstr(":");
            append_stmt(stmts, code_stmt_textraw(alc, o.flush()));
        }
        if (opts->dFlag) {
            o.str(opts->yydebug).cstr("(").label(init.label).cstr(", *")
                .str(opts->yycursor).cstr(");");
            append_stmt(stmts, code_stmt_text(alc, o.flush()));
        }
        append_stmts(stmts, need(output, s->fill));
        if (backup) {
            append_stmt(stmts, code_stmt_backup(alc));
        }
        append_stmts(stmts, gen_rescan_label(output, s));
        if (!endstate(s)) {
            append_stmt(stmts, code_stmt_peek(alc));
        }
        break;
    }
    case Action::SAVE:
        if (dfa.accepts.size() > 1) {
            o.str(opts->yyaccept).cstr(" = ").u64(s->action.info.save).cstr(";");
            append_stmt(stmts, code_stmt_text(alc, o.flush()));
        }
        if (!opts->eager_skip) {
            append_stmt(stmts, code_stmt_skip(alc));
        }
        append_stmt(stmts, code_stmt_backup(alc));
        append_stmts(stmts, need(output, s->fill));
        append_stmts(stmts, gen_rescan_label(output, s));
        append_stmt(stmts, code_stmt_peek(alc));
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

static CodeStmts *emit_accept_binary(Output &output, const DFA &dfa, const accept_t &acc,
    size_t l, size_t r)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;

    CodeStmts *stmts = code_stmts(alc);
    if (l < r) {
        const size_t m = (l + r) >> 1;

        o.str(opts->yyaccept).cstr(r == l+1 ? " == " : " <= ").u64(m);
        CodeText if_cond = o.flush();

        CodeStmts *if_then = emit_accept_binary(output, dfa, acc, l, m);
        CodeStmts *if_else = emit_accept_binary(output, dfa, acc, m + 1, r);

        CodeStmt *if_then_else = code_stmt_if_then_else(alc, if_cond, if_then, if_else);
        append_stmt(stmts, if_then_else);
    }
    else {
        gen_goto(output, stmts, NULL, acc[l].first, dfa, acc[l].second, false, false);
    }
    return stmts;
}

void emit_accept(Output &output, CodeStmts *stmts, const DFA &dfa, const accept_t &acc)
{
    const opt_t *opts = output.block().opts;
    const size_t nacc = acc.size();
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;

    if (nacc == 0) return;

    o.str(output_restore(opts));
    append_stmt(stmts, code_stmt_text(alc, o.flush()));

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
        CodeStmts *block = code_stmts(alc);

        o.cstr("static void *").str(opts->yytarget).cstr("[").u64(nacc).cstr("] = {");
        append_stmt(block, code_stmt_text(alc, o.flush()));

        CodeStmts *table = code_stmts(alc);
        for (uint32_t i = 0; i < nacc; ++i) {
            o.cstr("&&").str(opts->labelPrefix).label(acc[i].first->label).cstr(",");
            append_stmt(table, code_stmt_text(alc, o.flush()));
        }
        append_stmt(block, code_block(alc, table, CodeBlock::INDENTED));

        o.cstr("};");
        append_stmt(block, code_stmt_text(alc, o.flush()));

        o.cstr("goto *").str(opts->yytarget).cstr("[").str(opts->yyaccept).cstr("];");
        append_stmt(block, code_stmt_text(alc, o.flush()));

        append_stmt(stmts, code_block(alc, block, CodeBlock::WRAPPED));
        return;
    }

    // nested ifs
    if (opts->sFlag || nacc == 2) {
        append_stmts(stmts, emit_accept_binary(output, dfa, acc, 0, nacc - 1));
        return;
    }

    // switch
    o.str(opts->yyaccept);
    CodeText switch_expr = o.flush();

    CodeCases *switch_cases = code_cases(alc);
    CodeStmts *case_stmts = code_stmts(alc);
    gen_goto(output, case_stmts, NULL, acc[nacc - 1].first, dfa, acc[nacc - 1].second,
        false, false);
    append_case(switch_cases, code_case_number(alc, case_stmts, 0));

    for (uint32_t i = 0; i < nacc - 1; ++i) {
        CodeStmts *case_body = code_stmts(alc);
        gen_goto(output, case_body, NULL, acc[i].first, dfa, acc[i].second,
            false, false);
        append_case(switch_cases,
            code_case_number(alc, case_body, static_cast<int32_t>(i)));
    }

    CodeStmt *cswitch = code_switch(alc, switch_expr, switch_cases, true);
    append_stmt(stmts, cswitch);
}

void emit_rule(Output &output, CodeStmts *stmts, const DFA &dfa, size_t rule_idx)
{
    const opt_t *opts = output.block().opts;
    const Rule &rule = dfa.rules[rule_idx];
    const Code *code = rule.code;
    const std::string &cond = code->cond;

    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    std::string s;

    gen_fintags(output, stmts, dfa, rule);

    if (opts->target == TARGET_SKELETON) {
        emit_skeleton_action(output, stmts, dfa, rule_idx);
    }
    else {
        if (!cond.empty() && dfa.cond != cond) {
            strrreplace(s = opts->cond_set, opts->cond_set_arg,
                opts->condEnumPrefix + cond);
            o.str(s);
            if (!opts->cond_set_naked) {
                o.cstr("(").str(opts->condEnumPrefix).str(cond).cstr(");");
            }
            append_stmt(stmts, code_stmt_text(alc, o.flush()));
        }
        if (!code->autogen) {
            if (!dfa.setup.empty()) {
                o.str(dfa.setup);
                append_stmt(stmts, code_stmt_text(alc, o.flush()));
            }

            append_stmt(stmts, code_line_info_input(alc, code->loc));

            o.str(code->text);
            append_stmt(stmts, code_stmt_text(alc, o.flush()));

            append_stmt(stmts, code_line_info_output(alc));
        }
        else if (!cond.empty()) {
            strrreplace(s = opts->condGoto, opts->condGotoParam,
                opts->condPrefix + cond);
            o.str(s);
            append_stmt(stmts, code_stmt_text(alc, o.flush()));
        }
    }
}

CodeStmts *need(Output &output, size_t some)
{
    const opt_t *opts = output.block().opts;

    if (opts->eof != NOEOF || some == 0) return NULL;

    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    std::string s;

    CodeStmts *stmts = code_stmts(alc);

    if (opts->fFlag) {
        strrreplace(s = opts->state_set, opts->state_set_arg, output.fill_index);
        o.str(s);
        if (!opts->state_set_naked) {
            o.cstr("(").u32(output.fill_index).cstr(");");
        }
        append_stmt(stmts, code_stmt_text(alc, o.flush()));
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
        CodeStmt *yyfill = code_stmt_text(alc, o.flush());

        if (opts->fill_check) {
            o.str(output_expr_lessthan(some, opts));
            CodeText if_cond = o.flush();

            CodeStmts *if_then = code_stmts(alc);
            append_stmt(if_then, yyfill);

            append_stmt(stmts, code_stmt_if_then_else(alc, if_cond, if_then, NULL));
        }
        else {
            append_stmt(stmts, yyfill);
        }
    }

    if (opts->fFlag) {
        o.str(opts->yyfilllabel).u32(output.fill_index).cstr(":");
        append_stmt(stmts, code_stmt_textraw(alc, o.flush()));
        ++output.fill_index;
    }

    return stmts;
}

CodeStmts *gen_rescan_label(Output &output, const State *s)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;

    CodeStmts *stmts = code_stmts(alc);

    if (opts->eof == NOEOF || !opts->fill_use || endstate(s)) {
        // no rescan label
    }
    else if (opts->fFlag) {
        o.str(opts->yyfilllabel).u32(output.fill_index).cstr(":");
        append_stmt(stmts, code_stmt_textraw(alc, o.flush()));

        ++output.fill_index;
    }
    else {
        o.str(opts->labelPrefix).label(s->label).cstr("_:");
        append_stmt(stmts, code_stmt_textraw(alc, o.flush()));
    }

    return stmts;
}

void gen_goto(Output &output, CodeStmts *stmts, const State *from, const State *to,
    const DFA &dfa, tcid_t tcid, bool skip, bool eof)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;

    if (eof) {
        append_stmt(stmts, gen_on_eof(output, dfa, from, to));
    }

    if (skip && !opts->lookahead) {
        output_skip(o.stream(), 0, opts);
        append_stmt(stmts, code_stmt_text(alc, o.flush()));
    }

    gen_settags(output, stmts, dfa, tcid, false /* delayed */);

    if (skip && opts->lookahead) {
        output_skip(o.stream(), 0, opts);
        append_stmt(stmts, code_stmt_text(alc, o.flush()));
    }

    if (to) {
        o.cstr("goto ").str(opts->labelPrefix).label(to->label).cstr(";");
        append_stmt(stmts, code_stmt_text(alc, o.flush()));
    }
}

CodeStmt *gen_on_eof(Output &output, const DFA &dfa, const State *from, const State *to)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const bool final = from->rule != Rule::NONE;
    const State *fallback = final ? dfa.finstates[from->rule] : dfa.defstate;
    const tcid_t falltags = final ? from->rule_tags : from->fall_tags;
    const State *retry = from->action.type == Action::MOVE ? from->prev : from;
    uint32_t fillidx = output.fill_index;

    // check for the end of input
    o.str(output_expr_lessthan(1, opts));
    CodeText if_refill = o.flush();

    CodeStmts *refill = code_stmts(alc);

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
        append_stmt(refill, code_stmt_text(alc, o.flush()));

        // YYFILL invocation
        o.str(opts->fill).cstr(opts->fill_naked ? "" : opts->fill_arg_use ? "();" : ";");
        append_stmt(refill, code_stmt_text(alc, o.flush()));

        // yyeof label
        o.str(opts->labelPrefix).cstr("eof").u32(fillidx).cstr(":;");
        append_stmt(refill, code_stmt_text(alc, o.flush()));

    }
    else if (opts->fill_use) {
        // YYFILL invocation
        o.str(opts->fill).cstr(opts->fill_naked ? "" : opts->fill_arg_use ? " () == 0"
            : " == 0");
        CodeText if_yyfill = o.flush();

        // go to retry label (on YYFILL success)
        CodeStmts *rescan = code_stmts(alc);
        o.cstr("goto ").str(opts->labelPrefix).label(retry->label).cstr("_;");
        append_stmt(rescan, code_stmt_text(alc, o.flush()));

        append_stmt(refill, code_stmt_if_then_else(alc, if_yyfill, rescan, NULL));
    }

    // refill failed
    if (from->action.type == Action::INITIAL) {
        // initial state: if accepting, go to eof state, else go to default state
        o.cstr("goto ").str(opts->labelPrefix);
        if (final) {
            o.label(fallback->label);
        }
        else {
            o.cstr("eofrule").u64(output.blockid());
        }
        o.cstr(";");
        append_stmt(refill, code_stmt_text(alc, o.flush()));
    }
    else if (fallback != to) {
        // tag actions on the fallback transition
        gen_settags(output, refill, dfa, falltags, false /* delayed */);

        // go to fallback state
        o.cstr("goto ").str(opts->labelPrefix).label(fallback->label).cstr(";");
        append_stmt(refill, code_stmt_text(alc, o.flush()));
    }

    return code_stmt_if_then_else(alc, if_refill, refill, NULL);
}

void gen_settags(Output &output, CodeStmts *tag_actions, const DFA &dfa, tcid_t tcid,
    bool delayed)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const bool generic = opts->input_api == INPUT_CUSTOM;
    const std::string &prefix = opts->tags_prefix;
    const std::string &expression = opts->tags_expression;
    const tcmd_t *cmd = dfa.tcpool[tcid];

    // single tag, backwards compatibility, use context marker
    if (cmd && dfa.oldstyle_ctxmarker) {
        DASSERT(!opts->stadfa);
        if (generic) {
            o.str(opts->yybackupctx).cstr(" ();");
        }
        else {
            o.str(opts->yyctxmarker).cstr(" = ").str(opts->yycursor).cstr(";");
        }
        append_stmt(tag_actions, code_stmt_text(alc, o.flush()));
        return;
    }

    for (const tcmd_t *p = cmd; p; p = p->next) {
        const tagver_t l = p->lhs, r = p->rhs, *h = p->history;
        const std::string le = vartag_expr(l, prefix, expression);
        const std::string re = vartag_expr(r, prefix, expression);

        if (tcmd_t::iscopy(p)) {
            // copy command
            o.str(le).cstr(" = ").str(re).cstr(";");
            append_stmt(tag_actions, code_stmt_text(alc, o.flush()));
        }
        else if (tcmd_t::isadd(p)) {
            // save command with history
            if (l != r) {
                o.str(le).cstr(" = ").str(re).cstr(";");
                append_stmt(tag_actions, code_stmt_text(alc, o.flush()));
            }
            // history is reversed, so use a statement sublist and prepend
            CodeStmts *actions = code_stmts(alc);
            for (; *h != TAGVER_ZERO; ++h) {
                const std::string &action = *h == TAGVER_BOTTOM ? opts->yymtagn
                    : delayed ? opts->yymtagpd : opts->yymtagp;
                o.str(action).cstr(" (").str(le).cstr(");");
                prepend_stmt(actions, code_stmt_text(alc, o.flush()));
            }
            append_stmts(tag_actions, actions);
        }
        else if (generic) {
            // save command without history; generic API
            const std::string &action = *h == TAGVER_BOTTOM ? opts->yystagn
                : delayed ? opts->yystagpd : opts->yystagp;
            o.str(action).cstr(" (").str(le).cstr(");");
            append_stmt(tag_actions, code_stmt_text(alc, o.flush()));
        }
        else {
            // save command without history; default API
            Scratchbuf o2(alc);
            for (const tcmd_t *q = p; q && tcmd_t::isset(q); p = q, q = q->next) {
                Scratchbuf &x = q->history[0] == TAGVER_BOTTOM ? o : o2;
                x.str(vartag_expr(q->lhs, prefix, expression)).cstr(" = ");
            }
            if (!o.empty()) {
                o.cstr("NULL;");
                append_stmt(tag_actions, code_stmt_text(alc, o.flush()));
            }
            if (!o2.empty()) {
                o2.str(opts->yycursor).cstr(delayed ? " - 1" : "").cstr(";");
                append_stmt(tag_actions, code_stmt_text(alc, o2.flush()));
            }
        }
    }
}

void gen_fintags(Output &output, CodeStmts *stmts, const DFA &dfa, const Rule &rule)
{
    const opt_t *opts = output.block().opts;
    const bool generic = opts->input_api == INPUT_CUSTOM;
    const std::string &prefix = opts->tags_prefix;
    const std::string &expression = opts->tags_expression;
    std::string expr;
    const std::vector<Tag> &tags = dfa.tags;
    const tagver_t *fins = dfa.finvers;

    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;

    if (rule.ncap > 0) {
        o.cstr("yynmatch = ").u64(rule.ncap).cstr(";");
        append_stmt(stmts, code_stmt_text(alc, o.flush()));
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
        o.cstr(";");
        append_stmt(stmts, code_stmt_text(alc, o.flush()));
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
        o.cstr(";");
        append_stmt(stmts, code_stmt_text(alc, o.flush()));
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
    DASSERT(s->go.nSpans > 0);
    const Action::type_t &a = s->go.span[0].to->action.type;
    return s->go.nSpans == 1
        && (a == Action::RULE || a == Action::ACCEPT);
}

} // namespace re2c
