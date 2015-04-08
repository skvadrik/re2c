#include "indent.h"
#include "print.h"
#include "skeleton.h"

namespace re2c
{

Skeleton::Skeleton (const DFA & dfa)
	: states (new SkeletonState [dfa.nStates])
{
	std::map<State *, SkeletonState *> m;
	m[NULL] = NULL;
	uint i = 0;
	for (State * s = dfa.head; s; s = s->next)
	{
		m[s] = &states[i++];
	}

	i = 0;
	for (State * s = dfa.head; s; s = s->next, ++i)
	{
		uint lb = 0;
		for (uint j = 0; j < s->go.nSpans; ++j)
		{
			states[i].go[m[s->go.span[j].to]].push_back (std::make_pair (lb, s->go.span[j].ub - 1));
			lb = s->go.span[j].ub;
		}
		states[i].rule = s->rule
			? s->rule->accept
			: ~0u;
		states[i].visited = false;
	}
}

Skeleton::~Skeleton ()
{
	delete [] states;
}

unsigned long count_data (SkeletonState * s, unsigned long count)
{
	const bool is_default = s == NULL;
	const bool is_final = !is_default && s->go.size () == 1 && s->go.begin ()->first == NULL;
	if (is_final || is_default)
	{
		return count;
	}
	else if (!s->visited)
	{
		s->visited = true;
		unsigned long result = 0;
		for (SkeletonState::go_t::iterator i = s->go.begin (); i != s->go.end (); ++i)
		{
			uint c = 0;
			for (uint j = 0; j < i->second.size (); ++j)
			{
				c += 1 + (i->second[j].first != i->second[j].second);
			}
			result += count_data (i->first, c * count);
		}
		s->visited = false;
		return result;
	}
	else
	{
		return 0;
	}
}

unsigned long Skeleton::count ()
{
	return count_data (states, 1);
}

void generate_data (DataFile & o, uint ind, SkeletonState * s, const std::vector<Prefix> & xs, std::vector<Result> & ys)
{
	const bool is_default = s == NULL;
	const bool is_final = !is_default && s->go.size () == 1 && s->go.begin ()->first == NULL;
	if (is_final || is_default)
	{
		for (uint i = 0; i < xs.size (); ++i)
		{
			o.file << indent (ind);
			for (uint j = 0 ; j < xs[i].chars.size (); ++j)
			{
				prtChOrHex (o.file, xs[i].chars[j]);
				o.file << ",";
			}
			o.file << "\n";
			const uint processed = xs[i].chars.size ();
			const uint consumed = is_final
				? xs[i].chars.size ()
				: xs[i].length;
			const uint rule = is_final
				? s->rule
				: xs[i].rule;
			ys.push_back (Result (processed, consumed, rule));
		}
	}
	else if (!s->visited)
	{
		s->visited = true;
		for (SkeletonState::go_t::iterator i = s->go.begin (); i != s->go.end (); ++i)
		{
			std::vector<Prefix> zs;
			for (uint j = 0; j < xs.size (); ++j)
			{
				const bool is_accepting = s->rule != ~0u;
				const uint l = is_accepting
					? xs[j].chars.size ()
					: xs[j].length;
				const uint r = is_accepting
					? s->rule
					: xs[j].rule;

				std::vector<uint> z (xs[j].chars);
				for (uint k = 0; k < i->second.size (); ++k)
				{
					z.push_back (i->second[k].first);
					zs.push_back (Prefix (z, l, r));
					if (i->second[k].first != i->second[k].second)
					{
						z.pop_back ();
						z.push_back (i->second[k].second);
						zs.push_back (Prefix (z, l, r));
					}
					z.pop_back ();
				}
			}
			generate_data (o, ind, i->first, zs, ys);
		}
		s->visited = false;
	}
}

void Skeleton::emit_data (DataFile & o)
{
fprintf (stderr, "%lx\n%lx\n", 0xFFFFffffFFFFffff, count ());
	uint ind = 0;

	std::string yyctype;
	switch (encoding.szCodeUnit ())
	{
		case 1:
			yyctype = " unsigned char";
			break;
		case 2:
			yyctype = " unsigned short";
			break;
		case 4:
			yyctype = " unsigned int";
			break;
	}

	o.file << "#define " << mapCodeName["YYCTYPE"] << yyctype << "\n";
	o.file << "#define " << mapCodeName["YYPEEK"] << "() *cursor\n";
	o.file << "#define " << mapCodeName["YYSKIP"] << "() ++cursor\n";
	o.file << "#define " << mapCodeName["YYBACKUP"] << "() marker = cursor\n";
	o.file << "#define " << mapCodeName["YYBACKUPCTX"] << "() ctxmarker = cursor\n";
	o.file << "#define " << mapCodeName["YYRESTORE"] << "() cursor = marker\n";
	o.file << "#define " << mapCodeName["YYRESTORECTX"] << "() cursor = ctxmarker\n";
	o.file << "#define " << mapCodeName["YYLESSTHAN"] << "(n) (limit - cursor) < n\n";
	o.file << "#define " << mapCodeName["YYFILL"] << "(n) { break; }\n";

	o.file << indent (ind) << "// These strings correspond to paths in DFA.\n";
	o.file << indent (ind) << "YYCTYPE data [] =\n";
	o.file << indent (ind) << "{\n";

	std::vector<Prefix> xs;
	std::vector<Result> ys;
	std::vector<uint> x;
	xs.push_back (Prefix (x, 0, ~0));
	generate_data (o, ind + 1, states, xs, ys);

	const uint count = ys.size ();

	uint max_len = 0;
	for (uint i = 0; i < count; ++i)
	{
		if (max_len < ys[i].consumed)
		{
			max_len = ys[i].consumed;
		}
	}
	o.file << indent (ind + 1);
	for (uint j = 0 ; j < max_len; ++j) // pad with YMAXFILL zeroes
	{
		o.file << "0,";
	}
	o.file << "\n";
	o.file << indent (ind) << "};\n";
	o.file << indent (ind) << "const unsigned int data_size = sizeof (data) / sizeof (YYCTYPE);\n";

	o.file << indent (ind) << "const unsigned int count = " << count << ";\n";

	uint pos = 0;
	o.file << indent (ind) << "struct Result {\n";
	o.file << indent (ind + 1) << "unsigned int endpos;\n";
	o.file << indent (ind + 1) << "unsigned int startpos;\n";
	o.file << indent (ind + 1) << "unsigned int rule;\n";
	o.file << indent (ind + 1) << "Result (unsigned int e, unsigned int s, unsigned int r) : endpos (e), startpos (s), rule (r) {}\n";
	o.file << indent (ind) << "};\n";
	o.file << indent (ind) << "Result result [] =\n";
	o.file << indent (ind) << "{\n";
	for (uint i = 0; i < count; ++i)
	{
		o.file << indent (ind + 1) << "Result (" << pos + ys[i].consumed << "," << pos + ys[i].processed << "," << ys[i].rule << "),\n";
		pos += ys[i].processed;
	}
	o.file << indent (ind) << "};\n";

	o.file << indent (ind) << "const YYCTYPE * cursor = data;\n";
	o.file << indent (ind) << "const YYCTYPE * marker = data;\n";
	o.file << indent (ind) << "const YYCTYPE * ctxmarker = data;\n";
	o.file << indent (ind) << "const YYCTYPE * const limit = &data[data_size - 1];\n";
}

void skeleton_emit_prolog (OutputFile & o, uint ind, const char * data_name)
{
	o << indent (ind) << "#include <stdio.h>\n";
	o << indent (ind) << "#include \"" << data_name << "\"\n";
	o << indent (ind) << "int main ()\n";
	o << indent (ind) << "{\n";
	o << indent (ind + 1) << "for (unsigned int i = 0; i < count; ++i)\n";
	o << indent (ind + 1) << "{\n";
}

void skeleton_emit_epilog (OutputFile & o, uint ind)
{
	o << indent (ind + 1) << "}\n";
	o << indent (ind + 1) << "return 0;\n";
	o << indent (ind) << "}\n";
}

} // namespace re2c
