#include "config.h"
#include "src/codegen/output.h"
#include "src/codegen/helpers.h"
#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/util/check.h"

namespace re2c {

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

static bool oneline_if(const CodeIfTE* code, const opt_t* opts) {
    const Code* first = code->if_code->head;
    return opts->lang == Lang::C // Go and Rust require braces
           && code->oneline
           && code->else_code == nullptr
           && first
           && first->next == nullptr
           && (first->kind == CodeKind::STMT || first->kind == CodeKind::TEXT);
}

static void render_if_nonl(RenderContext& rctx, const char* cond, const Code* then, bool oneline) {
    std::ostringstream& os = rctx.os;
    const opt_t* opts = rctx.opts;

    if (cond) {
        DCHECK(count_lines_text(cond) == 0);
        bool wrap = opts->lang != Lang::RUST;
        os << "if " << (wrap ? "(" : "") << cond << (wrap ? ")" : "")  << " ";
    }

    if (oneline) {
        DCHECK(count_lines_text(then->text) == 0);
        os << then->text;
        if (then->kind == CodeKind::STMT) os << ";";
    } else {
        os << "{" << std::endl;
        ++rctx.line;
        for (const Code* s = then; s; s = s->next) {
            ++rctx.ind;
            render(rctx, s);
            --rctx.ind;
        }
        os << indent(rctx.ind, opts->indent_str) << "}";
    }
}

static void render_if_then_else(RenderContext& rctx, const CodeIfTE* code) {
    std::ostringstream& os = rctx.os;
    const opt_t* opts = rctx.opts;

    bool oneline = oneline_if(code, opts);

    os << indent(rctx.ind, opts->indent_str);
    render_if_nonl(rctx, code->if_cond, code->if_code->head, oneline);
    if (code->else_code) {
        os << " else ";
        render_if_nonl(rctx, code->else_cond, code->else_code->head, oneline);
    }
    os << std::endl;
    ++rctx.line;
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

static const char* var_type_c(VarType type, const opt_t* opts) {
    switch (type) {
    case VarType::INT:
        return "int";
    case VarType::UINT:
        return "unsigned int";
    case VarType::YYCTYPE:
        return opts->api_char_type.c_str();
    }
    return nullptr;
}

static const char* var_type_go(VarType type, const opt_t* opts) {
    switch (type) {
    case VarType::INT:
        return "int";
    case VarType::UINT:
        return "uint";
    case VarType::YYCTYPE:
        return opts->api_char_type.c_str();
    }
    return nullptr;
}

static const char* var_type_rust(VarType type, const opt_t* opts) {
    switch (type) {
    case VarType::INT:
        return "isize";
    case VarType::UINT:
        return "usize";
    case VarType::YYCTYPE:
        return opts->api_char_type.c_str();
    }
    return nullptr;
}

static void render_var(RenderContext& rctx, const CodeVar* var) {
    std::ostringstream& os = rctx.os;
    const opt_t* opts = rctx.opts;

    const std::string& ind = indent(rctx.ind, opts->indent_str);
    switch (opts->lang) {
    case Lang::C:
        os << ind << var_type_c(var->type, opts) << " " << var->name;
        if (var->init) os << " = " << var->init;
        os << ";" << std::endl;
        ++rctx.line;
        break;

    case Lang::GO:
        os << ind;
        if (var->init) {
            os << var->name << " := " << var->init;
        } else {
            os << "var " << var->name << " " << var_type_go(var->type, opts);
        }
        os << std::endl;
        ++rctx.line;
        break;

    case Lang::RUST:
        // In Rust uninitialized variable is an error, but if the compiler is able to see that all
        // paths overwrite the initial value, it warns about unused assignments.
        if (!var->init) os << ind << "#[allow(unused_assignments)]" << std::endl;
        os << ind << "let mut " << var->name << " : " << var_type_rust(var->type, opts) << " = "
                << (var->init ? var->init : "0") << ";" << std::endl;
        rctx.line += 2;
        break;
    }
}

static bool case_on_same_line(const CodeCase* code, const opt_t* opts) {
    const Code* first = code->body->head;
    return first
           && first->next == nullptr
           && (first->kind == CodeKind::STMT || first->kind == CodeKind::TEXT)
           && opts->lang != Lang::GO; // gofmt prefers cases on a new line
}

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

static void render_case_range(
        RenderContext& rctx, int64_t low, int64_t upp, bool last, VarType type) {
    std::ostringstream& os = rctx.os;
    const opt_t* opts = rctx.opts;
    const Enc& enc = opts->encoding;

    os << indent(rctx.ind, opts->indent_str);

    switch (opts->lang) {
    case Lang::C:
        os << "case ";
        render_number(rctx, low, type);
        if (low != upp) {
            os << " ... ";
            render_number(rctx, upp, type);
        } else if (opts->debug && type == VarType::YYCTYPE && enc.type() == Enc::Type::EBCDIC) {
            uint32_t c = enc.decode_unsafe(static_cast<uint32_t>(low));
            if (is_print(c)) os << " /* " << static_cast<char>(c) << " */";
        }
        os << ":";
        if (!last) {
            os << std::endl;
            ++rctx.line;
        }
        break;

    case Lang::GO:
        os << "case ";
        render_number(rctx, low, type);
        for (int64_t c = low + 1; c <= upp; ++c) {
            os << ",";
            render_number(rctx, c, type);
        }
        os << ":";
        if (!last) {
            os << std::endl;
            os << indent(rctx.ind + 1, opts->indent_str) << "fallthrough" << std::endl;
            rctx.line += 2;
        }
        break;

    case Lang::RUST:
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

static void render_case(RenderContext& rctx, const CodeCase* code) {
    std::ostringstream& os = rctx.os;
    const opt_t* opts = rctx.opts;
    const uint32_t ind = rctx.ind;
    const Code* first = code->body->head;

    const char* s_case, *s_then, *s_default;
    if (opts->lang == Lang::RUST) {
        s_case = "";
        s_then = " =>";
        s_default = "_";
    } else {
        s_case = "case ";
        s_then = ":";
        s_default = "default";
    }

    switch (code->kind) {
    case CodeCase::Kind::DEFAULT:
        os << indent(ind, opts->indent_str) << s_default << s_then;
        break;
    case CodeCase::Kind::NUMBER:
        os << indent(ind, opts->indent_str) << s_case << code->number << s_then;
        break;
    case CodeCase::Kind::STRING:
        os << indent(ind, opts->indent_str) << s_case << code->string << s_then;
        break;
    case CodeCase::Kind::RANGES: {
        const size_t nranges = code->ranges->size;
        const int64_t* ranges = code->ranges->elems;
        const VarType type = code->ranges->type;

        for (uint32_t i = 0; i < nranges; ++i) {
            const bool last = i == nranges - 1;
            const int64_t low = ranges[2*i], upp = ranges[2*i + 1];
            DCHECK(low < upp);

            if (opts->lang != Lang::C || opts->case_ranges) {
                render_case_range(rctx, low, upp - 1, last, type);
            } else {
                for (int64_t c = low; c < upp; ++c) {
                    render_case_range(rctx, c, c, last && c == upp - 1, type);
                }
            }
        }
        break;
    }}

    if (case_on_same_line(code, opts)) {
        os << " " << first->text;
        rctx.line += count_lines_text(first->text);
        render_stmt_end(rctx, first->kind == CodeKind::STMT);
    } else {
        // For Rust wrap multi-line cases in braces.
        if (opts->lang == Lang::RUST) os << " {";
        os << std::endl;
        ++rctx.line;
        for (const Code* s = first; s; s = s->next) {
            ++rctx.ind;
            render(rctx, s);
            --rctx.ind;
        }
        if (opts->lang == Lang::RUST) {
            os << indent(rctx.ind, opts->indent_str) << "}" << std::endl;
            ++rctx.line;
        }
    }
}

static void render_switch(RenderContext& rctx, const CodeSwitch* code) {
    std::ostringstream& os = rctx.os;
    const opt_t* opts = rctx.opts;
    const uint32_t ind = rctx.ind;

    os << indent(ind, opts->indent_str);
    if (opts->lang == Lang::RUST) {
        os << "match " << code->expr;
    } else {
        os << "switch (" << code->expr << ")";
    }
    os << " {\n";
    ++rctx.line;

    // Do not indent switch cases for Go, as gofmt prefers them unindented.
    if (opts->lang != Lang::GO) ++rctx.ind;
    for (const CodeCase* c = code->cases->head; c; c = c->next) {
        render_case(rctx, c);
    }
    if (opts->lang != Lang::GO) --rctx.ind;

    os << indent(ind, opts->indent_str) << "}\n";
    ++rctx.line;
}

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

static void render_loop(RenderContext& rctx, const CodeList* loop) {
    std::ostringstream& os = rctx.os;
    const opt_t* opts = rctx.opts;

    switch (opts->lang) {
    case Lang::C:
        os << indent(rctx.ind, opts->indent_str) << "for (;;)";
        break;
    case Lang::GO:
        // In Go label is on a separate line with zero indent.
        if (!opts->label_loop.empty()) {
            os << opts->label_loop << ":" << std::endl;
            ++rctx.line;
        }
        os << indent(rctx.ind, opts->indent_str) << "for";
        break;
    case Lang::RUST:
        os << indent(rctx.ind, opts->indent_str);
        // In Rust label is on the same line, preceding the `loop` keyword.
        if (!opts->label_loop.empty()) os << opts->label_loop << ": ";
        os << "loop";
        break;
    }
    os << " {" << std::endl;
    ++rctx.line;

    ++rctx.ind;
    render_list(rctx, loop);
    --rctx.ind;

    os << indent(rctx.ind, opts->indent_str) << "}" << std::endl;
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

void render(RenderContext& rctx, const Code* code) {
    std::ostringstream& os = rctx.os;
    const opt_t* opts = rctx.opts;
    const uint32_t ind = rctx.ind;
    uint32_t& line = rctx.line;

    switch (code->kind) {
    case CodeKind::EMPTY:
        break;
    case CodeKind::IF_THEN_ELSE:
        render_if_then_else(rctx, &code->ifte);
        break;
    case CodeKind::SWITCH:
        render_switch(rctx, &code->swch);
        break;
    case CodeKind::BLOCK:
        render_block(rctx, &code->block);
        break;
    case CodeKind::FUNC:
        render_func(rctx, &code->func);
        break;
    case CodeKind::LOOP:
        render_loop(rctx, code->loop);
        break;
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
    case CodeKind::VAR:
        render_var(rctx, &code->var);
        break;
    case CodeKind::STAGS:
    case CodeKind::MTAGS:
    case CodeKind::MAXFILL:
    case CodeKind::MAXNMATCH:
    case CodeKind::COND_ENUM:
    case CodeKind::COND_TABLE:
    case CodeKind::STATE_GOTO:
    case CodeKind::LABEL:
    case CodeKind::DFAS:
        UNREACHABLE(); // must have been expanded before
    }
}

} // namespace re2c
