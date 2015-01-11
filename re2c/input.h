#ifndef _input_model_h
#define _input_model_h

#include <string>
#include "basics.h"

namespace re2c
{

enum input_t
{
	INPUT_DEFAULT,
	INPUT_ISTREAM,
	INPUT_CUSTOM
};

std::string expr_peek ();
std::string expr_peek_save ();
std::string stmt_peek (uint ind);
std::string stmt_skip (uint ind);
std::string stmt_backup (uint ind);
std::string stmt_backupctx (uint ind);
std::string stmt_restore (uint ind);
std::string stmt_restorectx (uint ind);
std::string stmt_skip_peek (uint ind);
std::string stmt_skip_backup (uint ind);
std::string stmt_backup_peek (uint ind);
std::string stmt_skip_backup_peek (uint ind);
std::string expr_has_one ();
std::string expr_has (uint n);

} // end namespace re2c

#endif // _input_model_h
