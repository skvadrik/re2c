#ifndef _RE2C_CODEGEN_SYNTAX_
#define _RE2C_CODEGEN_SYNTAX_

#include <iosfwd>
#include <stdint.h>
#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "src/constants.h"
#include "src/msg/location.h"
#include "src/msg/msg.h"
#include "src/util/allocator.h"
#include "src/util/check.h"
#include "src/util/containers.h"
#include "src/util/forbid_copy.h"

namespace re2c {

class RenderCallback;
struct StxCode;
struct opt_t;

// configuration-local variables in syntax files
#define RE2C_STX_LOCAL_VARS \
    STX_LOCAL_VAR(ARG, "arg") \
    STX_LOCAL_VAR(ARGMODS, "argmods") \
    STX_LOCAL_VAR(ARGNAME, "argname") \
    STX_LOCAL_VAR(ARGTYPE, "argtype") \
    STX_LOCAL_VAR(ARRAY, "array") \
    STX_LOCAL_VAR(BACKUP, "backup") \
    STX_LOCAL_VAR(BRANCH, "branch") \
    STX_LOCAL_VAR(CASE, "case") \
    STX_LOCAL_VAR(CHAR, "char") \
    STX_LOCAL_VAR(COND, "cond") \
    STX_LOCAL_VAR(CTYPE, "ctype") \
    STX_LOCAL_VAR(CURSOR, "cursor") \
    STX_LOCAL_VAR(DATE, "date") \
    STX_LOCAL_VAR(DEBUG, "debug") \
    STX_LOCAL_VAR(ELEM, "elem") \
    STX_LOCAL_VAR(EXPR, "expr") \
    STX_LOCAL_VAR(FN, "fn") \
    STX_LOCAL_VAR(FILE, "file") \
    STX_LOCAL_VAR(FNDECL, "fndecl") \
    STX_LOCAL_VAR(FNDEF, "fndef") \
    STX_LOCAL_VAR(INDEX, "index") \
    STX_LOCAL_VAR(INIT, "init") \
    STX_LOCAL_VAR(LABEL, "label") \
    STX_LOCAL_VAR(LHS, "lhs") \
    STX_LOCAL_VAR(LINE, "line") \
    STX_LOCAL_VAR(MARKER, "marker") \
    STX_LOCAL_VAR(NAME, "name") \
    STX_LOCAL_VAR(NUM, "num") \
    STX_LOCAL_VAR(OP, "op") \
    STX_LOCAL_VAR(PEEK, "peek") \
    STX_LOCAL_VAR(RETVAL, "retval") \
    STX_LOCAL_VAR(RHS, "rhs") \
    STX_LOCAL_VAR(ROW, "row") \
    STX_LOCAL_VAR(SIZE, "size") \
    STX_LOCAL_VAR(SKIP, "skip") \
    STX_LOCAL_VAR(STATE, "state") \
    STX_LOCAL_VAR(STMT, "stmt") \
    STX_LOCAL_VAR(TYPE, "type") \
    STX_LOCAL_VAR(TYPECAST, "typecast") \
    STX_LOCAL_VAR(VAL, "val") \
    STX_LOCAL_VAR(VAR, "var") \
    STX_LOCAL_VAR(VER, "version")

// global variables in syntax files
#define RE2C_STX_GLOBAL_VARS \
    STX_GLOBAL_VAR(NEWLINE, "nl") \
    STX_GLOBAL_VAR(INDENT, "indent") \
    STX_GLOBAL_VAR(DEDENT, "dedent") \
    STX_GLOBAL_VAR(TOPINDENT, "topindent")

#define STX_LOCAL_VAR(id, name) id,
#define STX_GLOBAL_VAR(id, name) id,
enum class StxVarId : uint32_t {
    RE2C_STX_LOCAL_VARS
    RE2C_STX_GLOBAL_VARS
};
#undef STX_LOCAL_VAR
#undef STX_GLOBAL_VAR

using StxCodes = list_t<StxCode>;

struct StxOpt {
    bool is_local;
    union {
        StxGOpt gopt;
        StxLOpt lopt;
    };
};

struct StxCodeCond {
    StxOpt* opt;
    StxCodes* then_code;
    StxCodes* else_code;
};

struct StxCodeList {
    StxVarId var;
    int32_t lbound;
    int32_t rbound;
    StxCodes* code;
};

enum class StxCodeType {STR, VAR, COND, LIST};

struct StxCode {
    StxCodeType type;
    union {
        const char* str;
        StxVarId var;
        StxCodeCond cond;
        StxCodeList list;
    };
    StxCode* next;
};

class Stx {
    using stack_code_t = std::vector<std::pair<const StxCode*, uint8_t>>;
    using stack_code_list_t = std::vector<const StxCode*>;

    constexpr static const char* DEFAULT_EMPTY = ""; // default value for undefined configurations

  public:
    OutAllocator& alc;

  private:
    // stacks are placed here to avoid reallocating them every time
    // (they can be mutated when evaluating configurations in a constant syntax object)
    mutable stack_code_t stack_code;
    mutable stack_code_list_t stack_code_list;

    static const char* var_name(StxVarId id);

    StxCode* make_code(StxCodeType type);

    Ret check_cond(StxLOpt opt, const char* conf, const std::unordered_set<StxLOpt>& conds) const;
    Ret check_var(StxVarId var, const char* conf, const std::unordered_set<StxVarId>& vars,
        const std::unordered_set<StxVarId>& list_vars) const;

    void push_list_on_stack(const StxCode* x) const;

  public:
    explicit Stx(OutAllocator& alc);

    // functions that construct AST when parsing syntax configurations
    StxCodes* new_code_list();
    StxCode* make_code_str(const char* str);
    StxCode* make_code_var(StxVarId id);
    StxCode* make_code_cond(StxOpt* opt, StxCodes* code_then, StxCodes* code_else);
    StxCode* make_code_list(StxVarId var, int32_t lbound, int32_t rbound, StxCodes* code);
    StxOpt* make_opt_global(StxGOpt opt);
    StxOpt* make_opt_local(StxLOpt opt);

    // functions that validate configuration and variable names in the AST
    Ret validate_conf_code(
        const StxCodes* code,
        const char* conf,
        const std::unordered_set<StxVarId>& vars,
        const std::unordered_set<StxVarId>& list_vars,
        const std::unordered_set<StxLOpt>& conds) const;

    // functions that check or evaluate configurations
    void eval_code_conf(const StxCodes* code, std::ostream& os, const opt_t* opts) const;
    void eval_code_conf(
        const StxCodes* code, std::ostream& os, const opt_t* opts, RenderCallback& callback) const;

    friend class opt_t;
};

} // namespace re2c

#endif // _RE2C_CODEGEN_SYNTAX_
