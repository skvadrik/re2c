#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "src/codegen/indent.h"
#include "src/codegen/output.h"
#include "src/codegen/print.h"
#include "src/globals.h"

namespace re2c
{

OutputFragment::OutputFragment (type_t t, uint32_t i)
	: type (t)
	, stream ()
	, indent (i)
{}

uint32_t OutputFragment::count_lines ()
{
	uint32_t lines = 0;
	const std::string content = stream.str ();
	const char * p = content.c_str ();
	for (uint32_t i = 0; i < content.size (); ++i)
	{
		if (p[i] == '\n')
		{
			++lines;
		}
	}
	return lines;
}

OutputBlock::OutputBlock ()
	: fragments ()
	, used_yyaccept (false)
	, force_start_label (false)
	, user_start_label ()
	, line (0)
{
	fragments.push_back (new OutputFragment (OutputFragment::CODE, 0));
}

OutputBlock::~OutputBlock ()
{
	for (unsigned int i = 0; i < fragments.size (); ++i)
	{
		delete fragments[i];
	}
}

OutputFile::OutputFile (const char * fn)
	: file_name (fn)
	, file (NULL)
	, blocks ()
	, label_counter ()
	, warn_condition_order (!opts.tFlag) // see note [condition order]
{
	new_block ();
}

bool OutputFile::open ()
{
	if (file_name == NULL)
	{
		file_name = "<stdout>";
		file = stdout;
	}
	else
	{
		file = fopen (file_name, "wb");
	}
	return file != NULL;
}

OutputFile::~OutputFile ()
{
	if (file != NULL && file != stdout)
	{
		fclose (file);
	}
	for (unsigned int i = 0; i < blocks.size (); ++i)
	{
		delete blocks[i];
	}
}

std::ostream & OutputFile::stream ()
{
	return blocks.back ()->fragments.back ()->stream;
}

void OutputFile::write (const char * s, size_t n)
{
	stream ().write (s, static_cast<std::streamsize> (n));
}

void OutputFile::write_hex (uint32_t n)
{
	prtHex (stream (), n);
}

void OutputFile::write_char_hex (uint32_t n)
{
	prtChOrHex (stream (), n);
}

void OutputFile::write_range (uint32_t l, uint32_t u)
{
	printSpan (stream (), l, u);
}

void OutputFile::write_uint32_t_width (uint32_t n, int w)
{
	stream () << std::setw (w);
	stream () << n;
}

void OutputFile::write_line_info (uint32_t l, const char * fn)
{
	output_line_info (stream (), l, fn);
}

void OutputFile::write_version_time ()
{
	output_version_time (stream ());
}

void OutputFile::write_user_start_label ()
{
	const std::string label = blocks.back ()->user_start_label;
	if (!label.empty ())
	{
		* this << label << ":\n";
	}
}

OutputFile & operator << (OutputFile & u, char c)
{
	u.stream () << c;
	return u;
}

OutputFile & operator << (OutputFile & u, uint32_t n)
{
	u.stream () << n;
	return u;
}

OutputFile & operator << (OutputFile & u, uint64_t n)
{
	u.stream () << n;
	return u;
}

OutputFile & operator << (OutputFile & u, const std::string & s)
{
	u.stream () << s;
	return u;
}

OutputFile & operator << (OutputFile & u, const char * s)
{
	u.stream () << s;
	return u;
}

OutputFile & operator << (OutputFile & u, label_t l)
{
	u.stream () << l;
	return u;
}

OutputFile & operator << (OutputFile & u, rule_rank_t r)
{
	u.stream () << r;
	return u;
}

void OutputFile::insert_code ()
{
	blocks.back ()->fragments.push_back (new OutputFragment (OutputFragment::CODE, 0));
}

void OutputFile::insert_line_info ()
{
	blocks.back ()->fragments.push_back (new OutputFragment (OutputFragment::LINE_INFO, 0));
	insert_code ();
}

void OutputFile::insert_state_goto (uint32_t ind)
{
	if (opts.fFlag && !bWroteGetState)
	{
		blocks.back ()->fragments.push_back (new OutputFragment (OutputFragment::STATE_GOTO, ind));
		insert_code ();
		bWroteGetState = true;
	}
}

void OutputFile::insert_types ()
{
	warn_condition_order = false; // see note [condition order]
	blocks.back ()->fragments.push_back (new OutputFragment (OutputFragment::TYPES, 0));
	insert_code ();
}

void OutputFile::insert_warn_condition_order ()
{
	blocks.back ()->fragments.push_back (new OutputFragment (OutputFragment::WARN_CONDITION_ORDER, 0));
	insert_code ();
}

void OutputFile::insert_yyaccept_init (uint32_t ind)
{
	blocks.back ()->fragments.push_back (new OutputFragment (OutputFragment::YYACCEPT_INIT, ind));
	insert_code ();
}

void OutputFile::insert_yymaxfill ()
{
	blocks.back ()->fragments.push_back (new OutputFragment (OutputFragment::YYMAXFILL, 0));
	insert_code ();
}

void OutputFile::set_used_yyaccept ()
{
	blocks.back ()->used_yyaccept = true;
}

bool OutputFile::get_used_yyaccept () const
{
	return blocks.back ()->used_yyaccept;
}

void OutputFile::set_force_start_label (bool force)
{
	blocks.back ()->force_start_label = force;
}

void OutputFile::set_user_start_label (const std::string & label)
{
	blocks.back ()->user_start_label = label;
}

bool OutputFile::get_force_start_label () const
{
	return blocks.back ()->force_start_label;
}

void OutputFile::set_block_line (uint32_t l)
{
	blocks.back ()->line = l;
}

uint32_t OutputFile::get_block_line () const
{
	return blocks.back ()->line;
}

void OutputFile::new_block ()
{
	blocks.push_back (new OutputBlock ());
	insert_code ();
}

void OutputFile::emit
	( const std::vector<std::string> & types
	, uint32_t max_fill
	)
{
	if (file != NULL)
	{
		unsigned int line_count = 1;
		for (unsigned int j = 0; j < blocks.size (); ++j)
		{
			OutputBlock & b = * blocks[j];
			for (unsigned int i = 0; i < b.fragments.size (); ++i)
			{
				OutputFragment & f = * b.fragments[i];
				switch (f.type)
				{
					case OutputFragment::CODE:
						break;
					case OutputFragment::LINE_INFO:
						output_line_info (f.stream, line_count + 1, file_name);
						break;
					case OutputFragment::STATE_GOTO:
						output_state_goto (f.stream, f.indent, 0);
						break;
					case OutputFragment::TYPES:
						output_types (f.stream, f.indent, types);
						break;
					case OutputFragment::WARN_CONDITION_ORDER:
						if (warn_condition_order) // see note [condition order]
						{
							warn.condition_order (b.line);
						}
						break;
					case OutputFragment::YYACCEPT_INIT:
						output_yyaccept_init (f.stream, f.indent, b.used_yyaccept);
						break;
					case OutputFragment::YYMAXFILL:
						output_yymaxfill (f.stream, max_fill);
						break;
				}
				std::string content = f.stream.str ();
				fwrite (content.c_str (), 1, content.size (), file);
				line_count += f.count_lines ();
			}
		}
	}
}

HeaderFile::HeaderFile (const char * fn)
	: stream ()
	, file_name (fn)
	, file (NULL)
{}

bool HeaderFile::open ()
{
	file = fopen (file_name, "wb");
	return file != NULL;
}

void HeaderFile::emit (const std::vector<std::string> & types)
{
	output_version_time (stream);
	output_line_info (stream, 3, file_name);
	stream << "\n";
	output_types (stream, 0, types);
}

HeaderFile::~HeaderFile ()
{
	if (file != NULL)
	{
		std::string content = stream.str ();
		fwrite (content.c_str (), 1, content.size (), file);
		fclose (file);
	}
}

Output::Output (const char * source_name, const char * header_name)
	: source (source_name)
	, header (header_name)
	, names ()
	, types ()
	, max_fill (1)
{}

Output::~Output ()
{
	if (!warn.error ())
	{
		source.emit (types, max_fill);
		header.emit (types);
	}
}

void output_state_goto (std::ostream & o, uint32_t ind, uint32_t start_label)
{
	o << indent(ind) << "switch (" << output_get_state() << ") {\n";
	if (opts.bUseStateAbort)
	{
		o << indent(ind) << "default: abort();\n";
		o << indent(ind) << "case -1: goto " << opts.labelPrefix << start_label << ";\n";
	}
	else
	{
		o << indent(ind) << "default: goto " << opts.labelPrefix << start_label << ";\n";
	}
	for (uint32_t i = 0; i < last_fill_index; ++i)
	{
		o << indent(ind) << "case " << i << ": goto " << mapCodeName["yyFillLabel"] << i << ";\n";
	}
	o << indent(ind) << "}\n";
	if (opts.bUseStateNext)
	{
		o << mapCodeName["yyNext"] << ":\n";
	}
}

void output_yyaccept_init (std::ostream & o, uint32_t ind, bool used_yyaccept)
{
	if (used_yyaccept)
	{
		o << indent (ind) << "unsigned int " << mapCodeName["yyaccept"] << " = 0;\n";
	}
}

void output_yymaxfill (std::ostream & o, uint32_t max_fill)
{
	o << "#define YYMAXFILL " << max_fill << "\n";
}

void output_line_info (std::ostream & o, uint32_t line_number, const char * file_name)
{
	if (!opts.iFlag)
	{
		o << "#line " << line_number << " \"" << file_name << "\"\n";
	}
}

void output_types (std::ostream & o, uint32_t ind, const std::vector<std::string> & types)
{
	o << indent (ind++) << "enum " << mapCodeName["YYCONDTYPE"] << " {\n";
	for (unsigned int i = 0; i < types.size (); ++i)
	{
		o << indent (ind) << opts.condEnumPrefix << types[i] << ",\n";
	}
	o << indent (--ind) << "};\n";
}

void output_version_time (std::ostream & o)
{
	o << "/* Generated by re2c " PACKAGE_VERSION;
	if (!opts.bNoGenerationDate)
	{
		o << " on ";
		time_t now = time (NULL);
		o.write (ctime (&now), 24);
	}
	o << "*/" << "\n";
}

std::string output_get_state ()
{
	if (opts.bUseYYGetStateNaked)
	{
		return mapCodeName["YYGETSTATE"];
	}
	else
	{
		return mapCodeName["YYGETSTATE"] + "()";
	}
}

} // namespace re2c
