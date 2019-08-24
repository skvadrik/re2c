#ifndef _RE2C_MSG_WARN_
#define _RE2C_MSG_WARN_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <string>
#include <vector>


namespace re2c {

struct loc_t;
class Msg;
class path_t;
struct Rule;
struct Skeleton;

#define RE2C_WARNING_TYPES \
    W (CONDITION_ORDER,          "condition-order"), \
    W (EMPTY_CHARACTER_CLASS,    "empty-character-class"), \
    W (MATCH_EMPTY_STRING,       "match-empty-string"), \
    W (NONDETERMINISTIC_TAGS,    "nondeterministic-tags"), \
    W (SWAPPED_RANGE,            "swapped-range"), \
    W (UNDEFINED_CONTROL_FLOW,   "undefined-control-flow"), \
    W (UNREACHABLE_RULES,        "unreachable-rules"), \
    W (USELESS_ESCAPE,           "useless-escape"), \
    W (SENTINEL_IN_MIDRULE,      "sentinel-in-midrule"),

class Warn
{
public:
    enum type_t
    {
#define W(x, y) x
        RE2C_WARNING_TYPES
#undef W
        TYPES // count
    };
    enum option_t
    {
        W,
        WNO,
        WERROR,
        WNOERROR
    };

private:
    static const uint32_t SILENT;
    static const uint32_t WARNING;
    static const uint32_t ERROR;
    static const char * names [TYPES];
    uint32_t mask[TYPES];
    bool error_accuml;
    Msg &msg;

public:
    explicit Warn (Msg &msg);
    bool error () const;
    void set (type_t t, option_t o);
    void set_all ();
    void set_all_error ();
    bool is_set(type_t t) const;
    void fail(type_t t, const loc_t &loc, const char *s) const;

    void condition_order(const loc_t &loc);
    void empty_class(const loc_t &loc);
    void match_empty_string(const loc_t &loc, const std::string &cond);
    void nondeterministic_tags(const loc_t &loc, const std::string &cond, const std::string *tagname, size_t nver);
    void swapped_range(const loc_t &loc, uint32_t l, uint32_t u);
    void undefined_control_flow(const Skeleton &skel, std::vector<path_t> & paths, bool overflow);
    void unreachable_rule(const std::string & cond, const Rule &rule);
    void useless_escape(const loc_t &loc, const char *str, const char *end);
    void sentinel_in_midrule(const loc_t &loc, const std::string &cond, uint32_t sentinel);
};

} // namespace re2c

#endif // _RE2C_MSG_WARN_
