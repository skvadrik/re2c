#include <assert.h>

#include "config.h"
#include "src/codegen/code.h"
#include "src/codegen/helpers.h"
#include "src/msg/msg.h"
#include "src/options/opt.h"


namespace re2c {

static uint32_t count_lines_text(const char *text)
{
    DASSERT(text);
    uint32_t lc = 0;
    for (const char *s = text; *s; ++s) {
        if (*s == '\n') ++lc;
    }
    return lc;
}

static inline void render_stmt_end(RenderContext &rctx, bool semi)
{
    if (semi && rctx.opts->lang != LANG_GO) rctx.os << ";";
    rctx.os << std::endl;
    ++rctx.line;
}

static void render_list(RenderContext &rctx, const CodeList *code)
{
    for (const Code *s = code->head; s; s = s->next) {
        render(rctx, s);
    }
}

static void render_line_info(std::ostream &o, uint32_t line, const std::string &fname,
    const opt_t *opts)
{
    if (opts->iFlag) return;

    switch (opts->lang) {
    case LANG_GO:
        // Go: //line <filename>:<line-number>
        o << "//line \"" << fname << "\":" << line << "\n";
        break;
    case LANG_C:
        // C/C++: #line <line-number> <filename>
        o << "#line " << line << " \"" << fname << "\"\n";
        break;
    case LANG_RUST:
        // For Rust line directives should be removed by now, as they confuse rendering
        // functions into formating a block as multiline even it fits on a single line.
        DASSERT(false);
        break;
    }
}

static bool oneline_if(const CodeIfTE *code, const opt_t *opts)
{
    const Code *first = code->if_code->head;
    return first
        && first->next == NULL
        && (first->kind == CODE_STMT || first->kind == CODE_TEXT)
        && opts->lang != LANG_GO // Go requires braces
        && code->else_code == NULL
        && code->oneline;
}

static void render_if_nonl(RenderContext &rctx, const char *cond, const Code *then,
    bool oneline)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;

    if (cond) {
        DASSERT(count_lines_text(cond) == 0);
        bool wrap = opts->lang != LANG_RUST;
        os << "if " << (wrap ? "(" : "") << cond << (wrap ? ")" : "")  << " ";
    }

    if (oneline) {
        DASSERT(count_lines_text(then->text) == 0);
        os << then->text;
        if (then->kind == CODE_STMT) os << ";";
    } else {
        os << "{" << std::endl;
        ++rctx.line;
        for (const Code *s = then; s; s = s->next) {
            ++rctx.ind;
            render(rctx, s);
            --rctx.ind;
        }
        os << indent(rctx.ind, opts->indString) << "}";
    }
}

static void render_if_then_else(RenderContext &rctx, const CodeIfTE *code)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;

    bool oneline = oneline_if(code, opts);

    os << indent(rctx.ind, opts->indString);
    render_if_nonl(rctx, code->if_cond, code->if_code->head, oneline);
    if (code->else_code) {
        os << " else ";
        render_if_nonl(rctx, code->else_cond, code->else_code->head, oneline);
    }
    os << std::endl;
    ++rctx.line;
}

static void render_block(RenderContext &rctx, const CodeBlock *code)
{
    switch (code->fmt) {
    case CodeBlock::WRAPPED:
        rctx.os << indent(rctx.ind, rctx.opts->indString) << "{" << std::endl;
        ++rctx.line;
        ++rctx.ind;
        render_list(rctx, code->stmts);
        --rctx.ind;
        rctx.os << indent(rctx.ind, rctx.opts->indString) << "}" << std::endl;
        ++rctx.line;
        break;
    case CodeBlock::INDENTED:
        ++rctx.ind;
        render_list(rctx, code->stmts);
        --rctx.ind;
        break;
    case CodeBlock::RAW:
        render_list(rctx, code->stmts);
        break;
    }
}

static const char *var_type_c(VarType type, const opt_t *opts)
{
    switch (type) {
    case VAR_TYPE_INT:     return "int";
    case VAR_TYPE_UINT:    return "unsigned int";
    case VAR_TYPE_YYCTYPE: return opts->yyctype.c_str();
    default:               return NULL;
    }
}

static const char *var_type_go(VarType type, const opt_t *opts)
{
    switch (type) {
    case VAR_TYPE_INT:     return "int";
    case VAR_TYPE_UINT:    return "uint";
    case VAR_TYPE_YYCTYPE: return opts->yyctype.c_str();
    default:               return NULL;
    }
}

