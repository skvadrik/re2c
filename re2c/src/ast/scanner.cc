#include <stdio.h>
#include <string.h>

#include "src/ast/scanner.h"
#include "src/conf/msg.h"

// used by Scanner::fatal_at and Scanner::fatalf
#if defined(_MSC_VER) && !defined(vsnprintf)
#    define vsnprintf _vsnprintf
#endif

namespace re2c {

class Warn;

const uint32_t Scanner::BSIZE = 8192;

ScannerState::ScannerState ()
    : tok (NULL)
    , ptr (NULL)
    , cur (NULL)
    , mar (NULL)
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

Scanner::Scanner(Input &i, Warn &w)
    : ScannerState(), in(i), warn(w) {}

void Scanner::fill (uint32_t need)
{
    if(!eof)
    {
        /* Get rid of everything that was already parsed. */
        const ptrdiff_t diff = tok - bot;
        if (diff > 0)
        {
            const size_t move = static_cast<size_t> (top - tok);
            memmove (bot, tok, move);
            tok -= diff;
            mar -= diff;
            ptr -= diff;
            cur -= diff;
            pos -= diff;
            lim -= diff;
            ctx -= diff;
        }
        /* Increase buffer size. */
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
            if (copy > 0) {
                memcpy (buf, bot, copy);
            }
            tok = &buf[tok - bot];
            mar = &buf[mar - bot];
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

Scanner::~Scanner()
{
    delete [] bot;
}

} // namespace re2c
