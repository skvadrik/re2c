#ifndef _RE2C_MSG_WARN_
#define _RE2C_MSG_WARN_

#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

#include "src/constants.h"
#include "src/util/attribute.h"

namespace re2c {

struct loc_t;
class Msg;
class path_t;
struct Rule;
struct Skeleton;

#define RE2C_WARNINGS \
    W(UNDEFINED_CONTROL_FLOW, "undefined-control-flow", true) \
    W(UNDEFINED_SYNTAX_CONFIG, "undefined-syntax-config", true) \
    W(SENTINEL_IN_MIDRULE, "sentinel-in-midrule", true) \
    W(UNREACHABLE_RULES, "unreachable-rules", true) \
    W(USELESS_ESCAPE, "useless-escape", true) \
    W(SWAPPED_RANGE, "swapped-range", true) \
    W(CONDITION_ORDER, "condition-order", true) \
    W(EMPTY_CHARACTER_CLASS, "empty-character-class", false) \
    W(MATCH_EMPTY_STRING, "match-empty-string", false) \
    W(NONDETERMINISTIC_TAGS, "nondeterministic-tags", false) \
    /* end */

class Warn {
  public:
    enum type_t {
#define W(kind, name, on) kind,
        RE2C_WARNINGS
#undef W
        TYPES // count
    };
    enum option_t {
        W,
        WNO,
        WERROR,
        WNOERROR
    };

  private:
    enum : uint32_t {
        SILENT  = 0,
        WARNING = 1u << 0,
        ERROR   = 1u << 1
    };

    static const char* names[TYPES];

    uint32_t mask[TYPES];
    bool error_accuml;
    Msg& msg;

  public:
    explicit Warn(Msg& msg);
    Ret check() const NODISCARD;
    void set(type_t t, option_t o);
    void set_all();
    void set_all_error();
    bool is_set(type_t t) const;
    void fail(type_t t, const loc_t& loc, const char* s) const;

    void condition_order(const loc_t& loc);
    void empty_class(const loc_t& loc);
    void match_empty_string(const loc_t& loc, const std::string& cond);
    void nondeterministic_tags(
            const loc_t& loc, const std::string& cond, const char* tagname, size_t nver);
    void swapped_range(const loc_t& loc, uint32_t l, uint32_t u);
    void undefined_control_flow(const Skeleton& skel, std::vector<path_t>& paths, bool overflow);
    void unreachable_rule(const std::string& cond, const Rule& rule);
    void useless_escape(const loc_t& loc, const uint8_t* str, const uint8_t* end);
    void sentinel_in_midrule(const loc_t& loc, const std::string& cond, uint32_t sentinel);
    void undefined_syntax_config(const loc_t& loc, const char* name);
};

} // namespace re2c

#endif // _RE2C_MSG_WARN_
