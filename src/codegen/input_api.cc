#include <sstream>

#include "src/codegen/emit.h"
#include "src/codegen/input_api.h"
#include "src/options/opt.h"
#include "src/debug/debug.h"


namespace re2c {

std::string output_expr_peek(const opt_t *opts)
{
    return opts->input_api == INPUT_DEFAULT
        ? "*" + opts->yycursor
        : opts->yypeek + " ()";
}

std::string output_restore(uint32_t ind, const opt_t *opts)
{
    std::string s = opts->input_api == INPUT_DEFAULT
        ? opts->yycursor + " = " + opts->yymarker
        : opts->yyrestore + " ()";
    return indent(ind, opts->indString) + s + ";\n";
}

std::string output_expr_lessthan(size_t n, const opt_t *opts)
{
    std::ostringstream s;
    if (opts->input_api == INPUT_CUSTOM) {
        s << opts->yylessthan << " (" << n << ")";
    } else if (n == 1) {
        s << opts->yylimit << " <= " << opts->yycursor;
    } else {
        s << "(" << opts->yylimit << " - " << opts->yycursor << ") < " << n;
    }
    return s.str ();
}

static std::string yych_conv(const opt_t *opts)
{
    return opts->yychConversion
        ? "(" + opts->yyctype + ")"
        : "";
}

void output_peek(std::ostream &o, uint32_t ind, const opt_t *opts)
{
    o << indent(ind, opts->indString) << opts->yych << " = " << yych_conv(opts);
    if (opts->input_api == INPUT_CUSTOM) {
        o << opts->yypeek << " ()";
    } else {
        o << "*" << opts->yycursor;
    }
    o << ";\n";
}

void output_skip(std::ostream &o, uint32_t ind, const opt_t *opts)
{
    o << indent(ind, opts->indString);
    if (opts->input_api == INPUT_CUSTOM) {
        o << opts->yyskip << " ()";
    } else {
        o << "++" << opts->yycursor;
    }
    o << ";\n";
}

void output_backup(std::ostream &o, uint32_t ind, const opt_t *opts)
{
    o << indent(ind, opts->indString);
    if (opts->input_api == INPUT_CUSTOM) {
        o << opts->yybackup << " ()";
    } else {
        o << opts->yymarker << " = " << opts->yycursor;
    }
    o << ";\n";
}

void output_skip_peek(std::ostream &o, uint32_t ind, const opt_t *opts)
{
    DASSERT(opts->input_api == INPUT_DEFAULT);
    o << indent(ind, opts->indString) << opts->yych << " = "
        << yych_conv(opts) << "*++" << opts->yycursor << ";\n";
}

void output_peek_skip(std::ostream &o, uint32_t ind, const opt_t *opts)
{
    DASSERT(opts->input_api == INPUT_DEFAULT);
    o << indent(ind, opts->indString) << opts->yych << " = "
        << yych_conv(opts) << "*" << opts->yycursor << "++;\n";
}

void output_skip_backup(std::ostream &o, uint32_t ind, const opt_t *opts)
{
    DASSERT(opts->input_api == INPUT_DEFAULT);
    o << indent(ind, opts->indString) << opts->yymarker << " = ++"
        << opts->yycursor << ";\n";
}

void output_backup_skip(std::ostream &o, uint32_t ind, const opt_t *opts)
{
    DASSERT(opts->input_api == INPUT_DEFAULT);
    o << indent(ind, opts->indString) << opts->yymarker << " = "
        << opts->yycursor << "++;\n";
}

void output_backup_peek(std::ostream &o, uint32_t ind, const opt_t *opts)
{
    DASSERT(opts->input_api == INPUT_DEFAULT);
    o << indent(ind, opts->indString) << opts->yych << " = "
        << yych_conv(opts) << "*(" << opts->yymarker << " = "
        << opts->yycursor << ");\n";
}

void output_skip_backup_peek(std::ostream &o, uint32_t ind, const opt_t *opts)
{
    DASSERT(opts->input_api == INPUT_DEFAULT);
    o << indent(ind, opts->indString) << opts->yych << " = "
        << yych_conv(opts) << "*(" << opts->yymarker << " = ++"
        << opts->yycursor << ");\n";
}

void output_backup_peek_skip(std::ostream &o, uint32_t ind, const opt_t *opts)
{
    DASSERT(opts->input_api == INPUT_DEFAULT);
    o << indent(ind, opts->indString) << opts->yych << " = "
        << yych_conv(opts) << "*(" << opts->yymarker << " = "
        << opts->yycursor << "++);\n";
}

} // end namespace re2c
