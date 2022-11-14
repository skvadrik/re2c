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

static std::string output_state_get(const opt_t* opts) {
    return opts->api_state_get + (opts->state_get_naked ? "" : "()");
}

static OutputBlock* find_block_with_name(Output& output, const char* name) {
    for (OutputBlock* b : output.cblocks) {
        if (b->name.compare(name) == 0) return b;
    }
    for (OutputBlock* b : output.hblocks) {
        if (b->name.compare(name) == 0) return b;
    }
    return nullptr;
}

Ret find_blocks(
        Output& output, const BlockNameList* names, blocks_t& blocks, const char* directive) {
    blocks.clear();
    for (const BlockNameList* p = names; p; p = p->next) {
        OutputBlock* b = find_block_with_name(output, p->name);
        if (b) {
            blocks.push_back(b);
        } else {
            RET_FAIL(error("cannot find block '%s' listed in `%s` directive", p->name, directive));
        }
    }
    return Ret::OK;
}

static void gen_state_goto_cases(Output& output, CodeCases* cases, const OutputBlock* block) {
    OutAllocator& alc = output.allocator;
    for (const auto& i : block->fill_goto) {
        append(cases, code_case_number(alc, i.second, static_cast<int32_t>(i.first)));
    }
}

LOCAL_NODISCARD(Ret gen_state_goto(Output& output, Code* code)) {
    OutputBlock& block = output.block();
    // If this is a `use:re2c` block, this must be an autogenerated block-local state switch, so use
    // block-local options. Otherwise use global options accumulated across the whole file, as the
    // state switch may include states from a few different blocks and it is not clear which options
    // it should inherit.
    const opt_t* globopts = block.kind == InputBlock::USE ? block.opts : output.total_opts;

    if (globopts->target != Target::CODE) {
        code->kind = CodeKind::EMPTY;
        return Ret::OK;
    }

    // Loop/switch approach is handled differently (by appending special cases to the state switch).
    DCHECK(!globopts->loop_switch);

    Scratchbuf& o = output.scratchbuf;
    OutAllocator& alc = output.allocator;
    const char* text;

    // There are two possibilities:
    //
    // 1. A state switch with an explicit list of block names. This is the case of a user-defined
    //    `getstate:re2c:<name1>[:<name2>...]` directive or a `use:re2c` block (use blocks have a
    //    block-local state switch that is automatically generated at the beginning of the block,
    //    and they have a special autogenerated name, as they cannot have a user-defined one).
    //
    // 2. A global state switch without a list of block names. This is the case of a user-defined
    //    `getstate:re2c` without a name list, or a global state switch that is generated
    //    automatically if the user did not specify any explicit `getstate:re2c` directives. The
    //    global switch includes all blocks except `use:re2c` (if a block generates no code it does
    //    not contribute any cases to the state switch).
    //
    bool global = (code->fmt.block_names == nullptr);

    CodeCases* cases = code_cases(alc);
    const OutputBlock* bstart = nullptr;

    if (global) {
        // No block names are specified: generate a global switch. It includes all blocks except for
        // the `re2c:use` ones which have a local switch.
        for (const OutputBlock* b : *output.pblocks) {
            if (b->kind != InputBlock::USE) {
                gen_state_goto_cases(output, cases, b);

                // Use start label of the first non-use block that generates code.
                if (!bstart && b->start_label) bstart = b;
            }
        }
        if (!bstart || !bstart->start_label) {
            // This must be a user-defined directive: the automatic state switch is generated only
            // when processing the first block that has code.
            RET_FAIL(error("none of the blocks in `getstate:re2c` generate any code"));
        }
    } else {
        // Generate a switch for all specified named blocks.
        CHECK_RET(find_blocks(output, code->fmt.block_names, output.tmpblocks, "getstate:re2c"));
        for (const OutputBlock* b : output.tmpblocks) {
            if (!b->start_label) {
                RET_FAIL(error("block '%s' does not generate code, so it should not be listed in "
                               "`getstate:re2c` directive",
                               b->name.c_str()));
            }
            // Use start label of the first block on the list.
            if (!bstart) bstart = b;
            gen_state_goto_cases(output, cases, b);
        }
    }

    // This is the use that makes 2nd codegen pass for labels necessary.
    Label* lstart = bstart->start_label;
    lstart->used = true;

    CodeList* goto_start = code_list(alc);
    text = o.cstr("goto ").str(bstart->opts->label_prefix).u32(lstart->index).flush();
    append(goto_start, code_stmt(alc, text));

    if (globopts->state_abort) {
        // case -1: goto <start label>;
        prepend(cases, code_case_number(alc, goto_start, -1));

        // default: abort
        CodeList* abort = code_list(alc);
        append(abort, code_abort(alc));
        prepend(cases, code_case_default(alc, abort));
    } else {
        // default: goto <start label>;
        prepend(cases, code_case_default(alc, goto_start));
    }

    CodeList* stmts = code_list(alc);
    text = o.str(output_state_get(globopts)).flush();
    append(stmts, code_switch(alc, text, cases));

    if (globopts->state_next) {
        text = o.str(globopts->label_next).cstr(":").flush();
        append(stmts, code_textraw(alc, text));
    }

    code->kind = CodeKind::BLOCK;
    code->block.kind = CodeBlock::Kind::RAW;
    code->block.stmts = stmts;
    return Ret::OK;
}

