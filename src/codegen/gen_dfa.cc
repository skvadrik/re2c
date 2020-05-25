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
#include "src/codegen/code.h"
#include "src/msg/location.h"
#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/skeleton/skeleton.h"
#include "src/util/string_utils.h"


namespace re2c {

static const char *gen_peek_expr(Scratchbuf &o, const opt_t *opts)
{
    if (opts->input_api == INPUT_DEFAULT) {
        o.cstr("*").str(opts->yycursor);
    }
    else {
        o.str(opts->yypeek).cstr(" ()");
    }
    return o.flush();
}

static void emit_state(Output &output, const State *s, CodeList *stmts)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const char *text;

    append(stmts, code_nlabel(alc, s->label));

    if (opts->dFlag && (s->action.type != Action::INITIAL)) {
        text = o.str(opts->yydebug).cstr("(").label(*s->label).cstr(", ")
            .cstr(gen_peek_expr(o, opts)).cstr(")").flush();
        append(stmts, code_stmt(alc, text));
    }
}

static void emit_eof(Output &output, const SemAct *semact, CodeList *stmts)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const char *text;

    if (opts->eof == NOEOF) return;

    // EOF label
    text = o.str(opts->labelPrefix).cstr("eofrule").u64(output.blockid()).flush();
    append(stmts, code_slabel(alc, text));

    // source line directive
    append(stmts, code_line_info_input(alc, semact->loc));

    // user-defined semantic action for EOF rule
    text = o.str(semact->text).flush();
    append(stmts, code_text(alc, text));

    // output line directive
    append(stmts, code_line_info_output(alc));
}

void DFA::emit_body(Output &output, CodeList *stmts) const
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const char *text;

    gen_settags(output, stmts, *this, tags0, false /* delayed */);

    // If DFA has transitions to initial state, then initial state
    // has a piece of code that advances input position. Wee must
    // skip it when entering DFA.
    if (head->label->used) {
        initial_label->used = true;
        text = o.cstr("goto ").str(opts->labelPrefix).label(*initial_label).flush();
        append(stmts, code_stmt(alc, text));
    }

    for (State * s = head; s; s = s->next) {
        emit_state(output, s, stmts);
        emit_action(output, *this, s, stmts);
        gen_go(output, *this, &s->go, s, stmts);
    }

    emit_eof(output, this->eof_action, stmts);
}

void DFA::emit_dot(Output &output, CodeList *program) const
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const char *text;

    if (opts->cFlag) {
        text = o.str(cond).cstr(" -> ").label(*head->label).flush();
        append(program, code_text(alc, text));
    }

    for (State *s = head; s; s = s->next) {
        if (s->action.type == Action::ACCEPT) {
            const accept_t &accs = *s->action.info.accepts;
            for (uint32_t i = 0; i < accs.size(); ++i) {
                text = o.label(*s->label).cstr(" -> ").label(*accs[i].first->label)
                    .cstr(" [label=\"yyaccept=").u32(i).cstr("\"]").flush();
                append(program, code_text(alc, text));
            }
        }
        else if (s->action.type == Action::RULE) {
            const SemAct *semact = rules[s->action.info.rule].semact;
            if (!semact->autogen) {
                text = o.label(*s->label).cstr(" [label=\"")
                    .str(msg.filenames[semact->loc.file]).cstr(":")
                    .u32(semact->loc.line).cstr("\"]").flush();
                append(program, code_text(alc, text));
            }
        }
        gen_go(output, *this, &s->go, s, program);
    }
}

static void gen_goto_start_state(Output &output, const Label *lstart)
{
    OutputBlock &block = output.block();
    if (!block.opts->fFlag) return;

    // Save transition to start label from the initial state dispatch.
    CodeList *goto_start = code_list(output.allocator);
    const char *text = output.scratchbuf.cstr("goto ")
        .str(block.opts->labelPrefix).u32(lstart->index).flush();
    append(goto_start, code_stmt(output.allocator, text));
    block.fill_goto.push_back(goto_start);
}

