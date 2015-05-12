#include <stdarg.h>

#include "scanner.h"

namespace re2c {

void Scanner::config(const Str& cfg, int num)
{
	if (cfg.to_string() == "indent:top")
	{
		if (num < 0)
		{
			fatal("configuration 'indent:top' must be a positive integer");
		}
		topIndent = num;
	}
	else if (cfg.to_string() == "yybm:hex")
	{
		yybmHexTable = num != 0;
	}
	else if (cfg.to_string() == "startlabel")
	{
		bUseStartLabel = num != 0;
		startLabelName = "";
	}
	else if (cfg.to_string() == "state:abort")
	{
		bUseStateAbort = num != 0;
	}
	else if (cfg.to_string() == "state:nextlabel")
	{
		bUseStateNext = num != 0;
	}
	else if (cfg.to_string() == "yyfill:enable")
	{
		bUseYYFill = num != 0;
	}
	else if (cfg.to_string() == "yyfill:parameter")
	{
		bUseYYFillParam = num != 0;
	}
	else if (cfg.to_string() == "yyfill:check")
	{
		bUseYYFillCheck = num != 0;
	}
	else if (cfg.to_string() == "cgoto:threshold")
	{
		cGotoThreshold = num;
	}
	else if (cfg.to_string() == "yych:conversion")
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
	else if (cfg.to_string() == "yych:emit")
	{
		bEmitYYCh = num != 0;
	}
	else if (cfg.to_string() == "define:YYFILL:naked")
	{
		bUseYYFillNaked = num != 0;
	}
	else if (cfg.to_string() == "define:YYGETCONDITION:naked")
	{
		bUseYYGetConditionNaked = num != 0;
	}
	else if (cfg.to_string() == "define:YYGETSTATE:naked")
	{
		bUseYYGetStateNaked = num != 0;
	}
	else if (cfg.to_string() == "define:YYSETSTATE:naked")
	{
		bUseYYSetStateNaked = num != 0;
	}
	else if (cfg.to_string() == "flags:e")
	{
		if (num != 0)
		{
			if (!encoding.set(Enc::EBCDIC))
				fatal("Cannot set '-e' switch: please reset '-w', '-x', '-u' and '-8' switches at first.\n");
		}
		else
			encoding.unset(Enc::EBCDIC);
	}
	else if (cfg.to_string() == "flags:u")
	{
		if (num != 0)
		{
			if (!encoding.set(Enc::UTF32))
				fatal("Cannot set '-u' switch: please reset '-e', '-w', '-x' and '-8' switches at first.\n");
		}
		else
			encoding.unset(Enc::UTF32);
	}
	else if (cfg.to_string() == "flags:w")
	{
		if (num != 0)
		{
			if (!encoding.set(Enc::UCS2))
				fatal("Cannot set '-w' switch: please reset '-e', '-x', '-u' and '-8' switches at first.\n");
		}
		else
			encoding.unset(Enc::UCS2);
	}
	else if (cfg.to_string() == "flags:x")
	{
		if (num != 0)
		{
			if (!encoding.set(Enc::UTF16))
				fatal("Cannot set '-x' switch: please reset '-e', '-x', '-u' and '-8' switches at first.\n");
		}
		else
			encoding.unset(Enc::UTF16);
	}
	else if (cfg.to_string() == "flags:8")
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
		fatalf("unrecognized configuration name '%s' or illegal integer value", cfg.to_string().c_str());
	}
}

static std::set<std::string> mapVariableKeys;
static std::set<std::string> mapDefineKeys;
static std::set<std::string> mapLabelKeys;

void Scanner::config(const Str& cfg, const Str& val)
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

	if (val.len >= 2 && val.str[0] == val.str[val.len-1] 
	&& (val.str[0] == '"' || val.str[0] == '\''))
	{
		SubStr tmp(val.str + 1, val.len - 2);
		unescape(tmp, strVal);
	}
	else
	{
		strVal = val.to_string();
	}

	if (cfg.to_string() == "indent:string")
	{
		indString = strVal;
	}
	else if (cfg.to_string() == "startlabel")
	{
		startLabelName = strVal;
		bUseStartLabel = !startLabelName.empty();
	}
	else if (cfg.to_string() == "labelprefix")
	{
		labelPrefix = strVal;
	}
	else if (cfg.to_string() == "condprefix")
	{
		condPrefix = strVal;
	}
	else if (cfg.to_string() == "condenumprefix")
	{
		condEnumPrefix = strVal;
	}
	else if (cfg.to_string() == "cond:divider")
	{
		condDivider = strVal;
	}
	else if (cfg.to_string() == "cond:divider@cond")
	{
		condDividerParam = strVal;
	}
	else if (cfg.to_string() == "cond:goto")
	{
		condGoto = strVal;
	}
	else if (cfg.to_string() == "cond:goto@cond")
	{
		condGotoParam = strVal;
	}
	else if (cfg.to_string() == "define:YYFILL@len")
	{
		yyFillLength = strVal;
		bUseYYFillParam = false;
	}
	else if (cfg.to_string() == "define:YYSETCONDITION@cond")
	{
		yySetConditionParam = strVal;
		bUseYYSetConditionParam = false;
	}
	else if (cfg.to_string() == "define:YYSETSTATE@state")
	{
		yySetStateParam = strVal;
		bUseYYSetStateParam = false;
	}
	else if (mapVariableKeys.find(cfg.to_string()) != mapVariableKeys.end())
	{
		if (!mapCodeName.insert(std::make_pair(cfg.to_string().substr(sizeof("variable:") - 1), strVal)).second)
		{
			fatalf("variable '%s' already being used and cannot be changed", cfg.to_string().c_str());
		}
	}
	else if (mapDefineKeys.find(cfg.to_string()) != mapDefineKeys.end())
	{
		if (!mapCodeName.insert(std::make_pair(cfg.to_string().substr(sizeof("define:") - 1), strVal)).second)
		{
			fatalf("define '%s' already being used and cannot be changed", cfg.to_string().c_str());
		}
	}
	else if (mapLabelKeys.find(cfg.to_string()) != mapLabelKeys.end())
	{
		if (!mapCodeName.insert(std::make_pair(cfg.to_string().substr(sizeof("label:") - 1), strVal)).second)
		{
			fatalf("label '%s' already being used and cannot be changed", cfg.to_string().c_str());
		}
	}
	else
	{
		std::string msg = "unrecognized configuration name '";
		msg += cfg.to_string();
		msg += "' or illegal string value";
		fatal(msg.c_str());
	}
}

ScannerState::ScannerState()
	: tok(NULL), ptr(NULL), cur(NULL), pos(NULL), ctx(NULL)
	, bot(NULL), lim(NULL), top(NULL), eof(NULL)
	, tchar(0), tline(0), cline(1), iscfg(0)
	, in_parse(false)
{
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

void Scanner::check_token_length(char *pos, uint32_t len) const
{
	if (pos < bot || pos + len > top)
	{
		fatal("Token exceeds limit");
	}
}

Str Scanner::raw_token(std::string enclosure) const
{
	return Str(std::string(enclosure + token().to_string() + enclosure).c_str());
}

void Scanner::reuse()
{
	next_label = 0;
	next_fill_index = 0;
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
