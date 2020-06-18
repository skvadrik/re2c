#include <assert.h>

#include "src/codegen/helpers.h"


namespace re2c_test {

static std::string f(const std::string &str, const std::string &stub,
    const char *arg, size_t val, bool allow_unnamed)
{
    std::ostringstream os;
    os << str;
    re2c::argsubst(os, stub, arg, allow_unnamed, val);
    return os.str();
}

} // namespace re2c_test

int main()
{
    assert(re2c_test::f("", "@@", "", 42, false) == "");
    assert(re2c_test::f("@@, @@, @@{xyz}, @@{xy}, @@{xyzz}, @@@{xyz}", "@@", "xyz", 42, false) == "@@, @@, 42, @@{xy}, @@{xyzz}, @42");
    assert(re2c_test::f("@@, @@, @@{xyz}, @@{xy}, @@{xyzz}, @@@{xyz}", "@@", "xyz", 42, true)  == "42, 42, 42, 42{xy}, 42{xyzz}, 42@{xyz}");
    assert(re2c_test::f("@@{",      "@@", "xy", 42, false) == "@@{");
    assert(re2c_test::f("@@{x",     "@@", "xy", 42, false) == "@@{x");
    assert(re2c_test::f("@@{xy",    "@@", "xy", 42, false) == "@@{xy");
    assert(re2c_test::f("@@{xyz",   "@@", "xy", 42, false) == "@@{xyz");
    assert(re2c_test::f("@@{xy@@}", "@@", "xy", 42, false) == "@@{xy@@}");
    assert(re2c_test::f("@@{",      "@@", "xy", 42, true) == "42{");
    assert(re2c_test::f("@@{x",     "@@", "xy", 42, true) == "42{x");
    assert(re2c_test::f("@@{xy",    "@@", "xy", 42, true) == "42{xy");
    assert(re2c_test::f("@@{xyz",   "@@", "xy", 42, true) == "42{xyz");
    assert(re2c_test::f("@@{xy@@}", "@@", "xy", 42, true) == "42{xy42}");
    assert(re2c_test::f("@@@@@", "@@", "", 42, true) == "4242@");
    assert(re2c_test::f("@@{xyz}@@{xyz}@", "@@", "xyz", 42, true) == "4242@");
    assert(re2c_test::f("@@@{xyz}@@{xyz}", "@@", "xyz", 42, true) == "42@{xyz}42");
    assert(re2c_test::f("@@@{xyz}@@{xyz}", "@@", "xyz", 42, false) == "@4242");

    return 0;
}
