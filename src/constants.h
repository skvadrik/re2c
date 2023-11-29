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

enum class InputBlock: uint32_t {
    END,
    GLOBAL,
    LOCAL,
    USE,
    RULES
};

enum class EmptyClass: uint32_t {
    MATCH_EMPTY, // match on empty input
    MATCH_NONE,  // fail to match on any input
    ERROR        // compilation error
};

enum class Minimization: uint32_t {
    TABLE,
    MOORE
};

// Whether a group is capturing or non-capturng depending on --invert-capture option and
// `re2c:invert_captures` configuration.
enum CaptureMode : uint8_t {
    NO_CAPTURE              = 0, // 00
    CAPTURE_IF_INVERTED     = 1, // 01
    CAPTURE_IF_NOT_INVERTED = 2, // 10
    CAPTURE                 = CAPTURE_IF_INVERTED | CAPTURE_IF_NOT_INVERTED
};

// Algorithm for construction of POSIX precedence table for disambiguation.
// Complexity estimates are in terms of TNFA size (m) and the number of tags (t).
enum class PosixPrectable: uint32_t {
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
    STATE_GOTO,
    STAGS,
    MTAGS,
    MAXFILL,
    MAXNMATCH,
    VAR,
    STMT,
    LOOP,
    TEXT,
    TEXT_RAW,
    RAW,
    DFAS,
    LABEL,
    ABORT,
    TABLE
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

static constexpr uint32_t NOEOF = ~0u - 1;

static constexpr size_t MAX_NFA_DEPTH  = 1000 * 1000;
static constexpr size_t MAX_NFA_STATES = 1000 * 1000 * 100;
static constexpr size_t MAX_DFA_STATES = 1000 * 100;
static constexpr size_t MAX_DFA_SIZE   = 1000 * 1000 * 50;

enum class Ret: uint32_t {
    OK,   // all good
    EXIT, // all good, but exit immediately (used for options like help or version)
    FAIL  // failure
};

#define CHECK_RET(x) do { Ret ret = x; if (ret != Ret::OK) return ret; } while(0)
#define RET_FAIL(x)  do { x; return Ret::FAIL; } while(0)

} // namespace re2c

#endif // _RE2C_CONSTANTS_
