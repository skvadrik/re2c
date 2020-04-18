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

static void emit_state(Output &output, const State *s, bool used_label, CodeStmts *stmts)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;

    if (used_label) {
        o.str(opts->labelPrefix).label(s->label).cstr(":");
        append_stmt(stmts, code_stmt_textraw(alc, o.flush()));
    }
    if (opts->dFlag && (s->action.type != Action::INITIAL)) {
        o.str(opts->yydebug).cstr("(").label(s->label).cstr(", ").str(output_expr_peek(opts))
            .cstr(");");
        append_stmt(stmts, code_stmt_text(alc, o.flush()));
    }
}

static void emit_eof(Output &output, const Code *code, CodeStmts *stmts)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;

    if (opts->eof == NOEOF) return;

    // EOF label
    o.str(opts->labelPrefix).cstr("eofrule").u64(output.blockid()).cstr(":");
    append_stmt(stmts, code_stmt_textraw(alc, o.flush()));

    // source line directive
    append_stmt(stmts, code_line_info_input(alc, code->loc));

    // user-defined semantic action for EOF rule
    o.str(code->text);
    append_stmt(stmts, code_stmt_text(alc, o.flush()));

    // output line directive
    append_stmt(stmts, code_line_info_output(alc));
}

void DFA::count_used_labels(const opt_t *opts)
{
    // In '-f' mode, default state is always state 0
    if (opts->fFlag) {
        used_labels.insert(label_t::first());
    }
    if (opts->startlabel_force && opts->startlabel.empty()) {
        used_labels.insert(start_label);
    }
    // FIXME: default label may be used by EOF checks, but they are generated
    // later and at this point we do not know if default label is really used
    if (defstate && opts->eof != NOEOF) {
        used_labels.insert(defstate->label);
    }
    for (State * s = head; s; s = s->next) {
        s->go.used_labels(used_labels);
        if (opts->eof != NOEOF && s->rule != Rule::NONE && !endstate(s)) {
            used_labels.insert(finstates[s->rule]->label);
        }
    }
    for (uint32_t i = 0; i < accepts.size(); ++i) {
        used_labels.insert(accepts[i].first->label);
    }
    // must go last: it needs the set of used labels
    if (used_labels.count(head->label)) {
        used_labels.insert(initial_label);
    }
}

void DFA::emit_body(Output &output, CodeStmts *stmts) const
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;

    gen_settags(output, stmts, *this, tags0, false /* delayed */);

    // If DFA has transitions to initial state, then initial state
    // has a piece of code that advances input position. Wee must
    // skip it when entering DFA.
    if (used_labels.count(head->label)) {
        o.cstr("goto ").str(opts->labelPrefix).label(initial_label).cstr(";");
        append_stmt(stmts, code_stmt_text(alc, o.flush()));
    }

    for (State * s = head; s; s = s->next) {
        emit_state(output, s, used_labels.count(s->label), stmts);
        emit_action(output, *this, s, stmts);
        s->go.emit(output, *this, s, stmts);
    }

    emit_eof(output, this->eof_action, stmts);
}

void DFA::emit_dot(Output &output, CodeStmts *program) const
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;

    if (opts->cFlag) {
        o.str(cond).cstr(" -> ").label(head->label);
        append_stmt(program, code_stmt_text(alc, o.flush()));
    }

    for (State *s = head; s; s = s->next) {
        if (s->action.type == Action::ACCEPT) {
            const accept_t &accs = *s->action.info.accepts;
            for (uint32_t i = 0; i < accs.size(); ++i) {
                o.label(s->label).cstr(" -> ").label(accs[i].first->label)
                    .cstr(" [label=\"yyaccept=").u32(i).cstr("\"]");
                append_stmt(program, code_stmt_text(alc, o.flush()));
            }
        }
        else if (s->action.type == Action::RULE) {
            const Code *action = rules[s->action.info.rule].code;
            if (!action->autogen) {
                o.label(s->label).cstr(" [label=\"")
                    .str(msg.filenames[action->loc.file]).cstr(":")
                    .u32(action->loc.line).cstr("\"]");
                append_stmt(program, code_stmt_text(alc, o.flush()));
            }
        }
        s->go.emit(output, *this, s, program);
    }
}

