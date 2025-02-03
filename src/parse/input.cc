#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <limits>

#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/parse/input.h"
#include "src/util/file_utils.h"
#include "src/util/string_utils.h"

namespace re2c {

InputFile::InputFile(size_t fidx)
    : file(nullptr),
      name(),
      path(),
      escaped_name(),
      so(Input::ENDPOS),
      eo(Input::ENDPOS),
      line(1),
      fidx(static_cast<uint32_t>(fidx)) {}

Ret InputFile::open(const std::string& filename,
                const std::string* parent,
                const std::vector<std::string>& include_paths) {
    name = filename;

    if (!parent) {
        path = name;
        file = name == "<stdin>" ? stdin : fopen(name.c_str(), "rb");
    } else {
        // first, search relative to the directory of including file
        path = *parent;
        get_dir(path);
        path += name;
        file = fopen(path.c_str(), "rb");

        // otherwise search in all include paths
        for (const std::string& incpath : include_paths) {
            if (file != nullptr) break;
            path = incpath + name;
            file = fopen(path.c_str(), "rb");
        }

        // if user-defined include paths failed, try stdlib path
        if (!file) {
            path = RE2C_STDLIB_DIR + name;
            file = fopen(path.c_str(), "rb");
        }
    }

    if (!file) RET_FAIL(error("cannot open file: %s", name.c_str()));

    // name displayed in #line directives is the resolved name
    escaped_name = escape_backslashes(path);

    return Ret::OK;
}

InputFile::~InputFile() {
    if (file != nullptr && file != stdin) {
        fclose(file);
    }
}

const uint8_t* const Input::ENDPOS = reinterpret_cast<const uint8_t*>(UINT64_MAX);

Input::~Input() {
    for (InputFile* in: files) {
        delete in;
    }
}

void Input::reset_lexer() {
    reset_ptrs();

    for (InputFile* in: files) {
        delete in;
    }
    files.clear();
    msg.filenames.clear();

    location = ATSTART;
}

size_t Input::get_input_index() const {
    // Find index of the current input file: the one corresponding to the buffer fragment that
    // contains the cursor.
    size_t i = files.size();
    DCHECK(i > 0);
    for (;;) {
        --i;
        InputFile* in = files[i];
        if (i == 0 || (cur >= in->so && cur <= in->eo)) break;
    }
    return i;
}

Ret Input::open(const std::string& filename, const std::string* parent) {
    InputFile* in = new InputFile(msg.filenames.size());
    files.push_back(in);
    CHECK_RET(in->open(filename, parent, globopts->include_paths));
    filedeps.insert(in->escaped_name);
    msg.filenames.push_back(in->escaped_name);
    return Ret::OK;
}

Ret Input::include(const std::string& filename, uint8_t* at) {
    // This function is called twice for each include file: first time when opening the file, and
    // second time when it has been fully read. The second time is needed to generate a line
    // directive marking the end of the include file and the continuation of the parent file. In
    // order to make the lexer stop at the boundary between files and do the second call, we
    // "unread" the `include` block on the first call (push it back to the parent file before
    // filling the buffer with the contents of include file), and let the lexer scan it twice.
    //
    // To avoid infinite recursion we need to differentiate the two calls. We do this by inspecting
    // the files on stack. First, we pop all finished files: there may be sibling includes before
    // this one in the parent file. They must be finished by now, meaning that the token pointer has
    // moved past their end pointer (even if another `include` block immediately precedes this one,
    // "unreading" the block has the effect of inserting an artificial boundary between include
    // files). However if the current include file is already on stack, then `at` must point exactly
    // at the end of it (not past the end), so we will not pop it.
    //
    // After popping finished files we have two alternatives:
    //  - Parent file is on top (then it is the first call).
    //  - There is exactly one file on top of the parent file (then it is the second call, and the
    //    file on top is the current include file).

    CHECK(tok <= at); // ensure that we won't pop the include file itself
    pop_finished_files();

    const size_t fidx = get_input_index(); // index of the parent file with the `include` block
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
    // position). `at` points at the start of `include` block.
    for (InputFile* in : files) {
        if (in->so >= at) {
            // unread whole fragment
            fseek(in->file, static_cast<long>(in->so - in->eo), SEEK_CUR);
            in->so = in->eo = ENDPOS;
        } else if (in->eo >= at) {
            // fragment on the boundary, unread partially
            fseek(in->file, static_cast<long>(at - in->eo), SEEK_CUR);
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

bool Input::read(size_t want) {
    CHECK(!files.empty());
    for (size_t i = files.size(); i --> 0; ) {
        InputFile* in = files[i];
        const size_t have = fread(lim, 1, want, in->file);
        if (have > 0) {
            in->so = lim;
            lim += have;
            in->eo = lim;
            want -= have;
        } else if (in->so == ENDPOS) {
            // Empty file: first time we read from it and have nothing.
            DCHECK(in->eo == ENDPOS);
            in->so = in->eo = lim;
        } else {
            // We have reached the end of file. Don't adjust start and end pointers, as
            // YYLIMIT may point outside of this file. This may happen if the previous `read()`
            // invocation drained this file, then read some data from the parent file, and
            // then YYFILL got triggered while YYCURSOR was still in this file, so this file
            // could not be popped off the stack yet.
        }

        // buffer filled
        if (want == 0) return true;
    }
    return false;
}

void Input::shift_ptrs_and_fpos(ptrdiff_t offs) {
    // shift buffer pointers
    shift_ptrs(offs);

    // shift file pointers
    for (size_t i = files.size(); i --> 0; ) {
        InputFile* in = files[i];
        if (in->so == ENDPOS && in->eo == ENDPOS) break;
        CHECK(in->so != ENDPOS && in->eo != ENDPOS);
        in->so += offs;
        in->eo += offs;
    }
}

void Input::pop_finished_files() {
    // Pop all files that have been fully processed (file upper bound in buffer points before the
    // first character of current lexeme), except for the first (main) file which must always remain
    // at the bottom of the stack.
    size_t i = files.size();
    CHECK(i > 0);
    for (;;) {
        --i;
        InputFile* in = files[i];
        // Keep the file if the end equals token. It is crucial for the include files.
        if (i == 0 || in->eo >= tok) break;
        files.pop_back();
        delete in;
    }
}

bool Input::fill(size_t need) {
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
        uint8_t* buf = new uint8_t[BSIZE + maxfill()];

        memmove(buf, tok, copy);
        shift_ptrs_and_fpos(buf - tok);
        delete [] bot;
        bot = buf;

        free = BSIZE - copy;
    }

    CHECK(lim + free <= bot + BSIZE);
    if (!read(free)) {
        eof = lim;
        memset(lim, 0, maxfill());
        lim += maxfill();
    }

    return true;
}

Ret Input::gen_dep_file(const std::string& header) const {
    const std::string& fname = globopts->dep_file;
    if (fname.empty()) return Ret::OK;

    FILE* file = fopen(fname.c_str(), "w");
    if (file == nullptr) RET_FAIL(error("cannot open dep file %s", fname.c_str()));

    fprintf(file, "%s", escape_backslashes(globopts->output_file).c_str());
    if (!header.empty()) {
        fprintf(file, " %s", header.c_str());
    }
    fprintf(file, ":");
    for (const std::string& fdep : filedeps) {
        fprintf(file, " %s", fdep.c_str());
    }
    fprintf(file, "\n");

    fclose(file);
    return Ret::OK;
}

uint32_t Input::decode(const uint8_t* str) const {
    return globopts->input_encoding == Enc::Type::ASCII ? str[0] : utf8::decode_unsafe(str);
}

void Input::error_at(const loc_t& loc, const char* fmt, ...) const {
    va_list args;
    va_start(args, fmt);
    msg.verror(loc, fmt, args);
    va_end(args);
}

void Input::error_at_cur(const char* fmt, ...) const {
    va_list args;
    va_start(args, fmt);
    msg.verror(cur_loc(), fmt, args);
    va_end(args);
}

void Input::error_at_tok(const char* fmt, ...) const {
    va_list args;
    va_start(args, fmt);
    msg.verror(tok_loc(), fmt, args);
    va_end(args);
}

} // namespace re2c
