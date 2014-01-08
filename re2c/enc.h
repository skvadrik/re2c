#ifndef _enc_h
#define _enc_h

#include "basics.h"

namespace re2c {

class Enc
{
	// Supported encodings.
	//
	// UTF32_16 mode is necessary for inplace configurations like:
	//	re2c:flags:u = 1;
	//	re2c:flags:w = 1;
	// which are for some strange reason considered valid.
	// (see test 're2c/test/repeat-07.gir.re' for example)
	enum type_t
		{ ASCII    = 0x00000000u
		, EBCDIC   = 0x00000001u
		, UTF16    = 0x00000002u
		, UTF32    = 0x00000004u
		, UTF32_16 = UTF32 | UTF16 // backward compatibility
		, UTF8     = 0x00000008u
		};

	// For re2c, encoding has two properties:
	//
	// 1) Maximal number of abstract code points
	//	(symbols), that can be encoded.
	//
	// 2) Maximal number of different characters that appear
	//	in encoded text. When parsing this text, re2c reads it
	//	character-by-character. These 'characters' shouldn't
	//	be mixed up with code points (symbols). In different
	//	encodings characters have different width.
	//
	// encoding | symbols  | character width
	// ---------|----------|----------------
	// ASCII    | 0xFF     | 1 byte
	// EBCDIC   | 0xFF     | 1 byte
	// UTF16    | 0xFFFF   | 2 bytes
	// UTF32    | 0x10FFFF | 4 bytes
	// UTF8     | 0x10FFFF | 1 byte
	// -------------------------------------
	static const uint ASCII_SYMBOLS;
	static const uint ASCII_CHARS;
	static const uint EBCDIC_SYMBOLS;
	static const uint EBCDIC_CHARS;
	static const uint UTF16_SYMBOLS;
	static const uint UTF16_CHARS;
	static const uint UTF32_SYMBOLS;
	static const uint UTF32_CHARS;
	static const uint UTF8_SYMBOLS;
	static const uint UTF8_CHARS;

	static const uint BAD;

	static const uint asc2ebc[256];
	static const uint ebc2asc[256];

	uint type;

public:
	Enc()
		: type (ASCII)
	{ }

	bool operator != (const Enc & e) const { return type != e.type; }

	inline uint nSymbols() const;
	inline uint nChars() const;

	inline uint szSymbol() const;
	inline uint szChar() const;

	inline void setEBCDIC()	{ type |= EBCDIC; }
	inline void setUTF16()	{ type |= UTF16; }
	inline void setUTF32()	{ type |= UTF32; }
	inline void setUTF8()	{ type |= UTF8; }

	inline void unsetEBCDIC()	{ type &= ~EBCDIC; }
	inline void unsetUTF16()	{ type &= ~UTF16; }
	inline void unsetUTF32()	{ type &= ~UTF32; }
	inline void unsetUTF8()		{ type &= ~UTF8; }

	inline bool isEBCDIC() const	{ return type & EBCDIC; }
	inline bool isUTF16() const	{ return type & UTF16; }
	inline bool isUTF32() const	{ return type & UTF32; }
	inline bool isUTF8() const	{ return type & UTF8; }

	inline bool isBad() const;

	inline uint xlat(uint c) const;
	inline uint talx(uint c) const;
};

inline uint Enc::nSymbols() const
{
	switch (type)
	{
		case ASCII:	return ASCII_SYMBOLS;
		case EBCDIC:	return EBCDIC_SYMBOLS;
		case UTF16:	return UTF16_SYMBOLS;
		case UTF32:
		case UTF32_16:	return UTF32_SYMBOLS;
		case UTF8:	return UTF8_SYMBOLS;
		default:	return BAD;
	}
}

inline uint Enc::nChars() const
{
	switch (type)
	{
		case ASCII:	return ASCII_CHARS;
		case EBCDIC:	return EBCDIC_CHARS;
		case UTF16:	return UTF16_CHARS;
		case UTF32:
		case UTF32_16:	return UTF32_CHARS;
		case UTF8:	return UTF8_CHARS;
		default:	return BAD;
	}
}

inline uint Enc::szSymbol() const
{
	switch (type)
	{
		case ASCII:
		case EBCDIC:	return 1;
		case UTF16:	return 2;
		case UTF32:
		case UTF32_16:
		case UTF8:	return 4;
		default:	return BAD;
	}
}

inline uint Enc::szChar() const
{
	switch (type)
	{
		case ASCII:
		case EBCDIC:
		case UTF8:	return 1;
		case UTF16:	return 2;
		case UTF32:
		case UTF32_16:	return 4;
		default:	return BAD;
	}
}

// This test returns 'true' for all valid
// encoding types except UTF32_16
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
		case UTF16:
		case UTF32:
		case UTF32_16:
		case UTF8:	return c;
		default:	return BAD;
	}
}

inline uint Enc::talx(uint c) const
{
	switch (type)
	{
		case ASCII:	return c & 0xFF;
		case EBCDIC:	return ebc2asc[c & 0xFF];
		case UTF16:
		case UTF32:
		case UTF32_16:
		case UTF8:	return c;
		default:	return BAD;
	}
}

} // namespace re2c

#endif // _enc_h
