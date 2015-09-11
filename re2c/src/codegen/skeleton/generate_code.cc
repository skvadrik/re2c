#include "src/codegen/indent.h"
#include "src/codegen/skeleton/skeleton.h"

namespace re2c
{

void Skeleton::emit_prolog (OutputFile & o, uint32_t maxfill)
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

	o << "\n" << "#include <stdio.h>";
	o << "\n" << "#include <stdlib.h> // malloc, free";
	o << "\n" << "#include <string.h> // memset";
	o << "\n";
	o << "\n" << "typedef " << yyctype << " YYCTYPE;";
	o << "\n" << "typedef unsigned int YYKEYTYPE;";
	o << "\n";
	o << "\n" << "#define YYPEEK() *cursor";
	o << "\n" << "#define YYSKIP() ++cursor";
	o << "\n" << "#define YYBACKUP() marker = cursor";
	o << "\n" << "#define YYBACKUPCTX() ctxmarker = cursor";
	o << "\n" << "#define YYRESTORE() cursor = marker";
	o << "\n" << "#define YYRESTORECTX() cursor = ctxmarker";
	o << "\n" << "#define YYLESSTHAN(n) (limit - cursor) < n";
	o << "\n" << "#define YYFILL(n) { break; }";
	o << "\n";
	o << "\n" << "static inline YYKEYTYPE length       (const YYKEYTYPE * keys, unsigned int i) { return keys [3 * i]; }";
	o << "\n" << "static inline YYKEYTYPE match_length (const YYKEYTYPE * keys, unsigned int i) { return keys [3 * i + 1]; }";
	o << "\n" << "static inline YYKEYTYPE rule         (const YYKEYTYPE * keys, unsigned int i) { return keys [3 * i + 2]; }";
	o << "\n";
	o << "\n" << "static inline int action";
	o << "\n" << indString << "( unsigned int i";
	o << "\n" << indString << ", const YYKEYTYPE * keys";
	o << "\n" << indString << ", const YYCTYPE * start";
	o << "\n" << indString << ", const YYCTYPE * token";
	o << "\n" << indString << ", const YYCTYPE ** cursor";
	o << "\n" << indString << ", YYKEYTYPE rule_act";
	o << "\n" << indString << ")";
	o << "\n" << "{";
	o << "\n" << indString << "const long pos = token - start;";
	o << "\n" << indString << "const long len_act = *cursor - token;";
	o << "\n" << indString << "const long len_exp = (long) match_length (keys, i);";
	o << "\n" << indString << "const YYKEYTYPE rule_exp = rule (keys, i);";
	o << "\n" << indString << "if (len_act == len_exp && rule_act == rule_exp)";
	o << "\n" << indString << "{";
	o << "\n" << indString << indString << "*cursor = token + length (keys, i);";
	o << "\n" << indString << indString << "return 0;";
	o << "\n" << indString << "}";
	o << "\n" << indString << "else";
	o << "\n" << indString << "{";
	o << "\n" << indString << indString << "const char * fmt = \"error at position %ld (iteration %u):\\n\"";
	o << "\n" << indString << indString << indString << "\"\\texpected: match length %ld, rule %u\\n\"";
	o << "\n" << indString << indString << indString << "\"\\tactual:   match length %ld, rule %u\\n\";";
	o << "\n" << indString << indString << "fprintf (stderr, fmt, pos, i, len_exp, rule_exp, len_act, rule_act);";
	o << "\n" << indString << indString << "return 1;";
	o << "\n" << indString << "}";
	o << "\n" << "}";
	o << "\n";
	o << "\n" << "static inline size_t filesize (FILE * f)";
	o << "\n" << "{";
	o << "\n" << indString << "fseek (f, 0, SEEK_END);";
	o << "\n" << indString << "const long size = ftell (f) ;";
	o << "\n" << indString << "fseek (f, 0, SEEK_SET);";
	o << "\n" << indString << "return (size_t) size;";
	o << "\n" << "}";
	o << "\n";
	o << "\n" << "int main ()";
	o << "\n" << "{";
	o << "\n" << indString << "FILE * finput = fopen (\"" << o.file_name << ".input" << "\", \"rb\");";
	o << "\n" << indString << "if (!finput)";
	o << "\n" << indString << "{";
	o << "\n" << indString << indString << "fprintf (stderr, \"cannot open file '%s'\\n\", \"" << o.file_name << ".input\");";
	o << "\n" << indString << indString << "return 1;";
	o << "\n" << indString << "}";
	o << "\n" << indString << "FILE * fkeys = fopen (\"" << o.file_name << ".keys" << "\", \"rb\");";
	o << "\n" << indString << "if (!fkeys)";
	o << "\n" << indString << "{";
	o << "\n" << indString << indString << "fprintf (stderr, \"cannot open file '%s'\\n\", \"" << o.file_name << ".keys\");";
	o << "\n" << indString << indString << "return 1;";
	o << "\n" << indString << "}";
	o << "\n";
	o << "\n" << indString << "const size_t input_len = filesize (finput) / sizeof (YYCTYPE);";
	o << "\n" << indString << "const size_t padding = " << maxfill << "; // YYMAXFILL";
	o << "\n" << indString << "YYCTYPE * input = (YYCTYPE *) malloc ((input_len + padding) * sizeof (YYCTYPE));";
	o << "\n" << indString << "fread (input, sizeof (YYCTYPE), input_len, finput);";
	o << "\n" << indString << "memset (input + input_len, 0, padding * sizeof (YYCTYPE));";
	o << "\n";
	o << "\n" << indString << "const size_t keys_size = filesize (fkeys);";
	o << "\n" << indString << "YYKEYTYPE * keys = (YYKEYTYPE *) malloc (keys_size);";
	o << "\n" << indString << "fread (keys, 1, keys_size, fkeys);";
	o << "\n" << indString << "const size_t keys_count = keys_size / (3 * sizeof (YYKEYTYPE));";
	o << "\n";
	o << "\n" << indString << "const YYCTYPE * cursor = input;";
	o << "\n" << indString << "const YYCTYPE * marker = input;";
	o << "\n" << indString << "const YYCTYPE * ctxmarker = input;";
	o << "\n" << indString << "const YYCTYPE * const limit = input + input_len + padding;";
	o << "\n" << indString << "const YYCTYPE * const eof = input + input_len;";
	o << "\n";
	o << "\n" << indString << "int status = 0;";
	o << "\n" << indString << "unsigned int i;";
	o << "\n" << indString << "for (i = 0; status == 0 && cursor < eof && i < keys_count; ++i)";
	o << "\n" << indString << "{";
	o << "\n" << indString << indString << "const YYCTYPE * token = cursor;";
	o << "\n";
}

