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
    D,
    GO,
    HASKELL,
    JAVA,
    JS,
    OCAML,
    PYTHON,
    RUST,
    V,
    ZIG,
    NONE // no language (no default syntax config will be loaded)
};

enum class Api: uint32_t {
    SIMPLE,
    GENERIC,
    RECORD
};

enum class ApiStyle: uint32_t {
    FUNCTIONS,
    FREEFORM
};

enum class CodeModel: uint32_t {
    GOTO_LABEL,
    LOOP_SWITCH,
    REC_FUNC
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
    FNDEF,
    FNCALL,
    SKIP,
    PEEK,
    BACKUP,
    BACKUPCTX,
    RESTORE,
    RESTORECTX,
    RESTORETAG,
    PEEK_SKIP,
    SKIP_PEEK,
    SKIP_BACKUP,
    BACKUP_SKIP,
    BACKUP_PEEK,
    BACKUP_PEEK_SKIP,
    SKIP_BACKUP_PEEK,
    SETACCEPT,
    SETCOND,
    SETSTATE,
    LINE_INFO_INPUT,
    LINE_INFO_OUTPUT,
    FINGERPRINT,
    COND_ENUM,
    SHIFT,
    SHIFTSTAG,
    SHIFTMTAG,
    STAGP,
    STAGN,
    MTAGP,
    MTAGN,
    COPYSTAG,
    COPYMTAG,
    STATE_GOTO,
    STAGS,
    MTAGS,
    SVARS,
    MVARS,
    MAXFILL,
    MAXNMATCH,
    VAR,
    CONST,
    ARRAY,
    ENUM,
    STMT,
    GOTO,
    CONTINUE,
    LOOP,
    TEXT,
    TEXT_RAW,
    RAW,
    DFAS,
    LABEL,
    ABORT,
    DEBUG,
    REC_FUNCS,
    ASSIGN
};

// Types of variables in codegen (independent of the language language).
enum class VarType: uint32_t {
    INT,
    UINT,
    YYCTYPE
};

// Bit flags for configurations used in re2c blocks.
enum DirConf: uint32_t {
    DCONF_FORMAT    = 1u,
    DCONF_SEPARATOR = 2u
};

enum class CharLit {
    CHAR,
    HEX,
    CHAR_OR_HEX
};

enum OpKind { // used as array indices => not a `enum class`
    OP_CMP_EQ,
    OP_CMP_NE,
    OP_CMP_GT,
    OP_CMP_LT,
    OP_CMP_GE,
    OP_CMP_LE,
    OP_COUNT // number of elements
};

static constexpr uint32_t NOEOF = ~0u - 1;

static constexpr size_t MAX_NFA_DEPTH  = 1000 * 1000;
static constexpr size_t MAX_NFA_STATES = 1000 * 1000 * 100;
static constexpr size_t MAX_DFA_STATES = 1000 * 100;
static constexpr size_t MAX_DFA_SIZE   = 1000 * 1000 * 50;

enum class StxGOpt {
    API_SIMPLE,
    API_GENERIC,
    API_RECORD,
    API_STYLE_FUNCTIONS,
    API_STYLE_FREEFORM,
    CODE_MODEL_GOTO_LABEL,
    CODE_MODEL_LOOP_SWITCH,
    CODE_MODEL_REC_FUNC,
    START_CONDITIONS,
    STORABLE_STATE,
    DATE,
    VER,
    CASE_RANGES,
    UNSAFE,
    MONADIC,
    LOOP_LABEL
};

enum class StxLOpt {
    CAST,
    CHAR_LITERALS,
    ARGS,
    COND,
    INIT,
    TYPE,
    RETVAL,
    MANY,
    NESTED
};

enum class Ret: uint32_t {
    OK,   // all good
    EXIT, // all good, but exit immediately (used for options like help or version)
    FAIL  // failure
};

#define CHECK_RET(x) do { Ret ret = x; if (ret != Ret::OK) return ret; } while(0)
#define RET_FAIL(x)  do { x; return Ret::FAIL; } while(0)

} // namespace re2c

#endif // _RE2C_CONSTANTS_
