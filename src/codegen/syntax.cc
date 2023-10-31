#include <stdio.h>

#include "src/codegen/syntax.h"
#include "src/msg/msg.h"

namespace re2c {

// validate that all option names used in the given boolean configuration do exist
Ret Stx::validate_bool_conf(const StxConf* conf) {
    CHECK(conf->type == StxConfType::BOOL);

    stack1_t& stack = stack1;
    stack.clear();
    stack.push_back({conf->bln, 0});

    while (!stack.empty()) {
        const StxBool* b = stack.back().first;
        uint8_t n = stack.back().second;
        stack.pop_back();

        switch (b->type) {
        case StxBoolType::NUM:
            // no option names to check here
            break;
        case StxBoolType::COND:
            if (n == 0) { // recurse into branches
                stack.push_back({b, 1});
                stack.push_back({b->cond.then_bool, 0});
                stack.push_back({b->cond.else_bool, 0});
            } else { // check conditional name and return
                if (bool_confs.find(b->cond.conf) == bool_confs.end()) {
                    RET_FAIL(error("unknown conditional name '%s' in configuration '%s'",
                            b->cond.conf, conf->name));
                }
            }
            break;
        }
    }

    return Ret::OK;
}

// validate that all option and variable names used in the given expression do exist
Ret Stx::validate_expr_conf(const StxConf* conf) {
    CHECK(conf->type == StxConfType::EXPR);

    stack2_t& stack = stack2;
    stack.clear();
    for (const StxExpr* e = conf->expr->head; e != nullptr; e = e->next) {
        stack.push_back({e, 0});
    }

    while (!stack.empty()) {
        const StxExpr* x = stack.back().first;
        uint8_t n = stack.back().second;
        stack.pop_back();

        switch (x->type) {
        case StxExprType::STR:
            // no option names to check here
            break;
        case StxExprType::VAR: {
            // check variable name
            const std::vector<std::string>& vars = conf2vars[conf->name];
            if (std::find(vars.cbegin(), vars.cend(), x->var.name) == vars.end()) {
                RET_FAIL(error("unknown variable name '%s' in configuration '%s'",
                        x->var.name, conf->name));
            }
            break;
        }
        case StxExprType::COND:
            if (n == 0) { // recurse into branches
                stack.push_back({x, 1});
                for (const StxExpr* e = x->cond.then_expr->head; e != nullptr; e = e->next) {
                    stack.push_back({e, 0});
                }
                if (x->cond.else_expr != nullptr) {
                    for (const StxExpr* e = x->cond.else_expr->head; e != nullptr; e = e->next) {
                        stack.push_back({e, 0});
                    }
                }
            } else { // check conditional name and return
                if (bool_confs.find(x->cond.conf) == bool_confs.end()) {
                    RET_FAIL(error("unknown conditional name '%s' in configuration '%s'",
                            x->cond.conf, conf->name));
                }
            }
            break;
        case StxExprType::LIST:
            if (n == 0) { // recurse into list body
                stack.push_back({x, 1});
                for (const StxExpr* e = x->list.expr->head; e != nullptr; e = e->next) {
                    stack.push_back({e, 0});
                }
            } else { // check variable name and return
                const std::vector<std::string>& vars = conf2vars[conf->name];
                if (std::find(vars.cbegin(), vars.cend(), x->list.var) == vars.end()) {
                    RET_FAIL(error("unknown variable name '%s' in configuration '%s'",
                            x->list.var, conf->name));
                }
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
