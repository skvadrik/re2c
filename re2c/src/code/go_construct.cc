#include <assert.h>
#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <string>
#include <utility>
#include <vector>

#include "src/adfa/action.h"
#include "src/adfa/adfa.h"
#include "src/code/bitmap.h"
#include "src/code/go.h"
#include "src/conf/opt.h"
#include "src/dfa/tcmd.h"
#include "src/util/allocate.h"

namespace re2c
{

static uint32_t unmap (Span * new_span, const Span * old_span, uint32_t old_nspans, const State * x);

bool consume(const State *s)
{
    switch (s->action.type) {
        case Action::RULE:
        case Action::MOVE:
        case Action::ACCEPT: return false;
        case Action::MATCH:
        case Action::INITIAL:
        case Action::SAVE:   return true;
    }
    return true; /* unreachable */
}

Cases::Cases(const Span *spans, uint32_t nspans, bool skip)
    : cases(new Case[nspans])
    , cases_size(0)
{
    assert(nspans > 0);

    // first case is default case
    Case &c = cases[cases_size++];
    const Span *s = spans + (nspans - 1);
    c.to = s->to;
    c.tags = s->tags;
    c.skip = skip && consume(s->to);

    for (uint32_t i = 0, lb = 0; i < nspans; ++i) {
        s = spans + i;
        add(lb, s->ub, s->to, s->tags, skip && consume(s->to));
        lb = s->ub;
    }
}

void Cases::add(uint32_t lb, uint32_t ub, State *to, tcid_t tags, bool skip)
{
    for (uint32_t i = 0; i < cases_size; ++i) {
        Case &c = cases[i];
        if (c.to == to && c.tags == tags) {
            c.ranges.push_back(std::make_pair(lb, ub));
            return;
        }
    }
    Case &c = cases[cases_size++];
    c.ranges.push_back(std::make_pair(lb, ub));
    c.to = to;
    c.tags = tags;
    c.skip = skip;
}

Cond::Cond (const std::string & cmp, uint32_t val)
    : compare (cmp)
    , value (val)
{}

Binary::Binary (const Span * s, uint32_t n, const State * next, bool skip)
    : cond (NULL)
    , thn (NULL)
    , els (NULL)
{
    const uint32_t l = n / 2;
    const uint32_t h = n - l;
    cond = new Cond ("<=", s[l - 1].ub - 1);
    thn = new If (l > 4 ? If::BINARY : If::LINEAR, &s[0], l, next, skip);
    els = new If (h > 4 ? If::BINARY : If::LINEAR, &s[l], h, next, skip);
}

void Linear::add_branch(const Cond *cond, const State *to, tcid_t tags, bool skip)
{
    Branch &b = branches[nbranches++];
    b.cond = cond;
    b.to = to;
    b.tags = tags;
    b.skip = skip;
}

Linear::Linear(const Span *s, uint32_t n, const State *next, bool skip)
    : nbranches(0)
    , branches(new Branch[n])
{
    for (;;) {
        if (n == 1 && s[0].to == next) {
            add_branch(NULL, NULL, s[0].tags, skip && consume(s[0].to));
            return;
        } else if (n == 1) {
            add_branch(NULL, s[0].to, s[0].tags, skip && consume(s[0].to));
            return;
        } else if (n == 2 && s[0].to == next) {
            add_branch(new Cond(">=", s[0].ub), s[1].to, s[1].tags, skip && consume(s[1].to));
            add_branch(NULL, NULL, s[0].tags, skip && consume(s[0].to));
            return;
        } else if (n == 3
            && s[1].to == next
            && s[1].ub - s[0].ub == 1
            && s[2].to == s[0].to
            && s[2].tags == s[0].tags) {
            add_branch(new Cond("!=", s[0].ub), s[0].to, s[0].tags, skip && consume(s[0].to));
            add_branch(NULL, NULL, s[1].tags, skip && consume(s[1].to));
            return;
        } else if (n >= 3
            && s[1].ub - s[0].ub == 1
            && s[2].to == s[0].to
            && s[2].tags == s[0].tags) {
            add_branch(new Cond("==", s[0].ub), s[1].to, s[1].tags, skip && consume(s[1].to));
            n -= 2;
            s += 2;
        } else {
            add_branch(new Cond("<=", s[0].ub - 1), s[0].to, s[0].tags, skip && consume(s[0].to));
            n -= 1;
            s += 1;
        }
    }
}

If::If (type_t t, const Span * sp, uint32_t nsp, const State * next, bool skip)
    : type (t)
    , info ()
{
    switch (type)
    {
        case BINARY:
            info.binary = new Binary (sp, nsp, next, skip);
            break;
        case LINEAR:
            info.linear = new Linear (sp, nsp, next, skip);
            break;
    }
}

SwitchIf::SwitchIf (const Span * sp, uint32_t nsp, const State * next, bool sflag, bool skip)
    : type (IF)
    , info ()
{
    if ((!sflag && nsp > 2) || (nsp > 8 && (sp[nsp - 2].ub - sp[0].ub <= 3 * (nsp - 2))))
    {
        type = SWITCH;
        info.cases = new Cases (sp, nsp, skip);
    }
    else if (nsp > 5)
    {
        info.ifs = new If (If::BINARY, sp, nsp, next, skip);
    }
    else
    {
        info.ifs = new If (If::LINEAR, sp, nsp, next, skip);
    }
}

GoBitmap::GoBitmap (const Span * span, uint32_t nSpans, const Span * hspan,
    uint32_t hSpans, const bitmap_t * bm, const State * bm_state,
    const State * next, bool sflag)
    : bitmap (bm)
    , bitmap_state (bm_state)
    , hgo (NULL)
    , lgo (NULL)
{
    Span * bspan = allocate<Span> (nSpans);
    uint32_t bSpans = unmap (bspan, span, nSpans, bm_state);
    lgo = bSpans == 0
        ? NULL
        : new SwitchIf (bspan, bSpans, next, sflag, false);
    // if there are any low spans, then next state for high spans
    // must be NULL to trigger explicit goto generation in linear 'if'
    hgo = hSpans == 0
        ? NULL
        : new SwitchIf (hspan, hSpans, lgo ? NULL : next, sflag, false);
    operator delete (bspan);
}

const uint32_t CpgotoTable::TABLE_SIZE = 0x100;

CpgotoTable::CpgotoTable (const Span * span, uint32_t nSpans)
    : table (new const State * [TABLE_SIZE])
{
    uint32_t c = 0;
    for (uint32_t i = 0; i < nSpans; ++i)
    {
        for(; c < span[i].ub && c < TABLE_SIZE; ++c)
        {
            table[c] = span[i].to;
        }
    }
}

Cpgoto::Cpgoto (const Span * span, uint32_t nSpans, const Span * hspan,
    uint32_t hSpans, const State * next, bool sflag)
    : hgo (hSpans == 0 ? NULL : new SwitchIf (hspan, hSpans, next, sflag, false))
    , table (new CpgotoTable (span, nSpans))
{}

Dot::Dot (const Span * sp, uint32_t nsp, const State * s)
    : from (s)
    , cases (new Cases (sp, nsp, false))
{}

Go::Go ()
    : nSpans (0)
    , span (NULL)
    , tags (TCID0)
    , skip (false)
    , type (EMPTY)
    , info ()
{}

void Go::init(const State *from, const opt_t *opts, bitmaps_t &bitmaps)
{
    if (nSpans == 0)
    {
        return;
    }

    // initialize high (wide) spans
    uint32_t hSpans = 0;
    const Span * hspan = NULL;
    for (uint32_t i = 0; i < nSpans; ++i)
    {
        if (span[i].ub > 0x100)
        {
            hspan = &span[i];
            hSpans = nSpans - i;
            break;
        }
    }

    bool low_spans_have_tags = false;
    for (uint32_t i = 0; i < nSpans - hSpans; ++i) {
        if (span[i].tags != TCID0) {
            low_spans_have_tags = true;
            break;
        }
    }

    // initialize bitmaps
    uint32_t nBitmaps = 0;
    const bitmap_t *bm = NULL;
    const State *bms = NULL;

    for (uint32_t i = 0; i < nSpans; ++i) {
        const State *s = span[i].to;
        if (!s->isBase) continue;

        const bitmap_t *b = bitmaps.find(this, s);
        if (b) {
            if (bm == NULL) {
                bm = b;
                bms = s;
            }
            ++nBitmaps;
        }
    }

    const uint32_t dSpans = nSpans - hSpans - nBitmaps;
    const bool part_skip = opts->eager_skip && !skip;
    if (opts->target == TARGET_DOT)
    {
        type = DOT;
        info.dot = new Dot (span, nSpans, from);
    }
    else if (opts->gFlag && !part_skip && (dSpans >= opts->cGotoThreshold) && !low_spans_have_tags)
    {
        type = CPGOTO;
        info.cpgoto = new Cpgoto (span, nSpans, hspan, hSpans, from->next, opts->sFlag);
    }
    else if (opts->bFlag && !part_skip && (nBitmaps > 0))
    {
        type = BITMAP;
        info.bitmap = new GoBitmap (span, nSpans, hspan, hSpans, bm, bms, from->next, opts->sFlag);
        bitmaps.used = true;
    }
    else
    {
        type = SWITCH_IF;
        info.switchif = new SwitchIf (span, nSpans, from->next, opts->sFlag, part_skip);
    }
}

/*
 * Find all spans, that map to the given state. For each of them,
 * find upper adjacent span, that maps to another state (if such
 * span exists, otherwize try lower one).
 * If input contains single span that maps to the given state,
 * then output contains 0 spans.
 */
uint32_t unmap (Span * new_span, const Span * old_span, uint32_t old_nspans, const State * x)
{
    uint32_t new_nspans = 0;
    for (uint32_t i = 0; i < old_nspans; ++i)
    {
        if (old_span[i].to != x)
        {
            if (new_nspans > 0
                && new_span[new_nspans - 1].to == old_span[i].to
                && new_span[new_nspans - 1].tags == old_span[i].tags)
                new_span[new_nspans - 1].ub = old_span[i].ub;
            else
            {
                new_span[new_nspans].to = old_span[i].to;
                new_span[new_nspans].ub = old_span[i].ub;
                new_span[new_nspans].tags = old_span[i].tags;
                ++new_nspans;
            }
        }
    }
    if (new_nspans > 0)
        new_span[new_nspans - 1].ub = old_span[old_nspans - 1].ub;
    return new_nspans;
}

} // namespace re2c
