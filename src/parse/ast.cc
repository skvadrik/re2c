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

Ast::Ast(AstAllocator& ast_alc, OutAllocator& out_alc)
    : ast_alc(ast_alc),
      out_alc(out_alc),
      temp_chars(),
      temp_ranges(),
      temp_condlist(),
      temp_blockname(),
      blocks() {}

AstNode* Ast::make(const loc_t& loc, AstKind kind, uint8_t has_caps) {
    AstNode* p = ast_alc.alloct<AstNode>(1);
    p->kind = kind;
    p->loc = loc;
    p->has_caps = has_caps;
    return p;
}

const AstNode* Ast::nil(const loc_t& loc) {
    return make(loc, AstKind::NIL, NO_CAPTURE);
}

const AstNode* Ast::str(const loc_t& loc, bool icase) {
    AstNode* ast = make(loc, AstKind::STR, NO_CAPTURE);
    ast->str.chars.init(temp_chars.data(), temp_chars.size(), ast_alc);
    ast->str.icase = icase;
    temp_chars.clear();
    return ast;
}

const AstNode* Ast::cls(const loc_t& loc, bool negated) {
    AstNode* ast = make(loc, AstKind::CLS, NO_CAPTURE);
    ast->cls.ranges.init(temp_ranges.data(), temp_ranges.size(), ast_alc);
    ast->cls.negated = negated;
    temp_ranges.clear();
    return ast;
}

const AstNode* Ast::dot(const loc_t& loc) {
    return make(loc, AstKind::DOT, NO_CAPTURE);
}

const AstNode* Ast::def(const loc_t& loc) {
    return make(loc, AstKind::DEF, NO_CAPTURE);
}

const AstNode* Ast::alt(const AstNode* a1, const AstNode* a2) {
    if (!a1) return a2;
    if (!a2) return a1;
    AstNode* ast = make(a1->loc, AstKind::ALT, a1->has_caps | a2->has_caps);
    ast->alt.ast1 = a1;
    ast->alt.ast2 = a2;
    return ast;
}

const AstNode* Ast::cat(const AstNode* a1, const AstNode* a2) {
    if (!a1) return a2;
    if (!a2) return a1;
    AstNode* ast = make(a1->loc, AstKind::CAT, a1->has_caps | a2->has_caps);
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
    AstNode* ast = make(a1->loc, AstKind::DIFF, a1->has_caps | a2->has_caps);
    ast->cat.ast1 = a1;
    ast->cat.ast2 = a2;
    return ast;
}

const AstNode* Ast::tag(const loc_t& loc, const char* n, bool h) {
    AstNode* ast = make(loc, AstKind::TAG, NO_CAPTURE);
    ast->tag.name = n;
    ast->tag.history = h;
    return ast;
}

const AstNode* Ast::cap(const AstNode* a, CaptureMode mode) {
    AstNode* ast = make(a->loc, AstKind::CAP, mode | a->has_caps);
    ast->cap.ast = a;
    ast->cap.mode = mode;
    return ast;
}

const SemAct* Ast::sem_act(const loc_t& loc, const char* text, const char* cond, bool autogen) {
    // Semantic actions are used in codegen after AST is destroyed, so they use output allocator.
    SemAct* a = out_alc.alloct<SemAct>(1);
    a->loc = loc;
    a->text = text;
    a->cond = cond;
    a->autogen = autogen;
    return a;
}

const char* Ast::cstr_local(const uint8_t* s, const uint8_t* e) {
    return newcstr(s, e, ast_alc);
}

const char* Ast::cstr_global(const uint8_t* s, const uint8_t* e) {
    // "Global" strings are used in codegen after AST is destroyed, so they use output allocator.
    return newcstr(s, e, out_alc);
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
        return true;
    }
    return false; // unreachable
}

AstGram::AstGram(const std::string& name)
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

AstBlock::AstBlock(const std::string& name, const opt_t* opts, const AstGrams& grams)
    : name(name), opts(opts), grams(grams) {}

