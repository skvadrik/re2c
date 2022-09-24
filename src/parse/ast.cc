#include <limits>

#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/parse/ast.h"
#include "src/regexp/rule.h"
#include "src/util/check.h"
#include "src/util/string_utils.h"

// note [end-of-input rule]
//
// The end-of-input rule $ is special and different from other rules, because it matches something
// other than input characters: namely, the end of input.
//
// Technically it can be implemented as a check on lexer entry, before matching any characters.
// However, this is not very efficient, as the check would be done unconditionally and it would not
// take advantage of the sentinel symbol that allows to scope the check to only one branch that
// matches the sentinel.
//
// Therefore is is better to match the end-of-input rule in the same way as normal rules, by
// matching the sentinel symbol in the initial state and then performing the end-of-input check. It
// could be implemented as a rule that matches the empty string "", but this approach has a few
// difficulties:
//
//  - The initial state must not be merged with any other states (this may happen in case of a
//    nullable loop), therefore the end-of-input rule must be present as a TNFA state (to prevent
//    determinization from mapping other states to the initial TDFA state), and the initial TDFA
//    state must be final (to prevent minimization from merging it with other states).
//
//  - There might be another rule that matches the empty string. If the end-of-input rule is in the
//    initial state, it should take priority, but otherwise the other empty rule may still match if
//    the longer rules fail and fallback. Technically there can be only one rule per TDFA state, so
//    if the end-of-input rule collides with a normal rule, the normal one wins and the end-of-input
//    rule is removed from a TDFA state (codegen has a special case for the initial state which
//    reinstates the end-of-input rule and gives it priority over normal rules).
//
//  - Unlike other rules, end-of-input rule should not be considered a fallback point in case longer
//    rules fail to match. It is not possible to fallback to it because it can only match at the end
//    of input, and in that case the lexer should not try to match any longer rules (or it will be
//    reading past the end of input).
//
//  - The end-of-input rule should not be considered accepting by undefined control flow analysis in
//    the skeleton, as it may fail to match even if the lexer is in a final TDFA state.
//
//  - The end-of-input rule should not raise -Wmatch-empty-string warning.
//
//  - The end-of-input rule should not be reported as shadowed by other rules.
//

