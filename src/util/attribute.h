#ifndef _RE2C_UTIL_ATTRIBUTE_
#define _RE2C_UTIL_ATTRIBUTE_

#ifdef __GNUC__

#define RE2C_ATTR(x) __attribute__(x)
#define NODISCARD    __attribute__((warn_unused_result))

#else // __GNUC__

#define RE2C_ATTR(x)
#define NODISCARD

#endif // __GNUC__

// reduce boilerplate on function prototypes (attributes are not allowed on function definition)
#define LOCAL_NODISCARD(f) static f NODISCARD; f

#endif // _RE2C_UTIL_ATTRIBUTE_
