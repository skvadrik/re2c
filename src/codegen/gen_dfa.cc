#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <algorithm>
#include <ostream>
#include <set>
#include <string>
#include <utility>
#include <valarray>
#include <vector>

#include "src/adfa/adfa.h"
#include "src/codegen/code.h"
#include "src/codegen/helpers.h"
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
        o.str(opts->yypeek).cstr("()");
    }
    return o.flush();
}

static void emit_state(Output &output, const State *s, CodeList *stmts)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const char *text;

    if (!opts->loop_switch) {
        append(stmts, code_nlabel(alc, s->label));
    }

    if (opts->dFlag && (s->action.type != Action::INITIAL)) {
        text = o.str(opts->yydebug).cstr("(").label(*s->label).cstr(", ")
            .cstr(gen_peek_expr(o, opts)).cstr(")").flush();
        append(stmts, code_stmt(alc, text));
    }
}

static void gen_storable_state_cases(Output &output, CodeCases *cases)
{
    OutputBlock &block = output.block();
    const opt_t *opts = block.opts;
    code_alc_t &alc = output.allocator;

    if (!opts->fFlag || !opts->loop_switch) return;

    // TODO: If `re2c:eof` is not used, some of these cases are redundant (they contain a
    // single transition to the DFA state that has the corresponding YYFILL invocation).
    for (storable_states_t::const_iterator i = block.fill_goto.begin();
            i != block.fill_goto.end(); ++i) {
        append(cases, code_case_number(alc, i->second, static_cast<int32_t>(i->first)));
    }

    CodeList *start_case = code_list(alc);
    if (opts->lang == LANG_GO) {
        append(start_case, code_stmt(alc, "fallthrough"));
    }
    prepend(cases, code_case_number(alc, start_case, -1));
}

void gen_dfa_as_blocks_with_labels(Output &output, const DFA &dfa, CodeList *stmts)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;

    gen_settags(output, stmts, dfa, dfa.tags0, /*delayed*/ false);

    // If DFA has transitions into the initial state and --eager-skip option is not used,
    // then the initial state must have a YYSKIP statement that must be bypassed when
    // first entering the DFA. With --loop-switch that would be impossible, because there
    // can be no transitions in the middle of a state.
    DASSERT(!opts->loop_switch);
    if (dfa.head->label->used && !opts->eager_skip) {
        dfa.initial_label->used = true;
        o.cstr("goto ").str(opts->labelPrefix).label(*dfa.initial_label);
        append(stmts, code_stmt(alc, o.flush()));
    }

    for (State *s = dfa.head; s; s = s->next) {
        emit_state(output, s, stmts);
        emit_action(output, dfa, s, stmts);
        gen_go(output, dfa, &s->go, s, stmts);
    }
}

void gen_dfa_as_switch_cases(Output &output, DFA &dfa, CodeCases *cases)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;

    DASSERT(opts->loop_switch);
    DASSERT(dfa.tags0 == TCID0);

    for (State *s = dfa.head; s; s = s->next) {
        CodeList *body = code_list(alc);
        emit_state(output, s, body);
        emit_action(output, dfa, s, body);
        gen_go(output, dfa, &s->go, s, body);
        append(cases, code_case_number(alc, body, static_cast<int32_t>(s->label->index)));
    }
}

void wrap_dfas_in_loop_switch(Output &output, CodeList *stmts, CodeCases *cases)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;

    DASSERT(opts->loop_switch);

    CodeList* loop = code_list(alc);
    gen_storable_state_cases(output, cases);
    append(loop, code_switch(alc, opts->yystate.c_str(), cases));
    append(stmts, code_loop(alc, loop));
}

