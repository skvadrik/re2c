#include <string.h> // memset
#include <algorithm> // min

#include "src/codegen/code.h"
#include "src/options/opt.h"
#include "src/dfa/tcmd.h"


namespace re2c {

// All spans in b1 that lead to s1 are pairwise equal to that in b2 leading to s2
static bool matches(const CodeGo *go1, const State *s1, const CodeGo *go2,
    const State *s2)
{
    const Span
        *b1 = go1->span, *e1 = &b1[go1->nspans],
        *b2 = go2->span, *e2 = &b2[go2->nspans];
    uint32_t lb1 = 0, lb2 = 0;

    for (;;) {
        for (; b1 < e1 && b1->to != s1; ++b1) {
            lb1 = b1->ub;
        }
        for (; b2 < e2 && b2->to != s2; ++b2) {
            lb2 = b2->ub;
        }
        if (b1 == e1) {
            return b2 == e2;
        }
        if (b2 == e2) {
            return false;
        }
        // tags are forbidden: transitions on different symbols
        // might go to the same state, but have different tag sets
        if (lb1 != lb2
                || b1->ub != b2->ub
                || b1->tags != TCID0
                || b2->tags != TCID0) {
            return false;
        }
        ++b1;
        ++b2;
    }
}

void insert_bitmap(code_alc_t &alc, CodeBitmap *bitmap, const CodeGo *go, const State *s)
{
    for (CodeBmState *b = bitmap->states->head; b; b = b->next) {
        if (matches(b->go, b->state, go, s)) return;
    }
    // bitmap list is constructed in reverse
    prepend(bitmap->states, code_bmstate(alc, go, s));
}

CodeBmState *find_bitmap(const CodeBitmap *bitmap, const CodeGo *go, const State *s)
{
    for (CodeBmState *b = bitmap->states->head; b; b = b->next) {
        if (b->state == s && matches(b->go, b->state, go, s)) return b;
    }
    return NULL;
}

CodeList *gen_bitmap(Output &output, const CodeBitmap *bitmap)
{
    if (!bitmap->states->head || !bitmap->used) return NULL;

    uint32_t nmaps = 0;
    for (CodeBmState *b = bitmap->states->head; b; b = b->next) ++nmaps;

    static const uint32_t WIDTH = 8;
    const bool annotate = nmaps > WIDTH;
    const uint32_t nchars = bitmap->nchars;

    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const char *text;

    CodeList *stmts = code_list(alc);

    text = opts->lang == LANG_C
        ? o.cstr("static const unsigned char ").str(opts->yybm).cstr("[] = {").flush()
        : o.str(opts->yybm).cstr(" := []byte{").flush();
    append(stmts, code_text(alc, text));

    CodeList *block = code_list(alc);

    uint32_t *buffer = new uint32_t[nchars];
    uint32_t bmidx = 0;

    // Iterate while there are states that may use bitmaps.
    for (CodeBmState *b = bitmap->states->head; b; ++bmidx) {
        const uint32_t offset = bmidx * nchars;

        // For each state generate a table with one bit per character, denoting
        // if there is a transition on this charater to the destination state.
        // Tables for up to 8 states are overlayed and compressed in one bitmap.
        memset(buffer, 0, nchars * sizeof(uint32_t));
        for (uint32_t mask = 0x80; mask && b; mask >>= 1, b = b->next) {
            b->offset = offset;
            b->mask = mask;

            uint32_t c = 0;
            const Span *span = b->go->span, *last = span + b->go->nspans;
            for (; span < last; ++span) {
                if (span->to == b->state) {
                    for (uint32_t u = std::min(span->ub, nchars); c < u; ++c) {
                        buffer[c] |= mask;
                    }
                }
                c = span->ub;
            }
        }

        // If there are multiple tables, annotate them with comments.
        if (annotate) {
            const uint32_t lowidx = bmidx * WIDTH + 1;
            const uint32_t uppidx = std::min(nmaps, lowidx + 7);
            text = o.cstr("/* table ").u32(lowidx).cstr(" .. ").u32(uppidx)
                .cstr(": ").u32(offset).cstr(" */").flush();
            append(block, code_text(alc, text));
        }

        // Generate code for the table.
        for (uint32_t c = 0; c < nchars; ) {
            for (uint32_t u = c + WIDTH; c < u; ++c) {
                o.yybm_char(buffer[c], opts, 3).cstr(", ");
            }
            text = o.flush();
            append(block, code_text(alc, text));
        }
    }

    delete[] buffer;

    append(stmts, code_block(alc, block, CodeBlock::INDENTED));
    append(stmts, code_stmt(alc, "}"));

    return stmts;
}

} // end namespace re2c
