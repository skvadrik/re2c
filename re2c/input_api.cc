#include <sstream>

#include "globals.h"
#include "indent.h"
#include "input_api.h"

namespace re2c
{

void InputAPI::set (type_t t)
{
	type = t;
}

std::string InputAPI::expr_peek ()
{
	std::string s;
	switch (type)
	{
		case DEFAULT:
			s = "*" + mapCodeName["YYCURSOR"];
			break;
		case CUSTOM:
			s = mapCodeName["RE2C_PEEK"] + " ()";
			break;
	}
	return s;
}

std::string InputAPI::expr_peek_save ()
{
	return mapCodeName["yych"] + " = " + yychConversion + expr_peek ();
}

std::string InputAPI::stmt_peek (uint ind)
{
	return indent (ind) + expr_peek_save () + ";\n";
}

std::string InputAPI::stmt_skip (uint ind)
{
	std::string s;
	switch (type)
	{
		case DEFAULT:
			s = "++" + mapCodeName["YYCURSOR"];
			break;
		case CUSTOM:
			s = mapCodeName["RE2C_SKIP"] + " ()";
			break;
	}
	return indent (ind) + s + ";\n";
}

std::string InputAPI::stmt_backup (uint ind)
{
	std::string s;
	switch (type)
	{
		case DEFAULT:
			s = mapCodeName["YYMARKER"] + " = " + mapCodeName["YYCURSOR"];
			break;
		case CUSTOM:
			s = mapCodeName["RE2C_BACKUP"] + " ()";
			break;
	}
	return indent (ind) + s + ";\n";
}

std::string InputAPI::stmt_backup_ctx (uint ind)
{
	std::string s;
	switch (type)
	{
		case DEFAULT:
			// backward compatibility: '+1' here instead of '++YYCURSOR;' in stmt_restore_ctx
			s = mapCodeName["YYCTXMARKER"] + " = " + mapCodeName["YYCURSOR"] + " + 1";
			break;
		case CUSTOM:
			s = mapCodeName["RE2C_BACKUP_CTX"] + " ()";
			break;
	}
	return indent (ind) + s + ";\n";
}

std::string InputAPI::stmt_restore (uint ind)
{
	std::string s;
	switch (type)
	{
		case DEFAULT:
			s = mapCodeName["YYCURSOR"] + " = " + mapCodeName["YYMARKER"];
			break;
		case CUSTOM:
			s = mapCodeName["RE2C_RESTORE"] + " ()";
			break;
	}
	return indent (ind) + s + ";\n";
}

std::string InputAPI::stmt_restore_ctx (uint ind)
{
	std::string s;
	switch (type)
	{
		case DEFAULT:
			// backward compatibility: 'no ++YYCURSOR;' here; instead '+1' in stmt_backup_ctx
			s = indent (ind) + mapCodeName["YYCURSOR"] + " = " + mapCodeName["YYCTXMARKER"] + ";\n";
			break;
		case CUSTOM:
			s = indent (ind) + mapCodeName["RE2C_RESTORE_CTX"] + " ();\n" + stmt_skip (ind);
			break;
	}
	return s;
}

std::string InputAPI::stmt_skip_peek (uint ind)
{
	return type == DEFAULT
		? indent (ind) + mapCodeName["yych"] + " = " + yychConversion + "*++" + mapCodeName["YYCURSOR"] + ";\n"
		: stmt_skip (ind) + stmt_peek (ind);
}

std::string InputAPI::stmt_skip_backup (uint ind)
{
	return type == DEFAULT
		? indent (ind) + mapCodeName["YYMARKER"] + " = ++" + mapCodeName["YYCURSOR"] + ";\n"
		: stmt_skip (ind) + stmt_backup (ind);
}

std::string InputAPI::stmt_backup_peek (uint ind)
{
	return type == DEFAULT
		? indent (ind) + mapCodeName["yych"] + " = " + yychConversion + "*(" + mapCodeName["YYMARKER"] + " = " + mapCodeName["YYCURSOR"] + ");\n"
		: stmt_backup (ind) + stmt_peek (ind);
}

std::string InputAPI::stmt_skip_backup_peek (uint ind)
{
	return type == DEFAULT
		? indent (ind) + mapCodeName["yych"] + " = " + yychConversion + "*(" + mapCodeName["YYMARKER"] + " = ++" + mapCodeName["YYCURSOR"] + ");\n"
		: stmt_skip (ind) + stmt_backup (ind) + stmt_peek (ind);
}

std::string InputAPI::expr_less_than_one ()
{
	return type == DEFAULT
		? mapCodeName["YYLIMIT"] + " <= " + mapCodeName["YYCURSOR"]
		: expr_less_than (1);
}

std::string InputAPI::expr_less_than (uint n)
{
	std::ostringstream s;
	switch (type)
	{
		case DEFAULT:
			s << "(" << mapCodeName["YYLIMIT"] << " - " << mapCodeName["YYCURSOR"] << ") < " << n;
			break;
		case CUSTOM:
			s << mapCodeName["RE2C_LESS_THAN"] << " (" << n << ")";
			break;
	}
	return s.str ();
}

} // end namespace re2c