static const char *var_type_rust(VarType type, const opt_t *opts)
{
    switch (type) {
    case VAR_TYPE_INT:     return "isize";
    case VAR_TYPE_UINT:    return "usize";
    case VAR_TYPE_YYCTYPE: return opts->yyctype.c_str();
    default:               return NULL;
    }
}

static void render_var(RenderContext &rctx, const CodeVar *var)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;

    const std::string &ind = indent(rctx.ind, opts->indString);
    switch (opts->lang) {
    case LANG_C:
        os << ind << var_type_c(var->type, opts) << " " << var->name;
        if (var->init) os << " = " << var->init;
        os << ";" << std::endl;
        ++rctx.line;
        break;

    case LANG_GO:
        os << ind;
        if (var->init) {
            os << var->name << " := " << var->init;
        } else {
            os << "var " << var->name << " " << var_type_go(var->type, opts);
        }
        os << std::endl;
        ++rctx.line;
        break;

    case LANG_RUST:
        // In Rust uninitialized variable is an error, but if the compiler is able to see
        // that all paths overwrite the initial value, it warns about unused assignments.
        if (!var->init) os << ind << "#[allow(unused_assignments)]" << std::endl;
        os << ind << "let mut " << var->name << " : " << var_type_rust(var->type, opts);
        os << " = " << (var->init ? var->init : "0");
        os << ";" << std::endl;
        rctx.line += 2;
        break;
    }
}

static bool case_on_same_line(const CodeCase *code, const opt_t *opts)
{
    const Code *first = code->body->head;
    return first
        && first->next == NULL
        && (first->kind == CODE_STMT || first->kind == CODE_TEXT)
        && opts->lang != LANG_GO; // gofmt prefers cases on a new line
}

static void render_number(RenderContext &rctx, int64_t num, VarType type) {
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;
    const Enc &enc = opts->encoding;
    bool hex = opts->lang == LANG_RUST || enc.type() == Enc::EBCDIC;

    switch (type) {
    case VAR_TYPE_UINT:
        DASSERT(num >= 0);
        os << static_cast<uint32_t>(num);
        break;
    case VAR_TYPE_INT:
        os << num;
        break;
    case VAR_TYPE_YYCTYPE:
        DASSERT(num >= 0);
        prtChOrHex(os, static_cast<uint32_t>(num), enc.szCodeUnit(), hex, /*dot*/ false);
        break;
    }
}

static void render_case_range(RenderContext &rctx, int64_t low, int64_t upp, bool last,
        VarType type) {
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;
    const Enc &enc = opts->encoding;

    os << indent(rctx.ind, opts->indString);

    switch (opts->lang) {
    case LANG_C:
        os << "case ";
        render_number(rctx, low, type);
        if (low != upp) {
            os << " ... ";
            render_number(rctx, upp, type);
        } else if (opts->dFlag && type == VAR_TYPE_YYCTYPE && enc.type() == Enc::EBCDIC) {
            uint32_t c = enc.decodeUnsafe(static_cast<uint32_t>(low));
            if (is_print(c)) os << " /* " << static_cast<char>(c) << " */";
        }
        os << ":";
        if (!last) {
            os << std::endl;
            ++rctx.line;
        }
        break;

    case LANG_GO:
        os << "case ";
        render_number(rctx, low, type);
        for (int64_t c = low + 1; c <= upp; ++c) {
            os << ",";
            render_number(rctx, c, type);
        }
        os << ":";
        if (!last) {
            os << std::endl;
            os << indent(rctx.ind + 1, opts->indString) << "fallthrough" << std::endl;
            rctx.line += 2;
        }
        break;

    case LANG_RUST:
        render_number(rctx, low, type);
        if (low != upp) {
            os << " ..= ";
            render_number(rctx, upp, type);
        }
        if (last) {
            os << " =>";
        } else {
            os << " |" << std::endl;
            ++rctx.line;
        }
        break;
    }
}

