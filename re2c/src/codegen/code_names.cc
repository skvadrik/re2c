#include "src/codegen/code_names.h"
#include "src/globals.h"

namespace re2c
{

std::string& CodeNames::operator [] (const char * what)
{
	CodeNames::iterator it = find(std::string(what));
	
	if (it == end())
	{
		return insert(std::make_pair(std::string(what), std::string(what))).first->second;
	}
	else
	{
		return it->second;
	}
}

} // end namespace re2c