void gen_code(Output &output, dfas_t &dfas)
{
    OutputBlock &ob = output.block();
    const opt_t *opts = ob.opts;

    dfas_t::const_iterator i, b = dfas.begin(), e = dfas.end();
    if (b == e) return;

    for (i = b; i != e; ++i) {
        const bool first = i == b;
        DFA &dfa = *(*i);

        // start_label points to the beginning of current re2c block
        // (prior to condition dispatch in '-c' mode)
        // it can forced by configuration 're2c:startlabel = <integer>;'
        dfa.start_label = output.label_counter.next();

        // initial_label points to the beginning of DFA
        // in '-c' mode this is NOT equal to start_label
        // TODO: remove special case for skeleton and fix test results.
        dfa.initial_label = opts->cFlag && (first || opts->target == TARGET_SKELETON)
            ? output.label_counter.next () : dfa.start_label;

        for (State * s = dfa.head; s; s = s->next) {
            s->label = output.label_counter.next();
        }

        dfa.count_used_labels(opts);

        dfa.head->action.set_initial(dfa.initial_label);
    }

    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    CodeStmts *program = code_stmts(alc);
    uint32_t ind = 0;

    if (opts->target == TARGET_DOT) {
        o.cstr("digraph re2c {");
        append_stmt(program, code_stmt_text(alc, o.flush()));
        append_stmt(program, code_cond_goto(alc));
        for (i = b; i != e; ++i) {
            (*i)->emit_dot(output, program);
        }
        o.cstr("}");
        append_stmt(program, code_stmt_text(alc, o.flush()));
    }
    else if (opts->target == TARGET_SKELETON) {
        for (i = b; i != e; ++i) {
            DFA &dfa = *(*i);
            if (output.skeletons.insert(dfa.name).second) {
                emit_skeleton(output, program, dfa);
            }
        }
    }
    else {
        ind = output.block().opts->topIndent;

        CodeStmts *program1 = code_stmts(alc);
        for (i = b; i != e; ++i) {
            const bool first = i == b;
            DFA &dfa = *(*i);

            CodeStmts *bms = dfa.bitmaps.gen(output);

            if (first && opts->fFlag) {
                append_stmt(program1, code_stmt_textraw(alc, ""));
            }

            if (first && !opts->fFlag) {
                append_stmt(program1, code_yych_decl(alc));
                append_stmt(program1, code_yyaccept_def(alc));
            }

            if (!opts->cFlag) {
                append_stmts(program1, bms);
            }

            if (first && opts->cFlag && opts->gFlag) {
                append_stmt(program1, code_cond_table(alc));
            }

            if (opts->fFlag && !output.state_goto) {
                append_stmt(program1, code_state_goto(alc));
                output.state_goto = true;
            }

            // start label
            if (first && opts->cFlag && dfa.used_labels.count(dfa.start_label)) {
                o.str(opts->labelPrefix).label(dfa.start_label).cstr(":");
                append_stmt(program1, code_stmt_textraw(alc, o.flush()));
            }

            // user-defined start label
            if (first && !opts->startlabel.empty()) {
                o.str(opts->startlabel).cstr(":");
                append_stmt(program1, code_stmt_textraw(alc, o.flush()));
            }

            if (opts->cFlag && !output.cond_goto) {
                append_stmt(program1, code_cond_goto(alc));
                output.cond_goto = true;
            }

            if (opts->cFlag && !dfa.cond.empty()) {
                if (opts->condDivider.length()) {
                    std::string divider = opts->condDivider;
                    strrreplace(divider, opts->condDividerParam, dfa.cond);
                    o.str(divider);
                    append_stmt(program1, code_stmt_textraw(alc, o.flush()));
                }
                o.str(opts->condPrefix).str(dfa.cond).cstr(":");
                append_stmt(program1, code_stmt_textraw(alc, o.flush()));
            }

            // generate code for DFA
            CodeStmts *body = code_stmts(alc);
            dfa.emit_body(output, body);

            // TODO: instead of rechecking bitmap-related conditions, just check if
            // the code for bitmaps is NULL (requires trivial changes in tests)
            if (opts->cFlag && opts->bFlag && !dfa.bitmaps.empty()) {
                CodeStmts *block = code_stmts(alc);
                append_stmts(block, bms);
                append_stmts(block, body);
                append_stmt(program1, code_block(alc, block, CodeBlock::WRAPPED));
            }
            else {
                append_stmts(program1, body);
            }
        }

        bool have_bitmaps = false;
        for (i = b; i != e; ++i) {
            have_bitmaps |= !(*i)->bitmaps.empty();
        }
        const bool prolog = (opts->fFlag && opts->gFlag)
            || (!opts->fFlag && (ob.used_yyaccept || opts->bEmitYYCh))
            || (opts->bFlag && !opts->cFlag && have_bitmaps)
            || (opts->cFlag && opts->gFlag);

        append_stmt(program, code_stmt_textraw(alc, ""));
        append_stmt(program, code_line_info_output(alc));

        if (prolog) {
            append_stmt(program, code_block(alc, program1, CodeBlock::WRAPPED));
        }
        else {
            ind = ind == 0 ? 1 : ind;
            append_stmts(program, program1);
        }
    }

    output.wdelay_stmt(ind, code_block(alc, program, CodeBlock::RAW));
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
