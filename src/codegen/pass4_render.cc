#include <time.h>

#include "config.h"
#include "src/codegen/helpers.h"
#include "src/codegen/output.h"
#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/options/syntax.h"
#include "src/util/check.h"
#include "src/util/file_utils.h"

namespace re2c {

static void render(RenderContext& rctx, const Code* code);

static bool oneline_stmt_list(const CodeList* list) {
    const Code* head = list->head;
    return head != nullptr
            && head->next == nullptr
            && (head->kind == CodeKind::STMT
                    || head->kind == CodeKind::TEXT
                    || head->kind == CodeKind::FNCALL);
}

static void render_nl(RenderContext& rctx) {
    if (!rctx.oneline_mode) {
        rctx.os << std::endl;
        ++rctx.line;
    }
}

template<typename Elem>
static inline void find_list_bounds(
        const Elem* head, size_t lbound, size_t rbound, const Elem** curr, const Elem** last) {
    const Elem* e = head;
    size_t i = 0;

    for (; i < lbound; ++i) e = e->next;
    *curr = e;

    for (; i <= rbound; ++i) e = e->next;
    *last = e;
}

static void render_global_var(RenderContext& rctx, const char* var) {
    if (strcmp(var, "nl") == 0) {
        render_nl(rctx);
    } else if (strcmp(var, "topindent") == 0) {
        rctx.os << indent(rctx.ind, rctx.opts->indent_str);
    } else if (strcmp(var, "indent") == 0) {
        ++rctx.ind;
    } else if (strcmp(var, "dedent") == 0) {
        DCHECK(rctx.ind > 0);
        --rctx.ind;
    } else {
        UNREACHABLE();
    }
}

class RenderSimple : public RenderCallback {
    RenderContext& rctx;

  public:
    RenderSimple(RenderContext& rctx): rctx(rctx) {}

    virtual void render_var(const char* var) {
        render_global_var(rctx, var);
    }
};

static uint32_t count_lines_text(const char* text) {
    DCHECK(text);
    uint32_t lc = 0;
    for (const char* s = text; *s; ++s) {
        if (*s == '\n') ++lc;
    }
    return lc;
}

static inline void render_stmt_end(RenderContext& rctx, bool semi) {
    if (semi && rctx.opts->eval_bool_conf("semicolons")) rctx.os << ";";
    render_nl(rctx);
}

static void render_maybe_oneline(RenderContext& rctx, const Code* code, bool oneline) {
    // backup mode and indent
    bool mode = rctx.oneline_mode;
    uint32_t ind = rctx.ind;

    rctx.oneline_mode = oneline;
    rctx.ind = oneline ? 0 : rctx.ind;

    render(rctx, code);

    // restore mode and indent
    rctx.oneline_mode = mode;
    rctx.ind = ind;
}

static void render_list(RenderContext& rctx, const CodeList* code) {
    for (const Code* s = code->head; s; s = s->next) {
        render(rctx, s);
    }
}

static void render_block(RenderContext& rctx, const CodeBlock* code) {
    switch (code->kind) {
    case CodeBlock::Kind::WRAPPED:
        rctx.os << indent(rctx.ind, rctx.opts->indent_str) << "{" << std::endl;
        ++rctx.line;
        ++rctx.ind;
        render_list(rctx, code->stmts);
        --rctx.ind;
        rctx.os << indent(rctx.ind, rctx.opts->indent_str) << "}" << std::endl;
        ++rctx.line;
        break;
    case CodeBlock::Kind::INDENTED:
        ++rctx.ind;
        render_list(rctx, code->stmts);
        --rctx.ind;
        break;
    case CodeBlock::Kind::RAW:
        render_list(rctx, code->stmts);
        break;
    }
}

class RenderVar : public RenderCallback {
    RenderContext& rctx;
    const CodeVar* code;

  public:
    RenderVar(RenderContext& rctx, const CodeVar* code): rctx(rctx), code(code) {}

    void render_var(const char* var) override {
        if (strcmp(var, "name") == 0) {
            rctx.os << code->name;
        } else if (strcmp(var, "init") == 0) {
            rctx.os << code->init;
        } else if (strcmp(var, "type") == 0) {
            switch (code->type) {
            case VarType::INT:
                rctx.opts->eval_code_conf(rctx.os, "code:type_int");
                break;
            case VarType::UINT:
                rctx.opts->eval_code_conf(rctx.os, "code:type_uint");
                break;
            case VarType::YYCTYPE:
                rctx.os << rctx.opts->api_char_type;
            }
        } else {
            render_global_var(rctx, var);
        }
    }

    bool eval_cond(StxLOpt opt) override {
        if (opt == StxLOpt::HAVE_INIT) {
            return code->init != nullptr;
        }
        UNREACHABLE();
        return false;
    }

    FORBID_COPY(RenderVar);
};

class RenderIfThenElse : public RenderCallback {
    RenderContext& rctx;
    const CodeBranches* code;
    const CodeBranch* curr_branch;
    const CodeBranch* last_branch;
    size_t nbranches;
    const Code* curr_stmt;
    const Code* last_stmt;
    size_t nstmts;
    bool oneline;

