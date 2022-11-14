#include "config.h"
#include "src/codegen/output.h"
#include "src/codegen/helpers.h"
#include "src/msg/msg.h"
#include "src/msg/warn.h"
#include "src/options/opt.h"
#include "src/util/attribute.h"
#include "src/util/check.h"
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
    case CodeKind::MAXFILL:
    case CodeKind::MAXNMATCH:
        return gen_yymax(ctx, code);
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
    case CodeKind::DFAS:
        break;
    case CodeKind::STATE_GOTO:
    case CodeKind::STAGS:
    case CodeKind::MTAGS:
    case CodeKind::COND_ENUM:
        UNREACHABLE();
        break;
    }
    return Ret::OK;
}

static void gen_label(Scratchbuf& o, const opt_t* opts, Code* code) {
    DCHECK(code->kind == CodeKind::LABEL);
    CodeLabel* label = &code->label;

    if (label->kind == CodeLabel::Kind::SLABEL) {
        code->kind = CodeKind::TEXT_RAW;
        code->text = o.cstr(label->slabel).cstr(":").flush();
    } else if (label->nlabel->used) {
        DCHECK(label->nlabel->index != Label::NONE);
        code->kind = CodeKind::TEXT_RAW;
        code->text = o.str(opts->label_prefix).u32(label->nlabel->index).cstr(":").flush();
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
    case CodeKind::STAGS:
    case CodeKind::MTAGS:
    case CodeKind::MAXFILL:
    case CodeKind::MAXNMATCH:
    case CodeKind::COND_ENUM:
    case CodeKind::STATE_GOTO:
    case CodeKind::LINE_INFO_INPUT:
    case CodeKind::LINE_INFO_OUTPUT:
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
    case CodeKind::DFAS:
        break;
    }
}

} // namespace re2c
