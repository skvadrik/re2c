#ifndef _RE2C_CODEGEN_SKELETON_PATH_
#define _RE2C_CODEGEN_SKELETON_PATH_

#include <vector>

#include "src/ir/rule_rank.h"
#include "src/util/c99_stdint.h"

namespace re2c
{

class path_t
{
	std::vector<uint32_t> arcs;
	rule_rank_t rule;
	size_t rule_pos;

public:
	path_t ();
	size_t len () const;
	size_t len_matching () const;
	rule_rank_t match () const;
	uint32_t operator [] (size_t i) const;
	void update (rule_rank_t r);
	void extend (rule_rank_t r, uint32_t c);
	void append (const path_t * p);
};

} // namespace re2c

#endif // _RE2C_CODEGEN_SKELETON_PATH_
