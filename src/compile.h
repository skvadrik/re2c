#ifndef _RE2C_COMPILE_
#define _RE2C_COMPILE_

#include "src/constants.h"
#include "src/util/attribute.h"

namespace re2c {

class Scanner;
struct Opt;
struct Output;

Ret compile(Scanner& input, Output& output, Opt& opts) NODISCARD;

} // namespace re2c

#endif // _RE2C_COMPILE_
