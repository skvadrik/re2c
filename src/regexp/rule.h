#ifndef _RE2C_RE_RULE_
#define _RE2C_RE_RULE_

#include <stddef.h>
#include <stdint.h>
#include <set>
#include <string>

#include "src/msg/location.h"
#include "src/util/free_list.h"

namespace re2c {

// semantic action (user-defined code for rule)
struct SemAct {
    static free_list<SemAct*> flist;

    const loc_t loc;
    bool autogen;
    const std::string text;
    std::string cond;

    explicit SemAct(const loc_t& loc)
            : loc(loc), autogen(true), text(""), cond("") {
        flist.insert(this);
    }
    SemAct(const loc_t& loc, const std::string& t)
            : loc(loc), autogen(false), text(t), cond("") {
        flist.insert(this);
    }
    ~SemAct() {
        flist.erase(this);
    }
};

struct Rule {
    static const size_t NONE;

    const SemAct* semact;
    std::set<uint32_t> shadow;
    size_t ltag; // first tag
    size_t htag; // next to last tag
    size_t ttag; // trailing context
    size_t ncap; // number of POSIX captures

    Rule(): semact(nullptr), shadow(), ltag(0), htag(0), ttag(0), ncap(0) {}
    ~Rule() {}
    Rule(const Rule& r) = default;
    Rule& operator=(const Rule& r) = default;
    Rule(Rule&& r) = default;
    Rule& operator=(Rule&& r) = default;
};

} // namespace re2c

#endif // _RE2C_RE_RULE_
