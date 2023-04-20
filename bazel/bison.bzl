load("//bazel:diff_test.bzl", "diff_test")

visibility("public")

def _bison_impl(ctx):
    srcs = ctx.files.srcs
    if len(srcs) != 1:
        fail("Attribute `srcs` must contain exactly 1 '.yy' file.")
    err_file = ctx.actions.declare_file(ctx.attr.name + ".err")
    ctx.actions.run_shell(
        outputs = [ctx.outputs.output, ctx.outputs.defines, err_file],
        #tools = [ctx.executable._bison_tool],
        inputs = ctx.files.srcs,
        command = """
            BISON="{bison}"
            if [[ "${{BISON}}" == "auto" ]]; then
                BISON="bison"
                BISON_LOC=(
                    "/usr/local/opt/bison/bin/bison"
                    "/usr/local/bison/bin/bison"
                    "/usr/local/bin/bison"
                    "/usr/bin/bison"
                )
                for L in "${{BISON_LOC}}"; do
                    [ -x "${{L}}" ] && BISON="${{L}}" && break
                done
                echo "USING bison: '${{BISON}}'"
            fi
            "${{BISON}}" --output="{output}" --defines="{defines}" {bison_args} "{src}" > "{err}" 2>&1
            cat "{err}"
            cat "{err}" >> "{output}"
        """.format(
            bison = ctx.attr._bison_tool,
            src = srcs[0].path,
            output = ctx.outputs.output.path,
            defines = ctx.outputs.defines.path,
            err = err_file.path,
            bison_args = " ".join(ctx.attr.bison_args),
        ),
        mnemonic = "BISON",
        progress_message = "Generating bison %{label}",
        use_default_shell_env = True,
    )

_bison_attr = {
    "srcs": attr.label_list(
        doc = "The bison source.",
        allow_files = [".y", ".yy", ".y++", ".yxx", ".ypp"],
        mandatory = True,
    ),
    "output": attr.output(
        doc = "The generated output source (param to --output).",
        mandatory = True,
    ),
    "defines": attr.output(
        doc = "The generated output header (param to --defines).",
        mandatory = True,
    ),
    "bison_args": attr.string_list(
        doc = "Arguments to bison invocation.",
    ),
    "_bison_tool": attr.string(
        # Allows to specify the `bison` tool to use.
        #
        # If this is 'bison', then the tool must be available from the command
        # line through the standard environment (e.g. PATH must be set).
        #
        # If this is set to `auto`, then the following locations will be tested:
        # - /usr/local/opt/bison/bin/bison
        # - /usr/local/bison/bin/bison
        # - /usr/local/bin/bison
        # - /usr/bin/bison
        # This is done for systems where an already installed bison version is
        # too old, but a later installed version is newer.
        doc = "The target of the 'bison' executable.",
        default = "bison",
    ),
}

bison_gen = rule(
    attrs = _bison_attr,
    doc = """Use *native* bison tool to create an output files (e.g. '.cc'/'.h') from a '.yy' input.""",
    output_to_genfiles = True,
    implementation = _bison_impl,
)

def bison_gen_and_test(
        name,
        srcs,
        output,
        defines,
        golden_output,
        golden_defines,
        golden_sed = "",
        result_sed = "",
        size = "small",
        **kwargs
    ):
    """Execute bison and compare the generated files.

    Args:
        srcs: Input for bison.
        output: The generated output source (param to --output).
        defines: The generated output header (param to --defines).
        golden: Golden files to compare agains the generated `outs` files.
        golden_sed: See `diff_test` documentation.
        result_sed: See `diff_test` documentation.
        size: Test size (see bazel documentation on tests).
        **kwargs: See bison_gen and sh_test rules and their general attributs.
    """
    # Run `bison` on the input.
    bison_kwargs = dict([(k, v) for (k, v) in kwargs.items() if k not in [
        # Pass all standard args but not the test specific args.
        "env",
        "env_inherited",
        "size",
        "timeout",
        "flaky",
        "shard_count",
        "local",
    ]])
    bison_gen(
        name = name,
        srcs = srcs,
        output = output,
        defines = defines,
        **bison_kwargs
    )

    # Compare the results.
    # Pass all non bison args, that should be general and test args.
    test_args = dict([(k, v) for (k, v) in kwargs.items() if not k.startswith("bison")])
    diff_test(
        name = name + "_test",
        size = size,
        golden = [golden_output, golden_defines],
        result = [output, defines],
        golden_sed = golden_sed,
        result_sed = result_sed,
        **test_args
    )
