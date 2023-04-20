# re2c generator rules - assuming that re2c is available as '@re2c//:re2c'.

load("@bazel_skylib//lib:paths.bzl", "paths")
load("//bazel:diff_test.bzl", "diff_test")

visibility("public")

# Define supported extensions as defined by:
# . https://bazel.build/reference/be/c-cpp#cc_library_args
# . https://github.com/bazelbuild/bazel/blob/master/src/main/java/com/google/devtools/build/lib/rules/cpp/CppFileTypes.java
_C_SRC_EXT = [".c", ".cc", ".cpp", ".cxx", ".c++", ".C", ".cu", ".cl"]
_C_HDR_EXT = [".h", ".hh", ".hpp", ".ipp", ".hxx", ".h++", ".inc", ".inl", ".tlh", ".tli", ".H", ".tcc"]

def _re2c_impl(ctx):
    srcs = ctx.files.srcs
    if len(srcs) != 1:
        fail("Attribute `srcs` must contain exactly 1 '.re2c' file.")
    outs = ctx.outputs.outs
    if not outs or [o for o in outs if paths.split_extension(o.path)[1] not in _C_SRC_EXT + _C_HDR_EXT]:
        fail("Attribute `outs` must contain at least 1 '.cc' or '.h' file.")
    err_file = ctx.actions.declare_file(ctx.attr.name + ".err")
    ctx.actions.run_shell(
        outputs = outs + [err_file],
        tools = [ctx.executable.re2c_tool],
        inputs = ctx.files.srcs + ctx.files.data,
        command = """
            line_args=""
            [ -z "${re2c_parse_first_line}" ] && \\
                line_args="$(sed -rne "1s,// re2c .INPUT -o .OUTPUT (.+),\\1,p" "{src}")"
            "{re2c}" "{src}" -o "{out}" ${{line_args}} {re2c_args} {includes} > "{err}" 2>&1
            if [[ -n "$(cat "{err}")" ]]; then
                #echo -n "#error " >> "{out}"
                cat "{err}" >> "{out}"
                cat "{err}" >&2
            fi
        """.format(
            re2c = ctx.executable.re2c_tool.path,
            src = srcs[0].path,
            out = outs[0].path,
            err = err_file.path,
            includes = " ".join(list(dict([("-I" + f.dirname, 1) for f in ctx.files.data]))),
            re2c_parse_first_line = "1" if ctx.attr.re2c_parse_first_line else "",
            re2c_args = " ".join(ctx.attr.re2c_args),
        ),
        mnemonic = "RE2C",
        progress_message = "Generating re2c %{label}",
    )

_re2c_attr = {
    "srcs": attr.label_list(
        doc = "The re2c source.",
        allow_files = [
            ".re",
            ".re2c",
        ],
        mandatory = True,
    ),
    "data": attr.label_list(
        doc = "Other input data files (e.g. include files).",
        allow_files = True,
        mandatory = False,
    ),
    "outs": attr.output_list(
        doc = "The generated output source.",
        mandatory = True,
    ),
    "re2c_args": attr.string_list(
        doc = """
              Arguments to re2c invocation. These will be applied after arguments
              parsed from source if `re2c_parse_first_line` is active.
              """,
    ),
    "re2c_parse_first_line": attr.bool(
        doc = """
              Whether parse the first line of the re2c input for arguments.
              For this to work the first line must start with:
                `// re2c $INPUT -o $OUTPUT`.
              """,
    ),
    "re2c_tool": attr.label(
        # This should be private (prefied with a '_') but we need to be able to
        # specify the tool so that we can regenerate the bootstrap files.
        doc = "The target of the 're2c' executable.",
        default = Label("//:re2c"),
        allow_single_file = True,
        executable = True,
        cfg = "exec",
    ),
}

re2c_gen = rule(
    attrs = _re2c_attr,
    doc = """Use re2c tool to create an output file (e.g. '.cc') from a '.re2' input.""",
    output_to_genfiles = True,
    implementation = _re2c_impl,
)

def re2c_gen_and_test(
        name,
        srcs,
        outs,
        golden,
        golden_sed = "",
        result_sed = "",
        data = [],
        size = "small",
        **kwargs
    ):
    """Execute re2c and compare the generated files.

    Args:
        srcs: Input for re2c.
        outs: Output from re2c.
        data: Additional input for re2c.
        golden: Golden files to compare agains the generated `outs` files.
        golden_sed: See `diff_test` documentation.
        result_sed: See `diff_test` documentation.
        size: Test size (see bazel documentation on tests).
        **kwargs: See re2c_gen and sh_test rules and their general attributs.
    """
    # Run `re2c` on the input.
    re2c_kwargs = dict([(k, v) for (k, v) in kwargs.items() if k not in [
        # Pass all standard args but not the test specific args.
        "env",
        "env_inherited",
        "size",
        "timeout",
        "flaky",
        "shard_count",
        "local",
    ]])
    re2c_gen(
        name = name,
        srcs = srcs,
        outs = outs,
        data = data,
        **re2c_kwargs
    )

    # Compare the results.
    # Pass all non re2c args, that should be general and test args.
    test_args = dict([(k, v) for (k, v) in kwargs.items() if not k.startswith("re2c")])
    diff_test(
        name = name + "_test",
        size = size,
        golden = golden,
        result = outs,
        golden_sed = golden_sed,
        result_sed = result_sed,
        **test_args
    )
