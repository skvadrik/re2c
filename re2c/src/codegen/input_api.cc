#include <assert.h>
#include <sstream>

#include "src/codegen/emit.h"
#include "src/codegen/input_api.h"

namespace re2c
{

InputAPI::InputAPI ()
	: type_ (DEFAULT)
{}

InputAPI::type_t InputAPI::type () const
{
	return type_;
}

void InputAPI::set (type_t t)
{
	type_ = t;
}

std::string InputAPI::expr_peek(Opt &opts) const
{
	std::string s;
	switch (type_)
	{
		case DEFAULT:
			s = "*" + opts->yycursor;
			break;
		case CUSTOM:
			s = opts->yypeek + " ()";
			break;
	}
	return s;
}

std::string InputAPI::stmt_peek(uint32_t ind, Opt &opts) const
{
	return indent(ind, opts->indString) + opts->yych + " = " + opts.yychConversion()
		+ expr_peek(opts) + ";\n";
}

std::string InputAPI::stmt_skip(uint32_t ind, Opt &opts) const
{
	std::string s;
	switch (type_)
	{
		case DEFAULT:
			s = "++" + opts->yycursor;
			break;
		case CUSTOM:
			s = opts->yyskip + " ()";
			break;
	}
	return indent(ind, opts->indString) + s + ";\n";
}

std::string InputAPI::stmt_backup(uint32_t ind, Opt &opts) const
{
	std::string s;
	switch (type_)
	{
		case DEFAULT:
			s = opts->yymarker + " = " + opts->yycursor;
			break;
		case CUSTOM:
			s = opts->yybackup + " ()";
			break;
	}
	return indent(ind, opts->indString) + s + ";\n";
}

std::string InputAPI::stmt_restore(uint32_t ind, Opt &opts) const
{
	std::string s;
	switch (type_)
	{
		case DEFAULT:
			s = opts->yycursor + " = " + opts->yymarker;
			break;
		case CUSTOM:
			s = opts->yyrestore + " ()";
			break;
	}
	return indent(ind, opts->indString) + s + ";\n";
}

std::string InputAPI::stmt_skip_peek(uint32_t ind, Opt &opts) const
{
	return type_ == DEFAULT
		? indent(ind, opts->indString) + opts->yych + " = " + opts.yychConversion() + "*++" + opts->yycursor + ";\n"
		: stmt_skip(ind, opts) + stmt_peek(ind, opts);
}

std::string InputAPI::stmt_skip_backup(uint32_t ind, Opt &opts) const
{
	return type_ == DEFAULT
		? indent(ind, opts->indString) + opts->yymarker + " = ++" + opts->yycursor + ";\n"
		: stmt_skip(ind, opts) + stmt_backup(ind, opts);
}

std::string InputAPI::stmt_backup_peek(uint32_t ind, Opt &opts) const
{
	return type_ == DEFAULT
		? indent(ind, opts->indString) + opts->yych + " = " + opts.yychConversion() + "*(" + opts->yymarker + " = " + opts->yycursor + ");\n"
		: stmt_backup(ind, opts) + stmt_peek(ind, opts);
}

std::string InputAPI::stmt_skip_backup_peek(uint32_t ind, Opt &opts) const
{
	return type_ == DEFAULT
		? indent(ind, opts->indString) + opts->yych + " = " + opts.yychConversion() + "*(" + opts->yymarker + " = ++" + opts->yycursor + ");\n"
		: stmt_skip(ind, opts) + stmt_backup(ind, opts) + stmt_peek(ind, opts);
}

std::string InputAPI::expr_lessthan(size_t n, Opt &opts) const
{
	std::ostringstream s;
	if (type_ == CUSTOM) {
		s << opts->yylessthan << " (" << n << ")";
	} else if (n == 1) {
		s << opts->yylimit << " <= " << opts->yycursor;
	} else {
		s << "(" << opts->yylimit << " - " << opts->yycursor << ") < " << n;
	}
	return s.str ();
}

} // end namespace re2c
