#ifndef _RE2C_UTIL_STRING_UTILS_
#define _RE2C_UTIL_STRING_UTILS_

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

template<typename T>
static std::string to_string(const T &v)
{
	std::ostringstream s;
	s << v;
	return s.str();
}

} // namespace re2c

#endif // _RE2C_UTIL_STRING_UTILS_
