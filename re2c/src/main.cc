#include "src/parse/input.h"
#include "src/parse/scanner.h"
#include "src/codegen/output.h"
#include "src/compile.h"
#include "src/options/opt.h"
#include "src/options/warn.h"

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

    Scanner scanner(&globopts, warn);
    if (!scanner.init(opts.source_file)) return 1;

    Output output(warn);

    compile(scanner, output, opts);
    if (!output.emit()) return 1;

    return warn.error() ? 1 : 0;
}
