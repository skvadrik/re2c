#include "src/ast/input.h"
#include "src/ast/scanner.h"
#include "src/code/output.h"
#include "src/compile.h"
#include "src/conf/msg.h"
#include "src/conf/opt.h"
#include "src/conf/warn.h"

using namespace re2c;

int main(int, char *argv[])
{
    conopt_t globopts;
    Opt opts(globopts);
    Warn warn;

    switch (parse_opts(argv, globopts, opts, warn)) {
        case OK:        break;
        case EXIT_OK:   return 0;
        case EXIT_FAIL: return 1;
    }

    re2c::Input input(opts.source_file);
    if (!input.open()) {
        error("cannot open source file: %s", opts.source_file);
        return 1;
    }
    Scanner scanner(input, warn);
    Output output(warn);

    compile(scanner, output, opts);
    if (!output.emit()) return 1;

    return warn.error() ? 1 : 0;
}
