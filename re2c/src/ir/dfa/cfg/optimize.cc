#include "src/ir/dfa/cfg/cfg.h"
#include "src/ir/dfa/dfa.h"

namespace re2c
{

static void freeze_tags(dfa_t &dfa);

void optimize_tags(dfa_t &dfa)
{
	tagver_t maxver = dfa.maxtagver;
	if (maxver > 0) {
		cfg_t cfg(dfa);

		size_t nver = static_cast<size_t>(maxver) + 1;
		tagver_t *ver2new = new tagver_t[nver];

		maxver = cfg_t::compact(cfg, ver2new);
		cfg_t::renaming(cfg, ver2new, maxver);

		if (maxver > 0) {
			nver = static_cast<size_t>(maxver) + 1;
			bool *live = new bool[cfg.nbbfin * nver];
			bool *interf = new bool[nver * nver];

			static const uint32_t NPASS = 2;
			for (uint32_t n = 0; n < NPASS; ++n) {
				cfg_t::liveness_analysis(cfg, live);
				cfg_t::dead_code_elimination(cfg, live);
				cfg_t::interference(cfg, live, interf);
				maxver = cfg_t::variable_allocation(cfg, interf, ver2new);
				cfg_t::renaming(cfg, ver2new, maxver);
				cfg_t::normalization(cfg);
			}

			delete[] live;
			delete[] interf;
		}

		delete[] ver2new;
	}

	freeze_tags(dfa);
}

/* note [tag freezing]
 *
 * Comparison of tag commands should be very fast (constant time):
 * many optimizations rely on this (like tunnelling, hoisting and
 * especially Moore's minimization, which compares whole classes
 * of tagged transition at once). So we bring each command to some
 * 'normal form' and insert it into common index.
 *
 * After that commands can be addressed and compared by index.
 * They also become immutable, because different commands may
 * share representation in memory.
 */
void freeze_tags(dfa_t &dfa)
{
	tcpool_t &pool = dfa.tcpool;
	const size_t
		nstate = dfa.states.size(),
		nsym = dfa.nchars;

	dfa.tcid0 = new tcid_t(pool.insert(dfa.tcmd0->save, dfa.tcmd0->copy));
	delete dfa.tcmd0;
	dfa.tcmd0 = NULL;

	for (size_t i = 0; i < nstate; ++i) {
		dfa_state_t *s = dfa.states[i];
		const tcmd_t
			*cmd = s->tcmd,
			*const fin = cmd + nsym,
			*const fall = fin + 1;
		tcid_t *id = s->tcid = new tcid_t[nsym + 2];

		// transition commands
		for(; cmd < fin; ++cmd) {
			*id++ = pool.insert(cmd->save, cmd->copy);
		}

		// final epsilon-transition command
		*id++ = pool.insert(fin->save, fin->copy);

		// fallback epsilon-transition command
		*id++ = pool.insert(fall->save, fall->copy);

		delete[] s->tcmd;
		s->tcmd = NULL;
	}
}

} // namespace re2c

