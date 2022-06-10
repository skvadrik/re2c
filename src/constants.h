#ifndef _RE2C_CONSTANTS_
#define _RE2C_CONSTANTS_

#include <stddef.h>
#include <stdint.h>


namespace re2c {

enum class Target: uint32_t {
    CODE,
    DOT,
    SKELETON
};

enum class Lang: uint32_t {
    C,
    GO,
    RUST
};

enum class Api: uint32_t {
    DEFAULT,
    CUSTOM
};

enum class ApiStyle: uint32_t {
    FUNCTIONS,
    FREEFORM
};

enum class FixedTags: uint32_t {
    NONE,
    TOPLEVEL,
    ALL
};

enum class ParseOpts: uint32_t {
    OK,
    EXIT_OK,
    EXIT_FAIL
};

enum class InputBlock: uint32_t {
    END,
    GLOBAL,
    LOCAL,
    USE,
    RULES,
    ERROR
};

enum class EmptyClassPolicy: uint32_t {
    MATCH_EMPTY, // match on empty input
    MATCH_NONE,  // fail to match on any input
    ERROR        // compilation error
};

enum class Minimization: uint32_t {
    TABLE,
    MOORE
};

// Shortest path algorithm used in construction of POSIX epsilon-closure.
enum class PosixClosure: uint32_t {
    GOR1, // Goldberg-Radzik
    GTOP  // global topological order
};

// Algorithm for construction of POSIX precedence table for disambiguation.
// Complexity estimates are in terms of TNFA size (m) and the number of tags (t).
enum class PosixPrecedenceTable: uint32_t {
    NAIVE,  // O(m^2 * t)
    COMPLEX // O(m^2)
};

// Different kinds of statements / expressions / blocks / etc. used in codegen.
enum class CodeKind: uint32_t {
    EMPTY,
    IF_THEN_ELSE,
    SWITCH,
    BLOCK,
    FUNC,
    SKIP,
    PEEK,
    BACKUP,
    PEEK_SKIP,
    SKIP_PEEK,
    SKIP_BACKUP,
    BACKUP_SKIP,
    BACKUP_PEEK,
    BACKUP_PEEK_SKIP,
    SKIP_BACKUP_PEEK,
    LINE_INFO_INPUT,
    LINE_INFO_OUTPUT,
    COND_ENUM,
    COND_GOTO,
    COND_TABLE,
    STATE_GOTO,
    STAGS,
    MTAGS,
    MAXFILL,
    MAXNMATCH,
    YYCH,
    YYACCEPT,
    YYSTATE,
    VAR,
    STMT,
    LOOP,
    TEXT,
    TEXT_RAW,
    RAW,
    LABEL,
    ABORT
};

// Types of variables in codegen (independent of the language language).
enum class VarType: uint32_t {
    INT,
    UINT,
    YYCTYPE
};

// Bit flags for configurations used in directives.
enum DirConf: uint32_t {
    DCONF_FORMAT    = 1u,
    DCONF_SEPARATOR = 2u
};

static const uint32_t NOEOF = ~0u - 1;

static const size_t MAX_NFA_DEPTH  = 1000 * 1000;
static const size_t MAX_NFA_STATES = 1000 * 1000 * 100;
static const size_t MAX_DFA_STATES = 1000 * 100;
static const size_t MAX_DFA_SIZE   = 1000 * 1000 * 50;

} // namespace re2c

#endif // _RE2C_CONSTANTS_