void gen_tags(Scratchbuf& buf, const opt_t* opts, Code* code, const tagnames_t& tags) {
    DCHECK(code->kind == CodeKind::STAGS || code->kind == CodeKind::MTAGS);

    const char* fmt = code->fmt.format;
    const char* sep = code->fmt.separator;
    bool first = true;
    for (const std::string& tag : tags) {
        if (first) {
            first = false;
        } else if (sep != nullptr) {
            buf.cstr(sep);
        }
        if (fmt != nullptr) {
            std::ostringstream s(fmt);
            argsubst(s, opts->api_sigil, "tag", true, tag);
            buf.str(s.str());
        }
    }
    if (opts->line_dirs) {
        const std::string& s = buf.stream().str();
        if (!s.empty() && *s.rbegin() != '\n') buf.cstr("\n");
    }

    code->kind = CodeKind::RAW;
    code->raw.size = buf.stream().str().length();
    code->raw.data = buf.flush();
}

static void add_tags_from_blocks(const blocks_t& blocks, tagnames_t& tags, bool multival) {
    for (OutputBlock* b : blocks) {
        if (multival) {
            tags.insert(b->mtags.begin(), b->mtags.end());
        } else {
            tags.insert(b->stags.begin(), b->stags.end());
        }
    }
}

LOCAL_NODISCARD(Ret expand_tags_directive(Output& output, Code* code)) {
    DCHECK(code->kind == CodeKind::STAGS || code->kind == CodeKind::MTAGS);

    OutputBlock& block = output.block();
    Scratchbuf& buf = output.scratchbuf;
    const opt_t* opts = block.opts;

    if (opts->target != Target::CODE) {
        code->kind = CodeKind::EMPTY;
        return Ret::OK;
    }

    bool multival = (code->kind == CodeKind::MTAGS);

    tagnames_t tags;
    if (code->fmt.block_names == nullptr) {
        // Gather tags from all blocks in the output and header files.
        add_tags_from_blocks(output.cblocks, tags, multival);
        add_tags_from_blocks(output.hblocks, tags, multival);
    } else {
        // Gather tags from the blocks on the list.
        const char* directive = multival ? "mtags:re2c" : "stags:re2c";
        CHECK_RET(find_blocks(output, code->fmt.block_names, output.tmpblocks, directive));
        add_tags_from_blocks(output.tmpblocks, tags, multival);
    }
    gen_tags(buf, opts, code, tags);
    return Ret::OK;
}

