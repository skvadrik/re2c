#ifdef RE2C_DEBUG

#include <stdint.h>
#include <map>
#include <stdio.h>
#include <string>
#include <utility>
#include <vector>

#include "src/adfa/adfa.h"
#include "src/debug/debug.h"
#include "src/dfa/tcmd.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"

namespace re2c {

static void dump_adfa_range(uint32_t lower, uint32_t upper) {
    fprintf(stderr, "%u", lower);
    if (--upper > lower) {
        fprintf(stderr, "-%u", upper);
    }
}

void dump_adfa(const Adfa& dfa) {
    std::map<const State*, uint32_t> st2idx;
    uint32_t idx = 0;
    for (const State* s = dfa.head; s; s = s->next) {
        st2idx[s] = idx++;
    }

    fprintf(stderr,
            "digraph DFA {\n"
            "  rankdir=LR\n"
            "  node[shape=Mrecord fontname=fixed]\n"
            "  edge[arrowhead=vee fontname=fixed]\n\n");

    fprintf(stderr,
            "  n [shape=point]"
            "  n -> n%u [style=dotted label=\"\"]\n", st2idx[dfa.head]);

    for (const State* s = dfa.head; s; s = s->next) {
        const char* attr;
        Action::Kind action = s->action.kind;

        if (action == Action::Kind::ACCEPT) {
            attr = "style=filled fillcolor=gray";
        } else if (action == Action::Kind::RULE) {
            attr = "style=filled fillcolor=lightgray";
        } else {
            attr = "";
        }
        fprintf(stderr, "  n%u [height=0.2 width=0.2 label=\"", st2idx[s]);
        if (s->fill && action != Action::Kind::MOVE) {
            fprintf(stderr, "F(%zu) ", s->fill);
        }
        if (action == Action::Kind::RULE) {
            const Rule& r = dfa.rules[s->action.info.rule];
            for (size_t t = r.ltag; t < r.htag; ++t) {
                if (t > r.ltag) fprintf(stderr, " ");
                const char* name = dfa.tags[t].name;
                fprintf(stderr, "%s(%d)", name ? name : "/", dfa.finvers[t]);
            }
        }
        dump_tcmd(dfa.tcpool[s->go.tags]);
        fprintf(stderr, "\" %s]\n", attr);

        if (action == Action::Kind::ACCEPT) {
            for (const AcceptTrans& a: *s->action.info.accepts) {
                fprintf(stderr, "  n%u -> n%u [label=\"", st2idx[s], st2idx[a.state]);
                dump_tcmd(dfa.tcpool[a.tags]);
                fprintf(stderr, "\" style=dotted]\n");
            }
        }

        const Span* x = s->go.span, *e = x + s->go.span_count;
        for (uint32_t lb = 0; x < e; lb = x->ub, ++x) {
            if (!x->to) continue;

            bool eat = true;
            const Action::Kind act = x->to->action.kind;
            if (act == Action::Kind::MOVE || act == Action::Kind::RULE) {
                attr = "style=dotted";
                eat = false;
            } else {
                attr = "";
            }
            fprintf(stderr, "  n%u -> n%u [label=\"", st2idx[s], st2idx[x->to]);
            if (eat) dump_adfa_range(lb, x->ub);
            dump_tcmd(dfa.tcpool[x->tags]);
            fprintf(stderr, "\" %s]\n", attr);
        }
    }

    fprintf(stderr, "}\n");
}

} // namespace re2c

#endif // RE2C_DEBUG
