#include <limits>

#include "src/re/tag.h"

namespace re2c
{

const size_t Tag::RIGHTMOST = std::numeric_limits<size_t>::max();
const size_t Tag::VARDIST = std::numeric_limits<size_t>::max();
const size_t Tag::FICTIVE1 = (std::numeric_limits<size_t>::max() / 3 - 1) * 3;
const size_t Tag::FICTIVE2 = Tag::FICTIVE1 + 1;

} // namespace re2c