AstBlocks::AstBlocks(): blocks() {}

AstBlocks::~AstBlocks() {
    for (AstBlock* b : blocks) {
        delete b;
    }
}

bool AstBlocks::empty() const {
    return blocks.empty();
}

void AstBlocks::add(const std::string& name, const opt_t* opts, const AstGrams& grams) {
    blocks.push_back(new AstBlock(name, opts, grams));
}

const AstBlock* AstBlocks::find(const std::string& name) const {
    if (name.empty()) {
        if (!blocks.empty()) {
            return blocks.back();
        }
        error("cannot find `rules` block");
    } else {
        for (const AstBlock* b : blocks) {
            if (b->name == name) return b;
        }
        error("cannot find `rules` block named `%s`", name.c_str());
    }
    return nullptr;
}

const opt_t* AstBlocks::last_opts() const {
    return blocks.empty() ? nullptr : blocks.back()->opts;
}

AstGram& find_or_add_gram(AstGrams& grams, const std::string& name) {
    for (AstGram& gram : grams) {
        if (gram.name == name) return gram;
    }
    grams.push_back(AstGram(name));
    return grams.back();
}

template<typename T>
static inline void append(std::vector<T>& x, const std::vector<T>& y) {
    x.insert(x.end(), y.begin(), y.end());
}

Ret use_block(Input& input, const Ast& ast, Opt& opts, AstGrams& grams, const std::string& name) {
    const AstBlock* b = ast.blocks.find(name);
    if (b == nullptr) return Ret::FAIL;

    for (const AstGram& g : b->grams) {
        AstGram& gram = find_or_add_gram(grams, g.name);

        // Merge rules. Inherited special rules *, $ and <!> are kept separate from those defined in
        // the current block, because they are handled differently: they have lower priority and it
        // is allowed to override them with local rules (while within one block redefinition of a
        // special rule is an error).
        append(gram.rules, g.rules);
        append(gram.inherited_defs, g.defs);
        append(gram.inherited_eofs, g.eofs);
        append(gram.inherited_setup, g.setup);
    }

    // Merge configurations and symtab.
    return opts.merge(b->opts, input);
}

