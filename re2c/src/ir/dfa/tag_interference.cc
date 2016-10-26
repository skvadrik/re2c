#include <string.h>

#include "src/ir/dfa/tag_optimize.h"

namespace re2c
{

static void interfere(const tagcmd_t &cmd, const Tagpool &pool, bool *interf, bool *live, bool *buf, size_t nver);

void tag_interference(const dfa_t &dfa, const bool *live, bool *interf)
{
	const Tagpool &pool = dfa.tagpool;
	const size_t
		nstate = dfa.states.size(),
		ntag = pool.ntags,
		nver = static_cast<size_t>(dfa.maxtagver) + 1,
		nsym = dfa.nchars;
	bool *buf1 = new bool[nver];
	bool *buf2 = new bool[nver];

	memset(interf, 0, nver * nver * sizeof(bool));
	for (size_t i = 0; i < nstate; ++i) {
		const dfa_state_t *s = dfa.states[i];

		if (s->rule != Rule::NONE) {
			unpack(nver, buf1, ntag, pool[dfa.rules[s->rule].tags]);
			interfere(s->rule_tags, pool, interf, buf1, buf2, nver);
		}

		for (size_t c = 0; c < nsym; ++c) {
			memcpy(buf1, &live[(i * nsym + c) * nver], nver * sizeof(bool));
			interfere(s->tags[c], pool, interf, buf1, buf2, nver);
		}
	}

	delete[] buf1;
	delete[] buf2;
}

void interfere(const tagcmd_t &cmd, const Tagpool &pool,
	bool *interf, bool *live, bool *buf, size_t nver)
{
	// Each tag updated by set command interferes with all tags
	// alive after this command, except tags udated by other set
	// commands (they all have the same value: current position).
	if (cmd.set != ZERO_TAGS) {
		// updated by set commands
		unpack(nver, buf, pool.ntags, pool[cmd.set]);

		// alive after, but not updated by set commands
		// (a.k.a. all tags alive before the first set command)
		for (size_t v = 0; v < nver; ++v) {
			live[v] &= !buf[v];
		}

		for (size_t i = 0; i < nver; ++i) {
			if (!buf[i]) continue;
			for (size_t j = 0; j < nver; ++j) {
				if (!live[j]) continue;
				interf[i * nver + j] = interf[j * nver + i] = true;
			}
		}
	}

	// Each tag X updated by copy command X = Y interferes with
	// all tags alive after this command except tags equal to Y.
	// We don't track which tags are equal to Y at this point,
	// but at least we can exclude Y itself and all tags assigned
	// to Y by copy commands.
	for (const tagcopy_t *p = cmd.copy; p; p = p->next) {
		const tagver_t r = p->rhs;

		// alive after this command: tags used by subsequent copy
		// commands plus all tags alive before the first set command
		memcpy(buf, live, nver * sizeof(bool));
		for (const tagcopy_t *q = p->next; q; q = q->next) {
			if (q->rhs != r) {
				buf[q->rhs] = true;
			}
		}

		// exclude: tags equal to RHS of this command
		buf[r] = false;
		for (const tagcopy_t *q = cmd.copy; q; q = q->next) {
			if (q->rhs == r) {
				buf[q->lhs] = false;
			}
		}

		const size_t l = static_cast<size_t>(p->lhs);
		for (size_t v = 0; v < nver; ++v) {
			if (!buf[v]) continue;
			interf[l * nver + v] = interf[v * nver + l] = true;
		}
	}
}

} // namespace re2c

