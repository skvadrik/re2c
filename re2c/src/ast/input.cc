#include "src/ast/input.h"
#include "src/ast/scanner.h"
#include "src/conf/msg.h"
#include "src/util/string_utils.h"

namespace re2c {

Input::Input()
    : file(NULL)
    , name()
    , escaped_name()
    , so(Scanner::ENDPOS)
    , eo(Scanner::ENDPOS)
{}

bool Input::open(const std::string &filename)
{
    name = escaped_name = filename;
    strrreplace(escaped_name, "\\", "\\\\");

    file = name == "<stdin>" ? stdin : fopen(name.c_str(), "rb");
    if (!file) {
        error("cannot open file: %s", name.c_str());
        return false;
    }

    return true;
}

bool Input::open_in_dirs(const std::string &filename
    , const std::vector<std::string> &incpaths)
{
    name = escaped_name = filename;
    strrreplace(escaped_name, "\\", "\\\\");

    for (size_t i = 0; !file && i < incpaths.size(); ++i) {
        const std::string path = incpaths[i] + name;
        file = fopen(path.c_str(), "rb");
    }
    if (!file) {
        error("cannot open file: %s", name.c_str());
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
