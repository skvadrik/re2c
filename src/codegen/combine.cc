#include "config.h"
#include "src/codegen/code.h"
#include "src/options/opt.h"


namespace re2c {

static void combine_code(CodegenCtxPass2 &ctx, Code *code);

static void combine_list(CodegenCtxPass2 &ctx, CodeList *stmts)
{
    // remove empty statements
    for (Code **px = &stmts->head, *x; (x = *px); ) {
        if (x->kind == CODE_EMPTY) {
            *px = x->next;
        }
        else {
            px = &x->next;
        }
    }

    Code *x, *y, *z;
    for (x = stmts->head; x; ) {
        // have three statements ahead
        if ((y = x->next) && (z = y->next)) {
            CodeKind xk = x->kind;
            CodeKind yk = y->kind;
            CodeKind zk = z->kind;

            if (xk == CODE_BACKUP && yk == CODE_PEEK && zk == CODE_SKIP) {
                x->kind = CODE_BACKUP_PEEK_SKIP;
                x->next = z->next;
                continue;
            }
            else if (xk == CODE_SKIP && yk == CODE_BACKUP && zk == CODE_PEEK) {
                x->kind = CODE_SKIP_BACKUP_PEEK;
                x->next = z->next;
                continue;
            }
        }

        // have two statements ahead
        if ((y = x->next)) {
            CodeKind xk = x->kind;
            CodeKind yk = y->kind;

            if (xk == CODE_PEEK && yk == CODE_SKIP) {
                x->kind = CODE_PEEK_SKIP;
                x->next = y->next;
                continue;
            }
            else if (xk == CODE_SKIP && yk == CODE_PEEK) {
                x->kind = CODE_SKIP_PEEK;
                x->next = y->next;
                continue;
            }
            else if (xk == CODE_SKIP && yk == CODE_BACKUP) {
                x->kind = CODE_SKIP_BACKUP;
                x->next = y->next;
                continue;
            }
            else if (xk == CODE_BACKUP && yk == CODE_PEEK) {
                x->kind = CODE_BACKUP_PEEK;
                x->next = y->next;
                continue;
            }
            else if (xk == CODE_BACKUP && yk == CODE_SKIP) {
                x->kind = CODE_BACKUP_SKIP;
                x->next = y->next;
                continue;
            }
        }

        combine_code(ctx, x);
        x = x->next;
    }
}

void combine_code(CodegenCtxPass2 &ctx, Code *code)
{
    // don't recurse into other constructs because they have no skip/peek/backup
    if (code->kind == CODE_BLOCK) {
        combine_list(ctx, code->block.stmts);
    }
}

void combine(CodegenCtxPass2 &ctx, Code *code)
{
    // folding skip/peek/backup expressions is only possible with default input API
    if (ctx.opts->input_api != INPUT_DEFAULT) return;

    combine_code(ctx, code);
}

} // namespace re2c
