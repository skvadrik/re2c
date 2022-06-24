#ifndef _RE2C_OPTIONS_SYMTAB_
#define _RE2C_OPTIONS_SYMTAB_

#include <string.h>
#include <map>

namespace re2c {

struct AstNode;
struct loc_t;
class Msg;

struct symtab_cmp_t {
    inline bool operator()(const char* x, const char* y) const { 
        return strcmp(x, y) < 0;
    }
};

using symtab_t = std::map<const char*, const AstNode*, symtab_cmp_t>;

const AstNode* find_def(const symtab_t& symtab, const char* name, const loc_t& loc, Msg& msg);
void add_named_def(
    symtab_t& symtab, const char* name, const AstNode* ast, const loc_t& loc, Msg& msg);
void merge_symtab(symtab_t& symtab, const symtab_t& other, const loc_t& loc, Msg& msg);

} // namespace re2c

#endif // _RE2C_OPTIONS_SYMTAB_