  public:
    RenderIfThenElse(RenderContext& rctx, const CodeBranches* code, bool oneline)
            : rctx(rctx)
            , code(code)
            , curr_branch(nullptr)
            , last_branch(nullptr)
            , nbranches(0)
            , curr_stmt(nullptr)
            , last_stmt(nullptr)
            , nstmts(0)
            , oneline(oneline) {
        for (const CodeBranch* b = code->head; b; b = b->next) ++nbranches;
    }

    void render_var(const char* var) override {
        if (strcmp(var, "cond") == 0) {
            rctx.os << curr_branch->cond;
        } else if (strcmp(var, "stmt") == 0) {
            render_maybe_oneline(rctx, curr_stmt, oneline);
        } else {
            render_global_var(rctx, var);
        }
    }

    size_t get_list_size(const char* var) const override {
        if (strcmp(var, "branch") == 0) {
            return nbranches;
        } else if (strcmp(var, "stmt") == 0) {
            size_t n = 0;
            if (curr_branch->code != nullptr) {
                for (const Code* s = curr_branch->code->head; s; s = s->next) ++n;
            }
            const_cast<size_t&>(nstmts) = n;
            return nstmts;
        }
        UNREACHABLE();
        return 0;
    }

    void start_list(const char* var, size_t lbound, size_t rbound) override {
        if (strcmp(var, "branch") == 0) {
            DCHECK(rbound < nbranches);
            find_list_bounds(code->head, lbound, rbound, &curr_branch, &last_branch);
        } else if (strcmp(var, "stmt") == 0) {
            DCHECK(rbound < nstmts);
            find_list_bounds(curr_branch->code->head, lbound, rbound, &curr_stmt, &last_stmt);
        } else {
            UNREACHABLE();
        }
    }

    bool next_in_list(const char* var) override {
        if (strcmp(var, "branch") == 0) {
            curr_branch = curr_branch->next;
            return curr_branch != last_branch;
        } else if (strcmp(var, "stmt") == 0) {
            curr_stmt = curr_stmt->next;
            return curr_stmt != last_stmt;
        }
        UNREACHABLE();
        return false;
    }

    bool eval_cond(StxLOpt opt) override {
        if (opt == StxLOpt::HAVE_COND) {
            return curr_branch->cond != nullptr;
        }
        UNREACHABLE();
        return false;
    }

    FORBID_COPY(RenderIfThenElse);
};

class RenderSwitchCaseDefault : public RenderCallback {
    RenderContext& rctx;

  public:
    RenderSwitchCaseDefault(RenderContext& rctx): rctx(rctx) {}

    void render_var(const char* var) override {
        render_global_var(rctx, var);
    }
};

class RenderSwitchCaseRange : public RenderCallback {
    RenderContext& rctx;
    const CodeCase* code;
    size_t curr_range;
    size_t curr_sym;
    size_t last_sym;
    size_t nsyms;

  public:
    RenderSwitchCaseRange(RenderContext& rctx, const CodeCase* code, size_t nrange)
            : rctx(rctx)
            , code(code)
            , curr_range(nrange)
            , curr_sym(0)
            , last_sym(0)
            , nsyms(1) {
        if (code->kind == CodeCase::Kind::RANGES) {
            const int64_t* ranges = code->ranges->elems;
            nsyms = static_cast<size_t>(ranges[2*curr_range + 1] - ranges[2*curr_range]);
        }
    }

    void render_var(const char* var) override {
        if (strcmp(var, "val") == 0) {
            switch (code->kind) {
            case CodeCase::Kind::DEFAULT:
                UNREACHABLE();
                break;
            case CodeCase::Kind::NUMBER:
                rctx.os << code->number;
                break;
            case CodeCase::Kind::STRING:
                rctx.os << code->string;
                break;
            case CodeCase::Kind::RANGES: {
                DCHECK(curr_range < code->ranges->size && curr_sym < nsyms);
                int64_t sym = code->ranges->elems[2*curr_range] + static_cast<int64_t>(curr_sym);
                switch (code->ranges->type) {
                case VarType::UINT:
                    DCHECK(sym >= 0);
                    // fallthrough
                case VarType::INT:
                    rctx.os << sym;
                    break;
                case VarType::YYCTYPE:
                    DCHECK(sym >= 0);
                    print_char_or_hex(rctx.os, static_cast<uint32_t>(sym), rctx.opts);
                    break;
                }
                break;
            }}
        } else {
            render_global_var(rctx, var);
        }
    }

    size_t get_list_size(const char* var) const override {
        if (strcmp(var, "val") == 0) {
            return nsyms;
        }
        UNREACHABLE();
        return 0;
    }

    void start_list(const char* var, size_t lbound, size_t rbound) override {
        if (strcmp(var, "val") == 0) {
            curr_sym = lbound;
            last_sym = rbound;
        } else {
            UNREACHABLE();
        }
    }

    bool next_in_list(const char* var) override {
        if (strcmp(var, "val") == 0) {
            return ++curr_sym <= last_sym;
        }
        UNREACHABLE();
        return false;
    }

    bool eval_cond(StxLOpt opt) override {
        if (opt == StxLOpt::MULTIVAL) {
            return nsyms > 1;
        }
        UNREACHABLE();
        return false;
    }

