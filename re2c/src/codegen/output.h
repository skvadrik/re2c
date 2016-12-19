#ifndef _RE2C_CODEGEN_OUTPUT_
#define _RE2C_CODEGEN_OUTPUT_

#include "src/util/c99_stdint.h"
#include <stddef.h>
#include <stdio.h>
#include <fstream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "src/codegen/label.h"
#include "src/conf/opt.h"
#include "src/conf/warn.h"
#include "src/util/counter.h"
#include "src/util/forbid_copy.h"
#include "src/util/uniq_vector.h"

namespace re2c
{

struct ConfTags
{
	std::string format;
	std::string separator;

	ConfTags(const std::string &f, const std::string &s)
		: format(f), separator(s) {}
};

struct OutputFragment
{
	enum type_t
		{ CODE
//		, CONFIG
		, LINE_INFO
		, STATE_GOTO
		, TAGS
		, TYPES
		, WARN_CONDITION_ORDER
		, YYACCEPT_INIT
		, YYMAXFILL
		};

	type_t type;
	std::ostringstream stream;
	uint32_t indent;
	union
	{
		const ConfTags* tags;
	};

	OutputFragment (type_t t, uint32_t i);
	~OutputFragment ();
	uint32_t count_lines ();
};

struct OutputBlock
{
	std::vector<OutputFragment *> fragments;
	bool used_yyaccept;
	bool force_start_label;
	std::string user_start_label;
	std::string setup_rule;
	uint32_t line;
	std::vector<std::string> types;
	std::set<std::string> tags;

	OutputBlock ();
	~OutputBlock ();
};

class OutputFile
{
	std::vector<OutputBlock *> blocks;

public:
	counter_t<label_t> label_counter;
	uint32_t fill_index;
	bool state_goto;
	bool cond_goto;
	bool warn_condition_order;
	Opt &opts;
	Warn &warn;

	OutputFile(Opt &o, Warn &w);
	~OutputFile();

	std::ostream & stream ();
	OutputBlock &block();
	void insert_code ();
	bool open ();
	void new_block ();

	// immediate output
	OutputFile & wraw (const char *s, const char *e);
	OutputFile & wc (char c);
	OutputFile & wc_hex (uint32_t n);
	OutputFile & wu32 (uint32_t n);
	OutputFile & wu32_hex (uint32_t n);
	OutputFile & wu32_width (uint32_t n, int w);
	OutputFile & wu64 (uint64_t n);
	OutputFile & wstring (const std::string & s);
	OutputFile & ws (const char * s);
	OutputFile & wlabel (label_t l);
	OutputFile & wrange (uint32_t u, uint32_t l);
	OutputFile & wline_info (uint32_t l, const char * fn);
	OutputFile & wversion_time ();
	OutputFile & wuser_start_label ();
	OutputFile & wind (uint32_t ind);

	// delayed output
	OutputFile & wdelay_tags(uint32_t ind, const ConfTags *cf);
	OutputFile & wdelay_line_info ();
	OutputFile & wdelay_state_goto (uint32_t ind);
	OutputFile & wdelay_types ();
	OutputFile & wdelay_warn_condition_order ();
	OutputFile & wdelay_yyaccept_init (uint32_t ind);
	OutputFile & wdelay_yymaxfill ();

	void global_lists(uniq_vector_t<std::string> &types,
		std::set<std::string> &tags) const;

	bool emit(const uniq_vector_t<std::string> &global_types,
		const std::set<std::string> &global_tags, size_t max_fill);

	FORBID_COPY (OutputFile);
};

class HeaderFile
{
	std::ostringstream stream;

public:
	HeaderFile(): stream() {}
	bool emit(const uniq_vector_t<std::string> &types, Opt &opts);
	FORBID_COPY (HeaderFile);
};

struct Output
{
	OutputFile source;
	HeaderFile header;
	std::set<std::string> skeletons;
	size_t max_fill;

	Output(Opt &o, Warn &w);
	bool emit();
};

void output_tags          (std::ostream &o, const ConfTags &conf, const std::set<std::string> &tags);
void output_line_info     (std::ostream &o, uint32_t ind, const std::string &file_name, Opt &opts);
void output_state_goto    (std::ostream &o, uint32_t ind, uint32_t start_label, uint32_t fill_index, Opt &opts);
void output_types         (std::ostream &o, uint32_t ind, const uniq_vector_t<std::string> &types, Opt &opts);
void output_version_time  (std::ostream &o, Opt &opts);
void output_yyaccept_init (std::ostream &o, uint32_t ind, bool, Opt &opts);
void output_yymaxfill     (std::ostream &o, size_t max_fill);

// helpers
std::string output_get_state (Opt &opts);

} // namespace re2c

#endif // _RE2C_CODEGEN_OUTPUT_
