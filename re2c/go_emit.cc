#include "dfa.h"
#include "go.h"
#include "indent.h"
#include "print.h"

namespace re2c
{

std::string space(uint this_label)
{
	int nl = next_label > 999999 ? 6 : next_label > 99999 ? 5 : next_label > 9999 ? 4 : next_label > 999 ? 3 : next_label > 99 ? 2 : next_label > 9 ? 1 : 0;
	int tl = this_label > 999999 ? 6 : this_label > 99999 ? 5 : this_label > 9999 ? 4 : this_label > 999 ? 3 : this_label > 99 ? 2 : this_label > 9 ? 1 : 0;
	return std::string(std::max(1, nl - tl + 1), ' ');
}

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

void output_if (OutputFile & o, uint ind, bool & readCh, const std::string & compare, uint value)
{
	o << indent(ind) << "if (" << output_yych (readCh) << " " << compare << " ";
	o.write_char_hex (value);
	o << ") ";
}

void output_goto (OutputFile & o, uint ind, bool & readCh, uint to)
{
	if (readCh)
	{
		o << input_api.stmt_peek (ind);
		readCh = false;
	}
	o << indent (ind) << "goto " << labelPrefix << to << ";\n";
}

std::string output_hgo (OutputFile & o, uint ind, bool & readCh, SwitchIf * hgo)
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

uint Span::show (std::ostream & o, uint lb) const
{
	if (to)
	{
		printSpan(o, lb, ub);
		o << " " << to->label << "; ";
	}
	return ub;
}

void Case::emit (OutputFile & o, uint ind)
{
	for (uint i = 0; i < ranges.size (); ++i)
	{
		for (uint b = ranges[i].first; b < ranges[i].second; ++b)
		{
			o << indent (ind) << "case ";
			o.write_char_hex (b);
			o << ":";
			if (dFlag && encoding.is (Enc::EBCDIC))
			{
				const uint c = encoding.decodeUnsafe (b);
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

void Cases::emit (OutputFile & o, uint ind, bool & readCh)
{
	o << indent(ind) << "switch (" << output_yych (readCh) << ") {\n";
	for (uint i = 0; i < cases_size; ++i)
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

void Binary::emit (OutputFile & o, uint ind, bool & readCh)
{
	output_if (o, ind, readCh, cond->compare, cond->value);
	o << "{\n";
	thn->emit (o, ind + 1, readCh);
	o << indent (ind) << "} else {\n";
	els->emit (o, ind + 1, readCh);
	o << indent (ind) << "}\n";
}

void Linear::emit (OutputFile & o, uint ind, bool & readCh)
{
	for (uint i = 0; i < branches.size (); ++i)
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

void If::emit (OutputFile & o, uint ind, bool & readCh)
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

void SwitchIf::emit (OutputFile & o, uint ind, bool & readCh)
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

void Bitmap::emit (OutputFile & o, uint ind, bool & readCh)
{
	std::string yych = output_hgo (o, ind, readCh, hgo);
	o << "if (" << mapCodeName["yybm"] << "[" << bitmap->i << "+" << yych << "] & ";
	if (yybmHexTable)
	{
		o.write_hex (bitmap->m);
	}
	else
	{
		o << (uint) bitmap->m;
	}
	o << ") {\n";
	output_goto (o, ind + 1, readCh, bitmap_state->label);
	o << indent (ind) << "}\n";
	if (lgo != NULL)
	{
		lgo->emit (o, ind, readCh);
	}
}

void CpgotoTable::emit (OutputFile & o, uint ind)
{
	o << indent (ind) << "static void *" << mapCodeName["yytarget"] << "[256] = {\n";
	o << indent (++ind);
	for (uint i = 0; i < TABLE_SIZE; ++i)
	{
		o << "&&" << labelPrefix << table[i];
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
			o << "," << space (table[i]);
		}
	}
	o << indent (--ind) << "};\n";
}

void Cpgoto::emit (OutputFile & o, uint ind, bool & readCh)
{
	std::string yych = output_hgo (o, ind, readCh, hgo);
	o << "{\n";
	table->emit (o, ++ind);
	o << indent(ind) << "goto *" << mapCodeName["yytarget"] << "[" << yych << "];\n";
	o << indent(--ind) << "}\n";
}

void Dot::emit (OutputFile & o)
{
	const uint n = cases->cases_size;
	if (n == 1)
	{
		o << from->label << " -> " << cases->cases[0].to->label << "\n";
	}
	else
	{
		for (uint i = 0; i < n; ++i)
		{
			o << from->label << " -> " << cases->cases[i].to->label << " [label=\"";
			for (uint j = 0; j < cases->cases[i].ranges.size (); ++j)
			{
				o.write_range (cases->cases[i].ranges[j].first, cases->cases[i].ranges[j].second);
			}
			o << "\"]\n";
		}
	}
}

void Go::emit (OutputFile & o, uint ind, bool & readCh)
{
	switch (type)
	{
		case NOT_INITIALIZED:
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
