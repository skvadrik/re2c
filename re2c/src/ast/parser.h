#ifndef _RE2C_AST_PARSER_
#define _RE2C_AST_PARSER_

#include <set>
#include <string>

#include "src/ast/ast.h"
#include "src/conf/opt.h"
#include "src/ast/scanner.h"

namespace re2c
{

typedef std::set<std::string> CondList;

struct context_t
{
	Scanner &input;
	specs_t &specs;
	symtab_t &symtab;
	Opt &opts;
};

void parse(Scanner &input, specs_t &specs, symtab_t &symtab, Opt &opts);

} // namespace re2c

#endif // _RE2C_AST_PARSER_
