#include "indent.h"
#include "print.h"
#include "skeleton.h"

namespace re2c
{

const uint32_t Skeleton::MAX_PATHS = 1024 * 1024; // 1Mb

Skeleton::Skeleton (const DFA & dfa)
	: states_count (dfa.nStates + 1)
	, states (new SkeletonState [states_count])
{
	uint32_t i;

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
			uint32_t lb = 0;
			for (uint32_t j = 0; j < s->go.nSpans; ++j)
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

uint32_t Skeleton::estimate_paths_count (SkeletonState * s, uint32_t count)
{
	if (s->is_end ())
	{
		return count;
	}
	else if (s->visited < 2)
	{
		SkeletonState::visit _ (s->visited);
		uint64_t result = 0;
		for (SkeletonState::go_t::iterator i = s->go.begin (); i != s->go.end (); ++i)
		{
			const uint64_t new_count = i->second.size () * count;
			if (new_count >= MAX_PATHS)
			{
				return MAX_PATHS;
			}
			result += estimate_paths_count (i->first, new_count);
			if (result >= MAX_PATHS)
			{
				return MAX_PATHS;
			}
		}
		return result;
	}
	else
	{
		return 0;
	}
}

void generate_paths_all (SkeletonState * s, const std::vector<Path> & prefixes, std::vector<Path> & results)
{
	if (s->is_end ())
	{
		for (uint32_t i = 0; i < prefixes.size (); ++i)
		{
			results.push_back (prefixes[i]);
			results.back ().update (s->rule);
		}
	}
	else if (s->visited < 2)
	{
		SkeletonState::visit _ (s->visited);
		for (SkeletonState::go_t::iterator i = s->go.begin (); i != s->go.end (); ++i)
		{
			std::vector<Path> zs;
			for (uint32_t j = 0; j < prefixes.size (); ++j)
			{
				for (uint32_t k = 0; k < i->second.size (); ++k)
				{
					zs.push_back (prefixes[j]);
					zs.back ().extend (s->rule, i->second[k]);
				}
			}
			generate_paths_all (i->first, zs, results);
		}
	}
}

void generate_paths_cover (SkeletonState * s, const std::vector<Path> & prefixes, std::vector<Path> & results)
{
	if (s == NULL)
	{
		for (uint32_t i = 0; i < prefixes.size (); ++i)
		{
			results.push_back (prefixes[i]);
		}
	}
	else if (s->visited < 2)
	{
		SkeletonState::visit _ (s->visited);
		if (s->path != NULL)
		{
			std::vector<Path> zs (prefixes);
			for (uint32_t i = 0; i < zs.size (); ++i)
			{
				zs[i].append (s->path);
			}
			generate_paths_cover (NULL, zs, results);
		}
		else
		{
			const uint32_t in_arrows = prefixes.size ();
			const uint32_t out_states = s->go.size ();
			SkeletonState::go_t::iterator i = s->go.begin ();
			for	( uint32_t in = 0, out = 0
				; in < in_arrows || out < out_states
				; ++out, s->wrap (++i)
				)
			{
				std::vector<Path> zs;
				for (uint32_t j = 0; j < i->second.size (); ++j, ++in)
				{
					zs.push_back (prefixes[in % in_arrows]);
					zs[j].extend (s->rule, i->second[j]);
				}
				generate_paths_cover (i->first, zs, results);
				if (s->path == NULL && i->first->path != NULL)
				{
					s->path = new Path (std::vector<uint32_t> (1, i->second[0]), 0, s->rule);
					s->path->append (i->first->path);
				}
			}
		}
	}
}

void Skeleton::generate_paths (std::vector<Path> & results)
{
	std::vector<Path> prefixes;
	prefixes.push_back (Path (std::vector<uint32_t> (), 0, ~0));

	if (estimate_paths_count (states, 1) == MAX_PATHS)
	{
		// set paths for final states and default state
		// (those with zero outgoing arrows)
		for (uint32_t i = 0; i < states_count; ++i)
		{
			if (states[i].is_end ())
			{
				states[i].path = new Path (std::vector<uint32_t> (), 0, states[i].rule);
			}
		}
		generate_paths_cover (states, prefixes, results);
		// cleanup: delete all paths
		for (uint32_t i = 0; i < states_count; ++i)
		{
			delete states[i].path;
		}
	}
	else
	{
		generate_paths_all (states, prefixes, results);
	}
}

void Skeleton::emit_data (DataFile & o)
{
	uint32_t ind = 0;

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

	std::vector<Path> ys;
	generate_paths (ys);

	const uint32_t count = ys.size ();

	uint32_t max_len = 0;
	for (uint32_t i = 0; i < count; ++i)
	{
		if (max_len < ys[i].chars.size ())
		{
			max_len = ys[i].chars.size ();
		}
	}
	for (uint32_t i = 0; i < count; ++i)
	{
		o.file << indent (ind + 1);
		for (uint32_t j = 0 ; j < ys[i].chars.size (); ++j)
		{
			prtChOrHex (o.file, ys[i].chars[j]);
			o.file << ",";
		}
		o.file << "\n";
	}
	o.file << indent (ind + 1);
	for (uint32_t j = 0 ; j < max_len; ++j) // pad with YMAXFILL zeroes
	{
		o.file << "0,";
	}
	o.file << "\n";
	o.file << indent (ind) << "};\n";
	o.file << indent (ind) << "const unsigned int data_size = sizeof (data) / sizeof (YYCTYPE);\n";

	o.file << indent (ind) << "const unsigned int count = " << count << ";\n";

	uint32_t pos = 0;
	o.file << indent (ind) << "struct Result {\n";
	o.file << indent (ind + 1) << "unsigned int endpos;\n";
	o.file << indent (ind + 1) << "unsigned int startpos;\n";
	o.file << indent (ind + 1) << "unsigned int rule;\n";
	o.file << indent (ind + 1) << "Result (unsigned int e, unsigned int s, unsigned int r) : endpos (e), startpos (s), rule (r) {}\n";
	o.file << indent (ind) << "};\n";
	o.file << indent (ind) << "Result result [] =\n";
	o.file << indent (ind) << "{\n";
	for (uint32_t i = 0; i < count; ++i)
	{
		o.file << indent (ind + 1) << "Result (" << pos + ys[i].length << "," << pos + ys[i].chars.size () << "," << ys[i].rule << "),\n";
		pos += ys[i].chars.size ();
	}
	o.file << indent (ind) << "};\n";

	o.file << indent (ind) << "const YYCTYPE * cursor = data;\n";
	o.file << indent (ind) << "const YYCTYPE * marker = data;\n";
	o.file << indent (ind) << "const YYCTYPE * ctxmarker = data;\n";
	o.file << indent (ind) << "const YYCTYPE * const limit = &data[data_size - 1];\n";
}

void skeleton_emit_prolog (OutputFile & o, uint32_t ind, const char * data_name)
{
	o << indent (ind) << "#include <stdio.h>\n";
	o << indent (ind) << "#include \"" << data_name << "\"\n";
	o << indent (ind) << "int main ()\n";
	o << indent (ind) << "{\n";
	o << indent (ind + 1) << "for (unsigned int i = 0; i < count; ++i)\n";
	o << indent (ind + 1) << "{\n";
}

void skeleton_emit_epilog (OutputFile & o, uint32_t ind)
{
	o << indent (ind + 1) << "}\n";
	o << indent (ind + 1) << "return 0;\n";
	o << indent (ind) << "}\n";
}

} // namespace re2c
