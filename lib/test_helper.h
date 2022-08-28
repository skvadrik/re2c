#ifndef _RE2C_LIB_TEST_HELPER_
#define _RE2C_LIB_TEST_HELPER_

#include <vector>
#include "lib/regex.h"

// Parse test submatch result string.
//
// Expected format: comma-separated lists of offset pairs in parentheses, each list contains as many
// pairs as there are repetitions for the corresponding capturing group.
//
// Example for regexp "(a(b)?)*" and string "aba": "(0,3),(0,2)(2,3),(1,2)(?,?)".
//
// String representation of result is used instead of vectors and initializer lists because C++
// compilers take too long to process that many vectors, and the compilation gets very slow.
//
bool parse_submatch(const char* s, std::vector<std::vector<regoff_t> >& result);

#endif // _RE2C_LIB_TEST_HELPER_
