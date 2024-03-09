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
    allowed_list_confs[StxConfId::API] = {"default", "generic"};
    allowed_list_confs[StxConfId::API_STYLE] = {"functions", "freeform"};
    allowed_list_confs[StxConfId::CODE_MODEL] = {"goto_label", "loop_switch", "recursive_functions"};
    allowed_list_confs[StxConfId::TARGET] = {"code", "dot", "skeleton"};

    allowed_word_confs[StxConfId::COMPUTED_GOTO] = {"enabled", "optional", "unsupported"};
    allowed_word_confs[StxConfId::CASE_RANGES] = {"enabled", "optional", "unsupported"};
    allowed_word_confs[StxConfId::SEMICOLONS] = {"yes", "no"};
    allowed_word_confs[StxConfId::IMPLICIT_BOOL_CONVERSION] = {"yes", "no"};
    allowed_word_confs[StxConfId::BACKTICK_QUOTED_STRINGS] = {"yes", "no"};
    allowed_word_confs[StxConfId::STANDALONE_SINGLE_QUOTES] = {"yes", "no"};

    allowed_code_confs[StxConfId::VAR_LOCAL] = {
        {StxVarId::TYPE, StxVarId::NAME, StxVarId::INIT}, {}, {StxLOpt::HAVE_INIT}
    };
    allowed_code_confs[StxConfId::VAR_GLOBAL] = {
        {StxVarId::TYPE, StxVarId::NAME, StxVarId::INIT}, {}, {StxLOpt::HAVE_INIT}
    };
    allowed_code_confs[StxConfId::CONST_LOCAL] = {
        {StxVarId::TYPE, StxVarId::NAME, StxVarId::INIT}, {}, {}
    };
    allowed_code_confs[StxConfId::CONST_GLOBAL] = {
        {StxVarId::TYPE, StxVarId::NAME, StxVarId::INIT}, {}, {}
    };
    allowed_code_confs[StxConfId::ARRAY_LOCAL] = {
        {StxVarId::TYPE, StxVarId::NAME, StxVarId::SIZE}, {StxVarId::ROW, StxVarId::ELEM}, {}
    };
    allowed_code_confs[StxConfId::ARRAY_GLOBAL] = {
        {StxVarId::TYPE, StxVarId::NAME, StxVarId::SIZE}, {StxVarId::ROW, StxVarId::ELEM}, {}
    };
    allowed_code_confs[StxConfId::ARRAY_ELEM] = {
        {StxVarId::ARRAY, StxVarId::INDEX}, {}, {}
    };
    allowed_code_confs[StxConfId::TYPE_INT] = {};
    allowed_code_confs[StxConfId::TYPE_UINT] = {};
    allowed_code_confs[StxConfId::TYPE_COND_ENUM] = {};
    allowed_code_confs[StxConfId::TYPE_YYBM] = {};
    allowed_code_confs[StxConfId::TYPE_YYTARGET] = {};
    allowed_code_confs[StxConfId::ASSIGN] = {
        {StxVarId::RHS}, {StxVarId::LHS}, {}
    };
    allowed_code_confs[StxConfId::ASSIGN_OP] = {
        {StxVarId::LHS, StxVarId::RHS, StxVarId::OP}, {}, {}
    };
    allowed_code_confs[StxConfId::IF_THEN_ELSE] = {
        {StxVarId::COND}, {StxVarId::BRANCH, StxVarId::STMT}, {StxLOpt::HAVE_COND}
    };
    allowed_code_confs[StxConfId::IF_THEN_ELSE_ONELINE] = {
        {StxVarId::COND}, {StxVarId::BRANCH, StxVarId::STMT}, {StxLOpt::HAVE_COND}
    };
    allowed_code_confs[StxConfId::SWITCH] = {
        {StxVarId::EXPR}, {StxVarId::CASE}, {}
    };
    allowed_code_confs[StxConfId::SWITCH_CASES] = {
        {}, {StxVarId::CASE, StxVarId::STMT}, {}
    };
    allowed_code_confs[StxConfId::SWITCH_CASES_ONELINE] = {
        {}, {StxVarId::CASE, StxVarId::STMT}, {}
    };
    allowed_code_confs[StxConfId::SWITCH_CASE_RANGE] = {
        {}, {StxVarId::VAL}, {StxLOpt::MULTIVAL, StxLOpt::CHAR_LITERALS}
    };
    allowed_code_confs[StxConfId::SWITCH_CASE_DEFAULT] = {};
    allowed_code_confs[StxConfId::LOOP] = {
        {StxVarId::LABEL}, {StxVarId::STMT}, {}
    };
    allowed_code_confs[StxConfId::ENUM] = {
        {StxVarId::NAME, StxVarId::TYPE, StxVarId::INIT}, {StxVarId::ELEM}, {StxLOpt::HAVE_INIT}
    };
    allowed_code_confs[StxConfId::ENUM_ELEM] = {
        {StxVarId::NAME, StxVarId::TYPE}, {}, {}
    };
    allowed_code_confs[StxConfId::FNDECL] = {
        {StxVarId::NAME, StxVarId::TYPE, StxVarId::ARGNAME, StxVarId::ARGTYPE, StxVarId::ARGMODS},
        {StxVarId::ARG},
        {StxLOpt::HAVE_TYPE, StxLOpt::HAVE_ARGMODS}
    };
    allowed_code_confs[StxConfId::FNDEF] = {
        {StxVarId::NAME, StxVarId::TYPE, StxVarId::ARGNAME, StxVarId::ARGTYPE, StxVarId::ARGMODS},
        {StxVarId::ARG, StxVarId::STMT},
        {StxLOpt::HAVE_TYPE, StxLOpt::HAVE_ARGMODS}
    };
    allowed_code_confs[StxConfId::FNCALL] = {
        {StxVarId::NAME, StxVarId::RETVAL},
        {StxVarId::ARG},
        {StxLOpt::HAVE_ARGS, StxLOpt::HAVE_RETVAL}
    };
    allowed_code_confs[StxConfId::TAILCALL] = { // no `retval` as it won't be used anyway
        {StxVarId::NAME}, {StxVarId::ARG}, {StxLOpt::HAVE_ARGS, StxLOpt::HAVE_RETVAL}
    };
    allowed_code_confs[StxConfId::RECURSIVE_FUNCTIONS] = {
        {StxVarId::FNDECL, StxVarId::FNDEF}, {StxVarId::FN}, {}
    };
    allowed_code_confs[StxConfId::FINGERPRINT] = {
        {StxVarId::VER, StxVarId::DATE}, {}, {}
    };
    allowed_code_confs[StxConfId::LINE_INFO] = {
        {StxVarId::LINE, StxVarId::FILE}, {}, {}
    };
    allowed_code_confs[StxConfId::ABORT] = {};
    allowed_code_confs[StxConfId::ACCEPT] = {
        {StxVarId::VAR, StxVarId::NUM}, {}, {}
    };
    allowed_code_confs[StxConfId::DEBUG] = {
        {StxVarId::DEBUG, StxVarId::STATE, StxVarId::CHAR}, {}, {}
    };
    allowed_code_confs[StxConfId::PEEK] = {
        {StxVarId::CHAR, StxVarId::CTYPE, StxVarId::PEEK, StxVarId::CURSOR, StxVarId::TYPECAST},
        {},
        {}
    };
    allowed_code_confs[StxConfId::SKIP] = {
        {StxVarId::SKIP, StxVarId::CURSOR}, {}, {}
    };
    allowed_code_confs[StxConfId::BACKUP] = {
        {StxVarId::BACKUP, StxVarId::CURSOR, StxVarId::MARKER}, {}, {}
    };
    allowed_code_confs[StxConfId::SKIP_PEEK] = {
        {StxVarId::CHAR, StxVarId::CTYPE, StxVarId::CURSOR, StxVarId::TYPECAST}, {}, {}
    };
    allowed_code_confs[StxConfId::PEEK_SKIP] = {
        {StxVarId::CHAR, StxVarId::CTYPE, StxVarId::CURSOR, StxVarId::TYPECAST}, {}, {}
    };
    allowed_code_confs[StxConfId::SKIP_BACKUP] = {
        {StxVarId::CURSOR, StxVarId::MARKER}, {}, {}
    };
    allowed_code_confs[StxConfId::BACKUP_SKIP] = {
        {StxVarId::CURSOR, StxVarId::MARKER}, {}, {}
    };
    allowed_code_confs[StxConfId::BACKUP_PEEK] = {
        {StxVarId::CHAR, StxVarId::CTYPE, StxVarId::CURSOR, StxVarId::MARKER, StxVarId::TYPECAST},
        {},
        {}
    };
    allowed_code_confs[StxConfId::SKIP_BACKUP_PEEK] = {
        {StxVarId::CHAR, StxVarId::CTYPE, StxVarId::CURSOR, StxVarId::MARKER, StxVarId::TYPECAST},
        {},
        {}
    };
    allowed_code_confs[StxConfId::BACKUP_PEEK_SKIP] = {
        {StxVarId::CHAR, StxVarId::CTYPE, StxVarId::CURSOR, StxVarId::MARKER, StxVarId::TYPECAST},
        {},
        {}
    };

