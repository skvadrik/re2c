#include <stdio.h>
#include <iostream>

#include "src/codegen/output.h"
#include "src/codegen/syntax.h"

extern const char* DEFAULT_SYNTAX_C;
extern const char* DEFAULT_SYNTAX_GO;
extern const char* DEFAULT_SYNTAX_RUST;

namespace re2c {

Stx::Stx(OutAllocator& alc)
        : alc(alc)
        , allowed_list_confs()
        , allowed_word_confs()
        , allowed_code_confs()
        , allowed_conds()
        , allowed_vars()
        , stack_expr()
        , stack_code()
        , stack_code_list()
        , confs()
        , have_oneline_if(false)
        , have_oneline_switch(false) {
    allowed_list_confs["api"] = {"pointers", "generic"};
    allowed_list_confs["api_style"] = {"functions", "freeform"};
    allowed_list_confs["jump_model"] = {"goto_label", "loop_switch"};
    allowed_list_confs["target"] = {"code", "dot", "skeleton"};

    allowed_word_confs["computed_goto"] = {"enabled", "optional", "unsupported"};
    allowed_word_confs["case_ranges"] = {"enabled", "optional", "unsupported"};
    allowed_word_confs["constants"] = {"snake_case", "upper_case"};
    allowed_word_confs["char_literals"] = {"hexadecimal", "symbolic"};
    allowed_word_confs["semicolons"] = {"yes", "no"};
    allowed_word_confs["abort_requires_include"] = {"yes", "no"};

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
    allowed_code_confs["code:type_yybm"] = {};
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
    allowed_code_confs["code:cond_enum"] = {
        {"name", "init"}, {"elem"}, {}
    };
    allowed_code_confs["code:autogen_comment"] = {
        {"version", "date"}, {}, {}
    };
    allowed_code_confs["code:line_directive"] = {
        {"line", "file"}, {}, {}
    };
    allowed_code_confs["code:label"] = {
        {"name"}, {}, {}
    };
    allowed_code_confs["code:bitmap_check"] = {
        {"table", "offset", "char", "mask"}, {}, {}
    };
    allowed_code_confs["code:abort_expr"] = {};
    allowed_code_confs["code:yypeek_expr"] = {
        {"expr"}, {}, {}
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

// validate that all option names used in the given expression do exist
Ret Stx::validate_conf_expr(const StxConf* conf) {
    CHECK(conf->type == StxConfType::EXPR);

    if (allowed_word_confs.find(conf->name) == allowed_word_confs.end()) {
        RET_FAIL(error("unknown configuration '%s'", conf->name));
    }

    stack_expr_t& stack = stack_expr;
    stack.clear();
    stack.push_back({conf->expr, 0});

    while (!stack.empty()) {
        const StxExpr* e = stack.back().first;
        uint8_t n = stack.back().second;
        stack.pop_back();

        switch (e->type) {
        case StxExprType::NAME:
            CHECK_RET(check_word(conf->name, e->name, /*list*/ false));
            break;
        case StxExprType::COND:
            if (n == 0) { // recurse into branches
                stack.push_back({e, 1});
                stack.push_back({e->cond.then_expr, 0});
                stack.push_back({e->cond.else_expr, 0});
            } else { // check conditional name and return
                CHECK_RET(check_cond(conf->name, e->cond.conf, /*code*/ false));
            }
            break;
        }
    }

    return Ret::OK;
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

bool Stx::have_conf(const char* name) const {
    return confs.find(name) != confs.end();
}

void Stx::push_list_on_stack(const StxCode* x) {
    if (x == nullptr) return;
    push_list_on_stack(x->next);
    stack_code.push_back({x, 0});
}

bool Stx::eval_cond(const char* cond, const opt_t* opts, OutputCallback& callback) const {
    auto i = allowed_conds.find(cond);
    if (i != allowed_conds.end()) {
        return i->second(opts);
    } else {
        return callback.eval_cond(cond);
    }
}

static inline bool eval_list_bounds(size_t size, int32_t& lbound, int32_t& rbound) {
    lbound = lbound >= 0 ? lbound : (std::max(0, static_cast<int32_t>(size) + lbound));
    rbound = rbound >= 0 ? rbound : (static_cast<int32_t>(size) + rbound);
    return lbound <= rbound && rbound >= 0;
}

void Stx::gen_code(
        std::ostream& os, const opt_t* opts, const char* name, OutputCallback& callback) {
    DCHECK(confs.find(name) != confs.end());
    const StxConf* conf = confs[name];
    CHECK(conf->type == StxConfType::CODE);

    stack_code_t& stack = stack_code;
    size_t bottom = stack.size();
    push_list_on_stack(conf->code->head);

    while (stack.size() != bottom) {
        const StxCode* x = stack.back().first;
        int32_t n = stack.back().second;
        stack.pop_back();

        switch (x->type) {
        case StxCodeType::STR:
            os << x->str;
            break;
        case StxCodeType::VAR:
            // TODO: unify handling of global vars
            callback.render_var(x->var);
            break;
        case StxCodeType::COND:
            if (eval_cond(x->cond.conf, opts, callback)) {
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

void Stx::cache_conf_tests() {
    have_oneline_if = have_conf("code:if_then_oneline");
    have_oneline_switch = have_conf("code:switch_cases_oneline");
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

Ret StxFile::read(Lang lang) {
    msg.filenames.push_back(fname);

    if (fname.empty()) {
        // use the default syntax config that is provided as a string
        const char* src = nullptr;
        switch (lang) {
            case Lang::C: src = DEFAULT_SYNTAX_C; break;
            case Lang::GO: src = DEFAULT_SYNTAX_GO; break;
            case Lang::RUST: src = DEFAULT_SYNTAX_RUST; break;
        }
        flen = strlen(src);

        // allocate buffer
        buf = new uint8_t[flen + 1];

        // fill in buffer from the config string
        memcpy(buf, src, flen);
        buf[flen] = 0;
    } else {
        // use the provided syntax file
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
    }

    cur = tok = pos = buf;
    return Ret::OK;
}

Ret load_syntax_config(const std::string& fname, Msg& msg, OutAllocator& alc, Stx& stx, Lang lang) {
    StxFile sf(fname, msg, alc);
    CHECK_RET(sf.read(lang));
    CHECK_RET(sf.parse(stx));

    stx.cache_conf_tests();

    return Ret::OK;
}

} // namespace re2c
