#include "src/codegen/indent.h"
#include "src/codegen/print.h"
#include "src/codegen/skeleton/skeleton.h"
#include "src/util/allocate.h"

namespace re2c
{

namespace skeleton
{

const uint32_t Node::UNKNOWN_LEN = 0xFFFFffff;

Node::Node (const State * s, const s2n_map & s2n)
	: arcs ()
	, loop (0)
	, rule (NO_RULE)
	, path_len (UNKNOWN_LEN)
	, path (NULL)
{
	const bool is_accepting = s && s->rule;
	if (is_accepting)
	{
		rule = s->rule->accept;
	}

	const bool is_final = !s || (s->go.nSpans == 1 && !s->go.span[0].to);
	if (is_final)
	{
		path_len = 0;
		path = new Path (Path::chars_t (), 0, rule);
	}
	else
	{
		uint32_t lb = 0;
		for (uint32_t i = 0; i < s->go.nSpans; ++i)
		{
			const Span & span = s->go.span[i];
			Node * n = s2n.find (span.to)->second;
			arcs[n].push_back (lb);
			if (lb != span.ub - 1)
			{
				arcs[n].push_back (span.ub - 1);
			}
			lb = span.ub;
		}
	}
}

Node::~Node ()
{
	delete path;
}

bool Node::end () const
{
	return arcs.size () == 0;
}

uint32_t Node::estimate_size_all (uint32_t inarcs, uint32_t len)
{
	if (end ())
	{
		return inarcs * len;
	}
	else if (loop < 2)
	{
		local_inc _ (loop);
		uint64_t result = 0;
		for (arcs_t::iterator i = arcs.begin (); i != arcs.end (); ++i)
		{
			const uint64_t outarcs = i->second.size () * inarcs;
			if (outarcs >= Skeleton::DATA_LIMIT)
			{
				return Skeleton::DATA_LIMIT;
			}
			result += i->first->estimate_size_all (outarcs, len + 1);
			if (result >= Skeleton::DATA_LIMIT)
			{
				return Skeleton::DATA_LIMIT;
			}
		}
		return result;
	}
	else
	{
		return 0;
	}
}

uint32_t Node::estimate_size_cover (uint32_t inarcs, uint32_t len)
{
	if (path_len != UNKNOWN_LEN)
	{
		return inarcs * (len + path_len);
	}
	else if (loop < 2)
	{
		local_inc _ (loop);
		uint64_t result = 0;
		uint32_t in = 0;
		for (wrap_iter i (arcs); !i.end () || in < inarcs; ++i)
		{
			const uint32_t outarcs = i->second.size ();
			in += outarcs;
			const uint32_t size = i->first->estimate_size_cover (outarcs, len + 1);
			if (size != 0 && path_len == UNKNOWN_LEN)
			{
				path_len = i->first->path_len + 1;
			}
			result += size;
			if (result > Skeleton::DATA_LIMIT)
			{
				return Skeleton::DATA_LIMIT;
			}
		}
		return result;
	}
	else
	{
		return 0;
	}
}

void Node::generate_paths_all (const std::vector<Path> & prefixes, std::vector<Path> & results)
{
	if (end ())
	{
		for (uint32_t i = 0; i < prefixes.size (); ++i)
		{
			results.push_back (prefixes[i]);
			results.back ().update (rule);
		}
	}
	else if (loop < 2)
	{
		local_inc _ (loop);
		const uint32_t inarcs = prefixes.size ();
		for (arcs_t::iterator i = arcs.begin (); i != arcs.end (); ++i)
		{
			std::vector<Path> zs;
			for (uint32_t j = 0; j < inarcs; ++j)
			{
				for (uint32_t k = 0; k < i->second.size (); ++k)
				{
					zs.push_back (prefixes[j]);
					zs.back ().extend (rule, i->second[k]);
				}
			}
			i->first->generate_paths_all (zs, results);
		}
	}
}

void Node::generate_paths_cover (const std::vector<Path> & prefixes, std::vector<Path> & results)
{
	if (path != NULL)
	{
		for (uint32_t i = 0; i < prefixes.size (); ++i)
		{
			results.push_back (prefixes[i]);
			results.back ().append (path);
		}
	}
	else if (loop < 2)
	{
		local_inc _ (loop);
		const uint32_t inarcs = prefixes.size ();
		uint32_t in = 0;
		for (wrap_iter i (arcs); !i.end () || in < inarcs; ++i)
		{
			std::vector<Path> zs;
			for (uint32_t j = 0; j < i->second.size (); ++j, ++in)
			{
				zs.push_back (prefixes[in % inarcs]);
				zs[j].extend (rule, i->second[j]);
			}
			i->first->generate_paths_cover (zs, results);
			if (path == NULL && i->first->path != NULL)
			{
				path = new Path (Path::chars_t (1, i->second[0]), 0, rule);
				path->append (i->first->path);
			}
		}
	}
}

const uint32_t Skeleton::DATA_LIMIT = 1024 * 1024 * 1024; // 1Gb

Skeleton::Skeleton (const DFA & dfa)
	// +1 for default DFA state (NULL)
	: nodes (allocate<Node> (dfa.nStates + 1))
{
	Node * n;

	// map DFA states to skeleton nodes
	Node::s2n_map s2n;
	n = nodes;
	for (State * s = dfa.head; s; s = s->next, ++n)
	{
		s2n[s] = n;
	}
	s2n[NULL] = n;

	// initialize skeleton nodes
	n = nodes;
	for (State * s = dfa.head; s; s = s->next, ++n)
	{
		new (n) Node (s, s2n);
	}
	new (n) Node (NULL, s2n);
}

Skeleton::~Skeleton ()
{
	operator delete (nodes);
}

void Skeleton::generate_paths (std::vector<Path> & results)
{
	std::vector<Path> prefixes;
	prefixes.push_back (Path (Path::chars_t (), 0, NO_RULE));

	if (nodes->estimate_size_all (1, 0) == DATA_LIMIT)
	{
		if (nodes->estimate_size_cover (1, 0) == DATA_LIMIT)
		{
			fprintf (stderr, "re2c: generating too much data\n");
		}
		nodes->generate_paths_cover (prefixes, results);
	}
	else
	{
		nodes->generate_paths_all (prefixes, results);
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

void emit_prolog (OutputFile & o, uint32_t ind, const char * data_name)
{
	o << indent (ind) << "#include <stdio.h>\n";
	o << indent (ind) << "#include \"" << data_name << "\"\n";
	o << indent (ind) << "int main ()\n";
	o << indent (ind) << "{\n";
	o << indent (ind + 1) << "for (unsigned int i = 0; i < count; ++i)\n";
	o << indent (ind + 1) << "{\n";
}

void emit_epilog (OutputFile & o, uint32_t ind)
{
	o << indent (ind + 1) << "}\n";
	o << indent (ind + 1) << "return 0;\n";
	o << indent (ind) << "}\n";
}

} // namespace skeleton

} // namespace re2c