#define STX_GLOBAL_VAR(id, name) allowed_vars.insert(StxVarId:: id);
    RE2C_STX_GLOBAL_VARS
#undef STX_GLOBAL_VAR
}

const char* Stx::conf_name(StxConfId id) {
#define STX_CONF(id, name) name
    static const char* names[] = {
        RE2C_STX_CONFS
    };
#undef STX_CONF
    return names[static_cast<uint32_t>(id)];
}

const char* Stx::var_name(StxVarId id) {
#define STX_LOCAL_VAR(id, name) name,
#define STX_GLOBAL_VAR(id, name) name,
    static const char* names[] = {
        RE2C_STX_LOCAL_VARS
        RE2C_STX_GLOBAL_VARS
    };
#undef STX_LOCAL_VAR
#undef STX_GLOBAL_VAR
    return names[static_cast<uint32_t>(id)];
}

// is this a known configuration-specific conditional?
Ret Stx::check_cond(StxConfId id, StxLOpt opt) const {
    auto i = allowed_code_confs.find(id);
    CHECK(i != allowed_code_confs.end());
    const std::vector<StxLOpt>& conds = i->second.cond_vars;
    if (std::find(conds.begin(), conds.end(), opt) != conds.end()) return Ret::OK;

    RET_FAIL(error("unknown conditional in configuration '%s'", conf_name(id)));
}

