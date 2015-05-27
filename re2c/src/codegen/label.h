#ifndef __LABEL__
#define __LABEL__

#include "src/util/c99_stdint.h"

namespace re2c {

class Label
{
public:
	static const uint32_t FIRST_LABEL;

private:
	uint32_t next;

public:
	Label ()
		: next (FIRST_LABEL)
	{}
	uint32_t new_label ()
	{
		return next++;
	}
	void reset ()
	{
		next = FIRST_LABEL;
	}
};

} // namespace re2c

#endif // __LABEL__
