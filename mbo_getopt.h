/*
 Author: Marcus Boerger <helly@users.sourceforge.net>
*/

/* $Id$ */

/* Define structure for one recognized option (both single char and long name).
 * If short_open is '-' this is the last option.
 */

#ifndef RE2C_MBO_GETOPT_H_INCLUDE_GUARD_
#define RE2C_MBO_GETOPT_H_INCLUDE_GUARD_

namespace re2c
{

typedef struct _mbo_opt_struct
{
	const char opt_char;
	const int need_param;
	const char * opt_name;
}

mbo_opt_struct;

int mbo_getopt(int argc, char* const *argv, const mbo_opt_struct opts[], char **optarg, int *optind, int show_err);

} // end namespace re2c

#endif

