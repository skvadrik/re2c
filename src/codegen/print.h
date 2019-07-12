#ifndef _RE2C_CODE_PRINT_
#define _RE2C_CODE_PRINT_

#include "src/util/c99_stdint.h"
#include <iosfwd>


namespace re2c {

bool is_print   (uint32_t c);
void prtHex     (std::ostream &o, uint32_t c, uint32_t szcunit);
void prtChOrHex (std::ostream &o, uint32_t c, uint32_t szcunit, bool ebcdic, bool dot);
void printSpan  (std::ostream &o, uint32_t l, uint32_t u, uint32_t szcunit, bool ebcdic, bool dot);

} // end namespace re2c

#endif // _RE2C_CODE_PRINT_
