/* $Id$ */
#include "globals.h"

namespace re2c
{

char octCh(uint c)
{
	return '0' + c % 8;
}

static const char * sHex = "0123456789ABCDEF";

char hexCh(uint c)
{
	return sHex[c & 0x0F];
}

} // end namespace re2c
