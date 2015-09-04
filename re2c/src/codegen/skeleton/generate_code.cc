#include "src/codegen/indent.h"
#include "src/codegen/skeleton/skeleton.h"

namespace re2c
{

void emit_prolog (OutputFile & o, uint32_t ind, uint32_t maxfill)
{
	std::string yyctype;
	switch (encoding.szCodeUnit ())
	{
		case 1:
			yyctype = "unsigned char";
			break;
		case 2:
			yyctype = "unsigned short";
			break;
		case 4:
			yyctype = "unsigned int";
			break;
	}

	o << indent (ind) << "#include <stdio.h>\n";
	o << indent (ind) << "#include \"" << o.file_name << ".input" << "\"\n";
	o << indent (ind) << "#include \"" << o.file_name << ".keys" << "\"\n";
	o << indent (ind) << "int main ()\n";
	o << indent (ind) << "{\n";
	o << "#define " << mapCodeName["YYCTYPE"] << " " << yyctype << "\n";
	o << "#define " << mapCodeName["YYPEEK"] << "() *cursor\n";
	o << "#define " << mapCodeName["YYSKIP"] << "() ++cursor\n";
	o << "#define " << mapCodeName["YYBACKUP"] << "() marker = cursor\n";
	o << "#define " << mapCodeName["YYBACKUPCTX"] << "() ctxmarker = cursor\n";
	o << "#define " << mapCodeName["YYRESTORE"] << "() cursor = marker\n";
	o << "#define " << mapCodeName["YYRESTORECTX"] << "() cursor = ctxmarker\n";
	o << "#define " << mapCodeName["YYLESSTHAN"] << "(n) (limit - cursor) < n\n";
	o << "#define " << mapCodeName["YYFILL"] << "(n) { break; }\n";
	o << indent (ind + 1) << "const YYCTYPE * cursor = data;\n";
	o << indent (ind + 1) << "const YYCTYPE * marker = data;\n";
	o << indent (ind + 1) << "const YYCTYPE * ctxmarker = data;\n";
	o << indent (ind + 1) << "const YYCTYPE * const limit = data + data_size + " << maxfill << ";\n";
	o << indent (ind + 1) << "for (unsigned int i = 0; cursor < data + data_size; ++i)\n";
	o << indent (ind + 1) << "{\n";
	o << indent (ind + 2) << "const YYCTYPE * token = cursor;\n";
}

void emit_epilog (OutputFile & o, uint32_t ind)
{
	o << indent (ind + 1) << "}\n";
	o << "#undef " << mapCodeName["YYCTYPE"]      << "\n";
	o << "#undef " << mapCodeName["YYPEEK"]       << "\n";
	o << "#undef " << mapCodeName["YYSKIP"]       << "\n";
	o << "#undef " << mapCodeName["YYBACKUP"]     << "\n";
	o << "#undef " << mapCodeName["YYBACKUPCTX"]  << "\n";
	o << "#undef " << mapCodeName["YYRESTORE"]    << "\n";
	o << "#undef " << mapCodeName["YYRESTORECTX"] << "\n";
	o << "#undef " << mapCodeName["YYLESSTHAN"]   << "\n";
	o << "#undef " << mapCodeName["YYFILL"]       << "\n";
	o << indent (ind + 1) << "return 0;\n";
	o << indent (ind) << "}\n";
}

} // namespace re2c