static void render_case(RenderContext &rctx, const CodeCase *code)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;
    const uint32_t ind = rctx.ind;
    const Code *first = code->body->head;

    const char *s_case, *s_then, *s_default;
    if (opts->lang == LANG_RUST) {
        s_case = "";
        s_then = " =>";
        s_default = "_";
    } else {
        s_case = "case ";
        s_then = ":";
        s_default = "default";
    }

    if (code->kind == CodeCase::DEFAULT) {
        os << indent(ind, opts->indString) << s_default << s_then;
    } else if (code->kind == CodeCase::NUMBER) {
        os << indent(ind, opts->indString) << s_case << code->number << s_then;
    } else if (code->kind == CodeCase::STRING) {
        os << indent(ind, opts->indString) << s_case << code->string << s_then;
    } else {
        const size_t nranges = code->ranges->size;
        const int64_t *ranges = code->ranges->elems;
        const VarType type = code->ranges->type;

        for (uint32_t i = 0; i < nranges; ++i) {
            const bool last = i == nranges - 1;
            const int64_t low = ranges[2*i], upp = ranges[2*i + 1];
            DASSERT(low < upp);

            if (opts->lang != LANG_C || opts->case_ranges) {
                render_case_range(rctx, low, upp - 1, last, type);
            } else {
                for (int64_t c = low; c < upp; ++c) {
                    render_case_range(rctx, c, c, last && c == upp - 1, type);
                }
            }
        }
    }

    if (case_on_same_line(code, opts)) {
        os << " " << first->text;
        rctx.line += count_lines_text(first->text);
        render_stmt_end(rctx, first->kind == CODE_STMT);
    } else {
        // For Rust wrap multi-line cases in braces.
        if (opts->lang == LANG_RUST) os << " {";
        os << std::endl;
        ++rctx.line;
        for (const Code *s = first; s; s = s->next) {
            ++rctx.ind;
            render(rctx, s);
            --rctx.ind;
        }
        if (opts->lang == LANG_RUST) {
            os << indent(rctx.ind, opts->indString) << "}" << std::endl;
            ++rctx.line;
        }
    }
}

static void render_switch(RenderContext &rctx, const CodeSwitch *code)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;
    const uint32_t ind = rctx.ind;

    os << indent(ind, opts->indString);
    if (opts->lang == LANG_RUST) {
        os << "match " << code->expr;
    } else {
        os << "switch (" << code->expr << ")";
    }
    os << " {\n";
    ++rctx.line;

    // Do not indent switch cases for Go, as gofmt prefers them unindented.
    if (opts->lang != LANG_GO) ++rctx.ind;
    for (const CodeCase *c = code->cases->head; c; c = c->next) {
        render_case(rctx, c);
    }
    if (opts->lang != LANG_GO) --rctx.ind;

    os << indent(ind, opts->indString) << "}\n";
    ++rctx.line;
}

static void render_arg(RenderContext &rctx, const CodeArg *arg)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;

    const char *s = arg->arg, *p = s;
    for (; *s; ++s) {
        // remove unescaped newlines and render on a new line
        if (*s == '\n') {
            os.write(p, s - p);
            p = s + 1;
            os << std::endl << indent(rctx.ind + 1, opts->indString);
            ++rctx.line;
        }
    }
    os.write(p, s - p);
}

static void render_func(RenderContext &rctx, const CodeFunc *func)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;
    const CodeArg *first = func->args->head;

    os << indent(rctx.ind, opts->indString) << func->name;
    ++rctx.line;

    // Estimate total length of function call (in characters).
    // Arguments are rendered on one line if the total length does not exceed 80
    // characters (including indentation and the text preceding the list of
    // arguments) , otherwise each argument and the closing parenthesis are
    // rendered on a new line.
    size_t total = rctx.ind * opts->indString.length() + strlen(func->name);
    for (const CodeArg *a = first; a; a = a->next) {
        total += strlen(a->arg) + 2; // +2 for ", "
    }

    if (total < 80) {
        os << "(";
        for (const CodeArg *a = first; a; a = a->next) {
            if (a != first) os << ", ";
            render_arg(rctx, a);
        }
        os << ")";
    }
    else {
        ++rctx.ind;

        // An argument may be broken into multiple lines by inserting unescaped
        // newline characters in the argument string. The text after each
        // newline is "hanged after" the the argument (that is, rendered on the
        // next line with one extra level of indentation).
        os << std::endl;
        for (const CodeArg *a = first; a; a = a->next) {
            const char *sep = a == first ? "( " : ", ";
            os << indent(rctx.ind, opts->indString) << sep;
            render_arg(rctx, a);
            os << std::endl;
            ++rctx.line;
        }
        os << indent(rctx.ind, opts->indString) << ")";

        --rctx.ind;
    }

    os << func->semi << std::endl;
    ++rctx.line;
}

