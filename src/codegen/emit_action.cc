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

static void need               (Output &o, uint32_t ind, size_t some);
static void gen_rescan_label   (Output &o, const State *s);
static void emit_accept_binary (Output &o, uint32_t ind, const DFA &dfa, const accept_t &acc, size_t l, size_t r);
static void emit_accept        (Output &o, uint32_t ind, const DFA &dfa, const accept_t &acc);
static void emit_rule          (Output &o, uint32_t ind, const DFA &dfa, size_t rule_idx);
static void gen_fintags        (Output &o, uint32_t ind, const DFA &dfa, const Rule &rule);
static void gen_goto           (code_lines_t &, const State *, const State *, const DFA &, tcid_t, const opt_t *, bool, bool, uint32_t);
static void gen_on_eof         (code_lines_t &, const opt_t *, const DFA &, const State *, const State *, uint32_t);
static void gen_on_eof_fail    (code_lines_t &, const opt_t *, const DFA &, const State *, const State *, std::ostringstream &);
static void flushln            (code_lines_t &code, std::ostringstream &o);

void emit_action(Output &o, uint32_t ind, const DFA &dfa,
    const State *s, const std::set<label_t> &used_labels)
{
    const opt_t *opts = o.block().opts;
    switch (s->action.type) {
    case Action::MATCH:
        o.wdelay_skip(ind, !opts->eager_skip);
        need(o, ind, s->fill);
        gen_rescan_label(o, s);
        o.wdelay_peek(ind, !endstate(s));
        break;
    case Action::INITIAL: {
        const Initial &init = *s->action.info.initial;
        const bool
            backup = init.save != Initial::NOSAVE,
            ul1 = used_labels.count(s->label);
        if (ul1 && dfa.accepts.size() > 1 && backup) {
            o.wind(ind).wstring(opts->yyaccept).ws(" = ").wu64(init.save).ws(";\n");
        }
        o.wdelay_skip(ind, ul1 && !opts->eager_skip);
        if (used_labels.count(init.label)) {
            o.wstring(opts->labelPrefix).wlabel(init.label).wstring(":\n");
        }
        if (opts->dFlag) {
            o.wind(ind).wstring(opts->yydebug).ws("(").wlabel(init.label)
                .ws(", *").wstring(opts->yycursor).ws(");\n");
        }
        need(o, ind, s->fill);
        o.wdelay_backup(ind, backup);
        gen_rescan_label(o, s);
        o.wdelay_peek(ind, !endstate(s));
        break;
    }
    case Action::SAVE:
        if (dfa.accepts.size() > 1) {
            o.wind(ind).wstring(opts->yyaccept).ws(" = ").wu64(s->action.info.save).ws(";\n");
        }
        o.wdelay_skip(ind, !opts->eager_skip);
        o.wdelay_backup(ind, true);
        need(o, ind, s->fill);
        gen_rescan_label(o, s);
        o.wdelay_peek(ind, true);
        break;
    case Action::MOVE:
        break;
    case Action::ACCEPT:
        emit_accept(o, ind, dfa, *s->action.info.accepts);
        break;
    case Action::RULE:
        emit_rule(o, ind, dfa, s->action.info.rule);
        break;
    }
}

void emit_accept_binary(Output &o, uint32_t ind, const DFA &dfa,
    const accept_t &acc, size_t l, size_t r)
{
    const opt_t *opts = o.block().opts;
    if (l < r) {
        const size_t m = (l + r) >> 1;
        o.wind(ind).ws("if (").wstring(opts->yyaccept)
            .ws(r == l+1 ? " == " : " <= ").wu64(m).ws(") {\n");
        emit_accept_binary (o, ++ind, dfa, acc, l, m);
        o.wind(--ind).ws("} else {\n");
        emit_accept_binary (o, ++ind, dfa, acc, m + 1, r);
        o.wind(--ind).ws("}\n");
    } else {
        gen_goto_plain(o, ind, NULL, acc[l].first, dfa, acc[l].second, false, false);
    }
}

