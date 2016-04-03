#ifndef _RE2C_CODEGEN_EMIT_
#define _RE2C_CODEGEN_EMIT_

#include "src/codegen/output.h"
#include "src/ir/adfa/adfa.h"

namespace re2c {

typedef std::vector<std::string> RegExpIndices;

void emit_action
	( const Action & action
	, OutputFile & o
	, uint32_t ind
	, bool & readCh
	, const State * const s
	, const std::string & condName
	, const Skeleton * skeleton
	, const std::set<label_t> & used_labels
	, bool save_yyaccept
	, bool base_ctxmarker
	);

} // namespace re2c

#endif // _RE2C_CODEGEN_EMIT_
