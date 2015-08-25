#ifndef _RE2C_CODEGEN_OUTPUT_
#define _RE2C_CODEGEN_OUTPUT_

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "src/codegen/label.h"
#include "src/ir/rule_rank.h"
#include "src/util/c99_stdint.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

struct OutputFragment
{
	enum type_t
		{ CODE
//		, CONFIG
		, LINE_INFO
		, STATE_GOTO
		, TYPES
		, YYACCEPT_INIT
		, YYMAXFILL
		};

	type_t type;
	std::ostringstream stream;
	uint32_t indent;

	OutputFragment (type_t t, uint32_t i);
	uint32_t count_lines ();
};

struct OutputBlock
{
	std::vector<OutputFragment *> fragments;
	bool used_yyaccept;
	bool force_start_label;
	std::string user_start_label;
	uint32_t line;

	OutputBlock ();
	~OutputBlock ();
};

struct OutputFile
{
private:
	const char * file_name;
	FILE * file;
	std::vector<OutputBlock *> blocks;

public:
	counter_t<label_t> label_counter;

private:
	std::ostream & stream ();
	void insert_code ();

public:
	OutputFile (const char * fn);
	~OutputFile ();

	bool open ();

	void new_block ();

	void write (const char * s, size_t n);
	void write_hex (uint32_t n);
	void write_char_hex (uint32_t n);
	void write_range (uint32_t u, uint32_t l);
	void write_uint32_t_width (uint32_t n, uint32_t w);
	void write_line_info (uint32_t l, const char * fn);
	void write_version_time ();
	void write_user_start_label ();
	friend OutputFile & operator << (OutputFile & o, char c);
	friend OutputFile & operator << (OutputFile & o, uint32_t n);
	friend OutputFile & operator << (OutputFile & o, const std::string & s);
	friend OutputFile & operator << (OutputFile & o, const char * s);
	friend OutputFile & operator << (OutputFile & o, label_t l);
	friend OutputFile & operator << (OutputFile & o, rule_rank_t l);

	void insert_line_info ();
	void insert_state_goto (uint32_t ind);
	void insert_types ();
	void insert_yyaccept_init (uint32_t ind);
	void insert_yymaxfill ();

	void set_used_yyaccept ();
	bool get_used_yyaccept () const;
	void set_force_start_label (bool force);
	void set_user_start_label (const std::string & label);
	bool get_force_start_label () const;
	void set_block_line (uint32_t l);
	uint32_t get_block_line () const;

	void emit (const std::vector<std::string> & types, uint32_t max_fill);

	FORBID_COPY (OutputFile);
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

	FORBID_COPY (HeaderFile);
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

void output_line_info (std::ostream &, uint32_t, const char *);
void output_state_goto (std::ostream &, uint32_t, uint32_t);
void output_types (std::ostream &, uint32_t, const std::vector<std::string> &);
void output_version_time (std::ostream &);
void output_yyaccept_init (std::ostream &, uint32_t, bool);
void output_yymaxfill (std::ostream &, uint32_t);

// helpers
std::string output_get_state ();

} // namespace re2c

#endif // _RE2C_CODEGEN_OUTPUT_
