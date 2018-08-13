#include "src/util/c99_stdint.h"
#include <string>
#include <vector>

#include "src/ast/ast.h"
#include "src/ast/scanner.h"
#include "src/conf/msg.h"
#include "src/re/rule.h"

namespace re2c {

void validate_mode(Scanner::ParseMode mode, bool rflag, bool rules, Scanner &input)
{
    const uint32_t l = input.get_cline();
    if (mode == Scanner::Rules) {
        if (!rflag) {
            fatal_l(l, "found 'rules:re2c' block without -r flag");
        } else if (rules) {
            fatal_l(l, "cannot have a second 'rules:re2c' block");
        }
    } else if (mode == Scanner::Reuse) {
        if (!rflag) {
            fatal_l(l, "found 'use:re2c' block without -r flag");
        } else if (!rules) {
            fatal_l(l, "got 'use:re2c' without 'rules:re2c'");
        }
    } else if (rflag) {
        fatal_l(l, "found standard 're2c' block while using -r flag");
    }
}

void validate_ast(const specs_t &specs, bool cflag)
{
    specs_t::const_iterator i,
        b = specs.begin(),
        e = specs.end();

    for (i = b; i != e; ++i) {
        if (i->defs.size() > 1) {
            fatal_l(i->defs[1]->fline,
                "code to default rule %sis already defined at line %u",
                incond(i->name).c_str(), i->defs[0]->fline);
        }
    }

    if (!cflag) {
        for (i = b; i != e; ++i) {
            if (i->name != "") {
                fatal_l(i->rules[0].code->fline,
                    "conditions are only allowed with '-c', '--conditions' option");
            }
        }
    } else {
        for (i = b; i != e; ++i) {
            if (i->name == "") {
                fatal_l(i->rules[0].code->fline,
                    "non-conditional rules are not allowed"
                    " with '-c', '--conditions' option");
            }
        }

        for (i = b; i != e; ++i) {
            if (i->setup.size() > 1) {
                fatal_l(i->setup[1]->fline,
                    "code to setup rule '%s' is already defined at line %u",
                    i->name.c_str(), i->setup[0]->fline);
            }
        }

        for (i = b; i != e; ++i) {
            if (i->name != "*" && !i->setup.empty() && i->rules.empty()) {
                fatal_l(i->setup[0]->fline,
                    "setup for non existing condition '%s' found",
                    i->name.c_str());
            }
        }

        for (i = b; i != e && !i->setup.empty(); ++i);
        if (i == e) {
            for (i = b; i != e; ++i) {
                if (i->name == "*") {
                    fatal_l(i->setup[0]->fline,
                        "setup for all conditions '<!*>' is illegal "
                        "if setup for each condition is defined explicitly");
                }
            }
        }

        for (i = b; i != e; ++i) {
            if (i->name == "0" && i->rules.size() > 1) {
                fatal_l(i->rules[1].code->fline,
                    "startup code is already defined at line %u",
                    i->rules[0].code->fline);
            }
        }
    }
}

} // namespace re2c