void emit_accept(Output &o, uint32_t ind, const DFA &dfa, const accept_t &acc)
{
    const opt_t *opts = o.block().opts;
    const size_t nacc = acc.size();

    if (nacc == 0) return;

    o.wstring(output_restore(ind, opts));

    // only one possible 'yyaccept' value: unconditional jump
    if (nacc == 1) {
        gen_goto_plain(o, ind, NULL, acc[0].first, dfa, acc[0].second, false, false);
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
        o.wind(ind).ws("{\n")
            .wind(ind + 1).ws("static void *")
            .wstring(opts->yytarget).ws("[")
            .wu64(nacc).ws("] = {\n");
        for (uint32_t i = 0; i < nacc; ++i) {
            o.wind(ind + 2).ws("&&").wstring(opts->labelPrefix)
                .wlabel(acc[i].first->label).ws(",\n");
        }
        o.wind(ind + 1).ws("};\n")
            .wind(ind + 1).ws("goto *")
            .wstring(opts->yytarget).ws("[")
            .wstring(opts->yyaccept).ws("];\n")
            .wind(ind).ws("}\n");
        return;
    }

    // nested ifs
    if (opts->sFlag || nacc == 2) {
        emit_accept_binary(o, ind, dfa, acc, 0, nacc - 1);
        return;
    }

    // switch
    o.wind(ind).ws("switch (").wstring(opts->yyaccept).ws(") {\n");
    for (uint32_t i = 0; i < nacc - 1; ++i) {
        o.wind(ind).ws("case ").wu32(i).ws(": ");
        gen_goto_case(o, ind, NULL, acc[i].first, dfa, acc[i].second, false, false);
    }
    o.wind(ind).ws("default:");
    gen_goto_case(o, ind, NULL, acc[nacc - 1].first, dfa, acc[nacc - 1].second, false, false);
    o.wind(ind).ws("}\n");
}

void emit_rule(Output &o, uint32_t ind, const DFA &dfa, size_t rule_idx)
{
    const opt_t *opts = o.block().opts;
    const Rule &rule = dfa.rules[rule_idx];
    const Code *code = rule.code;
    const std::string &cond = code->cond;
    std::string s;

    gen_fintags(o, ind, dfa, rule);

    if (opts->target == TARGET_SKELETON) {
        emit_action(o, ind, dfa, rule_idx);
    } else {
        if (!cond.empty() && dfa.cond != cond) {
            strrreplace(s = opts->cond_set, opts->cond_set_arg, opts->condEnumPrefix + cond);
            o.wind(ind).wstring(s);
            if (!opts->cond_set_naked) {
                o.ws("(").wstring(opts->condEnumPrefix).wstring(cond).ws(");");
            }
            o.ws("\n");
        }
        if (!code->autogen) {
            if (!dfa.setup.empty()) {
                o.wind(ind).wstring(dfa.setup).ws("\n");
            }
            o.wdelay_line_info_input(code->loc)
                .wind(ind).wstring(code->text).ws("\n")
                .wdelay_line_info_output();
        } else if (!cond.empty()) {
            strrreplace(s = opts->condGoto, opts->condGotoParam, opts->condPrefix + cond);
            o.wind(ind).wstring(s).ws("\n");
        }
    }
}

