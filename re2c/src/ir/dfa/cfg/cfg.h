#ifndef _RE2C_IR_DFA_CFG_CFG_
#define _RE2C_IR_DFA_CFG_CFG_

#include "src/ir/dfa/dfa.h"

namespace re2c {

typedef uint32_t cfg_ix_t;

// basic block
struct cfg_bb_t
{
	cfg_ix_t *succb;
	cfg_ix_t *succe;
	tcmd_t *cmd;
	tagver_t *use;
};

// control flow graph
struct cfg_t
{
	dfa_t &dfa;
	cfg_bb_t *bblocks;
	cfg_ix_t nbblock;

	explicit cfg_t(dfa_t &a);
	~cfg_t();
	static void liveness_analysis(const cfg_t &cfg, bool *live);
	static void dead_code_elimination(cfg_t &cfg, const bool *live);
	static void interference(const cfg_t &cfg, const bool *live, bool *interf);
	static tagver_t variable_allocation(const cfg_t &cfg, const bool *interf, tagver_t *ver2new);
	static void renaming(cfg_t &cfg, const tagver_t *ver2new, tagver_t maxver);
	static void normalization(cfg_t &cfg);
	FORBID_COPY(cfg_t);
};

} // namespace re2c

#endif // _RE2C_IR_DFA_CFG_CFG_
