/* readfd.c
 * Scott Bronson
 * 28 Dec 2004
 *
 * Version VERSION
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

#include "readfd.h"
#include "scan-dyn.h"

/** @file readfd.c
 *
 * This file provides a readproc that reads from Unix file descriptors.
 */


/**
 * The internal function that performs the read.  You never call
 * it directly.  Instead, it is called automatically by the scanner
 * whenever it needs more data.
 */

static ssize_t readfd_read(scanstate *ss)
{
    int n, avail;

    avail = read_shiftbuf(ss);

    // ensure we get a full read
    do {
        n = read((int)ss->readref, (void*)ss->limit, avail);
    } while(n < 0 && errno == EINTR);
    ss->limit += n;

    return n;
}


/** Attaches the existing fd to the existing scanstate object.
 * Note that this routine checks the fd and if it's less than 0
 * (indicating an error) it returns null.
 *
 * If you pass this routine valid arguments, there's no way for it to fail.
 *
 * Note that the re2c library does not work very well with file descriptors
 * that may return short reads such as pipes and sockets.  You may want to
 * try to use the new re2c push model to fix this.
 */

scanstate* readfd_attach(scanstate *ss, int fd)
{
    if(!ss || fd < 0) {
        return 0;
    }

    ss->readref = (void*)fd;
    ss->read = readfd_read;
    return ss;
}


/* Opens the file and creates a new scanner to scan it.
 * This is just a convenience routine.  You can create a scanner
 * yourself and attach to it using readfd_attach().
 *
 * If you do use this routine, you should call readfd_close() to close
 * the file and deallocate the scanner.
 *
 * Bufsiz tells how big in bytes the scan buffer will be.  No single
 * token may be larger than bufsiz.
 *
 * This is the approximate equivalent to:
 * - dynscan_create(bufsiz);
 * - readfd_attach(ss, open(path));
 */

scanstate* readfd_open(const char *path, size_t bufsiz)
{
    scanstate *ss;
    int fd;

    fd = open(path, O_RDONLY);
    if(fd < 0) {
        return NULL;
    }

    ss = dynscan_create(bufsiz);
    if(!ss) {
        close(fd);
        return NULL;
    }

    return readfd_attach(ss, fd);
}


/**
 * Closes the file and deallocates the memory allocated by readfd_open().
 */

void readfd_close(scanstate *ss)
{
    close((int)ss->readref);
    dynscan_free(ss);
}

