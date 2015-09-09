#include "src/codegen/indent.h"
#include "src/codegen/skeleton/skeleton.h"

namespace re2c
{

void Skeleton::emit_prolog (OutputFile & o, uint32_t ind, uint32_t maxfill)
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
	o << indent (ind) << "#include <stdlib.h> // malloc, free\n";
	o << indent (ind) << "#include <string.h> // memset\n";
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
	o << "\n";
	o << indent (ind + 1) << "FILE * f = fopen (\"" << o.file_name << ".input" << "\", \"rb\");\n";
	o << "\n";
	o << indent (ind + 1) << "// get file size (measured in code units)\n";
	o << indent (ind + 1) << "fseek (f, 0, SEEK_END);\n";
	o << indent (ind + 1) << "const size_t size = ((size_t) ftell (f)) / sizeof (YYCTYPE);\n";
	o << indent (ind + 1) << "fseek (f, 0, SEEK_SET);\n";
	o << "\n";
	o << indent (ind + 1) << "// read file contents in buffer and pad it with YYMAXFILL zeroes\n";
	o << indent (ind + 1) << "const size_t YYMAXFILL = " << maxfill << ";\n";
	o << indent (ind + 1) << "YYCTYPE * data = (YYCTYPE *) malloc ((size + YYMAXFILL) * sizeof (YYCTYPE));\n";
	o << indent (ind + 1) << "fread (data, sizeof (YYCTYPE), size, f);\n";
	o << indent (ind + 1) << "memset (data + size, 0, YYMAXFILL * sizeof (YYCTYPE));\n";
	o << "\n";
	o << indent (ind + 1) << "const YYCTYPE * cursor = data;\n";
	o << indent (ind + 1) << "const YYCTYPE * marker = data;\n";
	o << indent (ind + 1) << "const YYCTYPE * ctxmarker = data;\n";
	o << indent (ind + 1) << "const YYCTYPE * const limit = data + size + YYMAXFILL;\n";
	o << indent (ind + 1) << "const YYCTYPE * const cursor_end = data + size;\n";
	o << "\n";
	o << indent (ind + 1) << "for (unsigned int i = 0; cursor < cursor_end; ++i)\n";
	o << indent (ind + 1) << "{\n";
	o << indent (ind + 2) << "const YYCTYPE * token = cursor;\n";
}

void Skeleton::emit_epilog (OutputFile & o, uint32_t ind)
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
	o << "\n";
	o << indent (ind + 1) << "free (data);\n";
	o << indent (ind + 1) << "fclose (f);\n";
	o << "\n";
	o << indent (ind + 1) << "return 0;\n";
	o << indent (ind) << "}\n";
}

} // namespace re2c
