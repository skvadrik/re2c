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

void dump_nfa(const Tnfa& nfa) {
    fprintf(stderr,
            "digraph NFA {\n"
            "  rankdir=LR\n"
            "  node[shape=Mrecord fontname=Courier height=0.2 width=0.2]\n"
            "  edge[arrowhead=vee fontname=Courier label=\" \"]\n\n");

    std::vector<bool> visited(nfa.nstates);
    std::vector<TnfaState*> stack{nfa.root};

    while (!stack.empty()) {
        const TnfaState* n = stack.back();
        stack.pop_back();

        if (visited[n->topord]) continue;
        visited[n->topord] = true;

        switch (n->kind) {
        case TnfaState::Kind::ALT:
            fprintf(stderr, "  %u -> %u\n", n->topord, n->out1->topord);
            fprintf(stderr, "  %u -> %u [color=lightgray]\n", n->topord, n->out2->topord);
            stack.push_back(n->out2);
            stack.push_back(n->out1);
            break;
        case TnfaState::Kind::RAN: {
            fprintf(stderr, "  %u -> %u [label=\"", n->topord, n->out1->topord);
            for (const Range* r = n->ran; r; r = r->next()) {
                const uint32_t
                l = r->lower(),
                u = r->upper() - 1;
                fprintf(stderr, "%u", l);
                if (u > l) fprintf(stderr, "-%u", u);
                if (r->next()) fprintf(stderr, ",");
            }
            fprintf(stderr, "\"]\n");
            stack.push_back(n->out1);
            break;
        }
        case TnfaState::Kind::TAG: {
            const Tag& tag = nfa.tags[n->tag.idx];
            fprintf(stderr, "  %u -> %u [label=\"/", n->topord, n->out1->topord);
            dump_tag(tag, n->tag.neg);
            fprintf(stderr, "(%d)", tag.height);
            fprintf(stderr, "\"]\n");
            stack.push_back(n->out1);
            break;
        }
        case TnfaState::Kind::FIN:
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
