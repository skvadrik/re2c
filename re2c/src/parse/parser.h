#ifndef _RE2C_PARSE_PARSER_
#define _RE2C_PARSE_PARSER_

#include <map>
#include <string>

#include "src/codegen/output.h"
#include "src/ir/regexp/regexp.h"
#include "src/parse/scanner.h"
#include "src/util/forbid_copy.h"
#include "src/util/smart_ptr.h"

namespace re2c
{

struct DFA;

void parse(Scanner &, Output &);

typedef std::set<std::string> CondList;
typedef std::vector<const RegExpRule*> Spec;
typedef std::map<std::string, Spec> SpecMap;
typedef std::map<std::string, const Code*> SetupMap;
typedef std::map<std::string, const RegExp *> symbol_table_t;
typedef std::map<std::string, smart_ptr<DFA> > dfa_map_t;

struct context_t
{
	std::vector<std::string> condnames;
	SpecMap specMap;
	Spec spec_all;
	SetupMap ruleSetupMap;
	const Code *startup;
	symbol_table_t symbol_table;

	context_t()
		: condnames()
		, specMap()
		, spec_all()
		, ruleSetupMap()
		, startup(NULL)
		, symbol_table()
	{}
	void clear()
	{
		condnames.clear();
		specMap.clear();
		spec_all.clear();
		startup = NULL;
		ruleSetupMap.clear();
		symbol_table.clear();
	}
	FORBID_COPY(context_t);
};

} // namespace re2c

#endif // _RE2C_PARSE_PARSER_
