#ifndef _RE2C_CODEGEN_SKELETON_PATH_
#define _RE2C_CODEGEN_SKELETON_PATH_

#include <vector>

#include "src/ir/rule_rank.h"
#include "src/util/c99_stdint.h"

namespace re2c
{

namespace skeleton
{

struct Path
{
	typedef std::vector<uint32_t> chars_t;

	chars_t chars;
	uint32_t length;
	rule_rank_t rule;

	Path (const chars_t & cs, uint32_t l, rule_rank_t r);
	void update (rule_rank_t r);
	void extend (rule_rank_t r, uint32_t c);
	void append (const Path * p);
};

} // namespace skeleton

} // namespace re2c

#endif // _RE2C_CODEGEN_SKELETON_PATH_
