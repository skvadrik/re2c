visibility("private")

def diff_test(
        name,
        golden,
        result,
        golden_sed = "",
        result_sed = "",
        **kwargs
    ):
    """Run a diff test comparing `golden` against `result`.

    Args:
        golden:     Golden inputs to compare against.
        result:     Result inputs to verify.
        golden_sed: SED expression to run on `golden`, may be empty string.
        result_sed: SED expression to run on `result`, may be empty string.
    """
    if not name.endswith("_test"):
        fail("Name must end in '_test'.")
    if not golden:
        fail("At least one golden input is required")
    if not result:
        fail("At least one result input is required")
    if len(golden) != len(result):
        fail("The number of golden inputs must match the number of result inputs.")
        native.sh_test(
            name = name,
            srcs = ["//bazel:diff_tests.sh"],
            data = golden + result,
            env = {
                "GOLDEN": "\n".join(golden),
                "RESULT": "\n".join(result),
                "GOLDEN_SED": golden_sed,
                "RESULT_SED": result_sed,
                "VERBOSE": "0",
            },
            **kwargs,
        )
