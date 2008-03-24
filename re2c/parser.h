/* $Id$ */
#ifndef _parser_h
#define _parser_h

#include "scanner.h"
#include "re.h"
#include <iosfwd>

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

#if PEDANTIC
	Symbol(const Symbol& oth)
		: re(oth.re)
		, name(oth.name)
	{
	}
	Symbol& operator = (const Symbol& oth)
	{
		new(this) Symbol(oth);
		return *this;
	}
#endif
};

extern void parse(Scanner&, std::ostream&, std::ostream*);
extern void parse_cleanup();

} // end namespace re2c

#endif
