#include "config.h"
#include "src/codegen/code.h"
#include "src/codegen/helpers.h"
#include "src/msg/msg.h"
#include "src/msg/warn.h"
#include "src/options/opt.h"
#include "src/util/string_utils.h"


namespace re2c {

static OutputBlock *find_block_with_name(CodegenCtxPass1 &ctx, const char *name)
{
    const blocks_t &cblocks = ctx.global->cblocks;
    for (size_t i = 0; i < cblocks.size(); ++i) {
        if (cblocks[i]->name.compare(name) == 0) return cblocks[i];
    }
    const blocks_t &hblocks = ctx.global->hblocks;
    for (size_t i = 0; i < hblocks.size(); ++i) {
        if (hblocks[i]->name.compare(name) == 0) return hblocks[i];
    }
    return NULL;
}

static void find_blocks(CodegenCtxPass1 &ctx, const BlockNameList *names,
    blocks_t &blocks, const char *directive)
{
    blocks.clear();
    for (const BlockNameList *p = names; p; p = p->next) {
        OutputBlock *b = find_block_with_name(ctx, p->name);
        if (b) {
            blocks.push_back(b);
        } else {
            error("cannot find block '%s' listed in `%s` directive", p->name, directive);
            exit(1);
        }
    }
}

static std::string output_cond_get(const opt_t *opts)
{
    return opts->cond_get + (opts->cond_get_naked ? "" : "()");
}

static std::string output_state_get(const opt_t *opts)
{
    return opts->state_get + (opts->state_get_naked ? "" : "()");
}

void gen_tags(Scratchbuf &buf, const opt_t *opts, Code *code, const tagnames_t &tags)
{
    DASSERT(code->kind == CODE_STAGS || code->kind == CODE_MTAGS);

    const char *fmt = code->fmt.format;
    const char *sep = code->fmt.separator;

    tagnames_t::const_iterator ib = tags.begin(), ie = tags.end(), it;
    for (it = ib; it != ie; ++it) {
        if (sep && it != ib) {
            buf.cstr(sep);
        }
        if (fmt) {
            std::ostringstream s(fmt);
            argsubst(s, opts->api_sigil, "tag", true, *it);
            buf.str(s.str());
        }
    }
    if (!opts->iFlag) {
        const std::string &s = buf.stream().str();
        if (!s.empty() && *s.rbegin() != '\n') buf.cstr("\n");
    }

    code->kind = CODE_RAW;
    code->raw.size = buf.stream().str().length();
    code->raw.data = buf.flush();
}

static void add_tags_from_blocks(const blocks_t &blocks, tagnames_t &tags, bool multival)
{
    for (size_t i = 0; i < blocks.size(); ++i) {
        const OutputBlock &block = *blocks[i];
        if (multival) {
            tags.insert(block.mtags.begin(), block.mtags.end());
        } else {
            tags.insert(block.stags.begin(), block.stags.end());
        }
    }
}

static void expand_tags_directive(CodegenCtxPass1 &ctx, Code *code)
{
    DASSERT(code->kind == CODE_STAGS || code->kind == CODE_MTAGS);
    if (ctx.global->opts->target != TARGET_CODE) {
        code->kind = CODE_EMPTY;
        return;
    }

    Scratchbuf &buf = ctx.global->scratchbuf;
    bool multival = (code->kind == CODE_MTAGS);

    tagnames_t tags;
    if (code->fmt.block_names == NULL) {
        // Gather tags from all blocks in the output and header files.
        add_tags_from_blocks(ctx.global->cblocks, tags, multival);
        add_tags_from_blocks(ctx.global->hblocks, tags, multival);
    } else {
        // Gather tags from the blocks on the list.
        const char *directive = multival ? "mtags:re2c" : "stags:re2c";
        find_blocks(ctx, code->fmt.block_names, ctx.global->tmpblocks, directive);
        add_tags_from_blocks(ctx.global->tmpblocks, tags, multival);
    }
    gen_tags(buf, ctx.block->opts, code, tags);
}

static void gen_cond_enum(Scratchbuf &buf, code_alc_t &alc, Code *code, const opt_t *opts,
    const StartConds &conds)
{
    DASSERT(opts->target == TARGET_CODE);

    if (code->fmt.format) {
        const char *fmt = code->fmt.format;
        const char *sep = code->fmt.separator;

        for (size_t i = 0; i < conds.size(); ++i) {
            if (i > 0 && sep) buf.cstr(sep);
            std::ostringstream s(fmt);
            // The main substitution (the one allowing unnamed sigil) must go last, or
            // else it will erroneously substitute all the named ones.
            size_t cid = opts->loop_switch ? conds[i].number : i;
            argsubst(s, opts->api_sigil, "num", false, cid);
            argsubst(s, opts->api_sigil, "cond", true, conds[i].name);
            buf.str(s.str());
        }
        buf.cstr("\n");

        code->kind = CODE_RAW;
        code->raw.size = buf.stream().str().length();
        code->raw.data = buf.flush();

    } else {
        const char *start = NULL, *end = NULL;
        CodeList *stmts = code_list(alc);
        CodeList *block = code_list(alc);

        if (opts->lang == LANG_C) {
            start = buf.cstr("enum ").str(opts->yycondtype).cstr(" {").flush();
            end = "};";
            for (size_t i = 0; i < conds.size(); ++i) {
                buf.str(conds[i].name);
                if (opts->loop_switch) {
                    buf.cstr(" = ").u32(conds[i].number);
                }
                append(block, code_text(alc, buf.cstr(",").flush()));
            }
        } else if (opts->lang == LANG_GO) {
            start = buf.cstr("const (").flush();
            end = ")";
            for (size_t i = 0; i < conds.size(); ++i) {
                buf.str(conds[i].name);
                if (opts->loop_switch) {
                    buf.cstr(" = ").u32(conds[i].number);
                } else if (i == 0) {
                    buf.cstr(" = iota");
                }
                append(block, code_text(alc, buf.flush()));
            }
        }

        append(stmts, code_text(alc, start));
        append(stmts, code_block(alc, block, CodeBlock::INDENTED));
        append(stmts, code_text(alc, end));

        code->kind = CODE_BLOCK;
        code->block.stmts = stmts;
        code->block.fmt = CodeBlock::RAW;
    }
}

static void add_condition_from_block(const OutputBlock &block, StartConds &conds,
    const StartCond &cond)
{
    // Condition prefix is specific to the block that defines it. If a few blocks define
    // conditions with the same name, but a different prefix, they should have different
    // enum entries.
    StartCond sc = cond;
    sc.name = block.opts->condEnumPrefix + sc.name;

    for (size_t i = 0; i < conds.size(); ++i) {
        if (conds[i].name == sc.name) {
            if (conds[i].number == sc.number) {
                // A duplicate condition, it's not an error but don't add it.
                return;
            } else {
                // An error: conditions with idetical names but different numbers.
                error("cannot generate condition enumeration: conditon '%s' has "
                    "different numbers in different blocks (use `re2c:condenumprefix` "
                    "configuration to set per-block prefix)", sc.name.c_str());
                exit(1);
            }
        }
    }

    conds.push_back(sc);
}

static void add_conditions_from_blocks(const blocks_t &blocks, StartConds &conds)
{
    for (size_t i = 0; i < blocks.size(); ++i) {
        const OutputBlock &block = *blocks[i];
        for (size_t i = 0; i < block.conds.size(); ++i) {
            add_condition_from_block(block, conds, block.conds[i]);
        }
    }
}

static void expand_cond_enum(CodegenCtxPass1 &ctx, Code *code)
{
    Scratchbuf &buf = ctx.global->scratchbuf;
    code_alc_t &alc = ctx.global->allocator;

    // Use global options accumulated across the whole file, as `types:re2c` may
    // include conditions from a few different blocks, and it is not clear which
    // block's options it should inherit.
    const opt_t *globopts = ctx.global->opts;

    if (globopts->target != TARGET_CODE) {
        code->kind = CODE_EMPTY;
        return;
    }

    StartConds conds;
    if (code->fmt.block_names == NULL) {
        // Gather conditions from all blocks in the output and header files.
        add_conditions_from_blocks(ctx.global->cblocks, conds);
        add_conditions_from_blocks(ctx.global->hblocks, conds);
    } else {
        // Gather conditions from the blocks on the list.
        find_blocks(ctx, code->fmt.block_names, ctx.global->tmpblocks, "types:re2c");
        add_conditions_from_blocks(ctx.global->tmpblocks, conds);
    }

    // Do not generate empty condition enum. Some compilers or language standards
    // allow it, but generally it's more likely to indicate an error in user code.
    if (conds.empty()) {
        code->kind = CODE_EMPTY;
        return;
    }

    gen_cond_enum(buf, alc, code, globopts, conds);
}

static void gen_state_goto_cases(CodegenCtxPass1 &ctx, CodeCases *cases,
    const OutputBlock *block)
{
    code_alc_t &alc = ctx.global->allocator;
    for (storable_states_t::const_iterator i = block->fill_goto.begin();
            i != block->fill_goto.end(); ++i) {
        append(cases, code_case_number(alc, i->second, static_cast<int32_t>(i->first)));
    }
}

static void gen_state_goto(CodegenCtxPass1 &ctx, Code *code)
{
    // If this is a `use:re2c` block, this must be an autogenerated block-local
    // state switch, so use block-local options. Otherwise use global options
    // accumulated across the whole file, as the state switch may include states
    // from a few different blocks and it is not clear which options it should
    // inherit.
    const opt_t *globopts = (ctx.block->kind == INPUT_USE)
        ? ctx.block->opts : ctx.global->opts;

    if (globopts->target != TARGET_CODE) {
        code->kind = CODE_EMPTY;
        return;
    }

    // Loop/switch approach is handled differently (by appending special cases
    // to the state switch).
    DASSERT(!globopts->loop_switch);

    Scratchbuf &o = ctx.global->scratchbuf;
    code_alc_t &alc = ctx.global->allocator;
    const char *text;

    // There are two possibilities:
    //
    // 1. A state switch with an explicit list of block names. This is the case
    //    of a user-defined `getstate:re2c:<name1>[:<name2>...]` directive or a
    //    `use:re2c` block (use blocks have a block-local state switch that is
    //    automatically generated at the beginning of the block, and they have a
    //    special autogenerated name, as they cannot have a user-defined one).
    //
    // 2. A global state switch without a list of block names. This is the case
    //    of a user-defined `getstate:re2c` without a name list, or a global
    //    state switch that is generated automatically if the user did not
    //    specify any explicit `getstate:re2c` directives. The global switch
    //    includes all blocks except `use:re2c` (if a block generates no code it
    //    does not contribute any cases to the state switch).
    //
    bool global = (code->fmt.block_names == NULL);

    CodeCases *cases = code_cases(alc);
    const OutputBlock *bstart = NULL;

    if (global) {
        // No block names are specified: generate a global switch. It includes
        // all blocks except for the `re2c:use` ones which have a local switch.
        const blocks_t &blocks = *ctx.global->pblocks;
        for (size_t i = 0; i < blocks.size(); ++i) {
            const OutputBlock *b = blocks[i];
            if (b->kind != INPUT_USE) {
                gen_state_goto_cases(ctx, cases, b);

                // Use start label of the first non-use block that generates code.
                if (!bstart && b->start_label) bstart = b;
            }
        }
        if (!bstart || !bstart->start_label) {
            // This must be a user-defined directive: the automatic state switch
            // is generated only when processing the first block that has code.
            error("none of the blocks in `getstate:re2c` generate any code");
            exit(1);
        }
    } else {
        // Generate a switch for all specified named blocks.
        blocks_t &blocks = ctx.global->tmpblocks;
        find_blocks(ctx, code->fmt.block_names, blocks, "getstate:re2c");
        for (size_t i = 0; i < blocks.size(); ++i) {
            const OutputBlock *b = blocks[i];
            if (!b->start_label) {
                error("block '%s' does not generate code, so it should not be"
                    " listed in `getstate:re2c` directive", b->name.c_str());
                exit(1);
            }
            // Use start label of the first block on the list.
            if (!bstart) bstart = b;
            gen_state_goto_cases(ctx, cases, b);
        }
    }

    // This is the use that makes 2nd codegen pass for labels necessary.
    Label *lstart = bstart->start_label;
    lstart->used = true;

    CodeList *goto_start = code_list(alc);
    text = o.cstr("goto ").str(bstart->opts->labelPrefix).u32(lstart->index).flush();
    append(goto_start, code_stmt(alc, text));

    if (globopts->bUseStateAbort) {
        // case -1: goto <start label>;
        prepend(cases, code_case_number(alc, goto_start, -1));

        // default: abort();
        CodeList *abort = code_list(alc);
        append(abort, code_stmt(alc, "abort()"));
        prepend(cases, code_case_default(alc, abort));
    } else {
        // default: goto <start label>;
        prepend(cases, code_case_default(alc, goto_start));
    }

    CodeList *stmts = code_list(alc);
    text = o.str(output_state_get(globopts)).flush();
    append(stmts, code_switch(alc, text, cases));

    if (globopts->bUseStateNext) {
        text = o.str(globopts->yynext).cstr(":").flush();
        append(stmts, code_textraw(alc, text));
    }

    code->kind = CODE_BLOCK;
    code->block.stmts = stmts;
    code->block.fmt = CodeBlock::RAW;
}

static void gen_yych_decl(const opt_t *opts, Code *code)
{
    if (opts->bEmitYYCh) {
        code->kind = CODE_VAR;
        code->var.type = opts->yyctype.c_str();
        code->var.name = opts->yych.c_str();
        code->var.init = NULL;
    }
    else {
        code->kind = CODE_EMPTY;
    }
}

static void gen_yyaccept_def(const opt_t *opts, Code *code, bool used_yyaccept)
{
    if (used_yyaccept) {
        code->kind = CODE_VAR;
        code->var.type = "unsigned int";
        code->var.name = opts->yyaccept.c_str();
        code->var.init = "0";
    }
    else {
        code->kind = CODE_EMPTY;
    }
}

static void gen_yystate_def(CodegenCtxPass1 &ctx, Code *code)
{
    const opt_t *opts = ctx.block->opts;
    Scratchbuf &o = ctx.global->scratchbuf;

    if (opts->loop_switch) {
        code->kind = CODE_VAR;
        code->var.name = o.str(opts->yystate).flush();
        if (opts->fFlag) {
            // With storable state `yystate` should be initialized to `YYGETSTATE`.
            // Since there is a -1 case, `yystate` should have a signed type.
            code->var.type = "int";
            code->var.init = o.str(output_state_get(opts)).flush();
        } else {
            code->var.type = "unsigned int";
            code->var.init = "0";
        }
    } else {
        code->kind = CODE_EMPTY;
    }
}

static size_t max_among_blocks(const blocks_t &blocks, size_t max, CodeKind kind)
{
    for (size_t i = 0; i < blocks.size(); ++i) {
        const OutputBlock &block = *blocks[i];
        max = std::max(max, kind == CODE_MAXFILL ? block.max_fill : block.max_nmatch);
    }
    return max;
}

static void gen_yymax(CodegenCtxPass1 &ctx, Code *code)
{
    const opt_t *opts = ctx.block->opts;
    Scratchbuf &o = ctx.global->scratchbuf;

    if (opts->target != TARGET_CODE) {
        code->kind = CODE_EMPTY;
        return;
    }

    CodeKind kind = code->kind;
    const char *dirname = kind == CODE_MAXFILL ? "max:re2c" : "maxnmatch:re2c";
    const char *varname = kind == CODE_MAXFILL ? "YYMAXFILL" : "YYMAXNMATCH";

    size_t max = 1;
    if (code->fmt.block_names == NULL) {
        // Gather max value from all blocks in the output and header files.
        max = max_among_blocks(ctx.global->cblocks, max, kind);
        max = max_among_blocks(ctx.global->hblocks, max, kind);
    } else {
        // Maximum among the blocks listed in the directive.
        find_blocks(ctx, code->fmt.block_names, ctx.global->tmpblocks, dirname);
        max = max_among_blocks(ctx.global->tmpblocks, max, kind);
    }

    if (code->fmt.format) {
        std::ostringstream os(code->fmt.format);
        argsubst(os, opts->api_sigil, "max", true, max);
        code->text = o.str(os.str()).flush();
    } else {
        if (opts->lang == LANG_C) {
            code->text = o.cstr("#define ").cstr(varname).cstr(" ").u64(max).flush();
        } else if (opts->lang == LANG_GO) {
            code->text = o.cstr("var ").cstr(varname).cstr(" int = ").u64(max).flush();
        }
    }
    code->kind = (opts->lang == LANG_C) ? CODE_TEXT : CODE_STMT;
}

/*
 * note [condition order]
 *
 * In theory re2c makes no guarantee about the order of conditions in
 * the generated lexer. Users should define condition type 'YYCONDTYPE'
 * and use values of this type with 'YYGETCONDITION' and 'YYSETCONDITION'.
 * This way code is independent of internal re2c condition numbering.
 *
 * However, it is possible to manually hardcode condition numbers and make
 * re2c generate condition dispatch without explicit use of condition names
 * (nested 'if' statements with '-b' or computed 'goto' table with '-g').
 * This code is syntactically valid (compiles), but unsafe:
 *     - change of re2c options may break compilation
 *     - change of internal re2c condition numbering may break runtime
 *
 * re2c has to preserve the existing numbering scheme.
 *
 * re2c warns about implicit assumptions about condition order, unless:
 *     - condition type is defined with 'types:re2c' or '-t, --type-header'
 *     - dispatch is independent of condition order: either it uses
 *       explicit condition names or there's only one condition and
 *       dispatch shrinks to unconditional jump
 */

static CodeList *gen_cond_goto_binary(CodegenCtxPass1 &ctx, size_t lower, size_t upper)
{
    const opt_t *opts = ctx.block->opts;
    code_alc_t &alc = ctx.global->allocator;
    Scratchbuf &o = ctx.global->scratchbuf;

    CodeList *stmts = code_list(alc);
    if (lower == upper) {
        o.cstr("goto ").str(opts->condPrefix).str(ctx.block->conds[lower].name);
        append(stmts, code_stmt(alc, o.flush()));
    } else {
        const size_t middle = lower + (upper - lower + 1) / 2;
        CodeList *if_then = gen_cond_goto_binary(ctx, lower, middle - 1);
        CodeList *if_else = gen_cond_goto_binary(ctx, middle, upper);
        o.str(output_cond_get(opts)).cstr(" < ").u64(middle);
        append(stmts, code_if_then_else(alc, o.flush(), if_then, if_else));
    }
    return stmts;
}

static void gen_cond_goto(CodegenCtxPass1 &ctx, Code *code)
{
    const opt_t *opts = ctx.block->opts;
    code_alc_t &alc = ctx.global->allocator;
    Scratchbuf &o = ctx.global->scratchbuf;
    const StartConds &conds = ctx.block->conds;
    bool warn_cond_ord = ctx.global->warn_cond_ord;

    const size_t ncond = conds.size();
    CodeList *stmts = code_list(alc);
    const char *text;

    if (opts->target == TARGET_DOT) {
        for (size_t i = 0; i < ncond; ++i) {
            const std::string &cond = conds[i].name;
            text = o.cstr("0 -> ").str(cond).cstr(" [label=\"state=").str(cond)
                .cstr("\"]").flush();
            append(stmts, code_text(alc, text));
        }
    } else {
        if (opts->gFlag) {
            text = o.cstr("goto *").str(opts->yyctable).cstr("[")
                .str(output_cond_get(opts)).cstr("]").flush();
            append(stmts, code_stmt(alc, text));
        } else if (opts->sFlag) {
            warn_cond_ord &= ncond > 1;
            append(stmts, gen_cond_goto_binary(ctx, 0, ncond - 1));
        } else {
            warn_cond_ord = false;

            CodeCases *ccases = code_cases(alc);
            for (size_t i = 0; i < ncond; ++i) {
                const std::string &cond = conds[i].name;

                CodeList *body = code_list(alc);
                text = o.cstr("goto ").str(opts->condPrefix).str(cond).flush();
                append(body, code_stmt(alc, text));

                text = o.str(opts->condEnumPrefix).str(cond).flush();
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

    code->kind = CODE_BLOCK;
    code->block.stmts = stmts;
    code->block.fmt = CodeBlock::RAW;
}

static void gen_cond_table(CodegenCtxPass1 &ctx, Code *code)
{
    const opt_t *opts = ctx.block->opts;
    code_alc_t &alc = ctx.global->allocator;
    Scratchbuf &o = ctx.global->scratchbuf;
    const StartConds &conds = ctx.block->conds;
    const size_t ncond = conds.size();

    CodeList *stmts = code_list(alc);

    o.cstr("static void *").str(opts->yyctable).cstr("[").u64(ncond).cstr("] = {");
    append(stmts, code_text(alc, o.flush()));

    CodeList *block = code_list(alc);
    for (size_t i = 0; i < ncond; ++i) {
        o.cstr("&&").str(opts->condPrefix).str(conds[i].name).cstr(",");
        append(block, code_text(alc, o.flush()));
    }
    append(stmts, code_block(alc, block, CodeBlock::INDENTED));

    append(stmts, code_stmt(alc, "}"));

    code->kind = CODE_BLOCK;
    code->block.stmts = stmts;
    code->block.fmt = CodeBlock::RAW;
}

static void expand_pass_1_list(CodegenCtxPass1 &ctx, CodeList *stmts)
{
    if (!stmts) return;
    for (Code *x = stmts->head; x; x = x->next) {
        expand_pass_1(ctx, x);
    }
}

void expand_pass_1(CodegenCtxPass1 &ctx, Code *code)
{
    const opt_t *opts = ctx.block->opts;
    switch (code->kind) {
        case CODE_BLOCK:
            expand_pass_1_list(ctx, code->block.stmts);
            break;
        case CODE_IF_THEN_ELSE:
            expand_pass_1_list(ctx, code->ifte.if_code);
            expand_pass_1_list(ctx, code->ifte.else_code);
            break;
        case CODE_SWITCH:
            for (CodeCase *x = code->swch.cases->head; x; x = x->next) {
                expand_pass_1_list(ctx, x->body);
            }
            break;
        case CODE_LOOP:
            expand_pass_1_list(ctx, code->loop);
            break;
        case CODE_STAGS:
        case CODE_MTAGS:
            expand_tags_directive(ctx, code);
            break;
        case CODE_MAXFILL:
        case CODE_MAXNMATCH:
            gen_yymax(ctx, code);
            break;
        case CODE_YYCH:
            gen_yych_decl(opts, code);
            break;
        case CODE_YYACCEPT:
            gen_yyaccept_def(opts, code, ctx.block->used_yyaccept);
            break;
        case CODE_YYSTATE:
            gen_yystate_def(ctx, code);
            break;
        case CODE_COND_ENUM:
            expand_cond_enum(ctx, code);
            break;
        case CODE_COND_GOTO:
            gen_cond_goto(ctx, code);
            break;
        case CODE_COND_TABLE:
            gen_cond_table(ctx, code);
            break;
        case CODE_STATE_GOTO:
            gen_state_goto(ctx, code);
            break;
        case CODE_LABEL:
            // Do nothing on the first pass (use information is not available
            // yet, as the rest of the first pass may generate some additional
            // label uses, e.g. for a block start label in `getstate:re2c`).
            break;
        case CODE_EMPTY:
        case CODE_FUNC:
        case CODE_STMT:
        case CODE_TEXT:
        case CODE_RAW:
        case CODE_TEXT_RAW:
        case CODE_SKIP:
        case CODE_PEEK:
        case CODE_BACKUP:
        case CODE_PEEK_SKIP:
        case CODE_SKIP_PEEK:
        case CODE_SKIP_BACKUP:
        case CODE_BACKUP_SKIP:
        case CODE_BACKUP_PEEK:
        case CODE_BACKUP_PEEK_SKIP:
        case CODE_SKIP_BACKUP_PEEK:
        case CODE_LINE_INFO_INPUT:
        case CODE_LINE_INFO_OUTPUT:
        case CODE_VAR:
            break;
    }
}

static void gen_label(Scratchbuf &o, const opt_t *opts, Code *code)
{
    DASSERT(code->kind == CODE_LABEL);
    CodeLabel *label = &code->label;

    if (label->kind == CodeLabel::SLABEL) {
        code->kind = CODE_TEXT_RAW;
        code->text = o.cstr(label->slabel).cstr(":").flush();
    } else if (label->nlabel->used) {
        code->kind = CODE_TEXT_RAW;
        code->text = o.str(opts->labelPrefix).u32(label->nlabel->index).cstr(":").flush();
    } else {
        code->kind = CODE_EMPTY;
    }
}

static void expand_pass_2_list(CodegenCtxPass2 &ctx, CodeList *stmts)
{
    if (!stmts) return;
    for (Code *x = stmts->head; x; x = x->next) {
        expand_pass_2(ctx, x);
    }
}

void expand_pass_2(CodegenCtxPass2 &ctx, Code *code)
{
    switch (code->kind) {
        case CODE_BLOCK:
            expand_pass_2_list(ctx, code->block.stmts);
            break;
        case CODE_IF_THEN_ELSE:
            expand_pass_2_list(ctx, code->ifte.if_code);
            expand_pass_2_list(ctx, code->ifte.else_code);
            break;
        case CODE_SWITCH:
            for (CodeCase *x = code->swch.cases->head; x; x = x->next) {
                expand_pass_2_list(ctx, x->body);
            }
            break;
        case CODE_LOOP:
            expand_pass_2_list(ctx, code->loop);
            break;
        case CODE_LABEL:
            gen_label(ctx.scratchbuf, ctx.opts, code);
            break;
        default:
            break;
    }
}

} // namespace re2c
