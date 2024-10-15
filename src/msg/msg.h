#ifndef _RE2C_MSG_MSG_
#define _RE2C_MSG_MSG_

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

#include "src/constants.h"
#include "src/msg/location.h"
#include "src/msg/warn.h"
#include "src/util/attribute.h"

namespace re2c {

class Msg {
  public:
    std::vector<std::string> filenames;
    Warn warn;
    locfmt_t locfmt;
    bool error_seen;

  public:
    inline Msg(): filenames(), warn(*this), locfmt(LOCFMT_GNU), error_seen(false) {}

    void error(const loc_t& loc, const char* fmt, ...) RE2C_ATTR((format(printf, 3, 4)));
    void verror(const loc_t& loc, const char* fmt, va_list args) RE2C_ATTR((format(printf, 3, 0)));
    void warning(const char* type, const loc_t& loc, bool error, const char* fmt, ...)
            RE2C_ATTR((format(printf, 5, 6)));

    friend class Warn;

  private:
    void print_location(const loc_t& loc) const;
    void warning_start(const loc_t& loc, bool error);
    void warning_end(const char* type, bool error);
};

void error(const char* fmt, ...) RE2C_ATTR((format(printf, 1, 2)));
void error_arg(const char* option);
Ret usage() NODISCARD;
Ret vernum() NODISCARD;
Ret version() NODISCARD;
std::string incond(const std::string& cond);

} // namespace re2c

#endif // _RE2C_MSG_MSG_