Ret check_and_merge_special_rules(AstGrams& grams, const opt_t* opts, Msg& msg, Ast& ast) {
    if (grams.empty()) return Ret::OK;

    for (const AstGram& g : grams) {
        if (g.defs.size() > 1) {
            RET_FAIL(msg.error(g.defs[1]->loc,
                               "code to default rule %sis already defined at line %u",
                               incond(g.name).c_str(), g.defs[0]->loc.line));
        } else if (g.eofs.size() > 1) {
            RET_FAIL(msg.error(g.eofs[1]->loc,
                               "EOF rule %sis already defined at line %u",
                               incond(g.name).c_str(), g.eofs[0]->loc.line));
        } else if (g.rules.empty() && g.defs.empty() && !g.eofs.empty()) {
            RET_FAIL(msg.error(g.eofs[0]->loc,
                               "EOF rule %swithout other rules doesn't make sense",
                               incond(g.name).c_str()));
        }
    }

    if (!opts->start_conditions) {
        // normal mode: there must be no named grams corresponding to conditions
        for (const AstGram& g : grams) {
            if (!g.name.empty()) { // found named gram
                const loc_t& loc = !g.rules.empty() ? g.rules[0].semact->loc
                        : !g.defs.empty() ? g.defs[0]->loc : NOWHERE;
                RET_FAIL(msg.error(loc,
                                   "conditions are only allowed with '-c', '--conditions' option"));
            }
        }
    } else if (grams.size() == 1 && grams[0].name.empty()) {
        // condition mode, a single unnamed gram => ok, normal blocks are allowed
    } else {
        // condition mode, at least one named gram => this is a block with conditions

        for (const AstGram& g : grams) {
            if (g.name.empty()) { // found unnamed gram
                const loc_t& l = !g.rules.empty() ? g.rules[0].semact->loc
                        : !g.defs.empty() ? g.defs[0]->loc : NOWHERE;
                RET_FAIL(msg.error(l, "cannot mix conditions with normal rules"));
            }
        }

        for (const AstGram& g : grams) {
            if (g.setup.size() > 1) {
                RET_FAIL(msg.error(g.setup[1]->loc,
                                   "code to setup rule `%s` is already defined at line %u",
                                   g.name.c_str(), g.setup[0]->loc.line));
            }
        }

        for (const AstGram& g : grams) {
            if (g.name != "*" && !g.setup.empty() && g.rules.empty()) {
                RET_FAIL(msg.error(g.setup[0]->loc,
                                   "setup for non existing condition `%s` found", g.name.c_str()));
            }
        }

        auto no_setup = std::find_if(
                grams.begin(), grams.end(), [](const AstGram& g) { return g.setup.empty(); });
        if (no_setup == grams.end()) { // all grams have setup
            for (const AstGram& g : grams) {
                if (g.name == "*") {
                    RET_FAIL(msg.error(g.setup[0]->loc,
                                       "setup for all conditions '<!*>' is illegal if setup for "
                                       "each condition is defined explicitly"));
                }
            }
        }

        for (const AstGram& g : grams) {
            if (g.name == "0" && g.rules.size() > 1) {
                RET_FAIL(msg.error(g.rules[1].semact->loc,
                                   "startup code is already defined at line %u",
                                   g.rules[0].semact->loc.line));
            }
        }
    }

    // Inherit special rules from other blocks (unless a local one is defined).
    for (AstGram& g : grams) {
        append(g.defs, g.inherited_defs);
        append(g.eofs, g.inherited_eofs);
        append(g.setup, g.inherited_setup);
    }

    // Merge <*> rules and <!*> setup to all conditions except "0". Star rules must have lower
    // priority than normal rules.
    auto star = std::find_if(
            grams.begin(), grams.end(), [](const AstGram& g) { return g.name == "*"; });
    if (star != grams.end()) {
        for (AstGram& g : grams) {
            if (g.name != "*" && g.name != "0") {
                append(g.rules, star->rules);
                append(g.defs, star->defs);
                append(g.eofs, star->eofs);
                append(g.setup, star->setup);
            }
        }
        grams.erase(star);
    }

    // Merge end of input rule $ and default rule * with the lowest priority.
    for (AstGram& g : grams) {
        // See note [EOF rule handling].
        if (!g.eofs.empty()) {
            g.eof_rule = g.rules.size();
            const SemAct* a = g.eofs[0];
            g.rules.push_back(AstRule(ast.nil(a->loc), a));
        }
        if (!g.defs.empty()) {
            g.def_rule = g.rules.size();
            const SemAct* a = g.defs[0];
            g.rules.push_back(AstRule(ast.def(a->loc), a));
        }
    }

    // "0" condition must be the first one.
    auto zero = std::find_if(
            grams.begin(), grams.end(), [](const AstGram& g) { return g.name == "0"; });
    if (zero != grams.end() && zero != grams.begin()) {
        AstGram zero_copy(*zero);
        grams.erase(zero);
        grams.insert(grams.begin(), zero_copy);
    }

    // Check that `re2c:eof` configuration and the $ rule are used together. This must be done after
    // merging rules inherited from other blocks and <*> condition (because they might add $ rule).
    for (const AstGram& g : grams) {
        if (!g.eofs.empty() && opts->fill_eof == NOEOF) {
            RET_FAIL(msg.error(g.eofs[0]->loc,
                               "%s$ rule found, but `re2c:eof` configuration is not set",
                               incond(g.name).c_str()));
        } else if (g.eofs.empty() && opts->fill_eof != NOEOF) {
            RET_FAIL(error("%s`re2c:eof` configuration is set, but no $ rule found",
                           incond(g.name).c_str()));
        }
    }

    return Ret::OK;
}

// C++11 requres outer decl for ODR-used static constexpr data members (not needed in C++17).
constexpr uint32_t Ast::MANY;

} // namespace re2c
