#ifndef _RE2C_DFA_ENCODING_UTF8_REGEXP_
#define _RE2C_DFA_ENCODING_UTF8_REGEXP_

#include "src/dfa/encoding/utf8/utf8.h"
#include "src/util/range.h"

namespace re2c {

class RegExp; // forward

RegExp * UTF8Symbol(utf8::rune r);
RegExp * UTF8Range(const Range * r);

} // namespace re2c

#endif // _RE2C_DFA_ENCODING_UTF8_REGEXP_
