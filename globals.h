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
		sort();
		unique();
	}
	
	bool contains(const _Ty &val)
	{
		return std::find(begin(), end(), val) != end();
	}
};

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

extern label_list<uint> vUsedLabels;

} // end namespace re2c

#endif
