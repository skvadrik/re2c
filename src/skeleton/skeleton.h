#ifndef _RE2C_SKELETON_SKELETON_
#define _RE2C_SKELETON_SKELETON_

#include "src/util/c99_stdint.h"
#include <stdio.h>
#include <algorithm>
#include <limits>
#include <map>
#include <set>
#include <string>
#include <valarray>
#include <vector>

#include "src/msg/location.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/util/forbid_copy.h"
#include "src/util/local_increment.h"
#include "src/util/wrap_iter.h"


namespace re2c {

class Output;
class path_t;
struct DFA;
struct dfa_state_t;
struct dfa_t;
class Msg;
class bitmaps_t;
struct opt_t;
struct tcmd_t;

typedef local_increment_t<uint8_t> local_inc;

struct Node
{
    struct range_t {
        uint32_t lower;
        uint32_t upper;
        const tcmd_t *cmd;

        range_t(): lower(0), upper(0), cmd(NULL) {}
        range_t(uint32_t l, uint32_t u, const tcmd_t *c)
            : lower(l), upper(u), cmd(c) {}
    };

    typedef std::vector<range_t> arc_t;
    typedef std::map<size_t, arc_t> arcs_t;
    typedef arc_t::const_iterator citer_t;
    typedef wrap_citer_t<arc_t> wciter_t;

    arcs_t arcs;
    size_t rule;
    const tcmd_t *cmd;
    const tcmd_t *stacmd;

    Node();
    void init(const dfa_state_t *s,
        const std::vector<uint32_t> &charset, size_t nil);
    bool end() const;

    FORBID_COPY(Node);
};

struct Skeleton
{
    static const size_t DEFTAG;

    const opt_t *opts;
    const std::string name;
    const std::string cond;
    const loc_t loc;
    Msg &msg;

    const size_t nodes_count;
    Node *nodes;
    const tcmd_t *cmd0;

    size_t sizeof_key;
    size_t defrule;
    size_t ntagver;
    const std::vector<uint32_t> &charset;
    const std::valarray<Rule> &rules;
    const std::vector<Tag> &tags;
    const tagver_t *finvers;

    Skeleton(const dfa_t &dfa, const opt_t *op, size_t def
        , const std::string &dfa_name, const std::string &dfa_cond
        , const loc_t &loc, Msg &msg);
    ~Skeleton ();
    FORBID_COPY(Skeleton);
};

template<typename key_t> key_t rule2key(size_t r, size_t def)
{
    if (r == Rule::NONE) {
        return std::numeric_limits<key_t>::max();
    } else if (r == def) {
        key_t k = std::numeric_limits<key_t>::max();
        return --k;
    } else {
        return static_cast<key_t>(r);
    }
}

uint64_t rule2key(size_t rule, size_t key, size_t def);
uint32_t maxpath(const Skeleton &skel);
void warn_undefined_control_flow(const Skeleton &skel);
void fprint_default_path(FILE *f, const Skeleton &skel, const path_t &p);
void emit_data(const Skeleton &skel);
void emit_prolog(Output & o);
void emit_start(Output &o, size_t maxfill, size_t maxnmatch, const std::string &name,
    size_t sizeof_key, size_t def, bool backup, bool accept, bool oldstyle_ctxmarker,
    const std::set<std::string> &stagnames, const std::set<std::string> &stagvars,
    const std::set<std::string> &mtagnames, const std::set<std::string> &mtagvars,
    bitmaps_t &bitmaps);
void emit_end(Output &o, const std::string &name, bool backup, bool oldstyle_ctxmarker,
    const std::set<std::string> &mtagnames);
void emit_epilog(Output &o, const std::set<std::string> &names);
void emit_action(Output &o, uint32_t ind, const DFA &dfa, size_t rid);

} // namespace re2c

#endif // _RE2C_SKELETON_SKELETON_
