#include "src/util/c99_stdint.h"
#include <stddef.h>
#include <set>
#include <string>

#include "src/codegen/emit.h"
#include "src/codegen/input_api.h"
#include "src/codegen/output.h"
#include "src/conf/opt.h"
#include "src/globals.h"
#include "src/ir/adfa/action.h"
#include "src/ir/adfa/adfa.h"
#include "src/ir/regexp/regexp.h"
#include "src/ir/skeleton/skeleton.h"
#include "src/parse/code.h"
#include "src/parse/loc.h"
#include "src/util/strrreplace.h"
#include "src/util/to_string.h"

namespace re2c
{

class label_t;

static void need(OutputFile &o, uint32_t ind, bool &readCh, size_t n, bool bSetMarker);
static void emit_match(OutputFile &o, uint32_t ind, bool &readCh, const State *s);
static void emit_initial(OutputFile &o, uint32_t ind, bool &readCh, const State *s, const std::set<label_t> &used_labels);
static void emit_save(OutputFile &o, uint32_t ind, bool &readCh, const State *s, bool save_yyaccept);
static void emit_accept_binary(OutputFile &o, uint32_t ind, bool &readCh, const DFA &dfa, const State *s, size_t l, size_t r);
static void emit_accept(OutputFile &o, uint32_t ind, bool &readCh, const DFA &dfa, const State *s);
static void emit_rule(OutputFile &o, uint32_t ind, const DFA &dfa, size_t rule_idx);
static void genYYFill(OutputFile &o, size_t need);
static void genSetCondition(OutputFile &o, uint32_t ind, const std::string &cond);
static void genSetState(OutputFile &o, uint32_t ind, uint32_t fillIndex);
static void gen_goto(code_lines_t &code, bool &readCh, const State *to, const DFA &dfa, const tagcmd_t &tags, bool restore_fallback);

void emit_action(OutputFile &o, uint32_t ind, bool &readCh,
	const DFA &dfa, const State *s, const std::set<label_t> &used_labels)
{
	switch (s->action.type) {
		case Action::MATCH:
			emit_match(o, ind, readCh, s);
			break;
		case Action::INITIAL:
			emit_initial(o, ind, readCh, s, used_labels);
			break;
		case Action::SAVE:
			emit_save(o, ind, readCh, s, dfa.accepts.size() > 1);
			break;
		case Action::MOVE:
			break;
		case Action::ACCEPT:
			emit_accept(o, ind, readCh, dfa, s);
			break;
		case Action::RULE:
			emit_rule(o, ind, dfa, s->action.info.rule);
			break;
	}
}

void emit_match(OutputFile &o, uint32_t ind, bool &readCh, const State *s)
{
	const bool read_ahead = s
		&& s->next
		&& s->next->action.type != Action::RULE;

	if (s->fill != 0) {
		o.wstring(opts->input_api.stmt_skip(ind));
	} else if (!read_ahead) {
		/* do not read next char if match */
		o.wstring(opts->input_api.stmt_skip(ind));
		readCh = true;
	} else {
		o.wstring(opts->input_api.stmt_skip_peek(ind));
		readCh = false;
	}

	if (s->fill != 0) {
		need(o, ind, readCh, s->fill, false);
	}
}

void emit_initial(OutputFile &o, uint32_t ind, bool &readCh,
	const State *s, const std::set<label_t> &used_labels)
{
	if (used_labels.count(s->label)) {
		if (s->fill != 0) {
			o.wstring(opts->input_api.stmt_skip(ind));
		} else {
			o.wstring(opts->input_api.stmt_skip_peek(ind));
		}
	}

	const Initial &initial = *s->action.info.initial;
	if (used_labels.count(initial.label)) {
		o.wstring(opts->labelPrefix).wlabel(initial.label).ws(":\n");
	}

	if (opts->dFlag) {
		o.wind(ind).wstring(opts->yydebug).ws("(")
			.wlabel(initial.label).ws(", *")
			.wstring(opts->yycursor).ws(");\n");
	}

	if (s->fill != 0) {
		need(o, ind, readCh, s->fill, initial.setMarker);
	} else {
		if (initial.setMarker) {
			o.wstring(opts->input_api.stmt_backup(ind));
		}
		readCh = false;
	}
}

void emit_save(OutputFile &o, uint32_t ind, bool &readCh,
	const State *const s, bool save_yyaccept)
{
	if (save_yyaccept) {
		o.wind(ind).wstring(opts->yyaccept).ws(" = ")
			.wu64(s->action.info.save).ws(";\n");
	}

	if (s->fill != 0) {
		o.wstring(opts->input_api.stmt_skip_backup(ind));
		need(o, ind, readCh, s->fill, false);
	} else {
		o.wstring(opts->input_api.stmt_skip_backup_peek(ind));
		readCh = false;
	}
}

void emit_accept_binary(OutputFile &o, uint32_t ind, bool &readCh,
	const DFA &dfa, const State *s, size_t l, size_t r)
{
	if (l < r) {
		const size_t m = (l + r) >> 1;
		o.wind(ind).ws("if (").wstring(opts->yyaccept)
			.ws(r == l+1 ? " == " : " <= ").wu64(m).ws(") {\n");
		emit_accept_binary (o, ++ind, readCh, dfa, s, l, m);
		o.wind(--ind).ws("} else {\n");
		emit_accept_binary (o, ++ind, readCh, dfa, s, m + 1, r);
		o.wind(--ind).ws("}\n");
	} else {
		const accept_t &acc = *s->action.info.accepts;
		gen_goto_plain(o, ind, readCh, acc[l].first, dfa, acc[l].second, true);
	}
}

void emit_accept(OutputFile &o, uint32_t ind, bool &readCh,
	const DFA &dfa, const State *s)
{
	const accept_t &acc = *s->action.info.accepts;
	const size_t nacc = acc.size();

	if (nacc == 0) {
		return;
	}

	o.wstring(opts->input_api.stmt_restore(ind));
	if (readCh) {
		o.wstring(opts->input_api.stmt_peek(ind));
		readCh = false;
	}

	// only one possible 'yyaccept' value: unconditional jump
	if (nacc == 1) {
		gen_goto_plain(o, ind, readCh, acc[0].first, dfa, acc[0].second, true);
		return;
	}

	bool have_tags = false;
	for (size_t i = 0; i < nacc; ++i) {
		if (!acc[i].second.empty()) {
			have_tags = true;
			break;
		}
	}

	// jump table
	if (opts->gFlag && nacc >= opts->cGotoThreshold && !have_tags) {
		o.wind(ind).ws("{\n")
			.wind(ind + 1).ws("static void *")
			.wstring(opts->yytarget).ws("[")
			.wu64(nacc).ws("] = {\n");
		for (uint32_t i = 0; i < nacc; ++i) {
			o.wind(ind + 2).ws("&&").wstring(opts->labelPrefix)
				.wlabel(acc[i].first->label).ws(",\n");
		}
		o.wind(ind + 1).ws("};\n")
			.wind(ind + 1).ws("goto *")
			.wstring(opts->yytarget).ws("[")
			.wstring(opts->yyaccept).ws("];\n")
			.wind(ind).ws("}\n");
		return;
	}

	// nested ifs
	if (opts->sFlag || nacc == 2) {
		emit_accept_binary(o, ind, readCh, dfa, s, 0, nacc - 1);
		return;
	}

	// switch
	o.wind(ind).ws("switch (").wstring(opts->yyaccept).ws(") {\n");
	for (uint32_t i = 0; i < nacc - 1; ++i) {
		o.wind(ind).ws("case ").wu32(i).ws(": ");
		gen_goto_case(o, ind, readCh, acc[i].first, dfa, acc[i].second, true);
	}
	o.wind(ind).ws("default:");
	gen_goto_case(o, ind, readCh, acc[nacc - 1].first, dfa, acc[nacc - 1].second, true);
	o.wind(ind).ws("}\n");
}

void emit_rule(OutputFile &o, uint32_t ind, const DFA &dfa, size_t rule_idx)
{
	const Rule &rule = dfa.rules[rule_idx];
	const RuleInfo *info = rule.info;
	const std::valarray<Tag> &tags = dfa.tags;

	if (rule.trail != Tag::NONE) {
		o.wstring(opts->input_api.stmt_restorectx(ind, tags, tags[rule.trail], dfa.basetag));
	}
	for (size_t t = rule.ltag; t < rule.htag; ++t) {
		o.wstring(opts->input_api.stmt_tag_finalizer(ind, tags, tags[t]));
	}

	if (opts->target == opt_t::SKELETON) {
		emit_action(*dfa.skeleton, o, ind, rule_idx);
	} else {
		const std::string &cond = info->newcond;
		if (!cond.empty() && dfa.cond != cond) {
			genSetCondition(o, ind, cond);
		}
		const Code *code = info->code;
		if (code) {
			if (!yySetupRule.empty()) {
				o.wind(ind).wstring(yySetupRule).ws("\n");
			}
			o.wline_info(code->loc.line, code->loc.filename.c_str())
				.wind(ind).wstring(code->text).ws("\n")
				.wdelay_line_info();
		} else if (!cond.empty()) {
			std::string action = opts->condGoto;
			strrreplace(action, opts->condGotoParam, opts->condPrefix + cond);
			o.wind(ind).wstring(action).ws("\n");
		}
	}
}

void need(OutputFile &o, uint32_t ind, bool &readCh, size_t n, bool bSetMarker)
{
	uint32_t fillIndex = last_fill_index;

	if (opts->fFlag) {
		last_fill_index++;
		genSetState(o, ind, fillIndex);
	}

	if (opts->fill_use && n > 0) {
		o.wind(ind);
		if (n == 1) {
			if (opts->fill_check) {
				o.ws("if (").wstring(opts->input_api.expr_lessthan_one()).ws(") ");
			}
			genYYFill(o, n);
		} else {
			if (opts->fill_check) {
				o.ws("if (").wstring(opts->input_api.expr_lessthan(n)).ws(") ");
			}
			genYYFill(o, n);
		}
	}

	if (opts->fFlag) {
		o.wstring(opts->yyfilllabel).wu32(fillIndex).ws(":\n");
	}

	if (n > 0) {
		if (bSetMarker) {
			o.wstring(opts->input_api.stmt_backup_peek(ind));
		} else {
			o.wstring(opts->input_api.stmt_peek(ind));
		}
		readCh = false;
	}
}

void genYYFill(OutputFile &o, size_t need)
{
	std::string fill = opts->fill;
	strrreplace(fill, opts->fill_arg, need);
	o.wstring(fill);
	if (!opts->fill_naked) {
		if (opts->fill_arg_use) {
			o.ws("(").wu64(need).ws(")");
		}
		o.ws(";");
	}
	o.ws("\n");
}

void genSetCondition(OutputFile &o, uint32_t ind, const std::string &cond)
{
	std::string cond_set = opts->cond_set;
	strrreplace(cond_set, opts->cond_set_arg, opts->condEnumPrefix + cond);
	o.wind(ind).wstring(cond_set);
	if (!opts->cond_set_naked) {
		o.ws("(").wstring(opts->condEnumPrefix).wstring(cond).ws(");");
	}
	o.ws("\n");
}

void genSetState(OutputFile &o, uint32_t ind, uint32_t fillIndex)
{
	std::string state_set = opts->state_set;
	strrreplace(state_set, opts->state_set_arg, fillIndex);
	o.wind(ind).wstring(state_set);
	if (!opts->state_set_naked) {
		o.ws("(").wu32(fillIndex).ws(");");
	}
	o.ws("\n");
}

void gen_goto_case(OutputFile &o, uint32_t ind, bool &readCh,
	const State *to, const DFA &dfa, const tagcmd_t &tags,
	bool restore_fallback)
{
	code_lines_t code;
	gen_goto(code, readCh, to, dfa, tags, restore_fallback);
	const size_t lines = code.size();

	if (lines == 1) {
		o.wind(1).wstring(code[0]);
	} else {
		o.ws("\n");
		for (size_t i = 0; i < lines; ++i) {
			o.wind(ind + 1).wstring(code[i]);
		}
	}
}

void gen_goto_if(OutputFile &o, uint32_t ind, bool &readCh,
	const State *to, const DFA &dfa, const tagcmd_t &tags,
	bool restore_fallback)
{
	code_lines_t code;
	gen_goto(code, readCh, to, dfa, tags, restore_fallback);
	const size_t lines = code.size();

	if (lines == 1) {
		o.wstring(code[0]);
	} else {
		o.ws("{\n");
		for (size_t i = 0; i < lines; ++i) {
			o.wind(ind + 1).wstring(code[i]);
		}
		o.wind(ind).ws("}\n");
	}
}

void gen_goto_plain(OutputFile &o, uint32_t ind, bool &readCh,
	const State *to, const DFA &dfa, const tagcmd_t &tags,
	bool restore_fallback)
{
	code_lines_t code;
	gen_goto(code, readCh, to, dfa, tags, restore_fallback);
	const size_t lines = code.size();

	for (size_t i = 0; i < lines; ++i) {
		o.wind(ind).wstring(code[i]);
	}
}

void gen_goto(code_lines_t &code, bool &readCh, const State *to,
	const DFA &dfa, const tagcmd_t &tags, bool restore_fallback)
{
	if (to == NULL) {
		readCh = false;
	}
	if (readCh) {
		code.push_back(opts->input_api.stmt_peek(0));
		readCh = false;
	}
	gen_settags(code, dfa, tags, restore_fallback);
	if (to) {
		code.push_back("goto " + opts->labelPrefix
			+ to_string(to->label) + ";\n");
	}
}

void gen_settags(code_lines_t &code, const DFA &dfa,
	const tagcmd_t &cmd, bool restore_fallback)
{
	if (cmd.empty()) return;

	if (!dfa.basetag) {
		assert(cmd.copy == ZERO_TAGS);
		code.push_back(opts->input_api.stmt_backupctx(0));
		return;
	}

	const std::valarray<Tag> &tags = dfa.tags;
	const size_t ntags = tags.size();
	const bool *copy = dfa.tagpool[cmd.copy];
	for (size_t t = 0; t < ntags; ++t) {
		if (copy[t]) {
			const Tag &tag = tags[t];
			std::string
				x = vartag_expr(tag.name, tag.rule),
				y = vartag_expr_fallback(tag);
			if (restore_fallback) std::swap(x, y);
			code.push_back(y + " = " + x + ";\n");
		}
	}
	if (cmd.set != ZERO_TAGS) {
		code.push_back(opts->input_api.stmt_dist(0,
			dfa.tagpool[cmd.set], tags));
	}
}

} // namespace re2c
