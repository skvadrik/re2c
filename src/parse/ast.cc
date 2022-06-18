#include <limits>

#include "src/debug/debug.h"
#include "src/parse/ast.h"
#include "src/util/free_list.h"

namespace re2c {

free_list<AST*> AST::flist;

const uint32_t AST::MANY = std::numeric_limits<uint32_t>::max();

AST::AST(const loc_t& l, Kind k): kind(k), loc(l) {
    flist.insert(this);
}

AST::~AST() {
    flist.erase(this);
    if (kind == Kind::TAG) {
        delete tag.name;
    } else if (kind == Kind::REF) {
        delete ref.name;
    } else if (kind == Kind::STR) {
        delete str.chars;
    } else if (kind == Kind::CLS) {
        delete cls.ranges;
    }
}

const AST* ast_nil(const loc_t& loc) {
    return new AST(loc, AST::Kind::NIL);
}

const AST* ast_str(const loc_t& loc, std::vector<ASTChar>* chars, bool icase) {
    AST* ast = new AST(loc, AST::Kind::STR);
    ast->str.chars = chars;
    ast->str.icase = icase;
    return ast;
}

const AST* ast_cls(const loc_t& loc, std::vector<ASTRange>* ranges, bool negated) {
    AST* ast = new AST(loc, AST::Kind::CLS);
    ast->cls.ranges = ranges;
    ast->cls.negated = negated;
    return ast;
}

const AST* ast_dot(const loc_t& loc) {
    return new AST(loc, AST::Kind::DOT);
}

const AST* ast_default(const loc_t& loc) {
    return new AST(loc, AST::Kind::DEFAULT);
}

const AST* ast_alt(const AST* a1, const AST* a2) {
    if (!a1) return a2;
    if (!a2) return a1;
    AST* ast = new AST(a1->loc, AST::Kind::ALT);
    ast->alt.ast1 = a1;
    ast->alt.ast2 = a2;
    return ast;
}

const AST* ast_cat(const AST* a1, const AST* a2) {
    if (!a1) return a2;
    if (!a2) return a1;
    AST* ast = new AST(a1->loc, AST::Kind::CAT);
    ast->cat.ast1 = a1;
    ast->cat.ast2 = a2;
    return ast;
}

const AST* ast_iter(const AST* a, uint32_t n, uint32_t m) {
    DASSERT(n <= m);
    AST* ast = new AST(a->loc, AST::Kind::ITER);
    ast->iter.ast = a;
    ast->iter.min = n;
    ast->iter.max = m;
    return ast;
}

const AST* ast_diff(const AST* a1, const AST* a2) {
    AST* ast = new AST(a1->loc, AST::Kind::DIFF);
    ast->cat.ast1 = a1;
    ast->cat.ast2 = a2;
    return ast;
}

const AST* ast_tag(const loc_t& loc, const std::string* n, bool h) {
    AST* ast = new AST(loc, AST::Kind::TAG);
    ast->tag.name = n;
    ast->tag.history = h;
    return ast;
}

const AST* ast_cap(const AST* a) {
    AST* ast = new AST(a->loc, AST::Kind::CAP);
    ast->cap = a;
    return ast;
}

const AST* ast_ref(const AST* a, const std::string& n) {
    AST* ast = new AST(a->loc, AST::Kind::REF);
    ast->ref.ast = a;
    ast->ref.name = new std::string(n);
    return ast;
}

bool ast_need_wrap(const AST* a) {
    switch (a->kind) {
    case AST::Kind::ITER:
    case AST::Kind::NIL:
    case AST::Kind::STR:
    case AST::Kind::CLS:
    case AST::Kind::DOT:
    case AST::Kind::DEFAULT:
    case AST::Kind::TAG:
    case AST::Kind::CAP:
        return false;
    case AST::Kind::ALT:
    case AST::Kind::CAT:
    case AST::Kind::DIFF:
    case AST::Kind::REF:
        return true;
    }
    return false; // unreachable
}

} // namespace re2c
