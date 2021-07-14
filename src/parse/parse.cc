#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/parse/parse.h"


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

namespace re2c {

RulesBlock::RulesBlock(const std::string &name, const opt_t *opts,
    const specs_t &specs): name(name), opts(opts), specs(specs) {}

RulesBlocks::RulesBlocks(): blocks() {}

RulesBlocks::~RulesBlocks()
{
    for (size_t i = 0; i < blocks.size(); ++i) {
        delete blocks[i];
    }
}

bool RulesBlocks::empty() const { return blocks.empty(); }

void RulesBlocks::add(const std::string &name, const opt_t *opts,
    const specs_t &specs)
{
    blocks.push_back(new RulesBlock(name, opts, specs));
}

const RulesBlock *RulesBlocks::find(const std::string &name) const
{
    if (name.empty()) {
        if (!blocks.empty()) {
            return blocks.back();
        }
        error("cannot find `/*!rules:re2c ... */` block");
    } else {
        for (size_t i = 0; i < blocks.size(); ++i) {
            const RulesBlock *b = blocks[i];
            if (b->name == name) {
                return b;
            }
        }
        error("cannot find `/*!rules:re2c:%s ... */` block", name.c_str());
    }
    return NULL;
}

const opt_t *RulesBlocks::last_opts() const
{
    return blocks.empty() ? NULL : blocks.back()->opts;
}

spec_t &find_or_add_spec(specs_t &specs, const std::string &name)
{
    for (specs_t::iterator i = specs.begin(); i != specs.end(); ++i) {
        if (i->name == name) return *i;
    }
    specs.push_back(spec_t(name));
    return specs.back();
}

template<typename T>
static inline void append(std::vector<T> &x, const std::vector<T> &y)
{
    x.insert(x.end(), y.begin(), y.end());
}

void use_block(context_t &context, const std::string &name, const loc_t &loc, Msg &msg)
{
    const RulesBlock *rb = context.rblocks.find(name);
    if (rb == NULL) exit(1);

    for (specs_t::const_iterator i = rb->specs.begin(); i != rb->specs.end(); ++i) {
        spec_t &spec = find_or_add_spec(context.specs, i->name);

        // Merge rules. Inherited special rules *, $ and <!> are kept separate
        // from those defined in the current block, because they are handled
        // differently: they have lower priority and it is allowed to override
        // them with local rules (while within one block redefinition of a
        // special rule is an error).
        append(spec.rules, i->rules);
        append(spec.inherited_defs, i->defs);
        append(spec.inherited_eofs, i->eofs);
        append(spec.inherited_setup, i->setup);
    }

    // Merge configurations and symtab.
    context.opts.merge(rb->opts, loc, msg);
}

void check_and_merge_special_rules(specs_t &specs, const opt_t *opts, Msg &msg)
{
    if (specs.empty()) return;
    specs_t::iterator i, j, e;

    for (i = specs.begin(), e = specs.end(); i != e; ++i) {
        if (i->defs.size() > 1) {
            msg.error(i->defs[1]->loc,
                "code to default rule %sis already defined at line %u",
                incond(i->name).c_str(), i->defs[0]->loc.line);
            exit(1);
        }
        if (i->eofs.size() > 1) {
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
        for (i = specs.begin(), e = specs.end(); i != e && i->name.empty(); ++i);
        if (i != e) { // found named spec
            const loc_t &l = !i->rules.empty() ? i->rules[0].semact->loc
                : !i->defs.empty() ? i->defs[0]->loc : NOWHERE;
            msg.error(l, "conditions are only allowed with '-c', '--conditions' option");
            exit(1);
        }
    } else if (specs.size() == 1 && specs[0].name.empty()) {
        // condition mode, a single unnamed spec => ok, normal blocks are allowed
    } else {
        // condition mode, at least one named spec => this is a block with conditions

        for (i = specs.begin(), e = specs.end(); i != e && !i->name.empty(); ++i);
        if (i != e) { // found unnamed spec
            const loc_t &l = !i->rules.empty() ? i->rules[0].semact->loc
                : !i->defs.empty() ? i->defs[0]->loc : NOWHERE;
            msg.error(l, "cannot mix conditions with normal rules");
            exit(1);
        }

        for (i = specs.begin(), e = specs.end(); i != e; ++i) {
            if (i->setup.size() > 1) {
                msg.error(i->setup[1]->loc,
                    "code to setup rule '%s' is already defined at line %u",
                    i->name.c_str(), i->setup[0]->loc.line);
                exit(1);
            }
        }

        for (i = specs.begin(), e = specs.end(); i != e; ++i) {
            if (i->name != "*" && !i->setup.empty() && i->rules.empty()) {
                msg.error(i->setup[0]->loc,
                    "setup for non existing condition '%s' found",
                    i->name.c_str());
                exit(1);
            }
        }

        for (i = specs.begin(), e = specs.end(); i != e && !i->setup.empty(); ++i);
        if (i == e) {
            for (i = specs.begin(), e = specs.end(); i != e; ++i) {
                if (i->name == "*") {
                    msg.error(i->setup[0]->loc,
                        "setup for all conditions '<!*>' is illegal "
                        "if setup for each condition is defined explicitly");
                    exit(1);
                }
            }
        }

        for (i = specs.begin(), e = specs.end(); i != e; ++i) {
            if (i->name == "0" && i->rules.size() > 1) {
                msg.error(i->rules[1].semact->loc,
                    "startup code is already defined at line %u",
                    i->rules[0].semact->loc.line);
                exit(1);
            }
        }
    }

    // Inherit special rules from other blocks (unless a local one is defined).
    for (i = specs.begin(), e = specs.end(); i != e; ++i) {
        append(i->defs, i->inherited_defs);
        append(i->eofs, i->inherited_eofs);
        append(i->setup, i->inherited_setup);
    }

    // Merge <*> rules and <!*> setup to all conditions except "0". Star rules
    // must have lower priority than normal rules
    for (i = specs.begin(), e = specs.end(); i != e && i->name != "*"; ++i);
    if (i != e) {
        for (j = specs.begin(); j != e; ++j) {
            if (j == i || j->name == "0") continue;

            append(j->rules, i->rules);
            append(j->defs, i->defs);
            append(j->eofs, i->eofs);
            append(j->setup, i->setup);
        }
        specs.erase(i);
    }

    // Merge end of input rule $ and default rule * with the lowest priority.
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

    // "0" condition must be the first one.
    for (i = specs.begin(), e = specs.end(); i != e && i->name != "0"; ++i);
    if (i != specs.end() && i != specs.begin()) {
        const spec_t zero = *i;
        specs.erase(i);
        specs.insert(specs.begin(), zero);
    }

    // Check that 're2c:eof' configuration and the $ rule are used together.
    // This must be done after merging rules inherited from other blocks and <*>
    // condition (because they might add $ rule).
    for (i = specs.begin(), e = specs.end(); i != e; ++i) {
        if (!i->eofs.empty() && opts->eof == NOEOF) {
            msg.error(i->eofs[0]->loc,
                "%s$ rule found, but 're2c:eof' configuration is not set",
                incond(i->name).c_str());
            exit(1);
        } else if (i->eofs.empty() && opts->eof != NOEOF) {
            error("%s're2c:eof' configuration is set, but no $ rule found",
                incond(i->name).c_str());
            exit(1);
        }
    }
}

} // namespace re2c