    FORBID_COPY(RenderSwitchCaseRange);
};

class RenderSwitchCaseBlock : public RenderCallback {
    RenderContext& rctx;
    const CodeCase* code;
    const Code* curr_stmt;
    const Code* last_stmt;
    size_t nstmt;
    size_t curr_range;
    size_t last_range;
    size_t nranges;
    bool oneline;

  public:
    RenderSwitchCaseBlock(RenderContext& rctx, const CodeCase* code, bool oneline)
            : rctx(rctx)
            , code(code)
            , curr_stmt(nullptr)
            , last_stmt(nullptr)
            , nstmt(0)
            , curr_range(0)
            , last_range(0)
            , nranges(code->kind == CodeCase::Kind::RANGES ? code->ranges->size : 1)
            , oneline(oneline) {
        for (const Code* s = code->body->head; s; s = s->next) ++nstmt;
    }

    void render_var(const char* var) override {
        if (strcmp(var, "case") == 0) {
            switch (code->kind) {
            case CodeCase::Kind::DEFAULT: {
                RenderSwitchCaseDefault callback(rctx);
                rctx.opts->eval_code_conf(rctx.os, "code:switch_case_default", callback);
                break;
            }
            case CodeCase::Kind::NUMBER:
            case CodeCase::Kind::STRING:
            case CodeCase::Kind::RANGES: {
                RenderSwitchCaseRange callback(rctx, code, curr_range);
                rctx.opts->eval_code_conf(rctx.os, "code:switch_case_range", callback);
                break;
            }}
        } else if (strcmp(var, "stmt") == 0) {
            render_maybe_oneline(rctx, curr_stmt, oneline);
        } else {
            render_global_var(rctx, var);
        }
    }

    size_t get_list_size(const char* var) const override {
        if (strcmp(var, "case") == 0) {
            return nranges;
        } else if (strcmp(var, "stmt") == 0) {
            return nstmt;
        }
        UNREACHABLE();
        return 0;
    }

    void start_list(const char* var, size_t lbound, size_t rbound) override {
        if (strcmp(var, "case") == 0) {
            curr_range = lbound;
            last_range = rbound;
        } else if (strcmp(var, "stmt") == 0) {
            DCHECK(rbound < nstmt);
            find_list_bounds(code->body->head, lbound, rbound, &curr_stmt, &last_stmt);
        } else {
            UNREACHABLE();
        }
    }

    bool next_in_list(const char* var) override {
        if (strcmp(var, "case") == 0) {
            return code->kind == CodeCase::Kind::RANGES && ++curr_range <= last_range;
        } else if (strcmp(var, "stmt") == 0) {
            curr_stmt = curr_stmt->next;
            return curr_stmt != last_stmt;
        }
        UNREACHABLE();
        return false;
    }

    FORBID_COPY(RenderSwitchCaseBlock);
};

class RenderSwitch : public RenderCallback {
    RenderContext& rctx;
    const CodeSwitch* code;
    const CodeCase* curr_case;
    const CodeCase* last_case;
    size_t ncases;

  public:
    RenderSwitch(RenderContext& rctx, const CodeSwitch* code)
            : rctx(rctx)
            , code(code)
            , curr_case(nullptr)
            , last_case(nullptr)
            , ncases(0) {
        for (const CodeCase* c = code->cases->head; c; c = c->next) ++ncases;
    }

    void render_var(const char* var) override {
        if (strcmp(var, "expr") == 0) {
            rctx.os << code->expr;
        } else if (strcmp(var, "case") == 0) {
            bool oneline = rctx.opts->specialize_oneline_switch()
                    && oneline_stmt_list(curr_case->body);
            const char* conf = oneline ? "code:switch_cases_oneline" : "code:switch_cases";
            RenderSwitchCaseBlock callback(rctx, curr_case, oneline);
            rctx.opts->eval_code_conf(rctx.os, conf, callback);
        } else {
            render_global_var(rctx, var);
        }
    }

    size_t get_list_size(const char* var) const override {
        if (strcmp(var, "case") == 0) {
            return ncases;
        }
        UNREACHABLE();
        return 0;
    }

    void start_list(const char* var, size_t lbound, size_t rbound) override {
        if (strcmp(var, "case") == 0) {
            DCHECK(rbound < ncases);
            find_list_bounds(code->cases->head, lbound, rbound, &curr_case, &last_case);
        } else {
            UNREACHABLE();
        }
    }

    bool next_in_list(const char* var) override {
        if (strcmp(var, "case") == 0) {
            curr_case = curr_case->next;
            return curr_case != last_case;
        }
        UNREACHABLE();
        return false;
    }

    FORBID_COPY(RenderSwitch);
};

class RenderLoop : public RenderCallback {
    RenderContext& rctx;
    const CodeList* code;
    const Code* curr_stmt;
    const Code* last_stmt;
    size_t nstmts;

  public:
    RenderLoop(RenderContext& rctx, const CodeList* code)
            : rctx(rctx), code(code), curr_stmt(nullptr), last_stmt(nullptr), nstmts(0) {
        for (const Code* s = code->head; s; s = s->next) ++nstmts;
    }

