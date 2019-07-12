#ifndef _RE2C_AST_PARSE_
#define _RE2C_AST_PARSE_

#include <set>
#include <string>

#include "src/parse/ast.h"
#include "src/parse/scanner.h"
#include "src/options/opt.h"


namespace re2c {

class Scanner;
struct Opt;

typedef std::set<std::string> CondList;

struct context_t
{
    Scanner &input;
    specs_t &specs;
    symtab_t &symtab;
    Opt &opts;
};

void parse(Scanner &input, specs_t &specs, symtab_t &symtab, Opt &opts);
void validate_mode(Scanner::ParseMode mode, bool rflag, bool rules, Scanner &input);
void validate_ast(const specs_t &specs, const opt_t *opts, Msg &msg);
void normalize_ast(specs_t &specs);

} // namespace re2c

#endif // _RE2C_AST_PARSE_
