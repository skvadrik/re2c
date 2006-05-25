/* readfd.h
 * Scott Bronson
 * 30 Dec 2004
 *
 * Version VERSION
 */

#include "read.h"


/** @file readfd.h
 *
 * This file provides a readproc that reads from Unix file descriptors.
 */


/** Sets the scanner to scan the data contained in the given file descriptor.
 *
 * @param ss The scanner to manipulate.
 * @param fd The file descriptor that the scanner should pull data from.
 */

scanstate* readfd_attach(scanstate *ss, int fd);


/** Creates a scanner to scan the given file.
 *
 * This routine dynamically allocates the scanstate and its buffer.
 * It then opens the given Unix file and attaches it to the scanner.
 *
 * @param path The Unix path to the file to scan.
 * @param bufsiz The size in bytes of the scanner buffer to allocate.
 */

scanstate* readfd_open(const char *path, size_t bufsiz);

/** Disposes of the scanner created by readfd_open().
 *
 * This routine closes the file and deallocates the scanner and buffer.
 * It frees all resourcs allocated by readfd_open().
 *
 * @param ss The scanner to destroy.
 */

void readfd_close(scanstate *ss);

