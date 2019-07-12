#ifndef _RE2C_RE_ENCODING_EBCDIC_REGEXP_
#define _RE2C_RE_ENCODING_EBCDIC_REGEXP_

#include "src/util/c99_stdint.h"


namespace re2c {

class Range;
struct RE;
struct RESpec;

RE *EBCDICRange(RESpec &spec, const Range *r);

} // namespace re2c

#endif // _RE2C_RE_ENCODING_EBCDIC_REGEXP_
