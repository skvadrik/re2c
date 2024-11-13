#include <time.h>

#include "config.h"
#include "src/codegen/helpers.h"
#include "src/codegen/output.h"
#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/util/check.h"
#include "src/util/file_utils.h"

namespace re2c {

namespace {

static void render(RenderContext& rctx, const Code* code);

static bool oneline_stmt_list(const CodeList* list) {
    static const std::unordered_set<CodeKind> oneliners {
        CodeKind::STMT,
        CodeKind::TEXT,
#define ONELINE_CODE(name, kind) kind,
        RE2C_ONELINE_CODES
#undef ONELINE_CODE
    };

    return list->head != nullptr
            && list->head->next == nullptr
            && oneliners.find(list->head->kind) != oneliners.end();
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

static void render_global_var(RenderContext& rctx, StxVarId var) {
    switch (var) {
    case StxVarId::NEWLINE:
        render_nl(rctx);
        break;
    case StxVarId::INDENT:
        ++rctx.ind;
        break;
    case StxVarId::DEDENT:
        DCHECK(rctx.ind > 0);
        --rctx.ind;
        break;
    case StxVarId::TOPINDENT:
        rctx.os << indent(rctx.ind, rctx.opts->indent_str);
        break;
    default:
        UNREACHABLE();
        break;
    }
}

class RenderSimple : public RenderCallback {
    RenderContext& rctx;

  public:
    RenderSimple(RenderContext& rctx): rctx(rctx) {}

    virtual void render_var(StxVarId var) override {
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
    if (semi && rctx.opts->semicolons) rctx.os << ";";
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

    void render_var(StxVarId var) override {
        switch (var) {
        case StxVarId::NAME:
            rctx.os << code->name;
            break;
        case StxVarId::INIT:
            DCHECK(code->init != nullptr);
            rctx.os << code->init;
            break;
        case StxVarId::TYPE:
            switch (code->type) {
            case VarType::INT:
                rctx.opts->render_code_type_int(rctx.os);
                break;
            case VarType::UINT:
                rctx.opts->render_code_type_uint(rctx.os);
                break;
            case VarType::YYCTYPE:
                rctx.os << rctx.opts->api_char_type;
                break;
            }
            break;
        default:
            render_global_var(rctx, var);
            break;
        }
    }

    bool eval_cond(StxLOpt opt) override {
        if (opt == StxLOpt::INIT) {
            return !code->is_default;
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

    void render_var(StxVarId var) override {
        switch (var) {
            case StxVarId::COND: rctx.os << curr_branch->cond; break;
            case StxVarId::STMT: render_maybe_oneline(rctx, curr_stmt, oneline); break;
            default: render_global_var(rctx, var); break;
        }
    }

    size_t get_list_size(StxVarId var) const override {
        switch (var) {
        case StxVarId::BRANCH:
            return nbranches;
        case StxVarId::STMT: {
            size_t n = 0;
            if (curr_branch->code != nullptr) {
                for (const Code* s = curr_branch->code->head; s; s = s->next) ++n;
            }
            const_cast<size_t&>(nstmts) = n;
            return nstmts;
        }
        default:
            UNREACHABLE();
            return 0;
        }
    }

    void start_list(StxVarId var, size_t lbound, size_t rbound) override {
        switch (var) {
        case StxVarId::BRANCH:
            DCHECK(rbound < nbranches);
            find_list_bounds(code->head, lbound, rbound, &curr_branch, &last_branch);
            break;
        case StxVarId::STMT:
            DCHECK(rbound < nstmts);
            find_list_bounds(curr_branch->code->head, lbound, rbound, &curr_stmt, &last_stmt);
            break;
        default:
            UNREACHABLE();
            break;
        }
    }

    bool next_in_list(StxVarId var) override {
        switch (var) {
        case StxVarId::BRANCH:
            curr_branch = curr_branch->next;
            return curr_branch != last_branch;
        case StxVarId::STMT:
            curr_stmt = curr_stmt->next;
            return curr_stmt != last_stmt;
        default:
            UNREACHABLE();
            return false;
        }
    }

    bool eval_cond(StxLOpt opt) override {
        switch (opt) {
            case StxLOpt::COND: return curr_branch->cond != nullptr;
            case StxLOpt::MANY: return nbranches > 1;
            default: break;
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

    void render_var(StxVarId var) override {
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

    void render_var(StxVarId var) override {
        if (var == StxVarId::VAL) {
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
                    rctx.os << sym;
                    break;
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

    size_t get_list_size(StxVarId var) const override {
        if (var == StxVarId::VAL) {
            return nsyms;
        }
        UNREACHABLE();
        return 0;
    }

    void start_list(StxVarId var, size_t lbound, size_t rbound) override {
        if (var == StxVarId::VAL) {
            curr_sym = lbound;
            last_sym = rbound;
        } else {
            UNREACHABLE();
        }
    }

    bool next_in_list(StxVarId var) override {
        if (var == StxVarId::VAL) {
            return ++curr_sym <= last_sym;
        }
        UNREACHABLE();
        return false;
    }

    bool eval_cond(StxLOpt opt) override {
        switch (opt) {
        case StxLOpt::MANY:
            return nsyms > 1;
        case StxLOpt::CHAR_LITERALS:
            return code->kind == CodeCase::Kind::RANGES
                    && rctx.opts->char_literals == CharLit::CHAR;
        default:
            UNREACHABLE();
            return false;
        }
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

    void render_var(StxVarId var) override {
        switch (var) {
        case StxVarId::CASE:
            switch (code->kind) {
            case CodeCase::Kind::DEFAULT: {
                RenderSwitchCaseDefault callback(rctx);
                rctx.opts->render_code_switch_case_default(rctx.os, callback);
                break;
            }
            case CodeCase::Kind::NUMBER:
            case CodeCase::Kind::STRING:
            case CodeCase::Kind::RANGES: {
                RenderSwitchCaseRange callback(rctx, code, curr_range);
                rctx.opts->render_code_switch_case_range(rctx.os, callback);
                break;
            }}
            break;
        case StxVarId::STMT:
            render_maybe_oneline(rctx, curr_stmt, oneline);
            break;
        default:
            render_global_var(rctx, var);
            break;
        }
    }

    size_t get_list_size(StxVarId var) const override {
        switch (var) {
        case StxVarId::CASE:
            return nranges;
        case StxVarId::STMT:
            return nstmt;
        default:
            UNREACHABLE();
            return 0;
        }
    }

    void start_list(StxVarId var, size_t lbound, size_t rbound) override {
        switch (var) {
        case StxVarId::CASE:
            curr_range = lbound;
            last_range = rbound;
            break;
        case StxVarId::STMT:
            DCHECK(rbound < nstmt);
            find_list_bounds(code->body->head, lbound, rbound, &curr_stmt, &last_stmt);
            break;
        default:
            UNREACHABLE();
            break;
        }
    }

    bool next_in_list(StxVarId var) override {
        switch (var) {
        case StxVarId::CASE:
            return code->kind == CodeCase::Kind::RANGES && ++curr_range <= last_range;
        case StxVarId::STMT:
            curr_stmt = curr_stmt->next;
            return curr_stmt != last_stmt;
        default:
            UNREACHABLE();
            return false;
        }
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

    void render_var(StxVarId var) override {
        switch (var) {
        case StxVarId::EXPR:
            rctx.os << code->expr;
            break;
        case StxVarId::CASE:
            if (rctx.opts->specialize_oneline_switch() && oneline_stmt_list(curr_case->body)) {
                RenderSwitchCaseBlock callback(rctx, curr_case, true);
                rctx.opts->render_code_switch_cases_oneline(rctx.os, callback);
            } else {
                RenderSwitchCaseBlock callback(rctx, curr_case, false);
                rctx.opts->render_code_switch_cases(rctx.os, callback);
            }
            break;
        default:
            render_global_var(rctx, var);
            break;
        }
    }

    size_t get_list_size(StxVarId var) const override {
        if (var == StxVarId::CASE) {
            return ncases;
        }
        UNREACHABLE();
        return 0;
    }

    void start_list(StxVarId var, size_t lbound, size_t rbound) override {
        if (var == StxVarId::CASE) {
            DCHECK(rbound < ncases);
            find_list_bounds(code->cases->head, lbound, rbound, &curr_case, &last_case);
        } else {
            UNREACHABLE();
        }
    }

    bool next_in_list(StxVarId var) override {
        if (var == StxVarId::CASE) {
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

    void render_var(StxVarId var) override {
        switch (var) {
            case StxVarId::LABEL: rctx.os << rctx.opts->label_loop; break;
            case StxVarId::STMT: render(rctx, curr_stmt); break;
            default: render_global_var(rctx, var); break;
        }
    }

    size_t get_list_size(StxVarId var) const override {
        if (var == StxVarId::STMT) {
            return nstmts;
        }
        UNREACHABLE();
        return 0;
    }

    void start_list(StxVarId var, size_t lbound, size_t rbound) override {
        if (var == StxVarId::STMT) {
            DCHECK(rbound < nstmts);
            find_list_bounds(code->head, lbound, rbound, &curr_stmt, &last_stmt);
        } else {
            UNREACHABLE();
        }
    }

    bool next_in_list(StxVarId var) override {
        if (var == StxVarId::STMT) {
            curr_stmt = curr_stmt->next;
            return curr_stmt != last_stmt;
        }
        UNREACHABLE();
        return false;
    }

    FORBID_COPY(RenderLoop);
};

class RenderJmp : public RenderCallback {
    RenderContext& rctx;
    const char* label;

  public:
    RenderJmp(RenderContext& rctx, const char* label)
            : rctx(rctx), label(label) {}

    void render_var(StxVarId var) override {
        switch (var) {
            case StxVarId::LABEL: rctx.os << label; break;
            default: render_global_var(rctx, var); break;
        }
    }

    FORBID_COPY(RenderJmp);
};

class RenderFnDef : public RenderCallback {
    RenderContext& rctx;
    const CodeFnDef* code;
    const CodeParam* curr_param;
    const CodeParam* last_param;
    size_t nparams;
    const Code* curr_stmt;
    const Code* last_stmt;
    size_t nstmts;

  public:
    RenderFnDef(RenderContext& rctx, const CodeFnDef* code)
            : rctx(rctx)
            , code(code)
            , curr_param(nullptr)
            , last_param(nullptr)
            , nparams(0)
            , curr_stmt(nullptr)
            , last_stmt(nullptr)
            , nstmts(0) {
        for (const CodeParam* p = code->params->head; p; p = p->next) ++nparams;
        for (const Code* s = code->body->head; s; s = s->next) ++nstmts;
    }

    void render_var(StxVarId var) override {
        switch (var) {
        case StxVarId::NAME:
            rctx.os << code->name;
            break;
        case StxVarId::TYPE:
            rctx.os << code->type;
            break;
        case StxVarId::ARGNAME:
            rctx.os << curr_param->name;
            break;
        case StxVarId::ARGTYPE:
            rctx.os << curr_param->type;
            break;
        case StxVarId::STMT:
            render(rctx, curr_stmt);
            break;
        default:
            render_global_var(rctx, var);
            break;
        }
    }

    size_t get_list_size(StxVarId var) const override {
        switch (var) {
            case StxVarId::ARG: return nparams;
            case StxVarId::STMT: return nstmts;
            default: UNREACHABLE(); return 0;
        }
    }

    void start_list(StxVarId var, size_t lbound, size_t rbound) override {
        switch (var) {
        case StxVarId::ARG:
            DCHECK(rbound < nparams);
            find_list_bounds(code->params->head, lbound, rbound, &curr_param, &last_param);
            break;
        case StxVarId::STMT:
            DCHECK(rbound < nstmts);
            find_list_bounds(code->body->head, lbound, rbound, &curr_stmt, &last_stmt);
            break;
        default:
            UNREACHABLE();
            break;
        }
    }

    bool next_in_list(StxVarId var) override {
        switch (var) {
        case StxVarId::ARG:
            curr_param = curr_param->next;
            return curr_param != last_param;
        case StxVarId::STMT:
            curr_stmt = curr_stmt->next;
            return curr_stmt != last_stmt;
        default:
            UNREACHABLE();
            return false;
        }
    }

    bool eval_cond(StxLOpt opt) override {
        if (opt == StxLOpt::TYPE) {
            return code->type != nullptr;
        }
        UNREACHABLE();
        return false;
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

    void render_var(StxVarId var) override {
        switch (var) {
            case StxVarId::NAME: rctx.os << code->name; break;
            case StxVarId::RETVAL: rctx.os << code->retval; break;
            case StxVarId::ARG: rctx.os << curr_arg->arg; break;
            default: render_global_var(rctx, var); break;
        }
    }

    size_t get_list_size(StxVarId var) const override {
        if (var == StxVarId::ARG) {
            return nargs;
        }
        UNREACHABLE();
        return 0;
    }

    void start_list(StxVarId var, size_t lbound, size_t rbound) override {
        if (var == StxVarId::ARG) {
            DCHECK(rbound < nargs);
            find_list_bounds(code->args->head, lbound, rbound, &curr_arg, &last_arg);
        } else {
            UNREACHABLE();
        }
    }

    bool next_in_list(StxVarId var) override {
        if (var == StxVarId::ARG) {
            curr_arg = curr_arg->next;
            return curr_arg != last_arg;
        }
        UNREACHABLE();
        return false;
    }

    bool eval_cond(StxLOpt opt) override {
        switch (opt) {
        case StxLOpt::ARGS:
            return nargs > 0;
        case StxLOpt::RETVAL:
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

    void render_var(StxVarId var) override {
        switch (var) {
        case StxVarId::FNDECL: {
            RenderFnDef callback(rctx, &curr_fn->fndef);
            rctx.opts->render_code_fndecl(rctx.os, callback);
            break;
        }
        case StxVarId::FNDEF: {
            RenderFnDef callback(rctx, &curr_fn->fndef);
            rctx.opts->render_code_fndef(rctx.os, callback);
            break;
        }
        default:
            render_global_var(rctx, var);
            break;
        }
    }

    size_t get_list_size(StxVarId var) const override {
        if (var == StxVarId::FN) {
            return nfuncs;
        }
        UNREACHABLE();
        return 0;
    }

    void start_list(StxVarId var, size_t lbound, size_t rbound) override {
        if (var == StxVarId::FN) {
            DCHECK(rbound < nfuncs);
            find_list_bounds(fns->head, lbound, rbound, &curr_fn, &last_fn);
        } else {
            UNREACHABLE();
        }
    }

    bool next_in_list(StxVarId var) override {
        if (var == StxVarId::FN) {
            curr_fn = curr_fn->next;
            return curr_fn != last_fn;
        }
        UNREACHABLE();
        return false;
    }

    FORBID_COPY(RenderRecFuncs);
};

class RenderAssign : public RenderCallback {
    RenderContext& rctx;
    const CodeAssign* code;

  public:
    RenderAssign(RenderContext& rctx, const CodeAssign* code)
            : rctx(rctx), code(code) {}

    void render_var(StxVarId var) override {
        switch (var) {
            case StxVarId::LHS: rctx.os << code->lhs; break;
            case StxVarId::RHS: rctx.os << code->rhs; break;
            default: render_global_var(rctx, var); break;
        }
    }

    FORBID_COPY(RenderAssign);
};

class RenderDebug : public RenderCallback {
    RenderContext& rctx;
    const CodeDebug* code;

  public:
    RenderDebug(RenderContext& rctx, const CodeDebug* code): rctx(rctx), code(code) {}

    void render_var(StxVarId var) override {
        switch (var) {
        case StxVarId::DEBUG: {
            std::ostringstream s(rctx.opts->api_debug);
            argsubst(s, rctx.opts->api_sigil, "state", false, code->state);
            argsubst(s, rctx.opts->api_sigil, "char", false, rctx.opts->var_char);
            rctx.os << s.str();
            break;
        }
        case StxVarId::STATE:
            rctx.os << code->state;
            break;
        case StxVarId::CHAR:
            rctx.os << rctx.opts->var_char;
            break;
        case StxVarId::RECORD:
            rctx.os << rctx.opts->var_record;
            break;
        default:
            render_global_var(rctx, var);
            break;
        }
    }

    FORBID_COPY(RenderDebug);
};

// One callback class is used for all combinations of YYSKIP, YYPEEK and YYBACKUP primitives,
// plus YYRESTORE, as they all have very similar variables. This should not cause variable misuse,
// as the variables for each configuration are checked after parsing syntax file.
class RenderSkipPeekBackupRestore : public RenderCallback {
    RenderContext& rctx;

  public:
    RenderSkipPeekBackupRestore(RenderContext& rctx): rctx(rctx) {}

    void render_var(StxVarId var) override {
        switch (var) {
            case StxVarId::CHAR: rctx.os << rctx.opts->var_char; break;
            case StxVarId::CTYPE: rctx.os << rctx.opts->api_char_type; break;
            case StxVarId::INPUT: rctx.os << rctx.opts->api_input; break;
            case StxVarId::CURSOR: rctx.os << rctx.opts->api_cursor; break;
            case StxVarId::MARKER: rctx.os << rctx.opts->api_marker; break;
            case StxVarId::PEEK: rctx.os << rctx.opts->api_peek; break;
            case StxVarId::SKIP: rctx.os << rctx.opts->api_skip; break;
            case StxVarId::BACKUP: rctx.os << rctx.opts->api_backup; break;
            case StxVarId::RESTORE: rctx.os << rctx.opts->api_restore; break;
            case StxVarId::RECORD: rctx.os << rctx.opts->var_record; break;
            default: render_global_var(rctx, var); break;
        }
    }

    bool eval_cond(StxLOpt opt) override {
        if (opt == StxLOpt::CAST) {
            return rctx.opts->char_conv;
        }
        UNREACHABLE();
        return false;
    }
};

class RenderBackupRestoreCtx : public RenderCallback {
    RenderContext& rctx;

  public:
    RenderBackupRestoreCtx(RenderContext& rctx): rctx(rctx) {}

    void render_var(StxVarId var) override {
        switch (var) {
            case StxVarId::CTXMARKER: rctx.os << rctx.opts->api_ctxmarker; break;
            case StxVarId::CURSOR: rctx.os << rctx.opts->api_cursor; break;
            case StxVarId::BACKUPCTX: rctx.os << rctx.opts->api_backup_ctx; break;
            case StxVarId::RESTORECTX: rctx.os << rctx.opts->api_restore_ctx; break;
            case StxVarId::RECORD: rctx.os << rctx.opts->var_record; break;
            default: render_global_var(rctx, var); break;
        }
    }
};

class RenderTagOps : public RenderCallback {
    RenderContext& rctx;
    const CodeTag* code;

  public:
    RenderTagOps(RenderContext& rctx, const CodeTag* code)
            : rctx(rctx), code(code) {}

    void render_var(StxVarId var) override {
        const opt_t* opts = rctx.opts;
        switch (var) {
        case StxVarId::TAG:
        case StxVarId::LHS:
            rctx.os << code->tag1;
            break;
        case StxVarId::RHS:
            rctx.os << code->tag2;
            break;
        case StxVarId::NEG:
            argsubst(rctx.os, opts->tags_negative, opts->api_sigil, "tag", true, code->tag2);
            break;
        case StxVarId::CURSOR:
            rctx.os << opts->api_cursor;
            break;
        case StxVarId::OFFSET:
            rctx.os << code->dist;
            break;
        case StxVarId::RESTORETAG:
            argsubst(rctx.os, opts->api_restore_tag, opts->api_sigil, "tag", true, code->tag1);
            break;
        case StxVarId::SHIFT:
            argsubst(rctx.os, opts->api_shift, opts->api_sigil, "shift", true, -code->dist);
            break;
        case StxVarId::SHIFTSTAG: {
            std::ostringstream s(opts->api_stag_shift);
            argsubst(s, opts->api_sigil, "tag", false, code->tag1);
            argsubst(s, opts->api_sigil, "shift", false, -code->dist);
            rctx.os << s.str();
            break;
        }
        case StxVarId::SHIFTMTAG: {
            std::ostringstream s(opts->api_mtag_shift);
            argsubst(s, opts->api_sigil, "tag", false, code->tag1);
            argsubst(s, opts->api_sigil, "shift", false, -code->dist);
            rctx.os << s.str();
            break;
        }
        case StxVarId::STAGP:
            argsubst(rctx.os, opts->api_stag_pos, opts->api_sigil, "tag", true, code->tag1);
            break;
        case StxVarId::STAGN:
            argsubst(rctx.os, opts->api_stag_neg, opts->api_sigil, "tag", true, code->tag1);
            break;
        case StxVarId::MTAGP:
            argsubst(rctx.os, opts->api_mtag_pos, opts->api_sigil, "tag", true, code->tag1);
            break;
        case StxVarId::MTAGN:
            argsubst(rctx.os, opts->api_mtag_neg, opts->api_sigil, "tag", true, code->tag1);
            break;
        case StxVarId::COPYSTAG: {
            std::ostringstream s(opts->api_stag_copy);
            argsubst(s, opts->api_sigil, "lhs", false, code->tag1);
            argsubst(s, opts->api_sigil, "rhs", false, code->tag2);
            rctx.os << s.str();
            break;
        }
        case StxVarId::COPYMTAG: {
            std::ostringstream s(opts->api_mtag_copy);
            argsubst(s, opts->api_sigil, "lhs", false, code->tag1);
            argsubst(s, opts->api_sigil, "rhs", false, code->tag2);
            rctx.os << s.str();
            break;
        }
        case StxVarId::RECORD:
            rctx.os << opts->var_record;
            break;
        default:
            render_global_var(rctx, var);
            break;
        }
    }

    bool eval_cond(StxLOpt opt) override {
        if (opt == StxLOpt::NESTED) {
            return code->tag2 != nullptr; // for nested tags there is a negative tag
        }
        UNREACHABLE();
        return false;
    }

    FORBID_COPY(RenderTagOps);
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

    void render_var(StxVarId var) override {
        switch (var) {
        case StxVarId::NAME:
            rctx.os << code->name;
            break;
        case StxVarId::TYPE:
            rctx.os << code->type;
            break;
        case StxVarId::SIZE:
            rctx.os << code->size;
            break;
        case StxVarId::ROW:
            break; // do nothing
        case StxVarId::ELEM: {
            const char* e = code->elems[curr_row * ncols + curr_col];
            if (code->tabulate) {
                rctx.os << indent(static_cast<uint32_t>(maxlen - strlen(e)), " ");
            }
            rctx.os << e;
            break;
        }
        default:
            render_global_var(rctx, var);
            break;
        }
    }

    size_t get_list_size(StxVarId var) const override {
        switch (var) {
            case StxVarId::ROW: return nrows;
            case StxVarId::ELEM: return ncols;
            default: UNREACHABLE(); return 0;
        }
    }

    void start_list(StxVarId var, size_t lbound, size_t rbound) override {
        switch (var) {
        case StxVarId::ROW:
            DCHECK(rbound < nrows);
            curr_row = lbound;
            last_row = rbound;
            break;
        case StxVarId::ELEM:
            DCHECK(rbound < ncols);
            curr_col = lbound;
            last_col = rbound;
            break;
        default:
            UNREACHABLE();
            break;
        }
    }

    bool next_in_list(StxVarId var) override {
        switch (var) {
            case StxVarId::ROW: return ++curr_row <= last_row;
            case StxVarId::ELEM: return ++curr_col <= last_col;
            default: UNREACHABLE(); return false;
        }
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

    void render_var(StxVarId var) override {
        switch (var) {
        case StxVarId::TYPE:
            rctx.os << code->type;
            break;
        case StxVarId::ELEM:
            rctx.os << code->elem_ids[curr_elem];
            break;
        case StxVarId::INIT:
            rctx.os << code->elem_nums[curr_elem];
            break;
        default:
            render_global_var(rctx, var);
            break;
        }
    }

    size_t get_list_size(StxVarId var) const override {
        if (var == StxVarId::ELEM) {
            return code->size;
        }
        UNREACHABLE();
        return 0;
    }

    void start_list(StxVarId var, size_t lbound, size_t rbound) override {
        if (var == StxVarId::ELEM) {
            curr_elem = lbound;
            last_elem = rbound;
        } else {
            UNREACHABLE();
        }
    }

    bool next_in_list(StxVarId var) override {
        if (var == StxVarId::ELEM) {
            return ++curr_elem <= last_elem;
        } else {
            UNREACHABLE();
        }
        return false;
    }

    bool eval_cond(StxLOpt opt) override {
        if (opt == StxLOpt::INIT) {
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

    void render_var(StxVarId var) override {
        switch (var) {
        case StxVarId::VER:
            rctx.os << PACKAGE_VERSION;
            break;
        case StxVarId::DATE: {
            time_t now = time(nullptr);
            rctx.os.write(ctime(&now), 24);
            break;
        }
        default:
            render_global_var(rctx, var);
            break;
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

    void render_var(StxVarId var) override {
        switch (var) {
            case StxVarId::LINE: rctx.os << line; break;
            case StxVarId::FILE: rctx.os << file; break;
            default: render_global_var(rctx, var); break;
        }
    }

    FORBID_COPY(RenderLineInfo);
};

class RenderSetAccept : public RenderCallback {
    RenderContext& rctx;
    size_t val;

  public:
    RenderSetAccept(RenderContext& rctx, size_t val)
        : rctx(rctx), val(val) {}

    void render_var(StxVarId var) override {
        switch (var) {
        case StxVarId::SETACCEPT: {
            std::ostringstream s(rctx.opts->api_accept_set);
            argsubst(s, rctx.opts->api_sigil, "var", false, rctx.opts->var_accept);
            argsubst(s, rctx.opts->api_sigil, "val", false, val);
            rctx.os << s.str();
            break;
        }
        case StxVarId::VAR:
            rctx.os << rctx.opts->var_accept;
            break;
        case StxVarId::VAL:
            rctx.os << val;
            break;
        case StxVarId::RECORD:
            rctx.os << rctx.opts->var_record;
            break;
        default:
            render_global_var(rctx, var);
            break;
        }
    }

    FORBID_COPY(RenderSetAccept);
};

class RenderSetCond : public RenderCallback {
    RenderContext& rctx;
    const char* cond;

  public:
    RenderSetCond(RenderContext& rctx, const char* cond)
        : rctx(rctx), cond(cond) {}

    void render_var(StxVarId var) override {
        switch (var) {
        case StxVarId::SETCOND:
            argsubst(
                rctx.os, rctx.opts->api_cond_set, rctx.opts->cond_set_param, "cond", true, cond);
            break;
        case StxVarId::VAR:
            rctx.os << rctx.opts->var_cond;
            break;
        case StxVarId::VAL:
            rctx.os << cond;
            break;
        case StxVarId::RECORD:
            rctx.os << rctx.opts->var_record;
            break;
        default:
            render_global_var(rctx, var);
            break;
        }
    }

    FORBID_COPY(RenderSetCond);
};

class RenderSetState : public RenderCallback {
    RenderContext& rctx;
    const char* state;

  public:
    RenderSetState(RenderContext& rctx, const char* state)
        : rctx(rctx), state(state) {}

    void render_var(StxVarId var) override {
        switch (var) {
        case StxVarId::SETSTATE:
            argsubst(rctx.os,
                rctx.opts->api_state_set, rctx.opts->state_set_param, "state", true, state);
            break;
        case StxVarId::VAR:
            rctx.os << rctx.opts->var_state;
            break;
        case StxVarId::VAL:
            rctx.os << state;
            break;
        case StxVarId::RECORD:
            rctx.os << rctx.opts->var_record;
            break;
        default:
            render_global_var(rctx, var);
            break;
        }
    }

    FORBID_COPY(RenderSetState);
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
            oneline = oneline_stmt_list(b->code);
        }
        RenderIfThenElse callback(rctx, code->ifte, oneline);
        if (oneline) {
            rctx.opts->render_code_if_then_else_oneline(rctx.os, callback);
        } else {
            rctx.opts->render_code_if_then_else(rctx.os, callback);
        }
        break;
    }
    case CodeKind::SWITCH: {
        RenderSwitch callback(rctx, &code->swch);
        rctx.opts->render_code_switch(rctx.os, callback);
        break;
    }
    case CodeKind::BLOCK:
        render_block(rctx, &code->block);
        break;
    case CodeKind::FNDEF: {
        RenderFnDef callback(rctx, &code->fndef);
        rctx.opts->render_code_fndef(rctx.os, callback);
        break;
    }
    case CodeKind::FNCALL: {
        RenderFnCall callback(rctx, &code->fncall);
        if (code->fncall.tailcall) {
            rctx.opts->render_code_tailcall(rctx.os, callback);
        } else {
            rctx.opts->render_code_fncall(rctx.os, callback);
        }
        break;
    }
    case CodeKind::REC_FUNCS: {
        RenderRecFuncs callback(rctx, code->rfuncs);
        rctx.opts->render_code_recursive_functions(rctx.os, callback);
        break;
    }
    case CodeKind::LOOP: {
        RenderLoop callback(rctx, code->loop);
        rctx.opts->render_code_loop(rctx.os, callback);
        break;
    }
    case CodeKind::GOTO: {
        RenderJmp callback(rctx, code->target);
        rctx.opts->render_code_goto(rctx.os, callback);
        break;
    }
    case CodeKind::CONTINUE: {
        RenderJmp callback(rctx, code->target);
        rctx.opts->render_code_continue(rctx.os, callback);
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
    case CodeKind::ASSIGN: {
        RenderAssign callback(rctx, &code->assign);
        rctx.opts->render_code_assign(rctx.os, callback);
        break;
    }
    case CodeKind::ABORT: {
        RenderSimple callback(rctx);
        rctx.opts->render_code_abort(rctx.os, callback);
        break;
    }
    case CodeKind::DEBUG: {
        RenderDebug callback(rctx, &code->debug);
        rctx.opts->render_code_yydebug(rctx.os, callback);
        break;
    }
    case CodeKind::SKIP: {
        RenderSkipPeekBackupRestore callback(rctx);
        rctx.opts->render_code_yyskip(rctx.os, callback);
        break;
    }
    case CodeKind::PEEK: {
        RenderSkipPeekBackupRestore callback(rctx);
        rctx.opts->render_code_yypeek(rctx.os, callback);
        break;
    }
    case CodeKind::BACKUP: {
        RenderSkipPeekBackupRestore callback(rctx);
        rctx.opts->render_code_yybackup(rctx.os, callback);
        break;
    }
    case CodeKind::BACKUPCTX: {
        RenderBackupRestoreCtx callback(rctx);
        rctx.opts->render_code_yybackupctx(rctx.os, callback);
        break;
    }
    case CodeKind::RESTORE: {
        RenderSkipPeekBackupRestore callback(rctx);
        rctx.opts->render_code_yyrestore(rctx.os, callback);
        break;
    }
    case CodeKind::RESTORECTX: {
        RenderBackupRestoreCtx callback(rctx);
        rctx.opts->render_code_yyrestorectx(rctx.os, callback);
        break;
    }
    case CodeKind::RESTORETAG: {
        RenderTagOps callback(rctx, &code->tag);
        rctx.opts->render_code_yyrestoretag(rctx.os, callback);
        break;
    }
    case CodeKind::SHIFT: {
        RenderTagOps callback(rctx, &code->tag);
        rctx.opts->render_code_yyshift(rctx.os, callback);
        break;
    }
    case CodeKind::SHIFTSTAG: {
        RenderTagOps callback(rctx, &code->tag);
        rctx.opts->render_code_yyshiftstag(rctx.os, callback);
        break;
    }
    case CodeKind::SHIFTMTAG: {
        RenderTagOps callback(rctx, &code->tag);
        rctx.opts->render_code_yyshiftstag(rctx.os, callback);
        break;
    }
    case CodeKind::STAGN: {
        RenderTagOps callback(rctx, &code->tag);
        rctx.opts->render_code_yystagn(rctx.os, callback);
        break;
    }
    case CodeKind::STAGP: {
        RenderTagOps callback(rctx, &code->tag);
        rctx.opts->render_code_yystagp(rctx.os, callback);
        break;
    }
    case CodeKind::MTAGN: {
        RenderTagOps callback(rctx, &code->tag);
        rctx.opts->render_code_yymtagn(rctx.os, callback);
        break;
    }
    case CodeKind::MTAGP: {
        RenderTagOps callback(rctx, &code->tag);
        rctx.opts->render_code_yymtagp(rctx.os, callback);
        break;
    }
    case CodeKind::COPYSTAG: {
        RenderTagOps callback(rctx, &code->tag);
        rctx.opts->render_code_yycopystag(rctx.os, callback);
        break;
    }
    case CodeKind::COPYMTAG: {
        RenderTagOps callback(rctx, &code->tag);
        rctx.opts->render_code_yycopymtag(rctx.os, callback);
        break;
    }
    case CodeKind::PEEK_SKIP: {
        RenderSkipPeekBackupRestore callback(rctx);
        rctx.opts->render_code_yypeek_yyskip(rctx.os, callback);
        break;
    }
    case CodeKind::SKIP_PEEK: {
        RenderSkipPeekBackupRestore callback(rctx);
        rctx.opts->render_code_yyskip_yypeek(rctx.os, callback);
        break;
    }
    case CodeKind::SKIP_BACKUP: {
        RenderSkipPeekBackupRestore callback(rctx);
        rctx.opts->render_code_yyskip_yybackup(rctx.os, callback);
        break;
    }
    case CodeKind::BACKUP_SKIP: {
        RenderSkipPeekBackupRestore callback(rctx);
        rctx.opts->render_code_yybackup_yyskip(rctx.os, callback);
        break;
    }
    case CodeKind::BACKUP_PEEK: {
        RenderSkipPeekBackupRestore callback(rctx);
        rctx.opts->render_code_yybackup_yypeek(rctx.os, callback);
        break;
    }
    case CodeKind::BACKUP_PEEK_SKIP: {
        RenderSkipPeekBackupRestore callback(rctx);
        rctx.opts->render_code_yybackup_yypeek_yyskip(rctx.os, callback);
        break;
    }
    case CodeKind::SKIP_BACKUP_PEEK: {
        RenderSkipPeekBackupRestore callback(rctx);
        rctx.opts->render_code_yyskip_yybackup_yypeek(rctx.os, callback);
        break;
    }
    case CodeKind::SETACCEPT: {
        RenderSetAccept callback(rctx, code->accept);
        rctx.opts->render_code_yysetaccept(rctx.os, callback);
        break;
    }
    case CodeKind::SETCOND: {
        RenderSetCond callback(rctx, code->cond);
        rctx.opts->render_code_yysetcond(rctx.os, callback);
        break;
    }
    case CodeKind::SETSTATE: {
        RenderSetState callback(rctx, code->state);
        rctx.opts->render_code_yysetstate(rctx.os, callback);
        break;
    }
    case CodeKind::LINE_INFO_INPUT: {
        RenderLineInfo callback(rctx, code->loc.line, rctx.msg.filenames[code->loc.file]);
        rctx.opts->render_code_line_info(rctx.os, callback);
        break;
    }
    case CodeKind::LINE_INFO_OUTPUT: {
        RenderLineInfo callback(rctx, rctx.line + 1, rctx.file);
        rctx.opts->render_code_line_info(rctx.os, callback);
        break;
    }
    case CodeKind::FINGERPRINT:
        if (rctx.opts->target == Target::DOT) {
            // Don't use `code:fingerprint`, as it has language-specific comment syntax.
            rctx.os << "/* Generated by re2c";
            if (rctx.opts->version) rctx.os << " " PACKAGE_VERSION;
            if (rctx.opts->date) {
                rctx.os << " on ";
                time_t now = time(nullptr);
                rctx.os.write(ctime(&now), 24);
            }
            rctx.os << " */";
            render_nl(rctx);
        } else {
            RenderFingerprint callback(rctx);
            rctx.opts->render_code_fingerprint(rctx.os, callback);
        }
        break;
    case CodeKind::VAR: {
        RenderVar callback(rctx, &code->var);
        rctx.opts->render_code_var_local(rctx.os, callback);
        break;
    }
    case CodeKind::CONST: {
        RenderVar callback(rctx, &code->var); // same code item as for `CodeKind::VAR`
        rctx.opts->render_code_const_global(rctx.os, callback);
        break;
    }
    case CodeKind::ARRAY: {
        RenderArray callback(rctx, &code->array);
        if (rctx.opts->code_model == CodeModel::REC_FUNC) {
            rctx.opts->render_code_array_global(rctx.os, callback);
        } else {
            rctx.opts->render_code_array_local(rctx.os, callback);
        }
        break;
    }
    case CodeKind::ENUM: {
        RenderEnum callback(rctx, &code->enumr);
        rctx.opts->render_code_enum(rctx.os, callback);
        break;
    }
    case CodeKind::LABEL:
        render_label(rctx, code->label);
        break;
    case CodeKind::STAGS:
    case CodeKind::MTAGS:
    case CodeKind::SVARS:
    case CodeKind::MVARS:
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
    // in configurations and blocks), and some are generated by re2c itself.
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

} // anonymous namespace

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
