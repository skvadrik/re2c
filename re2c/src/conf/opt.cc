#include "src/conf/msg.h"
#include "src/conf/opt.h"

namespace re2c
{

Opt opts;

opt_t::opt_t ()
	: target (CODE)
	, bNoGenerationDate (false)
	, encoding ()
	, bCaseInsensitive (false)
	, bCaseInverted (false)
	, empty_class_policy (EMPTY_CLASS_MATCH_EMPTY)
	, cFlag (false)
	, tFlag (false)
	, header_file (NULL)
	, yycondtype ("YYCONDTYPE")
	, yysetcondition ("YYSETCONDITION(@@);")
	, yygetcondition ("YYGETCONDITION")
	, yyctable ("yyctable")
	, yySetConditionParam ("@@")
	, bUseYYGetConditionNaked (false)
	, condPrefix ("yyc_")
	, condEnumPrefix ("yyc")
	, condDivider ("/* *********************************** */")
	, condDividerParam ("@@")
	, condGoto ("goto @@;")
	, condGotoParam ("@@")
	, fFlag (false)
	, yysetstate ("YYSETSTATE(@@);")
	, yygetstate ("YYGETSTATE")
	, yyfilllabel ("yyFillLabel")
	, yynext ("yyNext")
	, yyaccept ("yyaccept")
	, yySetStateParam ("@@")
	, bUseYYSetStateNaked (false)
	, bUseYYGetStateNaked (false)
	, bUseStateAbort (false)
	, bUseStateNext (false)
	, rFlag (false)
	, FFlag (false)
	, sFlag (false)
	, bFlag (false)
	, yybm ("yybm")
	, yybmHexTable (false)
	, gFlag (false)
	, yytarget ("yytarget")
	, cGotoThreshold (9)
	, topIndent (0)
	, indString ("\t")
	, input_api ()
	, yycursor ("YYCURSOR")
	, yymarker ("YYMARKER")
	, yyctxmarker ("YYCTXMARKER")
	, yylimit ("YYLIMIT")
	, yypeek ("YYPEEK")
	, yyskip ("YYSKIP")
	, yybackup ("YYBACKUP")
	, yybackupctx ("YYBACKUPCTX")
	, yyrestore ("YYRESTORE")
	, yyrestorectx ("YYRESTORECTX")
	, yylessthan ("YYLESSTHAN")
	, iFlag (false)
	, dFlag (false)
	, yydebug ("YYDEBUG")
	, yyctype ("YYCTYPE")
	, yych ("yych")
	, bEmitYYCh (true)
	, yychConversion (false)
	, yyfill ("YYFILL")
	, bUseYYFill (true)
	, bUseYYFillParam (true)
	, bUseYYFillCheck (true)
	, bUseYYFillNaked (false)
	, yyFillLength ("@@")
	, labelPrefix ("yy")
{}

opt_t::opt_t (const opt_t & opt)
	: target (opt.target)
	, bNoGenerationDate (opt.bNoGenerationDate)
	, encoding (opt.encoding)
	, bCaseInsensitive (opt.bCaseInsensitive)
	, bCaseInverted (opt.bCaseInverted)
	, empty_class_policy (opt.empty_class_policy)
	, cFlag (opt.cFlag)
	, tFlag (opt.tFlag)
	, header_file (opt.header_file)
	, yycondtype (opt.yycondtype)
	, yysetcondition (opt.yysetcondition)
	, yygetcondition (opt.yygetcondition)
	, yyctable (opt.yyctable)
	, yySetConditionParam (opt.yySetConditionParam)
	, bUseYYGetConditionNaked (opt.bUseYYGetConditionNaked)
	, condPrefix (opt.condPrefix)
	, condEnumPrefix (opt.condEnumPrefix)
	, condDivider (opt.condDivider)
	, condDividerParam (opt.condDividerParam)
	, condGoto (opt.condGoto)
	, condGotoParam (opt.condGotoParam)
	, fFlag (opt.fFlag)
	, yysetstate (opt.yysetstate)
	, yygetstate (opt.yygetstate)
	, yyfilllabel (opt.yyfilllabel)
	, yynext (opt.yynext)
	, yyaccept (opt.yyaccept)
	, yySetStateParam (opt.yySetStateParam)
	, bUseYYSetStateNaked (opt.bUseYYSetStateNaked)
	, bUseYYGetStateNaked (opt.bUseYYGetStateNaked)
	, bUseStateAbort (opt.bUseStateAbort)
	, bUseStateNext (opt.bUseStateNext)
	, rFlag (opt.rFlag)
	, FFlag (opt.FFlag)
	, sFlag (opt.sFlag)
	, bFlag (opt.bFlag)
	, yybm (opt.yybm)
	, yybmHexTable (opt.yybmHexTable)
	, gFlag (opt.gFlag)
	, yytarget (opt.yytarget)
	, cGotoThreshold (opt.cGotoThreshold)
	, topIndent (opt.topIndent)
	, indString (opt.indString)
	, input_api (opt.input_api)
	, yycursor (opt.yycursor)
	, yymarker (opt.yymarker)
	, yyctxmarker (opt.yyctxmarker)
	, yylimit (opt.yylimit)
	, yypeek (opt.yypeek)
	, yyskip (opt.yyskip)
	, yybackup (opt.yybackup)
	, yybackupctx (opt.yybackupctx)
	, yyrestore (opt.yyrestore)
	, yyrestorectx (opt.yyrestorectx)
	, yylessthan (opt.yylessthan)
	, iFlag (opt.iFlag)
	, dFlag (opt.dFlag)
	, yydebug (opt.yydebug)
	, yyctype (opt.yyctype)
	, yych (opt.yych)
	, bEmitYYCh (opt.bEmitYYCh)
	, yychConversion (opt.yychConversion)
	, yyfill (opt.yyfill)
	, bUseYYFill (opt.bUseYYFill)
	, bUseYYFillParam (opt.bUseYYFillParam)
	, bUseYYFillCheck (opt.bUseYYFillCheck)
	, bUseYYFillNaked (opt.bUseYYFillNaked)
	, yyFillLength (opt.yyFillLength)
	, labelPrefix (opt.labelPrefix)
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
			sFlag = Opt::baseopt.sFlag;
			bFlag = Opt::baseopt.bFlag;
			gFlag = Opt::baseopt.gFlag;
			cGotoThreshold = Opt::baseopt.cGotoThreshold;
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
			tFlag = Opt::baseopt.tFlag;
			header_file = Opt::baseopt.header_file;
			yycondtype = Opt::baseopt.yycondtype;
			yysetcondition = Opt::baseopt.yysetcondition;
			yygetcondition = Opt::baseopt.yygetcondition;
			yyctable = Opt::baseopt.yyctable;
			yySetConditionParam = Opt::baseopt.yySetConditionParam;
			bUseYYGetConditionNaked = Opt::baseopt.bUseYYGetConditionNaked;
			condPrefix = Opt::baseopt.condPrefix;
			condEnumPrefix = Opt::baseopt.condEnumPrefix;
			condGoto = Opt::baseopt.condGoto;
			condGotoParam = Opt::baseopt.condGotoParam;
			fFlag = Opt::baseopt.fFlag;
			yysetstate = Opt::baseopt.yysetstate;
			yygetstate = Opt::baseopt.yygetstate;
			yyfilllabel = Opt::baseopt.yyfilllabel;
			yynext = Opt::baseopt.yynext;
			yyaccept = Opt::baseopt.yyaccept;
			yySetStateParam = Opt::baseopt.yySetStateParam;
			bUseYYSetStateNaked = Opt::baseopt.bUseYYSetStateNaked;
			bUseYYGetStateNaked = Opt::baseopt.bUseYYGetStateNaked;
			bUseStateAbort = Opt::baseopt.bUseStateAbort;
			bUseStateNext = Opt::baseopt.bUseStateNext;
			yybm = Opt::baseopt.yybm;
			yytarget = Opt::baseopt.yytarget;
			input_api = Opt::baseopt.input_api;
			yycursor = Opt::baseopt.yycursor;
			yymarker = Opt::baseopt.yymarker;
			yyctxmarker = Opt::baseopt.yyctxmarker;
			yylimit = Opt::baseopt.yylimit;
			yypeek = Opt::baseopt.yypeek;
			yyskip = Opt::baseopt.yyskip;
			yybackup = Opt::baseopt.yybackup;
			yybackupctx = Opt::baseopt.yybackupctx;
			yyrestore = Opt::baseopt.yyrestore;
			yyrestorectx = Opt::baseopt.yyrestorectx;
			yylessthan = Opt::baseopt.yylessthan;
			dFlag = Opt::baseopt.dFlag;
			yydebug = Opt::baseopt.yydebug;
			yyctype = Opt::baseopt.yyctype;
			yych = Opt::baseopt.yych;
			bEmitYYCh = Opt::baseopt.bEmitYYCh;
			yychConversion = Opt::baseopt.yychConversion;
			yyfill = Opt::baseopt.yyfill;
			bUseYYFill = Opt::baseopt.bUseYYFill;
			bUseYYFillParam = Opt::baseopt.bUseYYFillParam;
			bUseYYFillCheck = Opt::baseopt.bUseYYFillCheck;
			bUseYYFillNaked = Opt::baseopt.bUseYYFillNaked;
			yyFillLength = Opt::baseopt.yyFillLength;
			labelPrefix = Opt::baseopt.labelPrefix;
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
		yycondtype = Opt::baseopt.yycondtype;
		yysetcondition = Opt::baseopt.yysetcondition;
		yygetcondition = Opt::baseopt.yygetcondition;
		yyctable = Opt::baseopt.yyctable;
		yySetConditionParam = Opt::baseopt.yySetConditionParam;
		bUseYYGetConditionNaked = Opt::baseopt.bUseYYGetConditionNaked;
		condPrefix = Opt::baseopt.condPrefix;
		condEnumPrefix = Opt::baseopt.condEnumPrefix;
		condDivider = Opt::baseopt.condDivider;
		condDividerParam = Opt::baseopt.condDividerParam;
		condGoto = Opt::baseopt.condGoto;
		condGotoParam = Opt::baseopt.condGotoParam;
	}
	if (!fFlag)
	{
		yysetstate = Opt::baseopt.yysetstate;
		yygetstate = Opt::baseopt.yygetstate;
		yyfilllabel = Opt::baseopt.yyfilllabel;
		yynext = Opt::baseopt.yynext;
		yyaccept = Opt::baseopt.yyaccept;
		yySetStateParam = Opt::baseopt.yySetStateParam;
		bUseYYSetStateNaked = Opt::baseopt.bUseYYSetStateNaked;
		bUseYYGetStateNaked = Opt::baseopt.bUseYYGetStateNaked;
		bUseStateAbort = Opt::baseopt.bUseStateAbort;
		bUseStateNext = Opt::baseopt.bUseStateNext;
	}
	if (!bFlag)
	{
		yybmHexTable = Opt::baseopt.yybmHexTable;
		yybm = Opt::baseopt.yybm;
	}
	if (!gFlag)
	{
		cGotoThreshold = Opt::baseopt.cGotoThreshold;
		yytarget = Opt::baseopt.yytarget;
	}
	if (input_api.type () != InputAPI::DEFAULT)
	{
		yycursor = Opt::baseopt.yycursor;
		yymarker = Opt::baseopt.yymarker;
		yyctxmarker = Opt::baseopt.yyctxmarker;
		yylimit = Opt::baseopt.yylimit;
	}
	if (input_api.type () != InputAPI::CUSTOM)
	{
		yypeek = Opt::baseopt.yypeek;
		yyskip = Opt::baseopt.yyskip;
		yybackup = Opt::baseopt.yybackup;
		yybackupctx = Opt::baseopt.yybackupctx;
		yyrestore = Opt::baseopt.yyrestore;
		yyrestorectx = Opt::baseopt.yyrestorectx;
		yylessthan = Opt::baseopt.yylessthan;
	}
	if (!dFlag)
	{
		yydebug = Opt::baseopt.yydebug;
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
	if (header_file != NULL)
	{
		tFlag = true;
	}
}