static void gen_cond_enum(Scratchbuf& buf,
                          OutAllocator& alc,
                          Code* code,
                          const opt_t* opts,
                          const StartConds& conds) {
    DCHECK(opts->target == Target::CODE);

    if (conds.empty()) return;
    const StartCond* first_cond = &conds.front();
    const StartCond* last_cond = &conds.back();

    if (code->fmt.format) {
        const char* fmt = code->fmt.format;
        const char* sep = code->fmt.separator;
        uint32_t cond_number = 0;
        for (const StartCond& cond : conds) {
            if (sep != nullptr && &cond != first_cond) {
                buf.cstr(sep);
            }
            std::ostringstream s(fmt);
            // The main substitution (the one allowing unnamed sigil) must go last, or else it will
            // erroneously substitute all the named ones.
            size_t cid = opts->loop_switch ? cond.number : cond_number;
            argsubst(s, opts->api_sigil, "num", false, cid);
            argsubst(s, opts->api_sigil, "cond", true, cond.name);
            buf.str(s.str());
            ++cond_number;
        }
        buf.cstr("\n");

        code->kind = CodeKind::RAW;
        code->raw.size = buf.stream().str().length();
        code->raw.data = buf.flush();
    } else {
        const char* start = nullptr, *end = nullptr;
        CodeList* stmts = code_list(alc);
        CodeList* block = code_list(alc);

        if (opts->lang == Lang::C) {
            start = buf.cstr("enum ").str(opts->api_cond_type).cstr(" {").flush();
            end = "};";
            for (const StartCond& cond : conds) {
                buf.str(cond.name);
                if (opts->loop_switch) {
                    buf.cstr(" = ").u32(cond.number);
                }
                if (&cond != last_cond) { // do not append comma after the last one
                    buf.cstr(",");
                }
                append(block, code_text(alc, buf.flush()));
            }
        } else if (opts->lang == Lang::GO) {
            start = buf.cstr("const (").flush();
            end = ")";
            for (const StartCond& cond : conds) {
                buf.str(cond.name);
                if (opts->loop_switch) {
                    buf.cstr(" = ").u32(cond.number);
                } else if (&cond == first_cond) {
                    buf.cstr(" = iota");
                }
                append(block, code_text(alc, buf.flush()));
            }
        } else if (opts->lang == Lang::RUST) {
            // For Rust generate standalone constants instead of enum to avoid casting to `yystate`
            // type on each operation. With the loop/switch approach conditions are handled as
            // regular states anyway, so the enum doesn't make much sense.
            start = "";
            end = "";
            DCHECK(opts->loop_switch);
            for (const StartCond& c : conds) {
                buf.cstr("const ").str(c.name).cstr(": ")
                        .cstr(opts->storable_state ? "isize" : "usize").cstr(" = ").u32(c.number);
                append(block, code_stmt(alc, buf.flush()));
            }
        } else {
            UNREACHABLE(); // no such language
        }

        append(stmts, code_text(alc, start));
        append(stmts, code_block(alc, block, opts->lang == Lang::RUST
                ? CodeBlock::Kind::RAW : CodeBlock::Kind::INDENTED));
        append(stmts, code_text(alc, end));

        code->kind = CodeKind::BLOCK;
        code->block.kind = CodeBlock::Kind::RAW;
        code->block.stmts = stmts;
    }
}

LOCAL_NODISCARD(Ret add_condition_from_block(
        const OutputBlock& block, StartConds& conds, StartCond cond)) {
    // Condition prefix is specific to the block that defines it. If a few blocks define conditions
    // with the same name, but a different prefix, they should have different enum entries.
    cond.name = block.opts->cond_enum_prefix + cond.name;

    for (const StartCond& c : conds) {
        if (c.name == cond.name) {
            if (c.number == cond.number) {
                // A duplicate condition, it's not an error but don't add it.
                return Ret::OK;
            } else {
                // An error: conditions with idetical names but different numbers.
                RET_FAIL(error("cannot generate condition enumeration: conditon '%s' has "
                               "different numbers in different blocks (use `re2c:condenumprefix` "
                               "configuration to set per-block prefix)",
                               cond.name.c_str()));
            }
        }
    }

    conds.push_back(cond);
    return Ret::OK;
}

