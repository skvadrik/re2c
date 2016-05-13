#include "src/codegen/emit.h"
#include "src/codegen/input_api.h"
#include "src/conf/opt.h"
#include "src/globals.h"

namespace re2c
{

std::string subst_tags(const std::string &action,
	const std::valarray<Tag> &tags, size_t ltag, size_t htag)
{
	if (ltag >= htag) {
		return action;
	}

	std::string result;
	const char
		*head = action.c_str(),
		*last = head + action.length(),
		*tail = head,
		*base;

	loop: /*!re2c

		re2c:define:YYCTYPE = char;
		re2c:define:YYCURSOR = head;
		re2c:define:YYCTXMARKER = base;
		re2c:yyfill:enable = 0;
		re2c:flags:tags = 1;

		* { goto loop; }

		"\x00" {
			if (base == last) {
				result.append(tail, base);
				return result;
			}
			goto loop;
		}

		"@" @name [a-zA-Z0-9_]+ {
			const std::string name(@name, head);
			for (size_t i = ltag; i < htag; ++i) {
				const Tag &t = tags[i];
				if (name == *t.name) {
					result.append(tail, base);
					result.append(t.type == Tag::VAR
						? opts->input_api.expr_tag(vartag_expr(t.name, t.rule))
						: opts->input_api.expr_tag_fix(t, tags));
					tail = head;
					break;
				}
			}
			goto loop;
		}
	*/
}

} // namespace re2c
