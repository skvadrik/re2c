#include <sstream>

#include "src/codegen/indent.h"
#include "src/codegen/input_api.h"
#include "src/globals.h"

namespace re2c
{

InputAPI::type_t InputAPI::type () const
{
	return type_;
}

void InputAPI::set (type_t t)
{
	type_ = t;
}

std::string InputAPI::expr_peek ()
{
	std::string s;
	switch (type_)
	{
		case DEFAULT:
			s = "*" + opts.mapCodeName["YYCURSOR"];
			break;
		case CUSTOM:
			s = opts.mapCodeName["YYPEEK"] + " ()";
			break;
	}
	return s;
}

std::string InputAPI::expr_peek_save ()
{
	return opts.mapCodeName["yych"] + " = " + opts.yychConversion + expr_peek ();
}

std::string InputAPI::stmt_peek (uint32_t ind)
{
	return indent (ind) + expr_peek_save () + ";\n";
}

std::string InputAPI::stmt_skip (uint32_t ind)
{
	std::string s;
	switch (type_)
	{
		case DEFAULT:
			s = "++" + opts.mapCodeName["YYCURSOR"];
			break;
		case CUSTOM:
			s = opts.mapCodeName["YYSKIP"] + " ()";
			break;
	}
	return indent (ind) + s + ";\n";
}

std::string InputAPI::stmt_backup (uint32_t ind)
{
	std::string s;
	switch (type_)
	{
		case DEFAULT:
			s = opts.mapCodeName["YYMARKER"] + " = " + opts.mapCodeName["YYCURSOR"];
			break;
		case CUSTOM:
			s = opts.mapCodeName["YYBACKUP"] + " ()";
			break;
	}
	return indent (ind) + s + ";\n";
}

std::string InputAPI::stmt_backupctx (uint32_t ind)
{
	std::string s;
	switch (type_)
	{
		case DEFAULT:
			// backward compatibility: '+1' here instead of '++YYCURSOR;' in stmt_restorectx
			s = opts.mapCodeName["YYCTXMARKER"] + " = " + opts.mapCodeName["YYCURSOR"] + " + 1";
			break;
		case CUSTOM:
			s = opts.mapCodeName["YYBACKUPCTX"] + " ()";
			break;
	}
	return indent (ind) + s + ";\n";
}

std::string InputAPI::stmt_restore (uint32_t ind)
{
	std::string s;
	switch (type_)
	{
		case DEFAULT:
			s = opts.mapCodeName["YYCURSOR"] + " = " + opts.mapCodeName["YYMARKER"];
			break;
		case CUSTOM:
			s = opts.mapCodeName["YYRESTORE"] + " ()";
			break;
	}
	return indent (ind) + s + ";\n";
}

std::string InputAPI::stmt_restorectx (uint32_t ind)
{
	std::string s;
	switch (type_)
	{
		case DEFAULT:
			// backward compatibility: 'no ++YYCURSOR;' here; instead '+1' in stmt_backupctx
			s = indent (ind) + opts.mapCodeName["YYCURSOR"] + " = " + opts.mapCodeName["YYCTXMARKER"] + ";\n";
			break;
		case CUSTOM:
			s = indent (ind) + opts.mapCodeName["YYRESTORECTX"] + " ();\n" + stmt_skip (ind);
			break;
	}
	return s;
}

std::string InputAPI::stmt_skip_peek (uint32_t ind)
{
	return type_ == DEFAULT
		? indent (ind) + opts.mapCodeName["yych"] + " = " + opts.yychConversion + "*++" + opts.mapCodeName["YYCURSOR"] + ";\n"
		: stmt_skip (ind) + stmt_peek (ind);
}

std::string InputAPI::stmt_skip_backup (uint32_t ind)
{
	return type_ == DEFAULT
		? indent (ind) + opts.mapCodeName["YYMARKER"] + " = ++" + opts.mapCodeName["YYCURSOR"] + ";\n"
		: stmt_skip (ind) + stmt_backup (ind);
}

std::string InputAPI::stmt_backup_peek (uint32_t ind)
{
	return type_ == DEFAULT
		? indent (ind) + opts.mapCodeName["yych"] + " = " + opts.yychConversion + "*(" + opts.mapCodeName["YYMARKER"] + " = " + opts.mapCodeName["YYCURSOR"] + ");\n"
		: stmt_backup (ind) + stmt_peek (ind);
}

std::string InputAPI::stmt_skip_backup_peek (uint32_t ind)
{
	return type_ == DEFAULT
		? indent (ind) + opts.mapCodeName["yych"] + " = " + opts.yychConversion + "*(" + opts.mapCodeName["YYMARKER"] + " = ++" + opts.mapCodeName["YYCURSOR"] + ");\n"
		: stmt_skip (ind) + stmt_backup (ind) + stmt_peek (ind);
}

std::string InputAPI::expr_lessthan_one ()
{
	return type_ == DEFAULT
		? opts.mapCodeName["YYLIMIT"] + " <= " + opts.mapCodeName["YYCURSOR"]
		: expr_lessthan (1);
}

std::string InputAPI::expr_lessthan (uint32_t n)
{
	std::ostringstream s;
	switch (type_)
	{
		case DEFAULT:
			s << "(" << opts.mapCodeName["YYLIMIT"] << " - " << opts.mapCodeName["YYCURSOR"] << ") < " << n;
			break;
		case CUSTOM:
			s << opts.mapCodeName["YYLESSTHAN"] << " (" << n << ")";
			break;
	}
	return s.str ();
}

} // end namespace re2c
