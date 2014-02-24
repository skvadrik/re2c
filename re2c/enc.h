#ifndef _enc_h
#define _enc_h

#include "basics.h"

namespace re2c {

// Each encoding defines two concepts:
//
// 1) Code point -- abstract number, which represents single encoding symbol.
//	E.g., Unicode defines 0x10FFFF code points, so each Unicode encoding
//	must be capable of representing 0x10FFFF code points.
//
// 2) Code unit -- the smallest unit of memory, which is used in the encoded
//	text. One or more code units can be needed to represent a single code
//	point, depending on the encoding. For each encoding, all code points
//	either are represented with equal number of code units (fixed-length
//	encodings), or with variable number of code units (variable-length
//	encodings).
//
// encoding | code point number | code point size       | code unit number | code unit size
// ---------|-------------------|-----------------------|------------------|----------------
// ASCII    | 0xFF              | fixed,        1 byte  | 0xFF             | 1 byte
// EBCDIC   | 0xFF              | fixed,        1 byte  | 0xFF             | 1 byte
// UCS2     | 0xFFFF            | fixed,        2 bytes | 0xFFFF           | 2 bytes
// UTF16    | 0x10FFFF          | variable, 2 - 4 bytes | 0xFFFF           | 2 bytes
// UTF32    | 0x10FFFF          | fixed,        4 bytes | 0x10FFFF         | 4 bytes
// UTF8     | 0x10FFFF          | variable, 1 - 4 bytes | 0xFF             | 1 byte
// -----------------------------------------------------------------------------------------

class Enc
{
	// Supported encodings.
	enum type_t
		{ ASCII  = 0x00000000u
		, EBCDIC = 0x00000001u
		, UCS2   = 0x00000002u
		, UTF16  = 0x00000004u
		, UTF32  = 0x00000008u
		, UTF8   = 0x00000010u
		};

	static const uint ERROR;
	static const uint asc2ebc[256];
	static const uint ebc2asc[256];

	uint type;

public:
	Enc()
		: type (ASCII)
	{ }

	bool operator != (const Enc & e) const { return type != e.type; }

	inline uint nCodePoints() const;
	inline uint nCodeUnits() const;
	inline uint szCodePoint() const;
	inline uint szCodeUnit() const;

	inline void setEBCDIC()	{ type |= EBCDIC; }
	inline void setUCS2()	{ type |= UCS2; }
	inline void setUTF16()	{ type |= UTF16; }
	inline void setUTF32()	{ type |= UTF32; }
	inline void setUTF8()	{ type |= UTF8; }

	inline void unsetEBCDIC()	{ type &= ~EBCDIC; }
	inline void unsetUCS2()		{ type &= ~UCS2; }
	inline void unsetUTF16()	{ type &= ~UTF16; }
	inline void unsetUTF32()	{ type &= ~UTF32; }
	inline void unsetUTF8()		{ type &= ~UTF8; }

	inline bool isEBCDIC() const	{ return type & EBCDIC; }
	inline bool isUCS2() const	{ return type & UCS2; }
	inline bool isUTF16() const	{ return type & UTF16; }
	inline bool isUTF32() const	{ return type & UTF32; }
	inline bool isUTF8() const	{ return type & UTF8; }

	inline bool isBad() const;

	inline uint xlat(uint c) const;
	inline uint talx(uint c) const;
};

inline uint Enc::nCodePoints() const
{
	switch (type)
	{
		case ASCII:
		case EBCDIC:	return 0x100;
		case UCS2:	return 0x10000;
		case UTF16:
		case UTF32:
		case UTF8:	return 0x110000;
		default:	return ERROR;
	}
}

inline uint Enc::nCodeUnits() const
{
	switch (type)
	{
		case ASCII:
		case EBCDIC:
		case UTF8:	return 0x100;
		case UCS2:
		case UTF16:	return 0x10000;
		case UTF32:	return 0x110000;
		default:	return ERROR;
	}
}

// returns *maximal* code point size for encoding
inline uint Enc::szCodePoint() const
{
	switch (type)
	{
		case ASCII:
		case EBCDIC:	return 1;
		case UCS2:	return 2;
		case UTF16:
		case UTF32:
		case UTF8:	return 4;
		default:	return ERROR;
	}
}

inline uint Enc::szCodeUnit() const
{
	switch (type)
	{
		case ASCII:
		case EBCDIC:
		case UTF8:	return 1;
		case UCS2:
		case UTF16:	return 2;
		case UTF32:	return 4;
		default:	return ERROR;
	}
}

// This test returns 'true' for all valid encoding types
inline bool Enc::isBad() const
{
	// test if 'type' is a power of 2
	// notice: ASCII mask is 0 => it's ok if either
	// 1) only ASCII is set
	// 2) both ASCII and some other encoding is set
	return (type & (type - 1)) != 0;
}

inline uint Enc::xlat(uint c) const
{
	switch (type)
	{
		case ASCII:	return c & 0xFF;
		case EBCDIC:	return asc2ebc[c & 0xFF];
		case UCS2:
		case UTF16:
		case UTF32:
		case UTF8:	return c;
		default:	return ERROR;
	}
}

inline uint Enc::talx(uint c) const
{
	switch (type)
	{
		case ASCII:	return c & 0xFF;
		case EBCDIC:	return ebc2asc[c & 0xFF];
		case UCS2:
		case UTF16:
		case UTF32:
		case UTF8:	return c;
		default:	return ERROR;
	}
}

} // namespace re2c

#endif // _enc_h
