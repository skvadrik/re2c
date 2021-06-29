#include <stdlib.h>

#include "src/msg/location.h"
#include "src/msg/msg.h"
#include "src/options/symtab.h"


namespace re2c {

const AST *find_def(const symtab_t &symtab, const std::string &name,
    const loc_t &loc, Msg &msg)
{
    symtab_t::const_iterator i = symtab.find(name);
    if (i == symtab.end()) {
        msg.error(loc, "undefined symbol '%s'", name.c_str());
        exit(1);
    }
    return i->second;
}

void add_named_def(symtab_t &symtab, const std::string &name, const AST *ast,
    const loc_t &loc, Msg &msg)
{
    symtab_t::iterator i = symtab.lower_bound(name);
    if (i != symtab.end() && !(symtab.key_comp()(name, i->first))) {
        msg.error(loc, "name '%s' is already defined", name.c_str());
        exit(1);
    } else {
        symtab.insert(i, symtab_t::value_type(name, ast));
    }
}

void merge_symtab(symtab_t &symtab, const symtab_t &other, const loc_t &loc, Msg &msg)
{
    for (symtab_t::const_iterator i = other.begin(); i != other.end(); ++i) {
        add_named_def(symtab, i->first, i->second, loc, msg);
    }
}

} // namespace re2c
