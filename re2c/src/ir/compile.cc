#include <algorithm>
#include <ostream>
#include <set>

#include "src/codegen/output.h"
#include "src/ir/compile.h"
#include "src/ir/adfa/adfa.h"
#include "src/ir/adfa/dump.h"
#include "src/ir/dfa/dfa.h"
#include "src/ir/dfa/dump.h"
#include "src/ir/nfa/nfa.h"
#include "src/ir/regexp/regexp.h"
#include "src/ir/skeleton/skeleton.h"

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

smart_ptr<DFA> compile(const spec_t &spec, Output &output)
{
	const opt_t *opts = output.source.block().opts;
	Warn &warn = output.source.warn;
	const std::vector<RegExpRule> &rules = spec.rules;
	const size_t defrule = spec.defs.empty()
		? Rule::NONE
		: rules.size() - 1;
	const uint32_t line = output.source.block().line;
	const std::string
		&cond = spec.name,
		name = make_name(cond, line),
		&setup = spec.setup.empty() ? "" : spec.setup[0]->text;

	RESpec re(rules);
	split_charset(re, opts);
	find_fixed_tags(re, opts);
	insert_default_tags(re);
	warn_nullable(re, cond, warn);

	nfa_t nfa(re);
	if (opts->dump_nfa) dump_nfa(nfa);

	dfa_t dfa(nfa, opts, cond, warn);
	if (opts->dump_dfa_det) dump_dfa(dfa);

	// skeleton must be constructed after DFA construction
	// but prior to any other DFA transformations
	Skeleton skeleton(dfa, opts, defrule, name, cond, line);
	warn_undefined_control_flow(skeleton, warn);
	if (opts->target == opt_t::SKELETON) {
		emit_data(skeleton);
	}

	cutoff_dead_rules(dfa, defrule, cond, warn);

	insert_fallback_tags(dfa);

	// try to minimize the number of tag variables
	optimize_tags(dfa);
	if (opts->dump_dfa_tagopt) dump_dfa(dfa);

	minimization(dfa, opts->dfa_minimization);
	if (opts->dump_dfa_min) dump_dfa(dfa);

	// find YYFILL states and calculate argument to YYFILL
	std::vector<size_t> fill;
	fillpoints(dfa, fill);

	// ADFA stands for 'DFA with actions'
	DFA *adfa = new DFA(dfa, fill, defrule, skeleton.sizeof_key,
		name, cond, line, setup);

	// see note [reordering DFA states]
	adfa->reorder();

	// skeleton is constructed, do further DFA transformations
	adfa->prepare(opts);
	if (opts->dump_adfa) dump_adfa(*adfa);

	// finally gather overall DFA statistics
	adfa->calc_stats(line, opts->tags);

	// accumulate global statistics from this particular DFA
	output.max_fill = std::max (output.max_fill, adfa->max_fill);
	if (adfa->need_accept)
	{
		output.source.block().used_yyaccept = true;
	}

	return make_smart_ptr(adfa);
}

} // namespace re2c
