#ifndef _RE2C_UTIL_FILE_UTILS_
#define _RE2C_UTIL_FILE_UTILS_

#include <stdio.h>
#include <string>

namespace re2c {

FILE* temp_file(std::string& fname);
bool overwrite_file(const char* srcname, const char* dstname);
void get_dir(std::string& path);

} // namespace re2c

#endif // _RE2C_UTIL_FILE_UTILS_
