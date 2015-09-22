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
	bool bFlag;
	bool cFlag;
	bool dFlag;
	bool DFlag;
	bool fFlag;
	bool FFlag;
	bool gFlag;
	bool iFlag;
	bool rFlag;
	bool sFlag;
	bool tFlag;
	const char * header_file;
	bool flag_skeleton;
	bool bNoGenerationDate;
	bool bEmitYYCh;
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
	std::string yychConversion;
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
};

struct Opt : public opt_t
{
	const char * source_file;
	const char * output_file;

private:
	const opt_t baseopt;
	opt_t useropt;

public:
	Opt ()
		: opt_t ()
		, source_file (NULL)
		, output_file (NULL)
		, baseopt ()
		, useropt ()
	{}

	bool apply ();

	void bit_vectors ();
	void start_conditions ();
	void debug_output ();
	void emit_dot ();
	void storable_state ();
	void flex_syntax ();
	void computed_gotos ();
	void no_debug_info ();
	void reusable ();
	void nested_ifs ();
	void no_generation_date ();
	void case_insensitive ();
	void case_inverted ();
	void skeleton ();
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
