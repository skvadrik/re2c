#include "config.h"
#include "src/codegen/output.h"
#include "src/options/opt.h"

namespace re2c {

static void combine_code(Code* code);

static void combine_list(CodeList* stmts) {
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

        combine_code(x);
        x = x->next;
    }
}

void combine_code(Code* code) {
    // don't recurse into other constructs because they have no skip/peek/backup
    if (code->kind == CodeKind::BLOCK) {
        combine_list(code->block.stmts);
    }
}

static void remove_line_dirs(CodeList* stmts) {
    for (Code** px = &stmts->head, *x; (x = *px);) {
        switch (x->kind) {
        case CodeKind::LINE_INFO_INPUT:
        case CodeKind::LINE_INFO_OUTPUT:
        case CodeKind::EMPTY: // also remove empty statements while at it
            *px = x->next; // remove this code item
            continue; // bypass pointer update at the end of the iteration
        case CodeKind::BLOCK:
            remove_line_dirs(x->block.stmts);
            break;
        case CodeKind::LOOP:
            remove_line_dirs(x->loop);
            break;
        case CodeKind::IF_THEN_ELSE:
            remove_line_dirs(x->ifte.if_code);
            if (x->ifte.else_code) {
                remove_line_dirs(x->ifte.else_code);
            }
            break;
        case CodeKind::SWITCH:
            for (const CodeCase* y = x->swch.cases->head; y; y = y->next) {
                remove_line_dirs(y->body);
            }
            break;
        default:
            // don't recurse into other constructs because they have no line directives
            break;
        }
        px = &(x->next);
    }
}

void codegen_fixup(Output& output) {
    for (const blocks_t& bs : {output.cblocks, output.hblocks}) {
        for (OutputBlock* b : bs) {
            if (!b->opts->line_dirs) {
                // We cannot avoid generating line directives, because some of them must be
                // added in the parser (when block options are not known yet).
                // We have to remove them here (before the rendering phase), or else oneline
                // statement checks will fail.
      
                remove_line_dirs(b->code);
            }
            if (b->opts->api == Api::DEFAULT) {
                // Folding skip/peek/backup expressions is only possible with default input API.
                combine_list(b->code);
            }
        }
    }
}

} // namespace re2c
