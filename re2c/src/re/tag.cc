#include <limits>

#include "src/re/tag.h"

namespace re2c
{

const size_t Tag::RIGHTMOST = std::numeric_limits<size_t>::max();
const size_t Tag::VARDIST = std::numeric_limits<size_t>::max();
const size_t Tag::FICTIVE = Tag::RIGHTMOST - 1;

} // namespace re2c