    void render_var(const char* var) override {
        if (strcmp(var, "label") == 0) {
            rctx.os << rctx.opts->label_loop;
        } else if (strcmp(var, "stmt") == 0) {
            render(rctx, curr_stmt);
        } else {
            render_global_var(rctx, var);
        }
    }

    size_t get_list_size(const char* var) const override {
        if (strcmp(var, "stmt") == 0) {
            return nstmts;
        }
        UNREACHABLE();
        return 0;
    }

    void start_list(const char* var, size_t lbound, size_t rbound) override {
        if (strcmp(var, "stmt") == 0) {
            DCHECK(rbound < nstmts);
            find_list_bounds(code->head, lbound, rbound, &curr_stmt, &last_stmt);
        } else {
            UNREACHABLE();
        }
    }

    bool next_in_list(const char* var) override {
        if (strcmp(var, "stmt") == 0) {
            curr_stmt = curr_stmt->next;
            return curr_stmt != last_stmt;
        }
        UNREACHABLE();
        return false;
    }

    FORBID_COPY(RenderLoop);
};

class RenderFnDef : public RenderCallback {
    RenderContext& rctx;
    const CodeFnDef* code;
    const CodeParam* curr_arg;
    const CodeParam* last_arg;
    size_t nargs;
    const Code* curr_stmt;
    const Code* last_stmt;
    size_t nstmts;

  public:
    RenderFnDef(RenderContext& rctx, const CodeFnDef* code)
            : rctx(rctx)
            , code(code)
            , curr_arg(nullptr)
            , last_arg(nullptr)
            , nargs(0)
            , curr_stmt(nullptr)
            , last_stmt(nullptr)
            , nstmts(0) {
        for (const CodeParam* p = code->params->head; p; p = p->next) ++nargs;
        for (const Code* s = code->body->head; s; s = s->next) ++nstmts;
    }

    void render_var(const char* var) override {
        if (strcmp(var, "name") == 0) {
            rctx.os << code->name;
        } else if (strcmp(var, "type") == 0) {
            rctx.os << code->type;
        } else if (strcmp(var, "argname") == 0) {
            rctx.os << curr_arg->name;
        } else if (strcmp(var, "argtype") == 0) {
            rctx.os << curr_arg->type;
        } else if (strcmp(var, "argmods") == 0) {
            DCHECK(curr_arg->mods != nullptr) ;
            rctx.os << curr_arg->mods;
        } else if (strcmp(var, "stmt") == 0) {
            render(rctx, curr_stmt);
        } else {
            render_global_var(rctx, var);
        }
    }

    size_t get_list_size(const char* var) const override {
        if (strcmp(var, "arg") == 0) {
            return nargs;
        } else if (strcmp(var, "stmt") == 0) {
            return nstmts;
        }
        UNREACHABLE();
        return 0;
    }

    void start_list(const char* var, size_t lbound, size_t rbound) override {
        if (strcmp(var, "arg") == 0) {
            DCHECK(rbound < nargs);
            find_list_bounds(code->params->head, lbound, rbound, &curr_arg, &last_arg);
        } else if (strcmp(var, "stmt") == 0) {
            DCHECK(rbound < nstmts);
            find_list_bounds(code->body->head, lbound, rbound, &curr_stmt, &last_stmt);
        } else {
            UNREACHABLE();
        }
    }

    bool next_in_list(const char* var) override {
        if (strcmp(var, "arg") == 0) {
            curr_arg = curr_arg->next;
            return curr_arg != last_arg;
        } else if (strcmp(var, "stmt") == 0) {
            curr_stmt = curr_stmt->next;
            return curr_stmt != last_stmt;
        }
        UNREACHABLE();
        return false;
    }

    bool eval_cond(StxLOpt opt) override {
        switch (opt) {
        case StxLOpt::HAVE_TYPE:
            return code->type != nullptr;
        case StxLOpt::HAVE_ARGMODS:
            return curr_arg->mods != nullptr;
        default:
            UNREACHABLE();
            return false;
        }
    }

    FORBID_COPY(RenderFnDef);
};

class RenderFnCall : public RenderCallback {
    RenderContext& rctx;
    const CodeFnCall* code;
    const CodeArg* curr_arg;
    const CodeArg* last_arg;
    size_t nargs;

  public:
    RenderFnCall(RenderContext& rctx, const CodeFnCall* code)
            : rctx(rctx)
            , code(code)
            , curr_arg(nullptr)
            , last_arg(nullptr)
            , nargs(0) {
        for (const CodeArg* a = code->args->head; a; a = a->next) ++nargs;
    }

    void render_var(const char* var) override {
        if (strcmp(var, "name") == 0) {
            rctx.os << code->name;
        } else if (strcmp(var, "retval") == 0) {
            rctx.os << code->retval;
        } else if (strcmp(var, "arg") == 0) {
            rctx.os << curr_arg->arg;
        } else {
            render_global_var(rctx, var);
        }
    }

    size_t get_list_size(const char* var) const override {
        if (strcmp(var, "arg") == 0) {
            return nargs;
        }
        UNREACHABLE();
        return 0;
    }

    void start_list(const char* var, size_t lbound, size_t rbound) override {
        if (strcmp(var, "arg") == 0) {
            DCHECK(rbound < nargs);
            find_list_bounds(code->args->head, lbound, rbound, &curr_arg, &last_arg);
        } else {
            UNREACHABLE();
        }
    }

