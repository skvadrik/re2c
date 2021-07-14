#include "src/util/c99_stdint.h"
#include <string.h>
#include <algorithm>
#include <limits>
#include <queue>
#include <set>
#include <utility>
#include <valarray>
#include <vector>

#include "src/adfa/adfa.h"
#include "src/codegen/code.h"
#include "src/debug/debug.h"
#include "src/dfa/dfa.h"
#include "src/dfa/tcmd.h"
#include "src/options/opt.h"
#include "src/regexp/rule.h"
#include "src/util/allocate.h"


namespace re2c {

class Msg;

static bool is_eof(const opt_t *opts, uint32_t ub)
{
    return opts->eof != NOEOF && static_cast<uint32_t>(opts->eof) == ub;
}

DFA::DFA
    ( const dfa_t &dfa
    , const std::vector<size_t> &fill
    , size_t key
    , const loc_t &loc
    , const std::string &nm
    , const std::string &cn
    , const std::string &su
    , const opt_t *opts
    , Msg &msg
    )
    : accepts ()
    , loc (loc)
    , name (nm)
    , cond (cn)
    , lbChar(0)
    , ubChar(dfa.charset.back())
    , nStates(0)
    , head(NULL)
    , defstate(NULL)
    , eof_state(NULL)
    , finstates(dfa.rules.size(), NULL)
    , tags0(dfa.tcid0)
    , charset(dfa.charset)
    , rules(dfa.rules)
    , tags(dfa.tags)
    , mtagvers(dfa.mtagvers)
    , stagnames()
    , stagvars()
    , mtagnames()
    , mtagvars()
    , finvers(dfa.finvers)
    , tcpool(dfa.tcpool)
    , max_fill (0)
    , max_nmatch(0)
    , need_backup (false)
    , need_accept (false)
    , oldstyle_ctxmarker (false)
    , maxtagver (dfa.maxtagver)
    , def_rule(dfa.def_rule)
    , eof_rule(dfa.eof_rule)
    , key_size (key)
    , bitmap(NULL)
    , setup(su)
    , msg(msg)
    , start_label(NULL)
    , initial_label(NULL)
{
    const size_t nstates = dfa.states.size();
    const size_t nchars = dfa.nchars;

    State **i2s = new State*[nstates];
    for (size_t i = 0; i < nstates; ++i)
    {
        i2s[i] = new State;
    }

    State **p = &head;
    for (size_t i = 0; i < nstates; ++i)
    {
        dfa_state_t *t = dfa.states[i];
        State *s = i2s[i];

        ++nStates;
        *p = s;
        p = &s->next;

        s->rule = t->rule;
        s->stadfa_tags = t->stacid;
        s->rule_tags = t->tcid[dfa.nchars];
        s->fall_tags = t->tcid[dfa.nchars + 1];
        s->fill = fill[i];
        s->fallback = t->fallback; // see note [fallback states]

        bool end = true;
        for (uint32_t c = 0; end && c < nchars; ++c) {
            end &= t->arcs[c] == dfa_t::NIL;
        }

        s->go.span = allocate<Span>(nchars);
        uint32_t j = 0;
        for (uint32_t c = 0; c < nchars; ++j) {
            const size_t to = t->arcs[c];
            const tcid_t tc = t->tcid[c];
            const bool ie = is_eof(opts, charset[c]);
            for (;++c < nchars
                && t->arcs[c] == to
                && t->tcid[c] == tc
                && (end || is_eof(opts, charset[c]) == ie)
                ;);
            s->go.span[j].to = to == dfa_t::NIL ? NULL : i2s[to];
            s->go.span[j].ub = charset[c];
            s->go.span[j].tags = tc;
        }
        s->go.nspans = j;
    }
    *p = NULL;

    delete[] i2s;
}

DFA::~DFA()
{
    State *s;

    while ((s = head))
    {
        head = s->next;
        delete s;
    }

    delete &charset;
    delete &rules;
    delete &tags;
    delete &mtagvers;
    delete[] finvers;
    delete &tcpool;
}

/* note [reordering DFA states]
 *
 * re2c-generated code depends on the order of states in DFA: simply
 * flipping two states may change the output significantly.
 * The order of states is affected by many factors, e.g.:
 *   - flipping left and right subtrees of alternative when constructing
 *     AST (also applies to iteration and counted repetition)
 *   - changing the order in which graph nodes are visited (applies to
 *     any intermediate representation: bytecode, NFA, DFA, etc.)
 *
 * To make the resulting code independent of such changes, we hereby
 * reorder DFA states. The ordering scheme is very simple:
 *
 * Starting with DFA root, walk DFA nodes in breadth-first order.
 * Child nodes are ordered accoding to the (alphabetically) first symbol
 * leading to each node. Each node must be visited exactly once.
 * Default state (NULL) is always the last state.
 */
void DFA::reorder()
{
    std::vector<State*> ord;
    ord.reserve(nStates);

    std::queue<State*> todo;
    todo.push(head);

    std::set<State*> done;
    done.insert(head);

    for(;!todo.empty();)
    {
        State *s = todo.front();
        todo.pop();
        ord.push_back(s);
        for(uint32_t i = 0; i < s->go.nspans; ++i)
        {
            State *q = s->go.span[i].to;
            if(q && done.insert(q).second)
            {
                todo.push(q);
            }
        }
    }

    DASSERT(nStates == ord.size());

    ord.push_back(NULL);
    for(uint32_t i = 0; i < nStates; ++i)
    {
        ord[i]->next = ord[i + 1];
    }
}

void DFA::addState(State *s, State *next)
{
    ++nStates;
    s->next = next->next;
    s->prev = next;
    next->next = s;
    next->prev = s->prev;
}

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
    s->go.nspans = 1;
    s->go.span = allocate<Span> (1);
    s->go.span[0].ub = ubChar;
    s->go.span[0].to = move;
    s->go.span[0].tags = TCID0;
}

