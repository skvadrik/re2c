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
typedef u32lim_t<1024 * 1024 * 1024> cover_size_t; // ~1Gb

struct cover_t
{
	FILE *input;
	FILE *keys;
	std::vector<uint8_t> loops;
	std::vector<suffix_t> suffixes;
	path_t prefix;
	cover_size_t size;

	cover_t(FILE *fi, FILE *fk, size_t nnodes):
		input(fi), keys(fk), loops(nnodes),
		suffixes(nnodes), prefix(0),
		size(cover_size_t::from32(0u)) {}

	FORBID_COPY(cover_t);
};

template<typename uintn_t> static uintn_t to_le(uintn_t n)
{
	uintn_t m;
	uint8_t *p = reinterpret_cast<uint8_t*>(&m);
	for (size_t i = 0; i < sizeof(uintn_t); ++i) {
		p[i] = static_cast<uint8_t>(n >> (i * 8));
	}
	return m;
}

// pick at most 0x100 unique edges from this range
// (for 1-byte code units this covers the whole range: [0 - 0xFF])
//   - range bounds must be included
//   - values should be evenly distributed
//   - values should be deterministic
static uint32_t step(uint32_t lower, uint32_t upper)
{
	return 1 + (upper - lower) / 0x100;
}

static void apply(size_t *tags, const tcmd_t *cmd, size_t pos)
{
	if (!cmd) return;
	for (const tagsave_t *p = cmd->save; p; p = p->next) {
		tags[p->ver] = pos;
	}
	for (const tagcopy_t *p = cmd->copy; p; p = p->next) {
		tags[p->lhs] = tags[p->rhs];
	}
}

