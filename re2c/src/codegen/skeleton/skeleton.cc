#include <stdlib.h> // exit

#include "src/codegen/indent.h"
#include "src/codegen/print.h"
#include "src/codegen/skeleton/skeleton.h"
#include "src/conf/msg.h"
#include "src/ir/regexp/regexp_rule.h"
#include "src/util/allocate.h"

namespace re2c
{

Node::Node (const State * s, const s2n_map & s2n)
	: arcs ()
	, arcsets ()
	, loop (0)
	, rule (rule_rank_t::none ())
	, path_len_init (false)
	, path_len (0u)
	, path (NULL)
{
	const bool is_accepting = s && s->rule;
	if (is_accepting)
	{
		rule = s->rule->rank;
	}

	const bool is_final = !s || (s->go.nSpans == 1 && !s->go.span[0].to);
	if (is_final)
	{
		path_len_init = true;
		path = new path_t;
		path->update (rule);
	}
	else
	{
		uint32_t lb = 0;
		for (uint32_t i = 0; i < s->go.nSpans; ++i)
		{
			const Span & span = s->go.span[i];
			Node * n = s2n.find (span.to)->second;
			const uint32_t ub = span.ub - 1;
			arcs[n].push_back (lb);
			if (lb != ub)
			{
				arcs[n].push_back (ub);
			}
			arcsets[n].push_back (std::make_pair (lb, ub));
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

/*
 * note [estimating total size of paths in skeleton]
 *
 * With --skeleton switch we need to generate lots of data: strings that
 * correspond to various paths in DFA and match given regular expression.
 * For small graphs we can afford to generate all paths, for large graphs
 * we can only generate path cover. Anyway we need to be able to estimate
 * the amount of data to be generated (measured in skeleton arcs). Since
 * it can easily exceed 32 bits (and 64 as well), calculations must stop
 * as soon as certain limit is reached.
 *
 * To avoid any possible overflows all values are wrapped in a special
 * truncated unsigned 32-bit integer type that checks for overflow on
 * each binary operation or conversion from another type.
 */
arccount_t Node::estimate_size_all (arccount_t wid, arccount_t len)
{
	if (end ())
	{
		return wid * len;
	}
	else if (loop < 2)
	{
		local_inc _ (loop);
		arccount_t size (0u);
		for (arcs_t::iterator i = arcs.begin (); i != arcs.end (); ++i)
		{
			const arccount_t new_wid = wid * arccount_t (i->second.size ());
			const arccount_t new_len = len + arccount_t (1u);
			if (new_wid.overflow () || new_len.overflow ())
			{
				return arccount_t::limit ();
			}
			size = size + i->first->estimate_size_all (new_wid, new_len);
			if (size.overflow ())
			{
				return arccount_t::limit ();
			}
		}
		return size;
	}
	else
	{
		return arccount_t (0u);
	}
}

// see note [estimating total size of paths in skeleton]
arccount_t Node::estimate_size_cover (arccount_t wid, arccount_t len)
{
	if (path_len_init)
	{
		return wid * (len + path_len);
	}
	else if (loop < 2)
	{
		local_inc _ (loop);
		arccount_t size (0u);
		arccount_t w (0u);
		for (wrap_iter i (arcs); !i.end () || w < wid; ++i)
		{
			const arccount_t new_wid = arccount_t (i->second.size ());
			const arccount_t new_len = len + arccount_t (1u);
			if (new_wid.overflow () || new_len.overflow ())
			{
				return arccount_t::limit ();
			}
			size = size + i->first->estimate_size_cover (new_wid, new_len);
			if (size.overflow ())
			{
				return arccount_t::limit ();
			}
			if (i->first->path_len_init)
			{
				w = w + new_wid;
				if (!path_len_init)
				{
					path_len_init = true;
					path_len = i->first->path_len + arccount_t (1u);
				}
			}
		}
		return size;
	}
	else
	{
		return arccount_t (0u);
	}
}

void Node::generate_paths_all (const std::vector<path_t> & prefixes, std::vector<path_t> & results)
{
	const size_t wid = prefixes.size ();
	if (end ())
	{
		for (size_t i = 0; i < wid; ++i)
		{
			results.push_back (prefixes[i]);
			results.back ().update (rule);
		}
	}
	else if (loop < 2)
	{
		local_inc _ (loop);
		for (arcs_t::iterator i = arcs.begin (); i != arcs.end (); ++i)
		{
			std::vector<path_t> zs;
			for (size_t j = 0; j < wid; ++j)
			{
				const size_t new_wid = i->second.size ();
				for (size_t k = 0; k < new_wid; ++k)
				{
					zs.push_back (prefixes[j]);
					zs.back ().extend (rule, i->second[k]);
				}
			}
			i->first->generate_paths_all (zs, results);
		}
	}
}

void Node::generate_paths_cover (const std::vector<path_t> & prefixes, std::vector<path_t> & results)
{
	const size_t wid = prefixes.size ();
	if (path != NULL)
	{
		for (size_t i = 0; i < wid; ++i)
		{
			results.push_back (prefixes[i]);
			results.back ().append (path);
		}
	}
	else if (loop < 2)
	{
		local_inc _ (loop);
		size_t w = 0;
		for (wrap_iter i (arcs); !i.end () || w < wid; ++i)
		{
			std::vector<path_t> zs;
			const size_t new_wid = i->second.size ();
			for (size_t j = 0; j < new_wid; ++j)
			{
				zs.push_back (prefixes[(w + j) % wid]);
				zs[j].extend (rule, i->second[j]);
			}
			i->first->generate_paths_cover (zs, results);
			if (i->first->path != NULL)
			{
				w += new_wid;
				if (path == NULL)
				{
					path = new path_t;
					path->extend (rule, i->second[0]);
					path->append (i->first->path);
				}
			}
		}
	}
}

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

void Skeleton::generate_paths (std::vector<path_t> & results)
{
	std::vector<path_t> prefixes;
	prefixes.push_back (path_t ());

	if (nodes->estimate_size_all (arccount_t (1u), arccount_t (0u)).overflow ())
	{
		if (nodes->estimate_size_cover (arccount_t (1u), arccount_t (0u)).overflow ())
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

void Skeleton::emit_data (const char * fname)
{
	const std::string dfname = std::string (fname) + ".data";
	std::ofstream f;
	f.open (dfname.c_str (), std::ofstream::out | std::ofstream::binary);
	if (!f.is_open ())
	{
		error ("cannot open data file: %s", dfname.c_str ());
		exit (1);
	}

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

	f << "#define " << mapCodeName["YYCTYPE"] << yyctype << "\n";
	f << "#define " << mapCodeName["YYPEEK"] << "() *cursor\n";
	f << "#define " << mapCodeName["YYSKIP"] << "() ++cursor\n";
	f << "#define " << mapCodeName["YYBACKUP"] << "() marker = cursor\n";
	f << "#define " << mapCodeName["YYBACKUPCTX"] << "() ctxmarker = cursor\n";
	f << "#define " << mapCodeName["YYRESTORE"] << "() cursor = marker\n";
	f << "#define " << mapCodeName["YYRESTORECTX"] << "() cursor = ctxmarker\n";
	f << "#define " << mapCodeName["YYLESSTHAN"] << "(n) (limit - cursor) < n\n";
	f << "#define " << mapCodeName["YYFILL"] << "(n) { break; }\n";

	f << indent (ind) << "// These strings correspond to paths in DFA.\n";
	f << indent (ind) << "YYCTYPE data [] =\n";
	f << indent (ind) << "{\n";

	std::vector<path_t> ys;
	generate_paths (ys);

	const size_t count = ys.size ();

	size_t max_len = 0;
	for (size_t i = 0; i < count; ++i)
	{
		const size_t len = ys[i].len ();
		if (max_len < len)
		{
			max_len = len;
		}
	}
	for (size_t i = 0; i < count; ++i)
	{
		f << indent (ind + 1);
		const size_t len = ys[i].len ();
		for (size_t j = 0 ; j < len; ++j)
		{
			prtChOrHex (f, ys[i][j]);
			f << ",";
		}
		f << "\n";
	}
	f << indent (ind + 1);
	for (size_t j = 0 ; j < max_len; ++j) // pad with YMAXFILL zeroes
	{
		f << "0,";
	}
	f << "\n";
	f << indent (ind) << "};\n";
	f << indent (ind) << "const unsigned int data_size = sizeof (data) / sizeof (YYCTYPE);\n";

	f << indent (ind) << "const unsigned int count = " << count << ";\n";

	size_t pos = 0;
	f << indent (ind) << "struct Result {\n";
	f << indent (ind + 1) << "unsigned int endpos;\n";
	f << indent (ind + 1) << "unsigned int startpos;\n";
	f << indent (ind + 1) << "unsigned int rule;\n";
	f << indent (ind + 1) << "Result (unsigned int e, unsigned int s, unsigned int r) : endpos (e), startpos (s), rule (r) {}\n";
	f << indent (ind) << "};\n";
	f << indent (ind) << "Result result [] =\n";
	f << indent (ind) << "{\n";
	for (size_t i = 0; i < count; ++i)
	{
		const size_t new_pos = pos + ys[i].len ();
		f << indent (ind + 1) << "Result (" << pos + ys[i].len_matching () << "," << new_pos << "," << ys[i].match () << "),\n";
		pos = new_pos;
	}
	f << indent (ind) << "};\n";

	f << indent (ind) << "const YYCTYPE * cursor = data;\n";
	f << indent (ind) << "const YYCTYPE * marker = data;\n";
	f << indent (ind) << "const YYCTYPE * ctxmarker = data;\n";
	f << indent (ind) << "const YYCTYPE * const limit = &data[data_size - 1];\n";

	f.close ();
}

void emit_prolog (OutputFile & o, uint32_t ind)
{
	o << indent (ind) << "#include <stdio.h>\n";
	o << indent (ind) << "#include \"" << o.file_name << ".data" << "\"\n";
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

} // namespace re2c
