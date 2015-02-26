#include <iomanip>
#include <stdio.h>

#include "output.h"
#include "re.h"

namespace re2c
{

uint OutputFragment::count_lines ()
{
	uint lines = 0;
	const std::string content = str ();
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
	: status (NO_FILE)
	, filename (fn)
	, file (NULL)
	, blocks ()
	, prolog_label (0)
{
	if (filename != NULL)
	{
		if (strcmp (filename, "<stdout>") == 0)
		{
			file = stdout;
			status = OK;
		}
		else
		{
			file = fopen (filename, "wb");
			status = file == NULL
				? FAIL_OPEN
				: OK;
		}
	}
	new_block ();
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

OutputFragment & OutputFile::fragment ()
{
	return * blocks.back ()->fragments.back ();
}

void OutputFile::write (const char * s, std::streamsize n)
{
	fragment ().write (s, n);
}

OutputFile & operator << (OutputFile & u, uint n)
{
	u.fragment () << n;
	return u;
}

OutputFile & operator << (OutputFile & u, const std::string & s)
{
	u.fragment () << s;
	return u;
}

OutputFile & operator << (OutputFile & u, const char * s)
{
	u.fragment () << s;
	return u;
}

OutputFile & operator << (OutputFile & u, const Str & s)
{
	u.fragment () << s;
	return u;
}

OutputFile & operator << (OutputFile & u, const Setw & s)
{
	u.fragment () << std::setw (s.width);
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
						output_line_info (f, line_count + 1, filename);
						break;
					case OutputFragment::STATE_GOTO:
						output_state_goto (f, prolog_label);
						break;
					case OutputFragment::TYPES:
						output_types (f, types);
						break;
					case OutputFragment::YYACCEPT_INIT:
						output_yyaccept_init (f, b.used_yyaccept);
						break;
					case OutputFragment::YYACCEPT_SELECTOR:
						output_yyaccept_selector (f, b.used_yyaccept);
						break;
					case OutputFragment::YYMAXFILL:
						output_yymaxfill (f, max_fill);
						break;
				}
				std::string content = f.str ();
				fwrite (content.c_str (), 1, content.size (), file);
				line_count += f.count_lines ();
			}
		}
	}
}

void Output::emit ()
{
	source.emit (types, max_fill);
	header.emit (types, max_fill);
}

} // namespace re2c
