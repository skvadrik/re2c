#include <assert.h>
#include <string.h>

#include "src/ast/scanner.h"
#include "src/conf/msg.h"


namespace re2c {

class Warn;

Scanner::Scanner(Warn &w)
    : ScannerState()
    , files()
    , warn(w)
{}

Scanner::~Scanner()
{
    for (; !files.empty(); ) {
        delete files.top();
        files.pop();
    }
}

bool Scanner::push_file(const char *filename)
{
    // push buffer tail back to file - we'll return to it later
    if (!files.empty()) {
        int err = fseek(files.top()->file, lim - cur, SEEK_CUR);
        if (err != 0) return false;
    }

    // open new file and place place at the top of stack
    Input *f = new Input;
    files.push(f);
    if (!f->open(filename)) return false;

    // refill buffer
    return fill(BSIZE);
}

bool Scanner::read(size_t want)
{
    const char *stop = lim + want;
    assert(!files.empty());
    for (;;) {
        Input *f = files.top();
        lim += fread(lim, 1, want, f->file);

        // buffer filled
        if (lim == stop) return true;

        // the first file must remain at the bottom of the stack
        if (files.size() == 1) break;
        delete f;
        files.pop();
    }
    return false;
}

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

    if (!read(free)) {
        eof = lim;
        memset(lim, 0, YYMAXFILL);
        lim += YYMAXFILL;
    }

    return true;
}

} // namespace re2c
