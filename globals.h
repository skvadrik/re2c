/* $Id$ */
#ifndef	_globals_h
#define	_globals_h

#include "basics.h"
#include <set>
#include <algorithm>
#include <string>

namespace re2c
{

extern const char *fileName;
extern const char *outputFileName;
extern bool bFlag;
extern bool dFlag;
extern bool eFlag;
extern bool iFlag;
extern bool sFlag;
extern bool wFlag;

extern bool bUsedYYAccept;
extern bool bUsedCtxMarker;
extern bool bUseStartLabel;
extern std::string startLabelName;
extern unsigned int oline;
extern uint maxFill;

/* configurations */
extern uint topIndent;
extern std::string indString;
extern bool yybmHexTable;

extern uint asc2ebc[256];
extern uint ebc2asc[256];

extern uint *xlat, *talx;

extern int vFillIndexes;
extern std::set<uint> vUsedLabels;

extern uint nRealChars;

inline char octCh(uint c)
{
	return '0' + c % 8;
}

inline char hexCh(uint c)
{
	static const char * sHex = "0123456789ABCDEF";
	
	return sHex[c & 0x0F];
}

} // end namespace re2c

#endif
