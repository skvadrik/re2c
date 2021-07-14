#ifndef _RE2C_CONSTANTS_
#define _RE2C_CONSTANTS_

#include "src/util/c99_stdint.h"


namespace re2c {

enum target_t {
    TARGET_CODE,
    TARGET_DOT,
    TARGET_SKELETON
};

enum lang_t {
    LANG_C,
    LANG_GO
};

enum input_api_t {
    INPUT_DEFAULT,
    INPUT_CUSTOM
};

enum api_style_t {
    API_FUNCTIONS,
    API_FREEFORM
};

enum fixed_tags_t {
    FIXTAG_NONE,
    FIXTAG_TOPLEVEL,
    FIXTAG_ALL
};

enum parse_opts_t {
    OK,
    EXIT_OK,
    EXIT_FAIL
};

enum InputBlockKind {
    INPUT_END,
    INPUT_GLOBAL,
    INPUT_LOCAL,
    INPUT_USE,
    INPUT_RULES,
    INPUT_ERROR
};

enum MaxDirectiveKind {
    MAX_FILL,
    MAX_NMATCH
};

enum empty_class_policy_t {
    EMPTY_CLASS_MATCH_EMPTY, // match on empty input
    EMPTY_CLASS_MATCH_NONE,  // fail to match on any input
    EMPTY_CLASS_ERROR        // compilation error
};

enum dfa_minimization_t {
    DFA_MINIMIZATION_TABLE,
    DFA_MINIMIZATION_MOORE
};

enum posix_closure_t {
    POSIX_CLOSURE_GOR1,
    POSIX_CLOSURE_GTOP
};

enum posix_prectable_alg_t {
    POSIX_PRECTABLE_NAIVE,
    POSIX_PRECTABLE_COMPLEX
};

const uint32_t NOEOF = ~0u - 1;

} // namespace re2c

#endif // _RE2C_CONSTANTS_
