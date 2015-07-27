#ifndef _RE2C_CONF_MSG_
#define _RE2C_CONF_MSG_

#include "src/util/attribute.h"
#include "src/util/c99_stdint.h"

namespace re2c {

void error (const char * fmt, ...) RE2C_GXX_ATTRIBUTE ((format (printf, 1, 2)));
void error_encoding ();
void warning (const char * type, uint32_t line, const char * fmt, ...) RE2C_GXX_ATTRIBUTE ((format (printf, 3, 4)));
void usage ();
void vernum ();
void version ();

} // namespace re2c

#endif // _RE2C_CONF_MSG_
