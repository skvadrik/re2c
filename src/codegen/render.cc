#include <assert.h>

#include "config.h"
#include "src/codegen/code.h"
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
    }
}

static bool oneline_if(const CodeIfTE *code, const opt_t *opts)
{
    const Code *first = code->if_code->head;
    return first
        && first->next == NULL
        && (first->kind == Code::STMT || first->kind == Code::TEXT)
        && opts->lang != LANG_GO // Go requires braces
        && code->else_code == NULL
        && code->oneline;
}

static void render_if_then_else(RenderContext &rctx, const CodeIfTE *code)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;
    const Code *first = code->if_code->head;

    os << indent(rctx.ind, opts->indString) << "if (" << code->if_cond << ") ";
    DASSERT(count_lines_text(code->if_cond) == 0);

    if (oneline_if(code, opts)) {
        os << first->text;
        if (first->kind == Code::STMT) os << ";";
        os << std::endl;
        DASSERT(count_lines_text(first->text) == 0);
        ++rctx.line;
    }
    else {
        os << "{" << std::endl;
        ++rctx.line;
        for (const Code *s = first; s; s = s->next) {
            ++rctx.ind;
            render(rctx, s);
            --rctx.ind;
        }
        os << indent(rctx.ind, opts->indString) << "}";
        if (code->else_code) {
            if (code->else_cond) {
                os << " else if (" << code->else_cond << ") {" << std::endl;
                DASSERT(count_lines_text(code->else_cond) == 0);
            }
            else {
                os << " else {" << std::endl;
            }
            ++rctx.line;
            for (const Code *s = code->else_code->head; s; s = s->next) {
                ++rctx.ind;
                render(rctx, s);
                --rctx.ind;
            }
            os << indent(rctx.ind, opts->indString) << "}";
        }
        os << std::endl;
        ++rctx.line;
    }
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

static void render_var(RenderContext &rctx, const CodeVar *var)
{
    std::ostringstream &os = rctx.os;

    os << indent(rctx.ind, rctx.opts->indString);
    switch (rctx.opts->lang) {
        case LANG_C:
            os << var->type << " " << var->name;
            if (var->init) {
                os << " = " << var->init;
            }
            os << ";";
            break;
        case LANG_GO:
            if (var->init) {
                os << var->name << " := " << var->init;
            }
            else {
                os << "var " << var->name << " " << var->type;
            }
            break;
    }
    os << std::endl;
    ++rctx.line;
}

static bool oneline_case(const CodeCase *code, const opt_t *opts)
{
    const Code *first = code->body->head;
    return code->kind == CodeCase::RANGES
        && first
        && first->next == NULL
        && first->kind == Code::STMT
        && opts->lang != LANG_GO; // gofmt prefers cases on a new line
}

static void render_case(RenderContext &rctx, const CodeCase *code, bool defcase)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;
    const uint32_t ind = rctx.ind;
    const Code *first = code->body->head;

    // TOOD: deduplicate "default" cases
    if (defcase || code->kind == CodeCase::DEFAULT) {
        os << indent(ind, opts->indString) << "default:";
    }
    else if (code->kind == CodeCase::NUMBER) {
        os << indent(ind, opts->indString) << "case " << code->number << ":";
    }
    else if (code->kind == CodeCase::STRING) {
        os << indent(ind, opts->indString) << "case " << code->string << ":";
    }
    else {
        const Enc &enc = opts->encoding;
        const bool ebcdic = enc.type() == Enc::EBCDIC;
        const size_t nranges = code->gocase->nranges;
        const uint32_t *ranges = code->gocase->ranges;

        for (uint32_t i = 0; i < nranges; ++i) {
            const uint32_t low = ranges[2 * i];
            const uint32_t upp = ranges[2 * i + 1];

            for (uint32_t c = low; c < upp; ++c) {
                os << indent(ind, opts->indString) << "case ";
                prtChOrHex(os, c, enc.szCodeUnit(), ebcdic, opts->target == TARGET_DOT);
                os << ":";
                if (opts->dFlag && ebcdic) {
                    const uint32_t c2 = enc.decodeUnsafe(c);
                    if (is_print(c2)) {
                        os << " /* " << static_cast<char>(c2) << " */";
                    }
                }

                const bool last_case = i == nranges - 1 && c == upp - 1;
                if (!last_case) {
                    if (opts->lang == LANG_GO) {
                        os << std::endl;
                        os << indent(ind + 1, opts->indString) << "fallthrough";
                        ++rctx.line;
                    }
                    os << std::endl;
                    ++rctx.line;
                }
            }
        }
    }

    if (oneline_case(code, opts)) {
        os << opts->indString << first->text << ";" << std::endl;
        ++rctx.line;
    }
    else {
        os << std::endl;
        ++rctx.line;
        for (const Code *s = first; s; s = s->next) {
            ++rctx.ind;
            render(rctx, s);
            --rctx.ind;
        }
    }
}