LOCAL_NODISCARD(Ret add_conditions_from_blocks(const blocks_t& blocks, StartConds& conds)) {
    for (const OutputBlock* block : blocks) {
        for (const StartCond& cond : block->conds) {
            CHECK_RET(add_condition_from_block(*block, conds, cond));
        }
    }
    return Ret::OK;
}

LOCAL_NODISCARD(Ret expand_cond_enum(Output& output, Code* code)) {
    Scratchbuf& buf = output.scratchbuf;
    OutAllocator& alc = output.allocator;

    // Use global options accumulated across the whole file, as `types:re2c` may include conditions
    // from a few different blocks, and it is not clear which block's options it should inherit.
    const opt_t* globopts = output.total_opts;

    if (globopts->target != Target::CODE) {
        code->kind = CodeKind::EMPTY;
        return Ret::OK;
    }

    StartConds conds;
    if (code->fmt.block_names == nullptr) {
        // Gather conditions from all blocks in the output and header files.
        CHECK_RET(add_conditions_from_blocks(output.cblocks, conds));
        CHECK_RET(add_conditions_from_blocks(output.hblocks, conds));
    } else {
        // Gather conditions from the blocks on the list.
        CHECK_RET(find_blocks(output, code->fmt.block_names, output.tmpblocks, "types:re2c"));
        CHECK_RET(add_conditions_from_blocks(output.tmpblocks, conds));
    }

    // Do not generate empty condition enum. Some compilers or language standards allow it, but
    // generally it's more likely to indicate an error in user code.
    if (conds.empty()) {
        code->kind = CodeKind::EMPTY;
        return Ret::OK;
    }

    gen_cond_enum(buf, alc, code, globopts, conds);
    return Ret::OK;
}

// Emit implicit condiiton enum in the header, if there is no explicit directive.
void gen_implicit_cond_enum(Output& output) {
    const opt_t* opts = output.total_opts;
    OutAllocator& alc = output.allocator;

    if (!opts->header_file.empty() && opts->start_conditions && output.cond_enum_autogen) {
        output.header_mode(true);
        output.gen_stmt(code_newline(alc));
        output.gen_stmt(code_fmt(alc, CodeKind::COND_ENUM, nullptr, nullptr, nullptr));
        output.header_mode(false);
    }
}

static std::string output_cond_get(const opt_t* opts) {
    return opts->api_cond_get + (opts->cond_get_naked ? "" : "()");
}

// note [condition order]
//
// In theory re2c makes no guarantee about the order of conditions in the generated lexer. Users
// should define condition type YYCONDTYPE and use values of this type with YYGETCONDITION and
// YYSETCONDITION. This way code is independent of internal re2c condition numbering.
//
// However, it is possible to manually hardcode condition numbers and make re2c generate condition
// dispatch without explicit use of condition names (nested `if` statements with `-b` or computed
// `goto` table with `-g`). This code is syntactically valid (compiles), but unsafe:
//     - change of re2c options may break compilation
//     - change of internal re2c condition numbering may break runtime
//
// re2c has to preserve the existing numbering scheme.
//
// re2c warns about implicit assumptions about condition order, unless:
//     - condition type is defined with 'types:re2c' or '-t, --type-header'
//     - dispatch is independent of condition order: either it uses explicit condition names or
//       there's only one condition and dispatch shrinks to unconditional jump

static CodeList* gen_cond_goto_binary(Output& output, size_t lower, size_t upper) {
    OutputBlock& block = output.block();
    const opt_t* opts = block.opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;

    CodeList* stmts = code_list(alc);
    if (lower == upper) {
        buf.cstr("goto ").str(opts->cond_label_prefix).str(block.conds[lower].name);
        append(stmts, code_stmt(alc, buf.flush()));
    } else {
        const size_t middle = lower + (upper - lower + 1) / 2;
        CodeList* if_then = gen_cond_goto_binary(output, lower, middle - 1);
        CodeList* if_else = gen_cond_goto_binary(output, middle, upper);
        buf.str(output_cond_get(opts)).cstr(" < ").u64(middle);
        append(stmts, code_if_then_else(alc, buf.flush(), if_then, if_else));
    }
    return stmts;
}

