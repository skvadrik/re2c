#include "config.h"
#include "src/codegen/code.h"
#include "src/codegen/helpers.h"
#include "src/msg/msg.h"
#include "src/msg/warn.h"
#include "src/options/opt.h"
#include "src/util/attribute.h"
#include "src/util/string_utils.h"

namespace re2c {

static OutputBlock* find_block_with_name(CodegenCtxPass1& ctx, const char* name) {
    for (OutputBlock* b : ctx.global->cblocks) {
        if (b->name.compare(name) == 0) return b;
    }
    for (OutputBlock* b : ctx.global->hblocks) {
        if (b->name.compare(name) == 0) return b;
    }
    return nullptr;
}

LOCAL_NODISCARD(Ret find_blocks(CodegenCtxPass1& ctx,
                                const BlockNameList*
                                names,blocks_t& blocks,
                                const char* directive)) {
    blocks.clear();
    for (const BlockNameList* p = names; p; p = p->next) {
        OutputBlock* b = find_block_with_name(ctx, p->name);
        if (b) {
            blocks.push_back(b);
        } else {
            RET_FAIL(error("cannot find block '%s' listed in `%s` directive", p->name, directive));
        }
    }
    return Ret::OK;
}

static std::string output_cond_get(const opt_t* opts) {
    return opts->cond_get + (opts->cond_get_naked ? "" : "()");
}

static std::string output_state_get(const opt_t* opts) {
    return opts->state_get + (opts->state_get_naked ? "" : "()");
}

void gen_tags(Scratchbuf& buf, const opt_t* opts, Code* code, const tagnames_t& tags) {
    DASSERT(code->kind == CodeKind::STAGS || code->kind == CodeKind::MTAGS);

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
    if (!opts->iFlag) {
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

LOCAL_NODISCARD(Ret expand_tags_directive(CodegenCtxPass1& ctx, Code* code)) {
    DASSERT(code->kind == CodeKind::STAGS || code->kind == CodeKind::MTAGS);
    if (ctx.global->opts->target != Target::CODE) {
        code->kind = CodeKind::EMPTY;
        return Ret::OK;
    }

    Scratchbuf& buf = ctx.global->scratchbuf;
    bool multival = (code->kind == CodeKind::MTAGS);

    tagnames_t tags;
    if (code->fmt.block_names == nullptr) {
        // Gather tags from all blocks in the output and header files.
        add_tags_from_blocks(ctx.global->cblocks, tags, multival);
        add_tags_from_blocks(ctx.global->hblocks, tags, multival);
    } else {
        // Gather tags from the blocks on the list.
        const char* directive = multival ? "mtags:re2c" : "stags:re2c";
        CHECK_RET(find_blocks(ctx, code->fmt.block_names, ctx.global->tmpblocks, directive));
        add_tags_from_blocks(ctx.global->tmpblocks, tags, multival);
    }
    gen_tags(buf, ctx.block->opts, code, tags);
    return Ret::OK;
}

static void gen_cond_enum(Scratchbuf& buf,
                          code_alc_t& alc,
                          Code* code,
                          const opt_t* opts,
                          const StartConds& conds) {
    DASSERT(opts->target == Target::CODE);

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
            start = buf.cstr("enum ").str(opts->yycondtype).cstr(" {").flush();
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
            DASSERT(opts->loop_switch);
            for (const StartCond& cond : conds) {
                buf.cstr("const ").str(cond.name).cstr(": ").cstr(opts->fFlag ? "isize" : "usize")
                        .cstr(" = ").u32(cond.number);
                append(block, code_stmt(alc, buf.flush()));
            }
        } else {
            DASSERT(false); // no such language
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
        const OutputBlock& block, StartConds& conds, const StartCond& cond)) {
    // Condition prefix is specific to the block that defines it. If a few blocks define conditions
    // with the same name, but a different prefix, they should have different enum entries.
    StartCond sc = cond;
    sc.name = block.opts->condEnumPrefix + sc.name;

    for (const StartCond& cond : conds) {
        if (cond.name == sc.name) {
            if (cond.number == sc.number) {
                // A duplicate condition, it's not an error but don't add it.
                return Ret::OK;
            } else {
                // An error: conditions with idetical names but different numbers.
                RET_FAIL(error("cannot generate condition enumeration: conditon '%s' has "
                               "different numbers in different blocks (use `re2c:condenumprefix` "
                               "configuration to set per-block prefix)",
                               sc.name.c_str()));
            }
        }
    }

    conds.push_back(sc);
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

LOCAL_NODISCARD(Ret expand_cond_enum(CodegenCtxPass1& ctx, Code* code)) {
    Scratchbuf& buf = ctx.global->scratchbuf;
    code_alc_t& alc = ctx.global->allocator;

    // Use global options accumulated across the whole file, as `types:re2c` may include conditions
    // from a few different blocks, and it is not clear which block's options it should inherit.
    const opt_t* globopts = ctx.global->opts;

    if (globopts->target != Target::CODE) {
        code->kind = CodeKind::EMPTY;
        return Ret::OK;
    }

    StartConds conds;
    if (code->fmt.block_names == nullptr) {
        // Gather conditions from all blocks in the output and header files.
        CHECK_RET(add_conditions_from_blocks(ctx.global->cblocks, conds));
        CHECK_RET(add_conditions_from_blocks(ctx.global->hblocks, conds));
    } else {
        // Gather conditions from the blocks on the list.
        CHECK_RET(find_blocks(ctx, code->fmt.block_names, ctx.global->tmpblocks, "types:re2c"));
        CHECK_RET(add_conditions_from_blocks(ctx.global->tmpblocks, conds));
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

static void gen_state_goto_cases(CodegenCtxPass1& ctx, CodeCases* cases, const OutputBlock* block) {
    code_alc_t& alc = ctx.global->allocator;
    for (const auto& i : block->fill_goto) {
        append(cases, code_case_number(alc, i.second, static_cast<int32_t>(i.first)));
    }
}

LOCAL_NODISCARD(Ret gen_state_goto(CodegenCtxPass1& ctx, Code* code)) {
    // If this is a `use:re2c` block, this must be an autogenerated block-local state switch, so use
    // block-local options. Otherwise use global options accumulated across the whole file, as the
    // state switch may include states from a few different blocks and it is not clear which options
    // it should inherit.
    const opt_t* globopts = ctx.block->kind == InputBlock::USE ? ctx.block->opts : ctx.global->opts;

    if (globopts->target != Target::CODE) {
        code->kind = CodeKind::EMPTY;
        return Ret::OK;
    }

    // Loop/switch approach is handled differently (by appending special cases to the state switch).
    DASSERT(!globopts->loop_switch);

    Scratchbuf& o = ctx.global->scratchbuf;
    code_alc_t& alc = ctx.global->allocator;
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
        for (const OutputBlock* b : *ctx.global->pblocks) {
            if (b->kind != InputBlock::USE) {
                gen_state_goto_cases(ctx, cases, b);

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
        CHECK_RET(find_blocks(ctx, code->fmt.block_names, ctx.global->tmpblocks, "getstate:re2c"));
        for (const OutputBlock* b : ctx.global->tmpblocks) {
            if (!b->start_label) {
                RET_FAIL(error("block '%s' does not generate code, so it should not be listed in "
                               "`getstate:re2c` directive",
                               b->name.c_str()));
            }
            // Use start label of the first block on the list.
            if (!bstart) bstart = b;
            gen_state_goto_cases(ctx, cases, b);
        }
    }

    // This is the use that makes 2nd codegen pass for labels necessary.
    Label* lstart = bstart->start_label;
    lstart->used = true;

    CodeList* goto_start = code_list(alc);
    text = o.cstr("goto ").str(bstart->opts->labelPrefix).u32(lstart->index).flush();
    append(goto_start, code_stmt(alc, text));

    if (globopts->bUseStateAbort) {
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

    if (globopts->bUseStateNext) {
        text = o.str(globopts->yynext).cstr(":").flush();
        append(stmts, code_textraw(alc, text));
    }

    code->kind = CodeKind::BLOCK;
    code->block.kind = CodeBlock::Kind::RAW;
    code->block.stmts = stmts;
    return Ret::OK;
}

static void gen_yych_decl(const opt_t* opts, Code* code) {
    if (opts->bEmitYYCh) {
        code->kind = CodeKind::VAR;
        code->var.type = VarType::YYCTYPE;
        code->var.name = opts->yych.c_str();
        code->var.init = nullptr;
    } else {
        code->kind = CodeKind::EMPTY;
    }
}

static void gen_yyaccept_def(const opt_t* opts, Code* code, bool used_yyaccept) {
    if (used_yyaccept) {
        code->kind = CodeKind::VAR;
        code->var.type = VarType::UINT;
        code->var.name = opts->yyaccept.c_str();
        code->var.init = "0";
    } else {
        code->kind = CodeKind::EMPTY;
    }
}

static void gen_yystate_def(CodegenCtxPass1& ctx, Code* code) {
    const opt_t* opts = ctx.block->opts;
    Scratchbuf& o = ctx.global->scratchbuf;

    if (opts->loop_switch) {
        code->kind = CodeKind::VAR;
        code->var.name = o.str(opts->yystate).flush();
        if (opts->fFlag) {
            // With storable state `yystate` should be initialized to YYGETSTATE. Since there is a
            // -1 case, `yystate` should have a signed type. If conditions are also used, YYGETSTATE
            // takes priority over YYGETCONDITION, because the lexer may be reentered after an
            // YYFILL invocation. In that case we use YYSETSTATE instead of YYSETCONDITION in the
            // final states.
            code->var.type = VarType::INT;
            code->var.init = o.str(output_state_get(opts)).flush();
        } else if (opts->cFlag) {
            // Else with start conditions yystate should be initialized to YYGETCONDITION.
            code->var.type = VarType::UINT;
            code->var.init = o.str(output_cond_get(opts)).flush();
        } else {
            // Else it should be the start DFA state (always case 0 with --loop-switch).
            code->var.type = VarType::UINT;
            code->var.init = "0";
        }
    } else {
        code->kind = CodeKind::EMPTY;
    }
}

static size_t max_among_blocks(const blocks_t& blocks, size_t max, CodeKind kind) {
    for (const OutputBlock* b : blocks) {
        max = std::max(max, kind == CodeKind::MAXFILL ? b->max_fill : b->max_nmatch);
    }
    return max;
}

LOCAL_NODISCARD(Ret gen_yymax(CodegenCtxPass1& ctx, Code* code)) {
    const opt_t* opts = ctx.block->opts;
    Scratchbuf& o = ctx.global->scratchbuf;

    if (opts->target != Target::CODE) {
        code->kind = CodeKind::EMPTY;
        return Ret::OK;
    }

    CodeKind kind = code->kind;
    const char* dirname = kind == CodeKind::MAXFILL ? "max:re2c" : "maxnmatch:re2c";
    const char* varname = kind == CodeKind::MAXFILL ? "YYMAXFILL" : "YYMAXNMATCH";

    size_t max = 1;
    if (code->fmt.block_names == nullptr) {
        // Gather max value from all blocks in the output and header files.
        max = max_among_blocks(ctx.global->cblocks, max, kind);
        max = max_among_blocks(ctx.global->hblocks, max, kind);
    } else {
        // Maximum among the blocks listed in the directive.
        CHECK_RET(find_blocks(ctx, code->fmt.block_names, ctx.global->tmpblocks, dirname));
        max = max_among_blocks(ctx.global->tmpblocks, max, kind);
    }

    if (code->fmt.format) {
        std::ostringstream os(code->fmt.format);
        argsubst(os, opts->api_sigil, "max", true, max);
        code->text = o.str(os.str()).flush();
    } else {
        switch (opts->lang) {
        case Lang::C:
            code->text = o.cstr("#define ").cstr(varname).cstr(" ").u64(max).flush();
            break;
        case Lang::GO:
            code->text = o.cstr("var ").cstr(varname).cstr(" int = ").u64(max).flush();
            break;
        case Lang::RUST:
            code->text = o.cstr("const ").cstr(varname).cstr(": usize = ").u64(max).flush();
            break;
        }
    }
    code->kind = (opts->lang == Lang::C) ? CodeKind::TEXT : CodeKind::STMT;
    return Ret::OK;
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

static CodeList* gen_cond_goto_binary(CodegenCtxPass1& ctx, size_t lower, size_t upper) {
    const opt_t* opts = ctx.block->opts;
    code_alc_t& alc = ctx.global->allocator;
    Scratchbuf& o = ctx.global->scratchbuf;

    CodeList* stmts = code_list(alc);
    if (lower == upper) {
        o.cstr("goto ").str(opts->condPrefix).str(ctx.block->conds[lower].name);
        append(stmts, code_stmt(alc, o.flush()));
    } else {
        const size_t middle = lower + (upper - lower + 1) / 2;
        CodeList* if_then = gen_cond_goto_binary(ctx, lower, middle - 1);
        CodeList* if_else = gen_cond_goto_binary(ctx, middle, upper);
        o.str(output_cond_get(opts)).cstr(" < ").u64(middle);
        append(stmts, code_if_then_else(alc, o.flush(), if_then, if_else));
    }
    return stmts;
}

static void gen_cond_goto(CodegenCtxPass1& ctx, Code* code) {
    const opt_t* opts = ctx.block->opts;
    code_alc_t& alc = ctx.global->allocator;
    Scratchbuf& o = ctx.global->scratchbuf;
    const StartConds& conds = ctx.block->conds;
    bool warn_cond_ord = ctx.global->warn_cond_ord;

    DASSERT(!opts->loop_switch);

    const size_t ncond = conds.size();
    CodeList* stmts = code_list(alc);
    const char* text;

    if (opts->target == Target::DOT) {
        for (const StartCond& cond : conds) {
            text = o.cstr("0 -> ").str(cond.name).cstr(" [label=\"state=").str(cond.name)
                    .cstr("\"]").flush();
            append(stmts, code_text(alc, text));
        }
    } else {
        if (opts->gFlag) {
            text = o.cstr("goto *").str(opts->yyctable).cstr("[").str(output_cond_get(opts))
                    .cstr("]").flush();
            append(stmts, code_stmt(alc, text));
        } else if (opts->sFlag) {
            warn_cond_ord &= ncond > 1;
            append(stmts, gen_cond_goto_binary(ctx, 0, ncond - 1));
        } else {
            warn_cond_ord = false;

            CodeCases* ccases = code_cases(alc);
            for (const StartCond& cond : conds) {
                CodeList* body = code_list(alc);
                text = o.cstr("goto ").str(opts->condPrefix).str(cond.name).flush();
                append(body, code_stmt(alc, text));

                text = o.str(opts->condEnumPrefix).str(cond.name).flush();
                append(ccases, code_case_string(alc, body, text));
            }
            text = o.str(output_cond_get(opts)).flush();
            append(stmts, code_switch(alc, text, ccases));
        }

        // see note [condition order]
        warn_cond_ord &= opts->header_file.empty();
        if (warn_cond_ord) {
            ctx.global->msg.warn.condition_order(ctx.block->loc);
        }
    }

    code->kind = CodeKind::BLOCK;
    code->block.kind = CodeBlock::Kind::RAW;
    code->block.stmts = stmts;
}

static void gen_cond_table(CodegenCtxPass1& ctx, Code* code) {
    const opt_t* opts = ctx.block->opts;
    code_alc_t& alc = ctx.global->allocator;
    const StartConds& conds = ctx.block->conds;
    Scratchbuf& o = ctx.global->scratchbuf;

    CodeList* stmts = code_list(alc);

    o.cstr("static void *").str(opts->yyctable).cstr("[").u64(conds.size()).cstr("] = {");
    append(stmts, code_text(alc, o.flush()));

    CodeList* block = code_list(alc);
    for (const StartCond& cond : conds) {
        o.cstr("&&").str(opts->condPrefix).str(cond.name).cstr(",");
        append(block, code_text(alc, o.flush()));
    }
    append(stmts, code_block(alc, block, CodeBlock::Kind::INDENTED));

    append(stmts, code_stmt(alc, "}"));

    code->kind = CodeKind::BLOCK;
    code->block.kind = CodeBlock::Kind::RAW;
    code->block.stmts = stmts;
}

LOCAL_NODISCARD(Ret expand_pass_1_list(CodegenCtxPass1& ctx, CodeList* stmts)) {
    if (stmts) {
        for (Code* x = stmts->head; x; x = x->next) {
            CHECK_RET(expand_pass_1(ctx, x));
        }
    }
    return Ret::OK;
}

Ret expand_pass_1(CodegenCtxPass1& ctx, Code* code) {
    const opt_t* opts = ctx.block->opts;
    switch (code->kind) {
    case CodeKind::BLOCK:
        return expand_pass_1_list(ctx, code->block.stmts);
    case CodeKind::IF_THEN_ELSE:
        CHECK_RET(expand_pass_1_list(ctx, code->ifte.if_code));
        CHECK_RET(expand_pass_1_list(ctx, code->ifte.else_code));
        break;
    case CodeKind::SWITCH:
        for (CodeCase* x = code->swch.cases->head; x; x = x->next) {
            CHECK_RET(expand_pass_1_list(ctx, x->body));
        }
        break;
    case CodeKind::LOOP:
        return expand_pass_1_list(ctx, code->loop);
    case CodeKind::STAGS:
    case CodeKind::MTAGS:
        return expand_tags_directive(ctx, code);
    case CodeKind::MAXFILL:
    case CodeKind::MAXNMATCH:
        return gen_yymax(ctx, code);
    case CodeKind::YYCH:
        gen_yych_decl(opts, code);
        break;
    case CodeKind::YYACCEPT:
        gen_yyaccept_def(opts, code, ctx.block->used_yyaccept);
        break;
    case CodeKind::YYSTATE:
        gen_yystate_def(ctx, code);
        break;
    case CodeKind::COND_ENUM:
        return expand_cond_enum(ctx, code);
    case CodeKind::COND_GOTO:
        gen_cond_goto(ctx, code);
        break;
    case CodeKind::COND_TABLE:
        gen_cond_table(ctx, code);
        break;
    case CodeKind::STATE_GOTO:
        return gen_state_goto(ctx, code);
    case CodeKind::LABEL:
        // Do nothing on the first pass (use information is not available yet, as the rest of the
        // first pass may generate some additional label uses, e.g. for a block start label in
        // `getstate:re2c`).
        break;
    case CodeKind::LINE_INFO_INPUT:
    case CodeKind::LINE_INFO_OUTPUT:
        // Although line directives are disabled for Rust, stubs confuse codegen into rendering
        // oneline semantic actions as multiline, which triggers rustc warnings about redundant
        // braces. We replace stubs with empty statements and rely on `remove_empty` pass.
        if (opts->lang == Lang::RUST) code->kind = CodeKind::EMPTY;
        break;
    case CodeKind::EMPTY:
    case CodeKind::FUNC:
    case CodeKind::STMT:
    case CodeKind::TEXT:
    case CodeKind::RAW:
    case CodeKind::TEXT_RAW:
    case CodeKind::SKIP:
    case CodeKind::PEEK:
    case CodeKind::BACKUP:
    case CodeKind::PEEK_SKIP:
    case CodeKind::SKIP_PEEK:
    case CodeKind::SKIP_BACKUP:
    case CodeKind::BACKUP_SKIP:
    case CodeKind::BACKUP_PEEK:
    case CodeKind::BACKUP_PEEK_SKIP:
    case CodeKind::SKIP_BACKUP_PEEK:
    case CodeKind::VAR:
    case CodeKind::ABORT:
        break;
    }
    return Ret::OK;
}

static void gen_label(Scratchbuf& o, const opt_t* opts, Code* code) {
    DASSERT(code->kind == CodeKind::LABEL);
    CodeLabel* label = &code->label;

    if (label->kind == CodeLabel::Kind::SLABEL) {
        code->kind = CodeKind::TEXT_RAW;
        code->text = o.cstr(label->slabel).cstr(":").flush();
    } else if (label->nlabel->used) {
        DASSERT(label->nlabel->index != Label::NONE);
        code->kind = CodeKind::TEXT_RAW;
        code->text = o.str(opts->labelPrefix).u32(label->nlabel->index).cstr(":").flush();
    } else {
        code->kind = CodeKind::EMPTY;
    }
}

static void expand_pass_2_list(CodegenCtxPass2& ctx, CodeList* stmts) {
    if (!stmts) return;
    for (Code* x = stmts->head; x; x = x->next) {
        expand_pass_2(ctx, x);
    }
}

void expand_pass_2(CodegenCtxPass2& ctx, Code* code) {
    switch (code->kind) {
    case CodeKind::BLOCK:
        expand_pass_2_list(ctx, code->block.stmts);
        break;
    case CodeKind::IF_THEN_ELSE:
        expand_pass_2_list(ctx, code->ifte.if_code);
        expand_pass_2_list(ctx, code->ifte.else_code);
        break;
    case CodeKind::SWITCH:
        for (CodeCase* x = code->swch.cases->head; x; x = x->next) {
            expand_pass_2_list(ctx, x->body);
        }
        break;
    case CodeKind::LOOP:
        expand_pass_2_list(ctx, code->loop);
        break;
    case CodeKind::LABEL:
        gen_label(ctx.scratchbuf, ctx.opts, code);
        break;
    default:
        break;
    }
}

} // namespace re2c
