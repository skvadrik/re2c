#include "indent.h"
#include "print.h"
#include "skeleton.h"

namespace re2c
{

Skeleton::Skeleton (const DFA & dfa)
	: states_count (dfa.nStates + 1)
	, states (new SkeletonState [states_count])
{
	uint i;

	std::map<State *, SkeletonState *> m;
	m[NULL] = &states[states_count - 1]; // default state
	i = 0;
	for (State * s = dfa.head; s; s = s->next, ++i)
	{
		m[s] = &(states[i]);
	}

	i = 0;
	for (State * s = dfa.head; s; s = s->next, ++i)
	{
		const bool is_final = s->go.nSpans == 1 && s->go.span[0].to == NULL;
		if (!is_final)
		{
			uint lb = 0;
			for (uint j = 0; j < s->go.nSpans; ++j)
			{
				SkeletonState * p = m[(s->go.span[j].to)];
				states[i].go[p].push_back (lb);
				if (lb != s->go.span[j].ub - 1)
				{
					states[i].go[p].push_back (s->go.span[j].ub - 1);
				}
				lb = s->go.span[j].ub;
			}
		}
		if (s->rule != NULL)
		{
			states[i].rule = s->rule->accept;
		}
	}
}

Skeleton::~Skeleton ()
{
	delete [] states;
}

unsigned long count_data (SkeletonState * s, unsigned long count)
{
	if (s->is_end ())
	{
		return count;
	}
	else if (s->visited < 2)
	{
		s->visited++;
		unsigned long result = 0;
		for (SkeletonState::go_t::iterator i = s->go.begin (); i != s->go.end (); ++i)
		{
			result += count_data (i->first, i->second.size () * count);
		}
		s->visited--;
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

/*
void generate_data (DataFile & o, uint ind, SkeletonState * s, const std::vector<Path> & xs, std::vector<Result> & ys)
{
	if (is_final (s) || is_default (s))
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
			const uint consumed = is_final (s)
				? xs[i].chars.size ()
				: xs[i].length;
			const uint rule = is_final (s)
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
			std::vector<Path> zs;
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
					zs.push_back (Path (z, l, r));
					if (i->second[k].first != i->second[k].second)
					{
						z.pop_back ();
						z.push_back (i->second[k].second);
						zs.push_back (Path (z, l, r));
					}
					z.pop_back ();
				}
			}
			generate_data (o, ind, i->first, zs, ys);
		}
		s->visited = false;
	}
}
*/

void update (Path & p, SkeletonState * s)
{
	if (s->rule != ~0u)
	{
		p.length = p.chars.size ();
		p.rule = s->rule;
	}
}

void append (Path & p1, const Path & p2)
{
	if (p2.rule != ~0u)
	{
		p1.length = p1.chars.size () + p2.length;
		p1.rule = p2.rule;
	}
	for (uint i = 0; i < p2.chars.size (); ++i)
	{
		p1.chars.push_back (p2.chars[i]);
	}
}

void dump_paths (DataFile & o, uint ind, const std::vector<uint> & path)
{
	o.file << indent (ind);
	for (uint i = 0 ; i < path.size (); ++i)
	{
		prtChOrHex (o.file, path[i]);
		o.file << ",";
	}
	o.file << "\n";
}

void generate (DataFile & o, uint ind, SkeletonState * s, const std::vector<Path> & prefixes, std::vector<Result> & results)
{
	if (s == NULL)
	{
		for (uint i = 0; i < prefixes.size (); ++i)
		{
			results.push_back (Result (prefixes[i]));
			dump_paths (o, ind, prefixes[i].chars);
		}
	}
	else if (s->visited < 2)
	{
		s->visited++;

		if (s->path != NULL)
		{
			std::vector<Path> zs (prefixes);
			for (uint i = 0; i < zs.size (); ++i)
			{
				append (zs[i], * s->path);
			}
			generate (o, ind, NULL, zs, results);
		}
		else
		{
			const uint in_arrows = prefixes.size ();
			const uint out_states = s->go.size ();
			SkeletonState::go_t::iterator i = s->go.begin ();
			for	( uint in = 0, out = 0
				; in < in_arrows || out < out_states
				; ++out, s->wrap (++i)
				)
			{
				std::vector<Path> zs;
				for (uint j = 0; j < i->second.size (); ++j, ++in)
				{
					zs.push_back (prefixes[in % in_arrows]);
					update (zs[j], s);
					zs[j].chars.push_back (i->second[j]);
				}
				generate (o, ind, i->first, zs, results);
				if (s->path == NULL && i->first->path != NULL)
				{
					s->path = new Path (std::vector<uint> (1, i->second[0]), 0, s->rule);
					append (* s->path, * i->first->path);
				}
			}
		}

		s->visited--;
	}
}

void Skeleton::generate_data (DataFile & o, uint ind, std::vector<Result> & results)
{
	// set paths for final states and default state
	// (those with zero outgoing arrows)
	for (uint i = 0; i < states_count; ++i)
	{
		if (states[i].is_end ())
		{
			states[i].path = new Path (std::vector<uint> (), 0, states[i].rule);
		}
	}
	std::vector<Path> prefixes;
	prefixes.push_back (Path (std::vector<uint> (), 0, ~0));

	generate (o, ind, states, prefixes, results);

	// cleanup: delete all paths
	for (uint i = 0; i < states_count; ++i)
	{
		delete states[i].path;
	}
}

void Skeleton::emit_data (DataFile & o)
{
//	fprintf (stderr, "%lx\n%lx\n", 0xFFFFffffFFFFffff, count ());
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

	std::vector<Result> ys;
	generate_data (o, ind + 1, ys);

	const uint count = ys.size ();

	uint max_len = 0;
	for (uint i = 0; i < count; ++i)
	{
		if (max_len < ys[i].processed)
		{
			max_len = ys[i].processed;
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
