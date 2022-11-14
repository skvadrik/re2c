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
    case CodeKind::LINE_INFO_INPUT:
    case CodeKind::LINE_INFO_OUTPUT:
        // Although line directives are disabled for Rust, stubs confuse codegen into rendering
        // oneline semantic actions as multiline, which triggers rustc warnings about redundant
        // braces. We replace stubs with empty statements and rely on `remove_empty` pass.
        if (ctx.opts->lang == Lang::RUST) code->kind = CodeKind::EMPTY;
        break;
    case CodeKind::STAGS:
    case CodeKind::MTAGS:
    case CodeKind::MAXFILL:
    case CodeKind::MAXNMATCH:
    case CodeKind::COND_ENUM:
    case CodeKind::STATE_GOTO:
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
