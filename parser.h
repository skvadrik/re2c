/* $Id$ */
#ifndef _parser_h
#define _parser_h

#include "scanner.h"
#include "re.h"
#include <iosfwd>
#include <map>

namespace re2c
{

class Symbol
{
public:

	RegExp*   re;

	static Symbol *find(const SubStr&);
	static void ClearTable();

	~Symbol()
	{
		/** \todo should we delete 're'? */
	}

protected:

	Symbol(const SubStr& str)
		: name(str)
		, re(NULL)
	{
	}

private:

	typedef std::map<std::string, Symbol*> SymbolTable;

	static SymbolTable symbol_table;

	Str	name;
};

void line_source(unsigned int, std::ostream&);
void parse(std::istream&, std::ostream&);

} // end namespace re2c

#endif
