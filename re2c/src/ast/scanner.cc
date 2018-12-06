#include <assert.h>
#include <string.h>

#include "src/ast/scanner.h"
#include "src/conf/msg.h"


namespace re2c {

class Warn;

Scanner::Scanner(Input &i, Warn &w): ScannerState(), in(i), warn(w) {}

bool Scanner::fill(size_t need)
{
    if (eof) return false;

    assert(bot <= tok && tok <= lim);
    size_t free = static_cast<size_t>(tok - bot);
    size_t copy = static_cast<size_t>(lim - tok);

    if (free >= need) {
        memmove(bot, tok, copy);
        shift_ptrs(-static_cast<ptrdiff_t>(free));
    }
    else {
        BSIZE += std::max(BSIZE, need);
        char * buf = new char[BSIZE + YYMAXFILL];
        if (!buf) fatal("out of memory");

        memmove(buf, tok, copy);
        shift_ptrs(buf - bot);
        delete [] bot;
        bot = buf;

        free = BSIZE - copy;
    }

    lim += fread(lim, 1, free, in.file);
    if (lim < bot + BSIZE) {
        eof = lim;
        memset(lim, 0, YYMAXFILL);
        lim += YYMAXFILL;
    }

    return true;
}

} // namespace re2c
