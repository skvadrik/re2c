#ifndef	_globals_h
#define	_globals_h

#include <string>

#include "src/codegen/code_names.h"
#include "src/codegen/input_api.h"
#include "src/dfa/encoding/enc.h"
#include "src/util/c99_stdint.h"

namespace re2c
{

enum BUFFERSIZE { BSIZE = 8192};

extern bool bFlag;
extern bool cFlag;
extern bool dFlag;
extern bool DFlag;
extern bool fFlag;
extern bool FFlag;
extern bool gFlag;
extern bool iFlag;
extern bool rFlag;
extern bool sFlag;
extern bool tFlag;
extern bool flag_skeleton;

extern bool bNoGenerationDate;
extern bool bUsedYYBitmap;

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
extern uint32_t cGotoThreshold;

/* configurations */
extern uint32_t topIndent;
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

extern const uint32_t asc2asc[256];
extern const uint32_t asc2ebc[256];
extern const uint32_t ebc2asc[256];

extern uint32_t last_fill_index;
extern CodeNames mapCodeName;

extern Enc encoding;
extern InputAPI input_api;

} // end namespace re2c

#endif