static void render_switch(RenderContext &rctx, const CodeSwitch *code)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;
    const uint32_t ind = rctx.ind;

    os << indent(ind, opts->indString) << "switch (" << code->expr << ") {\n";
    ++rctx.line;

    CodeCase *first = code->cases->head; // default
    DASSERT(first);

    if (code->impdef) {
        for (const CodeCase *c = first->next; c; c = c->next) {
            render_case(rctx, c, false);
        }
        render_case(rctx, first, true);
    }
    else {
        for (const CodeCase *c = first; c; c = c->next) {
            render_case(rctx, c, false);
        }
    }

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

static inline void yych_conv(std::ostream &os, const opt_t *opts)
{
    if (opts->yychConversion) {
        os << "(" <<  opts->yyctype << ")";
    }
}

static inline void render_stmt_end(RenderContext &rctx)
{
    if (rctx.opts->lang != LANG_GO) rctx.os << ";";
    rctx.os << std::endl;
    ++rctx.line;
}

static void render_peek(RenderContext &rctx)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;

    os << indent(rctx.ind, opts->indString) << opts->yych << " = ";
    yych_conv(os, opts);
    if (opts->input_api == INPUT_CUSTOM) {
        os << opts->yypeek;
        if (opts->decorate) os << " ()";
    }
    else {
        os << "*" << opts->yycursor;
    }
    render_stmt_end(rctx);
}

static void render_skip(RenderContext &rctx)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;

    os << indent(rctx.ind, opts->indString);
    if (opts->input_api == INPUT_CUSTOM) {
        os << opts->yyskip;
        if (opts->decorate) os << " ()";
    }
    else {
        os << "++" << opts->yycursor;
    }
    render_stmt_end(rctx);
}

static void render_backup(RenderContext &rctx)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;

    os << indent(rctx.ind, opts->indString);
    if (opts->input_api == INPUT_CUSTOM) {
        os << opts->yybackup;
        if (opts->decorate) os << " ()";
    }
    else {
        os << opts->yymarker << " = " << opts->yycursor;
    }
    render_stmt_end(rctx);
}

static void render_skip_peek(RenderContext &rctx)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;

    DASSERT(opts->input_api == INPUT_DEFAULT);
    os << indent(rctx.ind, opts->indString) << opts->yych << " = ";
    yych_conv(os, opts);
    os << "*++" << opts->yycursor;
    render_stmt_end(rctx);
}

static void render_peek_skip(RenderContext &rctx)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;

    DASSERT(opts->input_api == INPUT_DEFAULT);
    os << indent(rctx.ind, opts->indString) << opts->yych << " = ";
    yych_conv(os, opts);
    os << "*" << opts->yycursor << "++";
    render_stmt_end(rctx);
}

static void render_skip_backup(RenderContext &rctx)
{
    const opt_t *opts = rctx.opts;

    DASSERT(opts->input_api == INPUT_DEFAULT);
    rctx.os << indent(rctx.ind, opts->indString) << opts->yymarker << " = ++"
        << opts->yycursor;
    render_stmt_end(rctx);
}

static void render_backup_skip(RenderContext &rctx)
{
    const opt_t *opts = rctx.opts;

    DASSERT(opts->input_api == INPUT_DEFAULT);
    rctx.os << indent(rctx.ind, opts->indString) << opts->yymarker << " = "
        << opts->yycursor << "++";
    render_stmt_end(rctx);
}