static void render_loop(RenderContext &rctx, const CodeList *loop)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;

    os << indent(rctx.ind, opts->indString);
    switch (opts->lang) {
    case LANG_C:
        os << "for (;;)";
        break;
    case LANG_GO:
        os << "for";
        break;
    case LANG_RUST:
        os << "loop";
        break;
    }
    os << " {" << std::endl;
    ++rctx.line;

    ++rctx.ind;
    render_list(rctx, loop);
    --rctx.ind;

    os << indent(rctx.ind, opts->indString) << "}" << std::endl;
    ++rctx.line;
}

static inline void yych_conv(std::ostream &os, const opt_t *opts)
{
    if (opts->yychConversion) {
        os << "(" <<  opts->yyctype << ")";
    }
}

void gen_peek_expr(std::ostream &os, const opt_t *opts)
{
    yych_conv(os, opts);
    if (opts->input_api == INPUT_DEFAULT) {
        os << "*" << opts->yycursor;
    } else if (opts->lang == LANG_RUST) {
        if (opts->unsafe) os << "unsafe {";
        os << opts->yypeek;
        if (opts->api_style == API_FUNCTIONS) os << "()";
        if (opts->unsafe) os << "}";
    } else {
        os << opts->yypeek;
        if (opts->api_style == API_FUNCTIONS) os << "()";
    }
}

static void render_peek(RenderContext &rctx)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;

    os << indent(rctx.ind, opts->indString) << opts->yych << " = ";
    gen_peek_expr(os, opts);
    render_stmt_end(rctx, true);
}

static void render_skip(RenderContext &rctx)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;

    os << indent(rctx.ind, opts->indString);
    if (opts->input_api == INPUT_CUSTOM) {
        os << opts->yyskip;
        if (opts->api_style == API_FUNCTIONS) {
            os << "()";
            render_stmt_end(rctx, true);
        } else {
            render_stmt_end(rctx, false);
        }
    }
    else {
        os << "++" << opts->yycursor;
        render_stmt_end(rctx, true);
    }
}

static void render_backup(RenderContext &rctx)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;

    os << indent(rctx.ind, opts->indString);
    if (opts->input_api == INPUT_CUSTOM) {
        os << opts->yybackup;
        if (opts->api_style == API_FUNCTIONS) {
            os << "()";
            render_stmt_end(rctx, true);
        } else {
            render_stmt_end(rctx, false);
        }
    }
    else {
        os << opts->yymarker << " = " << opts->yycursor;
        render_stmt_end(rctx, true);
    }
}

static void render_skip_peek(RenderContext &rctx)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;

    DASSERT(opts->input_api == INPUT_DEFAULT);
    os << indent(rctx.ind, opts->indString) << opts->yych << " = ";
    yych_conv(os, opts);
    os << "*++" << opts->yycursor;
    render_stmt_end(rctx, true);
}

static void render_peek_skip(RenderContext &rctx)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;

    DASSERT(opts->input_api == INPUT_DEFAULT);
    os << indent(rctx.ind, opts->indString) << opts->yych << " = ";
    yych_conv(os, opts);
    os << "*" << opts->yycursor << "++";
    render_stmt_end(rctx, true);
}

static void render_skip_backup(RenderContext &rctx)
{
    const opt_t *opts = rctx.opts;

    DASSERT(opts->input_api == INPUT_DEFAULT);
    rctx.os << indent(rctx.ind, opts->indString) << opts->yymarker << " = ++"
        << opts->yycursor;
    render_stmt_end(rctx, true);
}

static void render_backup_skip(RenderContext &rctx)
{
    const opt_t *opts = rctx.opts;

    DASSERT(opts->input_api == INPUT_DEFAULT);
    rctx.os << indent(rctx.ind, opts->indString) << opts->yymarker << " = "
        << opts->yycursor << "++";
    render_stmt_end(rctx, true);
}

static void render_backup_peek(RenderContext &rctx)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;

    DASSERT(opts->input_api == INPUT_DEFAULT);
    os << indent(rctx.ind, opts->indString) << opts->yych << " = ";
    yych_conv(os, opts);
    os << "*(" << opts->yymarker << " = " << opts->yycursor << ")";
    render_stmt_end(rctx, true);
}

