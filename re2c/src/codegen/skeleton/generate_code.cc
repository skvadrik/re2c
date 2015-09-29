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
	const std::string & ind = opts->indString;

	o << "\n" << "#include <stdio.h>";
	o << "\n" << "#include <stdlib.h> /* malloc, free */";
	o << "\n";
	o << "\n" << "static void * read_file";
	o << "\n" << ind << "( const char * fname";
	o << "\n" << ind << ", size_t unit";
	o << "\n" << ind << ", size_t padding";
	o << "\n" << ind << ", size_t * pfsize";
	o << "\n" << ind << ")";
	o << "\n" << "{";
	o << "\n" << ind << "void * buffer = NULL;";
	o << "\n" << ind << "size_t fsize = 0;";
	o << "\n";
	o << "\n" << ind << "/* open file */";
	o << "\n" << ind << "FILE * f = fopen (fname, \"rb\");";
	o << "\n" << ind << "if (f == NULL)";
	o << "\n" << ind << "{";
	o << "\n" << ind << ind << "goto error;";
	o << "\n" << ind << "}";
	o << "\n";
	o << "\n" << ind << "/* get file size */";
	o << "\n" << ind << "fseek (f, 0, SEEK_END);";
	o << "\n" << ind << "fsize = (size_t) ftell (f) / unit;";
	o << "\n" << ind << "fseek (f, 0, SEEK_SET);";
	o << "\n";
	o << "\n" << ind << "/* allocate memory for file and padding */";
	o << "\n" << ind << "buffer = malloc (unit * (fsize + padding));";
	o << "\n" << ind << "if (buffer == NULL)";
	o << "\n" << ind << "{";
	o << "\n" << ind << ind << "goto error;";
	o << "\n" << ind << "}";
	o << "\n";
	o << "\n" << ind << "/* read the whole file in memory */";
	o << "\n" << ind << "if (fread (buffer, unit, fsize, f) != fsize)";
	o << "\n" << ind << "{";
	o << "\n" << ind << ind << "goto error;";
	o << "\n" << ind << "}";
	o << "\n";
	o << "\n" << ind << "fclose (f);";
	o << "\n" << ind << "*pfsize = fsize;";
	o << "\n" << ind << "return buffer;";
	o << "\n";
	o << "\n" << "error:";
	o << "\n" << ind << "fprintf (stderr, \"error: cannot read file '%s'\\n\", fname);";
	o << "\n" << ind << "free (buffer);";
	o << "\n" << ind << "if (f != NULL)";
	o << "\n" << ind << "{";
	o << "\n" << ind << ind << "fclose (f);";
	o << "\n" << ind << "}";
	o << "\n" << ind << "return NULL;";
	o << "\n" << "}";
	o << "\n";
}

