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
	static Symbol	*first;
	Symbol	*next;
	Str	name;
	RegExp	*re;

public:
	Symbol(const SubStr&);
	static Symbol *find(const SubStr&);
};

void line_source(unsigned int, std::ostream&);
void parse(std::istream&, std::ostream&);

} // end namespace re2c

#endif
