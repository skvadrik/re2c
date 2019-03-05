#include <time.h>
#include "src/msg/msg.h"
#include "src/util/temp_file.h"


#if defined(_WIN32) && !defined(__MINGW32__)

// MSVC
#include <io.h>
#define OPEN   _open
#define FDOPEN _fdopen
#define FLAGS  _O_CREAT | _O_EXCL | _O_RDWR
#define MODE   _S_IREAD | _S_IWRITE

#else

// POSIX
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define OPEN   open
#define FDOPEN fdopen
#define FLAGS  O_CREAT | O_EXCL | O_RDWR
#define MODE   S_IRUSR | S_IWUSR

#endif

namespace re2c {

FILE *temp_file(std::string &fname)
{
    // append "random enough" suffix to filename
    const time_t t = time(NULL);
    char buffer[20];
    strftime(buffer, sizeof(buffer), ".tmp.%Y%m%d%H%M%S", localtime(&t));
    fname += buffer;

    // open file for writing, unless it exists already
    FILE *f = NULL;
    int fd = OPEN(fname.c_str(), FLAGS, MODE);
    if (fd != -1) {
        f = FDOPEN(fd, "w");
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
#undef FLAGS
