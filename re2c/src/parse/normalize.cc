#include <string>
#include <vector>

#include "src/parse/ast.h"
#include "src/regexp/rule.h"

namespace re2c {

void normalize_ast(specs_t &specs)
{
    specs_t::iterator i, b = specs.begin(), e = specs.end();

    // merge <*> rules and <!*> setup to all conditions except "0"
    // star rules must have lower priority than normal rules
    for (i = b; i != e && i->name != "*"; ++i);
    if (i != e) {
        const specs_t::iterator star = i;

        for (i = b; i != e; ++i) {
            if (i == star || i->name == "0") continue;

            i->rules.insert(i->rules.end(), star->rules.begin(), star->rules.end());
            i->defs.insert(i->defs.end(), star->defs.begin(), star->defs.end());
            i->eofs.insert(i->eofs.end(), star->eofs.begin(), star->eofs.end());
            i->setup.insert(i->setup.end(), star->setup.begin(), star->setup.end());
        }

        specs.erase(star);
        e = specs.end();
    }

    // merge default rule with the lowest priority
    for (i = b; i != e; ++i) {
        if (!i->defs.empty()) {
            const Code *c = i->defs[0];
            const AST *r = ast_default(c->fline, 0);
            i->rules.push_back(ASTRule(r, c));
        }
    }

    // "0" condition must be the first one
    for (i = b; i != e && i->name != "0"; ++i);
    if (i != e && i != b) {
        const spec_t zero = *i;
        specs.erase(i);
        specs.insert(specs.begin(), zero);
    }
}

} // namespace re2c
