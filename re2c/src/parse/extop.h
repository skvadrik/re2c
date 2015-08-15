#ifndef _RE2C_PARSE_EXTOP_
#define _RE2C_PARSE_EXTOP_

#include "src/util/c99_stdint.h"

namespace re2c
{

struct ExtOp
{
	int32_t minsize;
	int32_t maxsize;
};

} // end namespace re2c

#endif // _RE2C_PARSE_EXTOP_
