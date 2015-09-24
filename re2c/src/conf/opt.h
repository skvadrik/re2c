#ifndef _RE2C_CONF_OPT_
#define _RE2C_CONF_OPT_

#include <string>

#include "src/codegen/input_api.h"
#include "src/ir/regexp/encoding/enc.h"
#include "src/ir/regexp/empty_class_policy.h"

namespace re2c
{

struct opt_t
{
	// target
	enum target_t
	{
		CODE,
		DOT,
		SKELETON
	} target;

	// fingerprint
	bool bNoGenerationDate;

	// regular expressions
	Enc encoding;
	bool bCaseInsensitive;
	bool bCaseInverted;
	empty_class_policy_t empty_class_policy;

	// conditions
	bool cFlag;
	bool tFlag;
	const char * header_file;
	std::string yycondtype;
	std::string yysetcondition;
	std::string yygetcondition;
	std::string yyctable;
	std::string yySetConditionParam;
	bool bUseYYSetConditionParam;
	bool bUseYYGetConditionNaked;
	std::string condPrefix;
	std::string condEnumPrefix;
	std::string condDivider;
	std::string condDividerParam;
	std::string condGoto;
	std::string condGotoParam;

	// states
	bool fFlag;
	std::string yysetstate;
	std::string yygetstate;
	std::string yyfilllabel;
	std::string yynext;
	std::string yyaccept;
	std::string yySetStateParam;
	bool bUseYYSetStateParam;
	bool bUseYYSetStateNaked;
	bool bUseYYGetStateNaked;
	bool bUseStateAbort;
	bool bUseStateNext;

	// reuse
	bool rFlag;

	// partial flex syntax support
	bool FFlag;

	// code generation
	bool sFlag;
	bool bFlag;
	std::string yybm;
	bool yybmHexTable;
	bool gFlag;
	std::string yytarget;
	uint32_t cGotoThreshold;

	// formatting
	uint32_t topIndent;
	std::string indString;

	// input API
	InputAPI input_api;
	std::string yycursor;
	std::string yymarker;
	std::string yyctxmarker;
	std::string yylimit;
	std::string yypeek;
	std::string yyskip;
	std::string yybackup;
	std::string yybackupctx;
	std::string yyrestore;
	std::string yyrestorectx;
	std::string yylessthan;

	// #line directives
	bool iFlag;

	// debug
	bool dFlag;
	std::string yydebug;

	// yych
	std::string yyctype;
	std::string yych;
	bool bEmitYYCh;
	bool yychConversion;

	// YYFILL
	std::string yyfill;
	bool bUseYYFill;
	bool bUseYYFillParam;
	bool bUseYYFillCheck;
	bool bUseYYFillNaked;
	std::string yyFillLength;

	// labels
	std::string labelPrefix;

	opt_t ();
	opt_t (const opt_t & opt);
	opt_t & operator = (const opt_t & opt);
	void fix ();
};

class useropt_t;
class realopt_t
{
	opt_t real;
	useropt_t & user;
public:
	realopt_t (useropt_t & opt);
	const opt_t * operator -> ();
	void sync ();
};

class useropt_t
{
	opt_t opt;
	bool diverge;
public:
	useropt_t ();
	opt_t * operator -> ();
	friend void realopt_t::sync ();
};

struct Opt
{
	static const opt_t baseopt;

	const char * source_file;
	const char * output_file;

private:
	useropt_t useropt;
	realopt_t realopt;

public:
	Opt ()
		: source_file (NULL)
		, output_file (NULL)
		, useropt ()
		, realopt (useropt)
	{}

	// read-only access, forces options syncronization
	const opt_t * operator -> ()
	{
		return realopt.operator -> ();
	}

	bool source (const char * s);
	bool output (const char * s);

