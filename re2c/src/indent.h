#ifndef _indent_h
#define _indent_h

#include <string>

#include "src/globals.h"

namespace re2c
{

inline std::string indent (uint32_t ind)
{
	std::string str;

	while (!DFlag && ind-- > 0)
	{
		str += indString;
	}
	return str;
}

} // end namespace re2c

#endif // _indent_h
