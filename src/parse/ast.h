#ifndef _RE2C_AST_AST_
#define _RE2C_AST_AST_

#include "src/util/c99_stdint.h"
#include <map>
#include <string>
#include <vector>

#include "src/msg/location.h"


namespace re2c {

struct Code;
template <class _Ty> class free_list;

struct ASTChar
{
    uint32_t chr;
    loc_t loc;
};

struct ASTRange
{
    uint32_t lower;
    uint32_t upper;
    loc_t loc;

    ASTRange(uint32_t low, uint32_t upp, const loc_t &loc)
        : lower(low), upper(upp), loc(loc) {}
};

/* AST must be immutable and independent of options */
struct AST
{
    static free_list<AST*> flist;
    static const uint32_t MANY;

    enum type_t
        { NIL, STR,  CLS,  DOT,  DEFAULT, ALT
        , CAT, ITER, DIFF, TAG,  CAP,     REF } type;
    union {
        struct {
            const std::vector<ASTChar> *chars;
            bool icase;
        } str;
        struct {
            const std::vector<ASTRange> *ranges;
            bool negated;
        } cls;
        struct {
            const AST *ast1;
            const AST *ast2;
        } alt;
        struct {
            const AST *ast1;
            const AST *ast2;
        } cat;
        struct {
            const AST *ast;
            uint32_t min;
            uint32_t max;
        } iter;
        struct {
            const AST *ast1;
            const AST *ast2;
        } diff;
        struct {
            const std::string *name;
            bool history;
        } tag;
        const AST *cap;
        struct {
            const AST *ast;
            const std::string *name;
        } ref;
    };
    loc_t loc;

    AST(const loc_t &loc, type_t t);
    ~AST();
};

struct ASTRule
{
    const AST *ast;
    const Code *code;

    ASTRule(const AST *r, const Code *c)
        : ast(r)
        , code(c)
    {}
};

struct ASTBounds
{
    uint32_t min;
    uint32_t max;
};

struct spec_t
{
    std::string name;
    std::vector<ASTRule> rules;
    std::vector<const Code*> defs;
    std::vector<const Code*> eofs;
    std::vector<const Code*> setup;

    explicit spec_t(const std::string &n):
        name(n), rules(), defs(), eofs(), setup() {}
};

typedef std::vector<spec_t> specs_t;
typedef std::map<std::string, const AST*> symtab_t;

const AST *ast_nil(const loc_t &loc);
const AST *ast_str(const loc_t &loc, std::vector<ASTChar> *chars, bool icase);
const AST *ast_cls(const loc_t &loc, std::vector<ASTRange> *ranges, bool negated);
const AST *ast_dot(const loc_t &loc);
const AST *ast_default(const loc_t &loc);
const AST *ast_alt(const AST *a1, const AST *a2);
const AST *ast_cat(const AST *a1, const AST *a2);
const AST *ast_iter(const AST *a, uint32_t n, uint32_t m);
const AST *ast_diff(const AST *a1, const AST *a2);
const AST *ast_tag(const loc_t &loc, const std::string *n, bool h);
const AST *ast_cap(const AST *a);
const AST *ast_ref(const AST *a, const std::string &n);
bool ast_need_wrap(const AST *a);

} // namespace re2c

#endif // _RE2C_AST_AST_