static void render_backup_peek(RenderContext &rctx)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;

    DASSERT(opts->input_api == INPUT_DEFAULT);
    os << indent(rctx.ind, opts->indString) << opts->yych << " = ";
    yych_conv(os, opts);
    os << "*(" << opts->yymarker << " = " << opts->yycursor << ")";
    render_stmt_end(rctx);
}

static void render_skip_backup_peek(RenderContext &rctx)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;

    DASSERT(opts->input_api == INPUT_DEFAULT);
    os << indent(rctx.ind, opts->indString) << opts->yych << " = ";
    yych_conv(os, opts);
    os << "*(" << opts->yymarker << " = ++" << opts->yycursor << ")";
    render_stmt_end(rctx);
}

static void render_backup_peek_skip(RenderContext &rctx)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;

    DASSERT(opts->input_api == INPUT_DEFAULT);
    os << indent(rctx.ind, opts->indString) << opts->yych << " = ";
    yych_conv(os, opts);
    os << "*(" << opts->yymarker << " = " << opts->yycursor << "++)";
    render_stmt_end(rctx);
}

void render(RenderContext &rctx, const Code *code)
{
    std::ostringstream &os = rctx.os;
    const opt_t *opts = rctx.opts;
    const uint32_t ind = rctx.ind;
    uint32_t &line = rctx.line;

    switch (code->kind) {
        case Code::EMPTY:
            break;
        case Code::IF_THEN_ELSE:
            render_if_then_else(rctx, &code->ifte);
            break;
        case Code::SWITCH:
            render_switch(rctx, &code->swch);
            break;
        case Code::BLOCK:
            render_block(rctx, &code->block);
            break;
        case Code::FUNC:
            render_func(rctx, &code->func);
            break;
        case Code::TEXT_RAW:
            os << code->text << std::endl;
            line += count_lines_text(code->text) + 1;
            break;
        case Code::STMT:
            os << indent(ind, opts->indString) << code->text;
            line += count_lines_text(code->text);
            render_stmt_end(rctx);
            break;
        case Code::TEXT:
            os << indent(ind, opts->indString) << code->text << std::endl;
            line += count_lines_text(code->text) + 1;
            break;
        case Code::RAW:
            os.write(code->raw.data, static_cast<std::streamsize>(code->raw.size));
            for (size_t i = 0; i < code->raw.size; ++i) {
                if (code->raw.data[i] == '\n') ++line;
            }
            break;
        case Code::SKIP:
            render_skip(rctx);
            break;
        case Code::PEEK:
            render_peek(rctx);
            break;
        case Code::BACKUP:
            render_backup(rctx);
            break;
        case Code::PEEK_SKIP:
            render_peek_skip(rctx);
            break;
        case Code::SKIP_PEEK:
            render_skip_peek(rctx);
            break;
        case Code::SKIP_BACKUP:
            render_skip_backup(rctx);
            break;
        case Code::BACKUP_SKIP:
            render_backup_skip(rctx);
            break;
        case Code::BACKUP_PEEK:
            render_backup_peek(rctx);
            break;
        case Code::BACKUP_PEEK_SKIP:
            render_backup_peek_skip(rctx);
            break;
        case Code::SKIP_BACKUP_PEEK:
            render_skip_backup_peek(rctx);
            break;
        case Code::LINE_INFO_INPUT:
            render_line_info(os, code->loc.line,
                rctx.msg.filenames[code->loc.file], opts);
            ++line;
            break;
        case Code::LINE_INFO_OUTPUT:
            render_line_info(os, rctx.line + 1, rctx.file, opts);
            ++line;
            break;
        case Code::VAR:
            render_var(rctx, &code->var);
            break;
        case Code::STAGS:
        case Code::MTAGS:
        case Code::YYMAXFILL:
        case Code::YYMAXNMATCH:
        case Code::YYCH:
        case Code::YYACCEPT:
        case Code::COND_ENUM:
        case Code::COND_GOTO:
        case Code::COND_TABLE:
        case Code::STATE_GOTO:
        case Code::LABEL:
            assert(false); // must have been expanded before
            break;
    }
}

} // namespace re2c
