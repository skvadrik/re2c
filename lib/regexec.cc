#include <stddef.h>

#include "lib/regex.h"
#include "lib/regex_impl.h"
#include "src/msg/location.h"

using namespace re2c;
using namespace re2c::libre2c;

int regexec(const regex_t* re, const char* string, size_t nmatch, regmatch_t pmatch[], int eflags) {
    const int cflags = re->flags;
    if (!(cflags & REG_NFA)) {
        // DFA-based algorithms
        if (cflags & REG_MULTIPASS) {
            // Multi-pass TDFA.
            if (cflags & REG_LEFTMOST) {
                return regexec_dfa_multipass<ldetctx_t>(re, string, nmatch, pmatch, eflags);
            } else {
                return regexec_dfa_multipass<pdetctx_t>(re, string, nmatch, pmatch, eflags);
            }
        } else {
            // TDFA with registers and register operations on transitions.
            return regexec_dfa(re, string, nmatch, pmatch, eflags);
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
            if (cflags & REG_TRIE) {
                return regexec_nfa_posix_trie(re, string, nmatch, pmatch, eflags);
            } else {
                return regexec_nfa_posix(re, string, nmatch, pmatch, eflags);
            }
        }
    }
}

subhistory_t* regparse(const regex_t* re, const char* string, size_t nmatch) {
    const int cflags = re->flags;
    CHECK(cflags & REG_SUBHIST);
    if (!(cflags & REG_NFA)) {
        // DFA-based algorithms
        if (cflags & REG_MULTIPASS) {
            // Multi-pass TDFA.
            if (cflags & REG_LEFTMOST) {
                return regparse_dfa_multipass<ldetctx_t>(re, string, nmatch);
            } else {
                return regparse_dfa_multipass<pdetctx_t>(re, string, nmatch);
            }
        } else {
            // TDFA with registers and register operations on transitions.
            return regparse_dfa(re, string, nmatch);
        }
    } else {
        // NFA-based algorithms (not implemented yet).
        UNREACHABLE();
        return nullptr;
    }
}

const tstring_t* regtstring(const regex_t* re, const char* string) {
    const int cflags = re->flags;
    CHECK(cflags & REG_TSTRING);
    if (!(cflags & REG_NFA)) {
        // DFA-based algorithms
        if (cflags & REG_MULTIPASS) {
            // Multi-pass TDFA.
            if (cflags & REG_LEFTMOST) {
                return regtstring_dfa_multipass<ldetctx_t>(re, string);
            } else {
                return regtstring_dfa_multipass<pdetctx_t>(re, string);
            }
        } else {
            // TDFA with registers is not suited to tstring construction.
            UNREACHABLE();
            return nullptr;
        }
    } else {
        // NFA-based algorithms (not implemented yet).
        UNREACHABLE();
        return nullptr;
    }
}
