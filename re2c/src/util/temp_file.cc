#include "config.h"
#include <time.h>
#include "src/msg/msg.h"
#include "src/util/temp_file.h"


#if !defined(_MSVC) \
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

#elif defined(_MSVC) \
    && defined(HAVE_IO_H)

// MSVC
#include <io.h>
#define OPEN(fn)   _open(fn, _O_CREAT | _O_EXCL | _O_RDWR, _S_IREAD | _S_IWRITE)
#define FDOPEN(fd) _fdopen(fd, "w")
#define CLOSE(fd)  _close(fd)

#else

// stubs
#define OPEN(fn)   -1
#define FDOPEN(fd) NULL
#define CLOSE      -1

#endif

namespace re2c {

// In C++11, all this could be substituted with fopen(..., "x")
FILE *temp_file(std::string &fname)
{
    // append "random enough" suffix to filename
    const time_t t = time(NULL);
    char buffer[20];
    strftime(buffer, sizeof(buffer), ".tmp.%Y%m%d%H%M%S", localtime(&t));
    fname += buffer;

    // open file for writing, unless it exists already
    FILE *f = NULL;
    int fd = OPEN(fname.c_str());
    if (fd != -1) {
        f = FDOPEN(fd);
        if (!f) {
            CLOSE(fd);
        }
    }

    // we don't try too hard
    if (!f) {
        error("cannot open temporary file %s", fname.c_str());
    }
    return f;
}

} // namespace re2c

#undef OPEN
#undef FDOPEN
#undef CLOSE
