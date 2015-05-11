/* $Id$ */
#ifndef _ins_h
#define _ins_h

#include "src/util/c99_stdint.h"

namespace re2c
{

typedef uint32_t Char;

const uint32_t CHAR = 0;
const uint32_t GOTO = 1;
const uint32_t FORK = 2;
const uint32_t TERM = 3;
const uint32_t CTXT = 4;

union Ins {

	struct
	{
		uint8_t	tag;
		uint8_t	marked;
		void	*link;
	}

	i;

	struct
	{
		uint32_t	value;
		uint32_t	bump;
		void		*link;
	}

	c;
};

inline bool isMarked(Ins *i)
{
	return i->i.marked != 0;
}

inline void mark(Ins *i)
{
	i->i.marked = true;
}

inline void unmark(Ins *i)
{
	i->i.marked = false;
}

} // end namespace re2c

#endif