void gen_code(Output &output, dfas_t &dfas)
{
    OutputBlock &block = output.block();
    const opt_t *opts = block.opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;

    dfas_t::const_iterator i, b = dfas.begin(), e = dfas.end();
    if (b == e) return;

    for (i = b; i != e; ++i) {
        const bool first = i == b;
        const bool first_state = output.label_counter == 0
            || (first && block.is_reuse_block);
        DFA &dfa = *(*i);

        // Start label is needed in `-f` mode: it points to state 0 (the
        // beginning of block, before condition dispatch in `-c` mode).
        if ((opts->startlabel_force && first) || (opts->fFlag && first_state)) {
            dfa.start_label = new_label(alc, output.label_counter++);
            dfa.start_label->used = true;
        }

        // Initial label points to the beginning of the DFA (after condition
        // dispatch in `-c` mode).
        dfa.initial_label = new_label(alc, output.label_counter++);
        dfa.head->action.set_initial();

        for (State *s = dfa.head; s; s = s->next) {
            s->label = new_label(alc, output.label_counter++);
        }

        if (opts->bFlag) {
            dfa.bitmap = code_bitmap(alc, std::min(dfa.ubChar, 256u));
            for (State *s = dfa.head; s; s = s->next) {
                if (s->isBase) {
                    DASSERT(s->next);
                    insert_bitmap(alc, dfa.bitmap, &s->next->go, s);
                }
            }
        }

        for (State *s = dfa.head; s; s = s->next) {
            code_go(alc, &s->go, s, opts, dfa.bitmap);
        }
    }

    CodeList *program = code_list(alc);
    uint32_t ind = 0;

    if (opts->target == TARGET_DOT) {
        append(program, code_text(alc, "digraph re2c {"));
        append(program, code_cond_goto(alc));
        for (i = b; i != e; ++i) {
            (*i)->emit_dot(output, program);
        }
        append(program, code_text(alc, "}"));
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
        bool have_bitmaps = false;

        const char *text;
        CodeList *program1 = code_list(alc);
        for (i = b; i != e; ++i) {
            const bool first = i == b;
            DFA &dfa = *(*i);

            CodeList *bms = opts->bFlag ? gen_bitmap(output, dfa.bitmap) : NULL;
            have_bitmaps |= bms != NULL;

            if (first && opts->fFlag) {
                append(program1, code_newline(alc));
            }

            if (first && !opts->fFlag) {
                append(program1, code_yych_decl(alc));
                append(program1, code_yyaccept_def(alc));
            }

            if (!opts->cFlag && bms) {
                append(program1, bms);
            }

            if (first && opts->cFlag && opts->gFlag) {
                append(program1, code_cond_table(alc));
            }

            if (opts->fFlag && !output.state_goto) {
                append(program1, code_state_goto(alc));
                output.state_goto = true;
            }

            // start label
            if (dfa.start_label) {
                append(program1, code_nlabel(alc, dfa.start_label));
                gen_goto_start_state(output, dfa.start_label);
            }

            // user-defined start label
            if (first && !opts->startlabel.empty()) {
                text = o.str(opts->startlabel).flush();
                append(program1, code_slabel(alc, text));
            }

            if (opts->cFlag && !output.cond_goto) {
                append(program1, code_cond_goto(alc));
                output.cond_goto = true;
            }

            if (opts->cFlag && !dfa.cond.empty()) {
                if (opts->condDivider.length()) {
                    std::string divider = opts->condDivider;
                    strrreplace(divider, opts->condDividerParam, dfa.cond);
                    text = o.str(divider).flush();
                    append(program1, code_textraw(alc, text));
                }
                text = o.str(opts->condPrefix).str(dfa.cond).flush();
                append(program1, code_slabel(alc, text));
            }

            // generate code for DFA
            CodeList *body = code_list(alc);
            dfa.emit_body(output, body);

            if (opts->cFlag && bms) {
                CodeList *block = code_list(alc);
                append(block, bms);
                append(block, body);
                append(program1, code_block(alc, block, CodeBlock::WRAPPED));
            }
            else {
                append(program1, body);
            }
        }

        const bool prolog = (opts->fFlag && opts->gFlag)
            || (!opts->fFlag && (block.used_yyaccept || opts->bEmitYYCh))
            || (!opts->cFlag && have_bitmaps)
            || (opts->cFlag && opts->gFlag);

        append(program, code_newline(alc));
        append(program, code_line_info_output(alc));

        if (prolog) {
            append(program, code_block(alc, program1, CodeBlock::WRAPPED));
        }
        else {
            ind = ind == 0 ? 1 : ind;
            append(program, program1);
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

std::string vartag_expr(tagver_t ver, const opt_t *opts)
{
    const std::string s = vartag_name(ver, opts->tags_prefix);
    std::string e = opts->tags_expression;
    strrreplace(e, opts->placeholder, s);
    return e;
}

} // end namespace re2c
