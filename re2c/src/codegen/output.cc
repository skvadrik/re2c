#include <stdio.h>
#include <time.h>
#include <iomanip>

#include "src/codegen/indent.h"
#include "src/codegen/output.h"
#include "src/codegen/print.h"
#include "src/conf/msg.h"
#include "src/conf/opt.h"
#include "src/conf/warn.h"
#include "src/util/strrreplace.h"
#include "src/globals.h"

namespace re2c
{

OutputFragment::OutputFragment (type_t t, uint32_t i)
	: type (t)
	, stream ()
	, indent (i)
{}

OutputFragment::~OutputFragment()
{
	if (type == TAGS) {
		delete tags;
	}
}

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
	, types ()
	, tags ()
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

OutputFile::OutputFile()
	: blocks ()
	, label_counter ()
	, warn_condition_order (!opts->tFlag) // see note [condition order]
	, default_tags (true)
{
	new_block ();
}

OutputFile::~OutputFile ()
{
	for (unsigned int i = 0; i < blocks.size(); ++i) {
		delete blocks[i];
	}
}

OutputBlock& OutputFile::block()
{
	return *blocks.back();
}

std::ostream & OutputFile::stream ()
{
	return block().fragments.back ()->stream;
}

OutputFile &OutputFile::wraw(const char *s, const char *e)
{
	stream().write(s, static_cast<std::streamsize>(e - s));
	return *this;
}

OutputFile & OutputFile::wu32_hex (uint32_t n)
{
	prtHex (stream (), n);
	return *this;
}

OutputFile & OutputFile::wc_hex (uint32_t n)
{
	prtChOrHex (stream (), n);
	return *this;
}

OutputFile & OutputFile::wrange (uint32_t l, uint32_t u)
{
	printSpan (stream (), l, u);
	return *this;
}

OutputFile & OutputFile::wu32_width (uint32_t n, int w)
{
	stream () << std::setw (w);
	stream () << n;
	return *this;
}

OutputFile & OutputFile::wline_info (uint32_t l, const char * fn)
{
	output_line_info (stream (), l, fn);
	return *this;
}

OutputFile & OutputFile::wversion_time ()
{
	output_version_time (stream ());
	return *this;
}

OutputFile & OutputFile::wuser_start_label ()
{
	const std::string label = block().user_start_label;
	if (!label.empty ())
	{
		wstring(label).ws(":\n");
	}
	return *this;
}

OutputFile & OutputFile::wc (char c)
{
	stream () << c;
	return *this;
}

OutputFile & OutputFile::wu32 (uint32_t n)
{
	stream () << n;
	return *this;
}

OutputFile & OutputFile::wu64 (uint64_t n)
{
	stream () << n;
	return *this;
}

OutputFile & OutputFile::wstring (const std::string & s)
{
	stream () << s;
	return *this;
}

OutputFile & OutputFile::ws (const char * s)
{
	stream () << s;
	return *this;
}

OutputFile & OutputFile::wlabel (label_t l)
{
	stream () << l;
	return *this;
}

OutputFile & OutputFile::wind (uint32_t ind)
{
	stream () << indent(ind);
	return *this;
}

void OutputFile::insert_code ()
{
	block().fragments.push_back (new OutputFragment (OutputFragment::CODE, 0));
}

OutputFile &OutputFile::wdelay_tags(uint32_t ind, const ConfTags *cf)
{
	OutputFragment *frag = new OutputFragment(OutputFragment::TAGS, ind);
	frag->tags = cf;
	if (cf) {
		default_tags = false;
	}
	blocks.back()->fragments.push_back(frag);
	insert_code();
	return *this;
}

OutputFile & OutputFile::wdelay_line_info ()
{
	block().fragments.push_back (new OutputFragment (OutputFragment::LINE_INFO, 0));
	insert_code ();
	return *this;
}

OutputFile & OutputFile::wdelay_state_goto (uint32_t ind)
{
	if (opts->fFlag && !bWroteGetState)
	{
		block().fragments.push_back (new OutputFragment (OutputFragment::STATE_GOTO, ind));
		insert_code ();
		bWroteGetState = true;
	}
	return *this;
}

OutputFile & OutputFile::wdelay_types ()
{
	warn_condition_order = false; // see note [condition order]
	block().fragments.push_back (new OutputFragment (OutputFragment::TYPES, 0));
	insert_code ();
	return *this;
}

OutputFile & OutputFile::wdelay_warn_condition_order ()
{
	block().fragments.push_back (new OutputFragment (OutputFragment::WARN_CONDITION_ORDER, 0));
	insert_code ();
	return *this;
}

OutputFile & OutputFile::wdelay_yyaccept_init (uint32_t ind)
{
	block().fragments.push_back (new OutputFragment (OutputFragment::YYACCEPT_INIT, ind));
	insert_code ();
	return *this;
}

OutputFile & OutputFile::wdelay_yymaxfill ()
{
	block().fragments.push_back (new OutputFragment (OutputFragment::YYMAXFILL, 0));
	insert_code ();
	return *this;
}

void OutputFile::new_block ()
{
	blocks.push_back (new OutputBlock ());
	insert_code ();
}

void OutputFile::global_lists(
	uniq_vector_t<std::string> &types,
	std::set<std::string> &tags) const
{
	for (unsigned int i = 0; i < blocks.size(); ++i) {

		const std::vector<std::string> &ts = blocks[i]->types;
		for (size_t j = 0; j < ts.size(); ++j) {
			types.find_or_add(ts[j]);
		}

		const std::set<std::string> &cs = blocks[i]->tags;
		tags.insert(cs.begin(), cs.end());
	}
}

bool OutputFile::emit(const uniq_vector_t<std::string> &global_types,
	const std::set<std::string> &global_tags,
	size_t max_fill)
{
	FILE *file = NULL;
	std::string filename = opts->output_file;
	if (filename.empty()) {
		filename = "<stdout>";
		file = stdout;
	} else {
		file = fopen(filename.c_str(), "wb");
		if (!file) {
			error("cannot open output file: %s", filename.c_str());
			return false;
		}
	}

	unsigned int line_count = 1;
	for (unsigned int j = 0; j < blocks.size(); ++j) {
		OutputBlock & b = * blocks[j];
		for (unsigned int i = 0; i < b.fragments.size(); ++i) {
			OutputFragment & f = * b.fragments[i];
			switch (f.type) {
				case OutputFragment::CODE: break;
				case OutputFragment::LINE_INFO:
					output_line_info(f.stream, line_count + 1, filename);
					break;
				case OutputFragment::STATE_GOTO:
					output_state_goto(f.stream, f.indent, 0);
					break;
				case OutputFragment::TAGS:
					if (f.tags) {
						output_tags(f.stream, *f.tags, global_tags);
					} else if (default_tags) {
						output_tags_default(f.stream, f.indent, b.tags);
					}
					break;
				case OutputFragment::TYPES:
					output_types(f.stream, f.indent, global_types);
					break;
				case OutputFragment::WARN_CONDITION_ORDER:
					if (warn_condition_order) {// see note [condition order]
						warn.condition_order (b.line);
					}
					break;
				case OutputFragment::YYACCEPT_INIT:
					output_yyaccept_init(f.stream, f.indent, b.used_yyaccept);
					break;
				case OutputFragment::YYMAXFILL:
					output_yymaxfill(f.stream, max_fill);
					break;
			}
			std::string content = f.stream.str();
			fwrite(content.c_str(), 1, content.size(), file);
			line_count += f.count_lines();
		}
	}

	fclose(file);
	return true;
}

bool HeaderFile::emit(const uniq_vector_t<std::string> &types)
{
	if (!opts->tFlag) {
		return true;
	}

	FILE *file = NULL;
	std::string filename = opts->header_file;
	if (filename.empty()) {
		filename = "<stdout>.h";
		file = stdout;
	} else {
		file = fopen(filename.c_str(), "wb");
		if (!file) {
			error("cannot open header file: %s", filename.c_str());
			return false;
		}
	}

	output_version_time(stream);
	output_line_info(stream, 3, filename);
	stream << "\n";
	output_types(stream, 0, types);

	std::string content = stream.str();
	fwrite(content.c_str(), 1, content.size(), file);

	fclose(file);
	return true;
}

Output::Output()
	: source()
	, header()
	, skeletons()
	, max_fill(1)
{}

bool Output::emit()
{
	if (warn.error()) {
		return false;
	}

	uniq_vector_t<std::string> types;
	std::set<std::string> tags;
	source.global_lists(types, tags);

	return source.emit(types, tags, max_fill)
		&& header.emit(types);
}

void output_tags(std::ostream &o, const ConfTags &conf,
	const std::set<std::string> &tags)
{
	std::set<std::string>::const_iterator
		tag = tags.begin(),
		end = tags.end();
	for (;tag != end;) {
		std::string line = conf.line;
		strrreplace(line, "@@", *tag);
		o << line;
		if (++tag == end) {
			break;
		}
		o << conf.sep;
	}
}

void output_tags_default(std::ostream &o, uint32_t ind,
	const std::set<std::string> &tags)
{
	std::set<std::string>::const_iterator
		tag = tags.begin(),
		end = tags.end();
	for (;tag != end; ++tag) {
		o << indent(ind) << "long " << *tag << ";\n";
	}
}

void output_state_goto (std::ostream & o, uint32_t ind, uint32_t start_label)
{
	o << indent(ind) << "switch (" << output_get_state() << ") {\n";
	if (opts->bUseStateAbort)
	{
		o << indent(ind) << "default: abort();\n";
		o << indent(ind) << "case -1: goto " << opts->labelPrefix << start_label << ";\n";
	}
	else
	{
		o << indent(ind) << "default: goto " << opts->labelPrefix << start_label << ";\n";
	}
	for (uint32_t i = 0; i < last_fill_index; ++i)
	{
		o << indent(ind) << "case " << i << ": goto " << opts->yyfilllabel << i << ";\n";
	}
	o << indent(ind) << "}\n";
	if (opts->bUseStateNext)
	{
		o << opts->yynext << ":\n";
	}
}

void output_yyaccept_init (std::ostream & o, uint32_t ind, bool used_yyaccept)
{
	if (used_yyaccept)
	{
		o << indent (ind) << "unsigned int " << opts->yyaccept << " = 0;\n";
	}
}

void output_yymaxfill (std::ostream & o, size_t max_fill)
{
	o << "#define YYMAXFILL " << max_fill << "\n";
}

void output_line_info (std::ostream & o, uint32_t line_number, const std::string &file_name)
{
	if (!opts->iFlag)
	{
		o << "#line " << line_number << " \"" << file_name << "\"\n";
	}
}

void output_types(
	std::ostream &o,
	uint32_t ind,
	const uniq_vector_t<std::string> &types)
{
	o << indent(ind++) << "enum " << opts->yycondtype << " {\n";
	for (size_t i = 0; i < types.size(); ++i) {
		o << indent(ind) << opts->condEnumPrefix << types[i] << ",\n";
	}
	o << indent(--ind) << "};\n";
}

void output_version_time (std::ostream & o)
{
	o << "/* Generated by re2c";
	if (opts->version)
	{
		o << " " << PACKAGE_VERSION;
	}
	if (!opts->bNoGenerationDate)
	{
		o << " on ";
		time_t now = time (NULL);
		o.write (ctime (&now), 24);
	}
	o << " */" << "\n";
}

std::string output_get_state ()
{
	return opts->state_get_naked
		? opts->state_get
		: opts->state_get + "()";
}

} // namespace re2c
