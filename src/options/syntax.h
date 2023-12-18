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
struct StxName;
struct opt_t;

using StxCodes = list_t<StxCode>;
using StxList = list_t<StxName>;

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

struct StxName {
    const char* name;
    StxName* next;
};

enum class StxConfType {LIST, WORD, CODE};

struct StxConf {
    const char* name;
    StxConfType type;
    union {
        StxList* list;
        const char* word;
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
    using stack_code_t = std::vector<std::pair<const StxCode*, uint8_t>>;
    using stack_code_list_t = std::vector<const StxCode*>;
    using confs_t = std::unordered_map<std::string, const StxConf*>;

    constexpr static const char* DEFAULT_EMPTY = ""; // default value for undefined configurations

  public:
    OutAllocator& alc;

  private:
    allowed_list_confs_t allowed_list_confs;
    allowed_word_confs_t allowed_word_confs;
    allowed_code_confs_t allowed_code_confs;
    allowed_conds_t allowed_conds;
    allowed_vars_t allowed_vars;

    confs_t confs;

    bool have_oneline_if;
    bool have_oneline_switch;

    // stacks are placed here to avoid reallocating them every time
    // (they can be mutated when evaluating configurations in a constant syntax object)
    mutable stack_code_t stack_code;
    mutable stack_code_list_t stack_code_list;

    StxConf* make_conf(StxConfType type, const char* name);
    StxCode* make_code(StxCodeType type);

    Ret check_cond(const char* conf, const char* cond, bool code) const;
    Ret check_word(const char* conf, const char* word, bool list) const;
    Ret check_var(const char* conf, const char* var) const;

    void push_list_on_stack(const StxCode* x) const;
    bool eval_cond(const char* cond, const opt_t* opts, RenderCallback* callback) const;

  public:
    explicit Stx(OutAllocator& alc);

    // functions that construct AST when parsing syntax configurations
    StxCodes* new_code_list();
    StxList* new_name_list();
    StxConf* make_conf_code(const char* name, StxCodes* code);
    StxConf* make_conf_word(const char* name, const char* word);
    StxConf* make_conf_list(const char* name, StxList* list);
    StxCode* make_code_str(const char* str);
    StxCode* make_code_var(const char* name);
    StxCode* make_code_cond(const char* conf, StxCodes* code_then, StxCodes* code_else);
    StxCode* make_code_list(const char* var, int32_t lbound, int32_t rbound, StxCodes* code);
    StxName* make_name(const char* name);
    void add_conf(const char* name, const StxConf* conf);

    // functions that validate configuration and variable names in the AST
    Ret validate_conf_list(const StxConf* conf);
    Ret validate_conf_word(const StxConf* conf);
    Ret validate_conf_code(const StxConf* conf);

    // functions related to configuration checks
    bool have_conf(const char* name) const;
    void cache_conf_tests();

    // functions that check or evaluate configurations
    const char* list_conf_head(const char* name) const;
    bool list_conf_find(const char* name, const char* elem) const;
    const char* eval_word_conf(const char* name) const;
    bool eval_bool_conf(const char* name) const;
    Ret eval_str_conf(const char* name, std::string& str) const;
    void eval_code_conf(std::ostream& os, const opt_t* opts, const char* name) const;
    void eval_code_conf(
            std::ostream& os, const opt_t* opts, const char* name, RenderCallback& callback) const;

    friend class opt_t;
};

} // namespace re2c

#endif // _RE2C_CODEGEN_SYNTAX_
