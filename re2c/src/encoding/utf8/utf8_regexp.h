#ifndef _RE2C_RE_ENCODING_UTF8_REGEXP_
#define _RE2C_RE_ENCODING_UTF8_REGEXP_

#include "src/regexp/re.h"
#include "src/encoding/utf8/utf8.h"


namespace re2c {

class Range;

RE *UTF8Range(RESpec &spec, const Range *r);

} // namespace re2c

#endif // _RE2C_RE_ENCODING_UTF8_REGEXP_
