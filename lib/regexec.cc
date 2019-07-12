#include <stddef.h>

#include "lib/regex.h"
#include "lib/regex_impl.h"
#include "src/msg/location.h"


using namespace re2c;
using namespace re2c::libre2c;

int regexec(const regex_t *preg, const char *string, size_t nmatch,
    regmatch_t pmatch[], int eflags)
{
    if (!(preg->flags & REG_NFA)) {
        return regexec_dfa(preg, string, nmatch, pmatch, eflags);
    }
    else if ((preg->flags & REG_LEFTMOST) && (preg->flags & REG_TRIE)) {
        return regexec_nfa_leftmost_trie(preg, string, nmatch, pmatch, eflags);
    }
    else if (preg->flags & REG_LEFTMOST) {
        return regexec_nfa_leftmost(preg, string, nmatch, pmatch, eflags);
    }
    else if (preg->flags & REG_BACKWARD) {
        return regexec_nfa_posix_backward(preg, string, nmatch, pmatch, eflags);
    }
    else if (preg->flags & REG_KUKLEWICZ) {
        return regexec_nfa_posix_kuklewicz(preg, string, nmatch, pmatch, eflags);
    }
    else if (preg->flags & REG_TRIE) {
        return regexec_nfa_posix_trie(preg, string, nmatch, pmatch, eflags);
    }
    else {
        return regexec_nfa_posix(preg, string, nmatch, pmatch, eflags);
    }
}

