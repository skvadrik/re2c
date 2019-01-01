#ifndef _RE2C_UTIL_DEBUG_
#define _RE2C_UTIL_DEBUG_

#ifdef RE2C_DEBUG

#include <assert.h>

#define DEBUG(x)   x
#define DASSERT(x) assert(x)

#else // RE2C_DEBUG

#define DEBUG(x)
#define DASSERT(x)

#endif // RE2C_DEBUG

#endif // _RE2C_UTIL_DEBUG_