    bool next_in_list(const char* var) override {
        if (strcmp(var, "arg") == 0) {
            curr_arg = curr_arg->next;
            return curr_arg != last_arg;
        }
        UNREACHABLE();
        return false;
    }

    bool eval_cond(StxLOpt opt) override {
        switch (opt) {
        case StxLOpt::HAVE_ARGS:
            return nargs > 0;
        case StxLOpt::HAVE_RETVAL:
            return code->retval != nullptr;
        default:
            UNREACHABLE();
            return false;
        }
    }

    FORBID_COPY(RenderFnCall);
};

class RenderRecFuncs : public RenderCallback {
    RenderContext& rctx;
    const CodeList* fns;
    const Code* curr_fn;
    const Code* last_fn;
    size_t nfuncs;

  public:
    RenderRecFuncs(RenderContext& rctx, const CodeList* fns)
            : rctx(rctx)
            , fns(fns)
            , curr_fn(nullptr)
            , last_fn(nullptr)
            , nfuncs(0) {
        for (const Code* x = fns->head; x; x = x->next) ++nfuncs;
    }

    void render_var(const char* var) override {
        if (strcmp(var, "fndecl") == 0) {
            RenderFnDef callback(rctx, &curr_fn->fndef);
            rctx.opts->eval_code_conf(rctx.os, "code:fndecl", callback);
        } else if (strcmp(var, "fndef") == 0) {
            RenderFnDef callback(rctx, &curr_fn->fndef);
            rctx.opts->eval_code_conf(rctx.os, "code:fndef", callback);
        } else {
            render_global_var(rctx, var);
        }
    }

    size_t get_list_size(const char* var) const override {
        if (strcmp(var, "fn") == 0) {
            return nfuncs;
        }
        UNREACHABLE();
        return 0;
    }

    void start_list(const char* var, size_t lbound, size_t rbound) override {
        if (strcmp(var, "fn") == 0) {
            DCHECK(rbound < nfuncs);
            find_list_bounds(fns->head, lbound, rbound, &curr_fn, &last_fn);
        } else {
            UNREACHABLE();
        }
    }

    bool next_in_list(const char* var) override {
        if (strcmp(var, "fn") == 0) {
            curr_fn = curr_fn->next;
            return curr_fn != last_fn;
        }
        UNREACHABLE();
        return false;
    }

    FORBID_COPY(RenderRecFuncs);
};

static inline void yych_conv(std::ostream& os, const opt_t* opts) {
    if (opts->char_conv) {
        os << "(" <<  opts->api_char_type << ")";
    }
}

class RenderAccept : public RenderCallback {
    RenderContext& rctx;
    uint32_t accept;

  public:
    RenderAccept(RenderContext& rctx, uint32_t accept): rctx(rctx), accept(accept) {}

    void render_var(const char* var) override {
        if (strcmp(var, "var") == 0) {
            rctx.os << rctx.opts->var_accept;
        } else if (strcmp(var, "num") == 0) {
            rctx.os << accept;
        } else {
            render_global_var(rctx, var);
        }
    }
};

class RenderDebug : public RenderCallback {
    RenderContext& rctx;
    const CodeDebug* code;

  public:
    RenderDebug(RenderContext& rctx, const CodeDebug* code): rctx(rctx), code(code) {}

    void render_var(const char* var) override {
        if (strcmp(var, "debug") == 0) {
            rctx.os << rctx.opts->api_debug;
        } else if (strcmp(var, "state") == 0) {
            rctx.os << code->state;
        } else if (strcmp(var, "char") == 0) {
            rctx.os << rctx.opts->var_char;
        } else {
            render_global_var(rctx, var);
        }
    }

    FORBID_COPY(RenderDebug);
};

// One callback class is used for all combinations of YYSKIP, YYPEEK and YYBACKUP primitives,
// as they all have very similar variables. This should not cause variable misuse, as the variables
// for each configuration are checked after parsing syntax file.
class RenderSkipPeekBackup : public RenderCallback {
    RenderContext& rctx;

  public:
    RenderSkipPeekBackup(RenderContext& rctx): rctx(rctx) {}

    void render_var(const char* var) override {
        if (strcmp(var, "char") == 0) {
            rctx.os << rctx.opts->var_char;
        } else if (strcmp(var, "ctype") == 0) {
            rctx.os << rctx.opts->api_char_type;
        } else if (strcmp(var, "cursor") == 0) {
            rctx.os << rctx.opts->api_cursor;
        } else if (strcmp(var, "marker") == 0) {
            rctx.os << rctx.opts->api_marker;
        } else if (strcmp(var, "typecast") == 0) {
            yych_conv(rctx.os, rctx.opts);
        } else if (strcmp(var, "peek") == 0) {
            rctx.os << rctx.opts->api_peek;
        } else if (strcmp(var, "skip") == 0) {
            rctx.os << rctx.opts->api_skip;
        } else if (strcmp(var, "backup") == 0) {
            rctx.os << rctx.opts->api_backup;
        } else {
            render_global_var(rctx, var);
        }
    }
};

static void render_label(RenderContext& rctx, const CodeLabel& label) {
    if (label.kind == CodeLabel::Kind::SLABEL) {
        rctx.os << label.slabel << ":" << std::endl;
        ++rctx.line;
    } else if (label.nlabel->used) {
        DCHECK(label.nlabel->index != Label::NONE);
        rctx.os << rctx.opts->label_prefix << label.nlabel->index << ":" << std::endl;
        ++rctx.line;
    }
}

class RenderArray : public RenderCallback {
    RenderContext& rctx;
    const CodeArray* code;
    const size_t ncols;
    const size_t nrows;
    size_t curr_col;
    size_t last_col;
    size_t curr_row;
    size_t last_row;
    size_t maxlen;

