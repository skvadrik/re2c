#ifndef _RE2C_RE_ENCODING_UTF16_REGEXP_
#define _RE2C_RE_ENCODING_UTF16_REGEXP_


namespace re2c {

class Range;
struct RE;
struct RESpec;

RE *UTF16Range(RESpec &spec, const Range *r);

} // namespace re2c

#endif // _RE2C_RE_ENCODING_UTF16_REGEXP_
