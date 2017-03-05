#ifndef _RE2C_AST_AST_
#define _RE2C_AST_AST_

#include "src/util/c99_stdint.h"
#include <string>
#include <vector>

#include "src/rule.h"
#include "src/util/free_list.h"
#include "src/util/range.h"

namespace re2c
{

/* AST must be immutable and independent of options */
struct AST
{
	static free_list<AST*> flist;
	static const uint32_t MANY;

	enum type_t
		{ NIL, SCHAR, ICHAR, CLASS, DOT, DEFAULT
		, ALT, CAT,   ITER,  DIFF,  TAG, CAP
		, REF } type;
	union {
		uint32_t schar;
		uint32_t ichar;
		const Range *cls;
		struct {
			const AST *ast1;
			const AST *ast2;
		} alt;
		struct {
			const AST *ast1;
			const AST *ast2;
		} cat;
		struct {
			const AST *ast;
			uint32_t min;
			uint32_t max;
		} iter;
		struct {
			const AST *ast1;
			const AST *ast2;
		} diff;
		const std::string *tag;
		const AST *cap;
		struct {
			const AST *ast;
			const std::string *name;
		} ref;
	};
	uint32_t line;
	uint32_t column;

	AST(uint32_t l, uint32_t c, type_t t);
	~AST();
};

struct ASTRule
{
	const AST *ast;
	const Code *code;

	ASTRule(const AST *r, const Code *c)
		: ast(r)
		, code(c)
	{}
};

struct ASTBounds
{
	uint32_t min;
	uint32_t max;
};

const AST *ast_nil(uint32_t l, uint32_t c);
const AST *ast_schar(uint32_t l, uint32_t c, uint32_t x);
const AST *ast_ichar(uint32_t l, uint32_t c, uint32_t x);
const AST *ast_class(uint32_t l, uint32_t c, const Range *r);
const AST *ast_dot(uint32_t l, uint32_t c);
const AST *ast_default(uint32_t l, uint32_t c);
const AST *ast_alt(const AST *r1, const AST *r2);
const AST *ast_cat(const AST *r1, const AST *r2);
const AST *ast_iter(const AST *r, uint32_t n, uint32_t m);
const AST *ast_diff(const AST *r1, const AST *r2);
const AST *ast_tag(uint32_t l, uint32_t c, const std::string *t);
const AST *ast_cap(const AST *r);
const AST *ast_ref(const AST *r, const std::string &n);
bool ast_need_wrap(const AST *ast);

} // namespace re2c

#endif // _RE2C_AST_AST_
