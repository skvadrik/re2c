#ifndef _re2c_utf8_h
#define _re2c_utf8_h

#include "basics.h"

namespace re2c {

class utf8
{
public:
	typedef uint rune;

	enum	{ MAX_RUNE_LENGTH = 4 /* maximum characters per rune */

		, ERROR = 0xFFFD /* decoding error */

		/* maximal runes for each rune length */
		, MAX_1BYTE_RUNE = 0x7F
		, MAX_2BYTE_RUNE = 0x7FF
		, MAX_3BYTE_RUNE = 0xFFFF
		, MAX_4BYTE_RUNE = 0x10FFFF
		, MAX_RUNE       = MAX_4BYTE_RUNE

		, PREFIX_1BYTE = 0    /* 0000 0000 */
		, INFIX        = 0x80 /* 1000 0000 */
		, PREFIX_2BYTE = 0xC0 /* 1100 0000 */
		, PREFIX_3BYTE = 0xE0 /* 1110 0000 */
		, PREFIX_4BYTE = 0xF0 /* 1111 0000 */

		, SHIFT = 6
		, MASK = 0x3F /* 0011 1111 */
		};

	/* UTF-8 bytestring for given Unicode rune */
	static uint rune_to_bytes(uchar * s, rune r);

	/* length of UTF-8 bytestring for given Unicode rune */
	static uint rune_length(rune r);

	/* maximal Unicode rune with given length of UTF-8 bytestring */
	static rune max_rune(uint i);
};

}  // namespace re2c

#endif // _re2c_utf8_h
