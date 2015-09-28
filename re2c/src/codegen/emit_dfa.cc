#include <assert.h>

#include "src/codegen/bitmap.h"
#include "src/codegen/emit.h"
#include "src/codegen/go.h"
#include "src/codegen/indent.h"
#include "src/codegen/input_api.h"
#include "src/codegen/skeleton/skeleton.h"

namespace re2c
{

static std::string genGetCondition ();
static void genCondGotoSub (OutputFile & o, uint32_t ind, const std::vector<std::string> & condnames, uint32_t cMin, uint32_t cMax);
static void genCondTable   (OutputFile & o, uint32_t ind, const std::vector<std::string> & condnames);
static void genCondGoto    (OutputFile & o, uint32_t ind, const std::vector<std::string> & condnames);
static void emit_state     (OutputFile & o, uint32_t ind, const State * s, bool used_label);

std::string genGetCondition()
{
	return opts->cond_get_naked
		? opts->cond_get
		: opts->cond_get + "()";
}

void genGoTo(OutputFile & o, uint32_t ind, const State *from, const State *to, bool & readCh)
{
	if (opts->target == opt_t::DOT)
	{
		o << from->label << " -> " << to->label << "\n";
		return;
	}

	if (readCh && from->next != to)
	{
		o << opts->input_api.stmt_peek (ind);
		readCh = false;
	}

	o << indent(ind) << "goto " << opts->labelPrefix << to->label << ";\n";
}

void emit_state (OutputFile & o, uint32_t ind, const State * s, bool used_label)
{
	if (opts->target != opt_t::DOT)
	{
		if (used_label)
		{
			o << opts->labelPrefix << s->label << ":\n";
		}
		if (opts->dFlag && (s->action.type != Action::INITIAL))
		{
			o << indent(ind) << opts->yydebug << "(" << s->label << ", " << opts->input_api.expr_peek () << ");\n";
		}
		if (s->isPreCtxt)
		{
			o << opts->input_api.stmt_backupctx (ind);
		}
	}
}

void DFA::count_used_labels (std::set<label_t> & used, label_t start, label_t initial, bool force_start) const
{
	// In '-f' mode, default state is always state 0
	if (opts->fFlag)
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
		used.insert (accepts[i]->label);
	}
	// must go last: it needs the set of used labels
	if (used.count (head->label))
	{
		used.insert (initial);
	}
}

void DFA::emit_body (OutputFile & o, uint32_t& ind, const std::set<label_t> & used_labels) const
{
	const bool save_yyaccept = accepts.size () > 1;
	for (State * s = head; s; s = s->next)
	{
		bool readCh = false;
		emit_state (o, ind, s, used_labels.count (s->label));
		emit_action (s->action, o, ind, readCh, s, cond, name, used_labels, save_yyaccept);
		s->go.emit(o, ind, readCh);
	}
}

