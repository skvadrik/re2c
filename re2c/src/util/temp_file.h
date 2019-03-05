#ifndef _RE2C_UTIL_TEMP_FILE_
#define _RE2C_UTIL_TEMP_FILE_

#include <stdio.h>
#include <string>


namespace re2c {

FILE *temp_file(std::string &fname);

} // namespace re2c

#endif // _RE2C_UTIL_TEMP_FILE_
