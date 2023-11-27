#ifndef _RE2C_CODEGEN_SYNTAX_
#define _RE2C_CODEGEN_SYNTAX_

#include <iosfwd>
#include <stdint.h>
#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "src/codegen/syntax_parser.h"
#include "src/constants.h"
#include "src/msg/location.h"
#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/util/allocator.h"
#include "src/util/check.h"
#include "src/util/containers.h"
#include "src/util/forbid_copy.h"

namespace re2c {

class OutputCallback;
struct StxCode;

struct StxCodeCond {
    const char* conf; // condition is based on the value of this config
    StxCodes* then_code;
    StxCodes* else_code;
};

struct StxCodeList {
    const char* var;
    int32_t lbound;
    int32_t rbound;
    StxCodes* code;
};

enum class StxCodeType {STR, VAR, COND, LIST};

struct StxCode {
    StxCodeType type;
    union {
        const char* str;
        const char* var;
        StxCodeCond cond;
        StxCodeList list;
    };
    StxCode* next;
};

enum class StxExprType {NAME, COND};

struct StxExpr {
    StxExprType type;
    union {
        const char* name;
        struct {
            const char* conf;
            StxExpr* then_expr;
            StxExpr* else_expr;
        } cond;
    };
};

struct StxName {
    const char* name;
    StxName* next;
};

enum class StxConfType {LIST, EXPR, CODE};

struct StxConf {
    const char* name;
    StxConfType type;
    union {
        StxList* list;
        StxExpr* expr;
        StxCodes* code;
    };
};

class Stx {
    struct code_conf_t {
        std::vector<std::string> vars;
        std::vector<std::string> list_vars;
        std::vector<std::string> cond_vars;

        code_conf_t(): vars(), list_vars(), cond_vars() {}
        code_conf_t(
            const std::vector<std::string>& vars,
            const std::vector<std::string>& list_vars,
            const std::vector<std::string>& cond_vars)
                : vars(vars), list_vars(list_vars), cond_vars(cond_vars) {}
    };
    using allowed_code_confs_t = std::unordered_map<std::string, code_conf_t>;
    using allowed_list_confs_t = std::unordered_map<std::string, std::vector<std::string>>;
    using allowed_word_confs_t = std::unordered_map<std::string, std::vector<std::string>>;
    using selector_t = std::function<bool(const opt_t*)>;
    using allowed_conds_t = std::unordered_map<std::string, selector_t>;
    using allowed_vars_t = std::unordered_set<std::string>;
    using stack_expr_t = std::vector<std::pair<const StxExpr*, uint8_t>>;
    using stack_code_t = std::vector<std::pair<const StxCode*, uint8_t>>;
    using stack_code_list_t = std::vector<const StxCode*>;
    using confs_t = std::unordered_map<std::string, const StxConf*>;

    OutAllocator& alc;
    allowed_list_confs_t allowed_list_confs;
    allowed_word_confs_t allowed_word_confs;
    allowed_code_confs_t allowed_code_confs;
    allowed_conds_t allowed_conds;
    allowed_vars_t allowed_vars;
    stack_expr_t stack_expr;
    stack_code_t stack_code;
    stack_code_list_t stack_code_list;
    confs_t confs;
    bool have_oneline_if;
    bool have_oneline_switch;

    StxConf* make_conf(StxConfType type, const char* name);
    StxCode* make_code(StxCodeType type);
    StxExpr* make_expr(StxExprType type);

    Ret check_cond(const char* conf, const char* cond, bool code) const;
    Ret check_word(const char* conf, const char* word, bool list) const;
    Ret check_var(const char* conf, const char* var) const;

    void push_list_on_stack(const StxCode* x);
    bool eval_cond(const char* cond, const opt_t* opts, OutputCallback& callback) const;

    bool have_conf(const char* name) const;

  public:
    explicit Stx(OutAllocator& alc);

    // functions that construct AST when parsing syntax configurations
    StxCodes* new_code_list();
    StxList* new_name_list();
    StxConf* make_conf_code(const char* name, StxCodes* code);
    StxConf* make_conf_expr(const char* name, StxExpr* expr);
    StxConf* make_conf_list(const char* name, StxList* list);
    StxExpr* make_expr_name(const char* name);
    StxExpr* make_expr_cond(const char* conf, StxExpr* then_expr, StxExpr* else_expr);
    StxCode* make_code_str(const char* str);
    StxCode* make_code_var(const char* name);
    StxCode* make_code_cond(const char* conf, StxCodes* code_then, StxCodes* code_else);
    StxCode* make_code_list(const char* var, int32_t lbound, int32_t rbound, StxCodes* code);
    StxName* make_name(const char* name);
    void add_conf(const char* name, const StxConf* conf);

