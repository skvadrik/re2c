#ifndef _RE2C_IR_BYTECODE_CHARSET_
#define _RE2C_IR_BYTECODE_CHARSET_

#include "src/util/c99_stdint.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

struct CharPtn
{
	uint32_t card;
	CharPtn * fix;
	CharPtn * nxt;

	FORBID_COPY (CharPtn);
};

typedef CharPtn * CharPtr;

struct CharSet
{
	CharPtn * fix;
	CharPtn * freeHead;
	CharPtn ** freeTail;
	CharPtr * rep;
	CharPtn * ptn;

	CharSet (uint32_t cunits);
	~CharSet ();

	FORBID_COPY (CharSet);
};

} // namespace re2c

#endif // _RE2C_IR_BYTECODE_CHARSET_
