#ifndef _RE2C_IR_DFA_TAG_OPTIMIZE_
#define _RE2C_IR_DFA_TAG_OPTIMIZE_

#include "src/ir/dfa/dfa.h"

namespace re2c {

typedef uint32_t cfg_ix_t;

// basic block
struct cfg_bb_t
{
	cfg_ix_t *succb;
	cfg_ix_t *succe;
	tagcmd_t *cmd;
	size_t use;
};

// control flow graph
struct cfg_t
{
	dfa_t &dfa;
	cfg_bb_t *bblocks;
	cfg_ix_t nbblock;

	explicit cfg_t(dfa_t &a);
	~cfg_t();
	FORBID_COPY(cfg_t);
};

void tag_liveness(const cfg_t &cfg, bool *live);
void tag_dce(cfg_t &cfg, const bool *live);
void tag_interference(const cfg_t &cfg, const bool *live, bool *interf);
tagver_t tag_allocation(const cfg_t &cfg, const bool *interf, tagver_t *ver2new);
void tag_renaming(cfg_t &cfg, const tagver_t *ver2new, tagver_t maxver);
void tag_indexing(const cfg_t &cfg);

} // namespace re2c

#endif // _RE2C_IR_DFA_TAG_OPTIMIZE_
