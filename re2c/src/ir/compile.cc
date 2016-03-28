#include <algorithm>
#include <ostream>
#include <set>

#include "src/codegen/output.h"
#include "src/conf/opt.h"
#include "src/ir/compile.h"
#include "src/ir/adfa/adfa.h"
#include "src/ir/dfa/dfa.h"
#include "src/ir/nfa/nfa.h"
#include "src/ir/regexp/regexp.h"
#include "src/ir/skeleton/skeleton.h"
#include "src/parse/spec.h"
#include "src/globals.h"

namespace re2c {

static std::string make_name(const std::string &cond, uint32_t line)
{
	std::ostringstream os;
	os << "line" << line;
	std::string name = os.str();
	if (!cond.empty ())
	{
		name += "_";
		name += cond;
	}
	return name;
}

smart_ptr<DFA> compile (Spec & spec, Output & output, const std::string & cond, uint32_t cunits)
{
	const uint32_t line = output.source.get_block_line();
	const std::string name = make_name(cond, line);

	// The original set of code units (charset) might be very large.
	// A common trick it is to split charset into disjoint character ranges
	// and choose a representative of each range (we choose lower bound).
	// The set of all representatives is the new (compacted) charset.
	// Don't forget to include zero and upper bound, even if they
	// do not explicitely apper in ranges.
	std::set<uint32_t> bounds;
	split(spec.res, bounds);
	bounds.insert(0);
	bounds.insert(cunits);
	charset_t cs;
	for (std::set<uint32_t>::const_iterator i = bounds.begin(); i != bounds.end(); ++i)
	{
		cs.push_back(*i);
	}

	nfa_t nfa(spec);

	dfa_t dfa(nfa, cs, line, cond);

	// skeleton must be constructed after DFA construction
	// but prior to any other DFA transformations
	const size_t defrule = spec.def
		? dfa.rules.size() - 1
		: Rule::NONE;
	Skeleton *skeleton = new Skeleton(dfa, cs, defrule, name, cond, line);

	minimization(dfa);

	// find YYFILL states and calculate argument to YYFILL
	std::vector<size_t> fill;
	fillpoints(dfa, fill);

	// see note [fallback states]
	std::vector<size_t> fallback;
	fallback_states(dfa, fallback);

	// Non-trailing contexts imply the existence of base context marker
	// that points at the beginning of lexeme. First, it is a feature
	// of re2c API. Second, it simplifies implementation (otherwise
	// it would be hard to mix generic API and fixed-length contexts).
	//
	// The only case without base context marker is when:
	//     - only trailing contexts are allowed
	//     - they don't overlap (one marker is enough for all of them)
	//     - with generic API fixed-length contexts are forbidden
	// Note that in this case, if generic API is used, fixed-length
	// contexts are forbidden (which may cause additional overlaps).
	const bool multiple_ctxmarkers = deduplicate_contexts(dfa, fallback);
	const bool base_ctxmarker
		= multiple_ctxmarkers
		|| opts->contexts;

	// ADFA stands for 'DFA with actions'
	DFA *adfa = new DFA(dfa, fill, fallback, skeleton, cs,
		name, cond, line, base_ctxmarker);

	// see note [reordering DFA states]
	adfa->reorder();

	// skeleton is constructed, do further DFA transformations
	adfa->prepare();

	// finally gather overall DFA statistics
	adfa->calc_stats();

	// accumulate global statistics from this particular DFA
	output.max_fill = std::max (output.max_fill, adfa->max_fill);
	if (adfa->need_accept)
	{
		output.source.set_used_yyaccept ();
	}

	return make_smart_ptr(adfa);
}

} // namespace re2c
