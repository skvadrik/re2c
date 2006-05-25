/* scan.h
 * Scott Bronson
 * 27 Dec 2004
 *
 * Version VERSION
 *
 * This part of support code to make writing re2c scanners much easier.
 *
 * TODO: add dispose procs.  Normally these will just be null but
 * if they're set, they will ensure that all resources are collected.
 *
 * TODO: probably want to split the re2c-specific code from the general
 * code.  This file is overall very useful, but it's got a few limitations
 * imposed by re2c that should probably be placed in its own layer.
 * That way, future versions of re2c won't have to suffer the same
 * limitations.
 */

// to pull in the definition for size_t
#include <sys/types.h>


/** @file scan.h
 *
 * This file contains the definition of the scanstate, the most
 * important data structure for a scanner.  It also contains some
 * support macros.
 *
 * TERMINOLOGY
 *
 * allocate: scanstates can be dynamically (dynamicscan_create()) or
 * statically (scanstate_init()) allocated.  The buffers they use to
 * hold data may also be either dynamic or static.  Of course, any
 * time you allocate something dynamically, you must call the
 * corresponding free routine when you're done with it.
 *
 * attach: when the scanner is first initialized (scanstate_init())
 * or allocated (dynamicscan_create()), it is not associated with
 * a reader (to supply data) or a scanner (to scan the data).
 * You first need to attach both a ::scanproc and a ::readproc.
 *
 * initialize: prepare an already-allocated scanner for use.
 * After initializing it, you must ATTACH the scanner to a
 * READER.
 *
 * reader: See readproc
 *
 * ::readproc:: reads data into the scanstate for the scanner.
 * Examples are readmem.c (read from a contiguous block in
 * memory), readfp.c (read from a FILE*), readfd.c (read
 * from a Unix file descriptor), etc.
 *
 * scanner The function (or functions, see \ref startstates)
 * that actually performs the scanning.
 * The scanner need not actually be written with the assistance
 * of re2c
 * It accepts a scanstate data structure and returns the next
 * token in the stream.
 *
 * scanproc:
 *
 * ::scanstate: the data structure that retains complete state for the
 * scanner.  Scanners are thread safe: they never, ever use global
 * state.
 */


#ifndef R2SCAN_H
#define R2SCAN_H


// for re2c...
#define YYCTYPE     char
#define YYCURSOR    (ss->cursor)
#define YYLIMIT     (ss->limit)
#define YYMARKER    (ss->marker)

/** Fills the scan buffer with more data.
 *
 * This routine needs to force a return if 0 bytes were read because
 * otherwise the re2c scanner will end up scanning garbage way off
 * the end of the buffer.  There's no (good) way to tell the scanner
 * "the file is at eof so just finish the token that you're on" (right?).
 * It will always lose the token at the end of the file unless the file
 * ends in a token delimiter (usually a newline).
 *
 * We ignore n because there can be less than n bytes left in the file,
 * yet one or more tokens will still match.  Therefore, we should always
 * read as much data as we can, and we should return success even if we
 * have less than n bytes in the buffer.  N is totally useless.
 *
 * The last line is the limitation.  If it weren't there, YYFILL would
 * return with an empty buffer so re2c would know it's at EOF and
 * shut down gracefully.  But re2c can't handle that.
 *
 * If you're using the re2c lib but writing your own re2c scanners,
 * call ss->read directly.
 */

#define YYFILL(n)   do { \
		if(ss->last_read > 0) ss->last_read = (*ss->read)(ss); \
		if(ss->last_read < 0) return ss->last_read; \
		if((ss)->cursor >= (ss)->limit) return 0; \
	} while(0);


// forward declaration
struct scanstate;


/** Readprocs are provide the scanners with data.
 *
 * Each scanner has a single readproc that feeds it with data.
 * The re2c library includes some standard readprocs 
 * (see \ref readproc_builtins) and makes it easy to write your own
 * if the builtins don't do what you want (see \ref writing_readprocs).
 *
 * @returns: A positive return value specifies the number of bytes
 * that were returned.  Zero means EOF.  Negative means an error
 * occurred (the exact meaning of the error code depends on the
 * readproc).
 *
 * re2c doesn't work well with partial reads so be sure your readproc
 * fills the entire buffer if possible (see \ref readproc_shortreads).
 *
 * See \ref error_handling for more on how errors are propagated
 * through the re2c library.
 */

typedef ssize_t (*readproc)(struct scanstate *ss);


