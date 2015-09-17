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
	o << "\n" << "#include <stdlib.h> /* malloc, free */";
	o << "\n";
	o << "\n" << "static void * read_file";
	o << "\n" << indString << "( const char * fname";
	o << "\n" << indString << ", size_t unit";
	o << "\n" << indString << ", size_t padding";
	o << "\n" << indString << ", size_t * pfsize";
	o << "\n" << indString << ")";
	o << "\n" << "{";
	o << "\n" << indString << "void * buffer = NULL;";
	o << "\n" << indString << "size_t fsize = 0;";
	o << "\n";
	o << "\n" << indString << "/* open file */";
	o << "\n" << indString << "FILE * f = fopen (fname, \"rb\");";
	o << "\n" << indString << "if (f == NULL)";
	o << "\n" << indString << "{";
	o << "\n" << indString << indString << "goto error;";
	o << "\n" << indString << "}";
	o << "\n";
	o << "\n" << indString << "/* get file size */";
	o << "\n" << indString << "fseek (f, 0, SEEK_END);";
	o << "\n" << indString << "fsize = (size_t) ftell (f) / unit;";
	o << "\n" << indString << "fseek (f, 0, SEEK_SET);";
	o << "\n";
	o << "\n" << indString << "/* allocate memory for file and padding */";
	o << "\n" << indString << "buffer = malloc (unit * (fsize + padding));";
	o << "\n" << indString << "if (buffer == NULL)";
	o << "\n" << indString << "{";
	o << "\n" << indString << indString << "goto error;";
	o << "\n" << indString << "}";
	o << "\n";
	o << "\n" << indString << "/* read the whole file in memory */";
	o << "\n" << indString << "if (fread (buffer, unit, fsize, f) != fsize)";
	o << "\n" << indString << "{";
	o << "\n" << indString << indString << "goto error;";
	o << "\n" << indString << "}";
	o << "\n";
	o << "\n" << indString << "fclose (f);";
	o << "\n" << indString << "*pfsize = fsize;";
	o << "\n" << indString << "return buffer;";
	o << "\n";
	o << "\n" << "error:";
	o << "\n" << indString << "fprintf (stderr, \"error: cannot read file '%s'\\n\", fname);";
	o << "\n" << indString << "free (buffer);";
	o << "\n" << indString << "if (f != NULL)";
	o << "\n" << indString << "{";
	o << "\n" << indString << indString << "fclose (f);";
	o << "\n" << indString << "}";
	o << "\n" << indString << "return NULL;";
	o << "\n" << "}";
	o << "\n";
}

void Skeleton::emit_start (OutputFile & o, uint32_t maxfill, bool yyaccept) const
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
	o << "\n" << indString << "const size_t padding = " << maxfill << "; /* YYMAXFILL */";
	o << "\n" << indString << "int status = 0;";
	o << "\n" << indString << "size_t input_len = 0;";
	o << "\n" << indString << "size_t keys_count = 0;";
	o << "\n" << indString << "YYCTYPE * input = NULL;";
	o << "\n" << indString << "YYKEYTYPE * keys = NULL;";
	o << "\n" << indString << "const YYCTYPE * cursor = NULL;";
	o << "\n" << indString << "const YYCTYPE * marker = NULL;";
	o << "\n" << indString << "const YYCTYPE * ctxmarker = NULL;";
	o << "\n" << indString << "const YYCTYPE * limit = NULL;";
	o << "\n" << indString << "const YYCTYPE * eof = NULL;";
	o << "\n" << indString << "unsigned int i = 0;";
	o << "\n";
	o << "\n" << indString << "input = (YYCTYPE *) read_file";
	o << "\n" << indString << indString << "(\"" << o.file_name << "." << name << ".input\"";
	o << "\n" << indString << indString << ", sizeof (YYCTYPE)";
	o << "\n" << indString << indString << ", padding";
	o << "\n" << indString << indString << ", &input_len";
	o << "\n" << indString << indString << ");";
	o << "\n" << indString << "if (input == NULL)";
	o << "\n" << indString << "{";
	o << "\n" << indString << indString << "status = 1;";
	o << "\n" << indString << indString << "goto end;";
	o << "\n" << indString << "}";
	o << "\n";
	o << "\n" << indString << "keys = (YYKEYTYPE *) read_file";
	o << "\n" << indString << indString << "(\"" << o.file_name << "." << name << ".keys\"";
	o << "\n" << indString << indString << ", 3 * sizeof (YYKEYTYPE)";
	o << "\n" << indString << indString << ", 0";
	o << "\n" << indString << indString << ", &keys_count";
	o << "\n" << indString << indString << ");";
	o << "\n" << indString << "if (keys == NULL)";
	o << "\n" << indString << "{";
	o << "\n" << indString << indString << "status = 1;";
	o << "\n" << indString << indString << "goto end;";
	o << "\n" << indString << "}";
	o << "\n";
	o << "\n" << indString << "cursor = input;";
	o << "\n" << indString << "marker = input;";
	o << "\n" << indString << "ctxmarker = input;";
	o << "\n" << indString << "limit = input + input_len + padding;";
	o << "\n" << indString << "eof = input + input_len;";
	o << "\n";
	o << "\n" << indString << "for (i = 0; status == 0 && cursor < eof && i < keys_count; ++i)";
	o << "\n" << indString << "{";
	o << "\n" << indString << indString << "const YYCTYPE * token = cursor;";
	o << "\n" << indString << indString << "YYCTYPE yych;";
	if (yyaccept)
	{
		o << "\n" << indString << indString << "unsigned int yyaccept = 0;";
	}
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
	o << "\n";
	o << "\n" << "end:";
	o << "\n" << indString << "free (input);";
	o << "\n" << indString << "free (keys);";
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
