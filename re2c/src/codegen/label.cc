#include <ostream>

#include "src/codegen/label.h"

namespace re2c {

const label_t label_counter_t::FIRST (0);

std::ostream & operator << (std::ostream & o, label_t l)
{
	o << l.value;
	return o;
}

bool operator < (const label_t & l1, const label_t & l2)
{
	return l1.value < l2.value;
}

bool operator == (const label_t & l1, const label_t & l2)
{
	return l1.value == l2.value;
}

uint32_t width (label_t l)
{
	uint32_t digits = 0;
	while (l.value /= 10) ++digits;
	return digits;
}

} // namespace re2c
