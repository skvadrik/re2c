#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <ostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "src/adfa/adfa.h"
#include "src/codegen/output.h"
#include "src/codegen/helpers.h"
#include "src/msg/location.h"
#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/skeleton/skeleton.h"
#include "src/util/check.h"
#include "src/util/string_utils.h"

namespace re2c {

void gen_yydebug(Output& output, const Label* label, CodeList* stmts) {
    const opt_t* opts = output.block().opts;
    Scratchbuf& buf = output.scratchbuf;

    if (!opts->debug) return;

    // The label may be unused but still have a valid index (one such example is the initial label
    // in goto/label mode). It still needs an YYDEBUG statement.
    buf.str(opts->api_debug).cstr("(").unchecked_label(*label).cstr(", ");
    gen_peek_expr(buf.stream(), opts);
    buf.cstr(")");
    append(stmts, code_stmt(output.allocator, buf.flush()));
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
    if (dfa.head->label->used && !opts->eager_skip) {
        dfa.initial_label->used = true;
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
    if (opts->state_abort || opts->lang != Lang::C) {
        // Do not abort by default in C/C++ as it requires including a header.
        CodeList* abort = code_list(alc);
        append(abort, code_abort(alc));
        append(cases, code_case_default(alc, abort));
    }
    append(loop, code_switch(alc, opts->var_state.c_str(), cases));
    append(stmts, code_loop(alc, loop));
}

static void gen_block_dot(Output& output, const Adfas& dfas, CodeList* code) {
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;

    append(code, code_text(alc, "digraph re2c {"));
    append(code, code_cond_goto(alc));

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

static void gen_block_code(Output& output, const Adfas& dfas, CodeList* program) {
    OutputBlock& oblock = output.block();
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;
    const opt_t* opts = oblock.opts;

    // All conditions are named, so it suffices to check the first DFA.
    DCHECK(!dfas.empty());
    const bool is_cond_block = !dfas.front()->cond.empty();

    append(program, code_newline(alc)); // the following #line info must start at zero indent
    append(program, code_line_info_output(alc));

    CodeList* code = code_list(alc);

    if (!opts->storable_state && opts->char_emit) {
        append(code, code_yych_decl(alc));
    }
    if (!opts->storable_state && oblock.used_yyaccept) {
        append(code, code_yyaccept_def(alc));
    }

    if (opts->loop_switch) {
        // In the loop/switch mode append all DFA states as cases of the `yystate` switch.
        // Merge DFAs for different conditions together in one switch.
        append(code, code_yystate_def(alc));

        CodeCases* cases = code_cases(alc);
        for (const std::unique_ptr<Adfa>& dfa : dfas) {
            gen_dfa_as_switch_cases(output, *dfa, cases);
        }
        wrap_dfas_in_loop_switch(output, code, cases);

    } else {
        // In the goto/label mode, generate DFA states as blocks of code preceded with labels,
        // and `goto` transitions between states.
        if (opts->cgoto && is_cond_block) {
            append(code, code_cond_table(alc));
        }
        if (opts->bitmaps) {
            for (const std::unique_ptr<Adfa>& dfa : dfas) {
                append(code, gen_bitmap(output, dfa->bitmap, dfa->cond));
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
                append(code, code_state_goto(alc, p));
            } else if (!output.state_goto) {
                // For a non-use block, generate a state switch only if it wasn't generated before.
                // Null block list means that the autogenerated state switch should include all
                // non-use blocks in the file.
                append(code, code_state_goto(alc, nullptr));
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
            append(code, code_cond_goto(alc));
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
    append(program, code_block(alc, code, CodeBlock::Kind::WRAPPED));
}

void gen_code_pass1(Output& output) {
    OutputBlock& block = output.block();
    Adfas& dfas = block.dfas;
    OutAllocator& alc = output.allocator;
    const opt_t* opts = block.opts;

    Code* code = block.code->head;
    if (code->kind != CodeKind::DFAS) {
        return;
    } else if (dfas.empty()) {
        code->kind = CodeKind::EMPTY;
        return;
    }

    const std::unique_ptr<Adfa>& first_dfa = *dfas.begin();

    for (const std::unique_ptr<Adfa>& dfa : dfas) {
        const bool first = (dfa == first_dfa);

        if (opts->bitmaps) {
            dfa->bitmap = code_bitmap(alc, std::min(dfa->upper_char, 256u));
            for (State* s = dfa->head; s; s = s->next) {
                if (s->is_base) {
                    DCHECK(s->next);
                    insert_bitmap(alc, dfa->bitmap, &s->next->go, s);
                }
            }
        }

        // Allocate labels for DFA states, but do not assign indices yet: they will be assigned
        // after the used label analysis only to the labels that are used.
        for (State* s = dfa->head; s; s = s->next) {
            s->label = new_label(alc, Label::NONE);
        }

        if (!opts->loop_switch) {
            if (first) {
                if (opts->label_start_force) {
                    // User-enforced start label.
                    block.start_label = new_label(alc, output.label_counter++);
                    block.start_label->used = true;
                } else if (opts->storable_state) {
                    // Start label is needed in `-f` mode: it points to state 0 (the beginning of
                    // block, before condition dispatch in `-c` mode).
                    block.start_label = new_label(alc, output.label_counter++);
                }
            }
            // Initial label points to the start of the DFA (after condition dispatch in `-c`).
            dfa->initial_label = new_label(alc, output.label_counter++);
        } else {
            // In loop/switch mode the label of the first state is always used.
            dfa->head->label->used = true;
            // With loop/switch there are no labels, and each block has its own state switch where
            // all conditions are joined. Restart state counter from zero so that cases start from
            // zero. With skeleton conditions are separate.
            if (first || opts->target == Target::SKELETON) output.label_counter = 0;
        }

        // Generate DFA transitions and perform used label analysis: for every transition mark its
        // destination state label as used.
        for (State* s = dfa->head; s; s = s->next) {
            code_go(alc, *dfa, opts, s);
        }

        // Assign label indices (only to the labels that are used).
        for (State* s = dfa->head; s; s = s->next) {
            if (s->label->used) s->label->index = output.label_counter++;
        }

        if (!dfa->cond.empty()) {
            // If loop/switch is used, condition numbers are the numeric indices of their initial
            // DFA state. Otherwise we do not assign explicit numbers, and conditions are implicitly
            // assigned consecutive numbers starting from zero.
            block.conds.push_back({dfa->cond, opts->loop_switch ? dfa->head->label->index : 0});
        }
    }

    // In loop/switch mode storable states occupy continuous index range after the last state index.
    // In goto/label mode they use separate global enumeration that starts from zero.
    uint32_t& counter = opts->loop_switch ? output.label_counter : output.fill_label_counter;
    for (const std::unique_ptr<Adfa>& dfa : dfas) {
        for (State* s = dfa->head; s; s = s->next) {
            if (s->fill_state == s) {
                s->fill_label = new_label(alc, counter++);
            }
        }
    }
}

void gen_code_pass2(Output& output) {
    OutputBlock& block = output.block();
    Adfas& dfas = block.dfas;
    const opt_t* opts = block.opts;

    Code* code = block.code->head;
    if (code->kind != CodeKind::DFAS) return;

    CodeList* program = code_list(output.allocator);
    if (opts->target == Target::DOT) {
        gen_block_dot(output, dfas, program);
    } else if (opts->target == Target::SKELETON) {
        gen_block_skeleton(output, dfas, program);
    } else {
        gen_block_code(output, dfas, program);
    }

    code->kind = CodeKind::BLOCK;
    code->block.kind = CodeBlock::Kind::RAW;
    code->block.stmts = program;
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
