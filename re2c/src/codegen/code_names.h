#ifndef _RE2C_CODEGEN_CODE_NAMES_
#define _RE2C_CODEGEN_CODE_NAMES_

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

#endif // _RE2C_CODEGEN_CODE_NAMES_
