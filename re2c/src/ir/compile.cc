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

static smart_ptr<DFA> compile_rules(
	const std::vector<const RegExpRule*> &rules,
	size_t defrule,
	Output &output,
	const std::string &cond,
	uint32_t cunits)
{
	const uint32_t line = output.source.block().line;
	const std::string name = make_name(cond, line);

	warn_nullable(rules, cond);

	// The original set of code units (charset) might be very large.
	// A common trick it is to split charset into disjoint character ranges
	// and choose a representative of each range (we choose lower bound).
	// The set of all representatives is the new (compacted) charset.
	// Don't forget to include zero and upper bound, even if they
	// do not explicitely apper in ranges.
	std::set<uint32_t> bounds;
	split(rules, bounds);
	bounds.insert(0);
	bounds.insert(cunits);
	charset_t cs;
	for (std::set<uint32_t>::const_iterator i = bounds.begin(); i != bounds.end(); ++i)
	{
		cs.push_back(*i);
	}

	nfa_t nfa(rules);

	dfa_t dfa(nfa, cs, cond);

	// skeleton must be constructed after DFA construction
	// but prior to any other DFA transformations
	Skeleton skeleton(dfa, cs, defrule, name, cond, line);
	warn_undefined_control_flow(skeleton);
	if (opts->target == opt_t::SKELETON) {
		emit_data(skeleton);
	}

	cutoff_dead_rules(dfa, defrule, cond);

	insert_fallback_tags(dfa);

	// try to minimize the number of tag variables
	optimize_tags(dfa);

	minimization(dfa);

	// find YYFILL states and calculate argument to YYFILL
	std::vector<size_t> fill;
	fillpoints(dfa, fill);

	// ADFA stands for 'DFA with actions'
	DFA *adfa = new DFA(dfa, fill, defrule, skeleton.sizeof_key, cs, name, cond, line);

	// see note [reordering DFA states]
	adfa->reorder();

	// skeleton is constructed, do further DFA transformations
	adfa->prepare();

	// finally gather overall DFA statistics
	adfa->calc_stats(line);

	// accumulate global statistics from this particular DFA
	output.max_fill = std::max (output.max_fill, adfa->max_fill);
	if (adfa->need_accept)
	{
		output.source.block().used_yyaccept = true;
	}

	return make_smart_ptr(adfa);
}

// small wrapper that makes sure default rule is not forgotten
smart_ptr<DFA> compile(
	const Spec &spec,
	Output &output,
	const std::string &cond,
	uint32_t cunits)
{
	size_t defrule = Rule::NONE;
	std::vector<const RegExpRule*> rules(spec.res);
	if (spec.def) {
		defrule = spec.res.size();
		rules.push_back(spec.def);
	}
	return compile_rules(rules, defrule, output, cond, cunits);
}

} // namespace re2c
