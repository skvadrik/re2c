#include "src/util/c99_stdint.h"
#include <stddef.h>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "src/codegen/bitmap.h"
#include "src/codegen/emit.h"
#include "src/codegen/go.h"
#include "src/codegen/input_api.h"
#include "src/codegen/label.h"
#include "src/codegen/output.h"
#include "src/ir/adfa/action.h"
#include "src/ir/adfa/adfa.h"
#include "src/ir/skeleton/skeleton.h"
#include "src/util/counter.h"
#include "src/util/string_utils.h"

namespace re2c
{

static std::string genGetCondition (Opt &opts);
static void genCondGotoSub (OutputFile & o, uint32_t ind, const std::vector<std::string> & condnames, uint32_t cMin, uint32_t cMax);
static void genCondTable   (OutputFile & o, uint32_t ind, const std::vector<std::string> & condnames);
static void genCondGoto    (OutputFile & o, uint32_t ind, const std::vector<std::string> & condnames);
static void emit_state     (OutputFile & o, uint32_t ind, const State * s, bool used_label);

std::string genGetCondition(Opt &opts)
{
	return opts->cond_get_naked
		? opts->cond_get
		: opts->cond_get + "()";
}

void emit_state (OutputFile & o, uint32_t ind, const State * s, bool used_label)
{
	Opt &opts = o.opts;
	if (used_label)
	{
		o.wstring(opts->labelPrefix).wlabel(s->label).ws(":\n");
	}
	if (opts->dFlag && (s->action.type != Action::INITIAL))
	{
		o.wind(ind).wstring(opts->yydebug).ws("(").wlabel(s->label).ws(", ").wstring(opts->input_api.expr_peek(opts)).ws(");\n");
	}
}

void DFA::count_used_labels (std::set<label_t> & used, label_t start,
	label_t initial, bool force_start, bool fFlag) const
{
	// In '-f' mode, default state is always state 0
	if (fFlag)
	{
		used.insert (label_t::first ());
	}
	if (force_start)
	{
		used.insert (start);
	}
	for (State * s = head; s; s = s->next)
	{
		s->go.used_labels (used);
	}
	for (uint32_t i = 0; i < accepts.size (); ++i)
	{
		used.insert (accepts[i].first->label);
	}
	// must go last: it needs the set of used labels
	if (used.count (head->label))
	{
		used.insert (initial);
	}
}

void DFA::emit_body(OutputFile &o, uint32_t& ind,
	const std::set<label_t> &used_labels, label_t initial) const
{
	// If DFA has transitions to initial state, then initial state
	// has a piece of code that advances input position. Wee must
	// skip it when entering DFA.
	if (used_labels.count(head->label)) {
		o.wind(ind).ws("goto ").wstring(o.opts->labelPrefix)
			.wlabel(initial).ws(";\n");
	}

	for (State * s = head; s; s = s->next) {
		emit_state(o, ind, s, used_labels.count(s->label));
		emit_action(o, ind, *this, s, used_labels);
		s->go.emit(o, ind, *this);
	}
}

void DFA::emit_dot(
	OutputFile &o,
	bool last_cond,
	const std::vector<std::string> &conds) const
{
	Opt &opts = o.opts;
	if (!opts->cFlag || !o.cond_goto) {
		o.ws("digraph re2c {\n");
	}
	if (opts->cFlag) {
		if (!o.cond_goto) {
			for (size_t i = 0; i < conds.size(); ++i) {
				const std::string &cond = conds[i];
				o.ws("0 -> ").wstring(cond)
					.ws(" [label=\"state=")
					.wstring(cond).ws("\"]\n");
			}
			o.cond_goto = true;
		}
		o.wstring(cond).ws(" -> ").wlabel(head->label).ws("\n");
	}
	for (State *s = head; s; s = s->next) {
		if (s->action.type == Action::ACCEPT) {
			const accept_t &accepts = *s->action.info.accepts;
			for (uint32_t i = 0; i < accepts.size(); ++i) {
				o.wlabel(s->label).ws(" -> ")
					.wlabel(accepts[i].first->label)
					.ws(" [label=\"yyaccept=")
					.wu32(i).ws("\"]").ws("\n");
			}
		} else if (s->action.type == Action::RULE) {
			const Code *code = rules[s->action.info.rule].info->code;
			if (code) {
				o.wlabel(s->label).ws(" [label=\"")
					.wstring(code->loc.filename)
					.ws(":").wu32(code->loc.line)
					.ws("\"]").ws("\n");
			}
		}
		s->go.emit(o, 0, *this);
	}
	if (!opts->cFlag || last_cond) {
		o.ws("}\n");
	}
}

void DFA::emit(Output & output, uint32_t& ind, bool isLastCond, bool& bPrologBrace)
{
	OutputFile &o = output.source;
	OutputBlock &ob = o.block();
	Opt &opts = o.opts;
	std::set<std::string> tagnames, tagvars;
	if (!oldstyle_ctxmarker) {
		for (size_t i = 0; i < vartags.size(); ++i) {
			const std::string *name = vartags[i].name;
			if (name) {
				tagvars.insert(*name);
			}
		}
		for (size_t i = 0; i < fixtags.size(); ++i) {
			const std::string *name = fixtags[i].name;
			if (name) {
				tagvars.insert(*name);
			}
		}
		for (tagver_t v = 1; v <= maxtagver; ++v) {
			tagnames.insert(vartag_name(v, opts->tags_prefix));
		}
		ob.tags.insert(tagnames.begin(), tagnames.end());
	}

	bool bProlog = (!opts->cFlag || !o.cond_goto);

	// start_label points to the beginning of current re2c block
	// (prior to condition dispatch in '-c' mode)
	// it can forced by configuration 're2c:startlabel = <integer>;'
	label_t start_label = o.label_counter.next ();
	// initial_label points to the beginning of DFA
	// in '-c' mode this is NOT equal to start_label
	label_t initial_label = bProlog && opts->cFlag
		? o.label_counter.next ()
		: start_label;
	for (State * s = head; s; s = s->next)
	{
		s->label = o.label_counter.next ();
	}
	std::set<label_t> used_labels;
	count_used_labels (used_labels, start_label, initial_label, ob.force_start_label, opts->fFlag);

	head->action.set_initial(initial_label);

	if (opts->target == opt_t::SKELETON) {
		if (output.skeletons.insert (name).second)
		{
			emit_start(o, max_fill, name, key_size, def_rule, need_backup,
				need_accept, oldstyle_ctxmarker, tagnames, tagvars, bitmaps);
			uint32_t i = 2;
			emit_body (o, i, used_labels, initial_label);
			emit_end(o, name, need_backup, oldstyle_ctxmarker);
		}
	} else if (opts->target == opt_t::DOT) {
		emit_dot(o, isLastCond, ob.types);
	} else {
		// Generate prolog
		if (bProlog)
		{
			o.ws("\n").wdelay_line_info ();
			if ((!opts->fFlag && ob.used_yyaccept)
			||  (!opts->fFlag && opts->bEmitYYCh)
			||  (opts->bFlag && !opts->cFlag && !bitmaps.empty())
			||  (opts->cFlag && !o.cond_goto && opts->gFlag)
			||  (opts->fFlag && !o.state_goto && opts->gFlag)
			)
			{
				bPrologBrace = true;
				o.wind(ind++).ws("{\n");
			}
			else if (ind == 0)
			{
				ind = 1;
			}
			if (!opts->fFlag)
			{
				if (opts->bEmitYYCh)
				{
					o.wind(ind).wstring(opts->yyctype).ws(" ").wstring(opts->yych).ws(";\n");
				}
				o.wdelay_yyaccept_init (ind);
			}
			else
			{
				o.ws("\n");
			}
		}
		if (opts->bFlag && !opts->cFlag)
		{
			bitmaps.gen(o, ind);
		}
		if (bProlog)
		{
			if (opts->cFlag && !o.cond_goto && opts->gFlag)
			{
				genCondTable(o, ind, ob.types);
			}
			o.wdelay_state_goto (ind);
			if (opts->cFlag)
			{
				if (used_labels.count(start_label))
				{
					o.wstring(opts->labelPrefix).wlabel(start_label).ws(":\n");
				}
			}
			o.wuser_start_label ();
			if (opts->cFlag && !o.cond_goto)
			{
				genCondGoto(o, ind, ob.types);
			}
		}
		if (opts->cFlag && !cond.empty())
		{
			if (opts->condDivider.length())
			{
				std::string divider = opts->condDivider;
				strrreplace(divider, opts->condDividerParam, cond);
				o.wstring(divider).ws("\n");
			}
			o.wstring(opts->condPrefix).wstring(cond).ws(":\n");
		}
		if (opts->cFlag && opts->bFlag && !bitmaps.empty())
		{
			o.wind(ind++).ws("{\n");
			bitmaps.gen(o, ind);
		}
		// Generate code
		emit_body (o, ind, used_labels, initial_label);
		if (opts->cFlag && opts->bFlag && !bitmaps.empty())
		{
			o.wind(--ind).ws("}\n");
		}
		// Generate epilog
		if ((!opts->cFlag || isLastCond) && bPrologBrace)
		{
			o.wind(--ind).ws("}\n");
		}
	}
}

void genCondTable(OutputFile & o, uint32_t ind, const std::vector<std::string> & condnames)
{
	Opt &opts = o.opts;
	const size_t conds = condnames.size ();
	o.wind(ind++).ws("static void *").wstring(opts->yyctable).ws("[").wu64(conds).ws("] = {\n");
	for (size_t i = 0; i < conds; ++i)
	{
		o.wind(ind).ws("&&").wstring(opts->condPrefix).wstring(condnames[i]).ws(",\n");
	}
	o.wind(--ind).ws("};\n");
}

void genCondGotoSub(OutputFile & o, uint32_t ind, const std::vector<std::string> & condnames, uint32_t cMin, uint32_t cMax)
{
	Opt &opts = o.opts;
	if (cMin == cMax)
	{
		o.wind(ind).ws("goto ").wstring(opts->condPrefix).wstring(condnames[cMin]).ws(";\n");
	}
	else
	{
		uint32_t cMid = cMin + ((cMax - cMin + 1) / 2);

		o.wind(ind).ws("if (").wstring(genGetCondition(opts)).ws(" < ").wu32(cMid).ws(") {\n");
		genCondGotoSub(o, ind + 1, condnames, cMin, cMid - 1);
		o.wind(ind).ws("} else {\n");
		genCondGotoSub(o, ind + 1, condnames, cMid, cMax);
		o.wind(ind).ws("}\n");
	}
}

/*
 * note [condition order]
 *
 * In theory re2c makes no guarantee about the order of conditions in
 * the generated lexer. Users should define condition type 'YYCONDTYPE'
 * and use values of this type with 'YYGETCONDITION' and 'YYSETCONDITION'.
 * This way code is independent of internal re2c condition numbering.
 *
 * However, it is possible to manually hardcode condition numbers and make
 * re2c generate condition dispatch without explicit use of condition names
 * (nested 'if' statements with '-b' or computed 'goto' table with '-g').
 * This code is syntactically valid (compiles), but unsafe:
 *     - change of re2c options may break compilation
 *     - change of internal re2c condition numbering may break runtime
 *
 * re2c has to preserve the existing numbering scheme.
 *
 * re2c warns about implicit assumptions about condition order, unless:
 *     - condition type is defined with 'types:re2c' or '-t, --type-header'
 *     - dispatch is independent of condition order: either it uses
 *       explicit condition names or there's only one condition and
 *       dispatch shrinks to unconditional jump
 */
void genCondGoto(OutputFile & o, uint32_t ind, const std::vector<std::string> & condnames)
{
	Opt &opts = o.opts;
	const size_t conds = condnames.size ();
	if (opts->gFlag)
	{
		o.wind(ind).ws("goto *").wstring(opts->yyctable).ws("[").wstring(genGetCondition(opts)).ws("];\n");
	}
	else if (opts->sFlag)
	{
		if (conds == 1)
		{
			o.warn_condition_order = false; // see note [condition order]
		}
		genCondGotoSub(o, ind, condnames, 0, static_cast<uint32_t> (conds) - 1);
	}
	else
	{
		o.warn_condition_order = false; // see note [condition order]
		o.wind(ind).ws("switch (").wstring(genGetCondition(opts)).ws(") {\n");
		for (size_t i = 0; i < conds; ++i)
		{
			const std::string & cond = condnames[i];
			o.wind(ind).ws("case ").wstring(opts->condEnumPrefix).wstring(cond).ws(": goto ").wstring(opts->condPrefix).wstring(cond).ws(";\n");
		}
		o.wind(ind).ws("}\n");
	}
	o.wdelay_warn_condition_order ();
	o.cond_goto = true;
}

std::string vartag_name(tagver_t ver, const std::string &prefix)
{
	std::ostringstream s;
	s << prefix << ver;
	return s.str();
}

std::string vartag_expr(tagver_t ver, const std::string &prefix, const std::string &expression)
{
	const std::string s = vartag_name(ver, prefix);
	std::string e = expression;
	strrreplace(e, "@@", s);
	return e;
}

} // end namespace re2c
