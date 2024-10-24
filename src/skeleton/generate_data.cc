#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <algorithm>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "src/options/opt.h"
#include "src/dfa/tcmd.h"
#include "src/encoding/enc.h"
#include "src/msg/msg.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/skeleton/path.h"
#include "src/skeleton/skeleton.h"
#include "src/util/check.h"
#include "src/util/forbid_copy.h"
#include "src/util/u32lim.h"

namespace re2c {

// note [counting skeleton edges]
//
// To avoid any possible overflows all size calculations are wrapped in a special truncated
// unsigned 32-bit integer type that checks overflow on each binary operation or conversion from
// another type.
//
// Two things contribute to size calculation: path length and the number of outgoing arcs in each
// node. Some considerations on why these values will not overflow before they are converted to
// truncated type:
//
//   - Maximal number of outgoing arcs in each node cannot exceed 32 bits: it is bounded by the
//     number of code units in current encoding, and re2c doesn't support any encoding with more
//     than 2^32 code units. Conversion is safe.
//
//   - Maximal path length cannot exceed 32 bits: we estimate it right after skeleton construction
//     and check for overflow. If path length does overflow, an error is reported and re2c aborts.

// See note [counting skeleton edges].
// Type for calculating the size of path cover. Paths are dumped to file as soon as generated and
// don't eat heap space. The total size of path cover (measured in edges) is O(N^2) where N is the
// number of edges in skeleton.
using cover_size_t = u32lim_t<1024 * 1024 * 1024>; // ~1Gb

struct cover_t {
    std::vector<uint8_t> loops;
    std::vector<suffix_t> suffixes;
    path_t prefix;
    cover_size_t size;

    cover_t(size_t nnodes)
            : loops(nnodes), suffixes(nnodes), prefix(0), size(cover_size_t::from32(0u)) {}

