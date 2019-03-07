#ifndef _RE2C_COMPILE_
#define _RE2C_COMPILE_

#include "src/parse/scanner.h"
#include "src/codegen/output.h"
#include "src/options/opt.h"

namespace re2c
{

class Scanner;
struct Opt;
struct Output;

void compile(Scanner &input, Output &output, Opt &opts);

} // namespace re2c

#endif // _RE2C_COMPILE_
