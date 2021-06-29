#ifndef _RE2C_OPTIONS_SYMTAB_
#define _RE2C_OPTIONS_SYMTAB_

#include <map>
#include <string>


namespace re2c {

struct AST;
struct loc_t;
struct Msg;

typedef std::map<std::string, const AST*> symtab_t;

const AST *find_def(const symtab_t &symtab, const std::string &name,
    const loc_t &loc, Msg &msg);
void add_named_def(symtab_t &symtab, const std::string &name, const AST *ast,
    const loc_t &loc, Msg &msg);
void merge_symtab(symtab_t &symtab, const symtab_t &other, const loc_t &loc, Msg &msg);

} // namespace re2c

#endif // _RE2C_OPTIONS_SYMTAB_
