#ifndef _output_h
#define _output_h

#include <sstream>
#include <string>
#include <vector>

#include "basics.h"

namespace re2c
{

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

struct OutputBlock
{
	std::vector<OutputFragment *> fragments;
	bool used_yyaccept;

	OutputBlock ();
	~OutputBlock ();
};

struct OutputFile
{
	OutputFile (const char * fn);
	~OutputFile ();
	bool open ();
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
	friend OutputFile & operator << (OutputFile & o, const Str & s);
	friend OutputFile & operator << (OutputFile & o, const Setw & s);

private:
	const char * file_name;
	FILE * file;
	std::vector<OutputBlock *> blocks;
	uint prolog_label;

	void insert_code ();
};

struct HeaderFile
{
	HeaderFile (const char * fn);
	~HeaderFile ();
	bool open ();
	void emit (const std::vector<std::string> & types);

private:
	std::ostringstream stream;
	const char * file_name;
	FILE * file;
};

struct Output
{
	OutputFile source;
	HeaderFile header;
	std::vector<std::string> types;
	uint max_fill;

	Output (const char * source_name, const char * header_name);
	~Output ();
};

} // namespace re2c

#endif // _output_h
