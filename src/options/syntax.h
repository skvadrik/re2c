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
#include "src/options/syntax_parser.h"
#include "src/util/allocator.h"
#include "src/util/check.h"
#include "src/util/containers.h"
#include "src/util/forbid_copy.h"

namespace re2c {

class RenderCallback;
struct StxCode;
struct StxName;
struct conopt_t;
struct opt_t;

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

    OutAllocator& alc;

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

    Ret load_config(conopt_t& globopts, Msg& msg);

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

    bool have_conf(const char* name) const;
    bool first_in_list(const char* conf, const char* word) const;

    // functions that validate configuration and variable names in the AST
    Ret validate_conf_list(const StxConf* conf);
    Ret validate_conf_word(const StxConf* conf);
    Ret validate_conf_code(const StxConf* conf);

    // functions that test for presence of specific configs (cached in class fields)
    bool specialize_oneline_if() const;
    bool specialize_oneline_switch() const;
    void cache_conf_tests();

    // functions that generate code for a given syntax configuration
    void gen_code(
            std::ostream& os, const opt_t* opts, const char* name, RenderCallback& callback) const;
    void gen_str(std::ostream& os, const opt_t* opts, const char* name) const;

    // functions that evaluate word configurations
    const char* eval_conf(const char* name) const;
    bool eval_bool_conf(const char* name) const;
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
    std::string tmp_str;

  public:
    Msg& msg;

  public:
    StxFile(const std::string& fname, Msg& msg, OutAllocator& alc);
    ~StxFile();
    Ret read(Lang lang);
    Ret parse(Stx& stx);
    int lex_token(STX_STYPE* yylval);
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

inline StxConf* Stx::make_conf_word(const char* name, const char* word) {
    StxConf* x = make_conf(StxConfType::WORD, name);
    x->word = word;
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

inline bool Stx::have_conf(const char* name) const {
    return confs.find(name) != confs.end();
}

inline bool Stx::first_in_list(const char* name, const char* word) const {
    DCHECK(confs.find(name) != confs.end());
    const StxConf* conf = confs.find(name)->second;
    CHECK(conf->type == StxConfType::LIST);

    const StxName* x = conf->list->head;
    return x && strcmp(x->name, word) == 0;
}

inline const char* Stx::eval_conf(const char* name) const {
    DCHECK(confs.find(name) != confs.end());
    const StxConf* conf = confs.find(name)->second;
    CHECK(conf->type == StxConfType::WORD);
    return conf->word;
}

inline bool Stx::eval_bool_conf(const char* name) const {
    return strcmp(eval_conf(name), "yes") == 0;
}

loc_t StxFile::tok_loc() const {
    DCHECK(pos <= tok);
    return {loc.line, static_cast<uint32_t>(tok - pos), loc.file};
}

} // namespace re2c

#endif // _RE2C_CODEGEN_SYNTAX_
