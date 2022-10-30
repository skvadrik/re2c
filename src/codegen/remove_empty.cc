#include "src/codegen/output.h"

namespace re2c {

static void remove_empty_list(CodegenCtxPass2& ctx, CodeList* stmts) {
    if (!stmts) return;

    for (Code** px = &stmts->head, *x; (x = *px); ) {
        if (x->kind == CodeKind::EMPTY) {
            *px = x->next;
        } else {
            px = &x->next;
        }
    }

    for (Code* x = stmts->head; x; x = x->next) {
        remove_empty(ctx, x);
    }
}

void remove_empty(CodegenCtxPass2& ctx, Code* code) {
    switch (code->kind) {
    case CodeKind::BLOCK:
        remove_empty_list(ctx, code->block.stmts);
        break;
    case CodeKind::IF_THEN_ELSE:
        remove_empty_list(ctx, code->ifte.if_code);
        remove_empty_list(ctx, code->ifte.else_code);
        break;
    case CodeKind::SWITCH:
        for (CodeCase* x = code->swch.cases->head; x; x = x->next) {
            remove_empty_list(ctx, x->body);
        }
        break;
    case CodeKind::LOOP:
        remove_empty_list(ctx, code->loop);
        break;
    case CodeKind::LABEL:
    case CodeKind::STAGS:
    case CodeKind::MTAGS:
    case CodeKind::MAXFILL:
    case CodeKind::MAXNMATCH:
    case CodeKind::YYCH:
    case CodeKind::YYACCEPT:
    case CodeKind::YYSTATE:
    case CodeKind::COND_ENUM:
    case CodeKind::COND_GOTO:
    case CodeKind::COND_TABLE:
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
