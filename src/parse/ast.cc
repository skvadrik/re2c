#include <stddef.h>
#include <limits>

#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/parse/ast.h"
#include "src/regexp/rule.h"
#include "src/util/check.h"
#include "src/util/string_utils.h"

// note [end-of-input symbol]
//
// End-of-input symbol $ may occur as part of a regexp in a normal rule. As a result, TDFA will
// have a state that is accepting only if the end of input is reached in this state. Such states
// differ from normal states in a few ways:
//
// - They cannot be fallback states (it's not possible to fallback to such state, as it's either
//   an immediate end of input and match, or there's more input and no match).
//
// - With regard to unreachable rules, end-of-input final states cannot completely shadow normal
//   final states, as there's always a possibility of no match (depending on the length of input).
//
// - With regard to undefined control flow, in any non-accepting state there's always a
//   possibility of failure to default state, as there may be an unexpected end of input.
//
// Internally end-of-input symbol $ is implemented as a pseudo-transition on a fake code unit
// outside of the current charset. This has the advantage that there's still at most one rule
// per TDFA state (as opposed to having both a normal rule and an end-of-input rule), which is
// convenient for algorithms like -Wunreachable-rules analysis and TDFA minimization.

namespace re2c {

const char* ZERO_COND = "0";
static const char* STAR_COND = "*";

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

const AstNode* Ast::eof(const loc_t& loc) {
    return make(loc, AstKind::END, NO_CAPTURE);
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
    ast->diff.ast1 = a1;
    ast->diff.ast2 = a2;
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
    a->is_star = false;
    a->is_used = false;
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
    case AstKind::END:
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
      entry(),
      pre_rule(),
      post_rule(),
      inherited_defs(),
      inherited_eofs(),
      inherited_entry(),
      inherited_pre_rule(),
      inherited_post_rule(),
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

ptrdiff_t find_gram_idx(AstGrams& grams, const std::string& name) {
    auto i = std::find_if(grams.begin(), grams.end(),
            [&](const AstGram& g) { return g.name == name; });
    return (i == grams.end()) ? -1 : (i - grams.begin());
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

        // Merge rules. Inherited special rules and actions are kept separate from those
        // defined in the current block, because they are handled differently: they have lower
        // priority and it is allowed to override them with local rules (while it is an error
        // to redefine special rule within one block).
        append(gram.rules, g.rules);
        append(gram.inherited_defs, g.defs);
        append(gram.inherited_eofs, g.eofs);
        append(gram.inherited_entry, g.entry);
        append(gram.inherited_pre_rule, g.pre_rule);
        append(gram.inherited_post_rule, g.post_rule);
    }

    // Merge configurations and symtab.
    return opts.merge(b->opts, input);
}

static const loc_t& find_rule_location(const AstGram& g) {
    // Try to find location of some rule.

    if (!g.rules.empty()) return g.rules[0].semact->loc;
    if (!g.defs.empty()) return g.defs[0]->loc;
    if (!g.eofs.empty()) return g.eofs[0]->loc;
    if (!g.entry.empty()) return g.entry[0]->loc;
    if (!g.pre_rule.empty()) return g.pre_rule[0]->loc;
    if (!g.post_rule.empty()) return g.post_rule[0]->loc;

    if (!g.inherited_defs.empty()) return g.inherited_defs[0]->loc;
    if (!g.inherited_eofs.empty()) return g.inherited_eofs[0]->loc;
    if (!g.inherited_entry.empty()) return g.inherited_entry[0]->loc;
    if (!g.inherited_pre_rule.empty()) return g.inherited_pre_rule[0]->loc;
    if (!g.inherited_post_rule.empty()) return g.inherited_post_rule[0]->loc;

    UNREACHABLE();
    return NOWHERE;
}

bool is_oldstyle_eof(const AstNode* ast) {
    return ast->kind == AstKind::CAP
        && ast->cap.ast->kind == AstKind::END;
}

void AstGram::add_rule(AstRule&& r) {
    if (is_oldstyle_eof(r.ast)) {
        eofs.push_back(r.semact);
    }
    rules.push_back(std::move(r));
}

Ret check_and_merge_special_rules(AstGrams& grams, const opt_t* opts, Msg& msg, Ast& ast) {
    if (grams.empty()) return Ret::OK;

    for (const AstGram& g : grams) {
        // Check for redundant special rules and actions.
#define CHECK_SPECIAL(what, str) \
        if (g.what.size() > 1) { \
            RET_FAIL(msg.error(g.what[1]->loc, "%s %sis already defined at line %u", \
                str, incond(g.name).c_str(), g.what[0]->loc.line)); \
        }
        CHECK_SPECIAL(defs, "default rule");
        CHECK_SPECIAL(entry, "entry action");
        CHECK_SPECIAL(pre_rule, "pre-rule action");
        CHECK_SPECIAL(post_rule, "post-rule action");
#undef CHECK_SPECIAL
    }

    if (!opts->start_conditions) {
        // normal mode: there must be no named grams corresponding to conditions
        for (const AstGram& g : grams) {
            if (!g.name.empty()) { // found named gram
                RET_FAIL(msg.error(find_rule_location(g),
                    "conditions are only allowed with '-c', '--conditions' option"));
            }
        }
    } else if (grams.size() == 1 && grams[0].name.empty()) {
        // condition mode, a single unnamed gram => ok, normal blocks are allowed
    } else {
        // condition mode, at least one named gram => this is a block with conditions
        for (const AstGram& g : grams) {
            if (g.name.empty()) { // found unnamed gram
                RET_FAIL(msg.error(find_rule_location(g),
                    "cannot mix conditions with normal rules"));
            }
        }

        // Check for redundant actions in `<*>` condiiton or nonexistent conditions.
#define CHECK_ACTION(action, str) do { \
        bool all_conds_have_it = true; \
        const SemAct* star_action = nullptr; \
        for (const AstGram& g : grams) { \
            if (g.action.empty()) { \
                all_conds_have_it = false; \
            } else if (g.name == STAR_COND) { \
                star_action = g.action[0]; \
            } else if (g.rules.empty()) { \
                RET_FAIL(msg.error(g.action[0]->loc, \
                    "%s action for non-existing condition `%s` found", \
                    str, g.name.c_str())); \
            } \
        } \
        if (star_action && all_conds_have_it) { \
            RET_FAIL(msg.error(star_action->loc, \
                "%s action for all conditions `*` is unused, as it's already defined " \
                "for each condition individually", str)); \
        } \
} while(0)
        CHECK_ACTION(entry, "entry");
        CHECK_ACTION(pre_rule, "pre-rule");
        CHECK_ACTION(post_rule, "post-rule");
#undef CHECK_ACTION

        // Check zero condition. It has similar purpose to the !entry action, but the latter
        // is per-condition, while <> is one for all conditions.
        for (const AstGram& g : grams) {
            if (g.name == ZERO_COND && g.rules.size() > 1) {
                RET_FAIL(msg.error(g.rules[1].semact->loc,
                    "entry action is already defined at line %u", g.rules[0].semact->loc.line));
            }
        }
    }

