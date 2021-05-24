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

struct spec_t {
    std::string name;
    std::vector<ASTRule> rules;
    std::vector<const SemAct*> defs;
    std::vector<const SemAct*> eofs;
    std::vector<const SemAct*> setup;
    size_t def_rule;
    size_t eof_rule;

    explicit spec_t(const std::string &n)
        : name(n), rules(), defs(), eofs(), setup()
        , def_rule(Rule::NONE), eof_rule(Rule::NONE) {}
};

typedef std::vector<spec_t> specs_t;

struct rules_block_t {
    const std::string name;
    const opt_t *opts;
    specs_t specs;
};

typedef std::vector<rules_block_t> rules_blocks_t;
typedef std::map<std::string, const AST*> symtab_t;

struct context_t
{
    Scanner &input;
    specs_t &specs;
    symtab_t &symtab;
    Opt &opts;
    const rules_blocks_t &rules;
};

void parse(Scanner &input, specs_t &specs, symtab_t &symtab, Opt &opts,
    const rules_blocks_t &rules);
const rules_block_t *find_rules_block(const std::string &name,
    const rules_blocks_t &rules);
void validate_mode(Scanner::ParseMode mode, bool rflag, bool rules, Scanner &input);
void validate_ast(const specs_t &specs, const opt_t *opts, Msg &msg);
void normalize_ast(specs_t &specs);

} // namespace re2c

#endif // _RE2C_AST_PARSE_
