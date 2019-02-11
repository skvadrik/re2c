#ifndef _RE2C_CONF_MSG_
#define _RE2C_CONF_MSG_

#include "src/util/c99_stdint.h"
#include <string>

#include "src/util/attribute.h"

namespace re2c {

void error(const char *fmt, ...) RE2C_GXX_ATTRIBUTE ((format (printf, 1, 2)));
void fatal(const char *fmt, ...) RE2C_GXX_ATTRIBUTE ((format (printf, 1, 2), noreturn));
void fatal_l(const std::string &fname, uint32_t line, const char *fmt, ...) RE2C_GXX_ATTRIBUTE ((format (printf, 3, 4), noreturn));
void fatal_lc(const std::string &fname, uint32_t line, uint32_t column, const char *fmt, ...) RE2C_GXX_ATTRIBUTE ((format (printf, 4, 5), noreturn));
void error_arg(const char *option);
void warning_start(const std::string &fname, uint32_t line, bool error);
void warning_start_lc(const std::string &fname, uint32_t line, uint32_t coln, bool error);
void warning_end(const char *type, bool error);
void warning(const char *type, const std::string &fname, uint32_t line, bool error, const char *fmt, ...) RE2C_GXX_ATTRIBUTE ((format (printf, 5, 6)));
void warning_lc(const char *type, const std::string &fname, uint32_t line, uint32_t col, bool error, const char *fmt, ...) RE2C_GXX_ATTRIBUTE ((format (printf, 6, 7)));
void usage ();
void vernum ();
void version ();
std::string incond (const std::string & cond);

} // namespace re2c

#endif // _RE2C_CONF_MSG_
