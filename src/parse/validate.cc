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

void validate_mode(Scanner::ParseMode mode, bool rflag, bool rules
    , Scanner &input)
{
    Msg &msg = input.msg;
    const loc_t &l = input.tok_loc();
    if (mode == Scanner::Rules) {
        if (!rflag) {
            msg.fatal(l, "found 'rules:re2c' block without -r flag");
        }
    }
    else if (mode == Scanner::Reuse) {
        if (!rflag) {
            msg.fatal(l, "found 'use:re2c' block without -r flag");
        }
        else if (!rules) {
            msg.fatal(l, "got 'use:re2c' without 'rules:re2c'");
        }
    }
}

void validate_ast(const specs_t &specs, const opt_t *opts, Msg &msg)
{
    specs_t::const_iterator i, b = specs.begin(), e = specs.end();
    if (b == e) return;

    for (i = b; i != e; ++i) {
        if (i->defs.size() > 1) {
            msg.fatal(i->defs[1]->loc,
                "code to default rule %sis already defined at line %u",
                incond(i->name).c_str(), i->defs[0]->loc.line);
        }
        if (!i->eofs.empty() && opts->eof == NOEOF) {
            msg.fatal(i->eofs[0]->loc,
                "%sEOF rule found, but 're2c:eof' configuration is not set",
                incond(i->name).c_str());
        }
        else if (i->eofs.empty() && opts->eof != NOEOF) {
            fatal("%s're2c:eof' configuration is set, but no EOF rule found",
                incond(i->name).c_str());
        }
        else if (i->eofs.size() > 1) {
            msg.fatal(i->eofs[1]->loc,
                "EOF rule %sis already defined at line %u",
                incond(i->name).c_str(), i->eofs[0]->loc.line);
        }
        else if (i->rules.empty() && i->defs.empty() && !i->eofs.empty()) {
            msg.fatal(i->eofs[0]->loc,
                "EOF rule %swithout other rules doesn't make sense",
                incond(i->name).c_str());
        }
    }

    if (!opts->cFlag) {
        for (i = b; i != e; ++i) {
            if (!i->name.empty()) {
                const loc_t &l = !i->rules.empty()
                    ? i->rules[0].code->loc : !i->defs.empty()
                        ? i->defs[0]->loc : NOWHERE;
                if (l.line != NOWHERE.line) {
                    msg.fatal(l, "conditions are only allowed with "
                        "'-c', '--conditions' option");
                }
            }
        }
    }
    else {
        for (i = b; i != e; ++i) {
            if (i->name.empty()) {
                const loc_t &l = !i->rules.empty()
                    ? i->rules[0].code->loc : !i->defs.empty()
                        ? i->defs[0]->loc : NOWHERE;
                if (l.line != NOWHERE.line) {
                    msg.fatal(l, "non-conditional rules are not allowed with "
                        "'-c', '--conditions' option");
                }
            }
        }

        for (i = b; i != e; ++i) {
            if (i->setup.size() > 1) {
                msg.fatal(i->setup[1]->loc,
                    "code to setup rule '%s' is already defined at line %u",
                    i->name.c_str(), i->setup[0]->loc.line);
            }
        }

        for (i = b; i != e; ++i) {
            if (i->name != "*" && !i->setup.empty() && i->rules.empty()) {
                msg.fatal(i->setup[0]->loc,
                    "setup for non existing condition '%s' found",
                    i->name.c_str());
            }
        }

        for (i = b; i != e && !i->setup.empty(); ++i);
        if (i == e) {
            for (i = b; i != e; ++i) {
                if (i->name == "*") {
                    msg.fatal(i->setup[0]->loc,
                        "setup for all conditions '<!*>' is illegal "
                        "if setup for each condition is defined explicitly");
                }
            }
        }

        for (i = b; i != e; ++i) {
            if (i->name == "0" && i->rules.size() > 1) {
                msg.fatal(i->rules[1].code->loc,
                    "startup code is already defined at line %u",
                    i->rules[0].code->loc.line);
            }
        }
    }
}

} // namespace re2c
