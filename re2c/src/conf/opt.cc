#include "src/conf/msg.h"
#include "src/conf/opt.h"

namespace re2c
{

Opt opts;

opt_t::opt_t ()
	: bFlag (false)
	, cFlag (false)
	, dFlag (false)
	, DFlag (false)
	, fFlag (false)
	, FFlag (false)
	, gFlag (false)
	, iFlag (false)
	, rFlag (false)
	, sFlag (false)
	, tFlag (false)
	, header_file (NULL)
	, flag_skeleton (false)
	, bNoGenerationDate (false)
	, bEmitYYCh (true)
	, bUseStateNext (false)
	, bUseYYFill (true)
	, bUseYYFillParam (true)
	, bUseYYFillCheck (true)
	, bUseYYFillNaked (false)
	, bUseYYSetConditionParam (true)
	, bUseYYGetConditionNaked (false)
	, bUseYYSetStateParam (true)
	, bUseYYSetStateNaked (false)
	, bUseYYGetStateNaked (false)
	, yybmHexTable (false)
	, bUseStateAbort (false)
	, bCaseInsensitive (false)
	, bCaseInverted (false)
	, cGotoThreshold (9)
	, topIndent (0)
	, indString ("\t")
	, labelPrefix ("yy")
	, condPrefix ("yyc_")
	, condEnumPrefix ("yyc")
	, condDivider ("/* *********************************** */")
	, condDividerParam ("@@")
	, condGoto ("goto @@;")
	, condGotoParam ("@@")
	, yychConversion ("")
	, yyFillLength ("@@")
	, yySetConditionParam ("@@")
	, yySetStateParam ("@@")
	, mapCodeName ()
	, encoding ()
	, input_api ()
	, empty_class_policy (EMPTY_CLASS_MATCH_EMPTY)
{}

opt_t::opt_t (const opt_t & opt)
	: bFlag (opt.bFlag)
	, cFlag (opt.cFlag)
	, dFlag (opt.dFlag)
	, DFlag (opt.DFlag)
	, fFlag (opt.fFlag)
	, FFlag (opt.FFlag)
	, gFlag (opt.gFlag)
	, iFlag (opt.iFlag)
	, rFlag (opt.rFlag)
	, sFlag (opt.sFlag)
	, tFlag (opt.tFlag)
	, header_file (opt.header_file)
	, flag_skeleton (opt.flag_skeleton)
	, bNoGenerationDate (opt.bNoGenerationDate)
	, bEmitYYCh (opt.bEmitYYCh)
	, bUseStateNext (opt.bUseStateNext)
	, bUseYYFill (opt.bUseYYFill)
	, bUseYYFillParam (opt.bUseYYFillParam)
	, bUseYYFillCheck (opt.bUseYYFillCheck)
	, bUseYYFillNaked (opt.bUseYYFillNaked)
	, bUseYYSetConditionParam (opt.bUseYYSetConditionParam)
	, bUseYYGetConditionNaked (opt.bUseYYGetConditionNaked)
	, bUseYYSetStateParam (opt.bUseYYSetStateParam)
	, bUseYYSetStateNaked (opt.bUseYYSetStateNaked)
	, bUseYYGetStateNaked (opt.bUseYYGetStateNaked)
	, yybmHexTable (opt.yybmHexTable)
	, bUseStateAbort (opt.bUseStateAbort)
	, bCaseInsensitive (opt.bCaseInsensitive)
	, bCaseInverted (opt.bCaseInverted)
	, cGotoThreshold (opt.cGotoThreshold)
	, topIndent (opt.topIndent)
	, indString (opt.indString)
	, labelPrefix (opt.labelPrefix)
	, condPrefix (opt.condPrefix)
	, condEnumPrefix (opt.condEnumPrefix)
	, condDivider (opt.condDivider)
	, condDividerParam (opt.condDividerParam)
	, condGoto (opt.condGoto)
	, condGotoParam (opt.condGotoParam)
	, yychConversion (opt.yychConversion)
	, yyFillLength (opt.yyFillLength)
	, yySetConditionParam (opt.yySetConditionParam)
	, yySetStateParam (opt.yySetStateParam)
	, mapCodeName (opt.mapCodeName)
	, encoding (opt.encoding)
	, input_api (opt.input_api)
	, empty_class_policy (opt.empty_class_policy)
{}

opt_t & opt_t::operator = (const opt_t & opt)
{
	new (this) opt_t (opt);
	return *this;
}

bool Opt::apply ()
{
	*((opt_t *) this) = useropt;

	// check groups of mutually exclusive options
	if (DFlag && flag_skeleton)
	{
		error ("incompatible options: '-D, --emit-dot' and '--skeleton'");
		return false;
	}

	// reset to default options that make no sense in current configuration
	if (DFlag)
	{
		bFlag = baseopt.bFlag;
		dFlag = baseopt.dFlag;
		fFlag = baseopt.fFlag;
		gFlag = baseopt.gFlag;
		iFlag = baseopt.iFlag;
		sFlag = baseopt.sFlag;
		tFlag = baseopt.tFlag;
		header_file = baseopt.header_file;
		bEmitYYCh = baseopt.bEmitYYCh;
		bUseStateNext = baseopt.bUseStateNext;
		bUseYYFill = baseopt.bUseYYFill;
		bUseYYFillParam = baseopt.bUseYYFillParam;
		bUseYYFillCheck = baseopt.bUseYYFillCheck;
		bUseYYFillNaked = baseopt.bUseYYFillNaked;
		bUseYYSetConditionParam = baseopt.bUseYYSetConditionParam;
		bUseYYGetConditionNaked = baseopt.bUseYYGetConditionNaked;
		bUseYYSetStateParam = baseopt.bUseYYSetStateParam;
		bUseYYSetStateNaked = baseopt.bUseYYSetStateNaked;
		bUseYYGetStateNaked = baseopt.bUseYYGetStateNaked;
		yybmHexTable = baseopt.yybmHexTable;
		bUseStateAbort = baseopt.bUseStateAbort;
		cGotoThreshold = baseopt.cGotoThreshold;
		topIndent = baseopt.topIndent;
		indString = baseopt.indString;
		labelPrefix = baseopt.labelPrefix;
		condPrefix = baseopt.condPrefix;
		condEnumPrefix = baseopt.condEnumPrefix;
		condDivider = baseopt.condDivider;
		condDividerParam = baseopt.condDividerParam;
		condGoto = baseopt.condGoto;
		condGotoParam = baseopt.condGotoParam;
		yychConversion = baseopt.yychConversion;
		yyFillLength = baseopt.yyFillLength;
		yySetConditionParam = baseopt.yySetConditionParam;
		yySetStateParam = baseopt.yySetStateParam;
		mapCodeName = baseopt.mapCodeName;
		input_api = baseopt.input_api;
	}
	if (flag_skeleton)
	{
		dFlag = baseopt.dFlag;
		fFlag = baseopt.fFlag;
		iFlag = baseopt.iFlag;
		tFlag = baseopt.tFlag;
		header_file = baseopt.header_file;
		bEmitYYCh = baseopt.bEmitYYCh;
		bUseStateNext = baseopt.bUseStateNext;
		bUseYYFill = baseopt.bUseYYFill;
		bUseYYFillParam = baseopt.bUseYYFillParam;
		bUseYYFillCheck = baseopt.bUseYYFillCheck;
		bUseYYFillNaked = baseopt.bUseYYFillNaked;
		bUseYYSetConditionParam = baseopt.bUseYYSetConditionParam;
		bUseYYGetConditionNaked = baseopt.bUseYYGetConditionNaked;
		bUseYYSetStateParam = baseopt.bUseYYSetStateParam;
		bUseYYSetStateNaked = baseopt.bUseYYSetStateNaked;
		bUseYYGetStateNaked = baseopt.bUseYYGetStateNaked;
		bUseStateAbort = baseopt.bUseStateAbort;
		topIndent = baseopt.topIndent;
		indString = baseopt.indString;
		labelPrefix = baseopt.labelPrefix;
		condPrefix = baseopt.condPrefix;
		condEnumPrefix = baseopt.condEnumPrefix;
		condDivider = baseopt.condDivider;
		condDividerParam = baseopt.condDividerParam;
		condGoto = baseopt.condGoto;
		condGotoParam = baseopt.condGotoParam;
		yychConversion = baseopt.yychConversion;
		yyFillLength = baseopt.yyFillLength;
		yySetConditionParam = baseopt.yySetConditionParam;
		yySetStateParam = baseopt.yySetStateParam;
		mapCodeName = baseopt.mapCodeName;
		input_api = baseopt.input_api;
	}
	if (bCaseInsensitive)
	{
		bCaseInverted = baseopt.bCaseInverted;
	}
	if (!cFlag)
	{
		tFlag = baseopt.tFlag;
		header_file = baseopt.header_file;
		bUseYYSetConditionParam = baseopt.bUseYYSetConditionParam;
		bUseYYGetConditionNaked = baseopt.bUseYYGetConditionNaked;
		condPrefix = baseopt.condPrefix;
		condEnumPrefix = baseopt.condEnumPrefix;
		condDivider = baseopt.condDivider;
		condDividerParam = baseopt.condDividerParam;
		condGoto = baseopt.condGoto;
		condGotoParam = baseopt.condGotoParam;
		yySetConditionParam = baseopt.yySetConditionParam;
		mapCodeName.erase ("YYCONDTYPE");
		mapCodeName.erase ("YYGETCONDITION");
		mapCodeName.erase ("YYSETCONDITION");
		mapCodeName.erase ("yyctable");
	}
	if (!fFlag)
	{
		bUseStateNext = baseopt.bUseStateNext;
		bUseYYSetStateParam = baseopt.bUseYYSetStateParam;
		bUseYYSetStateNaked = baseopt.bUseYYSetStateNaked;
		bUseYYGetStateNaked = baseopt.bUseYYGetStateNaked;
		bUseStateAbort = baseopt.bUseStateAbort;
		yySetStateParam = baseopt.yySetStateParam;
		mapCodeName.erase ("YYGETSTATE");
		mapCodeName.erase ("YYSETSTATE");
		mapCodeName.erase ("yyaccept");
		mapCodeName.erase ("yyFillLabel");
		mapCodeName.erase ("yyNext");
	}
	if (!bFlag)
	{
		yybmHexTable = baseopt.yybmHexTable;
		mapCodeName.erase ("yybm");
	}
	if (!gFlag)
	{
		cGotoThreshold = baseopt.cGotoThreshold;
		mapCodeName.erase ("yytarget");
	}
	if (input_api.type () != InputAPI::DEFAULT)
	{
		mapCodeName.erase ("YYCURSOR");
		mapCodeName.erase ("YYMARKER");
		mapCodeName.erase ("YYCTXMARKER");
		mapCodeName.erase ("YYLIMIT");
	}
	if (input_api.type () != InputAPI::CUSTOM)
	{
		mapCodeName.erase ("YYPEEK");
		mapCodeName.erase ("YYSKIP");
		mapCodeName.erase ("YYBACKUP");
		mapCodeName.erase ("YYBACKUPCTX");
		mapCodeName.erase ("YYRESTORE");
		mapCodeName.erase ("YYRESTORECTX");
		mapCodeName.erase ("YYLESSTHAN");
	}
	if (!dFlag)
	{
		mapCodeName.erase ("YYDEBUG");
	}

	// force individual options
	if (DFlag)
	{
		iFlag = true;
	}
	if (flag_skeleton)
	{
		iFlag = true;
		input_api.set (InputAPI::CUSTOM);
		indString = "    ";
		topIndent = 2;
	}
	if (encoding.type () == Enc::UCS2)
	{
		sFlag = true;
	}
	if (encoding.type () == Enc::UTF16)
	{
		sFlag = true;
	}
	if (encoding.type () == Enc::UTF32)
	{
		sFlag = true;
	}
	if (bFlag)
	{
		sFlag = true;
	}
	if (gFlag)
	{
		bFlag = true;
		sFlag = true;
	}

	return true;
}

void Opt::bit_vectors ()
{
	useropt.bFlag = true;
	useropt.sFlag = true;
}

void Opt::start_conditions ()
{
	useropt.cFlag = true;
}

void Opt::debug_output ()
{
	useropt.dFlag = true;
}

void Opt::emit_dot ()
{
	useropt.DFlag = true;
	useropt.iFlag = true;
}

void Opt::storable_state ()
{
	useropt.fFlag = true;
}

void Opt::flex_syntax ()
{
	useropt.FFlag = true;
}

void Opt::computed_gotos ()
{
	useropt.gFlag = true;
	useropt.bFlag = true;
	useropt.sFlag = true;
}

void Opt::no_debug_info ()
{
	useropt.iFlag = true;
}

void Opt::reusable ()
{
	useropt.rFlag = true;
}

void Opt::nested_ifs ()
{
	useropt.sFlag = true;
}

void Opt::no_generation_date ()
{
	useropt.bNoGenerationDate = true;
}

void Opt::case_insensitive ()
{
	useropt.bCaseInsensitive = true;
}

void Opt::case_inverted ()
{
	useropt.bCaseInverted = true;
}

void Opt::skeleton ()
{
	useropt.flag_skeleton = true;
	useropt.iFlag = true;
	useropt.input_api.set (InputAPI::CUSTOM);
}

void Opt::encoding_policy (Enc::policy_t p)
{
	useropt.encoding.setPolicy (p);
}

void Opt::input (InputAPI::type_t i)
{
	useropt.input_api.set (i);
}

void Opt::empty_class (empty_class_policy_t p)
{
	useropt.empty_class_policy = p;
}

bool Opt::source (const char * s)
{
	if (source_file)
	{
		error ("multiple source files: %s, %s", source_file, s);
		return false;
	}
	else
	{
		source_file = s;
		return true;
	}
}

bool Opt::output (const char * s)
{
	if (output_file)
	{
		error ("multiple output files: %s, %s", output_file, s);
		return false;
	}
	else
	{
		output_file = s;
		return true;
	}
}

bool Opt::type_header (const char * s)
{
	if (useropt.header_file)
	{
		error ("multiple header files: %s, %s", useropt.header_file, s);
		return false;
	}
	else
	{
		useropt.tFlag = true;
		useropt.header_file = s;
		return true;
	}
}

bool Opt::ecb ()
{
	return useropt.encoding.set (Enc::EBCDIC);
}

bool Opt::unicode ()
{
	useropt.sFlag = true;
	return useropt.encoding.set(Enc::UTF32);
}

bool Opt::wide_chars ()
{
	useropt.sFlag = true;
	return useropt.encoding.set(Enc::UCS2);
}

bool Opt::utf_16 ()
{
	useropt.sFlag = true;
	return useropt.encoding.set(Enc::UTF16);
}

bool Opt::utf_8 ()
{
	return useropt.encoding.set(Enc::UTF8);
}

} // namespace re2c
