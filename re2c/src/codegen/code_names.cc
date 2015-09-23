#include "src/codegen/code_names.h"

namespace re2c
{

std::string CodeNames::operator [] (const char * what) const
{
	CodeNames::const_iterator it = find (what);
	return it == end ()
		? what
		: it->second;
}

} // end namespace re2c
