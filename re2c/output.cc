#include <iomanip>
#include <stdio.h>

#include "output.h"
#include "print.h"
#include "re.h"

namespace re2c
{

OutputFragment::OutputFragment (type_t t, uint i)
	: type (t)
	, stream ()
	, info ()
	, indent (i)
{}

uint OutputFragment::count_lines ()
{
	uint lines = 0;
	const std::string content = stream.str ();
	const char * p = content.c_str ();
	for (uint i = 0; i < content.size (); ++i)
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
	, prolog_label (0)
{
	new_block ();
}

bool OutputFile::open ()
{
	if (strcmp (file_name, "<stdout>") == 0)
	{
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

void OutputFile::write (const char * s, std::streamsize n)
{
	stream ().write (s, n);
}

void OutputFile::write_hex (uint n)
{
	prtHex (stream (), n);
}

void OutputFile::write_char_hex (uint n)
{
	prtChOrHex (stream (), n);
}

void OutputFile::write_range (uint l, uint u)
{
	printSpan (stream (), l, u);
}

void OutputFile::write_uint_width (uint n, uint w)
{
	stream () << std::setw (w) << n;
}

void OutputFile::write_line_info (uint l, const char * fn)
{
	output_line_info (stream (), l, fn);
}

void OutputFile::write_version_time ()
{
	output_version_time (stream ());
}

OutputFile & operator << (OutputFile & u, uint n)
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

OutputFile & operator << (OutputFile & u, const Str & s)
{
	u.stream () << s;
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

void OutputFile::insert_state_goto (uint ind, uint start_label)
{
	if (fFlag && !bWroteGetState)
	{
		prolog_label = start_label;
		vUsedLabels.insert (start_label);
		blocks.back ()->fragments.push_back (new OutputFragment (OutputFragment::STATE_GOTO, ind));
		insert_code ();
		bWroteGetState = true;
	}
}

void OutputFile::insert_types ()
{
	blocks.back ()->fragments.push_back (new OutputFragment (OutputFragment::TYPES, 0));
	insert_code ();
}

void OutputFile::insert_yyaccept_init (uint ind)
{
	blocks.back ()->fragments.push_back (new OutputFragment (OutputFragment::YYACCEPT_INIT, ind));
	insert_code ();
}

void OutputFile::insert_yyaccept_selector (uint ind, uint selector)
{
	OutputFragment * p = new OutputFragment (OutputFragment::YYACCEPT_SELECTOR, ind);
	p->info.yyaccept_selector = selector;
	blocks.back ()->fragments.push_back (p);
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

void OutputFile::new_block ()
{
	blocks.push_back (new OutputBlock ());
	insert_code ();
}

void OutputFile::emit
	( const std::vector<std::string> & types
	, uint max_fill
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
						output_state_goto (f.stream, f.indent, prolog_label);
						break;
					case OutputFragment::TYPES:
						output_types (f.stream, f.indent, types);
						break;
					case OutputFragment::YYACCEPT_INIT:
						output_yyaccept_init (f.stream, f.indent, b.used_yyaccept);
						break;
					case OutputFragment::YYACCEPT_SELECTOR:
						output_yyaccept_selector (f.stream, f.indent, b.used_yyaccept, f.info.yyaccept_selector);
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
	, types ()
	, max_fill (1)
{}

Output::~Output ()
{
	source.emit (types, max_fill);
	header.emit (types);
}

} // namespace re2c
