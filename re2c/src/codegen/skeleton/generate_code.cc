#include "src/codegen/bitmap.h"
#include "src/codegen/indent.h"
#include "src/codegen/skeleton/skeleton.h"
#include "src/conf/msg.h"

namespace re2c
{

static void exact_uint (OutputFile & o, size_t width)
{
	if (width == sizeof (char))
	{
		o << "unsigned char";
	}
	else if (width == sizeof (short))
	{
		o << "unsigned short";
	}
	else if (width == sizeof (int))
	{
		o << "unsigned int";
	}
	else if (width == sizeof (long))
	{
		o << "unsigned long";
	}
	else
	{
		o << "uint" << width * 8 << "_t";
	}
}

void Skeleton::emit_prolog (OutputFile & o)
{
	o << "\n" << "#include <stdio.h>";
	o << "\n" << "#include <stdlib.h> // malloc, free";
	o << "\n" << "#include <string.h> // memset";
	o << "\n";
	o << "\n" << "static size_t filesize (FILE * f)";
	o << "\n" << "{";
	o << "\n" << indString << "const long pos = ftell (f);";
	o << "\n" << indString << "fseek (f, 0, SEEK_END);";
	o << "\n" << indString << "const long size = ftell (f);";
	o << "\n" << indString << "fseek (f, pos, SEEK_SET);";
	o << "\n" << indString << "return (size_t) size;";
	o << "\n" << "}";
	o << "\n";
}

void Skeleton::emit_start (OutputFile & o, uint32_t maxfill) const
{
	const uint32_t default_rule = maxkey ();

	o << "\n" << "#define YYCTYPE ";
	exact_uint (o, encoding.szCodeUnit ());
	o << "\n" << "#define YYKEYTYPE ";
	exact_uint (o, sizeof_key);
	o << "\n" << "#define YYPEEK() *cursor";
	o << "\n" << "#define YYSKIP() ++cursor";
	o << "\n" << "#define YYBACKUP() marker = cursor";
	o << "\n" << "#define YYBACKUPCTX() ctxmarker = cursor";
	o << "\n" << "#define YYRESTORE() cursor = marker";
	o << "\n" << "#define YYRESTORECTX() cursor = ctxmarker";
	o << "\n" << "#define YYLESSTHAN(n) (limit - cursor) < n";
	o << "\n" << "#define YYFILL(n) { break; }";
	o << "\n";
	o << "\n" << "static int action_" << name;
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
	o << "\n" << indString << "const long len_exp = (long) keys [3 * i + 1];";
	o << "\n" << indString << "const YYKEYTYPE rule_exp = keys [3 * i + 2];";
	o << "\n" << indString << "if (rule_exp == " << default_rule << ")";
	o << "\n" << indString << "{";
	o << "\n" << indString << indString << "fprintf";
	o << "\n" << indString << indString << indString << "( stderr";
	o << "\n" << indString << indString << indString << ", \"warning: " << incond (cond) << "control flow is undefined for input\"";
	o << "\n" << indString << indString << indString << indString << "\" at position %ld, rerun re2c with '-W'\\n\"";
	o << "\n" << indString << indString << indString << ", pos";
	o << "\n" << indString << indString << indString << ");";
	o << "\n" << indString << "}";
	o << "\n" << indString << "if (len_act == len_exp && rule_act == rule_exp)";
	o << "\n" << indString << "{";
	o << "\n" << indString << indString << "const YYKEYTYPE offset = keys[3 * i];";
	o << "\n" << indString << indString << "*cursor = token + offset;";
	o << "\n" << indString << indString << "return 0;";
	o << "\n" << indString << "}";
	o << "\n" << indString << "else";
	o << "\n" << indString << "{";
	o << "\n" << indString << indString << "fprintf";
	o << "\n" << indString << indString << indString << "( stderr";
	o << "\n" << indString << indString << indString << ", \"error: " << incond (cond) << "at position %ld (iteration %u):\\n\"";
	o << "\n" << indString << indString << indString << indString << "\"\\texpected: match length %ld, rule %u\\n\"";
	o << "\n" << indString << indString << indString << indString << "\"\\tactual:   match length %ld, rule %u\\n\"";
	o << "\n" << indString << indString << indString << ", pos";
	o << "\n" << indString << indString << indString << ", i";
	o << "\n" << indString << indString << indString << ", len_exp";
	o << "\n" << indString << indString << indString << ", rule_exp";
	o << "\n" << indString << indString << indString << ", len_act";
	o << "\n" << indString << indString << indString << ", rule_act";
	o << "\n" << indString << indString << indString << ");";
	o << "\n" << indString << indString << "return 1;";
	o << "\n" << indString << "}";
	o << "\n" << "}";
	o << "\n";
	o << "\n" << "int lex_" << name << " ()";
	o << "\n" << "{";
	o << "\n" << indString << "FILE * finput = fopen (\"" << o.file_name << "." << name << ".input" << "\", \"rb\");";
	o << "\n" << indString << "if (!finput)";
	o << "\n" << indString << "{";
	o << "\n" << indString << indString << "fprintf (stderr, \"cannot open file '%s'\\n\", \"" << o.file_name << "." << name << ".input\");";
	o << "\n" << indString << indString << "return 1;";
	o << "\n" << indString << "}";
	o << "\n" << indString << "FILE * fkeys = fopen (\"" << o.file_name << "." << name << ".keys" << "\", \"rb\");";
	o << "\n" << indString << "if (!fkeys)";
	o << "\n" << indString << "{";
	o << "\n" << indString << indString << "fprintf (stderr, \"cannot open file '%s'\\n\", \"" << o.file_name << "." << name << ".keys\");";
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
	o << "\n" << indString << indString << "YYCTYPE yych;";
	o.insert_yyaccept_init (2);
	o << "\n";
	if (bFlag && BitMap::first)
	{
		BitMap::gen (o, 2, 0, std::min (0xFFu, encoding.nCodeUnits ()));
	}
	o << "\n";
}

void Skeleton::emit_end (OutputFile & o) const
{
	o << "\n" << indString << "}";
	o << "\n" << indString << "if (status == 0)";
	o << "\n" << indString << "{";
	o << "\n" << indString << indString << "if (cursor != eof)";
	o << "\n" << indString << indString << "{";
	o << "\n" << indString << indString << indString << "status = 1;";
	o << "\n" << indString << indString << indString << "fprintf (stderr, \"error: " << incond (cond) << "unused input strings left\\n\");";
	o << "\n" << indString << indString << "}";
	o << "\n" << indString << indString << "if (i != keys_count)";
	o << "\n" << indString << indString << "{";
	o << "\n" << indString << indString << indString << "status = 1;";
	o << "\n" << indString << indString << indString << "fprintf (stderr, \"error: " << incond (cond) << "unused keys left\\n\");";
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
	o << "\n" << "#undef YYKEYTYPE";
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

void Skeleton::emit_epilog (OutputFile & o, const std::vector<std::string> & names)
{
	o << "\n" << "int main ()";
	o << "\n" << "{";

	const size_t names_count = names.size ();
	for (size_t i = 0; i < names_count; ++i)
	{
		o << "\n" << indString << "if (lex_" << names[i] << " () != 0) return 1;";
	}

	o << "\n" << indString << "return 0;";
	o << "\n" << "}";
	o << "\n";
}

void Skeleton::emit_action (OutputFile & o, uint32_t ind, rule_rank_t rank, const std::string & name)
{
	o << indent (ind) << "status = action_" << name << " (i, keys, input, token, &cursor, " << rank << ");\n";
	o << indent (ind) << "continue;\n";
}

} // namespace re2c
