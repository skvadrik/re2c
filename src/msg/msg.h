#ifndef _RE2C_MSG_MSG_
#define _RE2C_MSG_MSG_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <string>
#include <vector>

#include "src/msg/location.h"
#include "src/msg/warn.h"
#include "src/util/attribute.h"


namespace re2c {

class Msg
{
public:
    std::vector<std::string> filenames;
    Warn warn;
    locfmt_t locfmt;

public:
    inline Msg(): filenames(), warn(*this), locfmt(LOCFMT_GNU) {}

    size_t register_filename(const std::string &filename);
    void fatal(const loc_t &loc, const char *fmt, ...) RE2C_ATTR((format (printf, 3, 4), noreturn));
    void warning(const char *type, const loc_t &loc, bool error, const char *fmt, ...) RE2C_ATTR((format (printf, 5, 6)));

    friend class Warn;

private:
    void print_location(const loc_t &loc) const;
    void warning_start(const loc_t &loc, bool error);
    void warning_end(const char *type, bool error);
};

void error(const char *fmt, ...) RE2C_ATTR((format (printf, 1, 2)));
void fatal(const char *fmt, ...) RE2C_ATTR((format (printf, 1, 2), noreturn));
void error_arg(const char *option);
void usage ();
void vernum ();
void version ();
std::string incond (const std::string & cond);

} // namespace re2c

#endif // _RE2C_MSG_MSG_

