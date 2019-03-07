#ifndef _RE2C_RE_ENCODING_UTF16_REGEXP_
#define _RE2C_RE_ENCODING_UTF16_REGEXP_

#include "src/regexp/re.h"
#include "src/encoding/utf16/utf16.h"


namespace re2c {

class Range;

RE *UTF16Range(RESpec &spec, const Range *r);

} // namespace re2c

#endif // _RE2C_RE_ENCODING_UTF16_REGEXP_
