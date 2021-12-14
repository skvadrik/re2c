#include "src/codegen/code.h"


namespace re2c {

static void remove_empty_list(CodegenCtxPass2 &ctx, CodeList *stmts)
{
    if (!stmts) return;

    for (Code **px = &stmts->head, *x; (x = *px); ) {
        if (x->kind == CODE_EMPTY) {
            *px = x->next;
        } else {
            px = &x->next;
        }
    }

    for (Code *x = stmts->head; x; x = x->next) {
        remove_empty(ctx, x);
    }
}

void remove_empty(CodegenCtxPass2 &ctx, Code *code)
{
    switch (code->kind) {
        case CODE_BLOCK:
            remove_empty_list(ctx, code->block.stmts);
            break;
        case CODE_IF_THEN_ELSE:
            remove_empty_list(ctx, code->ifte.if_code);
            remove_empty_list(ctx, code->ifte.else_code);
            break;
        case CODE_SWITCH:
            for (CodeCase *x = code->swch.cases->head; x; x = x->next) {
                remove_empty_list(ctx, x->body);
            }
            break;
        case CODE_LOOP:
            remove_empty_list(ctx, code->loop);
            break;
        default:
            break;
    }
}

} // namespace re2c