	// Inplace configurations are applied immediately when parsed.
	// This is very bad: first, re2c behaviour is changed in the middle
	// of the block; second, config is resynced too often (every
	// attempt to read config that has been updated results in
	// automatic resync). It is much better to set all options at once.
	void set_target (opt_t::target_t tgt)                { useropt->target = tgt; }
	void set_bNoGenerationDate (bool b)                  { useropt->bNoGenerationDate = b; }
	bool set_encoding (Enc::type_t t)                    { return useropt->encoding.set (t); }
	void unset_encoding (Enc::type_t t)                  { useropt->encoding.unset (t); }
	void set_encoding_policy (Enc::policy_t p)           { useropt->encoding.setPolicy (p); }
	void set_bCaseInsensitive (bool b)                   { useropt->bCaseInsensitive = b; }
	void set_bCaseInverted (bool b)                      { useropt->bCaseInverted = b; }
	void set_empty_class_policy (empty_class_policy_t p) { useropt->empty_class_policy = p; }
	void set_cFlag (bool b)                              { useropt->cFlag = b; }
	void set_header_file (const char * f)                { useropt->header_file = f; }
	void set_yycondtype (const std::string & s)          { useropt->yycondtype = s; }
	void set_yysetcondition (const std::string & s)      { useropt->yysetcondition = s; }
	void set_yygetcondition (const std::string & s)      { useropt->yygetcondition = s; }
	void set_yyctable (const std::string & s)            { useropt->yyctable = s; }
	void set_yySetConditionParam (const std::string & s)
	{
		useropt->yySetConditionParam = s;
		useropt->bUseYYSetConditionParam = false;
	}
	void set_bUseYYGetConditionNaked (bool b)            { useropt->bUseYYGetConditionNaked = b; }
	void set_condPrefix (const std::string & s)          { useropt->condPrefix = s; }
	void set_condEnumPrefix (const std::string & s)      { useropt->condEnumPrefix = s; }
	void set_condDivider (const std::string & s)         { useropt->condDivider = s; }
	void set_condDividerParam (const std::string & s)    { useropt->condDividerParam = s; }
	void set_condGoto (const std::string & s)            { useropt->condGoto = s; }
	void set_condGotoParam (const std::string & s)       { useropt->condGotoParam = s; }
	void set_fFlag (bool b)                              { useropt->fFlag = b; }
	void set_yysetstate (const std::string & s)          { useropt->yysetstate = s; }
	void set_yygetstate (const std::string & s)          { useropt->yygetstate = s; }
	void set_yyfilllabel (const std::string & s)         { useropt->yyfilllabel = s; }
	void set_yynext (const std::string & s)              { useropt->yynext = s; }
	void set_yyaccept (const std::string & s)            { useropt->yyaccept = s; }
	void set_yySetStateParam (const std::string & s)
	{
		useropt->yySetStateParam = s;
		useropt->bUseYYSetStateParam = false;
	}
	void set_bUseYYSetStateNaked (bool b)                { useropt->bUseYYSetStateNaked = b; }
	void set_bUseYYGetStateNaked (bool b)                { useropt->bUseYYGetStateNaked = b; }
	void set_bUseStateAbort (bool b)                     { useropt->bUseStateAbort = b; }
	void set_bUseStateNext (bool b)                      { useropt->bUseStateNext = b; }
	void set_rFlag (bool b)                              { useropt->rFlag = b; }
	void set_FFlag (bool b)                              { useropt->FFlag = b; }
	void set_sFlag (bool b)                              { useropt->sFlag = b; }
	void set_bFlag (bool b)                              { useropt->bFlag = b; }
	void set_yybm (const std::string & s)                { useropt->yybm = s; }
	void set_yybmHexTable (bool b)                       { useropt->yybmHexTable = b; }
	void set_gFlag (bool b)                              { useropt->gFlag = b; }
	void set_yytarget (const std::string & s)            { useropt->yytarget = s; }
	void set_cGotoThreshold (uint32_t n)                 { useropt->cGotoThreshold = n; }
	void set_topIndent (uint32_t n)                      { useropt->topIndent = n; }
	void set_indString (const std::string & s)           { useropt->indString = s; }
	void set_input_api (InputAPI::type_t t)              { useropt->input_api.set (t); }
	void set_yycursor (const std::string & s)            { useropt->yycursor = s; }
	void set_yymarker (const std::string & s)            { useropt->yymarker = s; }
	void set_yyctxmarker (const std::string & s)         { useropt->yyctxmarker = s; }
	void set_yylimit (const std::string & s)             { useropt->yylimit = s; }
	void set_yypeek (const std::string & s)              { useropt->yypeek = s; }
	void set_yyskip (const std::string & s)              { useropt->yyskip = s; }
	void set_yybackup (const std::string & s)            { useropt->yybackup = s; }
	void set_yybackupctx (const std::string & s)         { useropt->yybackupctx = s; }
	void set_yyrestore (const std::string & s)           { useropt->yyrestore = s; }
	void set_yyrestorectx (const std::string & s)        { useropt->yyrestorectx = s; }
	void set_yylessthan (const std::string & s)          { useropt->yylessthan = s; }
	void set_iFlag (bool b)                              { useropt->iFlag = b; }
	void set_dFlag (bool b)                              { useropt->dFlag = b; }
	void set_yydebug (const std::string & s)             { useropt->yydebug = s; }
	void set_yyctype (const std::string & s)             { useropt->yyctype = s; }
	void set_yych (const std::string & s)                { useropt->yych = s; }
	void set_bEmitYYCh (bool b)                          { useropt->bEmitYYCh = b; }
	void set_yychConversion (bool b)                     { useropt->yychConversion = b; }
	void set_yyfill (const std::string & s)              { useropt->yyfill = s; }
	void set_bUseYYFill (bool b)                         { useropt->bUseYYFill = b; }
	void set_bUseYYFillParam (bool b)                    { useropt->bUseYYFillParam = b; }
	void set_bUseYYFillCheck (bool b)                    { useropt->bUseYYFillCheck = b; }
	void set_bUseYYFillNaked (bool b)                    { useropt->bUseYYFillNaked = b; }
	void set_yyFillLength (const std::string & s)
	{
		useropt->yyFillLength = s;
		useropt->bUseYYFillParam = false;
	}
	void set_labelPrefix (const std::string & s)         { useropt->labelPrefix = s; }

	// helpers
	std::string yychConversion ()
	{
		return realopt->yychConversion
			? "(" + realopt->yyctype + ")"
			: "";
	}

	// bad temporary hacks, should be fixed by proper scoping of config (parts).
	void reset_encoding (const Enc & enc);
	void reset_mapCodeName ();

	FORBID_COPY (Opt);
};

enum parse_opts_t
{
	OK,
	EXIT_OK,
	EXIT_FAIL
};

parse_opts_t parse_opts (char ** argv, Opt & opts);

} // namespace re2c

#endif // _RE2C_CONF_OPT_
