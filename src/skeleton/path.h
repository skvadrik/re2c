#ifndef _RE2C_SKELETON_PATH_
#define _RE2C_SKELETON_PATH_

#include <stdint.h>
#include <vector>

#include "src/skeleton/skeleton.h"
#include "src/util/check.h"

namespace re2c {

struct suffix_t {
    bool init;

  private:
    std::vector<size_t> arcs;

  public:

    suffix_t(): init(false), arcs() {}
    size_t length() const { return arcs.size (); }
    void push(size_t i) { arcs.push_back(i); }
    friend class path_t;
};

class path_t {
    std::vector<size_t> arcs;

  public:
    explicit path_t(size_t i) : arcs() {
        arcs.push_back(i);
    }
    size_t len() const {
        return arcs.size() - 1;
    }
    const Node& node(const Skeleton& skel, size_t i) const {
        return skel.nodes[arcs[i]];
    }
    const Node::range_t* arc(const Skeleton& skel, size_t i) const {
        return skel.nodes[arcs[i]].arcs.find(arcs[i + 1])->second;
    }
    void clear() {
        DCHECK(!arcs.empty());
        arcs.resize(1);
    }
    void push(size_t n) {
        arcs.push_back(n);
    }
    void pop() {
        arcs.pop_back();
    }
    void push_sfx(const suffix_t& suffix) {
        arcs.insert(arcs.end(), suffix.arcs.rbegin(), suffix.arcs.rend());
    }
    void pop_sfx(const suffix_t& suffix) {
        arcs.resize(arcs.size() - suffix.arcs.size());
    }
    bool operator<(const path_t& p) const {
        const size_t
        s1 = arcs.size(),
        s2 = p.arcs.size();
        return (s1 == s2 && arcs < p.arcs) || s1 < s2;
    }
};

} // namespace re2c

#endif // _RE2C_SKELETON_PATH_
