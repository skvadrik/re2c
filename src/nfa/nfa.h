#ifndef _RE2C_NFA_NFA_
#define _RE2C_NFA_NFA_

#include <stddef.h>
#include <stdint.h>
#include <vector>

#include "src/regexp/re.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/util/forbid_copy.h"

namespace re2c {

struct clos_t;

// Passes of Goldberg-Radzik shortest path algorithm.
enum class GorPass: uint32_t {
    NOPASS = 0u,
    TOPSORT = 1u,
    LINEAR = 2u
};

static constexpr uint32_t NOCLOS = ~0u;

struct nfa_state_t {
    enum class Kind: uint32_t {ALT, RAN, TAG, FIN} kind;
    union {
        struct {
            nfa_state_t* out1;
            nfa_state_t* out2;
        } alt;
        struct {
            nfa_state_t* out;
            const Range* ran;
        } ran;
        struct {
            nfa_state_t* out;
            tag_info_t info;
        } tag;
    };
    size_t rule;

    // stuff needed for closure algorithms (GOR1 and GTOP)
    uint32_t clos;
    GorPass status  : 2;  // values 0, 1, 2
    uint32_t arcidx : 2;  // maximum out-dergee is 2
    uint32_t active : 1;  // boolean
    uint32_t indeg  : 27; // the rest; we are unlikely to have more than 2^27 states
    uint32_t topord;      // state index in fake topological ordering

    void init(size_t r) {
        rule = r;
        clos = NOCLOS;
        status = GorPass::NOPASS;
        arcidx = 0;
        active = 0;
        indeg = 0;
        topord = 0;
    }

    void make_alt(size_t r, nfa_state_t* s1, nfa_state_t* s2) {
        kind = Kind::ALT;
        alt.out1 = s1;
        alt.out2 = s2;
        init(r);
    }

    void make_ran(size_t r, nfa_state_t* s, const Range* p) {
        kind = Kind::RAN;
        ran.out = s;
        ran.ran = p;
        init(r);
    }

    void make_tag(size_t r, nfa_state_t* s, tag_info_t info) {
        kind = Kind::TAG;
        tag.out = s;
        tag.info = info;
        init(r);
    }

    void make_fin(size_t r) {
        kind = Kind::FIN;
        init(r);
    }
};

struct nfa_t {
    size_t max_size;
    size_t size;
    uint32_t ncores;

    nfa_state_t* states;
    nfa_state_t* root;

    std::vector<uint32_t> charset;
    std::vector<Rule> rules;
    std::vector<Tag> tags;

    nfa_t(RESpec&& spec, size_t max_size);
    ~nfa_t();

    FORBID_COPY(nfa_t);
};

static constexpr uint32_t NONCORE = ~0u;

void compute_size_and_depth(const std::vector<RE*>& res, size_t* psize, size_t* pdepth);

} // namespace re2c

#endif // _RE2C_NFA_NFA_
