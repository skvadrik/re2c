#include "config.h"
#include "src/codegen/code.h"
#include "src/codegen/helpers.h"
#include "src/msg/msg.h"
#include "src/msg/warn.h"
#include "src/options/opt.h"
#include "src/util/string_utils.h"


namespace re2c {

static const OutputBlock *find_block_with_name(CodegenCtxPass1 &ctx,
    const char *name, const char *where)
{
    const blocks_t &blocks = *ctx.global->pblocks;
    for (size_t i = 0; i < blocks.size(); ++i) {
        const OutputBlock *b = blocks[i];
        if (b->name.compare(name) == 0) return b;
    }
    error("cannot find block '%s' listed in `%s` directive", name, where);
    return NULL;
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

static void expand_tags_directive(CodegenCtxPass1 &ctx, Code *code)
{
    DASSERT(code->kind == CODE_STAGS || code->kind == CODE_MTAGS);
    if (ctx.global->opts->target != TARGET_CODE) {
        code->kind = CODE_EMPTY;
        return;
    }

    Scratchbuf &buf = ctx.global->scratchbuf;
    bool oneval = (code->kind == CODE_STAGS);

    if (code->fmt.block_names == NULL) {
        // Use the global set of tags accumulated from all blocks.
        gen_tags(buf, ctx.block->opts, code,
            oneval ? ctx.global->stags : ctx.global->mtags);
    } else {
        // Gather tags from the blocks on the list.
        const char *directive = oneval ? "stags:re2c" : "mtags:re2c";
        tagnames_t tags;
        for (BlockNameList *p = code->fmt.block_names; p; p = p->next) {
            const OutputBlock *b = find_block_with_name(ctx, p->name, directive);
            if (!b) exit(1);
            if (oneval) {
                tags.insert(b->stags.begin(), b->stags.end());
            } else {
                tags.insert(b->mtags.begin(), b->mtags.end());
            }
        }
        gen_tags(buf, ctx.block->opts, code, tags);
    }
}

static void gen_cond_enum(Scratchbuf &buf, code_alc_t &alc, Code *code,
    const opt_t *opts, const uniq_vector_t<std::string> &conds)
{
    DASSERT(opts->target == TARGET_CODE);

    if (code->fmt.format) {
        const char *fmt = code->fmt.format;
        const char *sep = code->fmt.separator;

        for (size_t i = 0; i < conds.size(); ++i) {
            if (i > 0 && sep) buf.cstr(sep);
            std::ostringstream s(fmt);
            // The main substitution (the one allowing unnamed sigil) must go
            // last, or else it will erroneously substitute all the named ones.
            argsubst(s, opts->api_sigil, "num", false, i);
            argsubst(s, opts->api_sigil, "cond", true, conds[i]);
            buf.str(s.str());
        }
        buf.cstr("\n");

        code->kind = CODE_RAW;
        code->raw.size = buf.stream().str().length();
        code->raw.data = buf.flush();

    } else {
        const char *text, *start = NULL, *end = NULL;
        CodeList *stmts = code_list(alc);
        CodeList *block = code_list(alc);

        if (opts->lang == LANG_C) {
            start = buf.cstr("enum ").str(opts->yycondtype).cstr(" {").flush();
            end = "};";
            for (size_t i = 0; i < conds.size(); ++i) {
                text = buf.str(conds[i]).cstr(",").flush();
                append(block, code_text(alc, text));
            }
        } else if (opts->lang == LANG_GO) {
            start = buf.cstr("const (").flush();
            end = ")";
            for (size_t i = 0; i < conds.size(); ++i) {
                text = buf.str(conds[i]).cstr(i == 0 ? " = iota" : "").flush();
                append(block, code_text(alc, text));
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

    if (code->fmt.block_names == NULL) {
        // Use the global set of conditions accumulated from all blocks.
        gen_cond_enum(buf, alc, code, globopts, ctx.global->conds);
    } else {
        // Gather conditions from the blocks on the list.
        uniq_vector_t<std::string> conds;
        for (BlockNameList *p = code->fmt.block_names; p; p = p->next) {
            const OutputBlock *b = find_block_with_name(ctx, p->name, "types:re2c");
            if (!b) exit(1);
            for (size_t i = 0; i < b->conds.size(); ++i) {
                // Condition prefix is specific to the block that defines it.
                // If a few blocks define conditions with the same name, but a
                // different prefix, they result in different enum entries.
                conds.find_or_add(b->opts->condEnumPrefix + b->conds[i]);
            }
        }
        gen_cond_enum(buf, alc, code, globopts, conds);
    }
}

static void gen_state_goto_cases(CodegenCtxPass1 &ctx, CodeCases *cases,
    const OutputBlock *block)
{
    code_alc_t &alc = ctx.global->allocator;

    uint32_t index_count = block->fill_index_end - block->fill_index_start;
    DASSERT(index_count <= block->fill_goto.size());

    for (uint32_t i = 0; i < index_count; ++i) {
        append(cases, code_case_number(alc, block->fill_goto[i],
            static_cast<int32_t>(i + block->fill_index_start)));
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
        for (BlockNameList *p = code->fmt.block_names; p; p = p->next) {
            const OutputBlock *b = find_block_with_name(ctx, p->name, "getstate:re2c");
            if (!b) exit(1);
            if (!b->start_label) {
                error("block '%s' does not generate code, so it should not be"
                    " listed in `getstate:re2c` directive", p->name);
                exit(1);
            }

            gen_state_goto_cases(ctx, cases, b);

            // Use start label of the first block on the list.
            if (!bstart) bstart = b;
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
    text = o.str(globopts->state_get).cstr(globopts->state_get_naked ? "" : "()").flush();
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

static void gen_yymax(CodegenCtxPass1 &ctx, Code *code)
{
    const opt_t *opts = ctx.block->opts;
    Scratchbuf &o = ctx.global->scratchbuf;

    if (opts->target != TARGET_CODE) {
        code->kind = CODE_EMPTY;
        return;
    }

    bool is_maxfill = (code->kind == CODE_MAXFILL);
    const char *dirname = is_maxfill ? "max:re2c" : "maxnmatch:re2c";
    const char *varname = is_maxfill ? "YYMAXFILL" : "YYMAXNMATCH";

    size_t max;
    if (code->fmt.block_names == NULL) {
        // Global maximum in the file.
        max = is_maxfill ? ctx.global->max_fill : ctx.global->max_nmatch;
    } else {
        // Maximum among the blocks listed in the directive.
        max = 0;
        for (BlockNameList *p = code->fmt.block_names; p; p = p->next) {
            const OutputBlock *b = find_block_with_name(ctx, p->name, dirname);
            if (!b) exit(1);
            max = std::max(max, is_maxfill ? b->max_fill : b->max_nmatch);
        }
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

static std::string output_cond_get(const opt_t *opts)
{
    return opts->cond_get + (opts->cond_get_naked ? "" : "()");
}

static CodeList *gen_cond_goto_binary(Scratchbuf &o, code_alc_t &alc,
    const std::vector<std::string> &conds, const opt_t *opts,
    size_t lower, size_t upper)
{
    CodeList *stmts = code_list(alc);
    const char *text;

    if (lower == upper) {
        text = o.cstr("goto ").str(opts->condPrefix).str(conds[lower]).flush();
        append(stmts, code_stmt(alc, text));
    }
    else {
        const size_t middle = lower + (upper - lower + 1) / 2;
        text = o.str(output_cond_get(opts)).cstr(" < ").u64(middle).flush();
        CodeList *if_then = gen_cond_goto_binary(o, alc, conds, opts, lower, middle - 1);
        CodeList *if_else = gen_cond_goto_binary(o, alc, conds, opts, middle, upper);
        append(stmts, code_if_then_else(alc, text, if_then, if_else));
    }

    return stmts;
}

static void gen_cond_goto(Scratchbuf &o, code_alc_t &alc, Code *code,
    const std::vector<std::string> &conds, const opt_t *opts, Msg &msg,
    bool warn_cond_ord, const loc_t &loc)
{
    const size_t ncond = conds.size();
    CodeList *stmts = code_list(alc);
    const char *text;

    if (opts->target == TARGET_DOT) {
        for (size_t i = 0; i < ncond; ++i) {
            const std::string &cond = conds[i];
            text = o.cstr("0 -> ").str(cond).cstr(" [label=\"state=").str(cond)
                .cstr("\"]").flush();
            append(stmts, code_text(alc, text));
        }
    }
    else {
        if (opts->gFlag) {
            text = o.cstr("goto *").str(opts->yyctable).cstr("[")
                .str(output_cond_get(opts)).cstr("]").flush();
            append(stmts, code_stmt(alc, text));
        }
        else if (opts->sFlag) {
            warn_cond_ord &= ncond > 1;
            append(stmts, gen_cond_goto_binary(o, alc, conds, opts, 0, ncond - 1));
        }
        else {
            warn_cond_ord = false;

            CodeCases *ccases = code_cases(alc);
            for (size_t i = 0; i < ncond; ++i) {
                const std::string &cond = conds[i];

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
            msg.warn.condition_order(loc);
        }
    }

    code->kind = CODE_BLOCK;
    code->block.stmts = stmts;
    code->block.fmt = CodeBlock::RAW;
}

static void gen_cond_table(Scratchbuf &o, code_alc_t &alc, Code *code,
    const std::vector<std::string> &conds, const opt_t *opts)
{
    const size_t ncond = conds.size();

    CodeList *stmts = code_list(alc);
    const char *text;

    text = o.cstr("static void *").str(opts->yyctable).cstr("[").u64(ncond)
        .cstr("] = {").flush();
    append(stmts, code_text(alc, text));

    CodeList *block = code_list(alc);
    for (size_t i = 0; i < ncond; ++i) {
        text = o.cstr("&&").str(opts->condPrefix).str(conds[i]).cstr(",").flush();
        append(block, code_text(alc, text));
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
    Scratchbuf &buf = ctx.global->scratchbuf;
    code_alc_t &alc = ctx.global->allocator;

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
        case CODE_COND_ENUM:
            expand_cond_enum(ctx, code);
            break;
        case CODE_COND_GOTO:
            gen_cond_goto(buf, alc, code, ctx.block->conds, opts,
                ctx.global->msg, ctx.global->warn_cond_ord, ctx.block->loc);
            break;
        case CODE_COND_TABLE:
            gen_cond_table(buf, alc, code, ctx.block->conds, opts);
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
        case CODE_LABEL:
            gen_label(ctx.scratchbuf, ctx.opts, code);
            break;
        default:
            break;
    }
}

} // namespace re2c
