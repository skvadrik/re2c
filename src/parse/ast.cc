#include <limits>

#include "src/parse/ast.h"
#include "src/util/free_list.h"


namespace re2c {

free_list<AST*> AST::flist;

const uint32_t AST::MANY = std::numeric_limits<uint32_t>::max();

AST::AST(const loc_t &l, type_t t)
    : type(t), loc(l)
{
    flist.insert(this);
}

AST::~AST()
{
    flist.erase(this);
    if (type == TAG) {
        delete tag.name;
    } else if (type == REF) {
        delete ref.name;
    } else if (type == STR) {
        delete str.chars;
    } else if (type == CLS) {
        delete cls.ranges;
    }
}

const AST *ast_nil(const loc_t &loc)
{
    return new AST(loc, AST::NIL);
}

const AST *ast_str(const loc_t &loc, std::vector<ASTChar> *chars, bool icase)
{
    AST *ast = new AST(loc, AST::STR);
    ast->str.chars = chars;
    ast->str.icase = icase;
    return ast;
}

const AST *ast_cls(const loc_t &loc, std::vector<ASTRange> *ranges, bool negated)
{
    AST *ast = new AST(loc, AST::CLS);
    ast->cls.ranges = ranges;
    ast->cls.negated = negated;
    return ast;
}

const AST *ast_dot(const loc_t &loc)
{
    return new AST(loc, AST::DOT);
}

const AST *ast_default(const loc_t &loc)
{
    return new AST(loc, AST::DEFAULT);
}

const AST *ast_alt(const AST *a1, const AST *a2)
{
    if (!a1) return a2;
    if (!a2) return a1;
    AST *ast = new AST(a1->loc, AST::ALT);
    ast->alt.ast1 = a1;
    ast->alt.ast2 = a2;
    return ast;
}

const AST *ast_cat(const AST *a1, const AST *a2)
{
    if (!a1) return a2;
    if (!a2) return a1;
    AST *ast = new AST(a1->loc, AST::CAT);
    ast->cat.ast1 = a1;
    ast->cat.ast2 = a2;
    return ast;
}

const AST *ast_iter(const AST *a, uint32_t n, uint32_t m)
{
    AST *ast = new AST(a->loc, AST::ITER);
    ast->iter.ast = a;
    ast->iter.min = n;
    ast->iter.max = m;
    return ast;
}

const AST *ast_diff(const AST *a1, const AST *a2)
{
    AST *ast = new AST(a1->loc, AST::DIFF);
    ast->cat.ast1 = a1;
    ast->cat.ast2 = a2;
    return ast;
}

const AST *ast_tag(const loc_t &loc, const std::string *n, bool h)
{
    AST *ast = new AST(loc, AST::TAG);
    ast->tag.name = n;
    ast->tag.history = h;
    return ast;
}

const AST *ast_cap(const AST *a)
{
    AST *ast = new AST(a->loc, AST::CAP);
    ast->cap = a;
    return ast;
}

const AST *ast_ref(const AST *a, const std::string &n)
{
    AST *ast = new AST(a->loc, AST::REF);
    ast->ref.ast = a;
    ast->ref.name = new std::string(n);
    return ast;
}

bool ast_need_wrap(const AST *a)
{
    switch (a->type) {
        case AST::ITER:
        case AST::NIL:
        case AST::STR:
        case AST::CLS:
        case AST::DOT:
        case AST::DEFAULT:
        case AST::TAG:
        case AST::CAP:
            return false;
        case AST::ALT:
        case AST::CAT:
        case AST::DIFF:
        case AST::REF:
            return true;
    }
    return false; /* unreachable */
}

} // namespace re2c
