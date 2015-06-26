#include <iostream>

#include "src/codegen/print.h"
#include "src/globals.h"

namespace re2c
{

char octCh(uint32_t c)
{
	return '0' + c % 8;
}

char hexCh(uint32_t c)
{
	static const char * sHex = "0123456789ABCDEF";
	return sHex[c & 0x0F];
}

void prtChOrHex(std::ostream& o, uint32_t c)
{
	if (!encoding.is(Enc::EBCDIC) && (c < 256u) && (isprint(c) || isspace(c)))
	{
		o << '\'';
		prtCh(o, c);
		o << '\'';
	}
	else
	{
		prtHex(o, c);
	}
}

void prtHex(std::ostream& o, uint32_t c)
{
	int oc = (int)(c);

	if (encoding.szCodeUnit() == 4)
	{
		o << "0x"
		  << hexCh(oc >> 28)
		  << hexCh(oc >> 24)
		  << hexCh(oc >> 20)
		  << hexCh(oc >> 16)
		  << hexCh(oc >> 12)
		  << hexCh(oc >>  8)
		  << hexCh(oc >>  4)
		  << hexCh(oc);
	}
	else if (encoding.szCodeUnit() == 2)
	{
		o << "0x"
		  << hexCh(oc >> 12)
		  << hexCh(oc >>  8)
		  << hexCh(oc >>  4)
		  << hexCh(oc);
	}
	else
	{
		o << "0x"
		  << hexCh(oc >>  4) 
		  << hexCh(oc);
	}
}

void prtCh(std::ostream& o, uint32_t c)
{
	if (encoding.is(Enc::EBCDIC))
	{
		prtHex(o, c);
		return;
	}

	int oc = (int)(c);

	switch (oc)
	{
		case '\'':
		o << (DFlag ? "'" : "\\'");
		break;

		case '"':
		o << (DFlag ? "\\\"" : "\"");
		break;

		case '\n':
		o << (DFlag ? "\\\\n" : "\\n");
		break;

		case '\t':
		o << (DFlag ? "\\\\t" : "\\t");
		break;

		case '\v':
		o << (DFlag ? "\\\\v" : "\\v");
		break;

		case '\b':
		o << (DFlag ? "\\\\b" : "\\b");
		break;

		case '\r':
		o << (DFlag ? "\\\\r" : "\\r");
		break;

		case '\f':
		o << (DFlag ? "\\\\f" : "\\f");
		break;

		case '\a':
		o << (DFlag ? "\\\\a" :"\\a");
		break;

		case '\\':
		o << "\\\\"; // both .dot and C/C++ code expect "\\"
		break;

		default:

		if ((oc < 256) && isprint(oc))
		{
			o << (char) oc;
		}
		else if (encoding.szCodeUnit() == 4)
		{
			o << "0x"
			  << hexCh(oc >> 20)
			  << hexCh(oc >> 16)
			  << hexCh(oc >> 12)
			  << hexCh(oc >>  8)
			  << hexCh(oc >>  4)
			  << hexCh(oc);
		}
		else if (encoding.szCodeUnit() == 2)
		{
			o << "0x"
			  << hexCh(oc >> 12)
			  << hexCh(oc >>  8)
			  << hexCh(oc >>  4)
			  << hexCh(oc);
		}
		else
		{
			o << '\\' << octCh(oc / 64) << octCh(oc / 8) << octCh(oc);
		}
	}
}

void prtChOrHexForSpan(std::ostream& o, uint32_t c)
{
	if (!encoding.is(Enc::EBCDIC) && (c < 256u) && isprint(c) && (c != ']'))
	{
		prtCh(o, c);
	}
	else
	{
		prtHex(o, c);
	}
}

void printSpan(std::ostream& o, uint32_t lb, uint32_t ub)
{
	o << "[";
	if ((ub - lb) == 1)
	{
		prtChOrHexForSpan(o, lb);
	}
	else
	{
		prtChOrHexForSpan(o, lb);
		o << "-";
		prtChOrHexForSpan(o, ub - 1);
	}
	o << "]";
}

} // end namespace re2c

