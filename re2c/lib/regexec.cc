#include "lib/regex.h"
#include "lib/regex_impl.h"


using namespace re2c;

int regexec(const regex_t *preg, const char *string, size_t nmatch,
    regmatch_t pmatch[], int eflags)
{
    if (preg->flags & REG_NFA) {
        if (preg->flags & REG_LEFTMOST) {
            return regexec_nfa_leftmost(preg, string, nmatch, pmatch, eflags);
        }
        else {
            return regexec_nfa_posix(preg, string, nmatch, pmatch, eflags);
        }
    }
    else {
        return regexec_dfa(preg, string, nmatch, pmatch, eflags);
    }
}

