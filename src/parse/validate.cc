#include "src/util/c99_stdint.h"
#include <memory>
#include <string>
#include <vector>

#include "src/msg/location.h"
#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/parse/ast.h"
#include "src/parse/parse.h"
#include "src/parse/scanner.h"
#include "src/regexp/rule.h"


namespace re2c {

void validate_ast(const specs_t &specs, const opt_t *opts, Msg &msg)
{
    specs_t::const_iterator i, b = specs.begin(), e = specs.end();
    if (b == e) return;

    for (i = b; i != e; ++i) {
        if (i->defs.size() > 1) {
            msg.error(i->defs[1]->loc,
                "code to default rule %sis already defined at line %u",
                incond(i->name).c_str(), i->defs[0]->loc.line);
            exit(1);
        }
        if (!i->eofs.empty() && opts->eof == NOEOF) {
            msg.error(i->eofs[0]->loc,
                "%sEOF rule found, but 're2c:eof' configuration is not set",
                incond(i->name).c_str());
            exit(1);
        }
        else if (i->eofs.empty() && opts->eof != NOEOF) {
            error("%s're2c:eof' configuration is set, but no EOF rule found",
                incond(i->name).c_str());
            exit(1);
        }
        else if (i->eofs.size() > 1) {
            msg.error(i->eofs[1]->loc,
                "EOF rule %sis already defined at line %u",
                incond(i->name).c_str(), i->eofs[0]->loc.line);
            exit(1);
        }
        else if (i->rules.empty() && i->defs.empty() && !i->eofs.empty()) {
            msg.error(i->eofs[0]->loc,
                "EOF rule %swithout other rules doesn't make sense",
                incond(i->name).c_str());
            exit(1);
        }
    }

    if (!opts->cFlag) {
        // normal mode: there must be no named specs corresponding to conditions
        for (i = b; i != e && i->name.empty(); ++i);
        if (i != e) { // found named spec
            const loc_t &l = !i->rules.empty() ? i->rules[0].semact->loc
                : !i->defs.empty() ? i->defs[0]->loc : NOWHERE;
            msg.error(l, "conditions are only allowed with '-c', '--conditions' option");
            exit(1);
        }
    } else if (e - b == 1 && b->name.empty()) {
        // condition mode, a single unnamed spec => ok, normal blocks are allowed
    } else {
        // condition mode, at least one named spec => this is a block with conditions

        for (i = b; i != e && !i->name.empty(); ++i);
        if (i != e) { // found unnamed spec
            const loc_t &l = !i->rules.empty() ? i->rules[0].semact->loc
                : !i->defs.empty() ? i->defs[0]->loc : NOWHERE;
            msg.error(l, "cannot mix conditions with normal rules");
            exit(1);
        }

        for (i = b; i != e; ++i) {
            if (i->setup.size() > 1) {
                msg.error(i->setup[1]->loc,
                    "code to setup rule '%s' is already defined at line %u",
                    i->name.c_str(), i->setup[0]->loc.line);
                exit(1);
            }
        }

        for (i = b; i != e; ++i) {
            if (i->name != "*" && !i->setup.empty() && i->rules.empty()) {
                msg.error(i->setup[0]->loc,
                    "setup for non existing condition '%s' found",
                    i->name.c_str());
                exit(1);
            }
        }

        for (i = b; i != e && !i->setup.empty(); ++i);
        if (i == e) {
            for (i = b; i != e; ++i) {
                if (i->name == "*") {
                    msg.error(i->setup[0]->loc,
                        "setup for all conditions '<!*>' is illegal "
                        "if setup for each condition is defined explicitly");
                    exit(1);
                }
            }
        }

        for (i = b; i != e; ++i) {
            if (i->name == "0" && i->rules.size() > 1) {
                msg.error(i->rules[1].semact->loc,
                    "startup code is already defined at line %u",
                    i->rules[0].semact->loc.line);
                exit(1);
            }
        }
    }
}

} // namespace re2c
