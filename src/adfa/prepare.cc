#include "src/util/c99_stdint.h"
#include <string.h>
#include <algorithm>
#include <utility>
#include <valarray>
#include <vector>

#include "src/adfa/action.h"
#include "src/adfa/adfa.h"
#include "src/codegen/bitmap.h"
#include "src/codegen/go.h"
#include "src/debug/debug.h"
#include "src/dfa/tcmd.h"
#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/regexp/rule.h"
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
    move->stadfa_tags = TCID0;
    move->rule_tags = s->rule_tags;
    move->fall_tags = s->fall_tags;
    s->rule = Rule::NONE;
    s->go.nSpans = 1;
    s->go.span = allocate<Span> (1);
    s->go.span[0].ub = ubChar;
    s->go.span[0].to = move;
    s->go.span[0].tags = TCID0;
}

static uint32_t merge(Span *x, State *fg, State *bg, const opt_t *opts)
{
    Span *f = fg->go.span;
    Span *b = bg->go.span;
    Span *const fe = f + fg->go.nSpans;
    Span *const be = b + bg->go.nSpans;
    Span *const x0 = x;
    const uint32_t eofub = opts->eof + 1;

    for (;!(f == fe && b == be);) {
        if (f->to == b->to
                && f->tags == b->tags
                && f->ub != eofub
                && b->ub != eofub) {
            x->to = bg;
            x->tags = TCID0;
        }
        else {
            x->to = f->to;
            x->tags = f->tags;
            x->ub = f->ub;
        }
        if (x == x0
                || x[-1].to != x->to
                || x[-1].tags != x->tags
                || x[-1].ub == eofub
                || f->ub == eofub
                || b->ub == eofub) {
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

void DFA::findBaseState(const opt_t *opts)
{
    Span *span = allocate<Span> (ubChar - lbChar);

    for (State *s = head; s; s = s->next) {
        if (s->fill == 0) {
            for (uint32_t i = 0; i < s->go.nSpans; ++i) {
                State *to = s->go.span[i].to;

                if (to->isBase
                    && to->go.span[0].to->stadfa_tags == s->stadfa_tags) {

                    DASSERT(s->stadfa_tags == TCID0);

                    to = to->go.span[0].to;
                    uint32_t nSpans = merge(span, s, to, opts);

                    if (nSpans < s->go.nSpans) {
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
    for (State *s = head; s; s = s->next) {
        if (s->rule != Rule::NONE) {
            if (!finstates[s->rule]) {
                State *n = new State;
                if (s->rule == def_rule) {
                    defstate = n;
                }
                n->action.set_rule(s->rule);
                finstates[s->rule] = n;
                addState(n, s);
            }
            for (uint32_t i = 0; i < s->go.nSpans; ++i) {
                if (!s->go.span[i].to) {
                    s->go.span[i].to = finstates[s->rule];
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
                    defstate = default_state;
                    addState(default_state, s);
                }
                s->go.span[i].to = defstate;
            }
        }
    }

    // bind save actions to fallback states and create accept state (if needed)
    if (default_state) {
        for (State *s = head; s; s = s->next) {
            if (s->fallback) {
                const std::pair<const State*, tcid_t> acc(finstates[s->rule], s->fall_tags);
                s->action.set_save(accepts.find_or_add(acc));
            }
        }
        defstate->action.set_accept(&accepts);
    }

    // tag hoisting should be done after binding default arcs:
    // (which may introduce new tags)
    // see note [tag hoisting, skip hoisting and tunneling]
    if (!opts->eager_skip) {
        hoist_tags(opts);
    }

    // split ``base'' states into two parts
    for (State * s = head; s; s = s->next) {
        s->isBase = false;

        if (s->fill != 0) {
            for (uint32_t i = 0; i < s->go.nSpans; ++i) {
                if (s->go.span[i].to == s) {
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
    findBaseState(opts);

    // see note [tag hoisting, skip hoisting and tunneling]
    if (opts->eager_skip) {
        hoist_tags_and_skip(opts);
    }

    for (State *s = head; s; s = s->next) {
        s->go.init(s, opts, bitmaps);
    }
}

void DFA::calc_stats(const opt_t *opts)
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

    // Determine if re2c should use 'YYCTXMARKER' ('YYBACKUPCTX'/'YYRESTORECTX'
    // in the case of generic API) instead of tag variables. This is needed for
    // backwards compatibility with the code that predates tags. Note that in
    // some cases trailing contexts overlap and a single variable is not enough
    // to hold them all -- in these cases autogenerated code was incorrect, so
    // it is ok to break backwards compatibility. Note that with generic API
    // fixed-length contexts are forbidden, which may cause additional overlaps.
    // In the case of staDFA always use tags, because there is no backwards
    // compatibility requirement (staDFA feature was added after tags).
    oldstyle_ctxmarker = !opts->tags && maxtagver == 1 && !opts->stadfa;

    // error if tags are not enabled, but we need them
    if (!opts->tags && maxtagver > 1) {
        msg.fatal(loc, "overlapping trailing contexts need "
            "multiple context markers, use '-t, --tags' "
            "option and '/*!stags:re2c ... */' directive");
    }
}

static bool can_hoist_tags(const State *s, const opt_t *opts)
{
    Span *span = s->go.span;
    const size_t nspan = s->go.nSpans;
    DASSERT(nspan != 0);

    if (nspan == 1 && s->rule != Rule::NONE) return false;

    // check that all transitions agree on tags
    tcid_t tags = span[0].tags;
    for (uint32_t i = 1; i < nspan; ++i) {
        if (span[i].tags != tags) {
            return false;
        }
    }

    // if EOF rule is used, also check final/fallback tags, as it can be that
    // EOF is reached and the final/fallback transition should be taken.
    if (opts->eof != NOEOF
            && tags != (s->rule == Rule::NONE ? s->fall_tags : s->rule_tags)) {
        return false;
    }

    return true;
}

void DFA::hoist_tags(const opt_t *opts)
{
    for (State * s = head; s; s = s->next) {
        Span *span = s->go.span;
        const size_t nspan = s->go.nSpans;
        if (nspan == 0) continue;

        if (can_hoist_tags(s, opts)) {
            s->go.tags = span[0].tags;
            for (uint32_t i = 0; i < nspan; ++i) {
                span[i].tags = TCID0;
            }
        }
    }
}

void DFA::hoist_tags_and_skip(const opt_t *opts)
{
    DASSERT(opts->eager_skip);

    for (State * s = head; s; s = s->next) {
        Span *span = s->go.span;
        const size_t nspan = s->go.nSpans;
        if (nspan == 0) continue;

        // do all spans agree on tags?
        bool hoist_tags = can_hoist_tags(s, opts);

        // do all spans agree on skip?
        bool hoist_skip = true;
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
