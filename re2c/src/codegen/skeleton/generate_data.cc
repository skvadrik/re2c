#include <stdlib.h> // exit

#include "src/codegen/indent.h"
#include "src/codegen/print.h"
#include "src/codegen/skeleton/skeleton.h"
#include "src/conf/msg.h"

namespace re2c
{

template <typename cunit_t, typename key_t>
	static void permutate_one (FILE * input, FILE * keys, const multipath_t & path);
template <typename cunit_t, typename key_t>
	static Node::covers_t cover_one (FILE * input, FILE * keys, const multipath_t & prefix, const path_t & suffix);

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
Node::permuts_t Node::sizeof_permutate (permuts_t wid, permuts_t len)
{
	if (end ())
	{
		return wid * len;
	}
	else if (loop < 2)
	{
		local_inc _ (loop);
		permuts_t size (0u);
		const permuts_t new_len = len + permuts_t (1u);
		for (arcs_t::iterator i = arcs.begin (); i != arcs.end (); ++i)
		{
			const permuts_t new_wid = wid * permuts_t (i->second.size ());
			if (new_wid.overflow ())
			{
				return permuts_t::limit ();
			}
			size = size + i->first->sizeof_permutate (new_wid, new_len);
			if (size.overflow ())
			{
				return permuts_t::limit ();
			}
		}
		return size;
	}
	else
	{
		return permuts_t (0u);
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
template <typename cunit_t, typename key_t>
	void Node::permutate (const multipath_t & prefix, FILE * input, FILE * keys)
{
	if (end ())
	{
		permutate_one<cunit_t, key_t> (input, keys, prefix);
	}
	else if (loop < 2)
	{
		local_inc _ (loop);
		for (arcs_t::iterator i = arcs.begin (); i != arcs.end (); ++i)
		{
			multipath_t new_prefix = prefix;
			new_prefix.extend (i->first->rule, i->first->ctx, &i->second);
			i->first->permutate<cunit_t, key_t> (new_prefix, input, keys);
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
template <typename cunit_t, typename key_t>
	Node::covers_t Node::cover (const multipath_t & prefix, FILE * input, FILE * keys)
{
	covers_t size (0u);
	if (suffix != NULL)
	{
		size = cover_one<cunit_t, key_t> (input, keys, prefix, *suffix);
	}
	else if (end ())
	{
		suffix = new path_t (rule, ctx);
	}
	else if (loop < 2)
	{
		local_inc _ (loop);
		for (arcs_t::iterator i = arcs.begin (); i != arcs.end (); ++i)
		{
			multipath_t new_prefix = prefix;
			new_prefix.extend (i->first->rule, i->first->ctx, &i->second);
			size = size + i->first->cover<cunit_t, key_t> (new_prefix, input, keys);
			if (size.overflow ())
			{
				return covers_t::limit ();
			}
			if (i->first->suffix != NULL && suffix == NULL)
			{
				suffix = new path_t (rule, ctx);
				suffix->append (i->second[0], i->first->suffix);
			}
		}
	}
	return size;
}

template <typename cunit_t, typename key_t>
	void Skeleton::generate_paths_cunit_key (FILE * input, FILE * keys)
{
	multipath_t prefix (nodes->rule, nodes->ctx);
	if (nodes->sizeof_permutate (Node::permuts_t (1u), Node::permuts_t (0u)).overflow ())
	{
		if (nodes->cover<cunit_t, key_t> (prefix, input, keys).overflow ())
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
		nodes->permutate<cunit_t, key_t> (prefix, input, keys);
	}
}

template <typename cunit_t>
	void Skeleton::generate_paths_cunit (FILE * input, FILE * keys)
{
	switch (sizeof_key)
	{
		case 4: generate_paths_cunit_key<cunit_t, uint32_t> (input, keys); break;
		case 2: generate_paths_cunit_key<cunit_t, uint16_t> (input, keys); break;
		case 1: generate_paths_cunit_key<cunit_t, uint8_t> (input, keys);  break;
	}
}

void Skeleton::generate_paths (FILE * input, FILE * keys)
{
	switch (opts->encoding.szCodeUnit ())
	{
		case 4: generate_paths_cunit<uint32_t> (input, keys); break;
		case 2: generate_paths_cunit<uint16_t> (input, keys); break;
		case 1: generate_paths_cunit<uint8_t>  (input, keys); break;
	}
}

void Skeleton::emit_data (const char * fname)
{
	const std::string input_name = std::string (fname) + "." + name + ".input";
	FILE * input = fopen (input_name.c_str (), "wb");
	if (!input)
	{
		error ("cannot open file: %s", input_name.c_str ());
		exit (1);
	}
	const std::string keys_name = std::string (fname) + "." + name + ".keys";
	FILE * keys = fopen (keys_name.c_str (), "wb");
	if (!keys)
	{
		error ("cannot open file: %s", keys_name.c_str ());
		exit (1);
	}

	generate_paths (input, keys);

	fclose (input);
	fclose (keys);
}

template <typename key_t>
	static void keygen (FILE * f, size_t count, size_t len, size_t len_match, rule_rank_t match)
{
	const key_t m = Skeleton::rule2key<key_t> (match);

	const size_t keys_size = 3 * count;
	key_t * keys = new key_t [keys_size];
	for (uint32_t i = 0; i < keys_size;)
	{
		keys[i++] = static_cast<key_t> (len);
		keys[i++] = static_cast<key_t> (len_match);
		keys[i++] = m;
	}
	fwrite (keys, sizeof (key_t), keys_size, f);
	delete [] keys;
}

template <typename cunit_t, typename key_t>
	static void permutate_one (FILE * input, FILE * keys, const multipath_t & path)
{
	const size_t len = path.len ();

	size_t count = 1;
	for (size_t i = 0; i < len; ++i)
	{
		count *= path[i]->size ();
	}

	// input
	const size_t buffer_size = len * count;
	cunit_t * buffer = new cunit_t [buffer_size];
	for (size_t i = 0, period = count; i < len; ++i)
	{
		const multiarc_t & arc = *path[i];
		const size_t width = arc.size ();
		period /= width;
		for (size_t j = 0; j < count; ++j)
		{
			const size_t k = (j / period) % width;
			buffer[j * len + i] = static_cast<cunit_t> (arc[k]);
		}
	}
	fwrite (buffer, sizeof (cunit_t), buffer_size, input);
	delete [] buffer;

	// keys
	keygen<key_t> (keys, count, len, path.len_matching (), path.match ());
}

template <typename cunit_t, typename key_t>
	static Node::covers_t cover_one (FILE * input, FILE * keys, const multipath_t & prefix, const path_t & suffix)
{
	const size_t prefix_len = prefix.len ();
	const size_t suffix_len = suffix.len ();
	const size_t len = prefix_len + suffix_len;

	size_t count = 1; // width of suffix is one arc
	for (size_t i = 0; i < prefix_len; ++i)
	{
		count = std::max (count, prefix[i]->size ());
	}

	const Node::covers_t size = Node::covers_t (len) * Node::covers_t (count);
	if (!size.overflow ())
	{
		// input
		const size_t buffer_size = size.uint32 ();
		cunit_t * buffer = new cunit_t [buffer_size];
		for (size_t i = 0; i < prefix_len; ++i)
		{
			const std::vector<uint32_t> & arc = *prefix[i];
			const size_t width = arc.size ();
			for (size_t j = 0; j < count; ++j)
			{
				const size_t k = j % width;
				buffer[j * len + i] = static_cast<cunit_t> (arc[k]);
			}
		}
		for (size_t i = 0; i < suffix_len; ++i)
		{
			const cunit_t c = static_cast<cunit_t> (suffix[i]);
			const size_t k = prefix_len + i;
			for (size_t j = 0; j < count; ++j)
			{
				buffer[j * len + k] = c;
			}
		}
		fwrite (buffer, sizeof (cunit_t), buffer_size, input);
		delete [] buffer;

		// keys
		keygen<key_t> (keys, count, len, len_matching (prefix, suffix), match (prefix, suffix));
	}

	return size;
}

} // namespace re2c
