#include <stdio.h>
#include <string.h>
#include <iostream>

#include "src/codegen/output.h"
#include "src/options/opt.h"
#include "src/options/syntax.h"

namespace re2c {

Stx::Stx(OutAllocator& alc)
        : alc(alc)
        , allowed_list_confs()
        , allowed_word_confs()
        , allowed_code_confs()
        , allowed_conds()
        , allowed_vars()
        , confs()
        , have_oneline_if(false)
        , have_oneline_switch(false)
        , stack_code()
        , stack_code_list() {
    allowed_list_confs["api"] = {"default", "generic"};
    allowed_list_confs["api_style"] = {"functions", "freeform"};
    allowed_list_confs["jump_model"] = {"goto_label", "loop_switch"};
    allowed_list_confs["target"] = {"code", "dot", "skeleton"};

    allowed_word_confs["computed_goto"] = {"enabled", "optional", "unsupported"};
    allowed_word_confs["case_ranges"] = {"enabled", "optional", "unsupported"};
    allowed_word_confs["constants"] = {"snake_case", "upper_case"};
    allowed_word_confs["char_literals"] = {"hexadecimal", "symbolic"};
    allowed_word_confs["semicolons"] = {"yes", "no"};
    allowed_word_confs["abort_in_default_case"] = {"yes", "no"};
    allowed_word_confs["implicit_bool_conversion"] = {"yes", "no"};
    allowed_word_confs["backtick_quoted_strings"] = {"yes", "no"};
    allowed_word_confs["standalone_single_quotes"] = {"yes", "no"};

    allowed_code_confs["code:var"] = {
        {"type", "name", "init"}, {}, {"have_init"}
    };
    allowed_code_confs["code:const"] = {
        {"type", "name", "init"}, {}, {}
    };
    allowed_code_confs["code:array"] = {
        {"type", "name", "size"}, {"row", "elem"}, {}
    };
    allowed_code_confs["code:type_int"] = {};
    allowed_code_confs["code:type_uint"] = {};
    allowed_code_confs["code:type_cond_enum"] = {};
    allowed_code_confs["code:type_yybm"] = {};
    allowed_code_confs["code:type_yytarget"] = {};
    allowed_code_confs["code:if_then_else"] = {
        {"then_cond", "else_cond"},
        {"then_stmt", "else_stmt"},
        {"have_else_part", "have_else_cond"}
    };
    allowed_code_confs["code:if_then_oneline"] = {
        {"then_cond"}, {"then_stmt"}, {}
    };
    allowed_code_confs["code:switch"] = {
        {"expr"}, {"case"}, {}
    };
    allowed_code_confs["code:switch_cases"] = {
        {}, {"case", "stmt"}, {}
    };
    allowed_code_confs["code:switch_cases_oneline"] = {
        {}, {"case", "stmt"}, {}
    };
    allowed_code_confs["code:switch_case_range"] = {
        {}, {"val"}, {"multival"}
    };
    allowed_code_confs["code:switch_case_default"] = {};
    allowed_code_confs["code:loop"] = {
        {"label"}, {"stmt"}, {"have_label"}
    };
    allowed_code_confs["code:loop_label"] = {};
    allowed_code_confs["code:enum"] = {
        {"name", "type", "init"}, {"elem"}, {"have_init"}
    };
    allowed_code_confs["code:enum_elem"] = {
        {"name", "type"}, {}, {}
    };
    allowed_code_confs["code:fingerprint"] = {
        {"version", "date"}, {}, {"have_version", "have_date"}
    };
    allowed_code_confs["code:line_info"] = {
        {"line", "file"}, {}, {}
    };
    allowed_code_confs["code:label"] = {
        {"name"}, {}, {}
    };
    allowed_code_confs["code:abort"] = {};
    allowed_code_confs["code:yypeek_expr"] = {
        {"peek", "cursor", "typecast"}, {}, {}
    };

#define STX_COND(name, selector) allowed_conds[name] = [](const opt_t* opts) { return selector; };
    RE2C_STX_CONDS
#undef STX_COND

#define STX_VAR(name) allowed_vars.insert(name);
    RE2C_STX_VARS
#undef STX_VAR
}

Ret Stx::check_cond(const char* conf, const char* cond, bool code) const {
    // is this a global conditional?
    if (allowed_conds.find(cond) != allowed_conds.end()) return Ret::OK;

    if (code) {
        // is this a known configuration-specific conditional?
        auto i = allowed_code_confs.find(conf);
        CHECK(i != allowed_code_confs.end());
        const std::vector<std::string>& conds = i->second.cond_vars;
        if (std::find(conds.begin(), conds.end(), cond) != conds.end()) return Ret::OK;
    }

    RET_FAIL(error("unknown conditional '%s' in configuration '%s'", cond, conf));
}

Ret Stx::check_var(const char* conf, const char* var) const {
    // is this a global variable?
    if (allowed_vars.find(var) != allowed_vars.end()) return Ret::OK;

    // is this a known configuration-specific variable?
    auto i = allowed_code_confs.find(conf);
    CHECK(i != allowed_code_confs.end());

    // this may be a list var; in that case it must be on the list stack
    bool is_list_var = std::find_if(stack_code_list.begin(), stack_code_list.end(),
            [var](const StxCode* x) { return strcmp(var, x->list.var) == 0; })
        != stack_code_list.end();

    const std::vector<std::string>& v = is_list_var ? i->second.list_vars : i->second.vars;
    if (std::find(v.begin(), v.end(), var) != v.end()) return Ret::OK;

    RET_FAIL(error("unknown variable '%s' in configuration '%s'", var, conf));
}

Ret Stx::check_word(const char* conf, const char* word, bool list) const {
    auto allowed_confs = list ? allowed_list_confs : allowed_word_confs;
    auto i = allowed_confs.find(conf);
    CHECK(i != allowed_confs.end());

    const std::vector<std::string>& w = i->second;
    if (std::find(w.begin(), w.end(), word) != w.end()) return Ret::OK;

    RET_FAIL(error("unknown value '%s' in configuration '%s'", word, conf));
}

// validate that the option name in the given configuration exists
Ret Stx::validate_conf_word(const StxConf* conf) {
    CHECK(conf->type == StxConfType::WORD);

    if (allowed_word_confs.find(conf->name) == allowed_word_confs.end()) {
        RET_FAIL(error("unknown configuration '%s'", conf->name));
    }

    return check_word(conf->name, conf->word, /*list*/ false);
}

// validate that all option names used in the given list do exist
Ret Stx::validate_conf_list(const StxConf* conf) {
    CHECK(conf->type == StxConfType::LIST);

    if (allowed_list_confs.find(conf->name) == allowed_list_confs.end()) {
        RET_FAIL(error("unknown configuration '%s'", conf->name));
    }

    for (const StxName* x = conf->list->head; x != nullptr; x = x->next) {
        CHECK_RET(check_word(conf->name, x->name, /*list*/ true));
    }

    return Ret::OK;
}

// validate that all option and variable names used in the given code do exist
Ret Stx::validate_conf_code(const StxConf* conf) {
    CHECK(conf->type == StxConfType::CODE);

    if (allowed_code_confs.find(conf->name) == allowed_code_confs.end()) {
        RET_FAIL(error("unknown configuration '%s'", conf->name));
    }

    stack_code_list.clear();
    stack_code_t& stack = stack_code;
    stack.clear();
    for (const StxCode* x = conf->code->head; x != nullptr; x = x->next) {
        stack.push_back({x, 0});
    }

    while (!stack.empty()) {
        const StxCode* x = stack.back().first;
        uint8_t n = stack.back().second;
        stack.pop_back();

        switch (x->type) {
        case StxCodeType::STR:
            // no option names to check here
            break;
        case StxCodeType::VAR:
            CHECK_RET(check_var(conf->name, x->var));
            break;
        case StxCodeType::COND:
            if (n == 0) { // recurse into branches
                stack.push_back({x, 1});
                for (const StxCode* y = x->cond.then_code->head; y != nullptr; y = y->next) {
                    stack.push_back({y, 0});
                }
                if (x->cond.else_code != nullptr) {
                    for (const StxCode* y = x->cond.else_code->head; y != nullptr; y = y->next) {
                        stack.push_back({y, 0});
                    }
                }
            } else { // check conditional name and return
                CHECK_RET(check_cond(conf->name, x->cond.conf, /*code*/ true));
            }
            break;
        case StxCodeType::LIST:
            if (n == 0) { // recurse into list body
                stack_code_list.push_back(x);
                CHECK_RET(check_var(conf->name, x->list.var));
                stack.push_back({x, 1});
                for (const StxCode* y = x->list.code->head; y != nullptr; y = y->next) {
                    stack.push_back({y, 0});
                }
            } else { // check variable name and return
                stack_code_list.pop_back();
            }
            break;
        }
    }

    return Ret::OK;
}

void Stx::add_conf(const char* name, const StxConf* conf) { confs[name] = conf; }

bool Stx::have_conf(const char* name) const {
    return confs.find(name) != confs.end();
}

void Stx::cache_conf_tests() {
    have_oneline_if = have_conf("code:if_then_oneline");
    have_oneline_switch = have_conf("code:switch_cases_oneline");
}

const char* Stx::list_conf_head(const char* name) const {
    auto i = confs.find(name);
    if (i != confs.end()) {
        const StxConf* c = i->second;
        CHECK(c->type == StxConfType::LIST);
        const StxName* x = c->list->head;
        if (x) return x->name;
    }
    return DEFAULT_EMPTY;
}

bool Stx::list_conf_find(const char* name, const char* elem) const {
    auto i = confs.find(name);
    if (i != confs.end()) {
        const StxConf* c = i->second;
        CHECK(c->type == StxConfType::LIST);
        for (const StxName* x = c->list->head; x; x = x->next) {
            if (strcmp(x->name, elem) == 0) return true;
        }
    }
    return false;
}

const char* Stx::eval_word_conf(const char* name) const {
    auto i = confs.find(name);
    if (i != confs.end()) {
        const StxConf* c = i->second;
        CHECK(c->type == StxConfType::WORD);
        return c->word;
    }
    return DEFAULT_EMPTY;
}

bool Stx::eval_bool_conf(const char* name) const {
    return strcmp(eval_word_conf(name), "yes") == 0;
}

Ret Stx::eval_str_conf(const char* name, std::string& str) const{
    auto i = confs.find(name);
    if (i == confs.end()) {
        str = DEFAULT_EMPTY;
        return Ret::OK;
    }

    const StxConf* c = i->second;
    CHECK(c->type == StxConfType::CODE);

    const StxCode* x = c->code->head;
    if (x && x->type == StxCodeType::STR && !x->next) {
        str = x->str;
        return Ret::OK;
    } else {
        RET_FAIL(error("configuration '%s' must have string value", c->name));
    }
}

void Stx::push_list_on_stack(const StxCode* x) const {
    if (x == nullptr) return;
    push_list_on_stack(x->next);
    stack_code.push_back({x, 0});
}

bool Stx::eval_cond(const char* cond, const opt_t* opts, RenderCallback* callback) const {
    auto i = allowed_conds.find(cond);
    if (i != allowed_conds.end()) {
        return i->second(opts);
    } else if (callback != nullptr) {
        return callback->eval_cond(cond);
    }
    UNREACHABLE();
    return false;
}

static inline bool eval_list_bounds(size_t size, int32_t& lbound, int32_t& rbound) {
    lbound = lbound >= 0 ? lbound : (std::max(0, static_cast<int32_t>(size) + lbound));
    rbound = rbound >= 0 ? rbound : (static_cast<int32_t>(size) + rbound);
    return lbound <= rbound && rbound >= 0;
}

void Stx::eval_code_conf(
        std::ostream& os, const opt_t* opts, const char* name, RenderCallback& callback) const {
    auto i = confs.find(name);
    if (i == confs.end()) return; // if configuration is not defined, do nothing

    const StxConf* c = i->second;
    CHECK(c->type == StxConfType::CODE);

    stack_code_t& stack = stack_code;
    size_t bottom = stack.size();
    push_list_on_stack(c->code->head);

    while (stack.size() != bottom) {
        const StxCode* x = stack.back().first;
        int32_t n = stack.back().second;
        stack.pop_back();

        switch (x->type) {
        case StxCodeType::STR:
            os << x->str;
            break;
        case StxCodeType::VAR:
            callback.render_var(x->var);
            break;
        case StxCodeType::COND:
            if (eval_cond(x->cond.conf, opts, &callback)) {
                push_list_on_stack(x->cond.then_code->head);
            } else if (x->cond.else_code != nullptr) {
                push_list_on_stack(x->cond.else_code->head);
            }
            break;
        case StxCodeType::LIST:
            if (n == 0) {
                int32_t lbound = x->list.lbound;
                int32_t rbound = x->list.rbound;
                if (eval_list_bounds(callback.get_list_size(x->list.var), lbound, rbound)) {
                    callback.start_list(
                            x->list.var, static_cast<size_t>(lbound), static_cast<size_t>(rbound));
                    stack.push_back({x, 1});
                    push_list_on_stack(x->list.code->head);
                }
            } else if (callback.next_in_list(x->list.var)) {
                stack.push_back({x, 1});
                push_list_on_stack(x->list.code->head);
            }
            break;
        }
    }
}

void Stx::eval_code_conf(std::ostream& os, const opt_t* opts, const char* name) const {
    RenderCallback dummy;
    eval_code_conf(os, opts, name, dummy);
}

} // namespace re2c
