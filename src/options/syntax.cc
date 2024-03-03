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
        , allowed_vars()
        , confs()
        , have_oneline_if(false)
        , have_oneline_switch(false)
        , stack_code()
        , stack_code_list() {
    allowed_list_confs["api"] = {"default", "generic"};
    allowed_list_confs["api_style"] = {"functions", "freeform"};
    allowed_list_confs["code_model"] = {"goto_label", "loop_switch", "recursive_functions"};
    allowed_list_confs["target"] = {"code", "dot", "skeleton"};

    allowed_word_confs["computed_goto"] = {"enabled", "optional", "unsupported"};
    allowed_word_confs["case_ranges"] = {"enabled", "optional", "unsupported"};
    allowed_word_confs["semicolons"] = {"yes", "no"};
    allowed_word_confs["implicit_bool_conversion"] = {"yes", "no"};
    allowed_word_confs["backtick_quoted_strings"] = {"yes", "no"};
    allowed_word_confs["standalone_single_quotes"] = {"yes", "no"};

    allowed_code_confs["code:var"] = {
        {"type", "name", "init"}, {}, {StxLOpt::HAVE_INIT}
    };
    allowed_code_confs["code:const"] = {
        {"type", "name", "init"}, {}, {}
    };
    allowed_code_confs["code:array"] = {
        {"type", "name", "size"}, {"row", "elem"}, {}
    };
    allowed_code_confs["code:array_elem"] = {
        {"array", "index"}, {}, {}
    };
    allowed_code_confs["code:type_int"] = {};
    allowed_code_confs["code:type_uint"] = {};
    allowed_code_confs["code:type_cond_enum"] = {};
    allowed_code_confs["code:type_yybm"] = {};
    allowed_code_confs["code:type_yytarget"] = {};
    allowed_code_confs["code:assign"] = {
        {"rhs"}, {"lhs"}, {}
    };
    allowed_code_confs["code:assign_op"] = {
        {"lhs", "rhs", "op"}, {}, {}
    };
    allowed_code_confs["code:if_then_else"] = {
        {"cond"}, {"branch", "stmt"}, {StxLOpt::HAVE_COND}
    };
    allowed_code_confs["code:if_then_else_oneline"] = {
        {"cond"}, {"branch", "stmt"}, {StxLOpt::HAVE_COND}
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
        {}, {"val"}, {StxLOpt::MULTIVAL, StxLOpt::CHAR_LITERALS}
    };
    allowed_code_confs["code:switch_case_default"] = {};
    allowed_code_confs["code:loop"] = {
        {"label"}, {"stmt"}, {}
    };
    allowed_code_confs["code:enum"] = {
        {"name", "type", "init"}, {"elem"}, {StxLOpt::HAVE_INIT}
    };
    allowed_code_confs["code:enum_elem"] = {
        {"name", "type"}, {}, {}
    };
    allowed_code_confs["code:fndecl"] = {
        {"name", "type", "argname", "argtype", "argmods"},
        {"arg"},
        {StxLOpt::HAVE_TYPE, StxLOpt::HAVE_ARGMODS}
    };
    allowed_code_confs["code:fndef"] = {
        {"name", "type", "argname", "argtype", "argmods"},
        {"arg", "stmt"},
        {StxLOpt::HAVE_TYPE, StxLOpt::HAVE_ARGMODS}
    };
    allowed_code_confs["code:fncall"] = {
        {"name", "retval"}, {"arg"}, {StxLOpt::HAVE_ARGS, StxLOpt::HAVE_RETVAL}
    };
    allowed_code_confs["code:tailcall"] = { // no `retval` as it won't be used anyway
        {"name"}, {"arg"}, {StxLOpt::HAVE_ARGS, StxLOpt::HAVE_RETVAL}
    };
    allowed_code_confs["code:recursive_functions"] = {
        {"fndecl", "fndef"}, {"fn"}, {}
    };
    allowed_code_confs["code:fingerprint"] = {
        {"version", "date"}, {}, {}
    };
    allowed_code_confs["code:line_info"] = {
        {"line", "file"}, {}, {}
    };
    allowed_code_confs["code:label"] = {
        {"name"}, {}, {}
    };
    allowed_code_confs["code:abort"] = {};
    allowed_code_confs["code:yyaccept"] = {
        {"var", "num"}, {}, {}
    };
    allowed_code_confs["code:yydebug"] = {
        {"debug", "state", "char"}, {}, {}
    };
    allowed_code_confs["code:yypeek"] = {
        {"char", "ctype", "peek", "cursor", "typecast"}, {}, {}
    };
    allowed_code_confs["code:yyskip"] = {
        {"skip", "cursor"}, {}, {}
    };
    allowed_code_confs["code:yybackup"] = {
        {"backup", "cursor", "marker"}, {}, {}
    };
    allowed_code_confs["code:yyskip_peek"] = {
        {"char", "ctype", "cursor", "typecast"}, {}, {}
    };
    allowed_code_confs["code:yypeek_skip"] = {
        {"char", "ctype", "cursor", "typecast"}, {}, {}
    };
    allowed_code_confs["code:yyskip_backup"] = {
        {"cursor", "marker"}, {}, {}
    };
    allowed_code_confs["code:yybackup_skip"] = {
        {"cursor", "marker"}, {}, {}
    };
    allowed_code_confs["code:yybackup_peek"] = {
        {"char", "ctype", "cursor", "marker", "typecast"}, {}, {}
    };
    allowed_code_confs["code:yyskip_backup_peek"] = {
        {"char", "ctype", "cursor", "marker", "typecast"}, {}, {}
    };
    allowed_code_confs["code:yybackup_peek_skip"] = {
        {"char", "ctype", "cursor", "marker", "typecast"}, {}, {}
    };

#define STX_VAR(name) allowed_vars.insert(name);
    RE2C_STX_VARS
#undef STX_VAR
}

