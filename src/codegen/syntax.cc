#include <stdio.h>

#include "src/codegen/syntax.h"

namespace re2c {

Stx::Stx(OutAllocator& alc)
        : alc(alc)
        , allowed_confs()
        , allowed_conds()
        , allowed_vars()
        , stack_expr()
        , stack_code()
        , stack_code_list()
        , confs() {
    allowed_confs["api"] = {
        {"pointers", "generic"}, {}, {}
    };
    allowed_confs["api_pointers"] = {};
    allowed_confs["api_generic"] = {};
    allowed_confs["api_style"] = {
        {"functions", "freeform"}, {}, {}
    };
    allowed_confs["api_style_functions"] = {};
    allowed_confs["api_style_freeform"] = {};
    allowed_confs["api_yypeek_expr"] = {
        {"expr"}, {}, {}
    };
    allowed_confs["codegen_model"] = {
        {"goto_label", "loop_switch"}, {}, {}
    };
    allowed_confs["codegen_model_goto_label"] = {};
    allowed_confs["codegen_model_loop_switch"] = {};
    allowed_confs["code_var_defn_local"] = {
        {"type", "name", "init"}, {}, {"have_init"}
    };
    allowed_confs["code_var_defn_global"] = {
        {"type", "name", "init"}, {}, {}
    };
    allowed_confs["code_array_defn"] = {
        {"type", "name", "init"}, {}, {}
    };
    allowed_confs["code_type_int"] = {};
    allowed_confs["code_type_uint"] = {};
    allowed_confs["code_type_yyctype"] = {
        {"type"}, {}, {}
    };
    allowed_confs["code_type_yybm"] = {};
    allowed_confs["code_if_then_else"] = {
        {"then_cond", "else_cond"},
        {"then_stmt", "else_stmt"},
        {"have_else_part", "have_else_cond"}
    };
    allowed_confs["code_if_then_else_oneline"] = {
        {"then_cond", "else_cond", "then_stmt", "else_stmt"},
        {},
        {"have_else_part", "have_else_cond"}
    };
    allowed_confs["code_switch"] = {
        {"expr"}, {"case"}, {}
    };
    allowed_confs["code_switch_cases"] = {
        {}, {"case", "stmt"}, {}
    };
    allowed_confs["code_switch_cases_oneline"] = {
        {"stmt"}, {"case"}, {}
    };
    allowed_confs["code_switch_case_single"] = {
        {"val"}, {}, {}
    };
    allowed_confs["code_switch_case_range"] = {
        {}, {"val"}, {}
    };
    allowed_confs["code_switch_default"] = {};
    allowed_confs["code_loop"] = {
        {}, {"stmt"}, {}
    };
    allowed_confs["code_enum"] = {
        {"name", "init"}, {"elem"}, {}
    };
    allowed_confs["code_autogen_comment"] = {
        {"version", "date"}, {}, {}
    };
    allowed_confs["code_line_directive"] = {
        {"line", "file"}, {}, {}
    };
    allowed_confs["code_abort_expr"] = {};
    allowed_confs["semicolons"] = {};
    allowed_confs["computed_goto"] = {};
    allowed_confs["case_ranges"] = {};
    allowed_confs["uppercase_constants"] = {};
    allowed_confs["char_literals_hex"] = {};
    allowed_confs["implicit_zero_to_bool_conversion"] = {};
    allowed_confs["abort_in_default_case"] = {};
    allowed_confs["skeleton"] = {};
    allowed_confs["label_indent"] = {
        {"default", "zero"}, {}, {}
    };
    allowed_confs["label_single_quote"] = {};
    allowed_confs["label_loop"] = {};

#define STX_COND(name, selector) allowed_conds[name] = [](const opt_t* opts) { return selector; };
    RE2C_STX_CONDS
#undef STX_COND

#define STX_VAR(name, selector) allowed_vars.insert(name);
    RE2C_STX_VARS
#undef STX_VAR
}

Ret Stx::check_conf(const char* conf) const {
    if (allowed_confs.find(conf) != allowed_confs.end()) return Ret::OK;
    RET_FAIL(error("unknown configuration '%s'", conf));
}

Ret Stx::check_cond(const char* conf, const char* cond) const {
    // is this a global conditional?
    if (allowed_conds.find(cond) != allowed_conds.end()) return Ret::OK;

    // is this a known configuration-specific conditional?
    auto i = allowed_confs.find(conf);
    CHECK(i != allowed_confs.end());
    const std::vector<std::string>& conds = i->second.cond_vars;
    if (std::find(conds.begin(), conds.end(), cond) != conds.end()) return Ret::OK;

    RET_FAIL(error("unknown conditional '%s' in configuration '%s'", cond, conf));
}

Ret Stx::check_var(const char* conf, const char* var) const {
    // is this a global variable?
    if (allowed_vars.find(var) != allowed_vars.end()) return Ret::OK;

    // is this a known configuration-specific variable?
    auto i = allowed_confs.find(conf);
    CHECK(i != allowed_confs.end());

    // check non-list variables first
    const std::vector<std::string>& v = i->second.vars;
    if (std::find(v.begin(), v.end(), var) != v.end()) return Ret::OK;

    // this may be a list var; in that case it must be on the list stack
    const std::vector<std::string>& lv = i->second.list_vars;
    for (const StxCode* x : stack_code_list) {
        if (strcmp(var, x->list.var) == 0) {
            if (std::find(lv.begin(), lv.end(), var) != lv.end()) return Ret::OK;
        }
    }

    RET_FAIL(error("unknown variable '%s' in configuration '%s'", var, conf));
}

// validate that all option names used in the given expression do exist
Ret Stx::validate_conf_expr(const StxConf* conf) {
    CHECK(conf->type == StxConfType::EXPR);
    CHECK_RET(check_conf(conf->name));

    stack_expr_t& stack = stack_expr;
    stack.clear();
    stack.push_back({conf->expr, 0});

    while (!stack.empty()) {
        const StxExpr* e = stack.back().first;
        uint8_t n = stack.back().second;
        stack.pop_back();

        switch (e->type) {
        case StxExprType::NAME:
            CHECK_RET(check_var(conf->name, e->name));
            break;
        case StxExprType::COND:
            if (n == 0) { // recurse into branches
                stack.push_back({e, 1});
                stack.push_back({e->cond.then_expr, 0});
                stack.push_back({e->cond.else_expr, 0});
            } else { // check conditional name and return
                CHECK_RET(check_cond(conf->name, e->cond.conf));
            }
            break;
        }
    }

    return Ret::OK;
}

// validate that all option names used in the given list do exist
Ret Stx::validate_conf_list(const StxConf* conf) {
    CHECK(conf->type == StxConfType::LIST);
    CHECK_RET(check_conf(conf->name));

    for (const StxName* x = conf->list->head; x != nullptr; x = x->next) {
        CHECK_RET(check_var(conf->name, x->name));
    }

    return Ret::OK;
}

// validate that all option and variable names used in the given code do exist
Ret Stx::validate_conf_code(const StxConf* conf) {
    CHECK(conf->type == StxConfType::CODE);
    CHECK_RET(check_conf(conf->name));

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
                CHECK_RET(check_cond(conf->name, x->cond.conf));
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

StxFile::StxFile(const std::string& fname, Msg& msg, OutAllocator& alc)
    : alc(alc)
    , fname(fname)
    , file(nullptr)
    , flen(0)
    , buf(nullptr)
    , cur(nullptr)
    , tok(nullptr)
    , pos(nullptr)
    , loc({1, 0, 0}) // file index 0 is reserved for syntax file
    , msg(msg)
{}

StxFile::~StxFile() {
    delete[] buf;
    if (file) fclose(file);
}

Ret StxFile::read() {
    msg.filenames.push_back(fname);

    file = fopen(fname.c_str(), "rb");
    if (!file) RET_FAIL(error("cannot open syntax file '%s'", fname.c_str()));

    // get file size
    fseek(file, 0, SEEK_END);
    flen = static_cast<size_t>(ftell(file));
    fseek(file, 0, SEEK_SET);

    // allocate buffer
    buf = new uint8_t[flen + 1];

    // read file contents into buffer and append terminating zero at the end
    if (fread(buf, 1, flen, file) != flen) {
        RET_FAIL(error("cannot read syntax file '%s'", fname.c_str()));
    }
    buf[flen] = 0;

    cur = tok = pos = buf;
    return Ret::OK;
}

Ret load_syntax_config(const std::string& fname, Msg& msg, OutAllocator& alc, Stx& stx) {
    StxFile sf(fname, msg, alc);
    CHECK_RET(sf.read());
    CHECK_RET(sf.parse(stx));
    return Ret::OK;
}

} // namespace re2c
