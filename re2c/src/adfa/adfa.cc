#include <assert.h>
#include <algorithm>
#include <limits>
#include <queue>
#include <set>
#include <utility>
#include <vector>

#include "src/adfa/adfa.h"
#include "src/code/go.h"
#include "src/dfa/dfa.h"
#include "src/util/allocate.h"

namespace re2c
{

const size_t Initial::NOSAVE = std::numeric_limits<size_t>::max();

DFA::DFA
    ( const dfa_t &dfa
    , const std::vector<size_t> &fill
    , size_t def
    , size_t key
    , const std::string &nm
    , const std::string &cn
    , uint32_t ln
    , const std::string &su
    )
    : accepts ()
    , name (nm)
    , cond (cn)
    , line (ln)
    , lbChar(0)
    , ubChar(dfa.charset.back())
    , nStates(0)
    , head(NULL)
    , tags0(dfa.tcid0)
    , charset(dfa.charset)
    , rules(dfa.rules)
    , tags(dfa.tags)
    , mtagvers(dfa.mtagvers)
    , finvers(dfa.finvers)
    , tcpool(dfa.tcpool)
    , max_fill (0)
    , max_nmatch(0)
    , need_backup (false)
    , need_accept (false)
    , oldstyle_ctxmarker (false)
    , maxtagver (dfa.maxtagver)
    , def_rule (def)
    , key_size (key)
    , bitmaps (std::min(ubChar, 256u))
    , setup(su)
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
        s->rule_tags = t->tcid[dfa.nchars];
        s->fall_tags = t->tcid[dfa.nchars + 1];
        s->fill = fill[i];
        s->fallback = t->fallback; // see note [fallback states]

        s->go.span = allocate<Span>(nchars);
        uint32_t j = 0;
        for (uint32_t c = 0; c < nchars; ++j)
        {
            const size_t to = t->arcs[c];
            const tcid_t tc = t->tcid[c];
            for (;++c < nchars && t->arcs[c] == to && t->tcid[c] == tc;);
            s->go.span[j].to = to == dfa_t::NIL ? NULL : i2s[to];
            s->go.span[j].ub = charset[c];
            s->go.span[j].tags = tc;
        }
        s->go.nSpans = j;
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
        for(uint32_t i = 0; i < s->go.nSpans; ++i)
        {
            State *q = s->go.span[i].to;
            if(q && done.insert(q).second)
            {
                todo.push(q);
            }
        }
    }

    assert(nStates == ord.size());

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
    next->next = s;
}

} // namespace re2c

