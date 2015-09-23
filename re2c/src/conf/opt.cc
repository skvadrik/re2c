#include "src/conf/msg.h"
#include "src/conf/opt.h"

namespace re2c
{

Opt opts;

opt_t::opt_t ()
	: target (CODE)
	, bFlag (false)
	, cFlag (false)
	, dFlag (false)
	, fFlag (false)
	, FFlag (false)
	, gFlag (false)
	, iFlag (false)
	, rFlag (false)
	, sFlag (false)
	, tFlag (false)
	, header_file (NULL)
	, bNoGenerationDate (false)
	, bEmitYYCh (true)
	, yychConversion (false)
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
	, yyFillLength ("@@")
	, yySetConditionParam ("@@")
	, yySetStateParam ("@@")
	, mapCodeName ()
	, encoding ()
	, input_api ()
	, empty_class_policy (EMPTY_CLASS_MATCH_EMPTY)
{}

opt_t::opt_t (const opt_t & opt)
	: target (opt.target)
	, bFlag (opt.bFlag)
	, cFlag (opt.cFlag)
	, dFlag (opt.dFlag)
	, fFlag (opt.fFlag)
	, FFlag (opt.FFlag)
	, gFlag (opt.gFlag)
	, iFlag (opt.iFlag)
	, rFlag (opt.rFlag)
	, sFlag (opt.sFlag)
	, tFlag (opt.tFlag)
	, header_file (opt.header_file)
	, bNoGenerationDate (opt.bNoGenerationDate)
	, bEmitYYCh (opt.bEmitYYCh)
	, yychConversion (opt.yychConversion)
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

void opt_t::fix ()
{
	// some options either make no sense or must have fixed value
	// with current target: reset them to default
	switch (target)
	{
		case DOT:
			// default code generation options
			bFlag = Opt::baseopt.bFlag;
			gFlag = Opt::baseopt.gFlag;
			cGotoThreshold = Opt::baseopt.cGotoThreshold;
			sFlag = Opt::baseopt.sFlag;
			// default environment-insensitive formatting
			yybmHexTable = Opt::baseopt.yybmHexTable;
			// fallthrough
		case SKELETON:
			// default line information
			iFlag = Opt::baseopt.iFlag;
			// default environment-sensitive formatting
			topIndent = Opt::baseopt.topIndent;
			indString = Opt::baseopt.indString;
			condDivider = Opt::baseopt.condDivider;
			condDividerParam = Opt::baseopt.condDividerParam;
			// default environment bindings
			input_api = Opt::baseopt.input_api;
			mapCodeName = Opt::baseopt.mapCodeName;
			dFlag = Opt::baseopt.dFlag;
			fFlag = Opt::baseopt.fFlag;
			tFlag = Opt::baseopt.tFlag;
			header_file = Opt::baseopt.header_file;
			bEmitYYCh = Opt::baseopt.bEmitYYCh;
			bUseStateNext = Opt::baseopt.bUseStateNext;
			bUseYYFill = Opt::baseopt.bUseYYFill;
			bUseYYFillParam = Opt::baseopt.bUseYYFillParam;
			bUseYYFillCheck = Opt::baseopt.bUseYYFillCheck;
			bUseYYFillNaked = Opt::baseopt.bUseYYFillNaked;
			bUseYYSetConditionParam = Opt::baseopt.bUseYYSetConditionParam;
			bUseYYGetConditionNaked = Opt::baseopt.bUseYYGetConditionNaked;
			bUseYYSetStateParam = Opt::baseopt.bUseYYSetStateParam;
			bUseYYSetStateNaked = Opt::baseopt.bUseYYSetStateNaked;
			bUseYYGetStateNaked = Opt::baseopt.bUseYYGetStateNaked;
			bUseStateAbort = Opt::baseopt.bUseStateAbort;
			labelPrefix = Opt::baseopt.labelPrefix;
			condPrefix = Opt::baseopt.condPrefix;
			condEnumPrefix = Opt::baseopt.condEnumPrefix;
			condGoto = Opt::baseopt.condGoto;
			condGotoParam = Opt::baseopt.condGotoParam;
			yychConversion = Opt::baseopt.yychConversion;
			yyFillLength = Opt::baseopt.yyFillLength;
			yySetConditionParam = Opt::baseopt.yySetConditionParam;
			yySetStateParam = Opt::baseopt.yySetStateParam;
			break;
		default:
			break;
	}

	if (bCaseInsensitive)
	{
		bCaseInverted = Opt::baseopt.bCaseInverted;
	}

	// respect hierarchy
	if (!cFlag)
	{
		tFlag = Opt::baseopt.tFlag;
		header_file = Opt::baseopt.header_file;
		bUseYYSetConditionParam = Opt::baseopt.bUseYYSetConditionParam;
		bUseYYGetConditionNaked = Opt::baseopt.bUseYYGetConditionNaked;
		condPrefix = Opt::baseopt.condPrefix;
		condEnumPrefix = Opt::baseopt.condEnumPrefix;
		condDivider = Opt::baseopt.condDivider;
		condDividerParam = Opt::baseopt.condDividerParam;
		condGoto = Opt::baseopt.condGoto;
		condGotoParam = Opt::baseopt.condGotoParam;
		yySetConditionParam = Opt::baseopt.yySetConditionParam;
		mapCodeName.erase ("YYCONDTYPE");
		mapCodeName.erase ("YYGETCONDITION");
		mapCodeName.erase ("YYSETCONDITION");
		mapCodeName.erase ("yyctable");
	}
	if (!fFlag)
	{
		bUseStateNext = Opt::baseopt.bUseStateNext;
		bUseYYSetStateParam = Opt::baseopt.bUseYYSetStateParam;
		bUseYYSetStateNaked = Opt::baseopt.bUseYYSetStateNaked;
		bUseYYGetStateNaked = Opt::baseopt.bUseYYGetStateNaked;
		bUseStateAbort = Opt::baseopt.bUseStateAbort;
		yySetStateParam = Opt::baseopt.yySetStateParam;
		mapCodeName.erase ("YYGETSTATE");
		mapCodeName.erase ("YYSETSTATE");
		mapCodeName.erase ("yyaccept");
		mapCodeName.erase ("yyFillLabel");
		mapCodeName.erase ("yyNext");
	}
	if (!bFlag)
	{
		yybmHexTable = Opt::baseopt.yybmHexTable;
		mapCodeName.erase ("yybm");
	}
	if (!gFlag)
	{
		cGotoThreshold = Opt::baseopt.cGotoThreshold;
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
	switch (target)
	{
		case DOT:
			iFlag = true;
			break;
		case SKELETON:
			iFlag = true;
			input_api.set (InputAPI::CUSTOM);
			indString = "    ";
			topIndent = 2;
			break;
		default:
			break;
	}
	switch (encoding.type ())
	{
		case Enc::UCS2:
		case Enc::UTF16:
		case Enc::UTF32:
			sFlag = true;
			break;
		default:
			break;
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
}

const opt_t Opt::baseopt;

void Opt::sync ()
{
	realopt = useropt;
	realopt.fix ();
}

void Opt::set_target (opt_t::target_t tgt)
{
	useropt.target = tgt;
}

void Opt::bit_vectors ()
{
	useropt.bFlag = true;
}

void Opt::start_conditions ()
{
	useropt.cFlag = true;
}

void Opt::debug_output ()
{
	useropt.dFlag = true;
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
	return useropt.encoding.set(Enc::UTF32);
}

bool Opt::wide_chars ()
{
	return useropt.encoding.set(Enc::UCS2);
}

bool Opt::utf_16 ()
{
	return useropt.encoding.set(Enc::UTF16);
}

bool Opt::utf_8 ()
{
	return useropt.encoding.set(Enc::UTF8);
}

bool Opt::sync_mapCodeName (const std::string & key, const std::string & val)
{
	if (!useropt.mapCodeName.insert (std::make_pair (key, val)).second)
	{
		return false;
	}
	sync ();
	return true;
}

void Opt::sync_condPrefix (const std::string & s)
{
	useropt.condPrefix = s;
	sync ();
}

void Opt::sync_condEnumPrefix (const std::string & s)
{
	useropt.condEnumPrefix = s;
	sync ();
}

void Opt::sync_condDivider (const std::string & s)
{
	useropt.condDivider = s;
	sync ();
}

void Opt::sync_condDividerParam (const std::string & s)
{
	useropt.condDividerParam = s;
	sync ();
}

void Opt::sync_condGoto (const std::string & s)
{
	useropt.condGoto = s;
	sync ();
}

void Opt::sync_condGotoParam (const std::string & s)
{
	useropt.condGotoParam = s;
	sync ();
}

void Opt::sync_cGotoThreshold (uint32_t n)
{
	useropt.cGotoThreshold = n;
	sync ();
}

void Opt::sync_bUseYYFillNaked (bool b)
{
	useropt.bUseYYFillNaked = b;
	sync ();
}

void Opt::sync_yyFillLength (const std::string & s)
{
	useropt.yyFillLength = s;
	useropt.bUseYYFillParam = false;
	sync ();
}

void Opt::sync_bUseYYGetConditionNaked (bool b)
{
	useropt.bUseYYGetConditionNaked = b;
	sync ();
}

void Opt::sync_bUseYYGetStateNaked (bool b)
{
	useropt.bUseYYGetStateNaked = b;
	sync ();
}

void Opt::sync_yySetConditionParam (const std::string & s)
{
	useropt.yySetConditionParam = s;
	useropt.bUseYYSetConditionParam = false;
	sync ();
}

void Opt::sync_bUseYYSetStateNaked (bool b)
{
	useropt.bUseYYSetStateNaked = b;
	sync ();
}

void Opt::sync_yySetStateParam (const std::string & s)
{
	useropt.yySetStateParam = s;
	useropt.bUseYYSetStateParam = false;
	sync ();
}

bool Opt::sync_encoding (Enc::type_t t)
{
	if (!useropt.encoding.set (t))
	{
		return false;
	}
	sync ();
	return true;
}

void Opt::sync_encoding_unset (Enc::type_t t)
{
	useropt.encoding.unset (t);
	sync ();
}

void Opt::sync_indString (const std::string & s)
{
	useropt.indString = s;
	sync ();
}

void Opt::sync_topIndent (uint32_t n)
{
	useropt.topIndent = n;
	sync ();
}

void Opt::sync_labelPrefix (const std::string & s)
{
	useropt.labelPrefix = s;
	sync ();
}

void Opt::sync_bUseStateAbort (bool b)
{
	useropt.bUseStateAbort = b;
	sync ();
}

void Opt::sync_bUseStateNext (bool b)
{
	useropt.bUseStateNext = b;
	sync ();
}

void Opt::sync_yybmHexTable (bool b)
{
	useropt.yybmHexTable = b;
	sync ();
}

void Opt::sync_yychConversion (bool b)
{
	useropt.yychConversion = b;
	sync ();
}

void Opt::sync_bEmitYYCh (bool b)
{
	useropt.bEmitYYCh = b;
	sync ();
}

void Opt::sync_bUseYYFillCheck (bool b)
{
	useropt.bUseYYFillCheck = b;
	sync ();
}

void Opt::sync_bUseYYFill (bool b)
{
	useropt.bUseYYFill = b;
	sync ();
}

void Opt::sync_bUseYYFillParam (bool b)
{
	useropt.bUseYYFillParam = b;
	sync ();
}

void Opt::sync_reset_encoding (const Enc & enc)
{
	useropt.encoding = enc;
	sync ();
}

void Opt::sync_reset_mapCodeName ()
{
	useropt.mapCodeName.clear ();
	sync ();
}

} // namespace re2c
