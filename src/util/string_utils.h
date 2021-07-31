#ifndef _RE2C_UTIL_STRING_UTILS_
#define _RE2C_UTIL_STRING_UTILS_

#include <string.h>
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

inline std::string getstr(const char *s, const char *e)
{
    return std::string(s, static_cast<size_t>(e - s));
}

inline std::string *newstr(const char *s, const char *e)
{
    return new std::string(s, static_cast<size_t>(e - s));
}

template<typename allocator_t>
inline const char *newcstr(const char *s, const char *e, allocator_t &alc)
{
    if (s == NULL) return NULL;
    const size_t n = static_cast<size_t>(e - s);
    char *p = alc.template alloct<char>(n + 1);
    memcpy(p, s, n);
    p[n] = 0;
    return p;
}

template<typename allocator_t>
inline const char *copystr(const std::string &s, allocator_t &alc)
{
    const size_t n = s.length() + 1;
    char *p = alc.template alloct<char>(n);
    memcpy(p, s.data(), n);
    return p;
}

} // namespace re2c

#endif // _RE2C_UTIL_STRING_UTILS_