    // functions that validate configuration and variable names in the AST
    Ret validate_conf_list(const StxConf* conf);
    Ret validate_conf_expr(const StxConf* conf);
    Ret validate_conf_code(const StxConf* conf);

    // functions that test for presence of specific configs (cached in class fields)
    bool specialize_oneline_if() const;
    bool specialize_oneline_switch() const;
    void cache_conf_tests();

    void gen_code(std::ostream& os, const opt_t* opts, const char* name, OutputCallback& callback);
};

class StxFile {
    OutAllocator& alc;
    const std::string& fname;
    FILE* file;
    size_t flen;
    uint8_t* buf;
    const uint8_t* cur; // current lexer position
    const uint8_t* tok; // token start
    const uint8_t* pos; // line start (used for error reporting)
    loc_t loc;

  public:
    Msg& msg;

  public:
    StxFile(const std::string& fname, Msg& msg, OutAllocator& alc);
    ~StxFile();
    Ret read(Lang lang);
    Ret parse(Stx& stx);
    int lex_token(YYSTYPE* yylval);
    bool check_conf_name(const char* name) const;
    inline loc_t tok_loc() const;

    FORBID_COPY(StxFile);
};

inline StxCodes* Stx::new_code_list() {
    return new_list<StxCode, OutAllocator>(alc);
}

inline StxList* Stx::new_name_list() {
    return new_list<StxName, OutAllocator>(alc);
}

inline StxConf* Stx::make_conf(StxConfType type, const char* name) {
    StxConf* x = alc.alloct<StxConf>(1);
    x->type = type;
    x->name = name;
    return x;
}

inline StxConf* Stx::make_conf_expr(const char* name, StxExpr* expr) {
    StxConf* x = make_conf(StxConfType::EXPR, name);
    x->expr = expr;
    return x;
}

inline StxConf* Stx::make_conf_list(const char* name, StxList* list) {
    StxConf* x = make_conf(StxConfType::LIST, name);
    x->list = list;
    return x;
}

inline StxConf* Stx::make_conf_code(const char* name, StxCodes* code) {
    StxConf* x = make_conf(StxConfType::CODE, name);
    x->code = code;
    return x;
}

inline StxName* Stx::make_name(const char* name) {
    StxName* x = alc.alloct<StxName>(1);
    x->name = name;
    x->next = nullptr;
    return x;
}

inline StxExpr* Stx::make_expr(StxExprType type) {
    StxExpr* x = alc.alloct<StxExpr>(1);
    x->type = type;
    return x;
}

inline StxExpr* Stx::make_expr_name(const char* name) {
    StxExpr* x = make_expr(StxExprType::NAME);
    x->name = name;
    return x;
}

inline StxExpr* Stx::make_expr_cond(const char* conf, StxExpr* then_expr, StxExpr* else_expr) {
    StxExpr* x = make_expr(StxExprType::COND);
    x->cond.conf = conf;
    x->cond.then_expr = then_expr;
    x->cond.else_expr = else_expr;
    return x;
}

inline StxCode* Stx::make_code(StxCodeType type) {
    StxCode* x = alc.alloct<StxCode>(1);
    x->type = type;
    x->next = nullptr;
    return x;
}

inline StxCode* Stx::make_code_str(const char* str) {
    StxCode* x = make_code(StxCodeType::STR);
    x->str = str;
    return x;
}

inline StxCode* Stx::make_code_var(const char* var) {
    StxCode* x = make_code(StxCodeType::VAR);
    x->var = var;
    return x;
}

inline StxCode* Stx::make_code_cond(const char* conf, StxCodes* then_code, StxCodes* else_code) {
    StxCode* x = make_code(StxCodeType::COND);
    x->cond.conf = conf;
    x->cond.then_code = then_code;
    x->cond.else_code = else_code;
    return x;
}

inline StxCode* Stx::make_code_list(
        const char* var, int32_t lbound, int32_t rbound, StxCodes* code) {
    StxCode* x = make_code(StxCodeType::LIST);
    x->list.var = var;
    x->list.lbound = lbound;
    x->list.rbound = rbound;
    x->list.code = code;;
    return x;
}

inline void Stx::add_conf(const char* name, const StxConf* conf) { confs[name] = conf; }

inline bool Stx::specialize_oneline_if() const { return have_oneline_if; }

inline bool Stx::specialize_oneline_switch() const { return have_oneline_switch; }

loc_t StxFile::tok_loc() const {
    DCHECK(pos <= tok);
    return {loc.line, static_cast<uint32_t>(tok - pos), loc.file};
}

Ret load_syntax_config(const std::string& fname, Msg& msg, OutAllocator& alc, Stx& stx, Lang lang);

} // namespace re2c

#endif // _RE2C_CODEGEN_SYNTAX_
