#include <sstream>

#include "globals.h"
#include "indent.h"
#include "input.h"

namespace re2c
{

std::string expr_peek ()
{
	std::string s;
	switch (input)
	{
		case INPUT_DEFAULT:	s = "*" + mapCodeName["YYCURSOR"]; break;
		case INPUT_ISTREAM:	s = mapCodeName["YYCURSOR"] + ".peek ()"; break;
		case INPUT_CUSTOM:	s = mapCodeName["YYPEEK"] + " ()"; break;
	}
	return s;
}

std::string expr_peek_save ()
{
	return mapCodeName["yych"] + " = " + yychConversion + expr_peek ();
}

std::string stmt_peek (uint ind)
{
	return indent (ind) + expr_peek_save () + ";\n";
}

std::string stmt_skip (uint ind)
{
	std::string s;
	switch (input)
	{
		case INPUT_DEFAULT:	s = "++" + mapCodeName["YYCURSOR"]; break;
		case INPUT_ISTREAM:	s = mapCodeName["YYCURSOR"] + ".ignore ()"; break;
		case INPUT_CUSTOM:	s = mapCodeName["YYSKIP"] + " ()"; break;
	}
	return indent (ind) + s + ";\n";
}

std::string stmt_backup (uint ind)
{
	std::string s;
	switch (input)
	{
		case INPUT_DEFAULT:	s = mapCodeName["YYMARKER"] + " = " + mapCodeName["YYCURSOR"]; break;
		case INPUT_ISTREAM:	s = mapCodeName["YYMARKER"] + " = " + mapCodeName["YYCURSOR"] + ".tellg ()"; break;
		case INPUT_CUSTOM:	s = mapCodeName["YYBACKUP"] + " ()"; break;
	}
	return indent (ind) + s + ";\n";
}

std::string stmt_backupctx (uint ind)
{
	std::string s;
	switch (input)
	{
		case INPUT_DEFAULT:	s = mapCodeName["YYCTXMARKER"] + " = " + mapCodeName["YYCURSOR"] + " + 1"; break;
		case INPUT_ISTREAM:	s = mapCodeName["YYCTXMARKER"] + " = " + mapCodeName["YYCURSOR"] + ".tellg () + static_cast<std::streamoff> (1)"; break;
		case INPUT_CUSTOM:	s = mapCodeName["YYBACKUPCTX"] + " ()"; break; // +1 in stmt_restorectx
	}
	return indent (ind) + s + ";\n";
}

std::string stmt_restore (uint ind)
{
	std::string s;
	switch (input)
	{
		case INPUT_DEFAULT:	s = mapCodeName["YYCURSOR"] + " = " + mapCodeName["YYMARKER"]; break;
		case INPUT_ISTREAM:	s = mapCodeName["YYCURSOR"] + ".seekg (" + mapCodeName["YYMARKER"] + ")"; break;
		case INPUT_CUSTOM:	s = mapCodeName["YYRESTORE"] + " ()"; break;
	}
	return indent (ind) + s + ";\n";
}

std::string stmt_restorectx (uint ind)
{
	std::string s;
	switch (input)
	{
		case INPUT_DEFAULT:	s = mapCodeName["YYCURSOR"] + " = " + mapCodeName["YYCTXMARKER"]; break;
		case INPUT_ISTREAM:	s = mapCodeName["YYCURSOR"] + ".seekg (" + mapCodeName["YYCTXMARKER"] + ")"; break;
		case INPUT_CUSTOM:	return indent (ind) + mapCodeName["YYRESTORECTX"] + " ();\n" + stmt_skip (ind);
	}
	return indent (ind) + s + ";\n";
}

std::string stmt_skip_peek (uint ind)
{
	return input == INPUT_DEFAULT
		? indent (ind) + mapCodeName["yych"] + " = " + yychConversion + "*++" + mapCodeName["YYCURSOR"] + ";\n"
		: stmt_skip (ind) + stmt_peek (ind);
}

std::string stmt_skip_backup (uint ind)
{
	return input == INPUT_DEFAULT
		? indent (ind) + mapCodeName["YYMARKER"] + " = ++" + mapCodeName["YYCURSOR"] + ";\n"
		: stmt_skip (ind) + stmt_backup (ind);
}

std::string stmt_backup_peek (uint ind)
{
	return input == INPUT_DEFAULT
		? indent (ind) + mapCodeName["yych"] + " = " + yychConversion + "*(" + mapCodeName["YYMARKER"] + " = " + mapCodeName["YYCURSOR"] + ");\n"
		: stmt_backup (ind) + stmt_peek (ind);
}

std::string stmt_skip_backup_peek (uint ind)
{
	return input == INPUT_DEFAULT
		? indent (ind) + mapCodeName["yych"] + " = " + yychConversion + "*(" + mapCodeName["YYMARKER"] + " = ++" + mapCodeName["YYCURSOR"] + ");\n"
		: stmt_skip (ind) + stmt_backup (ind) + stmt_peek (ind);
}

std::string expr_has_one ()
{
	return input == INPUT_DEFAULT
		? mapCodeName["YYLIMIT"] + " <= " + mapCodeName["YYCURSOR"]
		: expr_has (1);
}

std::string expr_has (uint n)
{
	std::ostringstream s;
	switch (input)
	{
		case INPUT_DEFAULT:	s << "(" << mapCodeName["YYLIMIT"] << " - " << mapCodeName["YYCURSOR"] << ") < " << n; break;
		case INPUT_ISTREAM:	s << "(" << mapCodeName["YYLIMIT"] << " - " << mapCodeName["YYCURSOR"] << ".tellg ()) < " << n; break;
		case INPUT_CUSTOM:	s << mapCodeName["YYHAS"] << " (" << n << ")"; break;
	}
	return s.str ();
}

} // end namespace re2c