  public:
    RenderArray(RenderContext& rctx, const CodeArray* code)
            : rctx(rctx)
            , code(code)
            , ncols(code->tabulate ? 8 : 1)
            , nrows(code->size / ncols)
            , curr_col(0)
            , last_col(0)
            , curr_row(0)
            , last_row(0)
            , maxlen(0) {
        CHECK(nrows * ncols == code->size);

        for (size_t i = 0; i < code->size; ++i) {
            maxlen = std::max(maxlen, strlen(code->elems[i]));
        }
    }

    void render_var(const char* var) override {
        if (strcmp(var, "name") == 0) {
            rctx.os << code->name;
        } else if (strcmp(var, "type") == 0) {
            rctx.os << code->type;
        } else if (strcmp(var, "size") == 0) {
            rctx.os << code->size;
        } else if (strcmp(var, "row") == 0) {
            // do nothing
        } else if (strcmp(var, "elem") == 0) {
            const char* e = code->elems[curr_row * ncols + curr_col];
            if (code->tabulate) {
                rctx.os << indent(static_cast<uint32_t>(maxlen - strlen(e)), " ");
            }
            rctx.os << e;
        } else {
            render_global_var(rctx, var);
        }
    }

    size_t get_list_size(const char* var) const override {
        if (strcmp(var, "row") == 0) {
            return nrows;
        } else if (strcmp(var, "elem") == 0) {
            return ncols;
        }
        UNREACHABLE();
        return 0;
    }

    void start_list(const char* var, size_t lbound, size_t rbound) override {
        if (strcmp(var, "row") == 0) {
            DCHECK(rbound < nrows);
            curr_row = lbound;
            last_row = rbound;
        } else if (strcmp(var, "elem") == 0) {
            DCHECK(rbound < ncols);
            curr_col = lbound;
            last_col = rbound;
        } else {
            UNREACHABLE();
        }
    }

    bool next_in_list(const char* var) override {
        if (strcmp(var, "row") == 0) {
            return ++curr_row <= last_row;
        } else if (strcmp(var, "elem") == 0) {
            return ++curr_col <= last_col;
        }
        UNREACHABLE();
        return false;
    }

    FORBID_COPY(RenderArray);
};

class RenderEnum : public RenderCallback {
    RenderContext& rctx;
    const CodeEnum* code;
    size_t curr_elem;
    size_t last_elem;

  public:
    RenderEnum(RenderContext& rctx, const CodeEnum* code)
            : rctx(rctx), code(code), curr_elem(0), last_elem(0) {}

    void render_var(const char* var) override {
        if (strcmp(var, "name") == 0) {
            rctx.os << code->name;
        } else if (strcmp(var, "type") == 0) {
            rctx.opts->eval_code_conf(rctx.os, "code:type_cond_enum");
        } else if (strcmp(var, "elem") == 0) {
            rctx.os << code->elem_ids[curr_elem];
        } else if (strcmp(var, "init") == 0) {
            rctx.os << code->elem_nums[curr_elem];
        } else {
            render_global_var(rctx, var);
        }
    }

    size_t get_list_size(const char* var) const override {
        if (strcmp(var, "elem") == 0) {
            return code->size;
        }
        UNREACHABLE();
        return 0;
    }

    void start_list(const char* var, size_t lbound, size_t rbound) override {
        if (strcmp(var, "elem") == 0) {
            curr_elem = lbound;
            last_elem = rbound;
        } else {
            UNREACHABLE();
        }
    }

    bool next_in_list(const char* var) override {
        if (strcmp(var, "elem") == 0) {
            return ++curr_elem <= last_elem;
        } else {
            UNREACHABLE();
        }
        return false;
    }

    bool eval_cond(StxLOpt opt) override {
        if (opt == StxLOpt::HAVE_INIT) {
            return code->elem_nums != nullptr;
        }
        UNREACHABLE();
        return false;
    }

    FORBID_COPY(RenderEnum);
};

class RenderFingerprint : public RenderCallback {
    RenderContext& rctx;

  public:
    RenderFingerprint(RenderContext& rctx): rctx(rctx) {}

    void render_var(const char* var) override {
        if (strcmp(var, "version") == 0) {
            rctx.os << PACKAGE_VERSION;
        } else if (strcmp(var, "date") == 0) {
            time_t now = time(nullptr);
            rctx.os.write(ctime(&now), 24);
        } else {
            render_global_var(rctx, var);
        }
    }

    FORBID_COPY(RenderFingerprint);
};

class RenderLineInfo : public RenderCallback {
    RenderContext& rctx;
    uint32_t line;
    const std::string& file;

