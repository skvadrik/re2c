#include "src/util/c99_stdint.h"
#include <stddef.h>
#include <set>
#include <string>

#include "src/codegen/emit.h"
#include "src/codegen/input_api.h"
#include "src/codegen/output.h"
#include "src/globals.h"
#include "src/ir/adfa/action.h"
#include "src/ir/adfa/adfa.h"
#include "src/ir/regexp/regexp.h"
#include "src/ir/skeleton/skeleton.h"
#include "src/parse/code.h"
#include "src/parse/loc.h"
#include "src/util/string_utils.h"

namespace re2c
{

class label_t;

static void need(OutputFile &o, uint32_t ind, size_t some);
static void emit_match(OutputFile &o, uint32_t ind, const State *s);
static void emit_initial(OutputFile &o, uint32_t ind, const State *s, const std::set<label_t> &used_labels, bool save_yyaccept);
static void emit_save(OutputFile &o, uint32_t ind, const State *s, bool save_yyaccept);
static void emit_accept_binary(OutputFile &o, uint32_t ind, const DFA &dfa, const State *s, size_t l, size_t r);
static void emit_accept(OutputFile &o, uint32_t ind, const DFA &dfa, const State *s);
static void emit_rule(OutputFile &o, uint32_t ind, const DFA &dfa, size_t rule_idx);
static void gen_goto(code_lines_t &code, const State *to, const DFA &dfa, tcid_t tcid, Opt &opts);
static void gen_fintags(OutputFile &o, uint32_t ind, const DFA &dfa, const Rule &rule);
static bool endstate(const State *s);

void emit_action(OutputFile &o, uint32_t ind, const DFA &dfa,
	const State *s, const std::set<label_t> &used_labels)
{
	const bool save_yyaccept = dfa.accepts.size() > 1;
	switch (s->action.type) {
		case Action::MATCH:
			emit_match(o, ind, s);
			break;
		case Action::INITIAL:
			emit_initial(o, ind, s, used_labels, save_yyaccept);
			break;
		case Action::SAVE:
			emit_save(o, ind, s, save_yyaccept);
			break;
		case Action::MOVE:
			break;
		case Action::ACCEPT:
			emit_accept(o, ind, dfa, s);
			break;
		case Action::RULE:
			emit_rule(o, ind, dfa, s->action.info.rule);
			break;
	}
}

void emit_match(OutputFile &o, uint32_t ind, const State *s)
{
	Opt &opts = o.opts;
	if (s->fill != 0) {
		o.wstring(opts->input_api.stmt_skip(ind, opts));
		need(o, ind, s->fill);
		o.wstring(opts->input_api.stmt_peek(ind, opts));
	} else if (endstate(s)) {
		o.wstring(opts->input_api.stmt_skip(ind, opts));
	} else {
		o.wstring(opts->input_api.stmt_skip_peek(ind, opts));
	}
}

void emit_initial(OutputFile &o, uint32_t ind, const State *s,
	const std::set<label_t> &used_labels, bool save_yyaccept)
{
	Opt &opts = o.opts;
	const Initial &init = *s->action.info.initial;
	const label_t label = init.label;
	const size_t save = init.save;
	const bool backup = save != Initial::NOSAVE;

	if (used_labels.count(s->label)) {
		if (save_yyaccept && backup) {
			o.wind(ind).wstring(opts->yyaccept).ws(" = ")
				.wu64(save).ws(";\n");
		}
		o.wstring(opts->input_api.stmt_skip(ind, opts));
	}

	if (used_labels.count(label)) {
		o.wstring(opts->labelPrefix).wlabel(label).ws(":\n");
	}

	if (opts->dFlag) {
		o.wind(ind).wstring(opts->yydebug).ws("(")
			.wlabel(label).ws(", *")
			.wstring(opts->yycursor).ws(");\n");
	}

	if (endstate(s)) return;

	need(o, ind, s->fill);
	if (backup) {
		o.wstring(opts->input_api.stmt_backup_peek(ind, opts));
	} else {
		o.wstring(opts->input_api.stmt_peek(ind, opts));
	}
}

void emit_save(OutputFile &o, uint32_t ind, const State *const s,
	bool save_yyaccept)
{
	Opt &opts = o.opts;

	if (save_yyaccept) {
		o.wind(ind).wstring(opts->yyaccept).ws(" = ")
			.wu64(s->action.info.save).ws(";\n");
	}

	if (s->fill != 0) {
		o.wstring(opts->input_api.stmt_skip_backup(ind, opts));
		need(o, ind, s->fill);
		o.wstring(opts->input_api.stmt_peek(ind, opts));
	} else {
		o.wstring(opts->input_api.stmt_skip_backup_peek(ind, opts));
	}
}

void emit_accept_binary(OutputFile &o, uint32_t ind, const DFA &dfa,
	const State *s, size_t l, size_t r)
{
	Opt &opts = o.opts;
	if (l < r) {
		const size_t m = (l + r) >> 1;
		o.wind(ind).ws("if (").wstring(opts->yyaccept)
			.ws(r == l+1 ? " == " : " <= ").wu64(m).ws(") {\n");
		emit_accept_binary (o, ++ind, dfa, s, l, m);
		o.wind(--ind).ws("} else {\n");
		emit_accept_binary (o, ++ind, dfa, s, m + 1, r);
		o.wind(--ind).ws("}\n");
	} else {
		const accept_t &acc = *s->action.info.accepts;
		gen_goto_plain(o, ind, acc[l].first, dfa, acc[l].second);
	}
}

void emit_accept(OutputFile &o, uint32_t ind, const DFA &dfa, const State *s)
{
	Opt &opts = o.opts;
	const accept_t &acc = *s->action.info.accepts;
	const size_t nacc = acc.size();

	if (nacc == 0) {
		return;
	}

	o.wstring(opts->input_api.stmt_restore(ind, opts));

	// only one possible 'yyaccept' value: unconditional jump
	if (nacc == 1) {
		gen_goto_plain(o, ind, acc[0].first, dfa, acc[0].second);
		return;
	}

	bool have_tags = false;
	for (size_t i = 0; i < nacc; ++i) {
		if (acc[i].second != TCID0) {
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
		emit_accept_binary(o, ind, dfa, s, 0, nacc - 1);
		return;
	}

	// switch
	o.wind(ind).ws("switch (").wstring(opts->yyaccept).ws(") {\n");
	for (uint32_t i = 0; i < nacc - 1; ++i) {
		o.wind(ind).ws("case ").wu32(i).ws(": ");
		gen_goto_case(o, ind, acc[i].first, dfa, acc[i].second);
	}
	o.wind(ind).ws("default:");
	gen_goto_case(o, ind, acc[nacc - 1].first, dfa, acc[nacc - 1].second);
	o.wind(ind).ws("}\n");
}

void emit_rule(OutputFile &o, uint32_t ind, const DFA &dfa, size_t rule_idx)
{
	Opt &opts = o.opts;
	const Rule &rule = dfa.rules[rule_idx];
	const std::string &cond = rule.info->newcond;
	const Code *code = rule.info->code;
	std::string s;

	gen_fintags(o, ind, dfa, rule);

	if (opts->target == opt_t::SKELETON) {
		emit_action(o, ind, dfa, rule_idx);
		return;
	}

	if (!cond.empty() && dfa.cond != cond) {
		strrreplace(s = opts->cond_set, opts->cond_set_arg, opts->condEnumPrefix + cond);
		o.wind(ind).wstring(s);
		if (!opts->cond_set_naked) {
			o.ws("(").wstring(opts->condEnumPrefix).wstring(cond).ws(");");
		}
		o.ws("\n");
	}
	if (code) {
		if (!yySetupRule.empty()) {
			o.wind(ind).wstring(yySetupRule).ws("\n");
		}
		o.wline_info(code->loc.line, code->loc.filename.c_str())
			.wind(ind).wstring(code->text).ws("\n")
			.wdelay_line_info();
	} else if (!cond.empty()) {
		strrreplace(s = opts->condGoto, opts->condGotoParam, opts->condPrefix + cond);
		o.wind(ind).wstring(s).ws("\n");
	}
}

void need(OutputFile &o, uint32_t ind, size_t some)
{
	assert(some > 0);

	Opt &opts = o.opts;
	std::string s;

	if (opts->fFlag) {
		strrreplace(s = opts->state_set, opts->state_set_arg, last_fill_index);
		o.wind(ind).wstring(s);
		if (!opts->state_set_naked) {
			o.ws("(").wu32(last_fill_index).ws(");");
		}
		o.ws("\n");
	}

	if (opts->fill_use) {
		o.wind(ind);
		if (opts->fill_check) {
			o.ws("if (").wstring(opts->input_api.expr_lessthan(some, opts)).ws(") ");
		}
		strrreplace(s = opts->fill, opts->fill_arg, some);
		o.wstring(s);
		if (!opts->fill_naked) {
			if (opts->fill_arg_use) {
				o.ws("(").wu64(some).ws(")");
			}
			o.ws(";");
		}
		o.ws("\n");
	}

	if (opts->fFlag) {
		o.wstring(opts->yyfilllabel).wu32(last_fill_index).ws(":\n");
		++last_fill_index;
	}
}

void gen_goto_case(OutputFile &o, uint32_t ind, const State *to,
	const DFA &dfa, tcid_t tcid)
{
	code_lines_t code;
	gen_goto(code, to, dfa, tcid, o.opts);
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

void gen_goto_if(OutputFile &o, uint32_t ind, const State *to,
	const DFA &dfa, tcid_t tcid)
{
	code_lines_t code;
	gen_goto(code, to, dfa, tcid, o.opts);
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

void gen_goto_plain(OutputFile &o, uint32_t ind, const State *to,
	const DFA &dfa, tcid_t tcid)
{
	code_lines_t code;
	gen_goto(code, to, dfa, tcid, o.opts);
	const size_t lines = code.size();

	for (size_t i = 0; i < lines; ++i) {
		o.wind(ind).wstring(code[i]);
	}
}

void gen_goto(code_lines_t &code, const State *to, const DFA &dfa,
	tcid_t tcid, Opt &opts)
{
	gen_settags(code, dfa, tcid, opts);
	if (to) {
		code.push_back("goto " + opts->labelPrefix
			+ to_string(to->label) + ";\n");
	}
}

void gen_settags(code_lines_t &code, const DFA &dfa, tcid_t tcid, Opt &opts)
{
	const bool generic = opts->input_api.type() == InputAPI::CUSTOM;
	const std::string
		&prefix = opts->tags_prefix,
		&expression = opts->tags_expression;
	const tccmd_t &cmd = dfa.tcpool[tcid];
	const tagsave_t *tsave = cmd.save;
	const tagcopy_t *tcopy = cmd.copy;

	// single tag YYCTXMARKER, backwards compatibility
	if (tsave && dfa.oldstyle_ctxmarker) {
		assert(tcopy == NULL);
		const std::string s = generic
			? opts->yybackupctx + " ();\n"
			: opts->yyctxmarker + " = " + opts->yycursor + ";\n";
		code.push_back(s);
		return;
	}

	// copy commands
	for (const tagcopy_t *p = tcopy; p; p = p->next) {
		const std::string
			l = vartag_expr(p->lhs, prefix, expression),
			r = vartag_expr(p->rhs, prefix, expression),
			s = generic
				? opts->yycopytag + " (" + l + ", " + r + ");\n"
				: l + " = " + r + ";\n";
		code.push_back(s);
	}

	// save commands
	if (generic) {
		for (const tagsave_t *p = tsave; p; p = p->next) {
			const std::string
				v = vartag_expr(p->ver, prefix, expression),
				s = p->bottom
					? opts->yycopytag + " (" + v + ", " + opts->tags_default + ");\n"
					: opts->yybackuptag + " (" + v + ");\n";
			code.push_back(s);
		}
	} else if (tsave) {
		std::string s1 = "", s2 = "";
		for (const tagsave_t *p = tsave; p; p = p->next) {
			const std::string v = vartag_expr(p->ver, prefix, expression);
			if (p->bottom) {
				s1 += v + " = ";
			} else {
				s2 += v + " = ";
			}
		}
		if (!s1.empty()) {
			s1 += opts->tags_default + ";\n";
			code.push_back(s1);
		}
		if (!s2.empty()) {
			s2 += opts->yycursor + ";\n";
			code.push_back(s2);
		}
	}
}

void gen_fintags(OutputFile &o, uint32_t ind, const DFA &dfa, const Rule &rule)
{
	Opt &opts = o.opts;
	const bool generic = opts->input_api.type() == InputAPI::CUSTOM;
	const std::string
		&prefix = opts->tags_prefix,
		&expression = opts->tags_expression;
	const std::vector<VarTag> &vartags = dfa.vartags;
	const std::vector<FixTag> &fixtags = dfa.fixtags;
	const tagver_t *fins = dfa.finvers;

	// variable tags
	for (size_t t = rule.lvar; t < rule.hvar; ++t) {
		const VarTag &tag = vartags[t];
		o.wind(ind);
		if (tag.name) {
			const std::string
				name = *tag.name,
				expr = vartag_expr(fins[t], prefix, expression);
			if (generic) {
				o.wstring(opts->yycopytag).ws(" (").wstring(name)
					.ws(", ").wstring(expr).ws(")");
			} else {
				o.wstring(name).ws(" = ").wstring(expr);
			}
		} else if (dfa.oldstyle_ctxmarker) {
			if (generic) {
				o.wstring(opts->yyrestorectx).ws(" ()");
			} else {
				o.wstring(opts->yycursor).ws(" = ").wstring(opts->yyctxmarker);
			}
		} else {
			const std::string expr = vartag_expr(fins[t], prefix, expression);
			if (generic) {
				o.wstring(opts->yyrestoretag).ws(" (").wstring(expr).ws(")");
			} else {
				o.wstring(opts->yycursor).ws(" = ").wstring(expr);
			}
		}
		o.ws(";\n");
	}

	// fixed tags
	for (size_t t = rule.lfix; t < rule.hfix; ++t) {
		assert(!generic);
		const FixTag &tag = fixtags[t];
		o.wind(ind);
		if (tag.name) {
			o.wstring(*tag.name).ws(" = ");
			if (tag.base == FixTag::RIGHTMOST) {
				// optimize '(YYCTXMARKER + ((YYCURSOR - YCTXMARKER) - tag))'
				// to       '(YYCURSOR - tag)'
				o.wstring(opts->yycursor).ws(" - ").wu64(tag.dist);
			} else {
				o.wstring(vartag_expr(fins[tag.base], prefix, expression))
					.ws(" - ").wu64(tag.dist);
			}
		} else {
			o.wstring(opts->yycursor).ws(" -= ").wu64(tag.dist);
		}
		o.ws(";\n");
	}
}

bool endstate(const State *s)
{
	if (s->go.nSpans > 1) return false;

	// 'end' state is a state which has no outgoing transitions on symbols
	// usually 'end' states are final states (not all final states are 'end'
	// states), but sometimes 'end' state happens to be initial non-accepting
	// state, e.g. in case of rule '[]'
	const Action::type_t &a = s->go.span[0].to->action.type;
	return a == Action::RULE
		|| a == Action::ACCEPT;
}

} // namespace re2c
