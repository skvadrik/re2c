#include <assert.h>
#include <sstream>

#include "src/codegen/input_api.h"
#include "src/codegen/indent.h"
#include "src/conf/opt.h"
#include "src/globals.h"

namespace re2c
{

InputAPI::InputAPI ()
	: type_ (DEFAULT)
{}

InputAPI::type_t InputAPI::type () const
{
	return type_;
}

void InputAPI::set (type_t t)
{
	type_ = t;
}

std::string InputAPI::expr_peek () const
{
	std::string s;
	switch (type_)
	{
		case DEFAULT:
			s = "*" + opts->yycursor;
			break;
		case CUSTOM:
			s = opts->yypeek + " ()";
			break;
	}
	return s;
}

std::string InputAPI::expr_peek_save () const
{
	return opts->yych + " = " + opts.yychConversion () + expr_peek ();
}

std::string InputAPI::stmt_peek (uint32_t ind) const
{
	return indent (ind) + expr_peek_save () + ";\n";
}

std::string InputAPI::stmt_skip (uint32_t ind) const
{
	std::string s;
	switch (type_)
	{
		case DEFAULT:
			s = "++" + opts->yycursor;
			break;
		case CUSTOM:
			s = opts->yyskip + " ()";
			break;
	}
	return indent (ind) + s + ";\n";
}

std::string InputAPI::stmt_backup (uint32_t ind) const
{
	std::string s;
	switch (type_)
	{
		case DEFAULT:
			s = opts->yymarker + " = " + opts->yycursor;
			break;
		case CUSTOM:
			s = opts->yybackup + " ()";
			break;
	}
	return indent (ind) + s + ";\n";
}

std::string InputAPI::stmt_backupctx (uint32_t ind) const
{
	std::string s;
	switch (type_)
	{
		case DEFAULT:
			s = opts->yyctxmarker + " = " + opts->yycursor;
			break;
		case CUSTOM:
			s = opts->yybackupctx + " ()";
			break;
	}
	return indent(ind) + s + ";\n";
}

std::string InputAPI::expr_dist () const
{
	std::string s;
	switch (type_) {
		case DEFAULT:
			s = "(" + opts->yycursor + " - " + opts->yyctxmarker + ")";
			break;
		case CUSTOM:
			s = opts->yydist + "()";
			break;
	}
	return s;
}

std::string InputAPI::stmt_dist (uint32_t ind, const std::set<size_t> &ctxs,
		const std::vector<CtxVar> &contexts) const
{
	std::string s = indent(ind);
	for (std::set<size_t>::const_iterator i = ctxs.begin(); i != ctxs.end(); ++i) {
		s += contexts[*i].expr() + " = ";
	}
	return s + expr_dist() + ";\n";
}

std::string InputAPI::expr_ctx(const std::string &ctx) const
{
	switch (type_) {
		case DEFAULT: return "(" + opts->yyctxmarker + " + " + ctx + ")";
		case CUSTOM:  return opts->yyctx + "(" + ctx + ")";
		default:      assert(false);
	}
}

std::string InputAPI::expr_ctx_fix(const CtxFix &ctx, const std::vector<CtxVar> &ctxvars) const
{
	std::ostringstream s;
	if (ctx.base == CtxFix::RIGHTMOST) {
		switch (type_) {
			case DEFAULT:
				// optimize '(YYCTXMARKER + ((YYCURSOR - YCTXMARKER) - yyctx))'
				// to       '(YYCURSOR - yyctx)'
				s << "(" << opts->yycursor << " - " << ctx.dist << ")";
				break;
			case CUSTOM:
				s << opts->yyctx << "(" << opts->yydist << "() - " << ctx.dist << ")";
				break;
		}
		return s.str();
	} else {
		s << "(" << ctxvars[ctx.base].expr() << " - " << ctx.dist << ")";
		return expr_ctx(s.str());
	}
}

std::string InputAPI::stmt_restore (uint32_t ind) const
{
	std::string s;
	switch (type_)
	{
		case DEFAULT:
			s = opts->yycursor + " = " + opts->yymarker;
			break;
		case CUSTOM:
			s = opts->yyrestore + " ()";
			break;
	}
	return indent (ind) + s + ";\n";
}

std::string InputAPI::stmt_restorectx_fix(uint32_t ind, size_t dist) const
{
	std::ostringstream s;
	switch (type_) {
		case DEFAULT:
			s << opts->yycursor << " -= " << dist;
			break;
		case CUSTOM:
			s << opts->yyrestorectx << " (" + opts->yydist + "() - " << dist << ")";
			break;
	}
	return indent(ind) + s.str() + ";\n";
}

std::string InputAPI::stmt_restorectx_var_base(uint32_t ind, const std::string &ctx) const
{
	std::string s;
	switch (type_) {
		case DEFAULT:
			s = opts->yycursor + " = " + opts->yyctxmarker + " + " + ctx;
			break;
		case CUSTOM:
			s = opts->yyrestorectx + " (" + ctx + ")";
			break;
	}
	return indent(ind) + s + ";\n";
}

std::string InputAPI::stmt_restorectx_var(uint32_t ind) const
{
	std::string s;
	switch (type_) {
		case DEFAULT:
			s = opts->yycursor + " = " + opts->yyctxmarker;
			break;
		case CUSTOM:
			s = opts->yyrestorectx + " ()";
			break;
	}
	return indent(ind) + s + ";\n";
}

std::string InputAPI::stmt_skip_peek (uint32_t ind) const
{
	return type_ == DEFAULT
		? indent (ind) + opts->yych + " = " + opts.yychConversion () + "*++" + opts->yycursor + ";\n"
		: stmt_skip (ind) + stmt_peek (ind);
}

std::string InputAPI::stmt_skip_backup (uint32_t ind) const
{
	return type_ == DEFAULT
		? indent (ind) + opts->yymarker + " = ++" + opts->yycursor + ";\n"
		: stmt_skip (ind) + stmt_backup (ind);
}

std::string InputAPI::stmt_backup_peek (uint32_t ind) const
{
	return type_ == DEFAULT
		? indent (ind) + opts->yych + " = " + opts.yychConversion () + "*(" + opts->yymarker + " = " + opts->yycursor + ");\n"
		: stmt_backup (ind) + stmt_peek (ind);
}

std::string InputAPI::stmt_skip_backup_peek (uint32_t ind) const
{
	return type_ == DEFAULT
		? indent (ind) + opts->yych + " = " + opts.yychConversion () + "*(" + opts->yymarker + " = ++" + opts->yycursor + ");\n"
		: stmt_skip (ind) + stmt_backup (ind) + stmt_peek (ind);
}

std::string InputAPI::expr_lessthan_one () const
{
	return type_ == DEFAULT
		? opts->yylimit + " <= " + opts->yycursor
		: expr_lessthan (1);
}

std::string InputAPI::expr_lessthan (size_t n) const
{
	std::ostringstream s;
	switch (type_)
	{
		case DEFAULT:
			s << "(" << opts->yylimit << " - " << opts->yycursor << ") < " << n;
			break;
		case CUSTOM:
			s << opts->yylessthan << " (" << n << ")";
			break;
	}
	return s.str ();
}

} // end namespace re2c
