#ifndef _RE2C_COMPILE_
#define _RE2C_COMPILE_

#include "src/ast/scanner.h"
#include "src/code/output.h"
#include "src/conf/opt.h"

namespace re2c
{

class Scanner;
struct Opt;
struct Output;

void compile(Scanner &input, Output &output, Opt &opts);

} // namespace re2c

#endif // _RE2C_COMPILE_
