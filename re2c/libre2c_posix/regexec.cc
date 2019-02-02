#include "libre2c_posix/regex.h"
#include "libre2c_posix/regex_impl.h"


using namespace re2c;

int regexec(const regex_t *preg, const char *string, size_t nmatch,
    regmatch_t pmatch[], int eflags)
{
    return (preg->flags & REG_NFA)
        ? regexec_nfa(preg, string, nmatch, pmatch, eflags)
        : regexec_dfa(preg, string, nmatch, pmatch, eflags);
}

