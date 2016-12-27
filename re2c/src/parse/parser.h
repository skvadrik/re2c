#ifndef _RE2C_PARSE_PARSER_
#define _RE2C_PARSE_PARSER_

#include <map>
#include <string>

#include "src/codegen/output.h"
#include "src/ir/regexp/regexp.h"
#include "src/parse/scanner.h"
#include "src/util/smart_ptr.h"

namespace re2c
{

struct DFA;

void parse(Scanner &input, Output &output);

struct spec_t
{
	std::string name;
	std::vector<RegExpRule> rules;
	std::vector<const Code*> defs;
	std::vector<const Code*> setup;

	explicit spec_t(const std::string &n):
		name(n), rules(), defs(), setup() {}
};

typedef std::vector<spec_t> specs_t;
typedef std::set<std::string> CondList;
typedef std::map<std::string, const RegExp *> symtab_t;
typedef std::vector<smart_ptr<DFA> > dfas_t;

struct context_t
{
	Scanner &input;
	specs_t &specs;
	symtab_t &symtab;
};

} // namespace re2c

#endif // _RE2C_PARSE_PARSER_
