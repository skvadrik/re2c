#include <algorithm>

#include "src/codegen/output.h"
#include "src/ir/compile.h"
#include "src/ir/dfa/dfa.h"
#include "src/ir/nfa/nfa.h"
#include "src/ir/regexp/regexp.h"
#include "src/parse/spec.h"

namespace re2c {

smart_ptr<DFA> compile (Spec & spec, Output & output, const std::string & cond, uint32_t cunits)
{
	RegExp * re = spec.re;

	// The original set of code units (charset) might be very large.
	// A common trick it is to split charset into disjoint character ranges
	// and choose a representative of each range (we choose lower bound).
	// The set of all representatives is the new (compacted) charset.
	// Don't forget to include zero and upper bound, even if they
	// do not explicitely apper in ranges.
	std::set<uint32_t> bounds;
	re->split(bounds);
	bounds.insert(0);
	bounds.insert(cunits);
	charset_t cs;
	for (std::set<uint32_t>::const_iterator i = bounds.begin(); i != bounds.end(); ++i)
	{
		cs.push_back(*i);
	}

	nfa_t nfa(re);

	smart_ptr<DFA> dfa = make_smart_ptr (new DFA
		( cond
		, output.source.get_block_line ()
		, 0
		, cunits
		, cs
		, spec.rules
		, nfa
		));

	// accumulate global statistics from this particular DFA
	output.max_fill = std::max (output.max_fill, dfa->max_fill);
	if (dfa->need_accept)
	{
		output.source.set_used_yyaccept ();
	}

	return dfa;
}

} // namespace re2c
