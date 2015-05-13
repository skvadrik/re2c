/* $Id$ */
#ifndef _parser_h
#define _parser_h

#include "src/codegen/output.h"
#include "src/dfa/re.h"
#include "src/parse/scanner.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

class Symbol
{
public:

	RegExp*   re;

	static Symbol *find(const SubStr&);
	static void ClearTable();

	typedef std::map<std::string, Symbol*> SymbolTable;
	
	const Str& GetName() const
	{
		return name;
	}

protected:

	Symbol(const SubStr& str)
		: re(NULL)
		, name(str)
	{
	}

private:

	static SymbolTable symbol_table;

	Str	name;

	FORBID_COPY (Symbol);
};

extern void parse(Scanner &, Output &);
extern void parse_cleanup();

typedef std::set<std::string> CondList;
typedef std::list<RuleOp*> RuleOpList;
typedef std::map<std::string, std::pair<uint32_t, std::string> > SetupMap;
typedef std::map<std::string, Token*> DefaultMap;

} // end namespace re2c

#endif
