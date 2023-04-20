load("//bazel:diff_test.bzl", "diff_test")

visibility("public")

def rst2txt():
    """Private rule to generate help for re2c."""
    name = "help_cc_gen"
    native.genrule(
        name = name,
        srcs = [
            "build/rst2txt.py",
            "doc/help.rst.in",
            "bootstrap/src/msg/help.cc",
        ] + native.glob(["doc/manual/**/*.rst_"]),
        outs = [
            "doc/help.rst",
            "src/msg/help.cc",
        ],
        cmd = """
        PYTHON_LOC=("python3" "python")
        PYTHON=""
        for P in "$${PYTHON_LOC}"; do
            if [[ -x $$(which "$${P}") ]]; then
                PYTHON="$${P}"
                break
            fi
        done
        if [[ -n "$${PYTHON}" ]]; then
            if ! $$("$${PYTHON}" -c "import docutils" >/dev/null 2>&1); then
                #PYTHON=""
                echo "WARN: Python module 'docutils' not found."
            fi
        fi
        if [[ -n "$${PYTHON}" ]]; then
            # Fix include path '@top_srcdir@' by replacing it followed by directory
            # of the provided input with the current dir followed by the location of
            # the input file.
            # This way we pass down the absolute path of the input. This is
            # important as the generated 'doc/help.rst' is in a different dir
            # than the include '*.rst_' files.
            cat "$(location doc/help.rst.in)" | sed -re "s,@top_srcdir@/$$(dirname "doc/help.rst.in"),$${PWD}/$$(dirname $(location doc/help.rst.in)),g" > "$(location doc/help.rst)"
            "$${PYTHON}" "$(location build/rst2txt.py)" --variable-name=help "$(location doc/help.rst)" "$(location src/msg/help.cc)"
        else
            echo "WARN: Not regenerating 'src/msg/help.cc'."
            cp "$(location bootstrap/src/msg/help.cc)" "$(location src/msg/help.cc)"
        fi
        """,
    )
    diff_test(
        name = name + "_test",
        golden = ["bootstrap/src/msg/help.cc"],
        result = ["src/msg/help.cc"],
    )