static void render_skip_backup_peek(RenderContext &rctx)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;

    DASSERT(opts->input_api == INPUT_DEFAULT);
    os << indent(rctx.ind, opts->indString) << opts->yych << " = ";
    yych_conv(os, opts);
    os << "*(" << opts->yymarker << " = ++" << opts->yycursor << ")";
    render_stmt_end(rctx, true);
}

static void render_backup_peek_skip(RenderContext &rctx)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;

    DASSERT(opts->input_api == INPUT_DEFAULT);
    os << indent(rctx.ind, opts->indString) << opts->yych << " = ";
    yych_conv(os, opts);
    os << "*(" << opts->yymarker << " = " << opts->yycursor << "++)";
    render_stmt_end(rctx, true);
}

static void render_abort(RenderContext &rctx)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;

    os << indent(rctx.ind, opts->indString);
    switch (opts->lang) {
    case LANG_C:
        DASSERT(opts->bUseStateAbort);
        os << "abort();";
        break;
    case LANG_GO:
        os << "panic(\"internal lexer error\")";
        break;
    case LANG_RUST:
        os << "panic!(\"internal lexer error\")";
        break;
    }
    os << std::endl;
    ++rctx.line;
}

void render(RenderContext &rctx, const Code *code)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;
    const uint32_t ind = rctx.ind;
    uint32_t &line = rctx.line;

    switch (code->kind) {
        case CODE_EMPTY:
            break;
        case CODE_IF_THEN_ELSE:
            render_if_then_else(rctx, &code->ifte);
            break;
        case CODE_SWITCH:
            render_switch(rctx, &code->swch);
            break;
        case CODE_BLOCK:
            render_block(rctx, &code->block);
            break;
        case CODE_FUNC:
            render_func(rctx, &code->func);
            break;
        case CODE_LOOP:
            render_loop(rctx, code->loop);
            break;
        case CODE_TEXT_RAW:
            os << code->text << std::endl;
            line += count_lines_text(code->text) + 1;
            break;
        case CODE_STMT:
            os << indent(ind, opts->indString) << code->text;
            line += count_lines_text(code->text);
            render_stmt_end(rctx, true);
            break;
        case CODE_TEXT:
            os << indent(ind, opts->indString) << code->text << std::endl;
            line += count_lines_text(code->text) + 1;
            break;
        case CODE_RAW:
            os.write(code->raw.data, static_cast<std::streamsize>(code->raw.size));
            for (size_t i = 0; i < code->raw.size; ++i) {
                if (code->raw.data[i] == '\n') ++line;
            }
            break;
        case CODE_ABORT:
            render_abort(rctx);
            break;
        case CODE_SKIP:
            render_skip(rctx);
            break;
        case CODE_PEEK:
            render_peek(rctx);
            break;
        case CODE_BACKUP:
            render_backup(rctx);
            break;
        case CODE_PEEK_SKIP:
            render_peek_skip(rctx);
            break;
        case CODE_SKIP_PEEK:
            render_skip_peek(rctx);
            break;
        case CODE_SKIP_BACKUP:
            render_skip_backup(rctx);
            break;
        case CODE_BACKUP_SKIP:
            render_backup_skip(rctx);
            break;
        case CODE_BACKUP_PEEK:
            render_backup_peek(rctx);
            break;
        case CODE_BACKUP_PEEK_SKIP:
            render_backup_peek_skip(rctx);
            break;
        case CODE_SKIP_BACKUP_PEEK:
            render_skip_backup_peek(rctx);
            break;
        case CODE_LINE_INFO_INPUT:
            render_line_info(os, code->loc.line,
                rctx.msg.filenames[code->loc.file], opts);
            ++line;
            break;
        case CODE_LINE_INFO_OUTPUT:
            render_line_info(os, rctx.line + 1, rctx.file, opts);
            ++line;
            break;
        case CODE_VAR:
            render_var(rctx, &code->var);
            break;
        case CODE_STAGS:
        case CODE_MTAGS:
        case CODE_MAXFILL:
        case CODE_MAXNMATCH:
        case CODE_YYCH:
        case CODE_YYACCEPT:
        case CODE_YYSTATE:
        case CODE_COND_ENUM:
        case CODE_COND_GOTO:
        case CODE_COND_TABLE:
        case CODE_STATE_GOTO:
        case CODE_LABEL:
            assert(false); // must have been expanded before
            break;
    }
}

} // namespace re2c