void Skeleton::emit_start
	( OutputFile & o
	, uint32_t maxfill
	, bool backup
	, bool backupctx
	, bool accept
	) const
{
	const std::string & ind = opts->indString;
	const uint32_t default_rule = maxkey ();

	o << "\n" << "#define YYCTYPE ";
	exact_uint (o, opts->encoding.szCodeUnit ());
	o << "\n" << "#define YYKEYTYPE ";
	exact_uint (o, sizeof_key);
	o << "\n" << "#define YYPEEK() *cursor";
	o << "\n" << "#define YYSKIP() ++cursor";
	if (backup)
	{
		o << "\n" << "#define YYBACKUP() marker = cursor";
		o << "\n" << "#define YYRESTORE() cursor = marker";
	}
	if (backupctx)
	{
		o << "\n" << "#define YYBACKUPCTX() ctxmarker = cursor";
		o << "\n" << "#define YYRESTORECTX() cursor = ctxmarker";
	}
	o << "\n" << "#define YYLESSTHAN(n) (limit - cursor) < n";
	o << "\n" << "#define YYFILL(n) { break; }";
	o << "\n";
	o << "\n" << "static int action_" << name;
	o << "\n" << ind << "( unsigned int i";
	o << "\n" << ind << ", const YYKEYTYPE * keys";
	o << "\n" << ind << ", const YYCTYPE * start";
	o << "\n" << ind << ", const YYCTYPE * token";
	o << "\n" << ind << ", const YYCTYPE ** cursor";
	o << "\n" << ind << ", YYKEYTYPE rule_act";
	o << "\n" << ind << ")";
	o << "\n" << "{";
	o << "\n" << ind << "const long pos = token - start;";
	o << "\n" << ind << "const long len_act = *cursor - token;";
	o << "\n" << ind << "const long len_exp = (long) keys [3 * i + 1];";
	o << "\n" << ind << "const YYKEYTYPE rule_exp = keys [3 * i + 2];";
	o << "\n" << ind << "if (rule_exp == " << default_rule << ")";
	o << "\n" << ind << "{";
	o << "\n" << ind << ind << "fprintf";
	o << "\n" << ind << ind << ind << "( stderr";
	o << "\n" << ind << ind << ind << ", \"warning: " << incond (cond) << "control flow is undefined for input\"";
	o << "\n" << ind << ind << ind << ind << "\" at position %ld, rerun re2c with '-W'\\n\"";
	o << "\n" << ind << ind << ind << ", pos";
	o << "\n" << ind << ind << ind << ");";
	o << "\n" << ind << "}";
	o << "\n" << ind << "if (len_act == len_exp && rule_act == rule_exp)";
	o << "\n" << ind << "{";
	o << "\n" << ind << ind << "const YYKEYTYPE offset = keys[3 * i];";
	o << "\n" << ind << ind << "*cursor = token + offset;";
	o << "\n" << ind << ind << "return 0;";
	o << "\n" << ind << "}";
	o << "\n" << ind << "else";
	o << "\n" << ind << "{";
	o << "\n" << ind << ind << "fprintf";
	o << "\n" << ind << ind << ind << "( stderr";
	o << "\n" << ind << ind << ind << ", \"error: " << incond (cond) << "at position %ld (iteration %u):\\n\"";
	o << "\n" << ind << ind << ind << ind << "\"\\texpected: match length %ld, rule %u\\n\"";
	o << "\n" << ind << ind << ind << ind << "\"\\tactual:   match length %ld, rule %u\\n\"";
	o << "\n" << ind << ind << ind << ", pos";
	o << "\n" << ind << ind << ind << ", i";
	o << "\n" << ind << ind << ind << ", len_exp";
	o << "\n" << ind << ind << ind << ", rule_exp";
	o << "\n" << ind << ind << ind << ", len_act";
	o << "\n" << ind << ind << ind << ", rule_act";
	o << "\n" << ind << ind << ind << ");";
	o << "\n" << ind << ind << "return 1;";
	o << "\n" << ind << "}";
	o << "\n" << "}";
	o << "\n";
	o << "\n" << "int lex_" << name << " ()";
	o << "\n" << "{";
	o << "\n" << ind << "const size_t padding = " << maxfill << "; /* YYMAXFILL */";
	o << "\n" << ind << "int status = 0;";
	o << "\n" << ind << "size_t input_len = 0;";
	o << "\n" << ind << "size_t keys_count = 0;";
	o << "\n" << ind << "YYCTYPE * input = NULL;";
	o << "\n" << ind << "YYKEYTYPE * keys = NULL;";
	o << "\n" << ind << "const YYCTYPE * cursor = NULL;";
	o << "\n" << ind << "const YYCTYPE * limit = NULL;";
	o << "\n" << ind << "const YYCTYPE * eof = NULL;";
	o << "\n" << ind << "unsigned int i = 0;";
	o << "\n";
	o << "\n" << ind << "input = (YYCTYPE *) read_file";
	o << "\n" << ind << ind << "(\"" << o.file_name << "." << name << ".input\"";
	o << "\n" << ind << ind << ", sizeof (YYCTYPE)";
	o << "\n" << ind << ind << ", padding";
	o << "\n" << ind << ind << ", &input_len";
	o << "\n" << ind << ind << ");";
	o << "\n" << ind << "if (input == NULL)";
	o << "\n" << ind << "{";
	o << "\n" << ind << ind << "status = 1;";
	o << "\n" << ind << ind << "goto end;";
	o << "\n" << ind << "}";
	o << "\n";
	o << "\n" << ind << "keys = (YYKEYTYPE *) read_file";
	o << "\n" << ind << ind << "(\"" << o.file_name << "." << name << ".keys\"";
	o << "\n" << ind << ind << ", 3 * sizeof (YYKEYTYPE)";
	o << "\n" << ind << ind << ", 0";
	o << "\n" << ind << ind << ", &keys_count";
	o << "\n" << ind << ind << ");";
	o << "\n" << ind << "if (keys == NULL)";
	o << "\n" << ind << "{";
	o << "\n" << ind << ind << "status = 1;";
	o << "\n" << ind << ind << "goto end;";
	o << "\n" << ind << "}";
	o << "\n";
	o << "\n" << ind << "cursor = input;";
	o << "\n" << ind << "limit = input + input_len + padding;";
	o << "\n" << ind << "eof = input + input_len;";
	o << "\n";
	o << "\n" << ind << "for (i = 0; status == 0 && i < keys_count; ++i)";
	o << "\n" << ind << "{";
	if (backup)
	{
		o << "\n" << ind << ind << "const YYCTYPE * marker = NULL;";
	}
	if (backupctx)
	{
		o << "\n" << ind << ind << "const YYCTYPE * ctxmarker = NULL;";
	}
	o << "\n" << ind << ind << "const YYCTYPE * token = cursor;";
	o << "\n" << ind << ind << "YYCTYPE yych;";
	if (accept)
	{
		o << "\n" << ind << ind << "unsigned int yyaccept = 0;";
	}
	if (opts->bFlag && BitMap::first)
	{
		BitMap::gen (o, 2, 0, std::min (0xFFu, opts->encoding.nCodeUnits ()));
	}
	o << "\n";
}

