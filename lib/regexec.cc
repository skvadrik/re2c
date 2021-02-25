#include <stddef.h>

#include "lib/regex.h"
#include "lib/regex_impl.h"
#include "src/msg/location.h"


using namespace re2c;
using namespace re2c::libre2c;

int regexec(const regex_t *re, const char *string, size_t nmatch,
    regmatch_t pmatch[], int eflags)
{
    const int cflags = re->flags;
    if (!(cflags & REG_NFA)) {
        // DFA-based algorithms
        if (cflags & REG_STADFA) {
            return regexec_dfa<true>(re, string, nmatch, pmatch, eflags);
        } else {
            return regexec_dfa<false>(re, string, nmatch, pmatch, eflags);
        }
    } else {
        // NFA-based algorithms
        if (cflags & REG_LEFTMOST) {
            // Leftmost greedy disambiguation
            if (cflags & REG_TRIE) {
                return regexec_nfa_leftmost_trie(re, string, nmatch, pmatch, eflags);
            } else {
                return regexec_nfa_leftmost(re, string, nmatch, pmatch, eflags);
            }
        } else {
            // POSIX disambiguation
            if (cflags & REG_BACKWARD) {
                return regexec_nfa_posix_backward(re, string, nmatch, pmatch, eflags);
            } else if (cflags & REG_KUKLEWICZ) {
                return regexec_nfa_posix_kuklewicz(re, string, nmatch, pmatch, eflags);
            } else if (cflags & REG_TRIE) {
                return regexec_nfa_posix_trie(re, string, nmatch, pmatch, eflags);
            } else {
                return regexec_nfa_posix(re, string, nmatch, pmatch, eflags);
            }
        }
    }
}

