#ifndef _RE2C_RE_ENCODING_EBCDIC_REGEXP_
#define _RE2C_RE_ENCODING_EBCDIC_REGEXP_

#include "src/util/c99_stdint.h"
#include "src/re/re.h"

namespace re2c {

class Range;

RE *EBCDICSymbol(RE::alc_t &alc, uint32_t c);
RE *EBCDICRange(RE::alc_t &alc, const Range *r);

} // namespace re2c

#endif // _RE2C_RE_ENCODING_EBCDIC_REGEXP_