void DFA::emit_dot(Output &output, CodeList *program) const
{
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const char *text;

    if (!cond.empty()) {
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

static inline BlockNameList *block_list_for_implicit_state_goto(code_alc_t &alc,
    const OutputBlock &block)
{
    BlockNameList *p = NULL;
    if (block.kind == INPUT_USE) {
        // For `use:re2c` blocks, link the block to the state switch by the
        // autogenerated block name. Note that it is impossible for the user to
        // do so with a `getstate:re2c` directive, as use blocks do not have a
        // user-defined name and cannot be referenced.
        p = alc.alloct<BlockNameList>(1);
        p->name = copystr(block.name, alc);
        p->next = NULL;
    } else {
        // For non-use blocks do not provide a block list: the autogenerated
        // state switch should include all non-use blocks in the file.
    }
    return p;
}

void gen_code(Output &output, dfas_t &dfas)
{
    OutputBlock &oblock = output.block();
    const opt_t *opts = oblock.opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;

    dfas_t::const_iterator i, b = dfas.begin(), e = dfas.end();
    if (b == e) return;

    // All conditions are named, so it suffices to check the first DFA.
    const bool is_cond_block = !(*b)->cond.empty();

    for (i = b; i != e; ++i) {
        const bool first = i == b;
        DFA &dfa = *(*i);

        if (opts->loop_switch && (first || opts->target == TARGET_SKELETON)) {
            // With loop/switch there are no labels, and each block has its own state
            // switch where all conditions are joined. Restart state counter from zero so
            // that cases start from zero. With skeleton conditions are separate.
            output.label_counter = 0;
        }

        if (!opts->loop_switch) {
            if (first) {
                if (opts->startlabel_force) {
                    // User-enforced start label.
                    dfa.start_label = new_label(alc, output.label_counter++);
                    dfa.start_label->used = true;
                } else if (opts->fFlag) {
                    // Start label is needed in `-f` mode: it points to state 0 (the
                    // beginning of block, before condition dispatch in `-c` mode).
                    dfa.start_label = new_label(alc, output.label_counter++);
                }
                oblock.start_label = dfa.start_label;
            }
            // Initial label points to the beginning of the DFA (after condition
            // dispatch in `-c` mode).
            dfa.initial_label = new_label(alc, output.label_counter++);
            dfa.head->action.set_initial();
        }
        for (State *s = dfa.head; s; s = s->next) {
            s->label = new_label(alc, output.label_counter++);
        }

        // With loop/switch storable states need their own cases in the state switch, as
        // they have some logic on top of transition to the state that invoked YYFILL.
        // Give them continuous indices after the last state index.
        if (opts->loop_switch && opts->fFlag) {
            oblock.fill_index = output.label_counter;
        }

        if (!dfa.cond.empty()) {
            // If loop/switch is used, condition numbers are the numeric indices of their
            // initial DFA state. Otherwise we do not assign explicit numbers, and
            // conditions are implicitly assigned consecutive numbers starting from zero.
            StartCond sc = {dfa.cond, opts->loop_switch ? dfa.head->label->index : 0};
            oblock.conds.push_back(sc);
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
        CodeCases *cases = code_cases(alc);
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
            if (first) {
                append(program1, code_yystate_def(alc));
            }

            if (!is_cond_block && bms) {
                append(program1, bms);
            }

            if (first && is_cond_block && opts->gFlag) {
                append(program1, code_cond_table(alc));
            }

            if (opts->fFlag && !output.state_goto && !opts->loop_switch) {
                append(program1, code_state_goto(alc,
                    block_list_for_implicit_state_goto(alc, oblock)));
                output.state_goto = true;
            }

            // start label
            if (dfa.start_label) {
                append(program1, code_nlabel(alc, dfa.start_label));
            }

            // user-defined start label
            if (first && !opts->startlabel.empty()) {
                text = o.str(opts->startlabel).flush();
                append(program1, code_slabel(alc, text));
            }

            if (is_cond_block && !opts->loop_switch) {
                if (!output.cond_goto) {
                    append(program1, code_cond_goto(alc));
                    output.cond_goto = true;
                }
                if (opts->condDivider.length()) {
                    o.str(opts->condDivider);
                    argsubst(o.stream(), opts->condDividerParam, "cond", true, dfa.cond);
                    append(program1, code_textraw(alc, o.flush()));
                }
                text = o.str(opts->condPrefix).str(dfa.cond).flush();
                append(program1, code_slabel(alc, text));
            }

            if (!opts->loop_switch) {
                // In the goto/label mode, generate DFA states as blocks of code preceded
                // with labels, and `goto` transitions between states.
                CodeList *body = code_list(alc);
                gen_dfa_as_blocks_with_labels(output, dfa, body);
                if (is_cond_block && bms) {
                    CodeList *block = code_list(alc);
                    append(block, bms);
                    append(block, body);
                    append(program1, code_block(alc, block, CodeBlock::WRAPPED));
                } else {
                    append(program1, body);
                }
            } else {
                // In the loop/switch mode append all DFA states as cases of the `yystate`
                // switch. Merge DFAs for different conditions together in one switch.
                DASSERT(!bms);
                gen_dfa_as_switch_cases(output, dfa, cases);
            }
        }
        if (opts->loop_switch) {
            wrap_dfas_in_loop_switch(output, program1, cases);
        }

        const bool prolog = (opts->fFlag && opts->gFlag)
            || (!opts->fFlag && (oblock.used_yyaccept || opts->bEmitYYCh))
            || (!is_cond_block && have_bitmaps)
            || (is_cond_block && opts->gFlag);

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
    std::ostringstream os(opts->tags_expression);
    argsubst(os, opts->api_sigil, "tag", true, vartag_name(ver, opts->tags_prefix));
    return os.str();
}

} // end namespace re2c
