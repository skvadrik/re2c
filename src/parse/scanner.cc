#include <stdio.h>
#include <algorithm>
#include <stdint.h>
#include <limits>
#include <string.h>

#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/parse/scanner.h"
#include "src/util/check.h"
#include "src/util/file_utils.h"
#include "src/util/string_utils.h"

namespace re2c {

const char* const Scanner::ENDPOS = (const char*) std::numeric_limits<uint64_t>::max();

Scanner::~Scanner() {
    for (Input* in: files) {
        delete in;
    }
}

size_t Scanner::get_input_index() const {
    // Find index of the current input file: the one corresponding to the buffer fragment that
    // contains the cursor.
    size_t i = files.size();
    DCHECK(i > 0);
    for (;;) {
        --i;
        Input* in = files[i];
        if (i == 0 || (cur >= in->so && cur <= in->eo)) break;
    }
    return i;
}

Ret Scanner::open(const std::string& filename, const std::string* parent) {
    Input* in = new Input(msg.filenames.size());
    files.push_back(in);
    CHECK_RET(in->open(filename, parent, globopts->incpaths));
    filedeps.insert(in->escaped_name);
    msg.filenames.push_back(in->escaped_name);
    return Ret::OK;
}

Ret Scanner::include(const std::string& filename, char* at) {
    // This function is called twice for each include file: first time when opening the file, and
    // second time when it has been fully read. The second time is needed to generate a line
    // directive marking the end of the include file and the continuation of the parent file. In
    // order to make the lexer stop at the boundary between files and do the second call, we
    // "unread" the directive on the first call (push it back to the parent file before filling the
    // buffer with the contents of include file), and let the lexer scan the directive twice.
    //
    // To avoid infinite recursion we need to differentiate the two calls. We do this by inspecting
    // the files on stack. First, we pop all finished files: there may be sibling includes before
    // this one in the parent file. They must be finished by now, meaning that the token pointer has
    // moved past their end pointer (even if another directive immediately precedes this one,
    // "unreading" the directive has the effect of inserting an artificial boundary between include
    // files). However if the current include file is already on stack, then `at` must point exactly
    // at the end of it (not past the end), so we will not pop it.
    //
    // After popping finished files we have two alternatives:
    //  - Parent file is on top (then it is the first call).
    //  - There is exactly one file on top of the parent file (then it is the second call, and the
    //    file on top is the current include file).

    CHECK(tok <= at); // ensure that we won't pop the include file itself
    pop_finished_files();

    const size_t fidx = get_input_index(); // index of the parent file with the directive
    const size_t last = files.size() - 1; // index of the topmost file
    if (fidx == last) {
        // This is the first call, go on.
    } else {
        // This is the second call, quit.
        CHECK(fidx + 1 == last
               && files[last]->name == filename
               && files[last]->eo == at);
        return Ret::OK;
    }

    // get name of the current file (before unreading)
    const std::string& parent = files[fidx]->escaped_name;

    // Unread buffer tail: we'll return to it later. In the buffer nested files go before outer
    // files. In the file stack, however, outer files go before nested files (nested are at the
    // top). We want to break from the unreading cycle early, therefore we go in reverse order of
    // file offsets in buffer and break as soon as the end offset is less than cursor (current
    // position). `at` points at the start of include directive.
    for (Input* in : files) {
        if (in->so >= at) {
            // unread whole fragment
            fseek(in->file, in->so - in->eo, SEEK_CUR);
            in->so = in->eo = ENDPOS;
        } else if (in->eo >= at) {
            // fragment on the boundary, unread partially
            fseek(in->file, at - in->eo, SEEK_CUR);
            in->eo = cur - 1;
        } else {
            // the rest has been consumed already
            break;
        }
    }

    // open new file and place place at the top of stack
    CHECK_RET(open(filename, &parent));

    // refill buffer (discard everything up to cursor, clear EOF)
    lim = cur = mar = ctx = tok = ptr = pos = bot + BSIZE;
    eof = nullptr;
    return fill(BSIZE) ? Ret::OK : Ret::FAIL;
}

bool Scanner::read(size_t want) {
    CHECK(!files.empty());
    for (size_t i = files.size(); i --> 0; ) {
        Input* in = files[i];
        const size_t have = fread(lim, 1, want, in->file);
        in->so = lim;
        lim += have;
        in->eo = lim;
        want -= have;

        // buffer filled
        if (want == 0) return true;
    }
    return false;
}

void Scanner::shift_ptrs_and_fpos(ptrdiff_t offs) {
    // shift buffer pointers
    shift_ptrs(offs);

    // shift file pointers
    for (size_t i = files.size(); i --> 0; ) {
        Input* in = files[i];
        if (in->so == ENDPOS && in->eo == ENDPOS) break;
        CHECK(in->so != ENDPOS && in->eo != ENDPOS);
        in->so += offs;
        in->eo += offs;
    }
}

void Scanner::pop_finished_files() {
    // Pop all files that have been fully processed (file upper bound in buffer points before the
    // first character of current lexeme), except for the first (main) file which must always remain
    // at the bottom of the stack.
    size_t i = files.size();
    CHECK(i > 0);
    for (;;) {
        --i;
        Input* in = files[i];
        // Keep the file if the end equals token. It is crucial for the include files.
        if (i == 0 || in->eo >= tok) break;
        files.pop_back();
        delete in;
    }
}

bool Scanner::fill(size_t need) {
    if (eof) return false;

    pop_finished_files();

    CHECK(bot <= tok && tok <= lim);
    size_t free = static_cast<size_t>(tok - bot);
    size_t copy = static_cast<size_t>(lim - tok);

    if (free >= need) {
        memmove(bot, tok, copy);
        shift_ptrs_and_fpos(-static_cast<ptrdiff_t>(free));
    } else {
        BSIZE += std::max(BSIZE, need);
        char* buf = new char[BSIZE + YYMAXFILL];
        if (buf == nullptr) {
            error("out of memory");
            return false;
        }

        memmove(buf, tok, copy);
        shift_ptrs_and_fpos(buf - tok);
        delete [] bot;
        bot = buf;

        free = BSIZE - copy;
    }

    CHECK(lim + free <= bot + BSIZE);
    if (!read(free)) {
        eof = lim;
        memset(lim, 0, YYMAXFILL);
        lim += YYMAXFILL;
    }

    return true;
}

Ret Scanner::gen_dep_file() const {
    const std::string& fname = globopts->dep_file;
    if (fname.empty()) return Ret::OK;

    FILE* file = fopen(fname.c_str(), "w");
    if (file == nullptr) RET_FAIL(error("cannot open dep file %s", fname.c_str()));

    fprintf(file, "%s:", escape_backslashes(globopts->output_file).c_str());
    for (const std::string& fdep : filedeps) {
        fprintf(file, " %s", fdep.c_str());
    }
    fprintf(file, "\n");

    fclose(file);
    return Ret::OK;
}

uint32_t Scanner::decode(const char* str) const {
    return globopts->input_encoding == Enc::Type::ASCII
           ? static_cast<uint8_t>(str[0]) : utf8::decode_unsafe(str);
}

} // namespace re2c
