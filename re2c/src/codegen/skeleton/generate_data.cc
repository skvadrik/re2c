#include <stdlib.h> // exit

#include "src/codegen/indent.h"
#include "src/codegen/print.h"
#include "src/codegen/skeleton/skeleton.h"
#include "src/conf/msg.h"

namespace re2c
{

static void write_string (FILE * f, const path_t & path);
static void write_key (std::ofstream & f, const path_t & path);

/*
 * note [estimating total size of paths in skeleton]
 *
 * With --skeleton switch we need to generate lots of data: strings that
 * correspond to various paths in DFA and match given regular expression.
 * Generation proceeds as follows:
 *
 *  1. Estimate total size of all paths in DFA (measured in skeleton arcs).
 *     Since it grows exponentially and can easily exceed 32 bits (and 64
 *     as well), estimation must stop as soon as certain limit is reached.
 *
 *  2. If the estimated size is small enough, generate all paths.
 *
 *  3. Otherwise, try to generate path cover (a set of paths that cover
 *     all DFA arcs at least once). Generation must stop as soon as the
 *     size of path cover exceeds limit (in which case we'll only get a
 *     partial path cover).
 *
 * To avoid any possible overflows all size calculations are wrapped in
 * a special truncated unsigned 32-bit integer type that checks overflow
 * on each binary operation or conversion from another type.
 *
 * Two things contribute to size calculation: path length and the number
 * of outgoing arcs in each node. Some considerations on why these values
 * will probably not overflow before they are converted to truncated type:
 *
 *   - Maximal number of outgoing arcs in each node cannot exceed 32 bits:
 *     it is bounded by the number of code units in current encoding, and
 *     re2c doesn't support any encoding with more than 2^32 code units.
 *     Conversion is safe.
 *
 *   - Path length is unlikely to exceed maximal value of 'size_t'. It is
 *     possible, but in that case re2c will crash anyway: path is stored
 *     in 'std::vector' and if path length exceeds 'size_t', STL will
 *     throw an exception.
 *
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
		const arccount_t new_len = len + arccount_t (1u);
		for (arcs_t::iterator i = arcs.begin (); i != arcs.end (); ++i)
		{
			const arccount_t new_wid = wid * arccount_t (i->second.size ());
			if (new_wid.overflow ())
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

void Node::generate_paths_all (const std::vector<path_t> & prefixes, FILE * input, std::ofstream & keys)
{
	const size_t wid = prefixes.size ();
	if (end ())
	{
		for (size_t i = 0; i < wid; ++i)
		{
			path_t p = prefixes[i];
			p.update (rule);
			write_string (input, p);
			write_key (keys, p);
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
			i->first->generate_paths_all (zs, input, keys);
		}
	}
}

/*
 * note [generating skeleton path cover]
 *
 * The algorithm tries to generate full path cover. It stops if the size
 * of the already generated partial path cover exceeds limit (see note
 * [estimating total size of paths in skeleton]).
 *
 * The algorithm walks graph nodes in deep-first order and assigns suffix
 * to each node (a path from this node to end node). Suffix for current node
 * is a concatenation of arc to child node and suffix of that child node.
 * End nodes are assigned empty suffix.
 *
 * The algorithm carries a set of prefixes leading to current node.
 * If current node has already been assigned suffix, the algorithm appends
 * suffix to each prefix and adds the newly constructed paths to path cover.
 * Otherwise it recurses to child nodes (updating prefixes on the go).
 *
 * The algorithm avoids eternal loops by maintaining loop counter for each
 * node. Loop counter is incremented on recursive enter and decremented on
 * recursive return. If loop counter is greater than 1, current branch is
 * abandoned and recursion returns immediately.
 *
 * Algorithm:
 * 1. Assign empty suffix to all end nodes.
 * 2. Start with the root node and a set of prefixes consisting of a single
 *    empty prefix:
 *     2.1. If current node's suffix is set, append it to each prefix and
 *          add the constructed paths to path cover.
 *     2.2. Else if current node's loop counter is greater than 1, return.
 *     2.3. Else assume that all prefixes and outgoing multiarcs are
 *          unmarked and repeat:
 *         2.3.1. Take the next unmarked multiarc and mark it.
 *         2.3.2. Build new prefix set: choose one prefix per each arc in
 *                multiarc (unmarked first, duplicates as needed) and
 *                extend each prefix with corresponding arc.
 *         2.3.3. Go to step 2.1. with child node (corresponding to chosen
 *                multiarc) and the new prefix set.
 *         2.3.4. If any new paths have been added to path cover:
 *             2.3.4.1. Mark the chosen prefixes in the old prefix set.
 *             2.3.4.2. If suffix is not set, let it be the concatenation
 *                      of any arc in multiarc and child node's suffix.
 *         2.3.5. Return if either:
 *             2.3.5.1. All outgoing multiarcs and all prefixes are marked.
 *             2.3.5.2. All outgoing multiarcs are marked, but none of the
 *                      prefixes is marked (it means that all possible
 *                      paths are stuck in loops and current recursion
 *                      branch must be abandoned).
 *
 */
arccount_t Node::generate_paths_cover (const std::vector<path_t> & prefixes, FILE * input, std::ofstream & keys)
{
	arccount_t size (0u);
	const size_t wid = prefixes.size ();
	if (path != NULL)
	{
		for (size_t i = 0; i < wid; ++i)
		{
			path_t p = prefixes[i];
			p.append (path);
			write_string (input, p);
			write_key (keys, p);
		}
		const arccount_t len (prefixes[0].len () + path->len ());
		size = arccount_t (wid) * len;
	}
	else if (loop < 2)
	{
		local_inc _ (loop);
		size_t w = 0;
		for (wrap_iter i (arcs); !i.end () || (w < wid && w != 0); ++i)
		{
			std::vector<path_t> zs;
			const size_t new_wid = i->second.size ();
			for (size_t j = 0; j < new_wid; ++j)
			{
				zs.push_back (prefixes[(w + j) % wid]);
				zs[j].extend (rule, i->second[j]);
			}
			size = size + i->first->generate_paths_cover (zs, input, keys);
			if (size.overflow ())
			{
				return arccount_t::limit ();
			}
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
	return size;
}

void Skeleton::generate_paths (uint32_t line, const std::string & cond, FILE * input, std::ofstream & keys)
{
	std::vector<path_t> prefixes;
	prefixes.push_back (path_t ());
	if (nodes->estimate_size_all (arccount_t (1u), arccount_t (0u)).overflow ())
	{
		if (nodes->generate_paths_cover (prefixes, input, keys).overflow ())
		{
			warning
				( NULL
				, line
				, false
				, "DFA %sis too large: can only generate partial path cover"
				, incond (cond).c_str ()
				);
		}
	}
	else
	{
		nodes->generate_paths_all (prefixes, input, keys);
	}
}

void Skeleton::emit_data (uint32_t line, const std::string & cond, const char * fname)
{
	const std::string input_name = std::string (fname) + ".input";
	FILE * input = fopen (input_name.c_str (), "wb");
	if (!input)
	{
		error ("cannot open file: %s", input_name.c_str ());
		exit (1);
	}

	const std::string keys_name = std::string (fname) + ".keys";
	std::ofstream keys;
	keys.open (keys_name.c_str (), std::ofstream::out | std::ofstream::binary);
	if (!keys.is_open ())
	{
		error ("cannot open keys file: %s", keys_name.c_str ());
		exit (1);
	}
	keys << "struct Result {\n";
	keys << indent (1) << "size_t len;\n";
	keys << indent (1) << "size_t len_matching;\n";
	keys << indent (1) << "unsigned int match;\n";
	keys << indent (1) << "Result (size_t n, size_t m, unsigned int r) : len (n), len_matching (m), match (r) {}\n";
	keys << "};\n";
	keys << "Result result [] =\n";
	keys << "{\n";

	generate_paths (line, cond, input, keys);

	fclose (input);

	keys << "};\n";
	keys.close ();
}

template <typename type_t>
static void write_cunits (FILE * f, const path_t & path)
{
	const size_t len = path.len ();
	type_t * cunits = new type_t [len];
	for (size_t i = 0 ; i < len; ++i)
	{
		cunits[i] = static_cast<type_t> (path[i]);
	}
	fwrite (cunits, sizeof (type_t), len, f);
	delete [] cunits;
}

void write_string (FILE * f, const path_t & path)
{
	switch (encoding.szCodeUnit ())
	{
		case 4: write_cunits<uint32_t> (f, path); break;
		case 2: write_cunits<uint16_t> (f, path); break;
		case 1: write_cunits<uint8_t>  (f, path); break;
	}
}

void write_key (std::ofstream & f, const path_t & path)
{
	f << indent (1) << "Result (" << path.len () << "," << path.len_matching () << "," << path.match () << "),\n";
}

} // namespace re2c
