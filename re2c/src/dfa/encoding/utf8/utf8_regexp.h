#ifndef _utf8_regexp_h
#define _utf8_regexp_h

#include "src/dfa/encoding/utf8/utf8.h"
#include "src/util/range.h"

namespace re2c {

class RegExp; // forward

RegExp * UTF8Symbol(utf8::rune r);
RegExp * UTF8Range(const Range * r);

} // namespace re2c

#endif // _utf8_regexp_h
