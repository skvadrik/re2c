#include "src/msg/msg.h"
#include "src/options/symtab.h"
#include "src/parse/input.h"

namespace re2c {

const AstNode* find_def(const symtab_t& symtab, const char* name) {
    symtab_t::const_iterator i = symtab.find(name);
    return i == symtab.end() ? nullptr : i->second;
}

Ret add_named_def(symtab_t& symtab, const char* name, const AstNode* ast, Input& input) {
    symtab_t::iterator i = symtab.find(name);
    if (i == symtab.end()) {
        // Ok, a new named definition, add it.
        symtab.insert(i, {name, ast});
        return Ret::OK;
    } else if (ast == i->second) {
        // Ok, an existing name with the same definition (note that we compare for pointer equality
        // of the AST, meaning that it is the same AST as before, not and identical one). Just skip
        // and do nothing (no error).
        //
        // This may happen if a name is defined in global scope and inherited by a `rules` block
        // that is followed by another block that uses the rules block with a `!use` directive. At
        // the time when symtab from the rules block is merged with the inherited one, there is a
        // collision on the global names that are present in both symtabs. It's harmless.
        return Ret::OK;
    } else {
        // Fail, as the same name is redefined to a different AST (don't bother checking if the ASTs
        // are identical, as there is no known valid use case for that).
        RET_FAIL(input.error_at_tok("name `%s` is already defined", name));
    }
}

Ret merge_symtab(symtab_t& symtab, const symtab_t& other, Input& input) {
    for (const auto& i : other) {
        CHECK_RET(add_named_def(symtab, i.first, i.second, input));
    }
    return Ret::OK;
}

} // namespace re2c
