#ifndef _RE2C_DFA_ENCODING_UTF16_REGEXP_
#define _RE2C_DFA_ENCODING_UTF16_REGEXP_

#include "src/dfa/encoding/utf16/utf16.h"
#include "src/util/range.h"

namespace re2c {

class RegExp; // forward

RegExp * UTF16Symbol(utf16::rune r);
RegExp * UTF16Range(const Range * r);

} // namespace re2c

#endif // _RE2C_DFA_ENCODING_UTF16_REGEXP_
