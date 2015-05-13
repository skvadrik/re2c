#ifndef __SYMBOL__
#define __SYMBOL__

#include <map>
#include <string>

#include "src/util/forbid_copy.h"
#include "src/util/substr.h"

namespace re2c
{

class RegExp;

class Symbol
{
	typedef std::map<std::string, Symbol *> SymbolTable;

	static SymbolTable symbol_table;
	Str name;

	Symbol(const SubStr & str)
		: name (str)
		, re (NULL)
	{}

public:
	RegExp * re;

	static Symbol * find (const SubStr &);
	static void ClearTable ();
	const Str & GetName () const
	{
		return name;
	}

	FORBID_COPY (Symbol);
};

} // namespace re2c

#endif // __SYMBOL__
