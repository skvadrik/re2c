/* $Id$ */
#ifndef	_globals_h
#define	_globals_h

#include "basics.h"

namespace re2c
{

extern char *fileName;
extern char *outputFileName;
extern bool sFlag;
extern bool bFlag;
extern unsigned int oline;

extern uchar asc2ebc[256];
extern uchar ebc2asc[256];

extern uchar *xlat, *talx;

} // end namespace re2c

#endif