void need(Output &o, uint32_t ind, size_t some)
{
    const opt_t *opts = o.block().opts;
    std::string s;

    if (opts->eof != NOEOF || some == 0) return;

    if (opts->fFlag) {
        strrreplace(s = opts->state_set, opts->state_set_arg, o.fill_index);
        o.wind(ind).wstring(s);
        if (!opts->state_set_naked) {
            o.ws("(").wu32(o.fill_index).ws(");");
        }
        o.ws("\n");
    }

    if (opts->fill_use) {
        o.wind(ind);
        if (opts->fill_check) {
            o.ws("if (").wstring(output_expr_lessthan(some, opts)).ws(") ");
        }
        strrreplace(s = opts->fill, opts->fill_arg, some);
        o.wstring(s);
        if (!opts->fill_naked) {
            if (opts->fill_arg_use) {
                o.ws("(").wu64(some).ws(")");
            }
            o.ws(";");
        }
        o.ws("\n");
    }

    if (opts->fFlag) {
        o.wstring(opts->yyfilllabel).wu32(o.fill_index).ws(":\n");
        ++o.fill_index;
    }
}

void gen_rescan_label(Output &o, const State *s)
{
    const opt_t *opts = o.block().opts;
    if (opts->eof == NOEOF || !opts->fill_use || endstate(s)) {
        // no rescan label
    }
    else if (opts->fFlag) {
        o.wstring(opts->yyfilllabel).wu32(o.fill_index).ws(":\n");
        ++o.fill_index;
    }
    else {
        o.wstring(opts->labelPrefix).wlabel(s->label).ws("_:\n");
    }
}

void gen_goto_case(Output &o, uint32_t ind, const State *from, const State *to,
    const DFA &dfa, tcid_t tcid, bool skip, bool eof)
{
    code_lines_t code;
    gen_goto(code, from, to, dfa, tcid, o.block().opts, skip, eof, o.fill_index);
    const size_t lines = code.size();

    if (lines == 1) {
        o.wind(1).wstring(code[0]);
    } else {
        o.ws("\n");
        for (size_t i = 0; i < lines; ++i) {
            o.wind(ind + 1).wstring(code[i]);
        }
    }
}

void gen_goto_if(Output &o, uint32_t ind, const State *from, const State *to,
    const DFA &dfa, tcid_t tcid, bool skip, bool eof)
{
    code_lines_t code;
    gen_goto(code, from, to, dfa, tcid, o.block().opts, skip, eof, o.fill_index);
    const size_t lines = code.size();

    if (lines == 1) {
        o.wstring(code[0]);
    } else {
        o.ws("{\n");
        for (size_t i = 0; i < lines; ++i) {
            o.wind(ind + 1).wstring(code[i]);
        }
        o.wind(ind).ws("}\n");
    }
}

void gen_goto_plain(Output &o, uint32_t ind, const State *from, const State *to,
    const DFA &dfa, tcid_t tcid, bool skip, bool eof)
{
    code_lines_t code;
    gen_goto(code, from, to, dfa, tcid, o.block().opts, skip, eof, o.fill_index);
    const size_t lines = code.size();

    for (size_t i = 0; i < lines; ++i) {
        o.wind(ind).wstring(code[i]);
    }
}

void gen_goto(code_lines_t &code, const State *from, const State *to
    , const DFA &dfa, tcid_t tcid, const opt_t *opts, bool skip, bool eof
    , uint32_t fillidx)
{
    if (eof) {
        gen_on_eof(code, opts, dfa, from, to, fillidx);
    }

    if (skip && !opts->lookahead) {
        std::ostringstream o;
        output_skip(o, 0, opts);
        code.push_back(o.str());
    }

    gen_settags(code, dfa, tcid, opts, false /* delayed */);

    if (skip && opts->lookahead) {
        std::ostringstream o;
        output_skip(o, 0, opts);
        code.push_back(o.str());
    }

    if (to) {
        code.push_back("goto " + opts->labelPrefix
            + to_string(to->label) + ";\n");
    }
}

