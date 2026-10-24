#include "re2c/base.h"

namespace re2c_vec_01__strings_fixed {

// The same lexers as in vec_00__strings.re, but generated with `--syntax vec_fixed.syntax`, which
// overrides `code:vector_loop` with a vector loop that tests the class itself rather than its
// complement (see vec_fixed.syntax). Only the vectorized variants differ from vec_00.
/*!include:re2c "vec_strings_rules.re" */
/*!include:re2c "vec_base.re" */

} // namespace re2c_vec_01__strings_fixed
