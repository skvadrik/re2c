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

void bitmaps_t::gen(Output &o, uint32_t ind)
{
    if (empty() || !used) return;

    const opt_t *opts = o.block().opts;
    const uint32_t nmap = static_cast<uint32_t>(maps.size());
    riter_t b = maps.rbegin(), e = maps.rend();

    o.wind(ind).ws("static const unsigned char ")
        .wstring(opts->yybm).ws("[] = {");

    for (uint32_t i = 0, t = 1; b != e; i += ncunit, t += 8) {
        memset(buffer, 0, ncunit * sizeof(uint32_t));

        for (uint32_t m = 0x80; b != e && m; m >>= 1, ++b) {
            b->i = i;
            b->m = m;
            doGen(b->go, b->on, buffer, 0, m);
        }

        if (nmap > 8) {
            o.ws("\n").wind(ind + 1).ws("/* table ").wu32(t).ws(" .. ")
                .wu32(std::min(nmap, t + 7)).ws(": ").wu32(i).ws(" */");
        }

        for (uint32_t c = 0; c < ncunit; ++c) {
            if (c % 8 == 0) {
                o.ws("\n").wind(ind + 1);
            }
            if (opts->yybmHexTable) {
                o.wu32_hex(buffer[c]);
            } else {
                o.wu32_width(buffer[c], 3);
            }
            o.ws(", ");
        }
    }

    o.ws("\n").wind(ind).ws("};\n");
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
