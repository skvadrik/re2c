#ifndef _RE2C_LIB_REGEX_IMPL_
#define _RE2C_LIB_REGEX_IMPL_

#include "regex.h"
#include <stddef.h>


namespace re2c {

int regexec_dfa(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int eflags);
int regexec_nfa(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int eflags);

} // namespace re2c

#endif // _RE2C_LIB_REGEX_IMPL_
