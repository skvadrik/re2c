#ifndef _RE2C_CONF_OPT_
#define _RE2C_CONF_OPT_

#include <string>

#include "src/codegen/code_names.h"
#include "src/codegen/input_api.h"
#include "src/ir/regexp/encoding/enc.h"
#include "src/ir/regexp/empty_class_policy.h"

namespace re2c
{

struct opt_t
{
	enum target_t
	{
		CODE,
		DOT,
		SKELETON
	} target;
	bool bFlag;
	bool cFlag;
	bool dFlag;
	bool fFlag;
	bool FFlag;
	bool gFlag;
	bool iFlag;
	bool rFlag;
	bool sFlag;
	bool tFlag;
	const char * header_file;
	bool bNoGenerationDate;
	bool bEmitYYCh;
	bool yychConversion;
	bool bUseStateNext;
	bool bUseYYFill;
	bool bUseYYFillParam;
	bool bUseYYFillCheck;
	bool bUseYYFillNaked;
	bool bUseYYSetConditionParam;
	bool bUseYYGetConditionNaked;
	bool bUseYYSetStateParam;
	bool bUseYYSetStateNaked;
	bool bUseYYGetStateNaked;
	bool yybmHexTable;
	bool bUseStateAbort;
	bool bCaseInsensitive;
	bool bCaseInverted;
	uint32_t cGotoThreshold;
	uint32_t topIndent;
	std::string indString;
	std::string labelPrefix;
	std::string condPrefix;
	std::string condEnumPrefix;
	std::string condDivider;
	std::string condDividerParam;
	std::string condGoto;
	std::string condGotoParam;
	std::string yyFillLength;
	std::string yySetConditionParam;
	std::string yySetStateParam;
	CodeNames mapCodeName;
	Enc encoding;
	InputAPI input_api;
	empty_class_policy_t empty_class_policy;

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

	// Inplace configurations are applied immediately when parsed.
	// This is very bad: first, re2c behaviour is changed in the middle
	// of the block; second, config is resynced too often (every
	// attempt to read config that has been updated results in
	// automatic resync). It is much better to set all options at once.
	void set_target (opt_t::target_t tgt);
	void bit_vectors ();
	void start_conditions ();
	void debug_output ();
	void storable_state ();
	void flex_syntax ();
	void computed_gotos ();
	void no_debug_info ();
	void reusable ();
	void nested_ifs ();
	void no_generation_date ();
	void case_insensitive ();
	void case_inverted ();
	void encoding_policy (Enc::policy_t);
	void input (InputAPI::type_t);
	void empty_class (empty_class_policy_t);
	bool source (const char * s);
	bool output (const char * s);
	bool type_header (const char * s);
	bool ecb ();
	bool unicode ();
	bool wide_chars ();
	bool utf_16 ();
	bool utf_8 ();
	bool sync_mapCodeName (const std::string & key, const std::string & val);
	bool sync_encoding (Enc::type_t t);
	void sync_encoding_unset (Enc::type_t t);
	void sync_condPrefix (const std::string & s);
	void sync_condEnumPrefix (const std::string & s);
	void sync_condDivider (const std::string & s);
	void sync_condDividerParam (const std::string & s);
	void sync_condGoto (const std::string & s);
	void sync_condGotoParam (const std::string & s);
	void sync_cGotoThreshold (uint32_t n);
	void sync_bUseYYFillNaked (bool b);
	void sync_yyFillLength (const std::string & s);
	void sync_bUseYYGetConditionNaked (bool b);
	void sync_bUseYYGetStateNaked (bool b);
	void sync_yySetConditionParam (const std::string & s);
	void sync_bUseYYSetStateNaked (bool b);
	void sync_yySetStateParam (const std::string & s);
	void sync_indString (const std::string & s);
	void sync_topIndent (uint32_t n);
	void sync_labelPrefix (const std::string & s);
	void sync_bUseStateAbort (bool b);
	void sync_bUseStateNext (bool b);
	void sync_yybmHexTable (bool b);
	void sync_yychConversion (bool b);
	void sync_bEmitYYCh (bool b);
	void sync_bUseYYFillCheck (bool b);
	void sync_bUseYYFill (bool b);
	void sync_bUseYYFillParam (bool b);
	// bad temporary hacks
	// should be fixed by proper scoping in config (parts).
	void sync_reset_encoding (const Enc & enc);
	void sync_reset_mapCodeName ();

