#ifndef _RE2C_CODEGEN_SYNTAX_
#define _RE2C_CODEGEN_SYNTAX_

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

struct StxExpr;

struct StxVar {
    const char* name;
    int32_t index; // nonnegative for list elements, -1 for standalone variables
};

struct StxCond {
    const char* conf; // condition is based on the value of this config
    StxExprList* then_expr;
    StxExprList* else_expr;
};

struct StxList {
    const char* var;
    int32_t lbound;
    int32_t rbound;
    StxExprList* expr;
};

enum class StxExprType {STR, VAR, COND, LIST};

struct StxExpr {
    StxExprType type;
    union {
        const char* str;
        StxVar var;
        StxCond cond;
        StxList list;
    };
    StxExpr* next;
};

using StxExprList = list_t<StxExpr>;

enum class StxBoolType {NUM, COND};

struct StxBool {
    StxBoolType type;
    union {
        int32_t num;
        struct {
            const char* conf;
            StxBool* then_bool;
            StxBool* else_bool;
        } cond;
    };
};

enum class StxConfType {BOOL, EXPR};

struct StxConf {
    const char* name;
    StxConfType type;
    union {
        StxBool* bln;
        StxExprList* expr;
    };
};

using confs_t = std::unordered_map<std::string, StxConf*>;

class Stx {
    struct allowed_conf_t {
        std::vector<std::string> vars;
        std::vector<std::string> list_vars;
        std::vector<std::string> cond_vars;

        allowed_conf_t(): vars(), list_vars(), cond_vars() {}
        allowed_conf_t(
            const std::vector<std::string>& vars,
            const std::vector<std::string>& list_vars,
            const std::vector<std::string>& cond_vars)
                : vars(vars), list_vars(list_vars), cond_vars(cond_vars) {}
    };

    using allowed_confs_t = std::unordered_map<std::string, allowed_conf_t>;
    using selector_t = std::function<bool(const opt_t*)>;
    using allowed_conds_t = std::unordered_map<std::string, selector_t>;
    using allowed_vars_t = std::unordered_set<std::string>;
    using stack1_t = std::vector<std::pair<const StxBool*, uint8_t>>;
    using stack2_t = std::vector<std::pair<const StxExpr*, uint8_t>>;

    OutAllocator& alc;
    allowed_confs_t allowed_confs;
    allowed_conds_t allowed_conds;
    allowed_vars_t allowed_vars;
    stack1_t stack1;
    stack2_t stack2;

    StxConf* make_conf(StxConfType type, const char* name);
    StxBool* make_bool(StxBoolType type);
    StxExpr* make_expr(StxExprType type);

    Ret check_conf(const char* conf) const;
    Ret check_cond(const char* conf, const char* cond) const;
    Ret check_var(const char* conf, const char* var) const;
    Ret check_list_var(const char* conf, const char* var) const;

  public:
    confs_t confs;

    explicit Stx(OutAllocator& alc);

    // functions that construct AST when parsing syntax configurations
    StxExprList* new_expr_list();
    StxConf* make_conf_bool(const char* name, StxBool* bln);
    StxConf* make_conf_expr(const char* name, StxExprList* expr);
    StxBool* make_bool_num(int32_t num);
    StxBool* make_bool_cond(const char* conf, StxBool* then_bool, StxBool* else_bool);
    StxExpr* make_str(const char* str);
    StxExpr* make_var(const char* name, int32_t index);
    StxExpr* make_cond(const char* conf, StxExprList* expr_then, StxExprList* expr_else);
    StxExpr* make_list(const char* var, int32_t lbound, int32_t rbound, StxExprList* expr);

    // functions that validate configuration and variable names in the AST
    Ret validate_bool_conf(const StxConf* conf);
    Ret validate_expr_conf(const StxConf* conf);
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
    Ret read();
    Ret parse(Stx& stx);
    int lex_token(YYSTYPE* yylval);
    bool check_conf_name(const char* name) const;
    inline loc_t tok_loc() const;

    FORBID_COPY(StxFile);
};

inline StxExprList* Stx::new_expr_list() {
    return new_list<StxExpr, OutAllocator>(alc);
}

inline StxConf* Stx::make_conf(StxConfType type, const char* name) {
    StxConf* x = alc.alloct<StxConf>(1);
    x->type = type;
    x->name = name;
    return x;
}

inline StxConf* Stx::make_conf_bool(const char* name, StxBool* bln) {
    StxConf* x = make_conf(StxConfType::BOOL, name);
    x->bln = bln;
    return x;
}

inline StxConf* Stx::make_conf_expr(const char* name, StxExprList* expr) {
    StxConf* x = make_conf(StxConfType::EXPR, name);
    x->expr = expr;
    return x;
}

inline StxBool* Stx::make_bool(StxBoolType type) {
    StxBool* x = alc.alloct<StxBool>(1);
    x->type = type;
    return x;
}

inline StxBool* Stx::make_bool_num(int32_t num) {
    StxBool* x = make_bool(StxBoolType::NUM);
    x->num = num;
    return x;
}

inline StxBool* Stx::make_bool_cond(const char* conf, StxBool* then_bool, StxBool* else_bool) {
    StxBool* x = make_bool(StxBoolType::COND);
    x->cond.conf = conf;
    x->cond.then_bool = then_bool;
    x->cond.else_bool = else_bool;
    return x;
}

inline StxExpr* Stx::make_expr(StxExprType type) {
    StxExpr* x = alc.alloct<StxExpr>(1);
    x->type = type;
    x->next = nullptr;
    return x;
}

inline StxExpr* Stx::make_str(const char* str) {
    StxExpr* x = make_expr(StxExprType::STR);
    x->str = str;
    return x;
}

inline StxExpr* Stx::make_var(const char* name, int32_t index) {
    StxExpr* x = make_expr(StxExprType::VAR);
    x->var.name = name;
    x->var.index = index;
    return x;
}

inline StxExpr* Stx::make_cond(const char* conf, StxExprList* then_expr, StxExprList* else_expr) {
    StxExpr* x = make_expr(StxExprType::COND);
    x->cond.conf = conf;
    x->cond.then_expr = then_expr;
    x->cond.else_expr = else_expr;
    return x;
}

inline StxExpr* Stx::make_list(const char* var, int32_t lbound, int32_t rbound, StxExprList* expr) {
    StxExpr* x = make_expr(StxExprType::LIST);
    x->list.var = var;
    x->list.lbound = lbound;
    x->list.rbound = rbound;
    x->list.expr = expr;
    return x;
}

Ret load_syntax_config(const std::string& fname, Msg& msg, OutAllocator& alc, Stx& stx);

loc_t StxFile::tok_loc() const {
    DCHECK(pos <= tok);
    return {loc.line, static_cast<uint32_t>(tok - pos), loc.file};
}

} // namespace re2c

#endif // _RE2C_CODEGEN_SYNTAX_
