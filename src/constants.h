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

enum CodeKind {
    CODE_EMPTY,
    CODE_IF_THEN_ELSE,
    CODE_SWITCH,
    CODE_BLOCK,
    CODE_FUNC,
    CODE_SKIP,
    CODE_PEEK,
    CODE_BACKUP,
    CODE_PEEK_SKIP,
    CODE_SKIP_PEEK,
    CODE_SKIP_BACKUP,
    CODE_BACKUP_SKIP,
    CODE_BACKUP_PEEK,
    CODE_BACKUP_PEEK_SKIP,
    CODE_SKIP_BACKUP_PEEK,
    CODE_LINE_INFO_INPUT,
    CODE_LINE_INFO_OUTPUT,
    CODE_COND_ENUM,
    CODE_COND_GOTO,
    CODE_COND_TABLE,
    CODE_STATE_GOTO,
    CODE_STAGS,
    CODE_MTAGS,
    CODE_MAXFILL,
    CODE_MAXNMATCH,
    CODE_YYCH,
    CODE_YYACCEPT,
    CODE_VAR,
    CODE_STMT,
    CODE_TEXT,
    CODE_TEXT_RAW,
    CODE_RAW,
    CODE_LABEL
};

// Bit flags for configurations used in directives.
enum DirConf {
    DCONF_FORMAT    = 1u,
    DCONF_SEPARATOR = 2u
};

const uint32_t NOEOF = ~0u - 1;

} // namespace re2c

#endif // _RE2C_CONSTANTS_
