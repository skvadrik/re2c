#ifndef _output_h
#define _output_h

#include <sstream>
#include <string>
#include <vector>

#include "basics.h"

namespace re2c
{

struct file_info;
struct Str;

struct Setw
{
	uint width;

	Setw (uint n)
		: width (n)
	{}
};

struct OutputFragment : public std::ostringstream
{
	enum type_t
		{ CODE
//		, CONFIG
		, LINE_INFO
		, STATE_GOTO
		, TYPES
		, YYACCEPT_INIT
		, YYACCEPT_SELECTOR
		, YYMAXFILL
		};

	union info_t
	{
		uint yyaccept_selector;
	};

	type_t type;
	info_t info;
	uint indent;

	OutputFragment (type_t t, uint i)
		: std::ostringstream ()
		, type (t)
		, info ()
		, indent (i)
	{}

	uint count_lines ();
};

OutputFragment & operator << (OutputFragment & f, const file_info & info);

struct OutputBlock
{
	std::vector<OutputFragment *> fragments;
	bool used_yyaccept;

	OutputBlock ();
	~OutputBlock ();
};

struct OutputFile
{
	enum status_t
		{ NO_FILE
		, OK
		, FAIL_OPEN
		} status;

	OutputFile (const char * filename);
	~OutputFile ();
	OutputFragment & fragment ();
	void write (const char * s, std::streamsize n);
	void insert_line_info ();
	void insert_state_goto (uint ind, uint start_label);
	void insert_types ();
	void insert_yyaccept_init (uint ind);
	void insert_yyaccept_selector (uint ind, uint selector);
	void insert_yymaxfill ();
	void new_block ();
	void set_used_yyaccept ();
	bool get_used_yyaccept () const;
	void emit (const std::vector<std::string> & types, uint max_fill);
	friend OutputFile & operator << (OutputFile & o, uint n);
	friend OutputFile & operator << (OutputFile & o, const std::string & s);
	friend OutputFile & operator << (OutputFile & o, const char * s);
	friend OutputFile & operator << (OutputFile & o, const file_info & i);
	friend OutputFile & operator << (OutputFile & o, const Str & s);
	friend OutputFile & operator << (OutputFile & o, const Setw & s);

private:
	const char * filename;
	FILE * file;
	std::vector<OutputBlock *> blocks;
	uint prolog_label;

	void insert_code ();
};

struct Output
{
	OutputFile source;
	OutputFile header;
	std::vector<std::string> types;
	uint max_fill;

	Output (const char * source_name, const char * header_name)
		: source (source_name)
		, header (header_name)
		, types ()
		, max_fill (1)
	{}

	void emit ();
};

} // namespace re2c

#endif // _output_h
