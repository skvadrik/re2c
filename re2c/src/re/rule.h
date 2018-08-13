#ifndef _RE2C_RE_RULE_
#define _RE2C_RE_RULE_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <set>
#include <string>

#include "src/re/tag.h"
#include "src/util/free_list.h"

namespace re2c
{

struct Code
{
    static free_list<Code*> flist;

    std::string fname;
    uint32_t fline;
    bool autogen;
    const std::string text;
    std::string cond;

    Code(const std::string &file, uint32_t line)
        : fname(file)
        , fline(line)
        , autogen(true)
        , text("")
        , cond("")
    {
        flist.insert(this);
    }
    Code(const std::string &file, uint32_t line, const char *s, size_t slen)
        : fname(file)
        , fline(line)
        , autogen(false)
        , text(s, slen)
        , cond("")
    {
        flist.insert(this);
    }
    ~Code()
    {
        flist.erase(this);
    }
};

struct Rule
{
    static const size_t NONE;

    const Code *code;
    std::set<uint32_t> shadow;

    // tags
    size_t ltag; // first
    size_t htag; // next to last
    size_t ttag; // trailing context

    size_t ncap; // number of POSIX captures

    Rule(): code(NULL), shadow(),
        ltag(0), htag(0), ttag(0), ncap(0) {}

    // copy ctor and assignment are required for containers on macOS
    Rule(const Rule &r)
        : code(r.code)
        , shadow(r.shadow)
        , ltag(r.ltag)
        , htag(r.htag)
        , ttag(r.ttag)
        , ncap(r.ncap)
    {}
    Rule& operator= (const Rule &r)
    {
        code = r.code;
        shadow = r.shadow;
        ltag = r.ltag;
        htag = r.htag;
        ttag = r.ttag;
        ncap = r.ncap;
        return *this;
    }
};

} // namespace re2c

#endif // _RE2C_RE_RULE_
