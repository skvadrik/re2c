#include <string>
#include <vector>

#include "src/parse/ast.h"
#include "src/parse/parse.h"
#include "src/regexp/rule.h"


namespace re2c {

/* note [EOF rule handling]
 *
 * EOF rule is special and different from other rules, because it matches
 * something other than input characters: namely, the end of input.
 *
 * Technically it can be implemented as a check on lexer entry, before matching
 * any characters. However, this is not very efficient, as the check would be
 * done unconditionally and it would not take advantage of the sentinel symbol
 * that allows to scope the check to only one branch that matches the sentinel.
 *
 * Therefore is is better to match EOF rule in the same way as normal rules, by
 * matching the sentinel symbol in the initial state and then performing the
 * end-of-input check. It can be done by implementing EOF rule as a rule that
 * matches empty string "", but this approach has a few difficulties:
 *
 *  - The initial state must not be merged with any other states (this may
 *    happen in case of a nullable loop), therefore EOF rule must be present as
 *    an NFA state (to prevent determinization from mapping other states to the
 *    initial DFA state), and the initial DFA state must be marked as accepting
 *    (to prevent minimization from merging it with other states).
 *
 *  - There might be another rule that matches empty string. In the case of EOF
 *    in the initial state EOF rule should take priority, but otherwise the
 *    other empty rule may still match if all longer rules fail and fallback.
 *    Technically there can be only one rule per DFA state, so if EOF rule
 *    collides with a normal rule, the normal rule wins and EOF rule is removed
 *    from the DFA state, but the code generation subsystem has a special case
 *    for the initial state which reinstates EOF rule and gives it priority over
 *    the normal rule.
 *
 *  - Unlike other rules, EOF rule should not be considered a fallback point in
 *    case longer rules fail to match. It is not possible to fallback to it
 *    because it can only match on EOF, and in that case lexer should not try to
 *    match any longer rules (or it will be reading past the end of input).
 *
 *  - EOF rule should not be considered accepting by undefined control flow
 *    analysis in the skeleton, as it may fail to match even if the lexer is in
 *    accepting DFA state.
 *
 *  - EOF rule should not raise -Wmatch-empty-string warning.
 *
 *  - EOF rule should not be reported as shadowed by other rules.
 */

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

    // merge EOF rule and default rule with the lowest priority
    for (i = specs.begin(), e = specs.end(); i != e; ++i) {
        // See note [EOF rule handling].
        if (!i->eofs.empty()) {
            i->eof_rule = i->rules.size();
            const SemAct *a = i->eofs[0];
            i->rules.push_back(ASTRule(ast_nil(a->loc), a));
        }
        if (!i->defs.empty()) {
            i->def_rule = i->rules.size();
            const SemAct *a = i->defs[0];
            i->rules.push_back(ASTRule(ast_default(a->loc), a));
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
