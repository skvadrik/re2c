#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <string>
#include <utility>
#include <vector>

#include "src/codegen/bitmap.h"
#include "src/codegen/go.h"
#include "src/codegen/emit.h"
#include "src/codegen/input_api.h"
#include "src/codegen/label.h"
#include "src/codegen/output.h"
#include "src/codegen/print.h"
#include "src/conf/opt.h"
#include "src/globals.h"
#include "src/ir/adfa/adfa.h"
#include "src/ir/regexp/encoding/enc.h"

namespace re2c
{

static void output_if (OutputFile & o, uint32_t ind, bool & readCh, const std::string & compare, uint32_t value);
static std::string output_yych (bool & readCh);
static std::string output_hgo (OutputFile & o, uint32_t ind, const DFA &dfa, bool & readCh, SwitchIf * hgo);

std::string output_yych (bool & readCh)
{
	if (readCh)
	{
		readCh = false;
		return "(" + opts->input_api.expr_peek_save () + ")";
	}
	else
	{
		return opts->yych;
	}
}

void output_if (OutputFile & o, uint32_t ind, bool & readCh, const std::string & compare, uint32_t value)
{
	o.wind(ind).ws("if (").wstring(output_yych (readCh)).ws(" ").wstring(compare).ws(" ").wc_hex (value).ws(") ");
}

std::string output_hgo (OutputFile & o, uint32_t ind, const DFA &dfa, bool & readCh, SwitchIf * hgo)
{
	std::string yych = output_yych (readCh);
	if (hgo != NULL)
	{
		o.wind(ind).ws("if (").wstring(yych).ws(" & ~0xFF) {\n");
		hgo->emit (o, ind + 1, dfa, readCh);
		o.wind(ind).ws("} else ");
		yych = opts->yych;
	}
	else
	{
		o.wind(ind);
	}
	return yych;
}

void Case::emit (OutputFile & o, uint32_t ind) const
{
	for (uint32_t i = 0; i < ranges.size (); ++i)
	{
		for (uint32_t b = ranges[i].first; b < ranges[i].second; ++b)
		{
			o.wind(ind).ws("case ").wc_hex (b).ws(":");
			if (opts->dFlag && opts->encoding.type () == Enc::EBCDIC)
			{
				const uint32_t c = opts->encoding.decodeUnsafe (b);
				if (is_print (c))
					o.ws(" /* ").wc(static_cast<char> (c)).ws(" */");
			}
			bool last_case = i == ranges.size () - 1 && b == ranges[i].second - 1;
			if (!last_case)
			{
				o.ws("\n");
			}
		}
	}
}

void Cases::emit(OutputFile &o, uint32_t ind, const DFA &dfa, bool &readCh) const
{
	o.wind(ind).ws("switch (").wstring(output_yych(readCh)).ws(") {\n");

	for (uint32_t i = 1; i < cases_size; ++i) {
		const Case &c = cases[i];
		c.emit(o, ind);
		gen_goto_case(o, ind, readCh, c.to, dfa, c.tags);
	}

	// default case must be the last one
	const Case &c = cases[0];
	o.wind(ind).ws("default:");
	gen_goto_case(o, ind, readCh, c.to, dfa, c.tags);

	o.wind(ind).ws("}\n");
}

void Binary::emit(OutputFile &o, uint32_t ind, const DFA &dfa, bool &readCh)
{
	output_if(o, ind, readCh, cond->compare, cond->value);
	o.ws("{\n");
	thn->emit(o, ind + 1, dfa, readCh);
	o.wind(ind).ws("} else {\n");
	els->emit(o, ind + 1, dfa, readCh);
	o.wind(ind).ws("}\n");
}

void Linear::emit(OutputFile &o, uint32_t ind, const DFA &dfa, bool &readCh)
{
	for (uint32_t i = 0; i < nbranches; ++i) {
		const Branch &b = branches[i];
		const Cond *cond = b.cond;
		if (cond) {
			output_if(o, ind, readCh, cond->compare, cond->value);
			gen_goto_if(o, ind, readCh, b.to, dfa, b.tags);
		} else {
			gen_goto(o, ind, readCh, b.to, dfa, b.tags);
		}
	}
}

void If::emit(OutputFile &o, uint32_t ind, const DFA &dfa, bool &readCh)
{
	switch (type) {
		case BINARY: info.binary->emit(o, ind, dfa, readCh); break;
		case LINEAR: info.linear->emit(o, ind, dfa, readCh); break;
	}
}

void SwitchIf::emit(OutputFile &o, uint32_t ind, const DFA &dfa, bool &readCh)
{
	switch (type) {
		case SWITCH: info.cases->emit(o, ind, dfa, readCh); break;
		case IF:     info.ifs->emit(o, ind, dfa, readCh); break;
	}
}

void GoBitmap::emit (OutputFile & o, uint32_t ind, const DFA &dfa, bool & readCh)
{
	std::string yych = output_hgo (o, ind, dfa, readCh, hgo);
	o.ws("if (").wstring(opts->yybm).ws("[").wu32(bitmap->i).ws("+").wstring(yych).ws("] & ");
	if (opts->yybmHexTable)
	{
		o.wu32_hex(bitmap->m);
	}
	else
	{
		o.wu32(bitmap->m);
	}
	o.ws(") {\n");
	gen_goto(o, ind + 1, readCh, bitmap_state, dfa, 0);
	o.wind(ind).ws("}\n");
	if (lgo != NULL)
	{
		lgo->emit (o, ind, dfa, readCh);
	}
}

label_t CpgotoTable::max_label () const
{
	label_t max = label_t::first ();
	for (uint32_t i = 0; i < TABLE_SIZE; ++i)
	{
		if (max < table[i]->label)
		{
			max = table[i]->label;
		};
	}
	return max;
}

void CpgotoTable::emit (OutputFile & o, uint32_t ind)
{
	o.wind(ind).ws("static void *").wstring(opts->yytarget).ws("[256] = {\n");
	o.wind(++ind);
	const uint32_t max_digits = max_label ().width ();
	for (uint32_t i = 0; i < TABLE_SIZE; ++i)
	{
		o.ws("&&").wstring(opts->labelPrefix).wlabel(table[i]->label);
		if (i == TABLE_SIZE - 1)
		{
			o.ws("\n");
		}
		else if (i % 8 == 7)
		{
			o.ws(",\n").wind(ind);
		}
		else
		{
			const uint32_t padding = max_digits - table[i]->label.width () + 1;
			o.ws(",").wstring(std::string (padding, ' '));
		}
	}
	o.wind(--ind).ws("};\n");
}

void Cpgoto::emit (OutputFile & o, uint32_t ind, const DFA &dfa, bool & readCh)
{
	std::string yych = output_hgo (o, ind, dfa, readCh, hgo);
	o.ws("{\n");
	table->emit (o, ++ind);
	o.wind(ind).ws("goto *").wstring(opts->yytarget).ws("[").wstring(yych).ws("];\n");
	o.wind(--ind).ws("}\n");
}

void Dot::emit(OutputFile &o, const DFA &dfa)
{
	const uint32_t n = cases->cases_size;
	if (n == 1) {
		o.wlabel(from->label).ws(" -> ").wlabel(cases->cases[0].to->label).ws("\n");
	} else {
		for (uint32_t i = 0; i < n; ++i) {
			const Case &c = cases->cases[i];
			o.wlabel(from->label).ws(" -> ").wlabel(c.to->label).ws(" [label=\"");
			for (uint32_t j = 0; j < c.ranges.size(); ++j) {
				o.wrange(c.ranges[j].first, c.ranges[j].second);
			}
			const bool *tags = dfa.tagpool[c.tags];
			for (size_t j = 0; j < dfa.tagpool.ntags; ++j) {
				if (tags[j]) {
					o.ws("<").wstring(dfa.contexts[j].name()).ws(">");
				}
			}
			o.ws("\"]\n");
		}
	}
}

void Go::emit (OutputFile & o, uint32_t ind, const DFA &dfa, bool & readCh)
{
	gen_settags(o, ind, dfa, tags);
	switch (type) {
		case EMPTY:
			break;
		case SWITCH_IF:
			info.switchif->emit (o, ind, dfa, readCh);
			break;
		case BITMAP:
			info.bitmap->emit (o, ind, dfa, readCh);
			break;
		case CPGOTO:
			info.cpgoto->emit (o, ind, dfa, readCh);
			break;
		case DOT:
			info.dot->emit (o, dfa);
			break;
	}
}

} // namespace re2c