void gen_on_eof_fail(code_lines_t &code, const opt_t *opts, const DFA &dfa
    , const State *from, const State *to, std::ostringstream &o)
{
    const bool final = from->rule != Rule::NONE;
    const State *fallback = final ? dfa.finstates[from->rule] : dfa.defstate;
    const tcid_t falltags = final ? from->rule_tags : from->fall_tags;

    if (from->action.type == Action::INITIAL) {
        o << opts->indString << "goto " << opts->labelPrefix;
        if (final) {
            o << fallback->label;
        }
        else {
            o << "eof";
        }
        o << ";";
        flushln(code, o);
    }
    else if (fallback != to) {
        code_lines_t tagcode;
        gen_settags(tagcode, dfa, falltags, opts, false /* delayed */);

        if (tagcode.empty()) {
            o << opts->indString
                << "goto " << opts->labelPrefix << fallback->label << ";";
            flushln(code, o);
        }
        else {
            for (uint32_t i = 0; i < tagcode.size(); ++i) {
                code.push_back(opts->indString + tagcode[i]);
            }
            o << opts->indString
                << "goto " << opts->labelPrefix << fallback->label << ";";
            flushln(code, o);
        }
    }
}

void gen_on_eof(code_lines_t &code, const opt_t *opts, const DFA &dfa
    , const State *from, const State *to, uint32_t fillidx)
{
    const State *retry = from->action.type == Action::MOVE ? from->prev : from;
    std::ostringstream o;

    o << "if (" << output_expr_lessthan(1, opts) << ") {";
    flushln(code, o);

    if (opts->fFlag) {
        --fillidx;
        std::string s = opts->state_set;
        strrreplace(s, opts->state_set_arg, fillidx);
        o << opts->indString << s;
        if (!opts->state_set_naked) {
            o << "(" << fillidx << ");";
        }
        flushln(code, o);

        o << opts->indString << opts->fill
            << (opts->fill_naked ? "" : opts->fill_arg_use ? "();" : ";");
        flushln(code, o);

        o << opts->indString << opts->labelPrefix << "eof" << fillidx << ":;";
        flushln(code, o);

        gen_on_eof_fail(code, opts, dfa, from, to, o);
    }
    else {
        if (opts->fill_use) {
            o << opts->indString << "if (" << opts->fill
                << (opts->fill_naked ? ""
                    : opts->fill_arg_use ? " () == 0" : " == 0")
                << ") goto " << opts->labelPrefix << retry->label << "_;";
            flushln(code, o);
        }
        gen_on_eof_fail(code, opts, dfa, from, to, o);
    }

    o << "}";
    flushln(code, o);
}

void gen_settags(code_lines_t &code, const DFA &dfa, tcid_t tcid,
    const opt_t *opts, bool delayed)
{
    const bool generic = opts->input_api == INPUT_CUSTOM;
    const std::string
        &prefix = opts->tags_prefix,
        &expression = opts->tags_expression;
    const tcmd_t *cmd = dfa.tcpool[tcid];

    // single tag YYCTXMARKER, backwards compatibility
    if (cmd && dfa.oldstyle_ctxmarker) {
        DASSERT(!opts->stadfa);

        const std::string s = generic
            ? opts->yybackupctx + " ();\n"
            : opts->yyctxmarker + " = " + opts->yycursor + ";\n";
        code.push_back(s);
        return;
    }

    for (const tcmd_t *p = cmd; p; p = p->next) {
        const tagver_t l = p->lhs, r = p->rhs, *h = p->history;

        // copy command
        if (tcmd_t::iscopy(p)) {
            const std::string
                le = vartag_expr(l, prefix, expression),
                re = vartag_expr(r, prefix, expression),
                s = le + " = " + re + ";\n";
            code.push_back(s);

        // save command; history
        } else if (tcmd_t::isadd(p)) {
            const std::string
                le = vartag_expr(l, prefix, expression),
                re = vartag_expr(r, prefix, expression);
            if (l != r) {
                const std::string s = le + " = " + re + ";\n";
                code.push_back(s);
            }
            code_lines_t code1;
            for (; *h != TAGVER_ZERO; ++h) {
                const std::string s = *h == TAGVER_BOTTOM
                    ? opts->yymtagn + " (" + le + ");\n"
                    : (delayed ? opts->yymtagpd : opts->yymtagp)
                        + " (" + le + ");\n";
                code1.push_back(s);
            }
            code.insert(code.end(), code1.rbegin(), code1.rend());

        // save command; no history; generic API
        } else if (generic) {
            const std::string
                v = vartag_expr(l, prefix, expression),
                s = *h == TAGVER_BOTTOM
                    ? opts->yystagn + " (" + v + ");\n"
                    : (delayed ? opts->yystagpd : opts->yystagp)
                        + " (" + v + ");\n";
            code.push_back(s);

        // save command; no history; default API
        } else {
            std::string s1 = "", s2 = "";
            for (const tcmd_t *q = p; q && tcmd_t::isset(q); p = q, q = q->next) {
                std::string &s = q->history[0] == TAGVER_BOTTOM ? s1 : s2;
                s += vartag_expr(q->lhs, prefix, expression) + " = ";
            }
            if (!s1.empty()) {
                s1 += "NULL;\n";
                code.push_back(s1);
            }
            if (!s2.empty()) {
                s2 += opts->yycursor + (delayed ? " - 1" : "") + ";\n";
                code.push_back(s2);
            }
        }
    }
}

