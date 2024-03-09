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
struct StxWord;
struct opt_t;

// list of configurations in syntax files (not including `conf:*` ones that)
#define RE2C_STX_CONFS \
    /* list configurations */ \
    STX_CONF(API, "api") \
    STX_CONF(API_STYLE, "api_style") \
    STX_CONF(CODE_MODEL, "code_model") \
    STX_CONF(TARGET, "target") \
    /* word configurations */ \
    STX_CONF(COMPUTED_GOTO, "computed_goto") \
    STX_CONF(CASE_RANGES, "case_ranges") \
    STX_CONF(SEMICOLONS, "semicolons") \
    STX_CONF(IMPLICIT_BOOL_CONVERSION, "implicit_bool_conversion") \
    STX_CONF(BACKTICK_QUOTED_STRINGS, "backtick_quoted_strings") \
    STX_CONF(STANDALONE_SINGLE_QUOTES, "standalone_single_quotes") \
    /* code configurations */ \
    STX_CONF(VAR_LOCAL, "code:var_local") \
    STX_CONF(VAR_GLOBAL, "code:var_global") \
    STX_CONF(CONST_LOCAL, "code:const_local") \
    STX_CONF(CONST_GLOBAL, "code:const_global") \
    STX_CONF(ARRAY_LOCAL, "code:array_local") \
    STX_CONF(ARRAY_GLOBAL, "code:array_global") \
    STX_CONF(ARRAY_ELEM, "code:array_elem") \
    STX_CONF(TYPE_INT, "code:type_int") \
    STX_CONF(TYPE_UINT, "code:type_uint") \
    STX_CONF(TYPE_COND_ENUM, "code:type_cond_enum") \
    STX_CONF(TYPE_YYBM, "code:type_yybm") \
    STX_CONF(TYPE_YYTARGET, "code:type_yytarget") \
    STX_CONF(ASSIGN, "code:assign") \
    STX_CONF(ASSIGN_OP, "code:assign_op") \
    STX_CONF(IF_THEN_ELSE, "code:if_then_else") \
    STX_CONF(IF_THEN_ELSE_ONELINE, "code:if_then_else_oneline") \
    STX_CONF(SWITCH, "code:switch") \
    STX_CONF(SWITCH_CASES, "code:switch_cases") \
    STX_CONF(SWITCH_CASES_ONELINE, "code:switch_cases_oneline") \
    STX_CONF(SWITCH_CASE_RANGE, "code:switch_case_range") \
    STX_CONF(SWITCH_CASE_DEFAULT, "code:switch_case_default") \
    STX_CONF(LOOP, "code:loop") \
    STX_CONF(ENUM, "code:enum") \
    STX_CONF(ENUM_ELEM, "code:enum_elem") \
    STX_CONF(FNDECL, "code:fndecl") \
    STX_CONF(FNDEF, "code:fndef") \
    STX_CONF(FNCALL, "code:fncall") \
    STX_CONF(TAILCALL, "code:tailcall") \
    STX_CONF(RECURSIVE_FUNCTIONS, "code:recursive_functions") \
    STX_CONF(FINGERPRINT, "code:fingerprint") \
    STX_CONF(LINE_INFO, "code:line_info") \
    STX_CONF(ABORT, "code:abort") \
    STX_CONF(ACCEPT, "code:yyaccept") \
    STX_CONF(DEBUG, "code:yydebug") \
    STX_CONF(PEEK, "code:yypeek") \
    STX_CONF(SKIP, "code:yyskip") \
    STX_CONF(BACKUP, "code:yybackup") \
    STX_CONF(SKIP_PEEK, "code:yyskip_peek") \
    STX_CONF(PEEK_SKIP, "code:yypeek_skip") \
    STX_CONF(SKIP_BACKUP, "code:yyskip_backup") \
    STX_CONF(BACKUP_SKIP, "code:yybackup_skip") \
    STX_CONF(BACKUP_PEEK, "code:yybackup_peek") \
    STX_CONF(SKIP_BACKUP_PEEK, "code:yyskip_backup_peek") \
    STX_CONF(BACKUP_PEEK_SKIP, "code:yybackup_peek_skip")

#define STX_CONF(id, name) id,
enum class StxConfId : uint32_t {
    RE2C_STX_CONFS
};
#undef STX_CONF

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
using StxList = list_t<StxWord>;

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

struct StxWord {
    const char* word;
    StxWord* next;
};