// is this a known configuration-specific conditional?
Ret Stx::check_cond(const char* conf, StxLOpt opt) const {
    auto i = allowed_code_confs.find(conf);
    CHECK(i != allowed_code_confs.end());
    const std::vector<StxLOpt>& conds = i->second.cond_vars;
    if (std::find(conds.begin(), conds.end(), opt) != conds.end()) return Ret::OK;

    RET_FAIL(error("unknown conditional in configuration '%s'", conf));
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
            } else if (x->cond.opt->is_local) {
                // no need to check global conditionals, as they are filtered in the lexer
                CHECK_RET(check_cond(conf->name, x->cond.opt->lopt));
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
    have_oneline_if = have_conf("code:if_then_else_oneline");
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

static bool eval_cond(const StxOpt* cond, const opt_t* opts, RenderCallback* callback) {
    if (cond->is_local) {
        DCHECK(callback != nullptr);
        return callback->eval_cond(cond->lopt);
    } else {
        switch (cond->gopt) {
        case StxGOpt::API_DEFAULT:
            return opts->api == Api::DEFAULT;
        case StxGOpt::API_CUSTOM:
            return opts->api == Api::CUSTOM;
        case StxGOpt::API_STYLE_FUNCTIONS:
            return opts->api_style == ApiStyle::FUNCTIONS;
        case StxGOpt::API_STYLE_FREEFORM:
            return opts->api_style == ApiStyle::FREEFORM;
        case StxGOpt::CODE_MODEL_GOTO_LABEL:
            return opts->code_model == CodeModel::GOTO_LABEL;
        case StxGOpt::CODE_MODEL_LOOP_SWITCH:
            return opts->code_model == CodeModel::LOOP_SWITCH;
        case StxGOpt::CODE_MODEL_REC_FUNC:
            return opts->code_model == CodeModel::REC_FUNC;
        case StxGOpt::START_CONDITIONS:
            return opts->start_conditions;
        case StxGOpt::STORABLE_STATE:
            return opts->storable_state;
        case StxGOpt::DATE:
            return opts->date;
        case StxGOpt::VER:
            return opts->version;
        case StxGOpt::CASE_RANGES:
            return opts->case_ranges;
        case StxGOpt::UNSAFE:
            return opts->unsafe;
        case StxGOpt::LOOP_LABEL:
            return !opts->label_loop.empty();
        }
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
            if (eval_cond(x->cond.opt, opts, &callback)) {
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
