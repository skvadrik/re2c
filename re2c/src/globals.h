#ifndef _RE2C_GLOBALS_
#define _RE2C_GLOBALS_

#include <string>

#include "src/codegen/code_names.h"
#include "src/codegen/input_api.h"
#include "src/conf/opt.h"
#include "src/conf/warn.h"
#include "src/ir/regexp/encoding/enc.h"
#include "src/ir/regexp/empty_class_policy.h"
#include "src/util/c99_stdint.h"

namespace re2c
{

extern const uint32_t asc2asc[256];
extern const uint32_t asc2ebc[256];
extern const uint32_t ebc2asc[256];

extern bool bUsedYYBitmap;
extern bool bWroteGetState;
extern bool bWroteCondCheck;
extern uint32_t last_fill_index;
extern CodeNames mapCodeName;

extern Opt opts;
extern Warn warn;

} // end namespace re2c

#endif // _RE2C_GLOBALS_
