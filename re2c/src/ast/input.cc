#include "src/ast/input.h"
#include "src/conf/msg.h"
#include "src/util/string_utils.h"

namespace re2c {

Input::Input(): file(NULL), name(), escaped_name() {}

bool Input::open(const char *filename)
{
    name = escaped_name = filename;
    strrreplace(escaped_name, "\\", "\\\\");

    file = name == "<stdin>" ? stdin : fopen(name.c_str(), "rb");
    if (!file) {
        error("cannot open source file: %s", name.c_str());
        return false;
    }

    return true;
}

Input::~Input()
{
    if (file != NULL && file != stdin) {
        fclose (file);
    }
}

} // namespace re2c