Ret Stx::check_var(StxConfId id, StxVarId var) const {
    // is this a global variable?
    if (allowed_vars.find(var) != allowed_vars.end()) return Ret::OK;

    // is this a known configuration-specific variable?
    auto i = allowed_code_confs.find(id);
    CHECK(i != allowed_code_confs.end());

    // this may be a list var; in that case it must be on the list stack
    bool is_list_var = std::find_if(stack_code_list.begin(), stack_code_list.end(),
            [var](const StxCode* x) { return var == x->list.var; })
        != stack_code_list.end();

    const std::vector<StxVarId>& v = is_list_var ? i->second.list_vars : i->second.vars;
    if (std::find(v.begin(), v.end(), var) != v.end()) return Ret::OK;

    RET_FAIL(error("unknown variable '%s' in configuration '%s'", var_name(var), conf_name(id)));
}

Ret Stx::check_word(StxConfId id, const char* word, bool list) const {
    auto allowed_confs = list ? allowed_list_confs : allowed_word_confs;
    auto i = allowed_confs.find(id);
    CHECK(i != allowed_confs.end());

    const std::vector<std::string>& w = i->second;
    if (std::find(w.begin(), w.end(), word) != w.end()) return Ret::OK;

    RET_FAIL(error("unknown value '%s' in configuration '%s'", word, conf_name(id)));
}

