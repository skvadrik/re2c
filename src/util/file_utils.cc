#include "config.h"
#include <time.h>
#include "src/util/file_utils.h"

#if !defined(_MSC_VER) \
    && defined(HAVE_FCNTL_H) \
    && defined(HAVE_SYS_STAT_H) \
    && defined(HAVE_SYS_TYPES_H) \
    && defined(HAVE_UNISTD_H)

// POSIX
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define OPEN(fn)   open(fn, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR)
#define FDOPEN(fd) fdopen(fd, "w")
#define CLOSE(fd)  close(fd)
#define UNLINK(f)  unlink(f)

#elif defined(_MSC_VER) \
    && defined(HAVE_IO_H) \
    && defined(HAVE_FCNTL_H)

// MSVC
#include <fcntl.h>
#include <io.h>
#define OPEN(fn)   _open(fn, _O_CREAT | _O_EXCL | _O_RDWR, _S_IREAD | _S_IWRITE)
#define FDOPEN(fd) _fdopen(fd, "w")
#define CLOSE(fd)  _close(fd)
#define UNLINK(f)  _unlink(f)

#else

// stubs
#define OPEN(fn)   -1
#define FDOPEN(fd) NULL
#define CLOSE(fd)  -1
#define UNLINK(f)  -1

#endif

namespace re2c {

// In C++17, all this could be substituted with fopen(..., "x")
FILE* temp_file(std::string& fname) {
    // append "random enough" suffix to filename
    const time_t t = time(nullptr);
    char buffer[20]; // 20 = 5(".tmp.") + 4(%Y) + 2(%m) + 2(%d) + 2(%H) + 2(%M) + 2(%S) + 1(null)
    if (strftime(buffer, sizeof(buffer), ".tmp.%Y%m%d%H%M%S", localtime(&t)) == 0) {
        return nullptr;
    }
    fname += buffer;

    // open file for writing, unless it exists already
    FILE* f = nullptr;
    int fd = OPEN(fname.c_str());
    if (fd != -1) {
        f = FDOPEN(fd);
        if (!f) {
            CLOSE(fd);
        }
    }

    // we don't try too hard
    return f;
}

bool overwrite_file(const char* srcname, const char* dstname) {
    // remove destination file no matter what
    UNLINK(dstname);

    // try the easy way: rename
    if (rename(srcname, dstname) == 0) return true;

    // rename failed: try write
    FILE* src = nullptr, *dst = nullptr;
    static constexpr size_t BLK = 4096;
    char buf[BLK];
    bool ok = false;
    size_t n;

    src = fopen(srcname, "r");
    if (!src) goto end;

    dst = fopen(dstname, "w");
    if (!dst) goto end;

    for (;;) {
        n = fread(buf, 1, BLK, src);
        fwrite(buf, 1, n, dst);
        if (n < BLK) break;
    }
    ok = true;

end:
    if (src) fclose(src);
    if (dst) fclose(dst);
    UNLINK(ok ? srcname : dstname);

    return ok;
}

void get_dir(std::string& path) {
    // scan the path backwards until the first slash (if any) and clip
    size_t i = path.length();
    for (; i > 0; --i) {
        const char c = path[i - 1];
        if (c == '/' || c == '\\') break;
    }
    path.resize(i);
}

} // namespace re2c

#undef OPEN
#undef FDOPEN
#undef CLOSE
#undef UNLINK
