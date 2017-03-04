#ifndef _RE2C_COMPILE_
#define _RE2C_COMPILE_

#include "src/ast/parser.h"

namespace re2c
{

struct Output;

smart_ptr<DFA> compile(const spec_t &spec, Output &output);

} // namespace re2c

#endif // _RE2C_COMPILE_
