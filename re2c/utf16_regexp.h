#ifndef _utf16_regexp_h
#define _utf16_regexp_h

#include "utf16.h"

namespace re2c {

struct RegExp; // forward

RegExp * UTF16Symbol(utf16::rune r);
RegExp * UTF16Range(const Range * r);

} // namespace re2c

#endif // _utf16_regexp_h
