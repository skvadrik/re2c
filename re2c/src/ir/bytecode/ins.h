#ifndef _RE2C_IR_BYTECODE_INS_
#define _RE2C_IR_BYTECODE_INS_

#include <iosfwd>

#include "src/util/c99_stdint.h"

namespace re2c
{

static const uint32_t CHAR = 0;
static const uint32_t GOTO = 1;
static const uint32_t FORK = 2;
static const uint32_t TERM = 3;
static const uint32_t CTXT = 4;

union Ins
{
	struct
	{
		uint8_t tag;
		uint8_t marked;
		void * link;
	} i;
	struct
	{
		uint32_t value;
		uint32_t bump;
		void * link;
	} c;
};

inline bool isMarked (Ins * i)
{
	return i->i.marked != 0;
}

inline void mark (Ins * i)
{
	i->i.marked = true;
}

inline void unmark (Ins * i)
{
	i->i.marked = false;
}

const Ins * showIns (std::ostream & o, const Ins & i, const Ins & base);

} // namespace re2c

#endif // _RE2C_IR_BYTECODE_INS_
