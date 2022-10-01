#ifndef _RE2C_OPTIONS_SYMTAB_
#define _RE2C_OPTIONS_SYMTAB_

#include <string.h>
#include <map>

#include "src/constants.h"
#include "src/util/attribute.h"

namespace re2c {

struct AstNode;
class Input;

struct symtab_cmp_t {
    inline bool operator()(const char* x, const char* y) const { 
        return strcmp(x, y) < 0;
    }
};

using symtab_t = std::map<const char*, const AstNode*, symtab_cmp_t>;

const AstNode* find_def(const symtab_t& symtab, const char* name) NODISCARD;
Ret add_named_def(symtab_t& symtab, const char* name, const AstNode* ast, Input& input) NODISCARD;
Ret merge_symtab(symtab_t& symtab, const symtab_t& other, Input& input) NODISCARD;

} // namespace re2c

#endif // _RE2C_OPTIONS_SYMTAB_
