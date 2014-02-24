#ifndef _re2c_utf16_h
#define _re2c_utf16_h

#include "basics.h"

namespace re2c {

class utf16
{
public:
	typedef uint rune;

	static const uint MAX_1WORD_RUNE;
	static const uint MIN_LEAD_SURR;
	static const uint MIN_TRAIL_SURR;
	static const uint MAX_TRAIL_SURR;

	/* leading surrogate of UTF-16 symbol */
	static inline ushort lead_surr(rune r);

	/* trailing surrogate of UTF-16 symbol */
	static inline ushort trail_surr(rune r);
};

inline ushort utf16::lead_surr(rune r)
{
	return ((r - 0x10000) / 0x400) + MIN_LEAD_SURR;
}

inline ushort utf16::trail_surr(rune r)
{
	return ((r - 0x10000) % 0x400) + MIN_TRAIL_SURR;
}

}  // namespace re2c

#endif // _re2c_utf16_h
