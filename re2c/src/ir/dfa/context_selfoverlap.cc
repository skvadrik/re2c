#include <algorithm>
#include <map>
#include <vector>

#include "src/conf/warn.h"
#include "src/ir/dfa/dfa.h"
#include "src/ir/nfa/nfa.h"
#include "src/util/intersect_sorted.h"
#include "src/globals.h"

namespace re2c
{

static void g(nfa_state_t *n, std::vector<nfa_state_t*> &tail);
static void e(nfa_state_t *n, std::vector<nfa_state_t*> &tail);
static void f(nfa_state_t *n, std::vector<nfa_state_t*> &tail);

void check_context_selfoverlap(
	ord_hash_set_t &kernels,
	const std::vector<CtxVar> &contexts,
	uint32_t line,
	const std::string &cond)
{
	const size_t nctxs = contexts.size();

	std::vector<bool> bad(nctxs, false);

	std::map<nfa_state_t*, std::vector<nfa_state_t*> > shadows;
	for (size_t i = 0; i < kernels.size(); ++i) {
		nfa_state_t **kernel;
		const size_t kernel_size = kernels.deref<nfa_state_t*>(i, kernel);
		for (size_t j = 0; j < kernel_size; ++j) {
			nfa_state_t *n = kernel[j];
			if (n->type == nfa_state_t::CTX
				&& !bad[n->value.ctx.info]) {
				std::vector<nfa_state_t*> &shadow = shadows[n];
				if (shadow.empty()) {
					f(n, shadow);
				}
				if (intersect_sorted(
					shadow.begin(), shadow.end(),
					kernel, kernel + kernel_size)) {
					bad[n->value.ctx.info] = true;
				}
			}
		}
	}

	for (size_t i = 0; i < nctxs; ++i) {
		if (bad[i]) {
			warn.selfoverlapping_contexts(line, cond, contexts[i]);
		}
	}
}

void f(nfa_state_t *n, std::vector<nfa_state_t*> &tail)
{
	e(n, tail);
	std::sort(tail.begin(), tail.end());
}

void g(nfa_state_t *n, std::vector<nfa_state_t*> &tail)
{
	if (!n->mark)
	{
		n->mark = true;
		tail.push_back(n);
		switch (n->type)
		{
			case nfa_state_t::ALT:
				g(n->value.alt.out2, tail);
				g(n->value.alt.out1, tail);
				break;
			case nfa_state_t::RAN:
				g(n->value.ran.out, tail);
				break;
			case nfa_state_t::CTX:
				g(n->value.ctx.out, tail);
				break;
			case nfa_state_t::FIN:
				break;
		}
		n->mark = false;
	}
}

static void e(nfa_state_t *n, std::vector<nfa_state_t*> &tail)
{
	if (!n->mark)
	{
		n->mark = true;
		switch (n->type)
		{
			case nfa_state_t::ALT:
				e(n->value.alt.out2, tail);
				e(n->value.alt.out1, tail);
				break;
			case nfa_state_t::RAN:
				g(n->value.ran.out, tail);
				break;
			case nfa_state_t::CTX:
				e(n->value.ctx.out, tail);
				break;
			case nfa_state_t::FIN:
				break;
		}
		n->mark = false;
	}
}

} // namespace re2c