/** Scans the data and returns the next token.
 *
 * A scanner is simply one or more functions that accept a scanstate
 * object and return the next token in that stream.
 * The scanproc will typically be generated with the
 * assistance of re2c, but the re2c library can be useful
 * even when re2c isn't used (see \ref cmpscan).
 *
 * Once you have created the scanstate data structure,
 * pass it to the scanner.  If the scanner returns 0,
 * you hit EOF.  If the scanner returns a negative number,
 * then some sort of error was encountered.  Or, if you're
 * doing nonblocking I/O, then it just might mean that this
 * there's not enough data available to determine the next
 * token.
 */

typedef int (*scanproc)(struct scanstate *ss);



/** Contains all state for a single scan session.
 *
 * This structure is used by a scanner to preserve its state.
 *
 * All charptrs are declared const to help ensure that you don't
 * accidentally end up modifying the buffer as it's being scanned.
 * This means that any time you want to read data into the buffer,
 * you need to cast the pointers to be nonconst.
 */

struct scanstate {
    const char *cursor; ///< The current character being looked at by the scanner.  This is the same as re2c's YYCURSOR.
    const char *limit;  ///< The last (uppermost) valid character in the current buffer.  This is the same as re2c's YYLIMIT.
    const char *marker; ///< Used internally by re2c engine to handle backtracking.  This is the same as re2c's YYMARKER.

    const char *token;  ///< The start of the current token.
    int line;           ///< The scanner may or may not maintain the current line number in this field.  Typically a scanner's attach routine sets this field to 1 if it properly keeps track of line numbers and leaves it set to 0 if it doesn't.  See \ref linenos for more.
    ssize_t last_read;         ///< The return value from the last time the ::readproc was called.  If last_read is 0 (eof) or negative (error), then the readproc should not be called.

    const char *bufptr; ///< The buffer currently in use.
    size_t bufsiz;   ///< The maximum number of bytes that the buffer can hold.

    void *readref;      ///< Data specific to the ::readproc (i.e. for readfp_attach(), readref contains the FILE*).
    readproc read;      ///< Routine that refills the scan buffer.  See ::readproc.

    void *scanref;      ///< Data specific to the scanner.  Only the scanner may use this field.
    scanproc state;     ///< The entrypoint for the scanning routine.  More complex scanners are made up of multiple individual scan routines -- \ref startstates -- and they store their state here.

    void *userref;      ///< Never touched by any re2c routines.   Well, except scanstate_init(), which clears both this field and userproc to 0.  It could be used to associate a parser with this scanstate.
    void *userproc;     ///< Never touched by any re2c routines.  See scanstate::userref.
};
typedef struct scanstate scanstate;


/** Initializes a given scanstate structure.
 *
 * Call this to prepare a scanner for use.  Some calls, such as readmem_init()
 * and dynscan_create
 *
 * @param ss The scanstate to initialize.  There is no need to clear this
 *   memory first -- scanstate_init initializes every field.
 * @param bufptr The scan buffer.  Pass NULL if you don't care to specify
 *   a scan buffer, such as when attaching a readproc that includes its
 *   own buffer (readmem_attach()).
 * @param bufsiz Size, in bytes, of bufptr.  Pass 0 when bufptr is NULL.
 */

void scanstate_init(scanstate *ss, const char *bufptr, size_t bufsiz);
void scanstate_reset(scanstate *ss);


/** Returns true when there's no more data to be scanned.
 *
 * It is much better to just call scan_next_token() until it returns
 * 0 (EOF) or a negative number (a readproc error).
 * While there are a few cases where it's useful to reliably
 * check for EOF without having to scan a token, this is often a
 * sign of bad design.  Therefore, try to use scan_is_finished() sparingly.
 *
 * There's a slim chance that this routine will call the readproc.
 * If the buffer
 * contains no more data but the file is not at eof, we must execute
 * a read to discover if there's any more data available.
 * If the read returns EOF or an error, scan_is_finished will return 1.
 *
 * How this macro works:
 *
 * - If there's still more data in the buffer, then we're not finished.
 * - If there's no data in the buffer and the previous read returned
 *   EOF or an error, then we're finished.
 * - If there's no data in the buffer but we're not at eof, then we need
 *   to execute a read to see if there's more data available.
 * - If the previous read returned EOF or error, then we're finished.
 *   Otherwise, there's now more data in the buffer so we're not done.
 */

#define scan_is_finished(ss) \
    (((ss)->cursor < (ss)->limit) ? 0 : \
		 ((ss)->last_read <= 0 || ((*(ss)->read)(ss) <= 0)) \
    )


