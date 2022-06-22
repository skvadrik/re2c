#ifndef _RE2C_RE_RULE_
#define _RE2C_RE_RULE_

#include <stddef.h>
#include <stdint.h>
#include <limits>
#include <set>
#include <string>

#include "src/msg/location.h"

namespace re2c {

// semantic action (user-defined code for rule)
struct SemAct {
    loc_t loc;
    const char* text;
    const char* cond;
    bool autogen;
};

struct Rule {
    static constexpr size_t NONE = std::numeric_limits<size_t>::max();

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
