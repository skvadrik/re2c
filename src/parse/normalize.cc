#include <string>
#include <vector>

#include "src/parse/ast.h"
#include "src/parse/parse.h"
#include "src/regexp/rule.h"


namespace re2c {

void normalize_ast(specs_t &specs)
{
    specs_t::iterator i, j, b, e;

    // merge <*> rules and <!*> setup to all conditions except "0"
    // star rules must have lower priority than normal rules
    for (i = specs.begin(), e = specs.end(); i != e && i->name != "*"; ++i);
    if (i != e) {
        for (j = specs.begin(); j != e; ++j) {
            if (j == i || j->name == "0") continue;

            j->rules.insert(j->rules.end(), i->rules.begin(), i->rules.end());
            j->defs.insert(j->defs.end(), i->defs.begin(), i->defs.end());
            j->eofs.insert(j->eofs.end(), i->eofs.begin(), i->eofs.end());
            j->setup.insert(j->setup.end(), i->setup.begin(), i->setup.end());
        }
        specs.erase(i);
    }

    // merge default rule with the lowest priority
    for (i = specs.begin(), e = specs.end(); i != e; ++i) {
        if (!i->defs.empty()) {
            const Code *c = i->defs[0];
            const AST *r = ast_default(c->loc);
            i->rules.push_back(ASTRule(r, c));
        }
    }

    // "0" condition must be the first one
    for (i = specs.begin(), e = specs.end(); i != e && i->name != "0"; ++i);
    if (i != specs.end() && i != specs.begin()) {
        const spec_t zero = *i;
        specs.erase(i);
        specs.insert(specs.begin(), zero);
    }
}

} // namespace re2c