static CodeList* gen_cond_goto(Output& output) {
    OutputBlock& block = output.block();
    const opt_t* opts = block.opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;
    const StartConds& conds = block.conds;
    bool warn_cond_ord = output.warn_condition_order;

    DCHECK(!opts->loop_switch);

    const size_t ncond = conds.size();
    CodeList* stmts = code_list(alc);
    const char* text;

    if (opts->target == Target::DOT) {
        for (const StartCond& cond : conds) {
            text = buf.cstr("0 -> ").str(cond.name).cstr(" [label=\"state=").str(cond.name)
                    .cstr("\"]").flush();
            append(stmts, code_text(alc, text));
        }
    } else {
        if (opts->cgoto) {
            text = buf.cstr("goto *").str(opts->var_cond_table).cstr("[")
                    .str(output_cond_get(opts)).cstr("]").flush();
            append(stmts, code_stmt(alc, text));
        } else if (opts->nested_ifs) {
            warn_cond_ord &= ncond > 1;
            append(stmts, gen_cond_goto_binary(output, 0, ncond - 1));
        } else {
            warn_cond_ord = false;

            CodeCases* ccases = code_cases(alc);
            for (const StartCond& cond : conds) {
                CodeList* body = code_list(alc);
                text = buf.cstr("goto ").str(opts->cond_label_prefix).str(cond.name).flush();
                append(body, code_stmt(alc, text));

                text = buf.str(opts->cond_enum_prefix).str(cond.name).flush();
                append(ccases, code_case_string(alc, body, text));
            }
            text = buf.str(output_cond_get(opts)).flush();
            append(stmts, code_switch(alc, text, ccases));
        }

        // see note [condition order]
        warn_cond_ord &= opts->header_file.empty();
        if (warn_cond_ord) {
            output.msg.warn.condition_order(block.loc);
        }
    }

    return stmts;
}

LOCAL_NODISCARD(Ret gen_block_code(Output& output, const Adfas& dfas, CodeList* program)) {
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
                Code* x = code_state_goto(alc, p);
                CHECK_RET(gen_state_goto(output, x));
                append(code, x);
            } else if (!output.state_goto) {
                // For a non-use block, generate a state switch only if it wasn't generated before.
                // Null block list means that the autogenerated state switch should include all
                // non-use blocks in the file.
                Code* x = code_state_goto(alc, nullptr);
                CHECK_RET(gen_state_goto(output, x));
                append(code, x);
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
            append(code, gen_cond_goto(output));
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

    return Ret::OK;
}

static void gen_block_dot(Output& output, const Adfas& dfas, CodeList* code) {
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;

    append(code, code_text(alc, "digraph re2c {"));
    append(code, gen_cond_goto(output));

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

                if (opts->storable_state) {
                    block.fill_goto[s->fill_label->index] =
                            gen_goto_after_fill(output, *dfa, s, nullptr);
                }
            }
        }
    }
}

Ret gen_code_pass2(Output& output) {
    OutputBlock& block = output.block();
    Adfas& dfas = block.dfas;
    const opt_t* opts = block.opts;

    for (Code* code = block.code->head; code != nullptr; code = code->next) {
        switch (code->kind) {
        case CodeKind::DFAS: {
            CodeList* program = code_list(output.allocator);
            if (opts->target == Target::DOT) {
                gen_block_dot(output, dfas, program);
            } else if (opts->target == Target::SKELETON) {
                gen_block_skeleton(output, dfas, program);
            } else {
                CHECK_RET(gen_block_code(output, dfas, program));
            }
            code->kind = CodeKind::BLOCK;
            code->block.kind = CodeBlock::Kind::RAW;
            code->block.stmts = program;
            break;
        }
        case CodeKind::STATE_GOTO:
            CHECK_RET(gen_state_goto(output, code));
            break;
        case CodeKind::STAGS:
        case CodeKind::MTAGS:
            CHECK_RET(expand_tags_directive(output, code));
            break;
        case CodeKind::COND_ENUM:
            CHECK_RET(expand_cond_enum(output, code));
            break;
        default:
            break;
        }
    }

    return Ret::OK;
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
