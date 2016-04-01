#ifndef _RE2C_UTIL_STRRREPLACE_
#define _RE2C_UTIL_STRRREPLACE_

#include <sstream>
#include <string>

namespace re2c
{

template<typename type_t> void strrreplace(
	std::string &s,
	const std::string &s1,
	const type_t &v)
{
	std::ostringstream sv;
	sv << v;
	const std::string &s2 = sv.str();
	const size_t l = s1.length();
	if (l != 0) {
		std::string::size_type pos;
		while ((pos = s.find(s1)) != std::string::npos) {
			s.replace(pos, l, s2);
		}
	}
}

} // namespace re2c

#endif // _RE2C_UTIL_STRRREPLACE_
