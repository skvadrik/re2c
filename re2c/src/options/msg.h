#ifndef _RE2C_CONF_MSG_
#define _RE2C_CONF_MSG_

#include "src/util/c99_stdint.h"
#include <string>

#include "src/msg/location.h"
#include "src/util/attribute.h"

namespace re2c {

void error(const char *fmt, ...) RE2C_GXX_ATTRIBUTE ((format (printf, 1, 2)));
void fatal(const char *fmt, ...) RE2C_GXX_ATTRIBUTE ((format (printf, 1, 2), noreturn));
void fatal(const loc_t &loc, const char *fmt, ...) RE2C_GXX_ATTRIBUTE ((format (printf, 2, 3), noreturn));
void error_arg(const char *option);
void warning_start(const loc_t &loc, bool error);
void warning_end(const char *type, bool error);
void warning(const char *type, const loc_t &loc, bool error, const char *fmt, ...) RE2C_GXX_ATTRIBUTE ((format (printf, 4, 5)));
void usage ();
void vernum ();
void version ();
std::string incond (const std::string & cond);

} // namespace re2c

#endif // _RE2C_CONF_MSG_
