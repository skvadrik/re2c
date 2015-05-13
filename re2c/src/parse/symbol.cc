#include "src/parse/symbol.h"

namespace re2c
{

Symbol::SymbolTable Symbol::symbol_table;

void Symbol::ClearTable ()
{
	for (SymbolTable::iterator it = symbol_table.begin(); it != symbol_table.end(); ++it)
	{
		delete it->second;
	}
	symbol_table.clear ();
}

Symbol * Symbol::find (const SubStr & str)
{
	const std::string ss (str.to_string ());
	SymbolTable::const_iterator it = symbol_table.find (ss);
	if (it == symbol_table.end ())
	{
		return (* symbol_table.insert (SymbolTable::value_type (ss, new Symbol (str))).first).second;
	}
	return (* it).second;
}

} // namespace re2c

