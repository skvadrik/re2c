#include <stddef.h>

#include "src/parse/input.h"

extern const char* help;
const char* help = "";

namespace re2c {

size_t LexerState::maxfill_main() { return 0; }
size_t LexerState::maxfill_conf() { return 0; }

}
