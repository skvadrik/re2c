#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <new>

#include "src/code/label.h"
#include "src/code/output.h"
#include "src/ast/scanner.h"
#include "src/util/counter.h"

// used by Scanner::fatal_at and Scanner::fatalf
#if defined(_MSC_VER) && !defined(vsnprintf)
#    define vsnprintf _vsnprintf
#endif

namespace re2c {

const uint32_t Scanner::BSIZE = 8192;

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
	, cline (1)
	, lexer_state (LEX_NORMAL)
{}

Scanner::Scanner (Input & i, OutputFile & o, Opt &p)
	: ScannerState ()
	, in (i)
	, out (o)
	, opts (p)
	, warn (o.warn)
{}

void Scanner::fill (uint32_t need)
{
	if(!eof)
	{
		/* Do not get rid of anything when rFlag is active. Otherwise
		 * get rid of everything that was already handedout. */
		if (!opts->rFlag)
		{
			const ptrdiff_t diff = tok - bot;
			if (diff > 0)
			{
				const size_t move = static_cast<size_t> (top - tok);
				memmove (bot, tok, move);
				tok -= diff;
				ptr -= diff;
				cur -= diff;
				pos -= diff;
				lim -= diff;
				ctx -= diff;
			}
		}
		/* In crease buffer size. */
		if (BSIZE > need)
		{
			need = BSIZE;
		}
		if (static_cast<uint32_t> (top - lim) < need)
		{
			const size_t copy = static_cast<size_t> (lim - bot);
			char * buf = new char[copy + need];
			if (!buf)
			{
				fatal("Out of memory");
			}
			memcpy (buf, bot, copy);
			tok = &buf[tok - bot];
			ptr = &buf[ptr - bot];
			cur = &buf[cur - bot];
			pos = &buf[pos - bot];
			lim = &buf[lim - bot];
			top = &lim[need];
			ctx = &buf[ctx - bot];
			delete [] bot;
			bot = buf;
		}
		/* Append to buffer. */
		const size_t have = fread (lim, 1, need, in.file);
		if (have != need)
		{
			eof = &lim[have];
			*eof++ = '\0';
		}
		lim += have;
	}
}

void Scanner::fatal_at(uint32_t line, ptrdiff_t ofs, const char *msg) const
{
	std::cerr << "re2c: error: "
		<< "line " << line << ", column " << (tchar + ofs + 1) << ": "
		<< msg << std::endl;
	exit(1);
}

void Scanner::fatal(ptrdiff_t ofs, const char *msg) const
{
	fatal_at(cline, ofs, msg);
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
	delete [] bot;
}

} // namespace re2c
