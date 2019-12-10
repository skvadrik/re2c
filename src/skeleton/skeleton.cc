#include <algorithm>

#include "src/debug/debug.h"
#include "src/dfa/dfa.h"
#include "src/skeleton/skeleton.h"


namespace re2c {

struct opt_t;
struct tcmd_t;

Node::Node()
    : arcs()
    , rule(Rule::NONE)
    , cmd(NULL)
    , stacmd(NULL)
{}

void Node::init(const dfa_state_t *s,
    const std::vector<uint32_t> &charset, size_t nil)
{
    const size_t nc = charset.size() - 1;
    for (uint32_t c = 0, l = 0; c < nc;) {

        size_t j = s->arcs[c];
        const tcmd_t *t = s->tcmd[c];
        for (; ++c < nc && s->arcs[c] == j && s->tcmd[c] == t;);
        if (j == dfa_t::NIL) j = nil;

        // all arcs go to default node => this node is final
        if (l == 0 && c == nc && j == nil) break;

        const uint32_t u = charset[c];
        arcs[j].push_back(Node::range_t(l, u - 1, t));

        l = u;
    }

    rule = s->rule;
    cmd = s->tcmd[nc];
    stacmd = s->stacmd;
}

bool Node::end() const
{
    return arcs.size() == 0;
}

const size_t Skeleton::DEFTAG = std::numeric_limits<size_t>::max();

Skeleton::Skeleton(const dfa_t &dfa, const opt_t *op, size_t def
    , const std::string &dfa_name, const std::string &dfa_cond
    , const loc_t &loc, Msg &msg)
    : opts(op)
    , name(dfa_name)
    , cond(dfa_cond)
    , loc(loc)
    , msg(msg)
    , nodes_count(dfa.states.size() + 1) // +1 for default state
    , nodes(new Node[nodes_count])
    , cmd0(dfa.tcmd0)
    , sizeof_key(8)
    , defrule(def)
    , ntagver(static_cast<size_t>(dfa.maxtagver) + 1)
    , charset(dfa.charset)
    , rules(dfa.rules)
    , tags(dfa.tags)
    , finvers(dfa.finvers)
{
    // initialize nodes
    const size_t nil = nodes_count - 1;
    for (size_t i = 0; i < nil; ++i) {
        nodes[i].init(dfa.states[i], charset, nil);
    }

    // initialize size of key
    const size_t maxlen = maxpath(*this);
    const size_t maxrule = dfa.rules.size() + 1; // +1 for none-rule
    const size_t max = std::max(maxlen, maxrule);
    if (max <= std::numeric_limits<uint8_t>::max()) {
        sizeof_key = 1;
    } else if (max <= std::numeric_limits<uint16_t>::max()) {
        sizeof_key = 2;
    } else if (max <= std::numeric_limits<uint32_t>::max()) {
        sizeof_key = 4;
    }
}

Skeleton::~Skeleton()
{
    delete[] nodes;
}

uint64_t rule2key(size_t rule, size_t key, size_t def)
{
    switch (key) {
        case 8: return rule2key<uint64_t>(rule, def);
        case 4: return rule2key<uint32_t>(rule, def);
        case 2: return rule2key<uint16_t>(rule, def);
        case 1: return rule2key<uint8_t>(rule, def);
    }
    // shouldn't happen
    DASSERT(false);
    return 0;
}

} // namespace re2c
