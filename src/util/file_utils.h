#ifndef _RE2C_UTIL_FILE_UTILS_
#define _RE2C_UTIL_FILE_UTILS_

#include <string>


namespace re2c {

void get_dir(std::string &path);
std::string escape_backslashes(const std::string &str);

} // namespace re2c

#endif // _RE2C_UTIL_FILE_UTILS_
