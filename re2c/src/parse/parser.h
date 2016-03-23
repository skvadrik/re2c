#ifndef _RE2C_PARSE_PARSER_
#define _RE2C_PARSE_PARSER_

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
const RegExp *make_rule(std::vector<CtxVar> &contexts, const Loc &loc,
	std::pair<std::vector<const RegExp*>, std::vector<std::string*> > *ctxs,
	rule_rank_t rank, const Code *code, const std::string *newcond);
const RegExp *make_rule_ctxfree(const Loc &loc, const RegExp *re,
	rule_rank_t rank, const Code *code, const std::string *newcond);
const RegExp *make_rule_copy(const RegExp *re, rule_rank_t rank, size_t shift);

typedef std::set<std::string> CondList;
typedef std::map<std::string, Spec> SpecMap;
typedef std::map<std::string, std::pair<uint32_t, std::string> > SetupMap;
typedef std::map<std::string, const Code *> DefaultMap;
typedef std::map<std::string, const RegExp *> symbol_table_t;
typedef std::pair<std::vector<const RegExp*>, std::vector<std::string*> > zzz_t;

} // namespace re2c

#endif // _RE2C_PARSE_PARSER_
