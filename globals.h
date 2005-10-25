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
extern bool sFlag;
extern bool bFlag;
extern bool dFlag;
extern bool iFlag;
extern bool bUsedYYAccept;
extern unsigned int oline;
extern uint maxFill;

extern uchar asc2ebc[256];
extern uchar ebc2asc[256];

extern uchar *xlat, *talx;

extern int vFillIndexes;
extern label_list<uint> vUsedLabels;

} // end namespace re2c

#endif
