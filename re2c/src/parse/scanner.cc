#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"

// used by Scanner::fatal_at and Scanner::fatalf
#if defined(_MSC_VER) && !defined(vsnprintf)
#    define vsnprintf _vsnprintf
#endif

namespace re2c {

void Scanner::config(const std::string & cfg, int num)
{
	if (cfg == "indent:top")
	{
		if (num < 0)
		{
			fatal("configuration 'indent:top' must be a positive integer");
		}
		topIndent = num;
	}
	else if (cfg == "yybm:hex")
	{
		yybmHexTable = num != 0;
	}
	else if (cfg == "startlabel")
	{
		out.set_force_start_label (num != 0);
	}
	else if (cfg == "state:abort")
	{
		bUseStateAbort = num != 0;
	}
	else if (cfg == "state:nextlabel")
	{
		bUseStateNext = num != 0;
	}
	else if (cfg == "yyfill:enable")
	{
		bUseYYFill = num != 0;
	}
	else if (cfg == "yyfill:parameter")
	{
		bUseYYFillParam = num != 0;
	}
	else if (cfg == "yyfill:check")
	{
		bUseYYFillCheck = num != 0;
	}
	else if (cfg == "cgoto:threshold")
	{
		cGotoThreshold = num;
	}
	else if (cfg == "yych:conversion")
	{
		if (num)
		{
			yychConversion  = "(";
			yychConversion += mapCodeName["YYCTYPE"];
			yychConversion += ")";
		}
		else
		{
			yychConversion  = "";
		}
	}
	else if (cfg == "yych:emit")
	{
		bEmitYYCh = num != 0;
	}
	else if (cfg == "define:YYFILL:naked")
	{
		bUseYYFillNaked = num != 0;
	}
	else if (cfg == "define:YYGETCONDITION:naked")
	{
		bUseYYGetConditionNaked = num != 0;
	}
	else if (cfg == "define:YYGETSTATE:naked")
	{
		bUseYYGetStateNaked = num != 0;
	}
	else if (cfg == "define:YYSETSTATE:naked")
	{
		bUseYYSetStateNaked = num != 0;
	}
	else if (cfg == "flags:e")
	{
		if (num != 0)
		{
			if (!encoding.set(Enc::EBCDIC))
				fatal("Cannot set '-e' switch: please reset '-w', '-x', '-u' and '-8' switches at first.\n");
		}
		else
			encoding.unset(Enc::EBCDIC);
	}
	else if (cfg == "flags:u")
	{
		if (num != 0)
		{
			if (!encoding.set(Enc::UTF32))
				fatal("Cannot set '-u' switch: please reset '-e', '-w', '-x' and '-8' switches at first.\n");
		}
		else
			encoding.unset(Enc::UTF32);
	}
	else if (cfg == "flags:w")
	{
		if (num != 0)
		{
			if (!encoding.set(Enc::UCS2))
				fatal("Cannot set '-w' switch: please reset '-e', '-x', '-u' and '-8' switches at first.\n");
		}
		else
			encoding.unset(Enc::UCS2);
	}
	else if (cfg == "flags:x")
	{
		if (num != 0)
		{
			if (!encoding.set(Enc::UTF16))
				fatal("Cannot set '-x' switch: please reset '-e', '-x', '-u' and '-8' switches at first.\n");
		}
		else
			encoding.unset(Enc::UTF16);
	}
	else if (cfg == "flags:8")
	{
		if (num != 0)
		{
			if (!encoding.set(Enc::UTF8))
				fatal("Cannot set '-8' switch: please reset '-e', '-w', '-x' and '-u' switches at first.\n");
		}
		else
			encoding.unset(Enc::UTF8);
	}
	else
	{
		fatalf("unrecognized configuration name '%s' or illegal integer value", cfg.c_str());
	}
}

static std::set<std::string> mapVariableKeys;
static std::set<std::string> mapDefineKeys;
static std::set<std::string> mapLabelKeys;

void Scanner::config(const std::string & cfg, const std::string & val)
{
	if (mapDefineKeys.empty())
	{
		mapVariableKeys.insert("variable:yyaccept");
		mapVariableKeys.insert("variable:yybm");
		mapVariableKeys.insert("variable:yych");
		mapVariableKeys.insert("variable:yyctable");
		mapVariableKeys.insert("variable:yystable");
		mapVariableKeys.insert("variable:yytarget");
		mapDefineKeys.insert("define:YYBACKUP");
		mapDefineKeys.insert("define:YYBACKUPCTX");
		mapDefineKeys.insert("define:YYCONDTYPE");
		mapDefineKeys.insert("define:YYCTXMARKER");
		mapDefineKeys.insert("define:YYCTYPE");
		mapDefineKeys.insert("define:YYCURSOR");
		mapDefineKeys.insert("define:YYDEBUG");
		mapDefineKeys.insert("define:YYFILL");
		mapDefineKeys.insert("define:YYGETCONDITION");
		mapDefineKeys.insert("define:YYGETSTATE");
		mapDefineKeys.insert("define:YYLESSTHAN");
		mapDefineKeys.insert("define:YYLIMIT");
		mapDefineKeys.insert("define:YYMARKER");
		mapDefineKeys.insert("define:YYPEEK");
		mapDefineKeys.insert("define:YYRESTORE");
		mapDefineKeys.insert("define:YYRESTORECTX");
		mapDefineKeys.insert("define:YYSETCONDITION");
		mapDefineKeys.insert("define:YYSETSTATE");
		mapDefineKeys.insert("define:YYSKIP");
		mapLabelKeys.insert("label:yyFillLabel");
		mapLabelKeys.insert("label:yyNext");
	}

	std::string strVal;

	const uint32_t val_len = val.size ();
	if (val_len >= 2 && val[0] == val[val_len - 1]
		&& (val[0] == '"' || val[0] == '\''))
	{
		SubStr tmp (val.c_str () + 1, val_len - 2);
		unescape (tmp, strVal);
	}
	else
	{
		strVal = val;
	}

	if (cfg == "indent:string")
	{
		indString = strVal;
	}
	else if (cfg == "startlabel")
	{
		out.set_user_start_label (strVal);
	}
	else if (cfg == "labelprefix")
	{
		labelPrefix = strVal;
	}
	else if (cfg == "condprefix")
	{
		condPrefix = strVal;
	}
	else if (cfg == "condenumprefix")
	{
		condEnumPrefix = strVal;
	}
	else if (cfg == "cond:divider")
	{
		condDivider = strVal;
	}
	else if (cfg == "cond:divider@cond")
	{
		condDividerParam = strVal;
	}
	else if (cfg == "cond:goto")
	{
		condGoto = strVal;
	}
	else if (cfg == "cond:goto@cond")
	{
		condGotoParam = strVal;
	}
	else if (cfg == "define:YYFILL@len")
	{
		yyFillLength = strVal;
		bUseYYFillParam = false;
	}
	else if (cfg == "define:YYSETCONDITION@cond")
	{
		yySetConditionParam = strVal;
		bUseYYSetConditionParam = false;
	}
	else if (cfg == "define:YYSETSTATE@state")
	{
		yySetStateParam = strVal;
		bUseYYSetStateParam = false;
	}
	else if (mapVariableKeys.find(cfg) != mapVariableKeys.end())
	{
		if (!mapCodeName.insert(std::make_pair(cfg.substr(sizeof("variable:") - 1), strVal)).second)
		{
			fatalf("variable '%s' already being used and cannot be changed", cfg.c_str());
		}
	}
	else if (mapDefineKeys.find(cfg) != mapDefineKeys.end())
	{
		if (!mapCodeName.insert(std::make_pair(cfg.substr(sizeof("define:") - 1), strVal)).second)
		{
			fatalf("define '%s' already being used and cannot be changed", cfg.c_str());
		}
	}
	else if (mapLabelKeys.find(cfg) != mapLabelKeys.end())
	{
		if (!mapCodeName.insert(std::make_pair(cfg.substr(sizeof("label:") - 1), strVal)).second)
		{
			fatalf("label '%s' already being used and cannot be changed", cfg.c_str());
		}
	}
	else
	{
		std::string msg = "unrecognized configuration name '";
		msg += cfg;
		msg += "' or illegal string value";
		fatal(msg.c_str());
	}
}

ScannerState::ScannerState ()
	: tok (NULL)
	, ptr (NULL)
	, cur (NULL)
	, pos (NULL)
	, ctx (NULL)
	, bot (NULL)
	, lim (NULL)
	, top (NULL)
	, eof (NULL)
	, tchar (0)
	, tline (0)
	, cline (1)
	, iscfg (0)
	, in_parse (false)
{}

ScannerState::ScannerState (const ScannerState & s)
	: tok (s.tok)
	, ptr (s.ptr)
	, cur (s.cur)
	, pos (s.pos)
	, ctx (s.ctx)
	, bot (s.bot)
	, lim (s.lim)
	, top (s.top)
	, eof (s.eof)
	, tchar (s.tchar)
	, tline (s.tline)
	, cline (s.cline)
	, iscfg (s.iscfg)
	, in_parse (s.in_parse)
{}

ScannerState & ScannerState::operator = (const ScannerState & s)
{
	tok = s.tok;
	ptr = s.ptr;
	cur = s.cur;
	pos = s.pos;
	ctx = s.ctx;
	bot = s.bot;
	lim = s.lim;
	top = s.top;
	eof = s.eof;
	tchar = s.tchar;
	tline = s.tline;
	cline = s.cline;
	iscfg = s.iscfg;
	in_parse = s.in_parse;
	return * this;
}

Scanner::Scanner (Input & i, OutputFile & o)
	: ScannerState ()
	, in (i)
	, out (o)
{}

char *Scanner::fill(char *cursor, uint32_t need)
{
	if(!eof)
	{
		uint32_t cnt;
		/* Do not get rid of anything when rFlag is active. Otherwise
		 * get rid of everything that was already handedout. */
		if (!rFlag)
		{
			cnt = tok - bot;
			if (cnt)
			{
				memmove(bot, tok, top - tok);
				tok  = bot;
				ptr -= cnt;
				cur -= cnt;
				pos -= cnt;
				lim -= cnt;
				ctx -= cnt;
				cursor -= cnt;
			}
		}
		/* In crease buffer size. */
		if (BSIZE > need)
		{
			need = BSIZE;
		}
		if (static_cast<uint32_t>(top - lim) < need)
		{
			char *buf = new char[(lim - bot) + need];
			if (!buf)
			{
				fatal("Out of memory");
			}
			memcpy(buf, bot, lim - bot);
			tok = &buf[tok - bot];
			ptr = &buf[ptr - bot];
			cur = &buf[cur - bot];
			pos = &buf[pos - bot];
			lim = &buf[lim - bot];
			top = &lim[need];
			ctx = &buf[ctx - bot];
			cursor = &buf[cursor - bot];
			delete [] bot;
			bot = buf;
		}
		/* Append to buffer. */
		cnt = fread (lim, 1, need, in.file);
		if (cnt != need)
		{
			eof = &lim[cnt];
			*eof++ = '\0';
		}
		lim += cnt;
	}
	return cursor;
}

void Scanner::set_in_parse(bool new_in_parse)
{
	in_parse = new_in_parse;
}

void Scanner::fatal_at(uint32_t line, uint32_t ofs, const char *msg) const
{
	std::cerr << "re2c: error: "
		<< "line " << line << ", column " << (tchar + ofs + 1) << ": "
		<< msg << std::endl;
	exit(1);
}

void Scanner::fatal(uint32_t ofs, const char *msg) const
{
	fatal_at(in_parse ? tline : cline, ofs, msg);
}

void Scanner::fatalf_at(uint32_t line, const char* fmt, ...) const
{
	char szBuf[4096];

	va_list args;
	
	va_start(args, fmt);
	vsnprintf(szBuf, sizeof(szBuf), fmt, args);
	va_end(args);
	
	szBuf[sizeof(szBuf)-1] = '0';
	
	fatal_at(line, 0, szBuf);
}

void Scanner::fatalf(const char *fmt, ...) const
{
	char szBuf[4096];

	va_list args;
	
	va_start(args, fmt);
	vsnprintf(szBuf, sizeof(szBuf), fmt, args);
	va_end(args);
	
	szBuf[sizeof(szBuf)-1] = '0';
	
	fatal(szBuf);
}

Scanner::~Scanner()
{
	if (bot)
	{
		delete [] bot;
	}
}

void Scanner::reuse()
{
	out.label_counter.reset ();
	last_fill_index = 0;
	bWroteGetState = false;
	bWroteCondCheck = false;
	mapCodeName.clear();
}

void Scanner::restore_state(const ScannerState& state)
{
	int diff = bot - state.bot;
	char *old_bot = bot;
	char *old_lim = lim;
	char *old_top = top;
	char *old_eof = eof;
	*(ScannerState*)this = state;
	if (diff)
	{
		tok -= diff;
		ptr -= diff;
		cur -= diff;
		pos -= diff;
		ctx -= diff;		
		bot = old_bot;
		lim = old_lim;
		top = old_top;
		eof = old_eof;
	}
}

} // namespace re2c
