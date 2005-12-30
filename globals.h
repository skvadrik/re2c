/* $Id$ */
#ifndef	_globals_h
#define	_globals_h

#include "basics.h"
#include <set>
#include <algorithm>

template<typename _Ty>
class label_list: protected std::set<_Ty>
{
public:
	label_list()
		: std::set<_Ty>()
	{
	}
	
	void append(const _Ty &val)
	{
		std::set<_Ty>::insert(val);
	}
	
	bool contains(const _Ty &val)
	{
		return find(val) != std::set<_Ty>::end();
	}
};

namespace re2c
{

extern char *fileName;
extern char *outputFileName;
extern bool bFlag;
extern bool dFlag;
extern bool eFlag;
extern bool iFlag;
extern bool sFlag;
extern bool wFlag;

extern bool bUsedYYAccept;
extern unsigned int oline;
extern uint maxFill;
extern uint topIndent;

extern uint asc2ebc[256];
extern uint ebc2asc[256];

extern uint *xlat, *talx;

extern int vFillIndexes;
extern label_list<uint> vUsedLabels;

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
