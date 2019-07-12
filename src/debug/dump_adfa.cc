#ifdef RE2C_DEBUG

#include "src/util/c99_stdint.h"
#include <map>
#include <stdio.h>
#include <string>
#include <utility>
#include <valarray>
#include <vector>

#include "src/adfa/action.h"
#include "src/adfa/adfa.h"
#include "src/codegen/go.h"
#include "src/debug/debug.h"
#include "src/dfa/tcmd.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"


namespace re2c {

static void dump_adfa_range(uint32_t lower, uint32_t upper)
{
    fprintf(stderr, "%u", lower);
    if (--upper > lower) {
        fprintf(stderr, "-%u", upper);
    }
}

void dump_adfa(const DFA &dfa)
{
    std::map<const State*, uint32_t> st2idx;
    uint32_t idx = 0;
    for (const State *s = dfa.head; s; s = s->next) {
        st2idx[s] = idx++;
    }

    fprintf(stderr,
        "digraph DFA {\n"
        "  rankdir=LR\n"
        "  node[shape=Mrecord fontname=fixed]\n"
        "  edge[arrowhead=vee fontname=fixed]\n\n");

    fprintf(stderr,
        "  n [shape=point]"
        "  n -> n%u [style=dotted label=\"", st2idx[dfa.head]);
    dump_tcmd(dfa.tcpool[dfa.tags0]);
    fprintf(stderr, "\"]\n");

    for (const State *s = dfa.head; s; s = s->next) {
        const char *attr;
        Action::type_t action = s->action.type;

        if (action == Action::ACCEPT) {
            attr = "style=filled fillcolor=gray";
        } else if (action == Action::RULE) {
            attr = "style=filled fillcolor=lightgray";
        } else {
            attr = "";
        }
        fprintf(stderr, "  n%u [height=0.2 width=0.2 label=\"", st2idx[s]);
        if (s->fill && action != Action::MOVE) {
            fprintf(stderr, "F(%u) ", (uint32_t)s->fill);
        }
        if (action == Action::RULE) {
            const Rule &r = dfa.rules[s->action.info.rule];
            for (size_t t = r.ltag; t < r.htag; ++t) {
                if (t > r.ltag) fprintf(stderr, " ");
                const std::string *name = dfa.tags[t].name;
                fprintf(stderr, "%s(%d)",
                    name ? name->c_str() : "/", dfa.finvers[t]);
            }
        }
        dump_tcmd(dfa.tcpool[s->go.tags]);
        fprintf(stderr, "\" %s]\n", attr);

        if (action == Action::ACCEPT) {
            const accept_t &accept = *s->action.info.accepts;
            for (uint32_t i = 0; i < accept.size(); ++i) {
                fprintf(stderr, "  n%u -> n%u [label=\"", st2idx[s],
                    st2idx[accept[i].first]);
                dump_tcmd(dfa.tcpool[accept[i].second]);
                fprintf(stderr, "\" style=dotted]\n");
            }
        }

        const Span *x = s->go.span, *e = x + s->go.nSpans;
        for (uint32_t lb = 0; x < e; lb = x->ub, ++x) {
            if (!x->to) continue;

            bool eat = true;
            const Action::type_t act = x->to->action.type;
            if (act == Action::MOVE || act == Action::RULE) {
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
