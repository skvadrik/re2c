#ifndef _enc_h
#define _enc_h

#include "basics.h"
#include "range.h"

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
public:
	// Supported encodings.
	enum type_t
		{ ASCII
		, EBCDIC
		, UCS2
		, UTF16
		, UTF32
		, UTF8
		};

	// What to do with invalid code points
	enum policy_t
		{ POLICY_FAIL
		, POLICY_SUBSTITUTE
		, POLICY_IGNORE
		};

private:
	static const uint asc2ebc[256];
	static const uint ebc2asc[256];
	static const uint SURR_MIN;
	static const uint SURR_MAX;
	static const uint UNICODE_ERROR;

	type_t type;
	policy_t policy;

public:
	Enc()
		: type (ASCII)
		, policy (POLICY_IGNORE)
	{ }

	bool operator != (const Enc & e) const { return type != e.type; }

	inline uint nCodePoints() const;
	inline uint nCodeUnits() const;
	inline uint szCodePoint() const;
	inline uint szCodeUnit() const;

	inline bool set(type_t t);
	inline void unset(type_t);
	inline bool is(type_t) const;

	inline void setPolicy(policy_t t);

	bool encode(uint & c) const;
	uint decodeUnsafe(uint c) const;
	Range * encodeRange(uint l, uint h) const;
	Range * fullRange() const;
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
	}
	return ~0; // to silence gcc warning
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
	}
	return ~0; // to silence gcc warning
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
	}
	return ~0; // to silence gcc warning
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
	}
	return ~0; // to silence gcc warning
}

inline bool Enc::set(type_t t)
{
	if (type == t)
		return true;
	else if (type != ASCII)
		return false;
	else
	{
		type = t;
		return true;
	}
}

inline void Enc::unset(type_t t)
{
	if (type == t)
		type = ASCII;
}

inline bool Enc::is(type_t t) const
{
	return type == t;
}

inline void Enc::setPolicy(policy_t t)
{
	policy = t;
}

} // namespace re2c

#endif // _enc_h
