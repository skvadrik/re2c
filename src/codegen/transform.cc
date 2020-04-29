#include "config.h"
#include "src/codegen/output.h"
#include "src/msg/msg.h"
#include "src/msg/warn.h"
#include "src/options/opt.h"
#include "src/util/string_utils.h"


namespace re2c {

void gen_tags(Scratchbuf &o, Code *code, const std::set<std::string> &tags)
{
    DASSERT(code->kind == Code::STAGS || code->kind == Code::MTAGS);

    const char *fmt = code->tags.fmt;
    const char *sep = code->tags.sep;

    std::set<std::string>::const_iterator tag = tags.begin(), end = tags.end();
    for (; tag != end; ) {
        std::string fmtstr = fmt;
        strrreplace(fmtstr, "@@", *tag);
        o.str(fmtstr);
        if (++tag == end) break;
        o.cstr(sep);
    }
    code->kind = Code::RAW;
    code->raw.size = o.stream().str().length();
    code->raw.data = o.flush();
}

static void gen_cond_enum(Scratchbuf &o, code_alc_t &alc, Code *code,
    const opt_t *opts, const uniq_vector_t<std::string> &condnames)
{
    if (opts->target != TARGET_CODE) {
        code->kind = Code::EMPTY;
        return;
    }

    const char *text;
    CodeList *stmts = code_list(alc);

    text = o.cstr("enum ").str(opts->yycondtype).cstr(" {").flush();
    append(stmts, code_text(alc, text));

    CodeList *block = code_list(alc);
    for (size_t i = 0; i < condnames.size(); ++i) {
        text = o.str(opts->condEnumPrefix).str(condnames[i]).cstr(",").flush();
        append(block, code_text(alc, text));
    }
    append(stmts, code_block(alc, block, CodeBlock::INDENTED));

    append(stmts, code_text(alc, "};"));

    code->kind = Code::BLOCK;
    code->block.stmts = stmts;
    code->block.fmt = CodeBlock::RAW;
}

static void gen_state_goto(Scratchbuf &o, code_alc_t &alc, Code *code,
    uint32_t start_label, uint32_t fill_index, const opt_t *opts)
{
    const char *text;

    CodeList *goto_start = code_list(alc);
    text = o.cstr("goto ").str(opts->labelPrefix).u32(start_label).cstr(";").flush();
    append(goto_start, code_text(alc, text));

    CodeCases *ccases = code_cases(alc);
    if (opts->bUseStateAbort) {
        // default: abort();
        CodeList *abort = code_list(alc);
        append(abort, code_text(alc, "abort();"));
        append(ccases, code_case_default(alc, abort));

        // case -1: goto <start label>;
        append(ccases, code_case_number(alc, goto_start, -1));
    }
    else {
        // default: goto <start label>;
        append(ccases, code_case_default(alc, goto_start));
    }
    for (uint32_t i = 0; i < fill_index; ++i) {
        CodeList *stmts = code_list(alc);

        if (opts->eof != NOEOF) {
            // TODO: render this as a separate statement
            o.cstr("if (").str(output_expr_lessthan(1, opts)).cstr(")")
                .cstr(" goto ").str(opts->labelPrefix).cstr("eof").u32(i).cstr("; ");
        }
        text = o.cstr("goto ").str(opts->yyfilllabel).u32(i).cstr(";").flush();
        append(stmts, code_text(alc, text));

        append(ccases, code_case_number(alc, stmts, static_cast<int32_t>(i)));
    }

    CodeList *stmts = code_list(alc);
    text = o.str(opts->state_get).cstr(opts->state_get_naked ? "" : "()").flush();
    append(stmts, code_switch(alc, text, ccases, false));

    if (opts->bUseStateNext) {
        text = o.str(opts->yynext).cstr(":").flush();
        append(stmts, code_textraw(alc, text));
    }

    code->kind = Code::BLOCK;
    code->block.stmts = stmts;
    code->block.fmt = CodeBlock::RAW;
}

static void gen_yych_decl(const opt_t *opts, Code *code)
{
    if (opts->bEmitYYCh) {
        code->kind = Code::VAR;
        code->var.type = opts->yyctype.c_str();
        code->var.name = opts->yych.c_str();
        code->var.init = NULL;
    }
    else {
        code->kind = Code::EMPTY;
    }
}

static void gen_yyaccept_def(const opt_t *opts, Code *code, bool used_yyaccept)
{
    if (used_yyaccept) {
        code->kind = Code::VAR;
        code->var.type = "unsigned int";
        code->var.name = opts->yyaccept.c_str();
        code->var.init = "0";
    }
    else {
        code->kind = Code::EMPTY;
    }
}

static void gen_yymaxfill(Scratchbuf &o, const opt_t *opts, Code *code,
    size_t max_fill)
{
    if (opts->target == TARGET_CODE) {
        code->kind = Code::TEXT;
        code->text = o.cstr("#define YYMAXFILL ").u64(max_fill).flush();
    }
    else {
        code->kind = Code::EMPTY;
    }
}

static void gen_yymaxnmatch(Scratchbuf &o, const opt_t *opts, Code *code,
    size_t max_nmatch)
{
    if (opts->target == TARGET_CODE && opts->posix_syntax) {
        code->kind = Code::TEXT;
        code->text = o.cstr("#define YYMAXNMATCH ").u64(max_nmatch).flush();
    }
    else {
        code->kind = Code::EMPTY;
    }
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
    Code *stmt = NULL;
    const char *text;

    if (lower == upper) {
        text = o.cstr("goto ").str(opts->condPrefix).str(conds[lower]).cstr(";").flush();
        stmt = code_text(alc, text);
    }
    else {
        const size_t middle = lower + (upper - lower + 1) / 2;
        text = o.str(output_cond_get(opts)).cstr(" < ").u64(middle).flush();
        CodeList *if_then = gen_cond_goto_binary(o, alc, conds, opts, lower, middle - 1);
        CodeList *if_else = gen_cond_goto_binary(o, alc, conds, opts, middle, upper);
        stmt = code_if_then_else(alc, text, if_then, if_else);
    }

    append(stmts, stmt);
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
                .str(output_cond_get(opts)).cstr("];").flush();
            append(stmts, code_text(alc, text));
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
                text = o.cstr("goto ").str(opts->condPrefix).str(cond).cstr(";").flush();
                append(body, code_text(alc, text));

                text = o.str(opts->condEnumPrefix).str(cond).flush();
                append(ccases, code_case_string(alc, body, text));
            }
            text = o.str(output_cond_get(opts)).flush();
            append(stmts, code_switch(alc, text, ccases, false));
        }

        // see note [condition order]
        warn_cond_ord &= opts->header_file.empty();
        if (warn_cond_ord) {
            msg.warn.condition_order(loc);
        }
    }

    code->kind = Code::BLOCK;
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

    append(stmts, code_text(alc, "};"));

    code->kind = Code::BLOCK;
    code->block.stmts = stmts;
    code->block.fmt = CodeBlock::RAW;
}

