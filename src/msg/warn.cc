#include <stddef.h>
#include <stdio.h>
#include <algorithm>
#include <set>

#include "src/msg/msg.h"
#include "src/msg/warn.h"
#include "src/options/opt.h"
#include "src/regexp/rule.h"
#include "src/skeleton/skeleton.h"
#include "src/skeleton/path.h"

namespace re2c {

struct loc_t;

const char* Warn::names [TYPES] = {
#define W(kind, name, on) name,
    RE2C_WARNINGS
#undef W
};

Warn::Warn(Msg& msg): mask(), error_accuml(false), msg(msg) {
#define W(kind, name, on) mask[kind] = on ? WARNING : SILENT;
    RE2C_WARNINGS
#undef W
}

Ret Warn::check() const {
    return error_accuml ? Ret::FAIL : Ret::OK;
}

void Warn::set(type_t t, option_t o) {
    switch (o) {
    case W:
        mask[t] |= WARNING;
        break;
    case WNO:
        mask[t] &= ~WARNING;
        break;
    case WERROR:
        // unlike -Werror, -Werror-<warning> implies -W<warning>
        mask[t] |= (WARNING | ERROR);
        break;
    case WNOERROR:
        mask[t] &= ~ERROR;
        break;
    }
}

void Warn::set_all() {
    for (uint32_t i = 0; i < TYPES; ++i) {
        mask[i] |= WARNING;
    }
}

// -Werror doesn't set any warnings: it only guarantees that if a warning has been set by now or
// will be set later then it will result into error.
void Warn::set_all_error() {
    for (uint32_t i = 0; i < TYPES; ++i) {
        mask[i] |= ERROR;
    }
}

bool Warn::is_set(type_t t) const {
    return mask[t] > 0;
}

void Warn::fail(type_t t, const loc_t& loc, const char* s) const {
    if (mask[t] & WARNING) {
        // -Werror has no effect
        msg.warning(names[t], loc, false, "%s", s);
    }
}

void Warn::condition_order(const loc_t& loc) {
    if (mask[CONDITION_ORDER] & WARNING) {
        const bool e = mask[CONDITION_ORDER] & ERROR;
        error_accuml |= e;
        msg.warning (names[CONDITION_ORDER], loc, e, "condition numbers may change"
                ", use `conditions` block to generate reliable condition identifiers");
    }
}

void Warn::empty_class(const loc_t& loc) {
    if (mask[EMPTY_CHARACTER_CLASS] & WARNING) {
        const bool e = mask[EMPTY_CHARACTER_CLASS] & ERROR;
        error_accuml |= e;
        msg.warning (names[EMPTY_CHARACTER_CLASS], loc, e, "empty character class");
    }
}

void Warn::match_empty_string(const loc_t& loc, const std::string& cond) {
    if (mask[MATCH_EMPTY_STRING] & WARNING) {
        const bool e = mask[MATCH_EMPTY_STRING] & ERROR;
        error_accuml |= e;
        msg.warning(names[MATCH_EMPTY_STRING], loc, e, "rule %smatches empty string",
                incond(cond).c_str());
    }
}

void Warn::nondeterministic_tags(
        const loc_t& loc, const std::string& cond, const char* tagname, size_t nver) {
    if (mask[NONDETERMINISTIC_TAGS] & WARNING) {
        bool e = mask[NONDETERMINISTIC_TAGS] & ERROR;
        error_accuml |= e;

        msg.warning_start(loc, e);
        if (tagname == nullptr) {
            fprintf(stderr, "trailing context");
        } else {
            fprintf(stderr, "tag `%s`", tagname);
        }
        fprintf(stderr, " %shas %zu%s degree of nondeterminism",
                incond(cond).c_str(), nver, nver == 2 ? "nd" : nver == 3 ? "rd" : "th");
        msg.warning_end(names[NONDETERMINISTIC_TAGS], e);
    }
}

void Warn::swapped_range(const loc_t& loc, uint32_t l, uint32_t u) {
    if (mask[SWAPPED_RANGE] & WARNING) {
        const bool e = mask[SWAPPED_RANGE] & ERROR;
        error_accuml |= e;
        msg.warning(names[SWAPPED_RANGE], loc, e,
                "range lower bound (0x%X) is greater than upper bound (0x%X), swapping", l, u);
    }
}

void Warn::undefined_control_flow(
    const Skeleton& skel, std::vector<path_t>& paths, bool overflow) {
    if (mask[UNDEFINED_CONTROL_FLOW] & WARNING) {
        const bool e = mask[UNDEFINED_CONTROL_FLOW] & ERROR;
        error_accuml |= e;

        // report shorter patterns first
        std::sort(paths.begin(), paths.end());

        msg.warning_start(skel.loc, e);
        fprintf(stderr, "control flow %sis undefined for strings that match ",
                incond(skel.cond).c_str());
        if (paths.size() == 1) {
            fprint_default_path(stderr, skel, paths.front());
        } else {
            for (const path_t& path : paths) {
                fprintf(stderr, "\n\t");
                fprint_default_path(stderr, skel, path);
            }
            fprintf (stderr, "\n");
        }
        if (overflow) {
            fprintf(stderr, " ... and a few more");
        }
        fprintf(stderr, ", use default rule '*'");
        msg.warning_end(names[UNDEFINED_CONTROL_FLOW], e);
    }
}

void Warn::unreachable_rule(const std::string& cond, const Rule& rule) {
    if (mask[UNREACHABLE_RULES] & WARNING) {
        const bool e = mask[UNREACHABLE_RULES] & ERROR;
        error_accuml |= e;

        msg.warning_start(rule.semact->loc, e);
        fprintf(stderr, "unreachable rule %s", incond(cond).c_str());
        const size_t shadows = rule.shadow.size();
        if (shadows > 0) {
            const char* pl = shadows > 1 ? "s" : "";
            std::set<uint32_t>::const_iterator i = rule.shadow.begin();
            fprintf (stderr, "(shadowed by rule%s at line%s %u", pl, pl, *i);
            for (++i; i != rule.shadow.end(); ++i) {
                fprintf(stderr, ", %u", *i);
            }
            fprintf(stderr, ")");
        }
        msg.warning_end(names[UNREACHABLE_RULES], e);
    }
}

void Warn::useless_escape(const loc_t& loc, const uint8_t* str, const uint8_t* end) {
    if (mask[USELESS_ESCAPE] & WARNING) {
        const bool e = mask[USELESS_ESCAPE] & ERROR;
        error_accuml |= e;
        msg.warning(names[USELESS_ESCAPE], loc, e, "escape has no effect: '%.*s'",
                static_cast<int>(end - str), str);
    }
}

void Warn::sentinel_in_midrule(const loc_t& loc, const std::string& cond, uint32_t sentinel) {
    if (mask[SENTINEL_IN_MIDRULE] & WARNING) {
        const bool defined = sentinel != NOEOF;
        const bool e = defined || (mask[SENTINEL_IN_MIDRULE] & ERROR);
        error_accuml |= e;
        msg.warning(names[SENTINEL_IN_MIDRULE], loc, e,
                    "%ssentinel symbol %u occurs in the middle of the rule%s",
                    incond(cond).c_str(),
                    defined ? sentinel : 0,
                    defined ? "" : " (note: if a different sentinel symbol is used,"
                    " specify it with `re2c:sentinel` configuration)");
    }
}

void Warn::undefined_syntax_config(const loc_t& loc, const char* name) {
    if (mask[UNDEFINED_SYNTAX_CONFIG] & WARNING) {
        const bool e = mask[UNDEFINED_SYNTAX_CONFIG] & ERROR;
        error_accuml |= e;
        msg.warning(names[UNDEFINED_SYNTAX_CONFIG], loc, e,
            "syntax configuration `%s` is not defined "
            "(set it to <undefined> explicitly to silence the warning)", name);
    }
}

} // namespace re2c
