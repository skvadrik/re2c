#include "src/conf/opt.h"

namespace re2c
{

bool bFlag = false;
bool cFlag = false;
bool dFlag = false;
bool DFlag = false;
bool fFlag = false;
bool FFlag = false;
bool gFlag = false;
bool iFlag = false;
bool rFlag = false;
bool sFlag = false;
bool tFlag = false;
bool flag_skeleton = false;

bool bNoGenerationDate = false;
bool bEmitYYCh = true;
bool bUseStateNext = false;
bool bUseYYFill = true;
bool bUseYYFillParam = true;
bool bUseYYFillCheck = true;
bool bUseYYFillNaked = false;
bool bUseYYSetConditionParam = true;
bool bUseYYGetConditionNaked = false;
bool bUseYYSetStateParam = true;
bool bUseYYSetStateNaked = false;
bool bUseYYGetStateNaked = false;

std::string labelPrefix("yy");
std::string condPrefix("yyc_");
std::string condEnumPrefix("yyc");
std::string condDivider("/* *********************************** */");
std::string condDividerParam("@@");
std::string condGoto("goto @@;");
std::string condGotoParam("@@");
std::string yychConversion("");
std::string yyFillLength("@@");
std::string yySetConditionParam("@@");
std::string yySetStateParam("@@");
std::string yySetupRule("");
uint32_t cGotoThreshold = 9;

uint32_t topIndent = 0;
std::string indString("\t");
bool yybmHexTable = false;
bool bUseStateAbort = false;
bool bCaseInsensitive = false;
bool bCaseInverted = false;

Enc encoding;
InputAPI input_api;

empty_class_policy_t empty_class_policy = EMPTY_CLASS_MATCH_EMPTY;

void Opt::bit_vectors ()
{
	bFlag = true;
	sFlag = true;
}

void Opt::start_conditions ()
{
	cFlag = true;
}

void Opt::debug_output ()
{
	dFlag = true;
}

void Opt::emit_dot ()
{
	DFlag = true;
	iFlag = true;
}

void Opt::storable_state ()
{
	fFlag = true;
}

void Opt::flex_syntax ()
{
	FFlag = true;
}

void Opt::computed_gotos ()
{
	gFlag = true;
	bFlag = true;
	sFlag = true;
}

void Opt::no_debug_info ()
{
	iFlag = true;
}

void Opt::reusable ()
{
	rFlag = true;
}

void Opt::nested_ifs ()
{
	sFlag = true;
}

void Opt::no_generation_date ()
{
	bNoGenerationDate = true;
}

void Opt::case_insensitive ()
{
	bCaseInsensitive = true;
}

void Opt::case_inverted ()
{
	bCaseInverted = true;
}

void Opt::skeleton ()
{
	flag_skeleton = true;
}

void Opt::source (const char * s)
{
	source_file = s;
}

void Opt::output (const char * s)
{
	output_file = s;
}

void Opt::type_header (const char * s)
{
	tFlag = true;
	header_file = s;
}

void Opt::encoding_policy (Enc::policy_t p)
{
	encoding.setPolicy (p);
}

void Opt::input (InputAPI::type_t i)
{
	input_api.set (i);
}

void Opt::empty_class (empty_class_policy_t p)
{
	empty_class_policy = p;
}

bool Opt::ecb ()
{
	return encoding.set (Enc::EBCDIC);
}

bool Opt::unicode ()
{
	sFlag = true;
	return encoding.set(Enc::UTF32);
}

bool Opt::wide_chars ()
{
	sFlag = true;
	return encoding.set(Enc::UCS2);
}

bool Opt::utf_16 ()
{
	sFlag = true;
	return encoding.set(Enc::UTF16);
}

bool Opt::utf_8 ()
{
	return encoding.set(Enc::UTF8);
}

} // namespace re2c
