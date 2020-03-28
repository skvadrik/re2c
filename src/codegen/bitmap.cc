#include <string.h> // memset
#include <algorithm> // min

#include "src/codegen/bitmap.h"
#include "src/codegen/go.h"
#include "src/codegen/output.h"
#include "src/options/opt.h"
#include "src/dfa/tcmd.h"


namespace re2c {

static bool matches(const Go *go1, const State *s1, const Go *go2, const State *s2);
static void doGen(const Go *g, const State *s, uint32_t *bm, uint32_t f, uint32_t m);

bitmaps_t::bitmaps_t(uint32_t n)
    : maps()
    , ncunit(n)
    , buffer(new uint32_t[ncunit])
    , used(false)
{}

bitmaps_t::~bitmaps_t()
{
    delete[] buffer;
}

void bitmaps_t::insert(const Go *go, const State *s)
{
    rciter_t i = maps.rbegin(), e = maps.rend();
    for (; i != e; ++i) {
        if (matches(i->go, i->on, go, s)) return;
    }

    bitmap_t b = {go, s, 0, 0};
    maps.push_back(b);
}

const bitmap_t *bitmaps_t::find(const Go *go, const State *s) const
{
    rciter_t i = maps.rbegin(), e = maps.rend();
    for (; i != e; ++i) {
        if (i->on == s && matches(i->go, i->on, go, s)) return &(*i);
    }
    return NULL;
}

bool bitmaps_t::empty() const { return maps.empty(); }

CodeStmts *bitmaps_t::gen(Output &output)
{
    if (empty() || !used) return NULL;

    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;

    CodeStmts *stmts = code_stmts(alc);

    const uint32_t nmap = static_cast<uint32_t>(maps.size());
    riter_t b = maps.rbegin(), e = maps.rend();

    o.cstr("static const unsigned char ").str(opts->yybm).cstr("[] = {");
    append_stmt(stmts, code_stmt_text(alc, o.flush()));

    CodeStmts *block = code_stmts(alc);
    static const uint32_t TABLE_WIDTH = 8;

    for (uint32_t i = 0, t = 1; b != e; i += ncunit, t += TABLE_WIDTH) {
        memset(buffer, 0, ncunit * sizeof(uint32_t));

        for (uint32_t m = 0x80; b != e && m; m >>= 1, ++b) {
            b->i = i;
            b->m = m;
            doGen(b->go, b->on, buffer, 0, m);
        }

        if (nmap > TABLE_WIDTH) {
            o.cstr("/* table ").u32(t).cstr(" .. ").u32(std::min(nmap, t + 7))
                .cstr(": ").u32(i).cstr(" */");
            append_stmt(block, code_stmt_text(alc, o.flush()));
        }

        for (uint32_t i = 0; i < ncunit / TABLE_WIDTH; ++i) {
            for (uint32_t j = 0; j < TABLE_WIDTH; ++j) {
                const uint32_t c = buffer[i * TABLE_WIDTH + j];
                if (opts->yybmHexTable) {
                    o.u32_hex(c, opts);
                }
                else {
                    o.u32_width(c, 3);
                }
                o.cstr(", ");
            }
            append_stmt(block, code_stmt_text(alc, o.flush()));
        }
    }

    append_stmt(stmts, code_block(alc, block, CodeBlock::INDENTED));

    o.cstr("};");
    append_stmt(stmts, code_stmt_text(alc, o.flush()));

    return stmts;
}

void doGen(const Go *g, const State *s, uint32_t *bm, uint32_t f, uint32_t m)
{
    Span *b = g->span, *e = &b[g->nSpans];
    uint32_t lb = 0;

    for (; b < e; ++b)
    {
        if (b->to == s)
        {
            for (; lb < b->ub && lb < 256; ++lb)
            {
                bm[lb-f] |= m;
            }
        }

        lb = b->ub;
    }
}

// All spans in b1 that lead to s1 are pairwise equal to that in b2 leading to s2
bool matches(const Go *go1, const State *s1, const Go *go2, const State *s2)
{
    const Span
        *b1 = go1->span, *e1 = &b1[go1->nSpans],
        *b2 = go2->span, *e2 = &b2[go2->nSpans];
    uint32_t lb1 = 0, lb2 = 0;

    for (;;)
    {
        for (; b1 < e1 && b1->to != s1; ++b1)
        {
            lb1 = b1->ub;
        }
        for (; b2 < e2 && b2->to != s2; ++b2)
        {
            lb2 = b2->ub;
        }
        if (b1 == e1)
        {
            return b2 == e2;
        }
        if (b2 == e2)
        {
            return false;
        }
        // tags are forbidden: transitions on different symbols
        // might go to the same state, but have different tag sets
        if (lb1 != lb2
            || b1->ub != b2->ub
            || b1->tags != TCID0
            || b2->tags != TCID0)
        {
            return false;
        }
        ++b1;
        ++b2;
    }
}

} // end namespace re2c
