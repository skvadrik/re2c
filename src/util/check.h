#ifndef _RE2C_UTIL_CHECK_
#define _RE2C_UTIL_CHECK_

#include <stdio.h>
#include <stdlib.h>

#define CHECK(x) do { \
    if (!(x)) { \
        fprintf(stderr, "check failed: file \"%s\", line %d\n",  __FILE__, __LINE__); \
        exit(1); \
    } \
} while(0)

#define UNREACHABLE() CHECK(false)

#ifdef RE2C_DEBUG

#define DCHECK(x) CHECK(x)

#else // RE2C_DEBUG

/* In non-debug mode we still produce a statement and use 'x'
   to avoid complains about unused variables. */
#define DCHECK(x) do {} while (false && (x))

#endif // RE2C_DEBUG

#endif // _RE2C_UTIL_CHECK_
