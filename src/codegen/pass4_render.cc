#include "config.h"
#include "src/codegen/helpers.h"
#include "src/codegen/output.h"
#include "src/codegen/syntax.h"
#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/util/check.h"
#include "src/util/file_utils.h"

namespace re2c {

static void render(RenderContext& rctx, const Code* code);

static bool oneline_stmt_list(const CodeList* list) {
    const Code* head = list->head;
    return head != nullptr
            && head->next == nullptr
            && (head->kind == CodeKind::STMT || head->kind == CodeKind::TEXT);
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
        rctx.os << std::endl;
        ++rctx.line;
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

static uint32_t count_lines_text(const char* text) {
    DCHECK(text);
    uint32_t lc = 0;
    for (const char* s = text; *s; ++s) {
        if (*s == '\n') ++lc;
    }
    return lc;
}

static inline void render_stmt_end(RenderContext& rctx, bool semi) {
    if (semi && rctx.opts->lang != Lang::GO) rctx.os << ";";
    rctx.os << std::endl;
    ++rctx.line;
}

static void render_list(RenderContext& rctx, const CodeList* code) {
    for (const Code* s = code->head; s; s = s->next) {
        render(rctx, s);
    }
}

static void render_line_info(
        std::ostream& o, uint32_t line, const std::string& fname, const opt_t* opts) {
    if (!opts->line_dirs) return;

    switch (opts->lang) {
    case Lang::GO:
        // Go: //line <filename>:<line-number>
        o << "//line \"" << fname << "\":" << line << "\n";
        break;
    case Lang::C:
        // C/C++: #line <line-number> <filename>
        o << "#line " << line << " \"" << fname << "\"\n";
        break;
    case Lang::RUST:
        // For Rust line directives should be removed by `remove_empty` pass.
        UNREACHABLE();
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

class RenderVar : public OutputCallback {
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
            OutputCallback callback; // dummy callback, these configurations have no variables
            switch (code->type) {
            case VarType::INT:
                rctx.stx.gen_code(rctx.os, rctx.opts, "code:type_int", callback);
                break;
            case VarType::UINT:
                rctx.stx.gen_code(rctx.os, rctx.opts, "code:type_uint", callback);
                break;
            case VarType::YYCTYPE:
                rctx.os << rctx.opts->api_char_type;
            }
        } else {
            render_global_var(rctx, var);
        }
    }

    bool eval_cond(const char* cond) override {
        if (strcmp(cond, "have_init") == 0) {
            return code->init != nullptr;
        }
        UNREACHABLE();
        return false;
    }

    FORBID_COPY(RenderVar);
};

class RenderIfThenElse : public OutputCallback {
    RenderContext& rctx;
    const CodeIfTE* code;
    const Code* curr_stmt;
    const Code* last_stmt;
    size_t nthen_stmts;
    size_t nelse_stmts;
    bool oneline;

  public:
    RenderIfThenElse(RenderContext& rctx, const CodeIfTE* code, bool oneline)
            : rctx(rctx)
            , code(code)
            , curr_stmt(nullptr)
            , last_stmt(nullptr)
            , nthen_stmts(0)
            , nelse_stmts(0)
            , oneline(oneline) {
        for (const Code* s = code->if_code->head; s; s = s->next) ++nthen_stmts;
        if (code->else_code != nullptr) {
            for (const Code* s = code->else_code->head; s; s = s->next) ++nelse_stmts;
        }
    }

    void render_var(const char* var) override {
        if (strcmp(var, "then_cond") == 0) {
            rctx.os << code->if_cond;
        } else if (strcmp(var, "else_cond") == 0) {
            rctx.os << code->else_cond;
        } else if (strcmp(var, "then_stmt") == 0) {
            if (oneline) {
                rctx.os << curr_stmt->text;
                render_stmt_end(rctx, curr_stmt->kind == CodeKind::STMT);
            } else {
                render(rctx, curr_stmt);
            }
        } else if (strcmp(var, "else_stmt") == 0) {
            DCHECK(!oneline);
            render(rctx, curr_stmt);
        } else {
            render_global_var(rctx, var);
        }
    }

    size_t get_list_size(const char* var) const override {
        if (strcmp(var, "then_stmt") == 0) {
            return nthen_stmts;
        } else if (strcmp(var, "else_stmt") == 0) {
            return nelse_stmts;
        }
        UNREACHABLE();
        return 0;
    }

    void start_list(const char* var, size_t lbound, size_t rbound) override {
        if (strcmp(var, "then_stmt") == 0) {
            DCHECK(rbound < nthen_stmts);
            find_list_bounds(code->if_code->head, lbound, rbound, &curr_stmt, &last_stmt);
        } else if (strcmp(var, "else_stmt") == 0) {
            DCHECK(rbound < nelse_stmts);
            find_list_bounds(code->else_code->head, lbound, rbound, &curr_stmt, &last_stmt);
        } else {
            UNREACHABLE();
        }
    }

    bool next_in_list(const char* var) override {
        if (strcmp(var, "then_stmt") == 0 || strcmp(var, "else_stmt") == 0) {
            curr_stmt = curr_stmt->next;
            return curr_stmt != last_stmt;
        }
        UNREACHABLE();
        return false;
    }

    bool eval_cond(const char* cond) override {
        if (strcmp(cond, "have_else_part") == 0) {
            return code->else_code != nullptr;
        } else if (strcmp(cond, "have_else_cond") == 0) {
            return code->else_cond != nullptr;
        }
        UNREACHABLE();
        return false;
    }

    FORBID_COPY(RenderIfThenElse);
};

static void render_number(RenderContext& rctx, int64_t num, VarType type) {
    std::ostringstream& os = rctx.os;
    const opt_t* opts = rctx.opts;
    const Enc& enc = opts->encoding;
    bool hex = opts->lang == Lang::RUST || enc.type() == Enc::Type::EBCDIC;

    switch (type) {
    case VarType::UINT:
        DCHECK(num >= 0);
        os << static_cast<uint32_t>(num);
        break;
    case VarType::INT:
        os << num;
        break;
    case VarType::YYCTYPE:
        DCHECK(num >= 0);
        print_char_or_hex(os, static_cast<uint32_t>(num), enc.cunit_size(), hex, /*dot*/ false);
        break;
    }
}

class RenderSwitchCaseDefault : public OutputCallback {
    RenderContext& rctx;

  public:
    RenderSwitchCaseDefault(RenderContext& rctx): rctx(rctx) {}

    void render_var(const char* var) override {
        render_global_var(rctx, var);
    }
};

class RenderSwitchCaseRange : public OutputCallback {
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
                render_number(rctx, sym, code->ranges->type);
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

    bool eval_cond(const char* cond) override {
        if (strcmp(cond, "multival") == 0) {
            return nsyms > 1;
        }
        UNREACHABLE();
        return false;
    }

    FORBID_COPY(RenderSwitchCaseRange);
};

class RenderSwitchCaseBlock : public OutputCallback {
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
                rctx.stx.gen_code(rctx.os, rctx.opts, "code:switch_case_default", callback);
                break;
            }
            case CodeCase::Kind::NUMBER:
            case CodeCase::Kind::STRING:
            case CodeCase::Kind::RANGES: {
                RenderSwitchCaseRange callback(rctx, code, curr_range);
                rctx.stx.gen_code(rctx.os, rctx.opts, "code:switch_case_range", callback);
                break;
            }}
        } else if (strcmp(var, "stmt") == 0) {
            if (oneline) {
                rctx.os << curr_stmt->text;
                render_stmt_end(rctx, curr_stmt->kind == CodeKind::STMT);
            } else {
                render(rctx, curr_stmt);
            }
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

class RenderSwitch : public OutputCallback {
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
            bool oneline = rctx.stx.specialize_oneline_switch()
                    && oneline_stmt_list(curr_case->body);
            const char* conf = oneline ? "code:switch_cases_oneline" : "code:switch_cases";
            RenderSwitchCaseBlock callback(rctx, curr_case, oneline);
            rctx.stx.gen_code(rctx.os, rctx.opts, conf, callback);
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

class RenderLoop : public OutputCallback {
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

    bool eval_cond(const char* cond) override {
        if (strcmp(cond, "have_label") == 0) {
            return !rctx.opts->label_loop.empty();
        }
        UNREACHABLE();
        return false;
    }

    FORBID_COPY(RenderLoop);
};

static void render_arg(RenderContext& rctx, const CodeArg* arg) {
    std::ostringstream& os = rctx.os;
    const opt_t* opts = rctx.opts;

    const char* s = arg->arg, *p = s;
    for (; *s; ++s) {
        // remove unescaped newlines and render on a new line
        if (*s == '\n') {
            os.write(p, s - p);
            p = s + 1;
            os << std::endl << indent(rctx.ind + 1, opts->indent_str);
            ++rctx.line;
        }
    }
    os.write(p, s - p);
}

static void render_func(RenderContext& rctx, const CodeFunc* func) {
    std::ostringstream& os = rctx.os;
    const opt_t* opts = rctx.opts;
    const CodeArg* first = func->args->head;

    os << indent(rctx.ind, opts->indent_str) << func->name;
    ++rctx.line;

    // Estimate total length of function call (in characters). Arguments are rendered on one line if
    // the total length does not exceed 80 characters (including indentation and the text preceding
    // the list of arguments) , otherwise each argument and the closing parenthesis are rendered on
    // a new line.
    size_t total = rctx.ind * opts->indent_str.length() + strlen(func->name);
    for (const CodeArg* a = first; a; a = a->next) {
        total += strlen(a->arg) + 2; // +2 for ", "
    }

    if (total < 80) {
        os << "(";
        for (const CodeArg* a = first; a; a = a->next) {
            if (a != first) os << ", ";
            render_arg(rctx, a);
        }
        os << ")";
    } else {
        ++rctx.ind;

        // An argument may be broken into multiple lines by inserting unescaped newline characters
        // in the argument string. The text after each newline is "hanged after" the the argument
        // (rendered on the next line with one extra level of indentation).
        os << std::endl;
        for (const CodeArg* a = first; a; a = a->next) {
            const char* sep = a == first ? "( " : ", ";
            os << indent(rctx.ind, opts->indent_str) << sep;
            render_arg(rctx, a);
            os << std::endl;
            ++rctx.line;
        }
        os << indent(rctx.ind, opts->indent_str) << ")";

        --rctx.ind;
    }

    os << func->semi << std::endl;
    ++rctx.line;
}

static inline void yych_conv(std::ostream& os, const opt_t* opts) {
    if (opts->char_conv) {
        os << "(" <<  opts->api_char_type << ")";
    }
}

void gen_peek_expr(std::ostream& os, const opt_t* opts) {
    yych_conv(os, opts);
    if (opts->api == Api::DEFAULT) {
        os << "*" << opts->api_cursor;
    } else if (opts->lang == Lang::RUST) {
        if (opts->unsafe) os << "unsafe {";
        os << opts->api_peek;
        if (opts->api_style == ApiStyle::FUNCTIONS) os << "()";
        if (opts->unsafe) os << "}";
    } else {
        os << opts->api_peek;
        if (opts->api_style == ApiStyle::FUNCTIONS) os << "()";
    }
}

static void render_peek(RenderContext& rctx) {
    std::ostringstream& os = rctx.os;
    const opt_t* opts = rctx.opts;

    os << indent(rctx.ind, opts->indent_str) << opts->var_char << " = ";
    gen_peek_expr(os, opts);
    render_stmt_end(rctx, true);
}

static void render_skip(RenderContext& rctx) {
    std::ostringstream& os = rctx.os;
    const opt_t* opts = rctx.opts;

    os << indent(rctx.ind, opts->indent_str);
    if (opts->api == Api::CUSTOM) {
        os << opts->api_skip;
        if (opts->api_style == ApiStyle::FUNCTIONS) {
            os << "()";
            render_stmt_end(rctx, true);
        } else {
            render_stmt_end(rctx, false);
        }
    } else {
        os << "++" << opts->api_cursor;
        render_stmt_end(rctx, true);
    }
}

static void render_backup(RenderContext& rctx) {
    std::ostringstream& os = rctx.os;
    const opt_t* opts = rctx.opts;

    os << indent(rctx.ind, opts->indent_str);
    if (opts->api == Api::CUSTOM) {
        os << opts->api_backup;
        if (opts->api_style == ApiStyle::FUNCTIONS) {
            os << "()";
            render_stmt_end(rctx, true);
        } else {
            render_stmt_end(rctx, false);
        }
    } else {
        os << opts->api_marker << " = " << opts->api_cursor;
        render_stmt_end(rctx, true);
    }
}

static void render_skip_peek(RenderContext& rctx) {
    std::ostringstream& os = rctx.os;
    const opt_t* opts = rctx.opts;

    DCHECK(opts->api == Api::DEFAULT);
    os << indent(rctx.ind, opts->indent_str) << opts->var_char << " = ";
    yych_conv(os, opts);
    os << "*++" << opts->api_cursor;
    render_stmt_end(rctx, true);
}

static void render_peek_skip(RenderContext& rctx) {
    std::ostringstream& os = rctx.os;
    const opt_t* opts = rctx.opts;

    DCHECK(opts->api == Api::DEFAULT);
    os << indent(rctx.ind, opts->indent_str) << opts->var_char << " = ";
    yych_conv(os, opts);
    os << "*" << opts->api_cursor << "++";
    render_stmt_end(rctx, true);
}

static void render_skip_backup(RenderContext& rctx) {
    const opt_t* opts = rctx.opts;

    DCHECK(opts->api == Api::DEFAULT);
    rctx.os << indent(rctx.ind, opts->indent_str) << opts->api_marker << " = ++" << opts->api_cursor;
    render_stmt_end(rctx, true);
}

static void render_backup_skip(RenderContext& rctx) {
    const opt_t* opts = rctx.opts;

    DCHECK(opts->api == Api::DEFAULT);
    rctx.os << indent(rctx.ind, opts->indent_str) << opts->api_marker << " = " << opts->api_cursor
            << "++";
    render_stmt_end(rctx, true);
}

static void render_backup_peek(RenderContext& rctx) {
    std::ostringstream& os = rctx.os;
    const opt_t* opts = rctx.opts;

    DCHECK(opts->api == Api::DEFAULT);
    os << indent(rctx.ind, opts->indent_str) << opts->var_char << " = ";
    yych_conv(os, opts);
    os << "*(" << opts->api_marker << " = " << opts->api_cursor << ")";
    render_stmt_end(rctx, true);
}

static void render_skip_backup_peek(RenderContext& rctx) {
    std::ostringstream& os = rctx.os;
    const opt_t* opts = rctx.opts;

    DCHECK(opts->api == Api::DEFAULT);
    os << indent(rctx.ind, opts->indent_str) << opts->var_char << " = ";
    yych_conv(os, opts);
    os << "*(" << opts->api_marker << " = ++" << opts->api_cursor << ")";
    render_stmt_end(rctx, true);
}

static void render_backup_peek_skip(RenderContext& rctx) {
    std::ostringstream& os = rctx.os;
    const opt_t* opts = rctx.opts;

    DCHECK(opts->api == Api::DEFAULT);
    os << indent(rctx.ind, opts->indent_str) << opts->var_char << " = ";
    yych_conv(os, opts);
    os << "*(" << opts->api_marker << " = " << opts->api_cursor << "++)";
    render_stmt_end(rctx, true);
}

static void render_abort(RenderContext& rctx) {
    std::ostringstream& os = rctx.os;
    const opt_t* opts = rctx.opts;

    os << indent(rctx.ind, opts->indent_str);
    switch (opts->lang) {
    case Lang::C:
        DCHECK(opts->state_abort);
        os << "abort();";
        break;
    case Lang::GO:
        os << "panic(\"internal lexer error\")";
        break;
    case Lang::RUST:
        os << "panic!(\"internal lexer error\")";
        break;
    }
    os << std::endl;
    ++rctx.line;
}

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

class RenderTable : public OutputCallback {
    RenderContext& rctx;
    const CodeTable* code;
    const size_t ncols;
    const size_t nrows;
    size_t curr_col;
    size_t last_col;
    size_t curr_row;
    size_t last_row;
    size_t maxlen;

  public:
    RenderTable(RenderContext& rctx, const CodeTable* code)
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

    FORBID_COPY(RenderTable);
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
        bool oneline = rctx.stx.specialize_oneline_if()
            && code->ifte.oneline
            && oneline_stmt_list(code->ifte.if_code)
            && code->ifte.else_code == nullptr;
        RenderIfThenElse callback(rctx, &code->ifte, oneline);
        const char* conf = oneline ? "code:if_then_oneline" : "code:if_then_else";
        rctx.stx.gen_code(rctx.os, rctx.opts, conf, callback);
        break;
    }
    case CodeKind::SWITCH: {
        RenderSwitch callback(rctx, &code->swch);
        rctx.stx.gen_code(rctx.os, rctx.opts, "code:switch", callback);
        break;
    }
    case CodeKind::BLOCK:
        render_block(rctx, &code->block);
        break;
    case CodeKind::FUNC:
        render_func(rctx, &code->func);
        break;
    case CodeKind::LOOP: {
        RenderLoop callback(rctx, code->loop);
        rctx.stx.gen_code(rctx.os, rctx.opts, "code:loop", callback);
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
        os << indent(ind, opts->indent_str) << code->text << std::endl;
        line += count_lines_text(code->text) + 1;
        break;
    case CodeKind::RAW:
        os.write(code->raw.data, static_cast<std::streamsize>(code->raw.size));
        for (size_t i = 0; i < code->raw.size; ++i) {
            if (code->raw.data[i] == '\n') ++line;
        }
        break;
    case CodeKind::ABORT:
        render_abort(rctx);
        break;
    case CodeKind::SKIP:
        render_skip(rctx);
        break;
    case CodeKind::PEEK:
        render_peek(rctx);
        break;
    case CodeKind::BACKUP:
        render_backup(rctx);
        break;
    case CodeKind::PEEK_SKIP:
        render_peek_skip(rctx);
        break;
    case CodeKind::SKIP_PEEK:
        render_skip_peek(rctx);
        break;
    case CodeKind::SKIP_BACKUP:
        render_skip_backup(rctx);
        break;
    case CodeKind::BACKUP_SKIP:
        render_backup_skip(rctx);
        break;
    case CodeKind::BACKUP_PEEK:
        render_backup_peek(rctx);
        break;
    case CodeKind::BACKUP_PEEK_SKIP:
        render_backup_peek_skip(rctx);
        break;
    case CodeKind::SKIP_BACKUP_PEEK:
        render_skip_backup_peek(rctx);
        break;
    case CodeKind::LINE_INFO_INPUT:
        render_line_info(os, code->loc.line, rctx.msg.filenames[code->loc.file], opts);
        ++line;
        break;
    case CodeKind::LINE_INFO_OUTPUT:
        render_line_info(os, rctx.line + 1, rctx.file, opts);
        ++line;
        break;
    case CodeKind::VAR: {
        RenderVar callback(rctx, &code->var);
        rctx.stx.gen_code(rctx.os, rctx.opts, "code:var", callback);
        break;
    }
    case CodeKind::LABEL:
        render_label(rctx, code->label);
        break;
    case CodeKind::TABLE: {
        RenderTable callback(rctx, code->table);
        rctx.stx.gen_code(rctx.os, rctx.opts, "code:array", callback);
        break;
    }
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
    RenderContext rctx(output.stx, output.msg, filename);
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
