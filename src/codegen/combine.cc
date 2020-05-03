#include "config.h"
#include "src/codegen/code.h"
#include "src/options/opt.h"


namespace re2c {

static void combine_code(CodegenContext &ctx, Code *code);

static void combine_list(CodegenContext &ctx, CodeList *stmts)
{
    // remove empty statements
    for (Code **px = &stmts->head, *x; (x = *px); ) {
        if (x->kind == Code::EMPTY) {
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

        combine_code(ctx, x);
        x = x->next;
    }
}

void combine_code(CodegenContext &ctx, Code *code)
{
    // don't recurse into other constructs because they have no skip/peek/backup
    if (code->kind == Code::BLOCK) {
        combine_list(ctx, code->block.stmts);
    }
}

void combine(CodegenContext &ctx, Code *code)
{
    // folding skip/peek/backup expressions is only possible with default input API
    if (ctx.opts->input_api != INPUT_DEFAULT) return;

    combine_code(ctx, code);
}

} // namespace re2c
