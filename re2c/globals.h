/* $Id$ */
#ifndef	_globals_h
#define	_globals_h

#include "basics.h"
#include <set>
#include <algorithm>
#include <string>
#include "stream_lc.h"
#include "code_names.h"

namespace re2c
{

enum { BSIZE = 8192};

extern file_info sourceFileInfo;
extern file_info outputFileInfo;
extern file_info headerFileInfo;

extern bool bFlag;
extern bool cFlag;
extern bool dFlag;
extern bool DFlag;
extern bool eFlag;
extern bool fFlag;
extern bool FFlag;
extern bool gFlag;
extern bool iFlag;
extern bool rFlag;
extern bool sFlag;
extern bool tFlag;
extern bool uFlag;
extern bool wFlag;

extern bool bNoGenerationDate;

extern bool bSinglePass;
extern bool bFirstPass;
extern bool bLastPass;

extern bool bUsedYYAccept;
extern bool bUsedYYMaxFill;
extern bool bUsedYYMarker;
extern bool bUsedYYBitmap;

extern bool bUseStartLabel;
extern std::string startLabelName;
extern std::string labelPrefix;
extern std::string condPrefix;
extern std::string condEnumPrefix;
extern std::string condDivider;
extern std::string condDividerParam;
extern std::string condGoto;
extern std::string condGotoParam;
extern std::string yychConversion;
extern std::string yyFillLength;
extern std::string yySetConditionParam;
extern std::string yySetStateParam;
extern std::string yySetupRule;
extern uint maxFill;
extern uint next_label;
extern uint cGotoThreshold;

/* configurations */
extern uint topIndent;
extern std::string indString;
extern bool yybmHexTable;
extern bool bEmitYYCh;
extern bool bUseStateAbort;
extern bool bUseStateNext;
extern bool bUseYYFill;
extern bool bUseYYFillParam;
extern bool bUseYYFillCheck;
extern bool bUseYYFillNaked;
extern bool bUseYYSetConditionParam;
extern bool bUseYYGetConditionNaked;
extern bool bUseYYSetStateParam;
extern bool bUseYYSetStateNaked;
extern bool bUseYYGetStateNaked;
extern bool bWroteGetState;
extern bool bWroteCondCheck;
extern bool bCaseInsensitive;
extern bool bCaseInverted;
extern bool bTypesDone;

extern uint asc2ebc[256];
extern uint ebc2asc[256];

extern uint *xlat, *talx;

extern uint next_fill_index;
extern uint last_fill_index;
extern std::set<uint> vUsedLabels;
extern CodeNames mapCodeName;
extern std::string typesInline;

extern uint nRealChars;

extern char octCh(uint c);
extern char hexCh(uint c);

} // end namespace re2c

#endif
