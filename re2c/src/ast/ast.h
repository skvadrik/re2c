#ifndef _RE2C_AST_AST_
#define _RE2C_AST_AST_

#include "src/util/c99_stdint.h"
#include <map>
#include <string>
#include <vector>

#include "src/ast/scanner.h"
#include "src/re/rule.h"
#include "src/util/free_list.h"
#include "src/util/range.h"

namespace re2c
{

struct Code;
template <class _Ty> class free_list;

struct ASTChar
{
    uint32_t chr;
    uint32_t column;
    ASTChar(uint32_t x, uint32_t c)
        : chr(x), column(c) {}
};

struct ASTRange
{
    uint32_t lower;
    uint32_t upper;
    uint32_t column;
    ASTRange(uint32_t l, uint32_t u, uint32_t c)
        : lower(l), upper(u), column(c) {}
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
    uint32_t line;
    uint32_t column;

    AST(uint32_t l, uint32_t c, type_t t);
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
    std::vector<const Code*> setup;

    explicit spec_t(const std::string &n):
        name(n), rules(), defs(), setup() {}
};

typedef std::vector<spec_t> specs_t;
typedef std::map<std::string, const AST*> symtab_t;

const AST *ast_nil(uint32_t l, uint32_t c);
const AST *ast_str(uint32_t l, uint32_t c, std::vector<ASTChar> *chars, bool icase);
const AST *ast_cls(uint32_t l, uint32_t c, std::vector<ASTRange> *ranges, bool negated);
const AST *ast_dot(uint32_t l, uint32_t c);
const AST *ast_default(uint32_t l, uint32_t c);
const AST *ast_alt(const AST *a1, const AST *a2);
const AST *ast_cat(const AST *a1, const AST *a2);
const AST *ast_iter(const AST *a, uint32_t n, uint32_t m);
const AST *ast_diff(const AST *a1, const AST *a2);
const AST *ast_tag(uint32_t l, uint32_t c, const std::string *n, bool h);
const AST *ast_cap(const AST *a);
const AST *ast_ref(const AST *a, const std::string &n);
bool ast_need_wrap(const AST *a);

void validate_mode(Scanner::ParseMode mode, bool rflag, bool rules, Scanner &input);
void validate_ast(const specs_t &specs, bool cflag);
void normalize_ast(specs_t &specs);

} // namespace re2c

#endif // _RE2C_AST_AST_
