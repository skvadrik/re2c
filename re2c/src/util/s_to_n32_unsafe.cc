#include "src/util/s_to_n32_unsafe.h"

// assumes that string matches regexp [0-9]+
// returns false on overflow
bool s_to_u32_unsafe (const char * s, const char * s_end, uint32_t & number)
{
	uint64_t u = 0;
	for (; s != s_end; ++s)
	{
		u *= 10;
		u += static_cast<uint32_t> (*s) - 0x30;
		if (u >= UINT32_MAX)
		{
			return false;
		}
	}
	number = static_cast<uint32_t> (u);
	return true;
}

// assumes that string matches regexp "-"? [0-9]+
// returns false on underflow/overflow
bool s_to_i32_unsafe (const char * s, const char * s_end, int32_t & number)
{
	int64_t i = 0;
	if (*s == '-')
	{
		++s;
		for (; s != s_end; ++s)
		{
			i *= 10;
			i -= *s - 0x30;
			if (i < INT32_MIN)
			{
				return false;
			}
		}
	}
	else
	{
		for (; s != s_end; ++s)
		{
			i *= 10;
			i += *s - 0x30;
			if (i > INT32_MAX)
			{
				return false;
			}
		}
	}
	number = static_cast<int32_t> (i);
	return true;
}