void gen_fintags(Output &o, uint32_t ind, const DFA &dfa, const Rule &rule)
{
    const opt_t *opts = o.block().opts;
    const bool generic = opts->input_api == INPUT_CUSTOM;
    const std::string
        &prefix = opts->tags_prefix,
        &expression = opts->tags_expression;
    std::string expr;
    const std::vector<Tag> &tags = dfa.tags;
    const tagver_t *fins = dfa.finvers;

    if (rule.ncap > 0) {
        o.wind(ind).ws("yynmatch = ").wu64(rule.ncap).ws(";\n");
    }

    // variable tags
    for (size_t t = rule.ltag; t < rule.htag; ++t) {
        const Tag &tag = tags[t];

        // see note [fixed and variable tags]
        if (fictive(tag) || fixed(tag)) continue;

        expr = vartag_expr(fins[t], prefix, expression);

        o.wind(ind);
        if (!trailing(tag)) {
            o.wstring(tag_expr(tag, true)).ws(" = ").wstring(expr);
        } else if (generic) {
            if (dfa.oldstyle_ctxmarker) {
                o.wstring(opts->yyrestorectx).ws(" ()");
            } else {
                o.wstring(opts->yyrestoretag).ws(" (").wstring(expr).ws(")");
            }
        } else {
            if (dfa.oldstyle_ctxmarker) {
                o.wstring(opts->yycursor).ws(" = ").wstring(opts->yyctxmarker);
            } else {
                o.wstring(opts->yycursor).ws(" = ").wstring(expr);
            }
        }
        o.ws(";\n");
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

        o.wind(ind);
        if (generic) {
            DASSERT(dist == 0);
            if (!trailing(tag)) {
                o.wstring(tag_expr(tag, true)).ws(" = ").wstring(expr);
            } else if (!fixed_on_cursor) {
                DASSERT(!dfa.oldstyle_ctxmarker);
                o.wstring(opts->yyrestoretag).ws(" (").wstring(expr).ws(")");
            }
        } else {
            if (!trailing(tag)) {
                o.wstring(tag_expr(tag, true)).ws(" = ").wstring(expr);
                if (dist > 0) o.ws(" - ").wu64(dist);
            } else if (!fixed_on_cursor) {
                o.wstring(opts->yycursor).ws(" = ").wstring(expr);
                if (dist > 0) o.ws(" - ").wu64(dist);
            } else if (dist > 0) {
                o.wstring(opts->yycursor).ws(" -= ").wu64(dist);
            }
        }
        o.ws(";\n");
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

void flushln(code_lines_t &code, std::ostringstream &o)
{
    o << "\n";
    code.push_back(o.str());
    o.str("");
    o.clear();
}

} // namespace re2c
