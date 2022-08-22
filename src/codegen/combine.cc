#include "config.h"
#include "src/codegen/code.h"
#include "src/options/opt.h"

namespace re2c {

static void combine_code(CodegenCtxPass2& ctx, Code* code);

static void combine_list(CodegenCtxPass2& ctx, CodeList* stmts) {
    Code* x, *y, *z;
    for (x = stmts->head; x; ) {
        // have three statements ahead
        if ((y = x->next) && (z = y->next)) {
            CodeKind xk = x->kind;
            CodeKind yk = y->kind;
            CodeKind zk = z->kind;

            if (xk == CodeKind::BACKUP && yk == CodeKind::PEEK && zk == CodeKind::SKIP) {
                x->kind = CodeKind::BACKUP_PEEK_SKIP;
                x->next = z->next;
                continue;
            } else if (xk == CodeKind::SKIP && yk == CodeKind::BACKUP && zk == CodeKind::PEEK) {
                x->kind = CodeKind::SKIP_BACKUP_PEEK;
                x->next = z->next;
                continue;
            }
        }

        // have two statements ahead
        if ((y = x->next)) {
            CodeKind xk = x->kind;
            CodeKind yk = y->kind;

            if (xk == CodeKind::PEEK && yk == CodeKind::SKIP) {
                x->kind = CodeKind::PEEK_SKIP;
                x->next = y->next;
                continue;
            } else if (xk == CodeKind::SKIP && yk == CodeKind::PEEK) {
                x->kind = CodeKind::SKIP_PEEK;
                x->next = y->next;
                continue;
            } else if (xk == CodeKind::SKIP && yk == CodeKind::BACKUP) {
                x->kind = CodeKind::SKIP_BACKUP;
                x->next = y->next;
                continue;
            } else if (xk == CodeKind::BACKUP && yk == CodeKind::PEEK) {
                x->kind = CodeKind::BACKUP_PEEK;
                x->next = y->next;
                continue;
            } else if (xk == CodeKind::BACKUP && yk == CodeKind::SKIP) {
                x->kind = CodeKind::BACKUP_SKIP;
                x->next = y->next;
                continue;
            }
        }

        combine_code(ctx, x);
        x = x->next;
    }
}

void combine_code(CodegenCtxPass2& ctx, Code* code) {
    // don't recurse into other constructs because they have no skip/peek/backup
    if (code->kind == CodeKind::BLOCK) {
        combine_list(ctx, code->block.stmts);
    }
}

void combine(CodegenCtxPass2& ctx, Code* code) {
    // folding skip/peek/backup expressions is only possible with default input API
    if (ctx.opts->api != Api::DEFAULT) return;

    combine_code(ctx, code);
}

} // namespace re2c