	opt_t::target_t target ()                  { return realopt->target; }
	bool bFlag ()                              { return realopt->bFlag; }
	bool cFlag ()                              { return realopt->cFlag; }
	bool dFlag ()                              { return realopt->dFlag; }
	bool fFlag ()                              { return realopt->fFlag; }
	bool FFlag ()                              { return realopt->FFlag; }
	bool gFlag ()                              { return realopt->gFlag; }
	bool iFlag ()                              { return realopt->iFlag; }
	bool rFlag ()                              { return realopt->rFlag; }
	bool sFlag ()                              { return realopt->sFlag; }
	bool tFlag ()                              { return realopt->tFlag; }
	const char * header_file ()                { return realopt->header_file; }
	bool bNoGenerationDate ()                  { return realopt->bNoGenerationDate; }
	bool bEmitYYCh ()                          { return realopt->bEmitYYCh; }
	std::string yychConversion ()
	{
		return realopt->yychConversion
			? "(" + realopt->mapCodeName["YYCTYPE"] + ")"
			: "";
	}
	bool bUseStateNext ()                      { return realopt->bUseStateNext; }
	bool bUseYYFill ()                         { return realopt->bUseYYFill; }
	bool bUseYYFillParam ()                    { return realopt->bUseYYFillParam; }
	bool bUseYYFillCheck ()                    { return realopt->bUseYYFillCheck; }
	bool bUseYYFillNaked ()                    { return realopt->bUseYYFillNaked; }
	bool bUseYYSetConditionParam ()            { return realopt->bUseYYSetConditionParam; }
	bool bUseYYGetConditionNaked ()            { return realopt->bUseYYGetConditionNaked; }
	bool bUseYYSetStateParam ()                { return realopt->bUseYYSetStateParam; }
	bool bUseYYSetStateNaked ()                { return realopt->bUseYYSetStateNaked; }
	bool bUseYYGetStateNaked ()                { return realopt->bUseYYGetStateNaked; }
	bool yybmHexTable ()                       { return realopt->yybmHexTable; }
	bool bUseStateAbort ()                     { return realopt->bUseStateAbort; }
	bool bCaseInsensitive ()                   { return realopt->bCaseInsensitive; }
	bool bCaseInverted ()                      { return realopt->bCaseInverted; }
	uint32_t cGotoThreshold ()                 { return realopt->cGotoThreshold; }
	uint32_t topIndent ()                      { return realopt->topIndent; }
	const std::string & indString ()           { return realopt->indString; }
	const std::string & labelPrefix ()         { return realopt->labelPrefix; }
	const std::string & condPrefix ()          { return realopt->condPrefix; }
	const std::string & condEnumPrefix ()      { return realopt->condEnumPrefix; }
	const std::string & condDivider ()         { return realopt->condDivider; }
	const std::string & condDividerParam ()    { return realopt->condDividerParam; }
	const std::string & condGoto ()            { return realopt->condGoto; }
	const std::string & condGotoParam ()       { return realopt->condGotoParam; }
	const std::string & yyFillLength ()        { return realopt->yyFillLength; }
	const std::string & yySetConditionParam () { return realopt->yySetConditionParam; }
	const std::string & yySetStateParam ()     { return realopt->yySetStateParam; }
	const CodeNames & mapCodeName ()           { return realopt->mapCodeName; }
	const Enc & encoding ()                    { return realopt->encoding; }
	const InputAPI & input_api ()              { return realopt->input_api; }
	empty_class_policy_t empty_class_policy () { return realopt->empty_class_policy; }

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