static void gen_label(Scratchbuf &o, const opt_t *opts, Code *code)
{
    DASSERT(code->kind == Code::LABEL);
    CodeLabel *label = &code->label;

    if (label->kind == CodeLabel::SLABEL) {
        code->kind = Code::TEXT_RAW;
        code->text = o.cstr(label->slabel).cstr(":").flush();
    }
    else if (label->nlabel->used) {
        code->kind = Code::TEXT_RAW;
        code->text = o.str(opts->labelPrefix).u32(label->nlabel->index).cstr(":").flush();
    }
    else {
        code->kind = Code::EMPTY;
    }
}

static void foldexpr(CodeList *stmts)
{
    Code *x, *y, *z;
    for (x = stmts->head; x; ) {
        // have three statements ahead
        if ((y = x->next) && (z = y->next)) {
            Code::Kind xk = x->kind;
            Code::Kind yk = y->kind;
            Code::Kind zk = z->kind;

            if (xk == Code::BACKUP && yk == Code::PEEK && zk == Code::SKIP) {
                x->kind = Code::BACKUP_PEEK_SKIP;
                x->next = z->next;
                continue;
            }
            else if (xk == Code::SKIP && yk == Code::BACKUP && zk == Code::PEEK) {
                x->kind = Code::SKIP_BACKUP_PEEK;
                x->next = z->next;
                continue;
            }
        }

        // have two statements ahead
        if ((y = x->next)) {
            Code::Kind xk = x->kind;
            Code::Kind yk = y->kind;

            if (xk == Code::PEEK && yk == Code::SKIP) {
                x->kind = Code::PEEK_SKIP;
                x->next = y->next;
                continue;
            }
            else if (xk == Code::SKIP && yk == Code::PEEK) {
                x->kind = Code::SKIP_PEEK;
                x->next = y->next;
                continue;
            }
            else if (xk == Code::SKIP && yk == Code::BACKUP) {
                x->kind = Code::SKIP_BACKUP;
                x->next = y->next;
                continue;
            }
            else if (xk == Code::BACKUP && yk == Code::PEEK) {
                x->kind = Code::BACKUP_PEEK;
                x->next = y->next;
                continue;
            }
            else if (xk == Code::BACKUP && yk == Code::SKIP) {
                x->kind = Code::BACKUP_SKIP;
                x->next = y->next;
                continue;
            }
        }

        x = x->next;
    }
}

