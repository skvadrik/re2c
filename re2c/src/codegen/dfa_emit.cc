#include <assert.h>

#include "src/codegen/bitmap.h"
#include "src/codegen/go.h"
#include "src/codegen/indent.h"
#include "src/codegen/input_api.h"
#include "src/codegen/skeleton/skeleton.h"
#include "src/dfa/dfa.h"

namespace re2c
{

// there must be at least one span in list;  all spans must cover
// same range

template<typename _Ty>
std::string replaceParam(std::string str, const std::string& param, const _Ty& value)
{
	std::ostringstream strValue;

	strValue << value;

	std::string::size_type pos;

	while((pos = str.find(param)) != std::string::npos)
	{
		str.replace(pos, param.length(), strValue.str());
	}

	return str;
}

static void genYYFill(OutputFile & o, uint32_t, uint32_t need)
{
	if (bUseYYFillParam)
	{
		o << mapCodeName["YYFILL"];
		if (!bUseYYFillNaked)
		{
			o << "(" << need << ");";
		}
		o << "\n";
	}
	else
	{
		o << replaceParam(mapCodeName["YYFILL"], yyFillLength, need);
		if (!bUseYYFillNaked)
		{
			o << ";";
		}
		o << "\n";
	}
}

static std::string genGetState()
{
	if (bUseYYGetStateNaked)
	{
		return mapCodeName["YYGETSTATE"];
	}
	else
	{
		return mapCodeName["YYGETSTATE"] + "()";
	}
}

static std::string genGetCondition()
{
	if (bUseYYGetConditionNaked)
	{
		return mapCodeName["YYGETCONDITION"];
	}
	else
	{
		return mapCodeName["YYGETCONDITION"] + "()";
	}
}

static void genSetCondition(OutputFile & o, uint32_t ind, const std::string& newcond)
{
	if (bUseYYSetConditionParam)
	{
		o << indent(ind) << mapCodeName["YYSETCONDITION"] << "(" << condEnumPrefix << newcond << ");\n";
	}
	else
	{
		o << indent(ind) << replaceParam(mapCodeName["YYSETCONDITION"], yySetConditionParam, condEnumPrefix + newcond) << "\n";
	}
}

static void genGoTo(OutputFile & o, uint32_t ind, const State *from, const State *to, bool & readCh)
{
	if (DFlag)
	{
		o << from->label << " -> " << to->label << "\n";
		return;
	}

	if (readCh && from->label + 1 != to->label)
	{
		o << input_api.stmt_peek (ind);
		readCh = false;
	}

	o << indent(ind) << "goto " << labelPrefix << to->label << ";\n";
	vUsedLabels.insert(to->label);
}

static void need(OutputFile & o, uint32_t ind, uint32_t n, bool & readCh, bool bSetMarker)
{
	if (DFlag)
	{
		return;
	}

	uint32_t fillIndex = next_fill_index;

	if (fFlag)
	{
		next_fill_index++;
		if (bUseYYSetStateParam)
		{
			o << indent(ind) << mapCodeName["YYSETSTATE"] << "(" << fillIndex << ");\n";
		}
		else
		{
			o << indent(ind) << replaceParam(mapCodeName["YYSETSTATE"], yySetStateParam, fillIndex) << "\n";
		}
	}

	if (bUseYYFill && n > 0)
	{
		o << indent(ind);
		if (n == 1)
		{
			if (bUseYYFillCheck)
			{
				o << "if (" << input_api.expr_lessthan_one () << ") ";
			}
			genYYFill(o, ind, n);
		}
		else
		{
			if (bUseYYFillCheck)
			{
				o << "if (" << input_api.expr_lessthan (n) << ") ";
			}
			genYYFill(o, ind, n);
		}
	}

	if (fFlag)
	{
		o << mapCodeName["yyFillLabel"] << fillIndex << ":\n";
	}

	if (n > 0)
	{
		if (bSetMarker)
		{
			o << input_api.stmt_backup_peek (ind);
		}
		else
		{
			o << input_api.stmt_peek (ind);
		}
		readCh = false;
	}
}

void Match::emit(Output & output, uint32_t ind, bool &readCh, const std::string&) const
{
	OutputFile & o = output.source;

	if (DFlag)
	{
		return;
	}

	if (state->link)
	{
		o << input_api.stmt_skip (ind);
	}
	else if (!readAhead())
	{
		/* do not read next char if match */
		o << input_api.stmt_skip (ind);
		readCh = true;
	}
	else
	{
		o << input_api.stmt_skip_peek (ind);
		readCh = false;
	}

	if (state->link)
	{
		need(o, ind, state->depth, readCh, false);
	}
}

void Initial::emit(Output & output, uint32_t ind, bool &readCh, const std::string&) const
{
	OutputFile & o = output.source;

	if (!cFlag && !startLabelName.empty())
	{
		o << startLabelName << ":\n";
	}

	if (vUsedLabels.count(label+1))
	{
		if (state->link)
		{
			o << input_api.stmt_skip (ind);
		}
		else
		{
			o << input_api.stmt_skip_peek (ind);
		}
	}

	if (vUsedLabels.count(label))
	{
		o << labelPrefix << label << ":\n";
	}
	else if (!label)
	{
		o << "\n";
	}

	if (dFlag)
	{
		o << indent(ind) << mapCodeName["YYDEBUG"] << "(" << label << ", *" << mapCodeName["YYCURSOR"] << ");" << "\n";
	}

	if (state->link)
	{
		need(o, ind, state->depth, readCh, setMarker && bUsedYYMarker);
	}
	else
	{
		if (setMarker && bUsedYYMarker)
		{
			o << input_api.stmt_backup (ind);
		}
		readCh = false;
	}
}

void Save::emit(Output & output, uint32_t ind, bool &readCh, const std::string&) const
{
	OutputFile & o = output.source;

	if (DFlag)
	{
		return;
	}

	o.insert_yyaccept_selector (ind, selector);

	if (state->link)
	{
		if (bUsedYYMarker)
		{
			o << input_api.stmt_skip_backup (ind);
		}
		need(o, ind, state->depth, readCh, false);
	}
	else
	{
		if (bUsedYYMarker)
		{
			o << input_api.stmt_skip_backup_peek (ind);
		}
		else
		{
			o << input_api.stmt_skip_peek (ind);
		}
		readCh = false;
	}
}

void Move::emit(Output &, uint32_t, bool &, const std::string&) const
{
	;
}

void Accept::genRuleMap()
{
	for (uint32_t i = 0; i < nRules; ++i)
	{
		if (saves[i] != ~0u)
		{
			mapRules[saves[i]] = rules[i];
		}
	}
}

void Accept::emitBinary(OutputFile & o, uint32_t ind, uint32_t l, uint32_t r, bool &readCh) const
{
	if (l < r)
	{
		uint32_t m = (l + r) >> 1;

		o << indent(ind) << "if (" << mapCodeName["yyaccept"] << (r == l+1 ? " == " : " <= ") << m << ") {\n";
		emitBinary(o, ++ind, l, m, readCh);
		o << indent(--ind) << "} else {\n";
		emitBinary(o, ++ind, m + 1, r, readCh);
		o << indent(--ind) << "}\n";
	}
	else
	{
		genGoTo(o, ind, state, mapRules.find(l)->second, readCh);
	}
}

void Accept::emit(Output & output, uint32_t ind, bool &readCh, const std::string &) const
{
	OutputFile & o = output.source;

	if (mapRules.size() > 0)
	{
		bUsedYYMarker = true;
		if (!DFlag)
		{
			o << input_api.stmt_restore (ind);
		}

		if (readCh) // shouldn't be necessary, but might become at some point
		{
			o << input_api.stmt_peek (ind);
			readCh = false;
		}

		if (mapRules.size() > 1)
		{
			o.set_used_yyaccept ();

			if (gFlag && mapRules.size() >= cGotoThreshold)
			{
				o << indent(ind++) << "{\n";
				o << indent(ind++) << "static void *" << mapCodeName["yytarget"] << "[" << mapRules.size() << "] = {\n";
				for (RuleMap::const_iterator it = mapRules.begin(); it != mapRules.end(); ++it)
				{
					o << indent(ind) << "&&" << labelPrefix << it->second->label << ",\n";
					vUsedLabels.insert(it->second->label);
				}
				o << indent(--ind) << "};\n";
				o << indent(ind) << "goto *" << mapCodeName["yytarget"] << "[" << mapCodeName["yyaccept"] << "];\n";
				o << indent(--ind) << "}\n";
			}
			else if (sFlag || (mapRules.size() == 2 && !DFlag))
			{
				emitBinary(o, ind, 0, mapRules.size() - 1, readCh);
			}
			else if (DFlag)
			{
				for (RuleMap::const_iterator it = mapRules.begin(); it != mapRules.end(); ++it)
				{
					o << state->label << " -> " << it->second->label;
					o << " [label=\"yyaccept=" << it->first << "\"]\n";
				}
			}
			else
			{
				o << indent(ind) << "switch (" << mapCodeName["yyaccept"] << ") {\n";

				RuleMap::const_iterator it = mapRules.begin(), end = mapRules.end();
		
				while (it != end)
				{
					RuleMap::const_iterator tmp = it;

					if (++it == end)
					{
						o << indent(ind) << "default:\t";
					}
					else
					{
						o << indent(ind) << "case " << tmp->first << ": \t";
					}

					genGoTo(o, 0, state, tmp->second, readCh);
				}
			
				o << indent(ind) << "}\n";
			}
		}
		else
		{
			// no need to write if statement here since there is only case 0.
			genGoTo(o, ind, state, mapRules.find(0)->second, readCh);
		}
	}
}

void Rule::emit(Output & output, uint32_t ind, bool &, const std::string& condName) const
{
	OutputFile & o = output.source;

	if (DFlag)
	{
		o << state->label << " [label=\"" << rule->code->source << ":" << rule->code->line << "\"]\n";
		return;
	}

	uint32_t back = rule->ctx->fixedLength();

	if (back != 0u && !DFlag)
	{
		o << input_api.stmt_restorectx (ind);
	}

	if (rule->code->newcond.length() && condName != rule->code->newcond)
	{
		genSetCondition(o, ind, rule->code->newcond);
	}

	if (!yySetupRule.empty() && !rule->code->autogen)
	{
		o << indent(ind) << yySetupRule << "\n";
	}

	o.write_line_info (rule->code->line, rule->code->source.c_str ());
	o << indent(ind);
	if (flag_skeleton)
	{
		o << "{ if (cursor == &data[result[i].endpos] && result[i].rule == " << rule->accept << ") ";
		o << "{ cursor = &data[result[i].startpos]; continue; }";
		o << " else ";
		o << "{ printf (\"error: %lu/%u, %u/%u, '%s'\\n\", cursor - data, result[i].endpos, result[i].rule, "
			<< rule->accept
			<< ", &data[result[i].startpos]); return 1; } }";
	}
	else if (rule->code->autogen)
	{
		o << replaceParam(condGoto, condGotoParam, condPrefix + rule->code->newcond);
	}
	else
	{
		o << rule->code->text;
	}
	o << "\n";
	o.insert_line_info ();
}

void State::emit(Output & output, uint32_t ind, bool &readCh, const std::string& condName) const
{
	OutputFile & o = output.source;

	if (vUsedLabels.count(label))
	{
		o << labelPrefix << label << ":\n";
	}
	if (dFlag && (action->type != Action::INITIAL))
	{
		o << indent(ind) << mapCodeName["YYDEBUG"] << "(" << label << ", " << input_api.expr_peek () << ");\n";
	}
	if (isPreCtxt && !DFlag)
	{
		o << input_api.stmt_backupctx (ind);
	}
	action->emit(output, ind, readCh, condName);
}

void DFA::emit(Output & output, uint32_t& ind, const RegExpMap* specMap, const std::string& condName, bool isLastCond, bool& bPrologBrace)
{
	OutputFile & o = output.source;

	bool bProlog = (!cFlag || !bWroteCondCheck);

	// In -c mode, the prolog needs its own label separate from start_label.
	// prolog_label is before the condition branch (GenCondGoto). It is
	// equivalent to startLabelName.
	// start_label corresponds to current condition.
	// NOTE: prolog_label must be yy0 because of the !getstate:re2c handling
	// in scanner.re
	uint32_t prolog_label = next_label;
	if (bProlog && cFlag)
	{
		next_label++;
	}

	uint32_t start_label = next_label;

	(void) new Initial(head, next_label++, bSaveOnHead);

	if (bUseStartLabel)
	{
		if (startLabelName.empty())
		{
			vUsedLabels.insert(prolog_label);
		}
	}

	State *s;

	for (s = head; s; s = s->next)
	{
		s->label = next_label++;
	}

	for (s = head; s; s = s->next)
	{
		s->go.used_labels ();
	}

	// Save 'next_fill_index' and compute information about code generation
	// while writing to null device.
	uint32_t save_fill_index = next_fill_index;
	Output null_dev (NULL, NULL);

	for (s = head; s; s = s->next)
	{
		bool readCh = false;
		s->emit(null_dev, ind, readCh, condName);
		s->go.emit(null_dev.source, ind, readCh);
	}
	if (last_fill_index < next_fill_index)
	{
		last_fill_index = next_fill_index;
	}
	next_fill_index = save_fill_index;

	// Generate prolog
	if (bProlog)
	{
		o << "\n";
		o.insert_line_info ();

		if (DFlag)
		{
			bPrologBrace = true;
			o << "digraph re2c {\n";
		}
		else if ((!fFlag && o.get_used_yyaccept ())
		||  (!fFlag && bEmitYYCh)
		||  (bFlag && !cFlag && BitMap::first)
		||  (cFlag && !bWroteCondCheck && gFlag && !specMap->empty())
		||  (fFlag && !bWroteGetState && gFlag)
		)
		{
			bPrologBrace = true;
			o << indent(ind++) << "{\n";
		}
		else if (ind == 0)
		{
			ind = 1;
		}

		if (!fFlag && !DFlag)
		{
			if (bEmitYYCh)
			{
				o << indent(ind) << mapCodeName["YYCTYPE"] << " " << mapCodeName["yych"] << ";\n";
			}
			o.insert_yyaccept_init (ind);
		}
		else
		{
			o << "\n";
		}
	}
	if (bFlag && !cFlag && BitMap::first)
	{
		BitMap::gen(o, ind, lbChar, ubChar <= 256 ? ubChar : 256);
	}
	if (bProlog)
	{
		genCondTable(o, ind, *specMap);
		o.insert_state_goto (ind, prolog_label);
		if (cFlag && !DFlag)
		{
			if (vUsedLabels.count(prolog_label))
			{
				o << labelPrefix << prolog_label << ":\n";
			}
			if (!startLabelName.empty())
			{
				o << startLabelName << ":\n";
			}
		}
		genCondGoto(o, ind, *specMap);
	}

	if (cFlag && !condName.empty())
	{
		if (condDivider.length())
		{
			o << replaceParam(condDivider, condDividerParam, condName) << "\n";
		}

		if (DFlag)
		{
			o << condName << " -> " << (start_label+1) << "\n";
		}
		else
		{
			o << condPrefix << condName << ":\n";
		}
	}
	if (cFlag && bFlag && BitMap::first)
	{
		o << indent(ind++) << "{\n";
		BitMap::gen(o, ind, lbChar, ubChar <= 256 ? ubChar : 256);
	}

	// The start_label is not always the first to be emitted, so we may have to jump. c.f. Initial::emit()
	if (vUsedLabels.count(start_label+1))
	{
		vUsedLabels.insert(start_label);
		o << indent(ind) << "goto " << labelPrefix << start_label << ";\n";
	}

	// Generate code
	for (s = head; s; s = s->next)
	{
		bool readCh = false;
		s->emit(output, ind, readCh, condName);
		s->go.emit(o, ind, readCh);
	}

	if (cFlag && bFlag && BitMap::first)
	{
		o << indent(--ind) << "}\n";
	}
	// Generate epilog
	if ((!cFlag || isLastCond) && bPrologBrace)
	{
		o << indent(--ind) << "}\n";
	}
	if (flag_skeleton)
	{
		skeleton::emit_epilog (o, ind);
	}

	// Cleanup
	if (BitMap::first)
	{
		delete BitMap::first;
		BitMap::first = NULL;
	}

	bUseStartLabel = false;
}

static void output_state_goto_sub (std::ostream & o, uint32_t ind, uint32_t start_label, int cMin, int cMax)
{
	if (cMin == cMax)
	{
		if (cMin == -1)
		{
			o << indent(ind) << "goto " << labelPrefix << start_label << ";\n";
		}
		else
		{
			o << indent(ind) << "goto " << mapCodeName["yyFillLabel"] << cMin << ";\n";
		}
	}
	else
	{
		int cMid = cMin + ((cMax - cMin + 1) / 2);

		o << indent(ind) << "if (" << genGetState() << " < " << cMid << ") {\n";
		output_state_goto_sub (o, ind + 1, start_label, cMin, cMid - 1);
		o << indent(ind) << "} else {\n";
		output_state_goto_sub (o, ind + 1, start_label, cMid, cMax);
		o << indent(ind) << "}\n";
	}
}

void output_state_goto (std::ostream & o, uint32_t ind, uint32_t start_label)
{
	if (gFlag)
	{
		o << indent(ind++) << "static void *" << mapCodeName["yystable"] << "[" << "] = {\n";

		for (size_t i=0; i<last_fill_index; ++i)
		{
			o << indent(ind) << "&&" << mapCodeName["yyFillLabel"] << i << ",\n";
		}

		o << indent(--ind) << "};\n";
		o << "\n";

		o << indent(ind) << "if (" << genGetState();
		if (bUseStateAbort)
		{
			o << " == -1) {\n";
		}
		else
		{
			o << " < 0) {\n";
		}
		o << indent(++ind) << "goto " << labelPrefix << start_label << ";\n";
		if (bUseStateAbort)
		{
			o << indent(--ind) << "} else if (" << genGetState() << " < -1) {\n";
			o << indent(++ind) << "abort();\n";
		}
		o << indent(--ind) << "}\n";

		o << indent(ind) << "goto *" << mapCodeName["yystable"] << "[" << genGetState() << "];\n";

	}
	else if (bFlag)
	{
		output_state_goto_sub (o, ind, start_label, -1, last_fill_index-1);
		if (bUseStateAbort)
		{
			o << indent(ind) << "abort();\n";
		}
	}
	else
	{
		o << indent(ind) << "switch (" << genGetState() << ") {\n";
		if (bUseStateAbort)
		{
			o << indent(ind) << "default: abort();\n";
			o << indent(ind) << "case -1: goto " << labelPrefix << start_label << ";\n";
		}
		else
		{
			o << indent(ind) << "default: goto " << labelPrefix << start_label << ";\n";
		}

		for (size_t i=0; i<last_fill_index; ++i)
		{
			o << indent(ind) << "case " << i << ": goto " << mapCodeName["yyFillLabel"] << i << ";\n";
		}

		o << indent(ind) << "}\n";
	}
	if (bUseStateNext)
	{
		o << mapCodeName["yyNext"] << ":\n";
	}
}

void genCondTable(OutputFile & o, uint32_t ind, const RegExpMap& specMap)
{
	if (cFlag && !bWroteCondCheck && gFlag && specMap.size())
	{
		RegExpIndices  vCondList(specMap.size());

		for(RegExpMap::const_iterator itSpec = specMap.begin(); itSpec != specMap.end(); ++itSpec)
		{
			vCondList[itSpec->second.first] = itSpec->first;
		}

		o << indent(ind++) << "static void *" << mapCodeName["yyctable"] << "[" << specMap.size() << "] = {\n";

		for(RegExpIndices::const_iterator it = vCondList.begin(); it != vCondList.end(); ++it)
		{
			o << indent(ind) << "&&" << condPrefix << *it << ",\n";
		}
		o << indent(--ind) << "};\n";
	}
}

static void genCondGotoSub(OutputFile & o, uint32_t ind, RegExpIndices& vCondList, uint32_t cMin, uint32_t cMax)
{
	if (cMin == cMax)
	{
		o << indent(ind) << "goto " << condPrefix << vCondList[cMin] << ";\n";
	}
	else
	{
		uint32_t cMid = cMin + ((cMax - cMin + 1) / 2);

		o << indent(ind) << "if (" << genGetCondition() << " < " << cMid << ") {\n";
		genCondGotoSub(o, ind + 1, vCondList, cMin, cMid - 1);
		o << indent(ind) << "} else {\n";
		genCondGotoSub(o, ind + 1, vCondList, cMid, cMax);
		o << indent(ind) << "}\n";
	}
}

void genCondGoto(OutputFile & o, uint32_t ind, const RegExpMap& specMap)
{
	if (cFlag && !bWroteCondCheck && specMap.size())
	{
		if (gFlag)
		{
			o << indent(ind) << "goto *" << mapCodeName["yyctable"] << "[" << genGetCondition() << "];\n";
		}
		else
		{
			if (sFlag)
			{
				RegExpIndices  vCondList(specMap.size());
			
				for(RegExpMap::const_iterator it = specMap.begin(); it != specMap.end(); ++it)
				{
					vCondList[it->second.first] = it->first;
				}
				genCondGotoSub(o, ind, vCondList, 0, vCondList.size() - 1);
			}
			else if (DFlag)
			{
				for(RegExpMap::const_iterator it = specMap.begin(); it != specMap.end(); ++it)
				{
					o << "0 -> " << it->first << " [label=\"state=" << it->first << "\"]\n";
				}
			}
			else
			{
				o << indent(ind) << "switch (" << genGetCondition() << ") {\n";
	
				for(RegExpMap::const_iterator it = specMap.begin(); it != specMap.end(); ++it)
				{
					o << indent(ind) << "case " << condEnumPrefix << it->first << ": goto " << condPrefix << it->first << ";\n";
				}
				o << indent(ind) << "}\n";
			}
		}
		bWroteCondCheck = true;
	}
}

void genTypes(Output & output, const RegExpMap& specMap)
{
	output.types.resize (specMap.size());
	for(RegExpMap::const_iterator itSpecMap = specMap.begin(); itSpecMap != specMap.end(); ++itSpecMap)
	{
		// If an entry is < 0 then we did the 0/empty correction twice.
		assert(itSpecMap->second.first >= 0);
		output.types[itSpecMap->second.first] = itSpecMap->first;
	}
}

void output_yyaccept_init (std::ostream & o, uint32_t ind, bool used_yyaccept)
{
	if (used_yyaccept)
	{
		o << indent (ind) << "unsigned int " << mapCodeName["yyaccept"] << " = 0;\n";
	}
}

void output_yyaccept_selector (std::ostream & o, uint32_t ind, bool used_yyaccept, uint32_t yyaccept_selector)
{
	if (used_yyaccept)
	{
		o << indent (ind) << mapCodeName["yyaccept"] << " = " << yyaccept_selector << ";\n";
	}
}

void output_yymaxfill (std::ostream & o, uint32_t max_fill)
{
	o << "#define YYMAXFILL " << max_fill << "\n";
}

void output_line_info (std::ostream & o, uint32_t line_number, const char * file_name)
{
	if (!iFlag)
	{
		o << "#line " << line_number << " \"" << file_name << "\"\n";
	}
}

void output_types (std::ostream & o, uint32_t ind, const std::vector<std::string> & types)
{
	o << indent (ind++) << "enum " << mapCodeName["YYCONDTYPE"] << " {\n";
	for (unsigned int i = 0; i < types.size (); ++i)
	{
		o << indent (ind) << condEnumPrefix << types[i] << ",\n";
	}
	o << indent (--ind) << "};\n";
}

void output_version_time (std::ostream & o)
{
	o << "/* Generated by re2c " PACKAGE_VERSION;
	if (!bNoGenerationDate)
	{
		o << " on ";
		time_t now = time (NULL);
		o.write (ctime (&now), 24);
	}
	o << "*/" << "\n";
}

} // end namespace re2c
