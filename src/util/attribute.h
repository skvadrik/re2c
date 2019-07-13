#ifndef _RE2C_UTIL_ATTRIBUTE_
#define _RE2C_UTIL_ATTRIBUTE_

#ifdef __GNUC__
#    define RE2C_ATTR(x) __attribute__(x)
#else
#    define RE2C_ATTR(x)
#endif

#endif // _RE2C_UTIL_ATTRIBUTE_
