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

	typedef std::map<std::string, Symbol*> SymbolTable;

protected:

	Symbol(const SubStr& str)
		: name(str)
		, re(NULL)
	{
	}

private:

	static SymbolTable symbol_table;

	Str	name;
};

void line_source(unsigned int, std::ostream&);
void parse(std::istream&, std::ostream&);

} // end namespace re2c

#endif
