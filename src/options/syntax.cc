#include <stdio.h>
#include <string.h>
#include <iostream>

#include "src/codegen/output.h"
#include "src/options/opt.h"
#include "src/options/syntax.h"

namespace re2c {

Stx::Stx(OutAllocator& alc)
        : alc(alc)
        , stack_code()
        , stack_code_list() {}

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
Ret Stx::check_cond(StxLOpt opt, const char* conf, const std::unordered_set<StxLOpt>& conds) const {
    if (conds.find(opt) != conds.end()) return Ret::OK;
    RET_FAIL(error("unknown conditional in configuration '%s'", conf));
}

Ret Stx::check_var(
        StxVarId var,
        const char* conf,
        const std::unordered_set<StxVarId>& vars,
        const std::unordered_set<StxVarId>& list_vars) const {
    // is this a global variable?
    static const std::unordered_set<StxVarId> global_vars({
#define STX_GLOBAL_VAR(id, name) StxVarId:: id,
    RE2C_STX_GLOBAL_VARS
#undef STX_GLOBAL_VAR
    });
    if (global_vars.find(var) != global_vars.end()) return Ret::OK;

    // this may be a list var; in that case it must be on the list stack
    bool is_list_var = std::find_if(stack_code_list.begin(), stack_code_list.end(),
            [var](const StxCode* x) { return var == x->list.var; })
        != stack_code_list.end();

    // is this a known configuration-specific variable?
    const std::unordered_set<StxVarId>& v = is_list_var ? list_vars : vars;
    if (std::find(v.begin(), v.end(), var) != v.end()) return Ret::OK;

    RET_FAIL(error("unknown variable '%s' in configuration '%s'", var_name(var), conf));
}

// validate that all option and variable names used in the given code do exist
Ret Stx::validate_conf_code(
        const StxCodes* code,
        const char* conf,
        const std::unordered_set<StxVarId>& vars,
        const std::unordered_set<StxVarId>& list_vars,
        const std::unordered_set<StxLOpt>& conds) const {
    stack_code_list.clear();
    stack_code_t& stack = stack_code;
    stack.clear();
    for (const StxCode* x = code->head; x != nullptr; x = x->next) {
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
            CHECK_RET(check_var(x->var, conf, vars, list_vars));
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
                CHECK_RET(check_cond(x->cond.opt->lopt, conf, conds));
            }
            break;
        case StxCodeType::LIST:
            if (n == 0) { // recurse into list body
                stack_code_list.push_back(x);
                CHECK_RET(check_var(x->list.var, conf, vars, list_vars));
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
        const StxCodes* code, std::ostream& os, const opt_t* opts, RenderCallback& callback) const {
    stack_code_t& stack = stack_code;
    size_t bottom = stack.size();
    push_list_on_stack(code->head);

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

void Stx::eval_code_conf(const StxCodes* code, std::ostream& os, const opt_t* opts) const {
    RenderCallback dummy;
    eval_code_conf(code, os, opts, dummy);
}

} // namespace re2c
