#include <limits>

#include "src/regexp/rule.h"


namespace re2c {

free_list<Code*> Code::flist;

const size_t Rule::NONE = std::numeric_limits<size_t>::max();

} // namespace re2c
