#ifndef _RE2C_UTIL_STRING_UTILS_
#define _RE2C_UTIL_STRING_UTILS_

#include <sstream>
#include <string>


namespace re2c {

template<typename type_t>
void strrreplace(std::string &s, const std::string &s1, const type_t &v)
{
    std::ostringstream sv;
    sv << v;
    const std::string &s2 = sv.str();
    const size_t l1 = s1.length(), l2 = s2.length();
    if (l1 != 0) {
        std::string::size_type pos = s.find(s1);
        while (pos != std::string::npos) {
            s.replace(pos, l1, s2);
            pos = s.find(s1, pos + l2);
        }
    }
}

template<typename T>
std::string to_string(const T &v)
{
    std::ostringstream s;
    s << v;
    return s.str();
}

// Yet another constructor of std::string, useful when the strings
// are constructed from fragments in buffer. A separate function is
// needed mainly to avoid static_cast's everywhere.
inline std::string getstr(const char *s, const char *e)
{
    return std::string(s, static_cast<size_t>(e - s));
}
inline std::string *newstr(const char *s, const char *e)
{
    return new std::string(s, static_cast<size_t>(e - s));
}

} // namespace re2c

#endif // _RE2C_UTIL_STRING_UTILS_
