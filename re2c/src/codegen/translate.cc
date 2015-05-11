/* $Id$ */
#include "src/globals.h"

namespace re2c
{

char octCh(uint32_t c)
{
	return '0' + c % 8;
}

static const char * sHex = "0123456789ABCDEF";

char hexCh(uint32_t c)
{
	return sHex[c & 0x0F];
}

} // end namespace re2c
