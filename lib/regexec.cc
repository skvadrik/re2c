#include <assert.h>
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
        if (cflags & REG_REGLESS) {
            // Registerless TDFA.
            if (cflags & REG_LEFTMOST) {
                return regexec_dfa_regless<ldetctx_t>(re, string, nmatch, pmatch, eflags);
            } else {
                return regexec_dfa_regless<pdetctx_t>(re, string, nmatch, pmatch, eflags);
            }
        } else {
            // TDFA with registers and register operations on transitions.
            if (cflags & REG_STADFA) {
                return regexec_dfa<true>(re, string, nmatch, pmatch, eflags);
            } else {
                return regexec_dfa<false>(re, string, nmatch, pmatch, eflags);
            }
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

subhistory_t *regparse(const regex_t *re, const char *string, size_t nmatch)
{
    const int cflags = re->flags;
    assert(cflags & REG_SUBHIST);
    if (!(cflags & REG_NFA)) {
        // DFA-based algorithms
        if (cflags & REG_REGLESS) {
            // Registerless TDFA.
            if (cflags & REG_LEFTMOST) {
                return regparse_dfa_regless<ldetctx_t>(re, string, nmatch);
            } else {
                return regparse_dfa_regless<pdetctx_t>(re, string, nmatch);
            }
        } else {
            // TDFA with registers and register operations on transitions.
            if (cflags & REG_STADFA) {
                return regparse_dfa<true>(re, string, nmatch);
            } else {
                return regparse_dfa<false>(re, string, nmatch);
            }
        }
    } else {
        // NFA-based algorithms (not implemented yet).
        assert(false);
        return NULL;
    }
}

const tstring_t *regtstring(const regex_t *re, const char *string)
{
    const int cflags = re->flags;
    assert(cflags & REG_TSTRING);
    if (!(cflags & REG_NFA)) {
        // DFA-based algorithms
        if (cflags & REG_REGLESS) {
            // Registerless TDFA.
            if (cflags & REG_LEFTMOST) {
                return regtstring_dfa_regless<ldetctx_t>(re, string);
            } else {
                return regtstring_dfa_regless<pdetctx_t>(re, string);
            }
        } else {
            // TDFA with registers is not suited to tstring construction.
            assert(false);
            return NULL;
        }
    } else {
        // NFA-based algorithms (not implemented yet).
        assert(false);
        return NULL;
    }
}

