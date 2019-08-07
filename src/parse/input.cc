#include "src/msg/msg.h"
#include "src/parse/input.h"
#include "src/parse/scanner.h"
#include "src/util/get_dir.h"
#include "src/util/string_utils.h"


namespace re2c {

Input::Input(size_t fidx)
    : file(NULL)
    , name()
    , escaped_name()
    , so(Scanner::ENDPOS)
    , eo(Scanner::ENDPOS)
    , line(1)
    , fidx(static_cast<uint32_t>(fidx))
{}

bool Input::open(const std::string &filename, const std::string *parent
    , const std::vector<std::string> &incpaths)
{
    std::string path;
    name = filename;

    if (!parent) {
        path = name;
        file = name == "<stdin>" ? stdin : fopen(name.c_str(), "rb");
    }
    else {
        // first, search relative to the directory of including file
        path = *parent;
        get_dir(path);
        path += name;
        file = fopen(path.c_str(), "rb");

        // otherwise search in all include paths
        for (size_t i = 0; !file && i < incpaths.size(); ++i) {
            path = incpaths[i] + name;
            file = fopen(path.c_str(), "rb");
        }

        // if user-defined include paths failed, try stdlib path
        if (!file) {
            path = RE2C_STDLIB_DIR + name;
            file = fopen(path.c_str(), "rb");
        }
    }

    if (!file) {
        fatal("cannot open file: %s", name.c_str());
    }

    // name displayed in #line directives is the resolved name
    escaped_name = path;
    strrreplace(escaped_name, "\\", "\\\\");

    return true;
}

Input::~Input()
{
    if (file != NULL && file != stdin) {
        fclose (file);
    }
}

} // namespace re2c
