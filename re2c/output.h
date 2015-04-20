#ifndef _output_h
#define _output_h

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "c99_stdint.h"

namespace re2c
{

struct Str;

struct OutputFragment
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
		uint32_t yyaccept_selector;
	};

	type_t type;
	std::ostringstream stream;
	info_t info;
	uint32_t indent;

	OutputFragment (type_t t, uint32_t i);
	uint32_t count_lines ();
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

	void new_block ();

	void write (const char * s, std::streamsize n);
	void write_hex (uint32_t n);
	void write_char_hex (uint32_t n);
	void write_range (uint32_t u, uint32_t l);
	void write_uint32_t_width (uint32_t n, uint32_t w);
	void write_line_info (uint32_t l, const char * fn);
	void write_version_time ();
	friend OutputFile & operator << (OutputFile & o, uint32_t n);
	friend OutputFile & operator << (OutputFile & o, const std::string & s);
	friend OutputFile & operator << (OutputFile & o, const char * s);
	friend OutputFile & operator << (OutputFile & o, const Str & s);

	void insert_line_info ();
	void insert_state_goto (uint32_t ind, uint32_t start_label);
	void insert_types ();
	void insert_yyaccept_init (uint32_t ind);
	void insert_yyaccept_selector (uint32_t ind, uint32_t selector);
	void insert_yymaxfill ();

	void set_used_yyaccept ();
	bool get_used_yyaccept () const;

	void emit (const std::vector<std::string> & types, uint32_t max_fill);

private:
	const char * file_name;
	FILE * file;
	std::vector<OutputBlock *> blocks;
	uint32_t prolog_label;

	std::ostream & stream ();
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

struct DataFile
{
	DataFile (const char * fn);
	~DataFile ();
	bool open ();

	std::string file_name;
	std::ofstream file;
};

struct Output
{
	OutputFile source;
	HeaderFile header;
	DataFile data;
	std::vector<std::string> types;
	uint32_t max_fill;

	Output (const char * source_name, const char * header_name);
	~Output ();
};

} // namespace re2c

#endif // _output_h