void DFA::emit(Output & output, uint32_t& ind, bool isLastCond, bool& bPrologBrace)
{
	OutputFile & o = output.source;

	bool bProlog = (!opts->cFlag || !bWroteCondCheck);

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
	count_used_labels (used_labels, start_label, initial_label, o.get_force_start_label ());

	head->action.set_initial (initial_label, head->action.type == Action::SAVE);

	skeleton->warn_undefined_control_flow ();

	if (opts->target == opt_t::SKELETON)
	{
		skeleton->emit_data (o.file_name);
		skeleton->emit_start (o, max_fill, need_backup, need_backupctx, need_accept);
		uint32_t i = 2;
		emit_body (o, i, used_labels);
		skeleton->emit_end (o, need_backup, need_backupctx);
	}
	else
	{
		// Generate prolog
		if (bProlog)
		{
			o << "\n";
			o.insert_line_info ();
			if (opts->target == opt_t::DOT)
			{
				bPrologBrace = true;
				o << "digraph re2c {\n";
			}
			else if ((!opts->fFlag && o.get_used_yyaccept ())
			||  (!opts->fFlag && opts->bEmitYYCh)
			||  (opts->bFlag && !opts->cFlag && BitMap::first)
			||  (opts->cFlag && !bWroteCondCheck && opts->gFlag)
			||  (opts->fFlag && !bWroteGetState && opts->gFlag)
			)
			{
				bPrologBrace = true;
				o << indent(ind++) << "{\n";
			}
			else if (ind == 0)
			{
				ind = 1;
			}
			if (!opts->fFlag && opts->target != opt_t::DOT)
			{
				if (opts->bEmitYYCh)
				{
					o << indent(ind) << opts->yyctype << " " << opts->yych << ";\n";
				}
				o.insert_yyaccept_init (ind);
			}
			else
			{
				o << "\n";
			}
		}
		if (opts->bFlag && !opts->cFlag && BitMap::first)
		{
			BitMap::gen(o, ind, lbChar, ubChar <= 256 ? ubChar : 256);
		}
		if (bProlog)
		{
			if (opts->cFlag && !bWroteCondCheck && opts->gFlag)
			{
				genCondTable(o, ind, output.types);
			}
			o.insert_state_goto (ind);
			if (opts->cFlag && opts->target != opt_t::DOT)
			{
				if (used_labels.count(start_label))
				{
					o << opts->labelPrefix << start_label << ":\n";
				}
			}
			o.write_user_start_label ();
			if (opts->cFlag && !bWroteCondCheck)
			{
				genCondGoto(o, ind, output.types);
			}
		}
		if (opts->cFlag && !cond.empty())
		{
			if (opts->condDivider.length())
			{
				o << replaceParam(opts->condDivider, opts->condDividerParam, cond) << "\n";
			}
			if (opts->target == opt_t::DOT)
			{
				o << cond << " -> " << head->label << "\n";
			}
			else
			{
				o << opts->condPrefix << cond << ":\n";
			}
		}
		if (opts->cFlag && opts->bFlag && BitMap::first)
		{
			o << indent(ind++) << "{\n";
			BitMap::gen(o, ind, lbChar, ubChar <= 256 ? ubChar : 256);
		}
		// If DFA has transitions to initial state, then initial state
		// has a piece of code that advances input position. Wee must
		// skip it when entering DFA.
		if (used_labels.count(head->label))
		{
			o << indent(ind) << "goto " << opts->labelPrefix << initial_label << ";\n";
		}
		// Generate code
		emit_body (o, ind, used_labels);
		if (opts->cFlag && opts->bFlag && BitMap::first)
		{
			o << indent(--ind) << "}\n";
		}
		// Generate epilog
		if ((!opts->cFlag || isLastCond) && bPrologBrace)
		{
			o << indent(--ind) << "}\n";
		}
	}

	// Cleanup
	if (BitMap::first)
	{
		delete BitMap::first;
		BitMap::first = NULL;
	}
}

void genCondTable(OutputFile & o, uint32_t ind, const std::vector<std::string> & condnames)
{
	const size_t conds = condnames.size ();
	o << indent(ind++) << "static void *" << opts->yyctable << "[" << conds << "] = {\n";
	for (size_t i = 0; i < conds; ++i)
	{
		o << indent(ind) << "&&" << opts->condPrefix << condnames[i] << ",\n";
	}
	o << indent(--ind) << "};\n";
}

void genCondGotoSub(OutputFile & o, uint32_t ind, const std::vector<std::string> & condnames, uint32_t cMin, uint32_t cMax)
{
	if (cMin == cMax)
	{
		o << indent(ind) << "goto " << opts->condPrefix << condnames[cMin] << ";\n";
	}
	else
	{
		uint32_t cMid = cMin + ((cMax - cMin + 1) / 2);

		o << indent(ind) << "if (" << genGetCondition() << " < " << cMid << ") {\n";
		genCondGotoSub(o, ind + 1, condnames, cMin, cMid - 1);
		o << indent(ind) << "} else {\n";
		genCondGotoSub(o, ind + 1, condnames, cMid, cMax);
		o << indent(ind) << "}\n";
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
	const size_t conds = condnames.size ();
	if (opts->target == opt_t::DOT)
	{
		o.warn_condition_order = false; // see note [condition order]
		for (size_t i = 0; i < conds; ++i)
		{
			const std::string cond = condnames[i];
			o << "0 -> " << cond << " [label=\"state=" << cond << "\"]\n";
		}
	}
	else if (opts->gFlag)
	{
		o << indent(ind) << "goto *" << opts->yyctable << "[" << genGetCondition() << "];\n";
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
		o << indent(ind) << "switch (" << genGetCondition() << ") {\n";
		for (size_t i = 0; i < conds; ++i)
		{
			const std::string & cond = condnames[i];
			o << indent(ind) << "case " << opts->condEnumPrefix << cond << ": goto " << opts->condPrefix << cond << ";\n";
		}
		o << indent(ind) << "}\n";
	}
	o.insert_warn_condition_order ();
	bWroteCondCheck = true;
}

} // end namespace re2c
