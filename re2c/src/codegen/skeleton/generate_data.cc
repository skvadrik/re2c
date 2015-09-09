#include <stdlib.h> // exit

#include "src/codegen/indent.h"
#include "src/codegen/print.h"
#include "src/codegen/skeleton/skeleton.h"
#include "src/conf/msg.h"

namespace re2c
{

static void permutate_one (FILE * input, std::ofstream & keys, const multipath_t & path);
static arccount_t cover_one (FILE * input, std::ofstream & keys, const multipath_t & prefix, const path_t & suffix);

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
 * will not overflow before they are converted to truncated type:
 *
 *   - Maximal number of outgoing arcs in each node cannot exceed 32 bits:
 *     it is bounded by the number of code units in current encoding, and
 *     re2c doesn't support any encoding with more than 2^32 code units.
 *     Conversion is safe.
 *
 *   - Maximal path length cannot exceed 32 bits: we estimate it right
 *     after skeleton construction and check for overflow. If path length
 *     does overflow, an error is reported and re2c aborts.
 *
 */
arccount_t Node::sizeof_permutate (arccount_t wid, arccount_t len)
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
			size = size + i->first->sizeof_permutate (new_wid, new_len);
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

/*
 * note [generating skeleton path permutations]
 *
 * The algorithm generates all path permutations. It relies on the fact
 * that the size of permutations has been estimated earlier and overflow
 * is impossible (see note [estimating total size of paths in skeleton]).
 *
 * The algorithm walks graph nodes in deep-first order and calculates
 * prefix (multipath to current node). When the algorithm reaches end node
 * it generates all permutations for the constructed prefix.
 *
 * The algorithm avoids eternal loops by maintaining loop counter for each
 * node. Loop counter is incremented on recursive enter and decremented on
 * recursive return. If loop counter is greater than 1, current branch is
 * abandoned and recursion returns immediately.
 *
 */
void Node::permutate (const multipath_t & prefix, FILE * input, std::ofstream & keys)
{
	if (end ())
	{
		permutate_one (input, keys, prefix);
	}
	else if (loop < 2)
	{
		local_inc _ (loop);
		for (arcs_t::iterator i = arcs.begin (); i != arcs.end (); ++i)
		{
			multipath_t new_prefix = prefix;
			new_prefix.extend (i->first->rule, &i->second);
			i->first->permutate (new_prefix, input, keys);
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
 * to each node (a path from this node to end node). In order to calculate
 * suffix for a given node the algorithm must know suffix for any child
 * node (end nodes are assigned empty suffix at start). Suffix is only
 * calculated once for each node and then reused as much times as the node
 * is visited. This is what reduces search space.
 *
 * The algorithm calculates prefix (multipath to current node). If current
 * node has already been assigned suffix, the algorithm immediately
 * calculates path cover from prefix and suffix. Otherwise it recurses to
 * child nodes (updating prefix on the go).
 *
 * The algorithm avoids eternal loops by maintaining loop counter for each
 * node. Loop counter is incremented on recursive enter and decremented on
 * recursive return. If loop counter is greater than 1, current branch is
 * abandoned and recursion returns immediately.
 *
 */
arccount_t Node::cover (const multipath_t & prefix, FILE * input, std::ofstream & keys)
{
	arccount_t size (0u);
	if (suffix != NULL)
	{
		size = cover_one (input, keys, prefix, *suffix);
	}
	else if (end ())
	{
		suffix = new path_t (rule);
	}
	else if (loop < 2)
	{
		local_inc _ (loop);
		for (arcs_t::iterator i = arcs.begin (); i != arcs.end (); ++i)
		{
			multipath_t new_prefix = prefix;
			new_prefix.extend (i->first->rule, &i->second);
			size = size + i->first->cover (new_prefix, input, keys);
			if (size.overflow ())
			{
				return arccount_t::limit ();
			}
			if (i->first->suffix != NULL && suffix == NULL)
			{
				suffix = new path_t (rule);
				suffix->append (i->second[0], i->first->suffix);
			}
		}
	}
	return size;
}

void Skeleton::generate_paths (FILE * input, std::ofstream & keys)
{
	multipath_t prefix (nodes->rule);
	if (nodes->sizeof_permutate (arccount_t (1u), arccount_t (0u)).overflow ())
	{
		if (nodes->cover (prefix, input, keys).overflow ())
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
		nodes->permutate (prefix, input, keys);
	}
}

void Skeleton::emit_data (const char * fname)
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

	generate_paths (input, keys);

	fclose (input);

	keys << "};\n";
	keys.close ();
}

static void keygen (std::ofstream & f, size_t count, size_t len, size_t len_match, rule_rank_t match)
{
	for (size_t i = 0; i < count; ++i)
	{
		f << indent (1) << "Result (" << len << "," << len_match << "," << match << "),\n";
	}
}

template <typename type_t>
static void generic_permutate_one (FILE * input, std::ofstream & keys, const multipath_t & path)
{
	const size_t len = path.len ();

	size_t count = 1;
	for (size_t i = 0; i < len; ++i)
	{
		count *= path[i]->size ();
	}

	// input
	const size_t buffer_size = len * count;
	type_t * buffer = new type_t [buffer_size];
	for (size_t i = 0, period = count; i < len; ++i)
	{
		const multiarc_t & arc = *path[i];
		const size_t width = arc.size ();
		period /= width;
		for (size_t j = 0; j < count; ++j)
		{
			const size_t k = (j / period) % width;
			buffer[j * len + i] = static_cast<type_t> (arc[k]);
		}
	}
	fwrite (buffer, sizeof (type_t), buffer_size, input);
	delete [] buffer;

	// keys
	keygen (keys, count, len, path.len_matching (), path.match ());
}

static void permutate_one (FILE * input, std::ofstream & keys, const multipath_t & path)
{
	switch (encoding.szCodeUnit ())
	{
		case 4: generic_permutate_one<uint32_t> (input, keys, path); break;
		case 2: generic_permutate_one<uint16_t> (input, keys, path); break;
		case 1: generic_permutate_one<uint8_t>  (input, keys, path); break;
	}
}

template <typename type_t>
static arccount_t generic_cover_one (FILE * input, std::ofstream & keys, const multipath_t & prefix, const path_t & suffix)
{
	const size_t prefix_len = prefix.len ();
	const size_t suffix_len = suffix.len ();
	const size_t len = prefix_len + suffix_len;

	size_t count = 1; // width of suffix is one arc
	for (size_t i = 0; i < prefix_len; ++i)
	{
		count = std::max (count, prefix[i]->size ());
	}

	const arccount_t size = arccount_t (len) * arccount_t (count);
	if (!size.overflow ())
	{
		// input
		const size_t buffer_size = size.uint32 ();
		type_t * buffer = new type_t [buffer_size];
		for (size_t i = 0; i < prefix_len; ++i)
		{
			const std::vector<uint32_t> & arc = *prefix[i];
			const size_t width = arc.size ();
			for (size_t j = 0; j < count; ++j)
			{
				const size_t k = j % width;
				buffer[j * len + i] = static_cast<type_t> (arc[k]);
			}
		}
		for (size_t i = 0; i < suffix_len; ++i)
		{
			const type_t c = static_cast<type_t> (suffix[i]);
			const size_t k = prefix_len + i;
			for (size_t j = 0; j < count; ++j)
			{
				buffer[j * len + k] = c;
			}
		}
		fwrite (buffer, sizeof (type_t), buffer_size, input);
		delete [] buffer;

		// keys
		const bool none = suffix.match ().is_none ();
		const size_t len_match = none
			? prefix.len_matching ()
			: prefix_len + suffix.len_matching ();
		const rule_rank_t match = none
			? prefix.match ()
			: suffix.match ();
		keygen (keys, count, len, len_match, match);
	}

	return size;
}

static arccount_t cover_one (FILE * input, std::ofstream & keys, const multipath_t & prefix, const path_t & suffix)
{
	switch (encoding.szCodeUnit ())
	{
		case 4: return generic_cover_one<uint32_t> (input, keys, prefix, suffix);
		case 2: return generic_cover_one<uint16_t> (input, keys, prefix, suffix);
		case 1: return generic_cover_one<uint8_t>  (input, keys, prefix, suffix);
		default: return arccount_t (0u);
	}
}

} // namespace re2c