static void transform_list(CodegenContext &ctx, CodeList *stmts)
{
    for (Code *x = stmts->head; x; x = x->next) {
        transform(ctx, x);
    }

    // remove empty statements
    for (Code **px = &stmts->head, *x; (x = *px); ) {
        if (x->kind == Code::EMPTY) {
            *px = x->next;
        }
        else {
            px = &x->next;
        }
    }

    // combine statements
    if (ctx.opts->input_api == INPUT_DEFAULT) {
        foldexpr(stmts);
    }
}

void transform(CodegenContext &ctx, Code *code)
{
    switch (code->kind) {
        case Code::BLOCK:
            transform_list(ctx, code->block.stmts);
            break;
        // don't recurse into these because they have no skip/peek/backup
        case Code::EMPTY:
        case Code::IF_THEN_ELSE:
        case Code::SWITCH:
        case Code::FUNC:
        case Code::TEXT:
        case Code::RAW:
        case Code::TEXT_RAW:
        case Code::SKIP:
        case Code::PEEK:
        case Code::BACKUP:
        case Code::PEEK_SKIP:
        case Code::SKIP_PEEK:
        case Code::SKIP_BACKUP:
        case Code::BACKUP_SKIP:
        case Code::BACKUP_PEEK:
        case Code::BACKUP_PEEK_SKIP:
        case Code::SKIP_BACKUP_PEEK:
        case Code::LINE_INFO_INPUT:
        case Code::LINE_INFO_OUTPUT:
        case Code::VAR:
            break;
        case Code::STAGS:
            gen_tags(ctx.scratchbuf, code, ctx.allstags);
            break;
        case Code::MTAGS:
            gen_tags(ctx.scratchbuf, code, ctx.allmtags);
            break;
        case Code::YYMAXFILL:
            gen_yymaxfill(ctx.scratchbuf, ctx.opts, code, ctx.maxfill);
            break;
        case Code::YYMAXNMATCH:
            gen_yymaxnmatch(ctx.scratchbuf, ctx.opts, code, ctx.maxnmatch);
            break;
        case Code::YYCH:
            gen_yych_decl(ctx.opts, code);
            break;
        case Code::YYACCEPT:
            gen_yyaccept_def(ctx.opts, code, ctx.used_yyaccept);
            break;
        case Code::COND_ENUM:
            gen_cond_enum(ctx.scratchbuf, ctx.allocator, code, ctx.globopts,
                ctx.allcondnames);
            break;
        case Code::COND_GOTO:
            gen_cond_goto(ctx.scratchbuf, ctx.allocator, code, ctx.condnames,
                ctx.opts, ctx.msg, ctx.warn_cond_ord, ctx.loc);
            break;
        case Code::COND_TABLE:
            gen_cond_table(ctx.scratchbuf, ctx.allocator, code, ctx.condnames,
                ctx.opts);
            break;
        case Code::STATE_GOTO:
            gen_state_goto(ctx.scratchbuf, ctx.allocator, code, 0, ctx.fillidx,
                ctx.globopts);
            break;
        case Code::LABEL:
            gen_label(ctx.scratchbuf, ctx.opts, code);
            break;
    }
}

} // namespace re2c
