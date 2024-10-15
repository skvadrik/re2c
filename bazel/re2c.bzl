"""re2c generator rules - assuming that re2c is available as '@re2c//:re2c'."""

load("@bazel_skylib//lib:paths.bzl", "paths")

visibility("public")

# Define supported extensions as defined by:
# . https://bazel.build/reference/be/c-cpp#cc_library_args
# . https://github.com/bazelbuild/bazel/blob/master/src/main/java/com/google/devtools/build/lib/rules/cpp/CppFileTypes.java
_C_SRC_EXT = [".c", ".cc", ".cpp", ".cxx", ".c++", ".C", ".cu", ".cl"]
_C_HDR_EXT = [".h", ".hh", ".hpp", ".ipp", ".hxx", ".h++", ".inc", ".inl", ".tlh", ".tli", ".H", ".tcc"]
_RE2C_EXT = [".re", ".re2c"]

def _re2c_impl(ctx):
    srcs = ctx.files.srcs
    if len(srcs) != 1:
        fail("Attribute `srcs` must contain exactly 1 re2c source file ({exts}).".format(exts = ", ".join(_RE2C_EXT)))
    outs = ctx.outputs.outs
    if not outs or [o for o in outs if paths.split_extension(o.path)[1] not in _C_SRC_EXT + _C_HDR_EXT]:
        fail("Attribute `outs` must contain at least 1 C/C++ shource or header file ({exts}).".format(exts = ", ".join(_C_SRC_EXT + _C_HDR_EXT)))
    ctx.actions.run_shell(
        outputs = outs,
        tools = [ctx.executable._re2c_tool],
        inputs = ctx.files.srcs + ctx.files.data,
        command = """
            "{re2c}" "{src}" -o "{out}" {re2c_args} {includes}
        """.format(
            re2c = ctx.executable._re2c_tool.path,
            src = srcs[0].path,
            out = outs[0].path,
            includes = " ".join(list(dict([("-I" + f.dirname, 1) for f in ctx.files.data]))),
            re2c_args = " ".join(ctx.attr.re2c_args),
        ),
        mnemonic = "RE2C",
        progress_message = "Generating re2c %{label}",
    )

_re2c_attr = {
    "srcs": attr.label_list(
        doc = "The re2c source.",
        allow_files = _RE2C_EXT,
        mandatory = True,
    ),
    "data": attr.label_list(
        doc = "Other input data files (e.g. include files).",
        allow_files = _C_SRC_EXT + _C_HDR_EXT,
        mandatory = False,
    ),
    "outs": attr.output_list(
        doc = "The generated output source.",
        mandatory = True,
    ),
    "re2c_args": attr.string_list(
        doc = "Arguments to re2c invocation.",
    ),
    "_re2c_tool": attr.label(
        doc = "The target of the 're2c' executable.",
        default = Label("//:re2c"),
        allow_single_file = True,
        executable = True,
        cfg = "exec",
    ),
}

re2c_gen = rule(
    attrs = _re2c_attr,
    doc = """Use re2c tool to create an output file (e.g. '.cc') from a '.re' input.""",
    output_to_genfiles = True,
    implementation = _re2c_impl,
)
