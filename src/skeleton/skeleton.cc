#include <algorithm>

#include "src/debug/debug.h"
#include "src/dfa/dfa.h"
#include "src/options/opt.h"
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

void Node::init(const dfa_state_t *s, const std::vector<uint32_t> &charset,
    size_t nil, range_allocator_t &allocator)
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
        Node::range_t *r = allocator.alloc();
        r->lower = l;
        r->upper = u - 1;
        r->cmd = t;

        // insert range at the end of a circular list
        if (arcs[j] == NULL) {
            arcs[j] = r->next = r;
        } else {
            range_t *p0 = arcs[j], *p = p0;
            for (; p->next != p0; p = p->next);
            p->next = r;
            r->next = p0;
        }

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

const uint32_t Skeleton::DEFTAG = std::numeric_limits<uint32_t>::max();

Skeleton::Skeleton(const dfa_t &dfa, const opt_t *opts, const std::string &name,
        const std::string &cond, const loc_t &loc, Msg &msg)
    : opts(opts)
    , name(name)
    , cond(cond)
    , loc(loc)
    , msg(msg)
    , range_allocator()
    , nodes_count(dfa.states.size() + 1) // +1 for default state
    , nodes(new Node[nodes_count])
    , cmd0(dfa.tcmd0)
    , sizeof_key(8)
    , def_rule(dfa.def_rule)
    , eof_rule(dfa.eof_rule)
    , ntagver(static_cast<size_t>(dfa.maxtagver) + 1)
    , charset(dfa.charset)
    , rules(dfa.rules)
    , tags(dfa.tags)
    , finvers(dfa.finvers)
    , tagvals(new uint32_t[ntagver])
    , tagtrie()
    , mtagval()
    , arc_iters()
    , char_iters()
    , buf_data()
    , buf_keys()
{
    // initialize nodes
    const size_t nil = nodes_count - 1;
    for (size_t i = 0; i < nil; ++i) {
        nodes[i].init(dfa.states[i], charset, nil, range_allocator);
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

    mtag_trie_init(tagtrie);
    init_membuf(arc_iters, 256);
    init_membuf(char_iters, 256);
    buf_data.init(opts->encoding.szCodeUnit());
    buf_keys.init(sizeof_key);
}

Skeleton::~Skeleton()
{
    delete[] nodes;
    delete[] tagvals;
    mtag_trie_free(tagtrie);
    free_membuf(arc_iters);
    free_membuf(char_iters);
    buf_data.free(opts->encoding.szCodeUnit());
    buf_keys.free(sizeof_key);
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