    FORBID_COPY(cover_t);
};

template<typename uintn_t> static uintn_t to_le(uintn_t n) {
    uintn_t m;
    uint8_t* p = reinterpret_cast<uint8_t*>(&m);
    for (size_t i = 0; i < sizeof(uintn_t); ++i) {
        p[i] = static_cast<uint8_t>(n >> (i * 8));
    }
    return m;
}

// pick at most 0x100 unique edges from this range (for 1-byte code units this covers the whole
// range: [0 - 0xFF])
//   - range bounds must be included
//   - values should be evenly distributed
//   - values should be deterministic
static inline uint32_t step(uint32_t lower, uint32_t upper) {
    return 1 + (upper - lower) / 0x100;
}

static inline uint32_t nsteps(uint32_t lower, uint32_t upper) {
    return 2 + (upper - lower - 1) / step(lower, upper);
}

static void apply(Skeleton& skel, const tcmd_t* cmd, uint32_t dist) {
    uint32_t* tags = skel.tagvals;

    for (const tcmd_t* p = cmd; p; p = p->next) {
        const tagver_t l = p->lhs, r = p->rhs, *h = p->history;
        if (tcmd_t::iscopy(p)) {
            tags[l] = tags[r];
        } else if (tcmd_t::isset(p)) {
            tags[l] = *h == TAGVER_BOTTOM ? Skeleton::DEFTAG : dist;
        } else {
            if (l != r) tags[l] = tags[r];

            uint32_t t = tags[l];
            const tagver_t* h0 = h;
            for (; *h != TAGVER_ZERO; ++h);
            for (; h --> h0; ) {
                t = mtag(skel.tagtrie, t, *h == TAGVER_BOTTOM ? Skeleton::DEFTAG : dist);
            }
            tags[l] = t;
        }
    }
}

static size_t path_width(const path_t& path, const Skeleton& skel) {
    size_t width = 0;
    for (size_t i = 0; i < path.len(); ++i) {

        // width of multiarc: total number of characters picked from all ranges
        size_t w = 0;
        const Node::range_t* a0 = path.arc(skel, i), *a = a0;
        do {
            w += nsteps(a->lower, a->upper);
            a = a->next;
        } while (a != a0);

        // width of multipath: maximal width of multiarc
        width = std::max(width, w);
    }
    return width;
}

template<typename cunit_t>
static void write_input(const path_t& path, Skeleton& skel, size_t width) {
    const size_t len = path.len();
    const size_t size = len * width;

    skel.arc_iters.grow(len);
    skel.char_iters.grow(len);
    const Node::range_t** arcs = skel.arc_iters.ptr_;
    size_t* chars = skel.char_iters.ptr_;
    for (size_t i = 0; i < len; ++i) {
        const Node::range_t* a = path.arc(skel, i);
        arcs[i] = a;
        chars[i] = a->lower;
    }

    cunit_t* p = skel.buf_data.alloc<cunit_t>(size);

    for (size_t w = 0; w < width; ++w) {
        for (size_t i = 0; i < len; ++i) {
            const Node::range_t* a = arcs[i];
            const uint32_t upper = a->upper;
            const uint32_t stride = step(a->lower, upper);
            uint32_t c = static_cast<uint32_t>(chars[i]);

            if (c >= upper) {
                // the current range covered, start the next one
                arcs[i] = a = a->next;
                chars[i] = a->lower;
            } else if (c >= upper - stride) {
                // Pick the last character in the current range (the last step may be shorter than
                // the stride, so round up to the upper bound and avoid potential overflow on `c` +
                // stride).
                chars[i] = upper;
            } else {
                // step to the next character in the current range
                chars[i] += stride;
            }

            *p++ = to_le(static_cast<cunit_t>(c));
        }
    }
}

template<typename key_t>
static void write_keys(const path_t& path, Skeleton& skel, size_t width) {
    // find last accepting node
    size_t f;
    for (f = path.len(); f > 0 && path.node(skel, f).rule == Rule::NONE; --f);
    const size_t rule = path.node(skel, f).rule;

    size_t ltag = 0, htag = 0, trail = 0;
    if (rule != Rule::NONE) {
        const Rule& r = skel.dfa.rules[rule];
        ltag = r.ltag;
        htag = r.htag;
        trail = r.ttag;
    }

    const Node::range_t** arcs = nullptr;
    size_t* chars = nullptr;
    uint32_t* tags = skel.tagvals;
    mtag_trie_t& tagtrie = skel.tagtrie;

    if (ltag < htag) {
        // init arc iterators and character iterators within each arc
        skel.arc_iters.grow(f);
        skel.char_iters.grow(f);
        arcs = skel.arc_iters.ptr_;
        chars = skel.char_iters.ptr_;
        for (size_t i = 0; i < f; ++i) {
            const Node::range_t* a = path.arc(skel, i);
            arcs[i] = a;
            chars[i] = nsteps(a->lower, a->upper);
        }
    }

    // Process each subpath of the multipath separately (rather than iterate on all subpaths in
    // lockstep) to reduce the size of storage used for intermediate tag values.
    for (size_t w = 0; w < width; ++w) {
        if (ltag < htag) {
            // clear buffers for tag values
            std::fill(tags, tags + skel.ntagver, MTAG_TRIE_ROOT);
            mtag_trie_clear(tagtrie);

            for (uint32_t i = 0; i < f; ++i) {
                // tag commands on transitions
                const Node::range_t* a = arcs[i];
                apply(skel, a->cmd, i);

                // advance character iterator; if it's the last one, then switch to the next arc
                if (--chars[i] == 0) {
                    arcs[i] = a = a->next;
                    chars[i] = nsteps(a->lower, a->upper);
                }
            }

            // tag commands in final states
            const tcmd_t* fcmd = path.node(skel, f).cmd;
            apply(skel, fcmd, static_cast<uint32_t>(f));
        }

        size_t matched = 0;
        if (rule != Rule::NONE) {
            if (trail == htag) {
                // no trailing context
                matched = f;
            } else {
                // trailing context must be an s-tag, not an m-tag
                const Tag& tag = skel.dfa.tags[trail];
                if (!fixed(tag)) {
                    // variable-length trailing context
                    matched = tags[skel.dfa.finvers[trail]];
                } else if (tag.base != Tag::RIGHTMOST) {
                    // fixed-length trailing context based on tag
                    matched = tags[skel.dfa.finvers[tag.base]] - tag.dist;
                } else {
                    // fixed-length trailing context based on cursor
                    matched = f - tag.dist;
                }
            }
            DCHECK(matched != Skeleton::DEFTAG);
        }

        // count keys
        size_t nkey = 3;
        for (size_t t = ltag; t < htag; ++t) {
            const Tag& tag = skel.dfa.tags[t];
            if (t == trail || fictive(tag)) continue;
            const size_t
            base = fixed(tag) ? tag.base : t,
            bver = static_cast<size_t>(skel.dfa.finvers[base]);
            if (history(tag)) {
                nkey += mtag_length(tagtrie, tags[bver]);
            }
            ++nkey;
        }

        key_t* k = skel.buf_keys.alloc<key_t>(nkey);

        // keys: 1 - scanned length, 2 - matched length, 3 - matched rule, the rest - tags
        *k++ = to_le(static_cast<key_t>(path.len()));
        *k++ = to_le(static_cast<key_t>(matched));
        *k++ = to_le(rule2key<key_t>(rule, skel.dfa.def_rule));

        for (size_t t = ltag; t < htag; ++t) {
            const Tag& tag = skel.dfa.tags[t];
            if (t == trail || fictive(tag)) continue;

            if (history(tag)) {
                DCHECK(!fixed(tag));
                // variable-length tag
                const size_t tver = static_cast<size_t>(skel.dfa.finvers[t]);
                uint32_t tval = tags[tver];
                const uint32_t len = mtag_length(tagtrie, tval);

                // Abort if history length exceeds maximum value of key type. This is not always
                // true, but it is difficult to estimate history length in advance, and explicit
                // assertion failure is better than an obscure skeleton match failure.
                //
                // TODO: Ideally we should use different encoding for the keys (structs with 2 or 4
                // byte fields for history length and proper serialization/deserialization instead
                // of flat arrays).
                DCHECK(len < std::numeric_limits<key_t>::max());

                // unfold m-tag history from the tag trie (from tail to head)
                std::vector<uint32_t>& history = skel.mtagval;
                history.clear();
                for (; tval != MTAG_TRIE_ROOT; ) {
                    const mtag_t& mt = tagtrie.head[tval];
                    history.push_back(mt.dist);
                    tval = mt.pred;
                }

                *k++ = to_le(static_cast<key_t>(len));
                for (uint32_t i = len; i --> 0; ) {
                    *k++ = to_le(static_cast<key_t>(history[i]));
                }
            } else {
                size_t tval;
                if (!fixed(tag)) {
                    // variable-length tag
                    const size_t tver = static_cast<size_t>(skel.dfa.finvers[t]);
                    tval = tags[tver];
                } else if (tag.base != Tag::RIGHTMOST) {
                    // fixed-length tag based on another tag
                    const size_t tver = static_cast<size_t>(skel.dfa.finvers[tag.base]);
                    tval = tags[tver];
                    if (tval != Skeleton::DEFTAG) tval -= tag.dist;
                } else {
                    // fixed-length tag based on the rightmost position
                    tval = f - tag.dist;
                }
                *k++ = to_le(static_cast<key_t>(tval));
            }
        }
    }
}

template<typename cunit_t, typename key_t>
static cover_size_t cover_one(Skeleton& skel, cover_t& cover) {
    const path_t& path = cover.prefix;
    const size_t width = path_width(path, skel);
    const cover_size_t size = cover_size_t::from64(path.len()) * cover_size_t::from64(width);

    if (!size.overflow()) {
        write_input<cunit_t>(path, skel, width);
        write_keys<key_t>(path, skel, width);
    }

    return size;
}

// note [generating skeleton path cover]
//
// With --skeleton switch we need to generate lots of data: strings that correspond to various paths
// in a TDFA and match given regular expression. We try to generate path cover (a set of paths that
// cover all skeleton arcs at least once). Generation must stop as soon as the size of path cover
// exceeds limit (in which case we'll only get a partial path cover).
//
// The algorithm walks graph nodes in deep-first order and assigns suffix to each node (a path from
// this node to end node). In order to calculate suffix for a given node the algorithm must know
// suffix for any child node (end nodes are assigned empty suffix at start). Suffix is only
// calculated once for each node and then reused as much times as the node is visited. This is what
// reduces search space.
//
// The algorithm calculates prefix (multipath to current node). If the current node has already been
// assigned a suffix, the algorithm immediately calculates path cover from prefix and suffix.
// Otherwise it recurses to the child nodes (updating prefix on the go).
//
// The algorithm avoids eternal loops by maintaining loop counter for each node. Loop counter is
// incremented on recursive enter and decremented on recursive return. If loop counter is greater
// than 1, current branch is abandoned and recursion returns immediately.
//
// See also note [counting skeleton edges].
//
template<typename cunit_t, typename key_t>
static void gencover(Skeleton& skel, cover_t& cover, size_t i) {
    const Node& node = skel.nodes[i];
    uint8_t& loop = cover.loops[i];
    suffix_t& suffix = cover.suffixes[i];
    path_t& prefix = cover.prefix;
    cover_size_t& size = cover.size;

    if (node.end()) {
        suffix.init = true;
    }

    if (suffix.init) {
        prefix.push_sfx(suffix);
        size = size + cover_one<cunit_t, key_t>(skel, cover);
        prefix.pop_sfx(suffix);
    } else if (loop < 2) { // unroll one iteration of the loop
        ++loop;

        Node::arcs_t::const_iterator
        arc = node.arcs.begin(),
        end = node.arcs.end();
        const suffix_t* min_sfx = nullptr;
        size_t min_idx = 0;

        // pick the shortest suffix to minimize cover size; handle all child states before setting
        // this state's suffix
        for (; arc != end && !size.overflow(); ++arc) {
            const size_t j = arc->first;

            prefix.push(j);
            gencover<cunit_t, key_t>(skel, cover, j);
            prefix.pop();

            const suffix_t& sfx = cover.suffixes[j];
            if (sfx.init && (!min_sfx || sfx.length() < min_sfx->length())) {
                min_sfx = &sfx;
                min_idx = j;
            }
        }

        if (min_sfx == nullptr) {
            // all outgoing paths loop back into this node (this can happen in cases like `[^]*`)
        } else {
            suffix = *min_sfx;
            suffix.push(min_idx);
        }

        --loop;
    }
}

template<typename cunit_t, typename key_t>
static void generate_paths_cunit_key(Skeleton& skel, cover_t& cover) {
    gencover<cunit_t, key_t>(skel, cover, 0);
    if (cover.size.overflow()) {
        skel.msg.warning(nullptr, skel.loc, false,
                         "DFA %sis too large: can only generate partial path cover",
                         incond(skel.cond).c_str());
    }
    skel.buf_data.flush<cunit_t>();
    skel.buf_keys.flush<key_t>();
}

template<typename cunit_t>
static void generate_paths_cunit(Skeleton& skel, cover_t& cover) {
    switch (skel.sizeof_key) {
    case 8:
        generate_paths_cunit_key<cunit_t, uint64_t>(skel, cover);
        break;
    case 4:
        generate_paths_cunit_key<cunit_t, uint32_t>(skel, cover);
        break;
    case 2:
        generate_paths_cunit_key<cunit_t, uint16_t>(skel, cover);
        break;
    case 1:
        generate_paths_cunit_key<cunit_t, uint8_t>(skel, cover);
        break;
    }
}

static void generate_paths(Skeleton& skel, cover_t& cover) {
    switch (skel.opts->encoding.cunit_size()) {
    case 4:
        generate_paths_cunit<uint32_t>(skel, cover);
        break;
    case 2:
        generate_paths_cunit<uint16_t>(skel, cover);
        break;
    case 1:
        generate_paths_cunit<uint8_t>(skel, cover);
        break;
    }
}

Ret emit_data(Skeleton& skel) {
    std::string fname = skel.opts->output_file;
    if (fname.empty()) {
        fname = "<stdout>";
    }

    const std::string input_name = fname + "." + skel.name + ".input";
    const std::string keys_name = std::string(fname) + "." + skel.name + ".keys";
    // For existing files `remove()`/`fopen("w")` works faster than `fopen("w")` at least on ext4.
    // Slowdown happens due to `auto_da_alloc` heuristic that forces data and metadata commit on
    // `open(O_TRUNC)` for non-empty files:
    //     https://www.kernel.org/doc/html/latest/admin-guide/ext4.html
    // Presence of `remove()` avoids it.
    remove(input_name.c_str());
    remove(keys_name.c_str());

    FILE* input = fopen(input_name.c_str(), "wb");
    if (!input) {
        RET_FAIL(error("cannot open file: %s", input_name.c_str()));
    }
    FILE* keys = fopen (keys_name.c_str(), "wb");
    if (!keys) {
        fclose(input);
        RET_FAIL(error("cannot open file: %s", keys_name.c_str()));
    }

    skel.buf_data.file = input;
    skel.buf_keys.file = keys;

    cover_t cover(skel.nodes_count);
    generate_paths(skel, cover);

    fclose(input);
    fclose(keys);
    return Ret::OK;
}

} // namespace re2c
