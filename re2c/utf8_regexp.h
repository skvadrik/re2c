#ifndef _utf8_regexp_h
#define _utf8_regexp_h

#include "utf8.h"

namespace re2c {

struct RegExp; // forward

RegExp * UTF8Symbol(utf8::rune r);
RegExp * UTF8Range(const Range * r);

} // namespace re2c

#endif // _utf8_regexp_h
