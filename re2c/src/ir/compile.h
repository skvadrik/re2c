#ifndef _RE2C_IR_COMPILE_
#define _RE2C_IR_COMPILE_

#include "src/util/c99_stdint.h"
#include <string>

#include "src/parse/parser.h"
#include "src/util/smart_ptr.h"

namespace re2c
{

class DFA;
struct Output;

smart_ptr<DFA> compile(const Spec &spec, Output &output,
	const std::string &cond, const std::string &setup);

} // namespace re2c

#endif // _RE2C_IR_COMPILE_