template<typename cunit_t, typename key_t> static cover_size_t cover_one(
	const Skeleton &skel, cover_t &cover)
{
	const path_t &path = cover.prefix;
	const size_t len = path.len();

	size_t width = 0;
	for (size_t i = 0; i < len; ++i) {

		// width of multiarc: total number of characters picked from all ranges
		size_t w = 0;
		const Node::arc_t &arc = path.arc(skel, i);
		for (Node::citer_t a = arc.begin(); a != arc.end(); ++a) {
			const uint32_t
				l = a->lower,
				u = a->upper;
			w += 2 + (u - l - 1) / step(l, u);
		}

		// width of multipath: maximal width of multiarc
		width = std::max(width, w);
	}

	const cover_size_t size = cover_size_t::from64(len)
		* cover_size_t::from64(width);
	if (size.overflow()) return size;

	const size_t
		nver = skel.ntagver,
		tags_size = width * nver,
		buffer_size = size.uint32(),
		NIL = std::numeric_limits<size_t>::max();
	cunit_t *buffer = new cunit_t [buffer_size];
	size_t *tags = new size_t[tags_size];

	// find the last accepting node
	size_t f = len;
	for (; f > 0; --f) {
		if (path.node(skel, f).rule != Rule::NONE) break;
	}
	const Node &fin = path.node(skel, f);

	// calculate input characters and tag values
	std::fill(tags, tags + tags_size, NIL);
	for (size_t i = 0; i < len; ++i) {
		const Node::arc_t &arc = path.arc(skel, i);
		Node::citer_t a = arc.begin();

		for (size_t j = 0; j < width;) {
			const uint32_t
				l = a->lower,
				u = a->upper,
				d = step(l, u);

			for (uint32_t m = l; m < u + d && j < width; m += d, ++j) {
				buffer[j * len + i] = to_le(static_cast<cunit_t>(std::min(m, u)));
				if (i < f) {
					apply(&tags[j * nver], a->cmd, i);
				}
			}

			if (++a == arc.end()) a = arc.begin();
		}
	}
	for (size_t j = 0; j < width; ++j) {
		apply(&tags[j * nver], fin.cmd, f);
	}

	// write input
	fwrite (buffer, sizeof(cunit_t), buffer_size, cover.input);

	// write keys
	const key_t match = rule2key<key_t>(fin.rule, skel.defrule);
	size_t len_match = 0, ltag = 0, htag = 0;
	const tagver_t *vers = NULL;
	if (fin.rule != Rule::NONE) {
		const Rule &rule = skel.rules[fin.rule];
		ltag = rule.ltag;
		htag = rule.htag;
		vers = rule.tags;
		const size_t trail = rule.trail;
		if (trail == Tag::NONE) {
			len_match = f;
		} else {
			assert(skel.tags[trail].type == Tag::VAR);
			len_match = tags[vers[trail]];
			assert(len_match != NIL);
		}
	}
	const size_t keys_size = (3 + htag - ltag) * width;
	key_t *keys = new key_t[keys_size], *p = keys;
	for (size_t j = 0; j < width; ++j) {
		*p++ = to_le<key_t>(static_cast<key_t>(len));
		*p++ = to_le<key_t>(static_cast<key_t>(len_match));
		*p++ = to_le<key_t>(match);
		for (size_t t = ltag; t < htag; ++t) {
			*p++ = to_le<key_t>(static_cast<key_t>(tags[vers[t]]));
		}
	}
	fwrite(keys, sizeof(key_t), keys_size, cover.keys);
	delete[] keys;

	delete[] buffer;
	delete[] tags;

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
template <typename cunit_t, typename key_t> static void gencover(
	const Skeleton &skel,
	cover_t &cover,
	size_t i)
{
	const Node &node = skel.nodes[i];
	uint8_t &loop = cover.loops[i];
	suffix_t &suffix = cover.suffixes[i];
	path_t &prefix = cover.prefix;
	cover_size_t &size = cover.size;

	if (node.end() && !suffix.init) {
		suffix.init = true;
	}

	if (suffix.init)
	{
		prefix.push_sfx(suffix);
		size = size + cover_one<cunit_t, key_t>(skel, cover);
		prefix.pop_sfx(suffix);
	} else if (loop < 2) {
		local_inc _(loop);

		Node::arcs_t::const_iterator
			arc = node.arcs.begin(),
			end = node.arcs.end();
		for (; arc != end && !size.overflow(); ++arc) {
			const size_t j = arc->first;

			prefix.push(j);
			gencover<cunit_t, key_t>(skel, cover, j);
			prefix.pop();

			const suffix_t &sfx = cover.suffixes[j];
			if (sfx.init && !suffix.init) {
				suffix = sfx;
				suffix.push(j);
			}
		}
	}
}

template<typename cunit_t, typename key_t>
	static void generate_paths_cunit_key(const Skeleton &skel, cover_t &cover)
{
	gencover<cunit_t, key_t>(skel, cover, 0);
	if (cover.size.overflow()) {
		warning(NULL, skel.line, false,
			"DFA %sis too large: can only generate partial path cover",
			incond(skel.cond).c_str());
	}
}

template<typename cunit_t>
	static void generate_paths_cunit(const Skeleton &skel, cover_t &cover)
{
	switch (skel.sizeof_key) {
		case 8: generate_paths_cunit_key<cunit_t, uint64_t>(skel, cover); break;
		case 4: generate_paths_cunit_key<cunit_t, uint32_t>(skel, cover); break;
		case 2: generate_paths_cunit_key<cunit_t, uint16_t>(skel, cover); break;
		case 1: generate_paths_cunit_key<cunit_t, uint8_t>(skel, cover); break;
	}
}

static void generate_paths(const Skeleton &skel, cover_t &cover)
{
	switch (opts->encoding.szCodeUnit()) {
		case 4: generate_paths_cunit<uint32_t>(skel, cover); break;
		case 2: generate_paths_cunit<uint16_t>(skel, cover); break;
		case 1: generate_paths_cunit<uint8_t>(skel, cover); break;
	}
}

void emit_data(const Skeleton &skel)
{
	std::string fname = opts->output_file;
	if (fname.empty()) {
		fname = "<stdout>";
	}

	const std::string input_name = fname + "." + skel.name + ".input";
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

	cover_t cover(input, keys, skel.nodes_count);
	generate_paths(skel, cover);

	fclose(input);
	fclose(keys);
}

} // namespace re2c
