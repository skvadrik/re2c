#ifndef _RE2C_PARSE_PARSER_
#define _RE2C_PARSE_PARSER_

#include <list>
#include <map>
#include <string>

#include "src/codegen/output.h"
#include "src/ir/regexp/regexp.h"
#include "src/parse/scanner.h"
#include "src/parse/spec.h"

namespace re2c
{

extern void parse(Scanner &, Output &);
extern void parse_cleanup();
const RegExp *make_rule(const Loc &loc, const RegExp *r1, const RegExp *r2,
	rule_rank_t rank, const Code *code, const std::string *newcond);
const RegExp *make_rule_copy(const RegExp *re, rule_rank_t rank);

typedef std::set<std::string> CondList;
typedef std::list<const RegExp*> RuleList;
typedef std::map<std::string, Spec> SpecMap;
typedef std::map<std::string, std::pair<uint32_t, std::string> > SetupMap;
typedef std::map<std::string, const Code *> DefaultMap;
typedef std::map<std::string, const RegExp *> symbol_table_t;

} // namespace re2c

#endif // _RE2C_PARSE_PARSER_