realopt_t::realopt_t (useropt_t & opt)
	: real ()
	, user (opt)
{}

const opt_t * realopt_t::operator -> ()
{
	sync ();
	return &real;
}

void realopt_t::sync ()
{
	if (user.diverge)
	{
		real = user.opt;
		real.fix ();
		user.diverge = false;
	}
}

useropt_t::useropt_t ()
	: opt ()
	, diverge (false)
{}

opt_t * useropt_t::operator -> ()
{
	diverge = true;
	return &opt;
}

const opt_t Opt::baseopt;

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

void Opt::reset_encoding (const Enc & enc)
{
	useropt->encoding = enc;
}

void Opt::reset_mapCodeName ()
{
	// historically arranged set of names
	// no actual reason why these particular options should be reset
	useropt->yybackup = Opt::baseopt.yybackup;
	useropt->yybackupctx = Opt::baseopt.yybackupctx;
	useropt->yycondtype = Opt::baseopt.yycondtype;
	useropt->yyctxmarker = Opt::baseopt.yyctxmarker;
	useropt->yyctype = Opt::baseopt.yyctype;
	useropt->yycursor = Opt::baseopt.yycursor;
	useropt->yydebug = Opt::baseopt.yydebug;
	useropt->yyfill = Opt::baseopt.yyfill;
	useropt->yygetcondition = Opt::baseopt.yygetcondition;
	useropt->yygetstate = Opt::baseopt.yygetstate;
	useropt->yylessthan = Opt::baseopt.yylessthan;
	useropt->yylimit = Opt::baseopt.yylimit;
	useropt->yymarker = Opt::baseopt.yymarker;
	useropt->yypeek = Opt::baseopt.yypeek;
	useropt->yyrestore = Opt::baseopt.yyrestore;
	useropt->yyrestorectx = Opt::baseopt.yyrestorectx;
	useropt->yysetcondition = Opt::baseopt.yysetcondition;
	useropt->yysetstate = Opt::baseopt.yysetstate;
	useropt->yyskip = Opt::baseopt.yyskip;
	useropt->yyfilllabel = Opt::baseopt.yyfilllabel;
	useropt->yynext = Opt::baseopt.yynext;
	useropt->yyaccept = Opt::baseopt.yyaccept;
	useropt->yybm = Opt::baseopt.yybm;
	useropt->yych = Opt::baseopt.yych;
	useropt->yyctable = Opt::baseopt.yyctable;
	useropt->yytarget = Opt::baseopt.yytarget;
}

} // namespace re2c
