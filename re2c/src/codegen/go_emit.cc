#include "src/codegen/bitmap.h"
#include "src/codegen/go.h"
#include "src/codegen/indent.h"
#include "src/codegen/print.h"
#include "src/ir/dfa/dfa.h"

namespace re2c
{

static void output_if (OutputFile & o, uint32_t ind, bool & readCh, const std::string & compare, uint32_t value);
static void output_goto (OutputFile & o, uint32_t ind, bool & readCh, label_t to);
static std::string output_yych (bool & readCh);
static std::string output_hgo (OutputFile & o, uint32_t ind, bool & readCh, SwitchIf * hgo);

std::string output_yych (bool & readCh)
{
	if (readCh)
	{
		readCh = false;
		return "(" + input_api.expr_peek_save () + ")";
	}
	else
	{
		return mapCodeName["yych"];
	}
}

void output_if (OutputFile & o, uint32_t ind, bool & readCh, const std::string & compare, uint32_t value)
{
	o << indent(ind) << "if (" << output_yych (readCh) << " " << compare << " ";
	o.write_char_hex (value);
	o << ") ";
}

void output_goto (OutputFile & o, uint32_t ind, bool & readCh, label_t to)
{
	if (readCh)
	{
		o << input_api.stmt_peek (ind);
		readCh = false;
	}
	o << indent (ind) << "goto " << labelPrefix << to << ";\n";
}

std::string output_hgo (OutputFile & o, uint32_t ind, bool & readCh, SwitchIf * hgo)
{
	std::string yych = output_yych (readCh);
	if (hgo != NULL)
	{
		o << indent (ind) << "if (" << yych <<" & ~0xFF) {\n";
		hgo->emit (o, ind + 1, readCh);
		o << indent (ind) << "} else ";
		yych = mapCodeName["yych"];
	}
	else
	{
		o << indent (ind);
	}
	return yych;
}

void Case::emit (OutputFile & o, uint32_t ind)
{
	for (uint32_t i = 0; i < ranges.size (); ++i)
	{
		for (uint32_t b = ranges[i].first; b < ranges[i].second; ++b)
		{
			o << indent (ind) << "case ";
			o.write_char_hex (b);
			o << ":";
			if (dFlag && encoding.is (Enc::EBCDIC))
			{
				const uint32_t c = encoding.decodeUnsafe (b);
				if (isprint (c))
					o << " /* " << std::string (1, c) << " */";
			}
			bool last_case = i == ranges.size () - 1 && b == ranges[i].second - 1;
			if (!last_case)
			{
				o << "\n";
			}
		}
	}
}

void Cases::emit (OutputFile & o, uint32_t ind, bool & readCh)
{
	o << indent(ind) << "switch (" << output_yych (readCh) << ") {\n";
	for (uint32_t i = 0; i < cases_size; ++i)
	{
		if (cases[i].to != def)
		{
			cases[i].emit (o, ind);
			output_goto (o, 1, readCh, cases[i].to->label);
		}
	}
	o << indent (ind) << "default:";
	output_goto (o, 1, readCh, def->label);
	o << indent (ind) << "}\n";
}

void Binary::emit (OutputFile & o, uint32_t ind, bool & readCh)
{
	output_if (o, ind, readCh, cond->compare, cond->value);
	o << "{\n";
	thn->emit (o, ind + 1, readCh);
	o << indent (ind) << "} else {\n";
	els->emit (o, ind + 1, readCh);
	o << indent (ind) << "}\n";
}

void Linear::emit (OutputFile & o, uint32_t ind, bool & readCh)
{
	for (uint32_t i = 0; i < branches.size (); ++i)
	{
		if (branches[i].first != NULL)
		{
			output_if (o, ind, readCh, branches[i].first->compare, branches[i].first->value);
			output_goto (o, 0, readCh, branches[i].second->label);
		}
		else
		{
			output_goto (o, ind, readCh, branches[i].second->label);
		}
	}
}

void If::emit (OutputFile & o, uint32_t ind, bool & readCh)
{
	switch (type)
	{
		case BINARY:
			info.binary->emit (o, ind, readCh);
			break;
		case LINEAR:
			info.linear->emit (o, ind, readCh);
			break;
	}
}

void SwitchIf::emit (OutputFile & o, uint32_t ind, bool & readCh)
{
	switch (type)
	{
		case SWITCH:
			info.cases->emit (o, ind, readCh);
			break;
		case IF:
			info.ifs->emit (o, ind, readCh);
			break;
	}
}

void GoBitmap::emit (OutputFile & o, uint32_t ind, bool & readCh)
{
	std::string yych = output_hgo (o, ind, readCh, hgo);
	o << "if (" << mapCodeName["yybm"] << "[" << bitmap->i << "+" << yych << "] & ";
	if (yybmHexTable)
	{
		o.write_hex (bitmap->m);
	}
	else
	{
		o << (uint32_t) bitmap->m;
	}
	o << ") {\n";
	output_goto (o, ind + 1, readCh, bitmap_state->label);
	o << indent (ind) << "}\n";
	if (lgo != NULL)
	{
		lgo->emit (o, ind, readCh);
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
	o << indent (ind) << "static void *" << mapCodeName["yytarget"] << "[256] = {\n";
	o << indent (++ind);
	const uint32_t max_digits = max_label ().width ();
	for (uint32_t i = 0; i < TABLE_SIZE; ++i)
	{
		o << "&&" << labelPrefix << table[i]->label;
		if (i == TABLE_SIZE - 1)
		{
			o << "\n";
		}
		else if (i % 8 == 7)
		{
			o << ",\n" << indent (ind);
		}
		else
		{
			const uint32_t padding = max_digits - table[i]->label.width () + 1;
			o << "," << std::string (padding, ' ');
		}
	}
	o << indent (--ind) << "};\n";
}

void Cpgoto::emit (OutputFile & o, uint32_t ind, bool & readCh)
{
	std::string yych = output_hgo (o, ind, readCh, hgo);
	o << "{\n";
	table->emit (o, ++ind);
	o << indent(ind) << "goto *" << mapCodeName["yytarget"] << "[" << yych << "];\n";
	o << indent(--ind) << "}\n";
}

void Dot::emit (OutputFile & o)
{
	const uint32_t n = cases->cases_size;
	if (n == 1)
	{
		o << from->label << " -> " << cases->cases[0].to->label << "\n";
	}
	else
	{
		for (uint32_t i = 0; i < n; ++i)
		{
			o << from->label << " -> " << cases->cases[i].to->label << " [label=\"";
			for (uint32_t j = 0; j < cases->cases[i].ranges.size (); ++j)
			{
				o.write_range (cases->cases[i].ranges[j].first, cases->cases[i].ranges[j].second);
			}
			o << "\"]\n";
		}
	}
}

void Go::emit (OutputFile & o, uint32_t ind, bool & readCh)
{
	switch (type)
	{
		case EMPTY:
			break;
		case SWITCH_IF:
			info.switchif->emit (o, ind, readCh);
			break;
		case BITMAP:
			info.bitmap->emit (o, ind, readCh);
			break;
		case CPGOTO:
			info.cpgoto->emit (o, ind, readCh);
			break;
		case DOT:
			info.dot->emit (o);
			break;
	}
}

} // namespace re2c
