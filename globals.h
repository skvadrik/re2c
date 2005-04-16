/* $Id$ */
#ifndef	_globals_h
#define	_globals_h

#include "basics.h"
#include <list>
#include <algorithm>

template<typename _Ty>
class label_list: protected std::list<_Ty>
{
public:
	label_list()
		: std::list<_Ty>()
	{
	}
	
	void append(const _Ty &val)
	{
		push_back(val);
		std::list<_Ty>::sort();
		std::list<_Ty>::unique();
	}
	
	bool contains(const _Ty &val)
	{
		return std::find(std::list<_Ty>::begin(), std::list<_Ty>::end(), val) != std::list<_Ty>::end();
	}
};

namespace re2c
{

extern char *fileName;
extern char *outputFileName;
extern bool sFlag;
extern bool bFlag;
extern unsigned int oline;
extern uint maxFill;

extern uchar asc2ebc[256];
extern uchar ebc2asc[256];

extern uchar *xlat, *talx;

extern int vFillIndexes;
extern label_list<uint> vUsedLabels;

} // end namespace re2c

#endif