/** Fetches the next token in the stream from the scanner.
 *
 * This routine causes the scanner to actually scan.
 * Here is an example of how to call it:
 *
 * <pre>
 * do {
 *     int token = scan_next_token(ss);
 *     if(token < 0) {
 *         // scanner's readproc returned an error
 *         break;
 *     }
 *     handle_token(token);
 * } while(token);
 * </pre>
 *
 * handle_token() must properly handle eof (token == 0).
 * You generally want to pass the EOF to the parser consuming
 * the tokenized data.  This allows it to complain if it's
 * in a bad state, such as when parsing an unterminated string
 * constant, etc.
 *
 * @param ss The scanstate with a readproc and a scanner attached.
 *
 * @returns The next token from the input stream (tokens are always
 * greater than 0).  Returns 0 if the input stream is at EOF and
 * there are no more tokens.  Returns a negative value if the
 * ::readproc returned an error.
 */

#define scan_next_token(ss) ((*((ss)->state))(ss))


/** Returns the text of the most recently scanned token.
 *
 * This returns all the text of the most recently matched token.
 * Note that this data is only valid until the next time 
 * you call scan_next_token.
 *
 * EXAMPLE:
 *
 * <pre>
 *  printf("Token is: %.*s\n", token_length(ss), token_start(ss));
 * </pre>
 *
 * See also scan_token_end() and scan_token_length().
 * You can also use scan_token_dup() to access the current token.
 */

#define scan_token_start(ss) ((ss)->token)

/** Returns a pointer to the end of the most recently scanned token.
 *
 * Returns a pointer to the character following the last character of the
 * most recently scanned token.
 *
 * token_end(ss) - token_start(ss) == token_length(ss)
 *
 * See scan_token_start().
 */

#define scan_token_end(ss) ((ss)->cursor)

/** Returns the length in bytes of the most recently scanned token.
 *
 * See the example in scan_token_start().
 */

#define scan_token_length(ss) ((ss)->cursor - (ss)->token)

/** Copies the text of the current token into a malloc'd memory buffer.
 *
 * Because it copies the token, the data in the buffer will be valid
 * until you call free(3) to release it.
 *
 * This macro just calls strdup(3) internally.  Make sure to
 * include <string.h> if you use this macro in your own code.
 *
 * Because it calls malloc, this routine is quite slow.
 * See scan_token_start() for a speedy way to access the
 * text of the current token.
 */

#define scan_token_dup(ss) strndup(token_start(ss), token_length(ss))


/** Pushes the current token back onto the stream
 *
 * Calling scan_pushback returns the scanner to the state it was in
 * immediately prior to returning the current token.  If you decide that
 * you don't want to handle this particular token right now,
 * you can push it back
 * onto the scanner.  It will be returned the next time scan_token()
 * is called.
 *
 * Note that you can only push back a single token.
 * Also, some scanners may become confused by pushing a token back.
 * Generally, if the scanner maintains any sort of state on its own,
 * you cannot use scan_pushback on it.
 *
 * Finally, this doesn't back the line number up.  Because most tokens
 * don't span multiple lines, this is generally not a problem.  However,
 * if you're pushing a token back and want to ensure the correct line
 * number is maintained, you'll have to do something like this:
 *
 * <pre>
 *     // First ensure that the scanner you're using doesn't
 *     // have internal state that will be screwed up if you
 *     // re-scan the current token!
 *
 *     oldline = ss->line;
 *     tok = scan_next_token(ss);
 *     if(tok == push_me_back) {
 *         scan_pushback(ss);
 *         ss->line = oldline;
 *     }
 * </pre>
 *
 * Yes, it takes some effort to call this function safely.
 * But it is all worth it when you really need it.
 */

#define scan_pushback(ss) ((ss)->cursor = (ss)->token)


/**
 * Sets the current line number in the scanner to the given value.
 *
 * It's generally better to use this macro to manipulate the
 * line number because it's more visible and easier to grep for.
 */

#define scan_set_line(ss,n) ((ss)->line=(n));


/** Increments the current line number by 1.
 *
 * It's generally better to use this macro to manipulate the
 * line number because it's more visible and easier to grep for.
 */

#define scan_inc_line(ss)   ((ss)->line++);


/** Prepares a scanner to scan the next token.
 *
 * This macro must be called by scanners only!  See
 * \ref writing_scanners for more.
 *
 * Scanners must call scanner_enter() at the beginning of each ::scanproc
 * to prepare the scanner to scan a new token.
 */

#define scanner_enter(ss) ((ss)->token = (ss)->cursor)


/** This gives the version number of the re2c library currently being used.
 */

extern const char *re2c_library_version;

#endif

