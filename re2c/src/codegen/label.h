#ifndef __LABEL__
#define __LABEL__

#include <iosfwd>

#include "src/util/c99_stdint.h"

namespace re2c {

class label_t
{
	uint32_t value;
	explicit label_t (uint32_t v)
		: value (v)
	{}
	friend class label_counter_t;
	friend std::ostream & operator << (std::ostream & o, label_t l);
	friend bool operator < (const label_t & l1, const label_t & l2);
	friend bool operator == (const label_t & l1, const label_t & l2);
	friend uint32_t width (label_t l);
};

class label_counter_t
{
public:
	static const label_t FIRST;

private:
	label_t label;

public:
	label_counter_t ()
		: label (FIRST)
	{}
	label_t next ()
	{
		label_t l = label;
		++label.value;
		return l;
	}
	void reset ()
	{
		label = FIRST;
	}
};

} // namespace re2c

#endif // __LABEL__