void Skeleton::emit_end
	( OutputFile & o
	, bool backup
	, bool backupctx
	) const
{
	const std::string & ind = opts->indString;

	o << "\n" << ind << "}";
	o << "\n" << ind << "if (status == 0)";
	o << "\n" << ind << "{";
	o << "\n" << ind << ind << "if (cursor != eof)";
	o << "\n" << ind << ind << "{";
	o << "\n" << ind << ind << ind << "status = 1;";
	o << "\n" << ind << ind << ind << "fprintf (stderr, \"error: " << incond (cond) << "unused input strings left\\n\");";
	o << "\n" << ind << ind << "}";
	o << "\n" << ind << ind << "if (i != keys_count)";
	o << "\n" << ind << ind << "{";
	o << "\n" << ind << ind << ind << "status = 1;";
	o << "\n" << ind << ind << ind << "fprintf (stderr, \"error: " << incond (cond) << "unused keys left\\n\");";
	o << "\n" << ind << ind << "}";
	o << "\n" << ind << "}";
	o << "\n";
	o << "\n" << "end:";
	o << "\n" << ind << "free (input);";
	o << "\n" << ind << "free (keys);";
	o << "\n";
	o << "\n" << ind << "return status;";
	o << "\n" << "}";
	o << "\n";
	o << "\n" << "#undef YYCTYPE";
	o << "\n" << "#undef YYKEYTYPE";
	o << "\n" << "#undef YYPEEK";
	o << "\n" << "#undef YYSKIP";
	if (backup)
	{
		o << "\n" << "#undef YYBACKUP";
		o << "\n" << "#undef YYRESTORE";
	}
	if (backupctx)
	{
		o << "\n" << "#undef YYBACKUPCTX";
		o << "\n" << "#undef YYRESTORECTX";
	}
	o << "\n" << "#undef YYLESSTHAN";
	o << "\n" << "#undef YYFILL";
	o << "\n";
}

void Skeleton::emit_epilog (OutputFile & o, const std::set<std::string> & names)
{
	o << "\n" << "int main ()";
	o << "\n" << "{";

	for (std::set<std::string>::const_iterator i = names.begin (); i != names.end (); ++i)
	{
		o << "\n" << opts->indString << "if (lex_" << *i << " () != 0) return 1;";
	}

	o << "\n" << opts->indString << "return 0;";
	o << "\n" << "}";
	o << "\n";
}

void Skeleton::emit_action (OutputFile & o, uint32_t ind, rule_rank_t rank, const std::string & name)
{
	o << indent (ind) << "status = action_" << name << " (i, keys, input, token, &cursor, " << rank << ");\n";
	o << indent (ind) << "continue;\n";
}

} // namespace re2c