    // Inherit special rules from other blocks (unless a local one is defined).
    for (AstGram& g : grams) {
        append(g.defs, g.inherited_defs);
        append(g.eofs, g.inherited_eofs);
        append(g.entry, g.inherited_entry);
        append(g.pre_rule, g.inherited_pre_rule);
        append(g.post_rule, g.inherited_post_rule);
    }

    // Find "*" condition (if any). The index stays valid after possible container resize below.
    ptrdiff_t star_idx = find_gram_idx(grams, STAR_COND);

    // Some conditions may occur only in `=>` and `:=>` but not on any condition list.
    // They might still be nonempty if `<*>` rules are merged to them, otherwise report an error.
    if (opts->start_conditions) {
#define MAYBE_ADD_COND(a) \
        if (!a->cond || find_gram_idx(grams, a->cond) >= 0) { \
            /* ok, either no condition or an existing one */ \
        } else if (star_idx >= 0) { \
            grams.push_back(AstGram(a->cond)); \
        } else { \
            RET_FAIL(msg.error(a->loc, "reference to undefined condition '%s'", a->cond)); \
        }
        for (size_t i = 0; i < grams.size(); ++i) {
            for (const AstRule& r : grams[i].rules) MAYBE_ADD_COND(r.semact);
            for (const SemAct* a : grams[i].defs) MAYBE_ADD_COND(a);
        }
#undef MAYBE_ADD_COND
    }

    // Merge <*> rules and actions to all conditions except zero condition <>.
    // Star rules must have lower priority than normal rules.
    if (star_idx >= 0) {
        AstGram& star = grams[static_cast<size_t>(star_idx)];
        // Mark <*> actions before merging - this is needed for reachability analysis.
        for (AstRule& r : star.rules) {
            if (r.semact) r.semact->is_star = true;
        }
        for (const SemAct* a : star.defs) a->is_star = true;
        for (const SemAct* a : star.eofs) a->is_star = true;
        for (const SemAct* a : star.entry) a->is_star = true;
        for (const SemAct* a : star.pre_rule) a->is_star = true;
        for (const SemAct* a : star.post_rule) a->is_star = true;

        for (AstGram& g : grams) {
            if (g.name != STAR_COND && g.name != ZERO_COND) {
                append(g.rules, star.rules);
                append(g.defs, star.defs);
                append(g.eofs, star.eofs);
                append(g.entry, star.entry);
                append(g.pre_rule, star.pre_rule);
                append(g.post_rule, star.post_rule);
            }
        }
        grams.erase(grams.begin() + star_idx);
    }

    for (AstGram& g : grams) {
        // Find end-of-input rule $. TODO: drop this after deprecating old-style $ rule.
        if (!g.eofs.empty()) {
            for (size_t i = 0; i < g.rules.size(); ++i) {
                if (g.rules[i].semact == g.eofs[0]) {
                    g.eof_rule = i;
                    break;
                }
            }
            CHECK(g.eof_rule != Rule::NONE);
        }
        // Merge default rule * with the lowest priority.
        if (!g.defs.empty()) {
            g.def_rule = g.rules.size();
            const SemAct* a = g.defs[0];
            g.rules.push_back({ast.def(a->loc), a});
        }
    }

    // zero condition must be the first one.
    auto zero = std::find_if(
            grams.begin(), grams.end(), [](const AstGram& g) { return g.name == ZERO_COND; });
    if (zero != grams.end() && zero != grams.begin()) {
        AstGram zero_copy(*zero);
        grams.erase(zero);
        grams.insert(grams.begin(), zero_copy);
    }

    return Ret::OK;
}

// C++11 requres outer decl for ODR-used static constexpr data members (not needed in C++17).
constexpr uint32_t Ast::MANY;

} // namespace re2c
