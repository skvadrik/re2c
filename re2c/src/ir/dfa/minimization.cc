#include <string.h>

#include "src/conf/opt.h"
#include "src/ir/dfa/dfa.h"
#include "src/ir/regexp/regexp_rule.h"
#include "src/globals.h"

namespace re2c
{

void dfa_t::minimization()
{
	const size_t count = states.size();

	size_t *part = new size_t[count + 1];

	switch (opts->dfa_minimization)
	{
		case TABLE: minimization_table(part); break;
		case MOORE: minimization_moore(part); break;
	}

	for (size_t i = 0; i < count; ++i)
	{
		if (i == part[i])
		{
			size_t *arcs = states[i]->arcs;
			for (size_t c = 0; c < nchars; ++c)
			{
				arcs[c] = part[arcs[c]];
			}
		}
		else
		{
			delete states[i];
			states[i] = NULL;
		}
	}

	delete[] part;
}

/*
 * note [DFA minimization: table filling algorithm]
 *
 * This algorithm is simple and slow; it's a reference implementation.
 *
 * The algorithm constructs (strictly lower triangular) boolean matrix
 * indexed by DFA states. Each matrix cell (S1,S2) indicates if states
 * S1 and S2 are distinguishable. Initialy states are distinguished
 * according to their rule and context. One step of the algorithm
 * updates the matrix as follows: each pair of states S1 and S2 is
 * marked as distinguishable iff exist transitions from S1 and S2 on
 * the same symbol that go to distinguishable states. The algorithm
 * loops until the matrix stops changing.
 */
void dfa_t::minimization_table(size_t *part)
{
	const size_t count = states.size();

	bool **tbl = new bool*[count + 1];
	tbl[0] = new bool[count * (count + 1) / 2];
	for (size_t i = 0; i < count; ++i)
	{
		tbl[i + 1] = tbl[i] + i;
	}

	for (size_t i = 0; i < count; ++i)
	{
		dfa_state_t *s1 = states[i];
		for (size_t j = 0; j < i; ++j)
		{
			dfa_state_t *s2 = states[j];
			tbl[i][j] = s1->ctx != s2->ctx
				|| s1->rule != s2->rule;
		}
		tbl[count][i] = true;
	}

	for (bool loop = true; loop;)
	{
		loop = false;
		for (size_t i = 0; i < count; ++i)
		{
			for (size_t j = 0; j < i; ++j)
			{
				if (!tbl[i][j])
				{
					for (size_t k = 0; k < nchars; ++k)
					{
						size_t oi = states[i]->arcs[k];
						size_t oj = states[j]->arcs[k];
						if (oi < oj)
						{
							std::swap(oi, oj);
						}
						if (oi != oj && tbl[oi][oj])
						{
							tbl[i][j] = true;
							loop = true;
							break;
						}
					}
				}
			}
		}
	}

	for (size_t i = 0; i <= count; ++i)
	{
		part[i] = i;
		for (size_t j = 0; j < i; ++j)
		{
			if (!tbl[i][j])
			{
				part[i] = j;
				break;
			}
		}
	}

	delete[] tbl[0];
	delete[] tbl;
}

/*
 * note [DFA minimization: Moore algorithm]
 *
 * The algorithm maintains partition of DFA states.
 * Initial partition is coarse: states are distinguished according
 * to their rule and context. Partition is gradually refined: each
 * set of states is split into minimal number of subsets such that
 * for all states in a subset transitions on the same symbol go to
 * the same set of states.
 * The algorithm loops until partition stops changing.
 */
void dfa_t::minimization_moore(size_t *part)
{
	const size_t count = states.size();

	size_t *next = new size_t[count];

	std::map<std::pair<RuleOp*, bool>, size_t> init;
	for (size_t i = 0; i < count; ++i)
	{
		dfa_state_t *s = states[i];
		std::pair<RuleOp*, bool> key(s->rule, s->ctx);
		if (init.insert(std::make_pair(key, i)).second)
		{
			part[i] = i;
			next[i] = count;
		}
		else
		{
			const size_t j = init[key];
			part[i] = j;
			next[i] = next[j];
			next[j] = i;
		}
	}
	part[count] = count;

	size_t *out = new size_t[nchars * count];
	size_t *diff = new size_t[count];
	for (bool loop = true; loop;)
	{
		loop = false;
		for (size_t i = 0; i < count; ++i)
		{
			if (i != part[i] || next[i] == count)
			{
				continue;
			}

			for (size_t j = i; j != count; j = next[j])
			{
				size_t *o = &out[j * nchars];
				size_t *a = states[j]->arcs;
				for (size_t c = 0; c < nchars; ++c)
				{
					o[c] = part[a[c]];
				}
			}

			size_t diff_count = 0;
			for (size_t j = i; j != count;)
			{
				const size_t j_next = next[j];
				size_t n = 0;
				for (; n < diff_count; ++n)
				{
					size_t k = diff[n];
					if (memcmp(&out[j * nchars], &out[k * nchars], nchars * sizeof(size_t)) == 0)
					{
						part[j] = k;
						next[j] = next[k];
						next[k] = j;
						break;
					}
				}
				if (n == diff_count)
				{
					diff[diff_count++] = j;
					part[j] = j;
					next[j] = count;
				}
				j = j_next;
			}
			loop |= diff_count > 1;
		}
	}
	delete[] out;
	delete[] diff;
	delete[] next;
}

} // namespace re2c

