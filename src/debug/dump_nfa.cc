#ifdef RE2C_DEBUG

#include "src/util/c99_stdint.h"
#include <stdio.h>
#include <memory>
#include <string>
#include <vector>

#include "src/debug/debug.h"
#include "src/nfa/nfa.h"
#include "src/regexp/tag.h"
#include "src/util/range.h"


namespace re2c {

uint32_t index(const nfa_t &nfa, const nfa_state_t *s)
{
    return static_cast<uint32_t>(s - nfa.states);
}

void dump_nfa(const nfa_t &nfa)
{
    fprintf(stderr,
        "digraph NFA {\n"
        "  rankdir=LR\n"
        "  node[shape=Mrecord fontname=Courier height=0.2 width=0.2]\n"
        "  edge[arrowhead=vee fontname=Courier label=\" \"]\n\n");

    for (uint32_t i = static_cast<uint32_t>(nfa.size); i --> 0;) {
        const nfa_state_t *n = &nfa.states[i];

        fprintf(stderr, "  n%u [label=\"%u\"]", i, i);
        if (n->type == nfa_state_t::FIN) {
            fprintf(stderr, " [fillcolor=gray]");
        }
        fprintf(stderr, "\n");

        switch (n->type) {
            case nfa_state_t::ALT:
                fprintf(stderr, "  n%u -> n%u\n", i, index(nfa, n->alt.out1));
                fprintf(stderr, "  n%u -> n%u [color=lightgray]\n", i, index(nfa, n->alt.out2));
                break;
            case nfa_state_t::RAN: {
                fprintf(stderr, "  n%u -> n%u [label=\"", i, index(nfa, n->ran.out));
                for (const Range *r = n->ran.ran; r; r = r->next()) {
                    const uint32_t
                        l = r->lower(),
                        u = r->upper() - 1;
                    fprintf(stderr, "%u", l);
                    if (u > l) fprintf(stderr, "-%u", u);
                    if (r->next()) fprintf(stderr, ",");
                }
                fprintf(stderr, "\"]\n");
                break;
            }
            case nfa_state_t::TAG: {
                const Tag &tag = nfa.tags[n->tag.info.idx];
                fprintf(stderr, "  n%u -> n%u [label=\"/", i, index(nfa, n->tag.out));
                dump_tag(tag, n->tag.info.neg);
                fprintf(stderr, "(%d)", tag.height);
                fprintf(stderr, "\"]\n");
                break;
            }
            case nfa_state_t::FIN:
                break;
            case nfa_state_t::NIL:
                fprintf(stderr, "  n%u -> n%u\n", i, index(nfa, n->nil.out));
                break;
        }
    }

    fprintf(stderr, "}\n");
}

void dump_tag(const Tag &tag, bool negative)
{
    if (capture(tag)) {
        for (size_t i = tag.lsub; i < tag.hsub; i += 2) {
            fprintf(stderr, "%u,", (uint32_t)i);
        }
        fprintf(stderr, "%u", (uint32_t)tag.hsub);
    }
    else if (!trailing(tag)) {
        fprintf(stderr, "%s", tag.name->c_str());
    }
    fprintf(stderr, "%s", negative ? "&darr;" : "&uarr;");
}

} // namespace re2c

#endif // RE2C_DEBUG