namespace re2c {

AstNode* Ast::make(const loc_t& loc, AstKind kind, bool has_caps) {
    AstNode* p = allocator.alloct<AstNode>(1);
    p->kind = kind;
    p->loc = loc;
    p->has_caps = has_caps;
    return p;
}

const AstNode* Ast::nil(const loc_t& loc) {
    return make(loc, AstKind::NIL, false);
}

const AstNode* Ast::str(const loc_t& loc, bool icase) {
    AstNode* ast = make(loc, AstKind::STR, false);
    ast->str.chars.init(temp_chars.data(), temp_chars.size(), allocator);
    ast->str.icase = icase;
    temp_chars.clear();
    return ast;
}

const AstNode* Ast::cls(const loc_t& loc, bool negated) {
    AstNode* ast = make(loc, AstKind::CLS, false);
    ast->cls.ranges.init(temp_ranges.data(), temp_ranges.size(), allocator);
    ast->cls.negated = negated;
    temp_ranges.clear();
    return ast;
}

const AstNode* Ast::dot(const loc_t& loc) {
    return make(loc, AstKind::DOT, false);
}

const AstNode* Ast::def(const loc_t& loc) {
    return make(loc, AstKind::DEF, false);
}

const AstNode* Ast::alt(const AstNode* a1, const AstNode* a2) {
    if (!a1) return a2;
    if (!a2) return a1;
    AstNode* ast = make(a1->loc, AstKind::ALT, a1->has_caps || a2->has_caps);
    ast->alt.ast1 = a1;
    ast->alt.ast2 = a2;
    return ast;
}

const AstNode* Ast::cat(const AstNode* a1, const AstNode* a2) {
    if (!a1) return a2;
    if (!a2) return a1;
    AstNode* ast = make(a1->loc, AstKind::CAT, a1->has_caps || a2->has_caps);
    ast->cat.ast1 = a1;
    ast->cat.ast2 = a2;
    return ast;
}

const AstNode* Ast::iter(const AstNode* a, uint32_t n, uint32_t m) {
    CHECK(n <= m);
    AstNode* ast = make(a->loc, AstKind::ITER, a->has_caps);
    ast->iter.ast = a;
    ast->iter.min = n;
    ast->iter.max = m;
    return ast;
}

const AstNode* Ast::diff(const AstNode* a1, const AstNode* a2) {
    AstNode* ast = make(a1->loc, AstKind::DIFF, a1->has_caps || a2->has_caps);
    ast->cat.ast1 = a1;
    ast->cat.ast2 = a2;
    return ast;
}

const AstNode* Ast::tag(const loc_t& loc, const char* n, bool h) {
    AstNode* ast = make(loc, AstKind::TAG, false);
    ast->tag.name = n;
    ast->tag.history = h;
    return ast;
}

const AstNode* Ast::cap(const AstNode* a) {
    AstNode* ast = make(a->loc, AstKind::CAP, true);
    ast->cap = a;
    return ast;
}

const AstNode* Ast::ref(const AstNode* a, const char* n) {
    AstNode* ast = make(a->loc, AstKind::REF, a->has_caps);
    ast->ref.ast = a;
    ast->ref.name = n;
    return ast;
}

const SemAct* Ast::sem_act(const loc_t& loc, const char* text, const char* cond, bool autogen) {
    SemAct* a = allocator.alloct<SemAct>(1);
    a->loc = loc;
    a->text = text;
    a->cond = cond;
    a->autogen = autogen;
    return a;
}

const char* Ast::cstr(const uint8_t* s, const uint8_t* e) {
    return newcstr(s, e, allocator);
}

bool Ast::needs_wrap(const AstNode* a) {
    switch (a->kind) {
    case AstKind::ITER:
    case AstKind::NIL:
    case AstKind::STR:
    case AstKind::CLS:
    case AstKind::DOT:
    case AstKind::DEF:
    case AstKind::TAG:
    case AstKind::CAP:
        return false;
    case AstKind::ALT:
    case AstKind::CAT:
    case AstKind::DIFF:
    case AstKind::REF:
        return true;
    }
    return false; // unreachable
}

spec_t::spec_t(const std::string& name)
    : name(name),
      rules(),
      defs(),
      eofs(),
      setup(),
      inherited_defs(),
      inherited_eofs(),
      inherited_setup(),
      def_rule(Rule::NONE),
      eof_rule(Rule::NONE) {}

RulesBlock::RulesBlock(const std::string& name, const opt_t* opts, const specs_t& specs)
    : name(name), opts(opts), specs(specs) {}

RulesBlocks::RulesBlocks(): blocks() {}

RulesBlocks::~RulesBlocks() {
    for (RulesBlock* b : blocks) {
        delete b;
    }
}

bool RulesBlocks::empty() const {
    return blocks.empty();
}

void RulesBlocks::add(const std::string& name, const opt_t* opts, const specs_t& specs) {
    blocks.push_back(new RulesBlock(name, opts, specs));
}

const RulesBlock* RulesBlocks::find(const std::string& name) const {
    if (name.empty()) {
        if (!blocks.empty()) {
            return blocks.back();
        }
        error("cannot find `/*!rules:re2c ... */` block");
    } else {
        for (const RulesBlock* b : blocks) {
            if (b->name == name) return b;
        }
        error("cannot find `/*!rules:re2c:%s ... */` block", name.c_str());
    }
    return nullptr;
}

const opt_t* RulesBlocks::last_opts() const {
    return blocks.empty() ? nullptr : blocks.back()->opts;
}

spec_t& find_or_add_spec(specs_t& specs, const std::string& name) {
    for (spec_t& spec : specs) {
        if (spec.name == name) return spec;
    }
    specs.push_back(spec_t(name));
    return specs.back();
}

template<typename T>
static inline void append(std::vector<T>& x, const std::vector<T>& y) {
    x.insert(x.end(), y.begin(), y.end());
}

Ret use_block(Scanner& input, const Ast& ast, Opt& opts, specs_t& specs, const std::string& name) {
    const RulesBlock* rb = ast.rblocks.find(name);
    if (rb == nullptr) return Ret::FAIL;

    for (const spec_t& s : rb->specs) {
        spec_t& spec = find_or_add_spec(specs, s.name);

        // Merge rules. Inherited special rules *, $ and <!> are kept separate from those defined in
        // the current block, because they are handled differently: they have lower priority and it
        // is allowed to override them with local rules (while within one block redefinition of a
        // special rule is an error).
        append(spec.rules, s.rules);
        append(spec.inherited_defs, s.defs);
        append(spec.inherited_eofs, s.eofs);
        append(spec.inherited_setup, s.setup);
    }

    // Merge configurations and symtab.
    return opts.merge(rb->opts, input);
}

Ret check_and_merge_special_rules(specs_t& specs, const opt_t* opts, Msg& msg, Ast& ast) {
    if (specs.empty()) return Ret::OK;

    for (const spec_t& s : specs) {
        if (s.defs.size() > 1) {
            RET_FAIL(msg.error(s.defs[1]->loc,
                               "code to default rule %sis already defined at line %u",
                               incond(s.name).c_str(), s.defs[0]->loc.line));
        } else if (s.eofs.size() > 1) {
            RET_FAIL(msg.error(s.eofs[1]->loc,
                               "EOF rule %sis already defined at line %u",
                               incond(s.name).c_str(), s.eofs[0]->loc.line));
        } else if (s.rules.empty() && s.defs.empty() && !s.eofs.empty()) {
            RET_FAIL(msg.error(s.eofs[0]->loc,
                               "EOF rule %swithout other rules doesn't make sense",
                               incond(s.name).c_str()));
        }
    }

    if (!opts->start_conditions) {
        // normal mode: there must be no named specs corresponding to conditions
        for (const spec_t& s : specs) {
            if (!s.name.empty()) { // found named spec
                const loc_t& loc = !s.rules.empty() ? s.rules[0].semact->loc
                        : !s.defs.empty() ? s.defs[0]->loc : NOWHERE;
                RET_FAIL(msg.error(loc,
                                   "conditions are only allowed with '-c', '--conditions' option"));
            }
        }
    } else if (specs.size() == 1 && specs[0].name.empty()) {
        // condition mode, a single unnamed spec => ok, normal blocks are allowed
    } else {
        // condition mode, at least one named spec => this is a block with conditions

        for (const spec_t& s : specs) {
            if (s.name.empty()) { // found unnamed spec
                const loc_t& l = !s.rules.empty() ? s.rules[0].semact->loc
                        : !s.defs.empty() ? s.defs[0]->loc : NOWHERE;
                RET_FAIL(msg.error(l, "cannot mix conditions with normal rules"));
            }
        }

        for (const spec_t& s : specs) {
            if (s.setup.size() > 1) {
                RET_FAIL(msg.error(s.setup[1]->loc,
                                   "code to setup rule '%s' is already defined at line %u",
                                   s.name.c_str(), s.setup[0]->loc.line));
            }
        }

        for (const spec_t& s : specs) {
            if (s.name != "*" && !s.setup.empty() && s.rules.empty()) {
                RET_FAIL(msg.error(s.setup[0]->loc,
                                   "setup for non existing condition '%s' found", s.name.c_str()));
            }
        }

        auto no_setup = std::find_if(
                specs.begin(), specs.end(), [](const spec_t& s) { return s.setup.empty(); });
        if (no_setup == specs.end()) { // all specs have setup
            for (const spec_t& s : specs) {
                if (s.name == "*") {
                    RET_FAIL(msg.error(s.setup[0]->loc,
                                       "setup for all conditions '<!*>' is illegal if setup for "
                                       "each condition is defined explicitly"));
                }
            }
        }

        for (const spec_t& s : specs) {
            if (s.name == "0" && s.rules.size() > 1) {
                RET_FAIL(msg.error(s.rules[1].semact->loc,
                                   "startup code is already defined at line %u",
                                   s.rules[0].semact->loc.line));
            }
        }
    }

    // Inherit special rules from other blocks (unless a local one is defined).
    for (spec_t& s : specs) {
        append(s.defs, s.inherited_defs);
        append(s.eofs, s.inherited_eofs);
        append(s.setup, s.inherited_setup);
    }

    // Merge <*> rules and <!*> setup to all conditions except "0". Star rules must have lower
    // priority than normal rules.
    auto star = std::find_if(
            specs.begin(), specs.end(), [](const spec_t& s) { return s.name == "*"; });
    if (star != specs.end()) {
        for (spec_t& s : specs) {
            if (s.name != "*" && s.name != "0") {
                append(s.rules, star->rules);
                append(s.defs, star->defs);
                append(s.eofs, star->eofs);
                append(s.setup, star->setup);
            }
        }
        specs.erase(star);
    }

    // Merge end of input rule $ and default rule * with the lowest priority.
    for (spec_t& s : specs) {
        // See note [EOF rule handling].
        if (!s.eofs.empty()) {
            s.eof_rule = s.rules.size();
            const SemAct* a = s.eofs[0];
            s.rules.push_back(AstRule(ast.nil(a->loc), a));
        }
        if (!s.defs.empty()) {
            s.def_rule = s.rules.size();
            const SemAct* a = s.defs[0];
            s.rules.push_back(AstRule(ast.def(a->loc), a));
        }
    }

    // "0" condition must be the first one.
    auto zero = std::find_if(
            specs.begin(), specs.end(), [](const spec_t& s) { return s.name == "0"; });
    if (zero != specs.end() && zero != specs.begin()) {
        spec_t zero_copy(*zero);
        specs.erase(zero);
        specs.insert(specs.begin(), zero_copy);
    }

    // Check that 're2c:eof' configuration and the $ rule are used together. This must be done after
    // merging rules inherited from other blocks and <*> condition (because they might add $ rule).
    for (const spec_t& s : specs) {
        if (!s.eofs.empty() && opts->fill_eof == NOEOF) {
            RET_FAIL(msg.error(s.eofs[0]->loc,
                               "%s$ rule found, but 're2c:eof' configuration is not set",
                               incond(s.name).c_str()));
        } else if (s.eofs.empty() && opts->fill_eof != NOEOF) {
            RET_FAIL(error("%s're2c:eof' configuration is set, but no $ rule found",
                           incond(s.name).c_str()));
        }
    }

    return Ret::OK;
}

// C++11 requres outer decl for ODR-used static constexpr data members (not needed in C++17).
constexpr uint32_t Ast::MANY;

} // namespace re2c
