#include "src/util/c99_stdint.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "src/conf/msg.h"
#include "src/conf/opt.h"
#include "src/globals.h"
#include "src/ir/regexp/encoding/enc.h"
#include "src/ir/rule_rank.h"
#include "src/ir/skeleton/path.h"
#include "src/ir/skeleton/skeleton.h"
#include "src/util/u32lim.h"

namespace re2c
{

/*
 * note [counting skeleton edges]
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
 */

// See note [counting skeleton edges].
// Type for calculating the size of path cover.
// Paths are dumped to file as soon as generated and don't eat
// heap space. The total size of path cover (measured in edges)
// is O(N^2) where N is the number of edges in skeleton.
typedef u32lim_t<1024 * 1024 * 1024> covers_t; // ~1Gb

template<typename uintn_t> static uintn_t to_le(uintn_t n)
{
	uintn_t m;
	uint8_t *p = reinterpret_cast<uint8_t*>(&m);
	for (size_t i = 0; i < sizeof(uintn_t); ++i) {
		p[i] = static_cast<uint8_t>(n >> (i * 8));
	}
	return m;
}

template<typename key_t> static void keygen(FILE *f, size_t count,
	size_t len, size_t len_match, rule_rank_t match)
{
	const key_t m = Skeleton::rule2key<key_t>(match);

	const size_t keys_size = 3 * count;
	key_t * keys = new key_t[keys_size];
	for (uint32_t i = 0; i < keys_size;) {
		keys[i++] = to_le<key_t>(static_cast<key_t>(len));
		keys[i++] = to_le<key_t>(static_cast<key_t>(len_match));
		keys[i++] = to_le<key_t>(m);
	}
	fwrite(keys, sizeof(key_t), keys_size, f);
	delete[] keys;
}

template<typename cunit_t, typename key_t> static covers_t cover_one(
	Skeleton &skel, FILE *input, FILE * keys, const path_t & path)
{
	const size_t len = path.len();

	size_t count = 0;
	for (size_t i = 0; i < len; ++i) {
		count = std::max (count, path.arc(skel, i).size());
	}

	const covers_t size = covers_t::from64(len)
		* covers_t::from64(count);
	if (!size.overflow()) {
		// input
		const size_t buffer_size = size.uint32();
		cunit_t *buffer = new cunit_t [buffer_size];
		for (size_t i = 0; i < len; ++i) {
			const std::vector<uint32_t> &arc = path.arc(skel, i);
			const size_t width = arc.size();
			for (size_t j = 0; j < count; ++j) {
				const size_t k = j % width;
				buffer[j * len + i] = to_le<cunit_t>(static_cast<cunit_t>(arc[k]));
			}
		}
		fwrite (buffer, sizeof(cunit_t), buffer_size, input);
		delete[] buffer;

		// keys
		keygen<key_t>(keys, count, len, path.len_matching(skel), path.match(skel));
	}

	return size;
}

/*
 * note [generating skeleton path cover]
 *
 * With --skeleton switch we need to generate lots of data: strings that
 * correspond to various paths in DFA and match given regular expression.
 * We try to generate path cover (a set of paths that cover all skeleton
 * arcs at least once). Generation must stop as soon as the size of path
 * cover exceeds limit (in which case we'll only get a partial path cover).
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
 * See also note [counting skeleton edges].
 *
 */
template <typename cunit_t, typename key_t> static void cover(
	Skeleton &skel,
	FILE *input,
	FILE *keys,
	path_t &prefix,
	covers_t &size,
	size_t i)
{
	const Node &node = skel.nodes[i];
	uint8_t &loop = skel.loops[i];
	suffix_t *&suffix = skel.suffixes[i];

	if (node.end() && suffix == NULL) {
		suffix = new suffix_t;
	}

	if (suffix != NULL)
	{
		prefix.push_sfx(*suffix);
		size = size + cover_one<cunit_t, key_t>(skel, input, keys, prefix);
		prefix.pop_sfx(*suffix);
	} else if (loop < 2) {
		local_inc _(loop);
		Node::arcs_t::const_iterator
			arc = node.arcs.begin(),
			end = node.arcs.end();
		for (; arc != end && !size.overflow(); ++arc) {
			const size_t j = arc->first;

			prefix.push(j);
			cover<cunit_t, key_t>(skel, input, keys, prefix, size, j);
			prefix.pop();

			const suffix_t *sfx = skel.suffixes[j];
			if (sfx != NULL && suffix == NULL) {
				suffix = new suffix_t(*sfx);
				suffix->push(j);
			}
		}
	}
}

template<typename cunit_t, typename key_t> static void generate_paths_cunit_key(
	Skeleton &skel, FILE *input, FILE *keys)
{
	path_t prefix(0);
	covers_t size = covers_t::from32(0u);

	cover<cunit_t, key_t>(skel, input, keys, prefix, size, 0);

	if (size.overflow()) {
		warning(NULL, skel.line, false,
			"DFA %sis too large: can only generate partial path cover",
			incond(skel.cond).c_str());
	}
}

template<typename cunit_t> static void generate_paths_cunit(
	Skeleton &skel, FILE *input, FILE *keys)
{
	switch (skel.sizeof_key) {
		case 4: generate_paths_cunit_key<cunit_t, uint32_t>(skel, input, keys); break;
		case 2: generate_paths_cunit_key<cunit_t, uint16_t>(skel, input, keys); break;
		case 1: generate_paths_cunit_key<cunit_t, uint8_t>(skel, input, keys); break;
	}
}

static void generate_paths(Skeleton &skel, FILE *input, FILE *keys)
{
	switch (opts->encoding.szCodeUnit()) {
		case 4: generate_paths_cunit<uint32_t>(skel, input, keys); break;
		case 2: generate_paths_cunit<uint16_t>(skel, input, keys); break;
		case 1: generate_paths_cunit<uint8_t>(skel, input, keys); break;
	}
}

void emit_data(Skeleton &skel, const char *fname)
{
	const std::string input_name = std::string(fname) + "." + skel.name + ".input";
	FILE *input = fopen(input_name.c_str(), "wb");
	if (!input) {
		error("cannot open file: %s", input_name.c_str());
		exit(1);
	}
	const std::string keys_name = std::string(fname) + "." + skel.name + ".keys";
	FILE *keys = fopen (keys_name.c_str(), "wb");
	if (!keys) {
		error("cannot open file: %s", keys_name.c_str());
		exit(1);
	}

	generate_paths(skel, input, keys);

	fclose(input);
	fclose(keys);
}

} // namespace re2c
