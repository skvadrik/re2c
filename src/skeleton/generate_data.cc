#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <stdio.h>
#include <algorithm>
#include <map>
#include <string>
#include <utility>
#include <valarray>
#include <vector>

#include "src/options/opt.h"
#include "src/debug/debug.h"
#include "src/dfa/tcmd.h"
#include "src/encoding/enc.h"
#include "src/msg/msg.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/skeleton/path.h"
#include "src/skeleton/skeleton.h"
#include "src/util/forbid_copy.h"
#include "src/util/u32lim.h"
#include "src/util/wrap_iter.h"


namespace re2c {

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

static uint32_t nsteps(uint32_t lower, uint32_t upper)
{
    return 2 + (upper - lower - 1) / step(lower, upper);
}

static void apply(std::vector<size_t> *tags, const tcmd_t *cmd, size_t pos)
{
    for (const tcmd_t *p = cmd; p; p = p->next) {
        const tagver_t l = p->lhs, r = p->rhs, *h = p->history;
        std::vector<size_t> &t = tags[l];
        if (tcmd_t::iscopy(p)) {
            t = tags[r];
        } else if (tcmd_t::isset(p)) {
            t.clear();
            t.push_back(*h == TAGVER_BOTTOM ? Skeleton::DEFTAG : pos);
        } else {
            if (l != r) t = tags[r];
            std::vector<size_t> x;
            for (; *h != TAGVER_ZERO; ++h) {
                x.push_back(*h == TAGVER_BOTTOM ? Skeleton::DEFTAG : pos);
            }
            t.insert(t.end(), x.rbegin(), x.rend());
        }
    }
}

static size_t path_width(const path_t &path, const Skeleton &skel)
{
    size_t width = 0;
    for (size_t i = 0; i < path.len(); ++i) {

        // width of multiarc: total number of characters picked from all ranges
        size_t w = 0;
        const Node::arc_t &arc = path.arc(skel, i);
        for (Node::citer_t a = arc.begin(); a != arc.end(); ++a) {
            w += nsteps(a->lower, a->upper);
        }

        // width of multipath: maximal width of multiarc
        width = std::max(width, w);
    }
    return width;
}

template<typename cunit_t>
static void write_input(const path_t &path, const Skeleton &skel,
    size_t width, FILE *file)
{
    const size_t
        len = path.len(),
        size = len * width;
    cunit_t *buffer = new cunit_t[size];

    // pick characters from ranges
    for (size_t i = 0; i < len; ++i) {
        Node::wciter_t a(path.arc(skel, i));
        for (size_t w = 0; w < width; ++a) {
            const uint32_t
                l = a->lower,
                u = a->upper,
                d = step(l, u);
            for (uint32_t m = l; m < u + d && w < width; m += d, ++w) {
                buffer[w * len + i] = to_le(static_cast<cunit_t>(std::min(m, u)));
            }
        }
    }

    fwrite(buffer, sizeof(cunit_t), size, file);

    delete[] buffer;
}

template<typename key_t>
static void write_keys(const path_t &path, const Skeleton &skel,
    size_t width, FILE *file)
{
    // find last accepting node
    size_t f;
    for (f = path.len(); f > 0 && path.node(skel, f).rule == Rule::NONE; --f);

    // calculate tags: start with default and apply commands step by step
    const size_t
        nver = skel.ntagver,
        ntag = width * nver,
        offby = skel.opts->lookahead ? 0 : 1;
    std::vector<size_t> *tags = new std::vector<size_t>[ntag];

    // initial tags (TDFA(0))
    for (size_t w = 0; w < width; ++w) {
        apply(&tags[w * nver], skel.cmd0, 0);
    }
    for (size_t i = 0; i < f; ++i) {
        Node::wciter_t a(path.arc(skel, i));

        // tags commands in state (staDFA), -1 because of "delayed store"
        for (size_t w = 0; w < width; ++w) {
            apply(&tags[w * nver], path.node(skel, i).stacmd, i - 1);
        }

        // tag commands on transitions (TDFA(0), TDFA(1))
        for (size_t w = 0; w < width; ++a) {
            uint32_t n = nsteps(a->lower, a->upper);
            for (; n --> 0 && w < width; ++w) {
                apply(&tags[w * nver], a->cmd, i + offby);
            }
        }
    }
    // tag commands in final states
    const tcmd_t *fcmd = path.node(skel, f).cmd;
    for (size_t w = 0; w < width; ++w) {

        // staDFA, -1 because of "delayed store"
        apply(&tags[w * nver], path.node(skel, f).stacmd, f - 1);

        // TDFA(1)
        apply(&tags[w * nver], fcmd, f);
    }

    const size_t rule = path.node(skel, f).rule;
    size_t matched = 0, ltag = 0, htag = 0, trail = 0;
    if (rule != Rule::NONE) {

        const Rule &r = skel.rules[rule];
        ltag = r.ltag;
        htag = r.htag;
        trail = r.ttag;

        // matched length might depend on tag values
        if (trail == htag) {
            matched = f;
        } else {
            DASSERT(!fixed(skel.tags[trail])); // no fixed trailing context
            matched = tags[skel.finvers[trail]].back();
            DASSERT(matched != Skeleton::DEFTAG);
        }
    }

    // count keys
    size_t nkey = 0;
    for (size_t w = 0; w < width; ++w) {
        nkey += 3;
        for (size_t t = ltag; t < htag; ++t) {
            const Tag &tag = skel.tags[t];
            if (t == trail || fictive(tag)) continue;
            const size_t
                base = fixed(tag) ? tag.base : t,
                bver = static_cast<size_t>(skel.finvers[base]);
            if (history(tag)) nkey += tags[w * nver + bver].size();
            ++nkey;
        }
    }

    // keys: 1 - scanned length, 2 - matched length, 3 - matched rule, the rest - tags
    key_t *keys = new key_t[nkey], *k = keys;
    for (size_t w = 0; w < width; ++w) {
        *k++ = to_le(static_cast<key_t>(path.len()));
        *k++ = to_le(static_cast<key_t>(matched));
        *k++ = to_le(rule2key<key_t>(rule, skel.defrule));

        for (size_t t = ltag; t < htag; ++t) {
            const Tag &tag = skel.tags[t];
            if (t == trail || fictive(tag)) continue;

            const size_t
                base = fixed(tag) ? tag.base : t,
                bver = static_cast<size_t>(skel.finvers[base]);
            const std::vector<size_t> &h = tags[w * nver + bver];
            if (history(tag)) {
                const size_t hlen = h.size();

                // Abort if history length exceeds maximum value of key type.
                // This is not always true, but it is difficult to estimate
                // history length in advance, and explicit assertion failure
                // is better than an obscure skeleton match failure.
                //
                // TODO: Ideally we should use different encoding for the keys
                // (structs with 2 or 4 byte fields for history length and
                // proper serialization/deserialization instead of flat arrays).
                DASSERT(hlen < std::numeric_limits<key_t>::max());

                *k++ = to_le(static_cast<key_t>(hlen));
                for (size_t i = 0; i < hlen; ++i) {
                    *k++ = to_le(static_cast<key_t>(h[i]));
                }
            } else {
                *k++ = to_le(static_cast<key_t>(h.back()));
            }
        }
    }

    // dump to file
    fwrite(keys, sizeof(key_t), nkey, file);

    delete[] tags;
    delete[] keys;
}

template<typename cunit_t, typename key_t>
static cover_size_t cover_one(const Skeleton &skel, cover_t &cover)
{
    const path_t &path = cover.prefix;

    const size_t width = path_width(path, skel);

    const cover_size_t size
        = cover_size_t::from64(path.len())
        * cover_size_t::from64(width);

    if (!size.overflow()) {
        write_input<cunit_t>(path, skel, width, cover.input);
        write_keys<key_t>(path, skel, width, cover.keys);
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

    if (node.end()) {
        suffix.init = true;
    }

    if (suffix.init)
    {
        prefix.push_sfx(suffix);
        size = size + cover_one<cunit_t, key_t>(skel, cover);
        prefix.pop_sfx(suffix);
    }

    // unroll one iteration of the loop
    else if (loop < 2) {
        local_inc _(loop);

        Node::arcs_t::const_iterator
            arc = node.arcs.begin(),
            end = node.arcs.end();
        const suffix_t *min_sfx = NULL;
        size_t min_idx = 0;

        // pick the shortest suffix to minimize cover size
        // handle all child states before setting this state's suffix
        for (; arc != end && !size.overflow(); ++arc) {
            const size_t j = arc->first;

            prefix.push(j);
            gencover<cunit_t, key_t>(skel, cover, j);
            prefix.pop();

            const suffix_t &sfx = cover.suffixes[j];
            if (sfx.init && (!min_sfx || sfx.length() < min_sfx->length())) {
                min_sfx = &sfx;
                min_idx = j;
            }
        }

        if (min_sfx == NULL) {
            // all outgoing paths loop back into this node
            // this can happen in cases like [^]*
        }
        else {
            suffix = *min_sfx;
            suffix.push(min_idx);
        }
    }
}

template<typename cunit_t, typename key_t>
    static void generate_paths_cunit_key(const Skeleton &skel, cover_t &cover)
{
    gencover<cunit_t, key_t>(skel, cover, 0);
    if (cover.size.overflow()) {
        skel.msg.warning(NULL, skel.loc, false,
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
    switch (skel.opts->encoding.szCodeUnit()) {
        case 4: generate_paths_cunit<uint32_t>(skel, cover); break;
        case 2: generate_paths_cunit<uint16_t>(skel, cover); break;
        case 1: generate_paths_cunit<uint8_t>(skel, cover); break;
    }
}

void emit_data(const Skeleton &skel)
{
    std::string fname = skel.opts->output_file;
    if (fname.empty()) {
        fname = "<stdout>";
    }

    const std::string input_name = fname + "." + skel.name + ".input";
    FILE *input = fopen(input_name.c_str(), "wb");
    if (!input) {
        fatal("cannot open file: %s", input_name.c_str());
    }
    const std::string keys_name = std::string(fname) + "." + skel.name + ".keys";
    FILE *keys = fopen (keys_name.c_str(), "wb");
    if (!keys) {
        fatal("cannot open file: %s", keys_name.c_str());
    }

    cover_t cover(input, keys, skel.nodes_count);
    generate_paths(skel, cover);

    fclose(input);
    fclose(keys);
}

} // namespace re2c
