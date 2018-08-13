#include <assert.h>
#include "src/util/c99_stdint.h"
#include <string.h>
#include <algorithm>
#include <utility>
#include <valarray>
#include <vector>

#include "src/adfa/action.h"
#include "src/adfa/adfa.h"
#include "src/code/bitmap.h"
#include "src/code/go.h"
#include "src/conf/msg.h"
#include "src/conf/opt.h"
#include "src/dfa/tcmd.h"
#include "src/re/rule.h"
#include "src/util/allocate.h"

namespace re2c {

void DFA::split(State *s)
{
    State *move = new State;
    addState(move, s);
    move->action.set_move ();
    move->rule = s->rule;
    move->fill = s->fill; /* used by tunneling, ignored by codegen */
    move->go = s->go;
    move->go.tags = TCID0; /* drop hoisted tags */
    move->rule_tags = s->rule_tags;
    move->fall_tags = s->fall_tags;
    s->rule = Rule::NONE;
    s->go.nSpans = 1;
    s->go.span = allocate<Span> (1);
    s->go.span[0].ub = ubChar;
    s->go.span[0].to = move;
    s->go.span[0].tags = TCID0;
}

static uint32_t merge(Span *x, State *fg, State *bg)
{
    Span *f = fg->go.span;
    Span *b = bg->go.span;
    Span *const fe = f + fg->go.nSpans;
    Span *const be = b + bg->go.nSpans;
    Span *const x0 = x;

    for (;!(f == fe && b == be);) {
        if (f->to == b->to && f->tags == b->tags) {
            x->to = bg;
            x->tags = TCID0;
        } else {
            x->to = f->to;
            x->tags = f->tags;
        }
        if (x == x0
            || x[-1].to != x->to
            || x[-1].tags != x->tags) {
            ++x;
        }
        x[-1].ub = std::min(f->ub, b->ub);

        if (f->ub < b->ub) {
            ++f;
        } else if (f->ub > b->ub) {
            ++b;
        } else {
            ++f;
            ++b;
        }
    }

    return static_cast<uint32_t>(x - x0);
}

void DFA::findBaseState()
{
    Span *span = allocate<Span> (ubChar - lbChar);

    for (State *s = head; s; s = s->next)
    {
        if (s->fill == 0)
        {
            for (uint32_t i = 0; i < s->go.nSpans; ++i)
            {
                State *to = s->go.span[i].to;

                if (to->isBase)
                {
                    to = to->go.span[0].to;
                    uint32_t nSpans = merge(span, s, to);

                    if (nSpans < s->go.nSpans)
                    {
                        operator delete (s->go.span);
                        s->go.nSpans = nSpans;
                        s->go.span = allocate<Span> (nSpans);
                        memcpy(s->go.span, span, nSpans*sizeof(Span));
                        break;
                    }
                }
            }
        }
    }

    operator delete (span);
}

/* note [tag hoisting, skip hoisting and tunneling]
 *
 * Tag hoisting is simple: if all transitions have the same commands,
 * they can be hoisted out of conditional branches.
 *
 * Skip hoisting is only relevant with '--eager-skip' option.
 * Normally this option is off and skip is lazy: it happens after
 * transition to the next state, if this state is consuming.
 * However, with '--eager-skip' skip happens before transition to the next
 * state. Different transitions may disagree: some of them go to consuming
 * states, others don't. If they agree, skip can be hoisted (just like tags).
 *
 * '--eager-skip' makes tag hoisting more complicated, because now we have
 * to care about the type of automaton: lookahead TDFAs must skip after
 * writing tags, while non-lookahead TDFAs must skip before writing tags.
 * Therefore skip hoising cannot be done without tag hoisting in lookahead
 * TDFAs, and vice versa with non-lookahead TDFAs.
 * (Note that '--eager-skip' is implied by '--no-lookahead').
 *
 * Tunneling splits base states in two parts: head and body. Body has all
 * the conditional branches (transitions on symbols), while head has just
 * one unconditional jump to body.
 *
 * Normally tag hoisting should go before tunneling: hoisting may add new
 * candidates to be merged by tunneling. However, with '--eager-skip' tag
 * hoisting is interwined with skip hoisting, and the latter needs to know
 * which states are consuming. This is not possible if tunneling is still
 * to be done, because it may turn consuming states into non-consuming ones.
 * Another option is to disallow splitting states with non-hoisted skip
 * in the presence of '--eager-skip' (this way skip hoisting wouldn't need
 * to know tunneling results), but it's much worse for tunneling.
 */

void DFA::prepare(const opt_t *opts)
{
    // create rule states
    std::vector<State*> rule2state(rules.size());
    for (State *s = head; s; s = s->next) {
        if (s->rule != Rule::NONE) {
            if (!rule2state[s->rule]) {
                State *n = new State;
                n->action.set_rule(s->rule);
                rule2state[s->rule] = n;
                addState(n, s);
            }
            for (uint32_t i = 0; i < s->go.nSpans; ++i) {
                if (!s->go.span[i].to) {
                    s->go.span[i].to = rule2state[s->rule];
                    s->go.span[i].tags = s->rule_tags;
                }
            }
        }
    }

    // create default state (if needed)
    State * default_state = NULL;
    for (State * s = head; s; s = s->next)
    {
        for (uint32_t i = 0; i < s->go.nSpans; ++i)
        {
            if (!s->go.span[i].to)
            {
                if (!default_state)
                {
                    default_state = new State;
                    addState(default_state, s);
                }
                s->go.span[i].to = default_state;
            }
        }
    }

    // bind save actions to fallback states and create accept state (if needed)
    if (default_state) {
        for (State *s = head; s; s = s->next) {
            if (s->fallback) {
                const std::pair<const State*, tcid_t> acc(rule2state[s->rule], s->fall_tags);
                s->action.set_save(accepts.find_or_add(acc));
            }
        }
        default_state->action.set_accept(&accepts);
    }

    // tag hoisting should be done after binding default arcs:
    // (which may introduce new tags)
    // see note [tag hoisting, skip hoisting and tunneling]
    if (!opts->eager_skip) {
        hoist_tags();
    }

    // split ``base'' states into two parts
    for (State * s = head; s; s = s->next)
    {
        s->isBase = false;

        if (s->fill != 0)
        {
            for (uint32_t i = 0; i < s->go.nSpans; ++i)
            {
                if (s->go.span[i].to == s)
                {
                    s->isBase = true;
                    split(s);

                    if (opts->bFlag) {
                        bitmaps.insert(&s->next->go, s);
                    }

                    s = s->next;
                    break;
                }
            }
        }
    }
    // find ``base'' state, if possible
    findBaseState();

    // see note [tag hoisting, skip hoisting and tunneling]
    if (opts->eager_skip) {
        hoist_tags_and_skip(opts);
    }

    for (State *s = head; s; s = s->next) {
        s->go.init(s, opts, bitmaps);
    }
}

void DFA::calc_stats(uint32_t ln, bool explicit_tags)
{
    // calculate 'YYMAXFILL'
    max_fill = 0;
    for (State * s = head; s; s = s->next)
    {
        if (max_fill < s->fill)
        {
            max_fill = s->fill;
        }
    }

    // calculate 'YYMAXNMATCH'
    max_nmatch = 0;
    const size_t nrule = rules.size();
    for (size_t i = 0; i < nrule; ++i) {
        max_nmatch = std::max(max_nmatch, rules[i].ncap);
    }

    // determine if 'YYMARKER' or 'YYBACKUP'/'YYRESTORE' pair is used
    need_backup = accepts.size () > 0;

    // determine if 'yyaccept' variable is used
    need_accept = accepts.size () > 1;

    // determine if 'YYCTXMARKER' or 'YYBACKUPCTX'/'YYRESTORECTX' pair is used
    // If tags are not enabled explicitely and trailing contexts
    // don't overlap (single variable is enough for all of them), then
    // re2c should use old-style YYCTXMARKER for backwards compatibility.
    // Note that with generic API fixed-length contexts are forbidden,
    // which may cause additional overlaps.
    oldstyle_ctxmarker = !explicit_tags && maxtagver == 1;

    // error if tags are not enabled, but we need them
    if (!explicit_tags && maxtagver > 1) {
        fatal_l(ln, "overlapping trailing contexts need "
            "multiple context markers, use '-t, --tags' "
            "option and '/*!stags:re2c ... */' directive");
    }
}

void DFA::hoist_tags()
{
    for (State * s = head; s; s = s->next) {
        Span *span = s->go.span;
        const size_t nspan = s->go.nSpans;
        if (nspan == 0) continue;

        tcid_t ts = span[0].tags;
        for (uint32_t i = 1; i < nspan; ++i) {
            if (span[i].tags != ts) {
                ts = TCID0;
                break;
            }
        }
        if (ts != TCID0) {
            s->go.tags = ts;
            for (uint32_t i = 0; i < nspan; ++i) {
                span[i].tags = TCID0;
            }
        }
    }
}

void DFA::hoist_tags_and_skip(const opt_t *opts)
{
    assert(opts->eager_skip);

    for (State * s = head; s; s = s->next) {
        Span *span = s->go.span;
        const size_t nspan = s->go.nSpans;
        if (nspan == 0) continue;

        bool hoist_tags = true, hoist_skip = true;

        // do all spans agree on tags?
        for (uint32_t i = 1; i < nspan; ++i) {
            if (span[i].tags != span[0].tags) {
                hoist_tags = false;
                break;
            }
        }

        // do all spans agree on skip?
        for (uint32_t i = 0; i < nspan; ++i) {
            if (consume(span[i].to) != consume(span[0].to)) {
                hoist_skip = false;
                break;
            }
        }

        if (opts->lookahead) {
            // skip must go after tags
            hoist_skip &= hoist_tags;
        } else {
            // skip must go before tags
            hoist_tags &= hoist_skip;
        }

        // hoisting tags is possible
        if (hoist_tags) {
            s->go.tags = span[0].tags;
            for (uint32_t i = 0; i < nspan; ++i) {
                span[i].tags = TCID0;
            }
        }

        // hoisting skip is possible
        s->go.skip = hoist_skip && consume(span[0].to);
    }
}

} // namespace re2c
