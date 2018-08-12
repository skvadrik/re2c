#ifndef _RE2C_DFA_DETERMINIZATION_
#define _RE2C_DFA_DETERMINIZATION_

#include "src/util/c99_stdint.h"
#include <string>

#include "src/dfa/closure.h"
#include "src/dfa/dump.h"
#include "src/dfa/tagpool.h"
#include "src/dfa/tagtree.h"
#include "src/dfa/find_state.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

// fwd
struct opt_t;
struct Warn;
struct nfa_t;
struct dfa_t;

struct determ_context_t
{
	// determinization input
	const opt_t        *dc_opts;      // options
	Warn               &dc_warn;      // warnings
	const std::string  &dc_condname;  // the name of current condition (with -c)
	const nfa_t        &dc_nfa;       // TNFA

	// determinization output
	dfa_t              &dc_dfa;       // resulting TDFA
//	tcpool_t           &dc_tcmdpool;  // pool of tag actions
//	uint32_t            dc_maxtagver; // maximal tag version
//	tagver_t           *dc_finvers;   // tag versions used in final states
//	std::set<tagver_t> &dc_mtagvers;  // the set of m-tags

	// temporary structures used by determinization
	uint32_t            dc_origin;    // from-state of the current transition
	uint32_t            dc_target;    // to-state of the current transition
	uint32_t            dc_symbol;    // alphabet symbol of the current transition
	tcmd_t             *dc_actions;   // tag actions of the current transition
	closure_t           dc_reached;
	closure_t           dc_closure;
	prectable_t        *dc_prectbl;   // precedence table for Okui POSIX disambiguation
	Tagpool             dc_tagpool;
	allocator_t        &dc_allocator;
	tagtree_t          &dc_tagtrie;   // prefix trie of tag histories
	kernels_t           dc_kernels;   // TDFA states under construction
	kernel_buffers_t    dc_buffers;
	newvers_t           dc_newvers;
	dump_dfa_t          dc_dump;

	determ_context_t(const opt_t *, Warn &, const std::string &, const nfa_t &, dfa_t &);
	FORBID_COPY(determ_context_t);
};

void tagged_epsilon_closure(determ_context_t &ctx);
void find_state(determ_context_t &ctx);
int32_t precedence(determ_context_t &, const clos_t &, const clos_t &, int32_t &, int32_t &);

} // namespace re2c

#endif // _RE2C_DFA_DETERMINIZATION_