  public:
    RenderLineInfo(RenderContext& rctx, uint32_t line, const std::string& file)
            : rctx(rctx), line(line), file(file) {}

    void render_var(const char* var) override {
        if (strcmp(var, "line") == 0) {
            rctx.os << line;
        } else if (strcmp(var, "file") == 0) {
            rctx.os << file;
        } else {
            render_global_var(rctx, var);
        }
    }

    FORBID_COPY(RenderLineInfo);
};

static void render(RenderContext& rctx, const Code* code) {
    std::ostringstream& os = rctx.os;
    const opt_t* opts = rctx.opts;
    const uint32_t ind = rctx.ind;
    uint32_t& line = rctx.line;

    switch (code->kind) {
    case CodeKind::EMPTY:
        break;
    case CodeKind::IF_THEN_ELSE: {
        bool oneline = rctx.opts->specialize_oneline_if();
        for (const CodeBranch* b = code->ifte->head; oneline && b; b = b->next) {
            oneline = oneline && oneline_stmt_list(b->code);
        }
        RenderIfThenElse callback(rctx, code->ifte, oneline);
        const char* conf = oneline ? "code:if_then_else_oneline" : "code:if_then_else";
        rctx.opts->eval_code_conf(rctx.os, conf, callback);
        break;
    }
    case CodeKind::SWITCH: {
        RenderSwitch callback(rctx, &code->swch);
        rctx.opts->eval_code_conf(rctx.os, "code:switch", callback);
        break;
    }
    case CodeKind::BLOCK:
        render_block(rctx, &code->block);
        break;
    case CodeKind::FNDEF: {
        RenderFnDef callback(rctx, &code->fndef);
        rctx.opts->eval_code_conf(rctx.os, "code:fndef", callback);
        break;
    }
    case CodeKind::FNCALL: {
        RenderFnCall callback(rctx, &code->fncall);
        const char* conf = code->fncall.tailcall ? "code:tailcall" : "code:fncall";
        rctx.opts->eval_code_conf(rctx.os, conf, callback);
        break;
    }
    case CodeKind::REC_FUNCS: {
        RenderRecFuncs callback(rctx, code->rfuncs);
        rctx.opts->eval_code_conf(rctx.os, "code:recursive_functions", callback);
        break;
    }
    case CodeKind::LOOP: {
        RenderLoop callback(rctx, code->loop);
        rctx.opts->eval_code_conf(rctx.os, "code:loop", callback);
        break;
    }
    case CodeKind::TEXT_RAW:
        os << code->text << std::endl;
        line += count_lines_text(code->text) + 1;
        break;
    case CodeKind::STMT:
        os << indent(ind, opts->indent_str) << code->text;
        line += count_lines_text(code->text);
        render_stmt_end(rctx, true);
        break;
    case CodeKind::TEXT:
        os << indent(ind, opts->indent_str) << code->text;
        line += count_lines_text(code->text);
        render_stmt_end(rctx, false);
        break;
    case CodeKind::RAW:
        os.write(code->raw.data, static_cast<std::streamsize>(code->raw.size));
        for (size_t i = 0; i < code->raw.size; ++i) {
            if (code->raw.data[i] == '\n') ++line;
        }
        break;
    case CodeKind::ABORT: {
        RenderSimple callback(rctx);
        rctx.opts->eval_code_conf(rctx.os, "code:abort", callback);
        break;
    }
    case CodeKind::ACCEPT: {
        RenderAccept callback(rctx, code->accept);
        rctx.opts->eval_code_conf(rctx.os, "code:yyaccept", callback);
        break;
    }
    case CodeKind::DEBUG: {
        RenderDebug callback(rctx, &code->debug);
        rctx.opts->eval_code_conf(rctx.os, "code:yydebug", callback);
        break;
    }
    case CodeKind::SKIP: {
        RenderSkipPeekBackup callback(rctx);
        rctx.opts->eval_code_conf(rctx.os, "code:yyskip", callback);
        break;
    }
    case CodeKind::PEEK: {
        RenderSkipPeekBackup callback(rctx);
        rctx.opts->eval_code_conf(rctx.os, "code:yypeek", callback);
        break;
    }
    case CodeKind::BACKUP: {
        RenderSkipPeekBackup callback(rctx);
        rctx.opts->eval_code_conf(rctx.os, "code:yybackup", callback);
        break;
    }
    case CodeKind::PEEK_SKIP: {
        RenderSkipPeekBackup callback(rctx);
        rctx.opts->eval_code_conf(rctx.os, "code:yypeek_skip", callback);
        break;
    }
    case CodeKind::SKIP_PEEK: {
        RenderSkipPeekBackup callback(rctx);
        rctx.opts->eval_code_conf(rctx.os, "code:yyskip_peek", callback);
        break;
    }
    case CodeKind::SKIP_BACKUP: {
        RenderSkipPeekBackup callback(rctx);
        rctx.opts->eval_code_conf(rctx.os, "code:yyskip_backup", callback);
        break;
    }
    case CodeKind::BACKUP_SKIP: {
        RenderSkipPeekBackup callback(rctx);
        rctx.opts->eval_code_conf(rctx.os, "code:yybackup_skip", callback);
        break;
    }
    case CodeKind::BACKUP_PEEK: {
        RenderSkipPeekBackup callback(rctx);
        rctx.opts->eval_code_conf(rctx.os, "code:yybackup_peek", callback);
        break;
    }
    case CodeKind::BACKUP_PEEK_SKIP: {
        RenderSkipPeekBackup callback(rctx);
        rctx.opts->eval_code_conf(rctx.os, "code:yybackup_peek_skip", callback);
        break;
    }
    case CodeKind::SKIP_BACKUP_PEEK: {
        RenderSkipPeekBackup callback(rctx);
        rctx.opts->eval_code_conf(rctx.os, "code:yyskip_backup_peek", callback);
        break;
    }
    case CodeKind::LINE_INFO_INPUT: {
        RenderLineInfo callback(rctx, code->loc.line, rctx.msg.filenames[code->loc.file]);
        rctx.opts->eval_code_conf(rctx.os, "code:line_info", callback);
        break;
    }
    case CodeKind::LINE_INFO_OUTPUT: {
        RenderLineInfo callback(rctx, rctx.line + 1, rctx.file);
        rctx.opts->eval_code_conf(rctx.os, "code:line_info", callback);
        break;
    }
    case CodeKind::FINGERPRINT: {
        RenderFingerprint callback(rctx);
        rctx.opts->eval_code_conf(rctx.os, "code:fingerprint", callback);
        break;
    }
    case CodeKind::VAR: {
        RenderVar callback(rctx, &code->var);
        rctx.opts->eval_code_conf(rctx.os, "code:var", callback);
        break;
    }
    case CodeKind::CONST: {
        RenderVar callback(rctx, &code->var); // same code item as for `CodeKind::VAR`
        rctx.opts->eval_code_conf(rctx.os, "code:const", callback);
        break;
    }
    case CodeKind::ARRAY: {
        RenderArray callback(rctx, &code->array);
        rctx.opts->eval_code_conf(rctx.os, "code:array", callback);
        break;
    }
    case CodeKind::ENUM: {
        RenderEnum callback(rctx, &code->enumr);
        rctx.opts->eval_code_conf(rctx.os, "code:enum", callback);
        break;
    }
    case CodeKind::LABEL:
        render_label(rctx, code->label);
        break;
    case CodeKind::STAGS:
    case CodeKind::MTAGS:
    case CodeKind::MAXFILL:
    case CodeKind::MAXNMATCH:
    case CodeKind::COND_ENUM:
    case CodeKind::STATE_GOTO:
    case CodeKind::DFAS:
        UNREACHABLE(); // must have been expanded before
    }
}

static uint32_t write_converting_newlines(const std::string& str, FILE* f) {
    const char* s = str.c_str(), *e = s + str.length();
    uint32_t lines = 0;

    // In order to maintain consistency we convert all newlines to LF when writing output to file.
    // Some newlines originate in user-defined code (including semantic actions and code fragments
    // in configurations and directives), and some are generated by re2c itself.
    for (const char* p = s;; ++p) {
        size_t l = static_cast<size_t>(p - s);
        if (p == e) {
            fwrite(s, 1, l, f);
            break;
        } else if (*p == '\n') {
            ++lines;
            if (p > s && p[-1] == '\r') --l;
            fwrite(s, 1, l, f);
            s = p;
        }
    }

    return lines;
}

LOCAL_NODISCARD(Ret codegen_render_blocks(
        Output& output, const std::string& fname, const blocks_t& blocks)) {
    FILE* file = nullptr, *temp = nullptr;
    std::string filename = fname, tempname = fname;

    if (filename.empty()) {
        filename = "<stdout>";
        file = stdout;
    } else if ((temp = temp_file(tempname))) {
        file = temp;
    } else if (!(file = fopen(filename.c_str(), "w"))) {
        RET_FAIL(error("cannot open output file %s", filename.c_str()));
    }
    filename = escape_backslashes(filename);

    // Second code generation pass: expand labels, combine/simplify statements, convert newlines,
    // write the generated code to a file.
    RenderContext rctx(output.msg, filename);
    for (const OutputBlock* b : blocks) {
        rctx.opts = b->opts;
        rctx.ind = b->opts->indent_top;
        render_list(rctx, b->code);
    }
    write_converting_newlines(rctx.os.str(), file);

    fclose(file);
    if (temp && !overwrite_file(tempname.c_str(), fname.c_str())) {
        error("cannot rename or write temporary file %s to output file %s",
              tempname.c_str(),
              fname.c_str());
        remove(tempname.c_str());
        return Ret::FAIL;
    }
    return Ret::OK;
}

Ret codegen_render(Output& output) {
    const opt_t* opts = output.total_opts; // global options

    // Emit header file.
    if (!opts->header_file.empty() || output.need_header) {
        CHECK_RET(codegen_render_blocks(output, opts->header_file, output.hblocks));
    }

    // Emit output file.
    CHECK_RET(codegen_render_blocks(output, opts->output_file, output.cblocks));

    // Check that the rendering pass did not generate any unexpected -Werror warnings.
    CHECK(output.msg.warn.check() == Ret::OK);
    return Ret::OK;
}

} // namespace re2c
