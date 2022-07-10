#ifdef RE2C_DEBUG

#include <stdint.h>
#include <stdio.h>
#include <memory>
#include <string>
#include <vector>

#include "src/debug/debug.h"
#include "src/nfa/nfa.h"
#include "src/regexp/tag.h"
#include "src/util/range.h"

namespace re2c {

void dump_nfa(const nfa_t& nfa) {
    fprintf(stderr,
            "digraph NFA {\n"
            "  rankdir=LR\n"
            "  node[shape=Mrecord fontname=Courier height=0.2 width=0.2]\n"
            "  edge[arrowhead=vee fontname=Courier label=\" \"]\n\n");

    std::vector<bool> visited(nfa.nstates);
    std::vector<nfa_state_t*> stack{nfa.root};

    while (!stack.empty()) {
        const nfa_state_t* n = stack.back();
        stack.pop_back();

        if (visited[n->topord]) continue;
        visited[n->topord] = true;

        switch (n->kind) {
        case nfa_state_t::Kind::ALT:
            fprintf(stderr, "  %u -> %u\n", n->topord, n->alt.out1->topord);
            fprintf(stderr, "  %u -> %u [color=lightgray]\n", n->topord, n->alt.out2->topord);
            stack.push_back(n->alt.out2);
            stack.push_back(n->alt.out1);
            break;
        case nfa_state_t::Kind::RAN: {
            fprintf(stderr, "  %u -> %u [label=\"", n->topord, n->ran.out->topord);
            for (const Range* r = n->ran.ran; r; r = r->next()) {
                const uint32_t
                l = r->lower(),
                u = r->upper() - 1;
                fprintf(stderr, "%u", l);
                if (u > l) fprintf(stderr, "-%u", u);
                if (r->next()) fprintf(stderr, ",");
            }
            fprintf(stderr, "\"]\n");
            stack.push_back(n->ran.out);
            break;
        }
        case nfa_state_t::Kind::TAG: {
            const Tag& tag = nfa.tags[n->tag.info.idx];
            fprintf(stderr, "  %u -> %u [label=\"/", n->topord, n->tag.out->topord);
            dump_tag(tag, n->tag.info.neg);
            fprintf(stderr, "(%d)", tag.height);
            fprintf(stderr, "\"]\n");
            stack.push_back(n->tag.out);
            break;
        }
        case nfa_state_t::Kind::FIN:
            fprintf(stderr, "  %u [fillcolor=gray]\n", n->topord);
            break;
        }
    }

    fprintf(stderr, "}\n");
}

void dump_tag(const Tag& tag, bool negative) {
    if (capture(tag)) {
        for (size_t i = tag.lsub; i < tag.hsub; i += 2) {
            fprintf(stderr, "%zu,", i);
        }
        fprintf(stderr, "%zu", tag.hsub);
    } else if (!trailing(tag)) {
        fprintf(stderr, "%s", tag.name);
    }
    fprintf(stderr, "%s", negative ? "&darr;" : "&uarr;");
}

} // namespace re2c

#endif // RE2C_DEBUG