void Skeleton::emit_epilog (OutputFile & o)
{
	o << "\n" << indString << "}";
	o << "\n" << indString << "if (status == 0)";
	o << "\n" << indString << "{";
	o << "\n" << indString << indString << "if (cursor != eof)";
	o << "\n" << indString << indString << "{";
	o << "\n" << indString << indString << indString << "status = 1;";
	o << "\n" << indString << indString << indString << "fprintf (stderr, \"error: unused input strings left\\n\");";
	o << "\n" << indString << indString << "}";
	o << "\n" << indString << indString << "if (i != keys_count)";
	o << "\n" << indString << indString << "{";
	o << "\n" << indString << indString << indString << "status = 1;";
	o << "\n" << indString << indString << indString << "fprintf (stderr, \"error: unused keys left\\n\");";
	o << "\n" << indString << indString << "}";
	o << "\n" << indString << "}";
	o << "\n" << indString << "free (input);";
	o << "\n" << indString << "free (keys);";
	o << "\n" << indString << "fclose (finput);";
	o << "\n" << indString << "fclose (fkeys);";
	o << "\n";
	o << "\n" << indString << "return status;";
	o << "\n" << "}";
	o << "\n";
	o << "\n" << "#undef YYCTYPE";
	o << "\n" << "#undef YYPEEK";
	o << "\n" << "#undef YYSKIP";
	o << "\n" << "#undef YYBACKUP";
	o << "\n" << "#undef YYBACKUPCTX";
	o << "\n" << "#undef YYRESTORE";
	o << "\n" << "#undef YYRESTORECTX";
	o << "\n" << "#undef YYLESSTHAN";
	o << "\n" << "#undef YYFILL";
	o << "\n";
}

void Skeleton::emit_action (OutputFile & o, uint32_t ind, rule_rank_t rank)
{
	o << indent (ind) << "status = action (i, keys, input, token, &cursor, " << rank << ");\n";
	o << indent (ind) << "continue;\n";
}

} // namespace re2c
