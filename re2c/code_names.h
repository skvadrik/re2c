/* $Id: token.h 547 2006-05-25 13:40:35Z helly $ */
#ifndef _code_names_h
#define	_code_names_h

#include <string>
#include <map>

namespace re2c
{

class CodeNames: public std::map<std::string, std::string>
{
public:
	std::string& operator [] (const char * what);
};

} // end namespace re2c

#endif
