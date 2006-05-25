/* readfp.c
 * Scott Bronson
 * 28 Dec 2004
 *
 * Version VERSION
 */

#include <stdio.h>
#include <assert.h>

#include "scan-dyn.h"
#include "readfp.h"


static ssize_t readfp_read(scanstate *ss)
{
    ssize_t n, avail;

    avail = read_shiftbuf(ss);
    n = fread((void*)ss->limit, 1, avail, ss->readref);
    ss->limit += n;

    if(n <= 0) {
        if(feof(ss->readref)) {
            return 0;
        }
        if(ferror(ss->readref)) {
            return -1;
        }
       
		// this implies some sort of internal consistency error
        assert(!"Not eof or error. I have no idea what happened!");
        return -3;
    }

    return n;
}


scanstate* readfp_attach(scanstate *ss, FILE *fp)
{
    if(!ss || !fp) {
        return 0;
    }

    ss->readref = fp;
    ss->read = readfp_read;
    return ss;
}


/** Creates a scanstate object that can read from the given file.
 * Returns NULL and prints to STDERR if an error ocurrs.
 * Ensure that you call readfp_close() when you're finished.
 * Uses the given buffer size, or BUFSIZ if bufsiz is 0.
 * Ensure that the buffer size will fit into a signed
 * int on the current machine architecture.
 *
 * This call is the approximate equivalent to:
 * - dynscan_create(bufsiz);
 * - readfp_attach(ss, fopen(path));
 */

scanstate* readfp_open(const char *path, size_t bufsiz)
{
    scanstate *ss;
    FILE *fp;

    // open the file
    fp = fopen(path, "r");
    if(!fp) {
        return NULL;
    }

    // create the dynamic scanstate
    ss = dynscan_create(bufsiz);
    if(!ss) {
        fclose(fp);
        return NULL;
    }

    return readfp_attach(ss, fp);
}


/** Releases the resources allocated by readfp_open()
 */

void readfp_close(scanstate *ss)
{
    fclose(ss->readref);
    dynscan_free(ss);
}


