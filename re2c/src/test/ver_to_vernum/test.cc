#include <stdio.h> /* fprintf() */
#include <string>
#include "src/conf/ver_to_vernum.h" /* re2c::ver_to_vernum() */

namespace re2c_test {

struct examples_t {
    std::string in;
    std::string expected;
};

static const examples_t EXAMPLES[] =
{
    { "0.14",      "001400", },
    { "0.14.1",    "001401", },
    { "1",         "010000", },
    { "1.1",       "010100", },
    // Those used to exist. Should be supported?
    //{ "1.1.dev",   "010100", },
    { "1.1.1",     "010101", },
    { "1.1.1.1",   "010101", },
};

int test ()
{
    int failures = 0;

    for (size_t i = 0; i < sizeof (EXAMPLES) / sizeof (EXAMPLES[0]); ++i)
    {
        const examples_t & e = EXAMPLES[i];

        std::string got = re2c::ver_to_vernum (e.in);
        if (got != e.expected)
        {
            ++failures;
            fprintf (stderr, "FAIL: re2c::ver_to_vernum('%s') = '%s', expected '%s'\n",
                     e.in.c_str(), got.c_str(), e.expected.c_str());
        }
        else
        {
            fprintf (stderr, "PASS: re2c::ver_to_vernum('%s') = '%s\n", e.in.c_str(), got.c_str());
        }
    }

    return failures;
}

} // namespace re2c_test

int main ()
{
    return re2c_test::test ();
}