static uint32_t merge(Span *x, State *fg, State *bg, const opt_t *opts)
{
    Span *f = fg->go.span;
    Span *b = bg->go.span;
    Span *const fe = f + fg->go.nspans;
    Span *const be = b + bg->go.nspans;
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
            for (uint32_t i = 0; i < s->go.nspans; ++i) {
                State *to = s->go.span[i].to;

                if (to->isBase
                    && to->go.span[0].to->stadfa_tags == s->stadfa_tags) {

                    DASSERT(s->stadfa_tags == TCID0);

                    to = to->go.span[0].to;
                    uint32_t nspans = merge(span, s, to, opts);

                    if (nspans < s->go.nspans) {
                        operator delete (s->go.span);
                        s->go.nspans = nspans;
                        s->go.span = allocate<Span> (nspans);
                        memcpy(s->go.span, span, nspans*sizeof(Span));
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
        if (s->rule != Rule::NONE && s->rule != eof_rule) {
            if (!finstates[s->rule]) {
                State *n = new State;
                if (s->rule == def_rule) {
                    defstate = n;
                }
                n->action.set_rule(s->rule);
                finstates[s->rule] = n;
                addState(n, s);
            }
            for (uint32_t i = 0; i < s->go.nspans; ++i) {
                if (!s->go.span[i].to) {
                    s->go.span[i].to = finstates[s->rule];
                    s->go.span[i].tags = s->rule_tags;
                }
            }
        }

        // last state, add EOF rule if needed (see note [EOF rule handling])
        if (!s->next && opts->eof != NOEOF) {
            eof_state = new State;
            eof_state->action.set_rule(eof_rule);
            finstates[eof_rule] = eof_state;
            addState(eof_state, s);
            break;
        }
    }

    // create default state (if needed)
    State *default_state = NULL;
    for (State *s = head; s; s = s->next) {
        for (uint32_t i = 0; i < s->go.nspans; ++i) {
            if (!s->go.span[i].to) {
                if (!default_state) {
                    default_state = defstate = new State;
                    addState(default_state, s);
                }
                s->go.span[i].to = defstate;
            }
        }
    }

    // With EOF rule there is a default quasi-transition on YYFILL failure, so
    // default state is needed if there is at least one final state with at
    // least one outgoing transition to a non-final state.
    if (!default_state && opts->eof != NOEOF) {
        bool have_fallback_states = false;

        for (State *s = head; s; s = s->next) {
            have_fallback_states |= s->fallback;

            if (!s->next && have_fallback_states) {
                default_state = defstate = new State;
                addState(default_state, s);
                break;
            }
        }
    }

    // bind save actions to fallback states and create accept state (if needed)
    if (default_state) {
        for (State *s = head; s; s = s->next) {
            if (s->fallback) {
                DASSERT(s->rule != eof_rule); // see note [EOF rule handling]
                const std::pair<State*, tcid_t> acc(finstates[s->rule], s->fall_tags);
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
            for (uint32_t i = 0; i < s->go.nspans; ++i) {
                if (s->go.span[i].to == s) {
                    s->isBase = true;
                    split(s);
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
}

void DFA::calc_stats(OutputBlock &out)
{
    const opt_t *opts = out.opts;

    // calculate 'YYMAXFILL'
    max_fill = 0;
    for (State * s = head; s; s = s->next) {
        if (max_fill < s->fill) {
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
        msg.error(loc, "overlapping trailing contexts need "
            "multiple context markers, use '-t, --tags' "
            "option and '/*!stags:re2c ... */' directive");
        exit(1);
    }

    if (!oldstyle_ctxmarker) {
        for (size_t i = 0; i < tags.size(); ++i) {
            const Tag &tag = tags[i];
            if (history(tag)) {
                mtagvars.insert(*tag.name);
            }
            else if (tag.name) {
                stagvars.insert(*tag.name);
            }
        }
        for (tagver_t v = 1; v <= maxtagver; ++v) {
            const std::string s = vartag_name(v, opts->tags_prefix);
            if (mtagvers.find(v) != mtagvers.end()) {
                mtagnames.insert(s);
            }
            else {
                stagnames.insert(s);
            }
        }
        out.stags.insert(stagnames.begin(), stagnames.end());
        out.mtags.insert(mtagnames.begin(), mtagnames.end());
    }

    if (!cond.empty()) {
        out.conds.push_back(cond);
    }
}

static bool can_hoist_tags(const State *s, const opt_t *opts)
{
    Span *span = s->go.span;
    const size_t nspan = s->go.nspans;
    DASSERT(nspan != 0);

    if (nspan == 1 && s->rule != Rule::NONE) return false;

    // check that all transitions agree on tags
    tcid_t tags = span[0].tags;
    for (uint32_t i = 1; i < nspan; ++i) {
        if (span[i].tags != tags) {
            return false;
        }
    }

    // If end-of-input rule $ is used, check that final/fallback tags agree with
    // other tags, as the lexer may follow the final/fallback transition.
    if (opts->eof != NOEOF
        && tags != (s->rule == Rule::NONE ? s->fall_tags : s->rule_tags)) {
        return false;
    }

    // No need to check idempotence of tag operations in case of the end-of-input
    // rule $, as they are applied before YYFILL label and there is no risk of
    // re-application if the current input character is re-scanned after YYFILL.
    return true;
}

static bool can_hoist_skip(const State *s, const opt_t *opts)
{
    Span *span = s->go.span;
    const size_t nspan = s->go.nspans;

    // If the end-of-input rule $ is used, skip cannot be hoisted because the
    // lexer may need to rescan the current input character after YYFILL, and
    // skip operation will be applied twice.
    if (opts->eof != NOEOF) return false;

    // All spans must agree on skip, and they all must be consuming.
    for (uint32_t i = 0; i < nspan; ++i) {
        if (!consume(span[i].to)) return false;
    }

    return true;
}

void DFA::hoist_tags(const opt_t *opts)
{
    for (State * s = head; s; s = s->next) {
        Span *span = s->go.span;
        const size_t nspan = s->go.nspans;
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
        const size_t nspan = s->go.nspans;
        if (nspan == 0) continue;

        // check if it is possible to hoist tags and/or skip
        bool hoist_tags = can_hoist_tags(s, opts);
        bool hoist_skip = can_hoist_skip(s, opts);
        if (opts->lookahead) {
            // skip must go after tags
            hoist_skip &= hoist_tags;
        } else {
            // skip must go before tags
            hoist_tags &= hoist_skip;
        }

        // hoist tags if possible
        if (hoist_tags) {
            s->go.tags = span[0].tags;
            for (uint32_t i = 0; i < nspan; ++i) {
                span[i].tags = TCID0;
            }
        }

        // hoist skip if possible
        s->go.skip = hoist_skip;
    }
}

} // namespace re2c