enum class StxConfType {LIST, WORD, CODE};

struct StxConf {
    StxConfId id;
    StxConfType type;
    union {
        StxList* list;
        const char* word;
        StxCodes* code;
    };
};

class Stx {
    struct code_conf_t {
        std::vector<StxVarId> vars;
        std::vector<StxVarId> list_vars;
        std::vector<StxLOpt> cond_vars;

        code_conf_t(): vars(), list_vars(), cond_vars() {}
        code_conf_t(
            const std::vector<StxVarId>& vars,
            const std::vector<StxVarId>& list_vars,
            const std::vector<StxLOpt>& conds)
                : vars(vars), list_vars(list_vars), cond_vars(conds) {}
    };
    using allowed_code_confs_t = std::unordered_map<StxConfId, code_conf_t>;
    using allowed_list_confs_t = std::unordered_map<StxConfId, std::vector<std::string>>;
    using allowed_word_confs_t = std::unordered_map<StxConfId, std::vector<std::string>>;
    using selector_t = std::function<bool(const opt_t*)>;
    using allowed_vars_t = std::unordered_set<StxVarId>;
    using stack_code_t = std::vector<std::pair<const StxCode*, uint8_t>>;
    using stack_code_list_t = std::vector<const StxCode*>;
    using confs_t = std::unordered_map<StxConfId, const StxConf*>;

    constexpr static const char* DEFAULT_EMPTY = ""; // default value for undefined configurations

  public:
    OutAllocator& alc;

  private:
    allowed_list_confs_t allowed_list_confs;
    allowed_word_confs_t allowed_word_confs;
    allowed_code_confs_t allowed_code_confs;
    allowed_vars_t allowed_vars;

    confs_t confs;

    bool have_oneline_if;
    bool have_oneline_switch;

    // stacks are placed here to avoid reallocating them every time
    // (they can be mutated when evaluating configurations in a constant syntax object)
    mutable stack_code_t stack_code;
    mutable stack_code_list_t stack_code_list;

    StxConf* make_conf(StxConfType type, StxConfId id);
    StxCode* make_code(StxCodeType type);

    Ret check_cond(StxConfId id, StxLOpt opt) const;
    Ret check_word(StxConfId id, const char* word, bool list) const;
    Ret check_var(StxConfId id, StxVarId var) const;

    void push_list_on_stack(const StxCode* x) const;

  public:
    explicit Stx(OutAllocator& alc);

    // functions that construct AST when parsing syntax configurations
    StxCodes* new_code_list();
    StxList* new_word_list();
    StxConf* make_conf_code(StxConfId id, StxCodes* code);
    StxConf* make_conf_word(StxConfId id, const char* word);
    StxConf* make_conf_list(StxConfId id, StxList* list);
    StxCode* make_code_str(const char* str);
    StxCode* make_code_var(StxVarId id);
    StxCode* make_code_cond(StxOpt* opt, StxCodes* code_then, StxCodes* code_else);
    StxCode* make_code_list(StxVarId var, int32_t lbound, int32_t rbound, StxCodes* code);
    StxWord* make_word(const char* word);
    StxOpt* make_opt_global(StxGOpt opt);
    StxOpt* make_opt_local(StxLOpt opt);
    void add_conf(StxConfId id, const StxConf* conf);
    const StxConf* get_conf(StxConfId id);

    // functions that validate configuration and variable names in the AST
    Ret validate_conf_list(const StxConf* conf);
    Ret validate_conf_word(const StxConf* conf);
    Ret validate_conf_code(const StxConf* conf);

    static const char* conf_name(StxConfId id);
    static const char* var_name(StxVarId id);

    // functions related to configuration checks
    bool have_conf(StxConfId id) const;
    void cache_conf_tests();

    // functions that check or evaluate configurations
    const char* list_conf_head(StxConfId id) const;
    bool list_conf_find(StxConfId id, const char* elem) const;
    const char* eval_word_conf(StxConfId id) const;
    bool eval_bool_conf(StxConfId id) const;
    Ret eval_str_conf(StxConfId id, std::string& str) const;
    void eval_code_conf(std::ostream& os, const opt_t* opts, StxConfId id) const;
    void eval_code_conf(
            std::ostream& os, const opt_t* opts, StxConfId id, RenderCallback& callback) const;

    friend class opt_t;
};

} // namespace re2c

#endif // _RE2C_CODEGEN_SYNTAX_
