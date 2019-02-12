#include "src/parse/input.h"
#include "src/parse/scanner.h"
#include "src/codegen/output.h"
#include "src/compile.h"
#include "src/msg/msg.h"
#include "src/options/opt.h"

using namespace re2c;

int main(int, char *argv[])
{
    conopt_t globopts;
    Opt opts(globopts);
    Msg msg;

    switch (parse_opts(argv, globopts, opts, msg)) {
        case OK:        break;
        case EXIT_OK:   return 0;
        case EXIT_FAIL: return 1;
    }

    Scanner scanner(&globopts, msg);
    if (!scanner.open(opts.source_file, NULL)) {
        return 1;
    }

    Output output(msg);

    compile(scanner, output, opts);

    if (!output.emit()) {
        return 1;
    }

    return msg.warn.error() ? 1 : 0;
}
