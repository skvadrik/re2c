#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <algorithm>
#include <ostream>
#include <set>
#include <string>
#include <utility>
#include <valarray>
#include <vector>

#include "src/adfa/action.h"
#include "src/adfa/adfa.h"
#include "src/codegen/bitmap.h"
#include "src/codegen/emit.h"
#include "src/codegen/go.h"
#include "src/codegen/input_api.h"
#include "src/codegen/label.h"
#include "src/codegen/output.h"
#include "src/msg/location.h"
#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/skeleton/skeleton.h"
#include "src/util/counter.h"
#include "src/util/string_utils.h"


namespace re2c {

static void emit_state(Output & o, uint32_t ind, const State * s, bool used_label);
static void emit_eof(Output &, uint32_t, const Code*);

void emit_state (Output & o, uint32_t ind, const State * s, bool used_label)
{
    const opt_t *opts = o.block().opts;
    if (used_label)
    {
        o.wstring(opts->labelPrefix).wlabel(s->label).ws(":\n");
    }
    if (opts->dFlag && (s->action.type != Action::INITIAL))
    {
        o.wind(ind).wstring(opts->yydebug).ws("(").wlabel(s->label).ws(", ").wstring(output_expr_peek(opts)).ws(");\n");
    }
}

void emit_eof(Output & o, uint32_t ind, const Code *code)
{
    const opt_t *opts = o.block().opts;

    if (opts->eof == NOEOF) return;

    o.wstring(opts->labelPrefix).ws("eof:\n");
    o.wdelay_line_info_input(code->loc);
    o.wind(ind).wstring(code->text).ws("\n");
    o.wdelay_line_info_output();
}

void DFA::count_used_labels(std::set<label_t> &used, label_t start
    , label_t initial, const opt_t *opts) const
{
    // In '-f' mode, default state is always state 0
    if (opts->fFlag) {
        used.insert(label_t::first());
    }
    if (opts->startlabel_force && opts->startlabel.empty()) {
        used.insert(start);
    }
    // FIXME: default label may be used by EOF checks, but they are generated
    // later and at this point we do not know if default label is really used
    if (defstate && opts->eof != NOEOF) {
        used.insert(defstate->label);
    }
    for (State * s = head; s; s = s->next) {
        s->go.used_labels(used);
        if (opts->eof != NOEOF && s->rule != Rule::NONE && !endstate(s)) {
            used.insert(finstates[s->rule]->label);
        }
    }
    for (uint32_t i = 0; i < accepts.size(); ++i) {
        used.insert(accepts[i].first->label);
    }
    // must go last: it needs the set of used labels
    if (used.count(head->label)) {
        used.insert(initial);
    }
}

void DFA::emit_body(Output &o, uint32_t& ind,
    const std::set<label_t> &used_labels, label_t initial) const
{
    const opt_t *opts = o.block().opts;

    code_lines_t code;
    gen_settags(code, *this, tags0, opts, false /* delayed */);
    for (size_t i = 0; i < code.size(); ++i) {
        o.wind(ind).wstring(code[i]);
    }

    // If DFA has transitions to initial state, then initial state
    // has a piece of code that advances input position. Wee must
    // skip it when entering DFA.
    if (used_labels.count(head->label)) {
        o.wind(ind).ws("goto ").wstring(opts->labelPrefix)
            .wlabel(initial).ws(";\n");
    }

    for (State * s = head; s; s = s->next) {
        emit_state(o, ind, s, used_labels.count(s->label));
        emit_action(o, ind, *this, s, used_labels);
        s->go.emit(o, ind, *this, s);
    }

    emit_eof(o, ind, this->eof_action);
}

void DFA::emit_dot(Output &o, bool last_cond) const
{
    const opt_t *opts = o.block().opts;
    if (!opts->cFlag || !o.cond_goto) {
        o.ws("digraph re2c {\n");
    }
    o.wdelay_cond_goto(0);
    if (opts->cFlag) {
        o.wstring(cond).ws(" -> ").wlabel(head->label).ws("\n");
    }
    for (State *s = head; s; s = s->next) {
        if (s->action.type == Action::ACCEPT) {
            const accept_t &accs = *s->action.info.accepts;
            for (uint32_t i = 0; i < accs.size(); ++i) {
                o.wlabel(s->label).ws(" -> ")
                    .wlabel(accs[i].first->label)
                    .ws(" [label=\"yyaccept=")
                    .wu32(i).ws("\"]").ws("\n");
            }
        } else if (s->action.type == Action::RULE) {
            const Code *code = rules[s->action.info.rule].code;
            if (!code->autogen) {
                o.wlabel(s->label).ws(" [label=\"")
                    .wstring(msg.filenames[code->loc.file])
                    .ws(":").wu32(code->loc.line)
                    .ws("\"]").ws("\n");
            }
        }
        s->go.emit(o, 0, *this, s);
    }
    if (!opts->cFlag || last_cond) {
        o.ws("}\n");
    }
}

void DFA::emit(Output & output, uint32_t& ind, bool isLastCond, bool& bPrologBrace)
{
    OutputBlock &ob = output.block();
    const opt_t *opts = ob.opts;

    std::set<std::string> stagnames, stagvars, mtagnames, mtagvars;
    if (!oldstyle_ctxmarker) {
        for (size_t i = 0; i < tags.size(); ++i) {
            const Tag &tag = tags[i];
            if (history(tag)) {
                mtagvars.insert(*tag.name);
            } else if (tag.name) {
                stagvars.insert(*tag.name);
            }
        }
        for (tagver_t v = 1; v <= maxtagver; ++v) {
            const std::string s = vartag_name(v, opts->tags_prefix);
            if (mtagvers.find(v) != mtagvers.end()) {
                mtagnames.insert(s);
            } else {
                stagnames.insert(s);
            }
        }
        ob.stags.insert(stagnames.begin(), stagnames.end());
        ob.mtags.insert(mtagnames.begin(), mtagnames.end());
    }
    if (!cond.empty()) output.block().types.push_back(cond);

    bool bProlog = (!opts->cFlag || !output.cond_goto);

    // start_label points to the beginning of current re2c block
    // (prior to condition dispatch in '-c' mode)
    // it can forced by configuration 're2c:startlabel = <integer>;'
    label_t start_label = output.label_counter.next ();
    // initial_label points to the beginning of DFA
    // in '-c' mode this is NOT equal to start_label
    label_t initial_label = bProlog && opts->cFlag
        ? output.label_counter.next ()
        : start_label;
    for (State * s = head; s; s = s->next)
    {
        s->label = output.label_counter.next ();
    }
    std::set<label_t> used_labels;
    count_used_labels (used_labels, start_label, initial_label, opts);

    head->action.set_initial(initial_label);

    if (opts->target == TARGET_SKELETON) {
        if (output.skeletons.insert (name).second)
        {
            emit_start(output, max_fill, max_nmatch, name, key_size, def_rule,
                need_backup, need_accept, oldstyle_ctxmarker,
                stagnames, stagvars, mtagnames, mtagvars, bitmaps);
            uint32_t i = 2;
            emit_body (output, i, used_labels, initial_label);
            emit_end(output, name, need_backup, oldstyle_ctxmarker, mtagnames);
        }
    } else if (opts->target == TARGET_DOT) {
        emit_dot(output, isLastCond);
    } else {
        // Generate prolog
        if (bProlog)
        {
            output.ws("\n").wdelay_line_info_output ();
            if ((!opts->fFlag && ob.used_yyaccept)
            ||  (!opts->fFlag && opts->bEmitYYCh)
            ||  (opts->bFlag && !opts->cFlag && !bitmaps.empty())
            ||  (opts->cFlag && !output.cond_goto && opts->gFlag)
            ||  (opts->fFlag && !output.state_goto && opts->gFlag)
            )
            {
                bPrologBrace = true;
                output.wind(ind++).ws("{\n");
            }
            else if (ind == 0)
            {
                ind = 1;
            }
            if (!opts->fFlag)
            {
                if (opts->bEmitYYCh)
                {
                    output.wind(ind).wstring(opts->yyctype).ws(" ").wstring(opts->yych).ws(";\n");
                }
                output.wdelay_yyaccept_init (ind);
            }
            else
            {
                output.ws("\n");
            }
        }
        if (opts->bFlag && !opts->cFlag)
        {
            bitmaps.gen(output, ind);
        }
        if (bProlog)
        {
            output.wdelay_cond_table(ind);
            output.wdelay_state_goto (ind);
            if (opts->cFlag)
            {
                if (used_labels.count(start_label))
                {
                    output.wstring(opts->labelPrefix).wlabel(start_label).ws(":\n");
                }
            }
            output.wuser_start_label ();
            output.wdelay_cond_goto(ind);
        }
        if (opts->cFlag && !cond.empty())
        {
            if (opts->condDivider.length())
            {
                std::string divider = opts->condDivider;
                strrreplace(divider, opts->condDividerParam, cond);
                output.wstring(divider).ws("\n");
            }
            output.wstring(opts->condPrefix).wstring(cond).ws(":\n");
        }
        if (opts->cFlag && opts->bFlag && !bitmaps.empty())
        {
            output.wind(ind++).ws("{\n");
            bitmaps.gen(output, ind);
        }
        // Generate code
        emit_body (output, ind, used_labels, initial_label);
        if (opts->cFlag && opts->bFlag && !bitmaps.empty())
        {
            output.wind(--ind).ws("}\n");
        }
        // Generate epilog
        if ((!opts->cFlag || isLastCond) && bPrologBrace)
        {
            output.wind(--ind).ws("}\n");
        }
    }
}

std::string vartag_name(tagver_t ver, const std::string &prefix)
{
    std::ostringstream s;
    s << prefix << ver;
    return s.str();
}

std::string vartag_expr(tagver_t ver, const std::string &prefix, const std::string &expression)
{
    const std::string s = vartag_name(ver, prefix);
    std::string e = expression;
    strrreplace(e, "@@", s);
    return e;
}

} // end namespace re2c
