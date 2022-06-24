#include <limits>

#include "src/debug/debug.h"
#include "src/parse/ast.h"
#include "src/util/string_utils.h"

namespace re2c {

AstNode* Ast::make(const loc_t& loc, AstKind kind) {
    AstNode* p = allocator.alloct<AstNode>(1);
    p->kind = kind;
    p->loc = loc;
    return p;
}

const AstNode* Ast::nil(const loc_t& loc) {
    return make(loc, AstKind::NIL);
}

const AstNode* Ast::str(const loc_t& loc, bool icase) {
    AstNode* ast = make(loc, AstKind::STR);
    ast->str.chars.init(temp_chars.data(), temp_chars.size(), allocator);
    ast->str.icase = icase;
    temp_chars.clear();
    return ast;
}

const AstNode* Ast::cls(const loc_t& loc, bool negated) {
    AstNode* ast = make(loc, AstKind::CLS);
    ast->cls.ranges.init(temp_ranges.data(), temp_ranges.size(), allocator);
    ast->cls.negated = negated;
    temp_ranges.clear();
    return ast;
}

const AstNode* Ast::dot(const loc_t& loc) {
    return make(loc, AstKind::DOT);
}

const AstNode* Ast::def(const loc_t& loc) {
    return make(loc, AstKind::DEF);
}

const AstNode* Ast::alt(const AstNode* a1, const AstNode* a2) {
    if (!a1) return a2;
    if (!a2) return a1;
    AstNode* ast = make(a1->loc, AstKind::ALT);
    ast->alt.ast1 = a1;
    ast->alt.ast2 = a2;
    return ast;
}

const AstNode* Ast::cat(const AstNode* a1, const AstNode* a2) {
    if (!a1) return a2;
    if (!a2) return a1;
    AstNode* ast = make(a1->loc, AstKind::CAT);
    ast->cat.ast1 = a1;
    ast->cat.ast2 = a2;
    return ast;
}

const AstNode* Ast::iter(const AstNode* a, uint32_t n, uint32_t m) {
    DASSERT(n <= m);
    AstNode* ast = make(a->loc, AstKind::ITER);
    ast->iter.ast = a;
    ast->iter.min = n;
    ast->iter.max = m;
    return ast;
}

const AstNode* Ast::diff(const AstNode* a1, const AstNode* a2) {
    AstNode* ast = make(a1->loc, AstKind::DIFF);
    ast->cat.ast1 = a1;
    ast->cat.ast2 = a2;
    return ast;
}

const AstNode* Ast::tag(const loc_t& loc, const char* n, bool h) {
    AstNode* ast = make(loc, AstKind::TAG);
    ast->tag.name = n;
    ast->tag.history = h;
    return ast;
}

const AstNode* Ast::cap(const AstNode* a) {
    AstNode* ast = make(a->loc, AstKind::CAP);
    ast->cap = a;
    return ast;
}

const AstNode* Ast::ref(const AstNode* a, const char* n) {
    AstNode* ast = make(a->loc, AstKind::REF);
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

const char* Ast::cstr(const char* s, const char* e) {
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

} // namespace re2c
