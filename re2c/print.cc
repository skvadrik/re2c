#include <iostream>

#include "globals.h"
#include "print.h"

namespace re2c
{

void prtChOrHex(std::ostream& o, uint c)
{
	if (!encoding.is(Enc::EBCDIC) && (c < 256u) && (isprint(c) || isspace(c)))
	{
		o << (DFlag ? '"' : '\'');
		prtCh(o, c);
		o << (DFlag ? '"' : '\'');
	}
	else
	{
		if (DFlag) o << '"';
		prtHex(o, c);
		if (DFlag) o << '"';
	}
}

void prtHex(std::ostream& o, uint c)
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

void prtCh(std::ostream& o, uint c)
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
		o << (DFlag ? "\\\\\\\\" : "\\\\");
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

void printSpan(std::ostream& o, uint lb, uint ub)
{
	if (lb > ub)
	{
		o << "*";
	}

	o << "[";

	if ((ub - lb) == 1)
	{
		prtCh(o, lb);
	}
	else
	{
		prtCh(o, lb);
		o << "-";
		prtCh(o, ub - 1);
	}

	o << "]";
}

} // end namespace re2c

