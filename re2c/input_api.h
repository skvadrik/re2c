#ifndef _input_api_h
#define _input_api_h

#include <map>
#include <string>

#include "basics.h"

namespace re2c
{

class InputAPI
{
public:
	enum type_t
		{ DEFAULT
		, CUSTOM
		};

private:
	type_t type;

public:
	void set (type_t t);
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
	std::string expr_lessthan_one ();
	std::string expr_lessthan (uint n);
};

} // end namespace re2c

#endif // _input_api_h
