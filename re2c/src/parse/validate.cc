#include "src/util/c99_stdint.h"
#include <string>
#include <vector>

#include "src/parse/ast.h"
#include "src/parse/scanner.h"
#include "src/options/msg.h"
#include "src/regexp/rule.h"

namespace re2c {

void validate_mode(Scanner::ParseMode mode, bool rflag, bool rules, Scanner &input)
{
    const std::string &f = input.get_fname();
    const uint32_t l = input.get_line();
    if (mode == Scanner::Rules) {
        if (!rflag) {
            fatal_l(f, l, "found 'rules:re2c' block without -r flag");
        } else if (rules) {
            fatal_l(f, l, "cannot have a second 'rules:re2c' block");
        }
    } else if (mode == Scanner::Reuse) {
        if (!rflag) {
            fatal_l(f, l, "found 'use:re2c' block without -r flag");
        } else if (!rules) {
            fatal_l(f, l, "got 'use:re2c' without 'rules:re2c'");
        }
    } else if (rflag) {
        fatal_l(f, l, "found standard 're2c' block while using -r flag");
    }
}

void validate_ast(const std::string &fname, const specs_t &specs
    , const opt_t *opts)
{
    static const uint32_t NONE = ~0u;
    specs_t::const_iterator i, b = specs.begin(), e = specs.end();
    if (b == e) return;

    for (i = b; i != e; ++i) {
        if (i->defs.size() > 1) {
            fatal_l(fname, i->defs[1]->fline,
                "code to default rule %sis already defined at line %u",
                incond(i->name).c_str(), i->defs[0]->fline);
        }
        if (!i->eofs.empty() && opts->eof == NOEOF) {
            fatal_l(fname, i->eofs[0]->fline,
                "%sEOF rule found, but 're2c:eof' configuration is not set",
                incond(i->name).c_str());
        }
        else if (i->eofs.empty() && opts->eof != NOEOF && !opts->fFlag) {
            fatal("%s're2c:eof' configuration is set, but no EOF rule found",
                incond(i->name).c_str());
        }
        else if (!i->eofs.empty() && opts->fFlag) {
            fatal_l(fname, i->eofs[0]->fline,
                "%sEOF rule is unreachable in push-model lexers",
                incond(i->name).c_str());
        }
        else if (i->eofs.size() > 1) {
            fatal_l(fname, i->eofs[1]->fline,
                "EOF rule %sis already defined at line %u",
                incond(i->name).c_str(), i->eofs[0]->fline);
        }
    }

    if (!opts->cFlag) {
        for (i = b; i != e; ++i) {
            if (i->name != "") {
                const uint32_t l = !i->rules.empty()
                    ? i->rules[0].code->fline : !i->defs.empty()
                        ? i->defs[0]->fline : NONE;
                if (l != NONE) {
                    fatal_l(fname, l, "conditions are only allowed with '-c', "
                        "'--conditions' option");
                }

            }
        }
    } else {
        for (i = b; i != e; ++i) {
            if (i->name == "") {
                const uint32_t l = !i->rules.empty()
                    ? i->rules[0].code->fline : !i->defs.empty()
                        ? i->defs[0]->fline : NONE;
                if (l != NONE) {
                    fatal_l(fname, l, "non-conditional rules are not allowed with "
                        "'-c', '--conditions' option");
                }
            }
        }

        for (i = b; i != e; ++i) {
            if (i->setup.size() > 1) {
                fatal_l(fname, i->setup[1]->fline,
                    "code to setup rule '%s' is already defined at line %u",
                    i->name.c_str(), i->setup[0]->fline);
            }
        }

        for (i = b; i != e; ++i) {
            if (i->name != "*" && !i->setup.empty() && i->rules.empty()) {
                fatal_l(fname, i->setup[0]->fline,
                    "setup for non existing condition '%s' found",
                    i->name.c_str());
            }
        }

        for (i = b; i != e && !i->setup.empty(); ++i);
        if (i == e) {
            for (i = b; i != e; ++i) {
                if (i->name == "*") {
                    fatal_l(fname, i->setup[0]->fline,
                        "setup for all conditions '<!*>' is illegal "
                        "if setup for each condition is defined explicitly");
                }
            }
        }

        for (i = b; i != e; ++i) {
            if (i->name == "0" && i->rules.size() > 1) {
                fatal_l(fname, i->rules[1].code->fline,
                    "startup code is already defined at line %u",
                    i->rules[0].code->fline);
            }
        }
    }
}

} // namespace re2c