// validate that the option name in the given configuration exists
Ret Stx::validate_conf_word(const StxConf* conf) {
    CHECK(conf->type == StxConfType::WORD);

    if (allowed_word_confs.find(conf->id) == allowed_word_confs.end()) {
        RET_FAIL(error("unknown configuration '%s'", conf_name(conf->id)));
    }

    return check_word(conf->id, conf->word, /*list*/ false);
}

// validate that all option names used in the given list do exist
Ret Stx::validate_conf_list(const StxConf* conf) {
    CHECK(conf->type == StxConfType::LIST);

    if (allowed_list_confs.find(conf->id) == allowed_list_confs.end()) {
        RET_FAIL(error("unknown configuration '%s'", conf_name(conf->id)));
    }

    for (const StxWord* x = conf->list->head; x != nullptr; x = x->next) {
        CHECK_RET(check_word(conf->id, x->word, /*list*/ true));
    }

    return Ret::OK;
}

// validate that all option and variable names used in the given code do exist
Ret Stx::validate_conf_code(const StxConf* conf) {
    CHECK(conf->type == StxConfType::CODE);
    DCHECK(allowed_code_confs.find(conf->id) != allowed_code_confs.end());

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
            CHECK_RET(check_var(conf->id, x->var));
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
                CHECK_RET(check_cond(conf->id, x->cond.opt->lopt));
            }
            break;
        case StxCodeType::LIST:
            if (n == 0) { // recurse into list body
                stack_code_list.push_back(x);
                CHECK_RET(check_var(conf->id, x->list.var));
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

bool Stx::have_conf(StxConfId id) const {
    return confs.find(id) != confs.end();
}

void Stx::cache_conf_tests() {
    have_oneline_if = have_conf(StxConfId::IF_THEN_ELSE_ONELINE);
    have_oneline_switch = have_conf(StxConfId::SWITCH_CASES_ONELINE);
}

const char* Stx::list_conf_head(StxConfId id) const {
    auto i = confs.find(id);
    if (i != confs.end()) {
        const StxConf* c = i->second;
        CHECK(c->type == StxConfType::LIST);
        const StxWord* x = c->list->head;
        if (x) return x->word;
    }
    return DEFAULT_EMPTY;
}

bool Stx::list_conf_find(StxConfId id, const char* elem) const {
    auto i = confs.find(id);
    if (i != confs.end()) {
        const StxConf* c = i->second;
        CHECK(c->type == StxConfType::LIST);
        for (const StxWord* x = c->list->head; x; x = x->next) {
            if (strcmp(x->word, elem) == 0) return true;
        }
    }
    return false;
}

const char* Stx::eval_word_conf(StxConfId id) const {
    auto i = confs.find(id);
    if (i != confs.end()) {
        const StxConf* c = i->second;
        CHECK(c->type == StxConfType::WORD);
        return c->word;
    }
    return DEFAULT_EMPTY;
}

bool Stx::eval_bool_conf(StxConfId id) const {
    return strcmp(eval_word_conf(id), "yes") == 0;
}

Ret Stx::eval_str_conf(StxConfId id, std::string& str) const{
    auto i = confs.find(id);
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
        RET_FAIL(error("configuration '%s' must have string value", conf_name(c->id)));
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
        std::ostream& os, const opt_t* opts, StxConfId id, RenderCallback& callback) const {
    auto i = confs.find(id);
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

void Stx::eval_code_conf(std::ostream& os, const opt_t* opts, StxConfId id) const {
    RenderCallback dummy;
    eval_code_conf(os, opts, id, dummy);
}

} // namespace re2c
