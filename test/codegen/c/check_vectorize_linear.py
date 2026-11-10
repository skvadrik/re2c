#!/usr/bin/env python3
"""Regenerate, inspect, compile and run the --vectorize-linear C and Go acceptance tests.

Usage: python3 test/codegen/c/check_vectorize_linear.py /path/to/re2c [--cc gcc] [--cc clang]

Like re2c, this test is in the public domain.
"""

import argparse
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile


FORBIDDEN_GENERIC_IDENT_RE = re.compile(
    r"\b(YYCURSOR|YYLIMIT|YYMARKER|YYINPUT|yycursor|yylimit|yymarker|yyinput)\b"
)
GO_MULTIBYTE_SHIFT_RE = re.compile(r"<<\s*\(?8")


def run(cmd, cwd=None, env=None):
    p = subprocess.run(cmd, cwd=cwd, env=env, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    if p.returncode != 0:
        sys.stdout.write(p.stdout)
        raise SystemExit("command failed: %s" % " ".join(str(x) for x in cmd))
    return p.stdout


def expect_failure(label, cmd, want_substr, cwd=None):
    p = subprocess.run(cmd, cwd=cwd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    if p.returncode == 0 or want_substr not in p.stdout:
        print(f"{label}: FAIL ({p.stdout.strip()})")
        return False
    print(f"{label}: ok")
    return True


def have_sanitizers(cc, tmp):
    probe = Path(tmp) / "probe.c"
    probe.write_text("int main(void) { return 0; }\n")
    p = subprocess.run(
        [cc, "-O1", "-g", "-fsanitize=address,undefined", "-o", str(Path(tmp) / "probe"), str(probe)],
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
    )
    return p.returncode == 0


def parse_switches(first_line, prefix):
    assert first_line.startswith(prefix), first_line
    return first_line[len(prefix):].split()


def extract_syntax_rhs(stx_text, key):
    m = re.search(rf"(?m)^\s*{re.escape(key)}\s*=\s*", stx_text)
    if not m:
        return None
    i = m.end()
    n = len(stx_text)
    in_str = False
    out = []
    while i < n:
        ch = stx_text[i]
        if in_str:
            out.append(ch)
            if ch == "\\" and i + 1 < n:
                i += 1
                out.append(stx_text[i])
            elif ch == '"':
                in_str = False
            i += 1
        else:
            if ch == '"':
                in_str = True
                out.append(ch)
                i += 1
            elif ch == "/" and i + 1 < n and stx_text[i + 1] == "/":
                while i < n and stx_text[i] != "\n":
                    i += 1
            elif ch == ";":
                return "".join(out).strip()
            else:
                out.append(ch)
                i += 1
    return None


def strip_syntax_layout_tokens(rhs):
    out = []
    buf = []
    in_quote = None
    i = 0
    n = len(rhs)
    while i < n:
        ch = rhs[i]
        if in_quote is not None:
            out.append(ch)
            if ch == "\\" and i + 1 < n:
                i += 1
                out.append(rhs[i])
            elif ch == in_quote:
                in_quote = None
            i += 1
        elif ch in ('"', "'"):
            if buf:
                cleaned = re.sub(r"\b(topindent|nl|indent|dedent)\b", " ", "".join(buf))
                out.append(cleaned)
                buf = []
            in_quote = ch
            out.append(ch)
            i += 1
        else:
            buf.append(ch)
            i += 1
    if buf:
        cleaned = re.sub(r"\b(topindent|nl|indent|dedent)\b", " ", "".join(buf))
        out.append(cleaned)
    return re.sub(r"\s+", " ", "".join(out)).strip()


def make_wide_hits_syntax(stx_text, fallback_stx=None):
    lines = []
    if fallback_stx is not None:
        lines.append(stx_text.rstrip() + "\n\n")
    for width in (2, 4, 8):
        key = f"code:yypeek{width}"
        rhs = extract_syntax_rhs(stx_text, key)
        if not rhs and fallback_stx is not None:
            rhs = extract_syntax_rhs(fallback_stx, key)
        if not rhs:
            raise SystemExit(f"missing {key} in syntax configuration")
        clean_rhs = strip_syntax_layout_tokens(rhs)
        if not clean_rhs:
            raise SystemExit(f"empty {key} after stripping layout tokens")
        lines.append(f'{key} = "(++re2c_wide{width}_hits, (" {clean_rhs} "))";\n')
    return "".join(lines)


def find_custom_syntax_switch(switches):
    for i, sw in enumerate(switches):
        if sw in ("--syntax", "-S"):
            if i + 1 >= len(switches):
                raise SystemExit(f"missing argument after {sw}")
            return sw, switches[i + 1], switches[:i] + [sw, None] + switches[i + 2 :], i + 1
        if sw.startswith("--syntax="):
            val = sw[len("--syntax=") :]
            return "--syntax=", val, switches[:i] + [None] + switches[i + 1 :], i
        if sw.startswith("-S="):
            val = sw[len("-S=") :]
            return "-S=", val, switches[:i] + [None] + switches[i + 1 :], i
    return None, None, None, None


def resolve_executable(cand):
    resolved = shutil.which(cand)
    if resolved:
        return resolved
    p = Path(cand)
    if p.is_file() and os.access(str(p), os.X_OK):
        return str(p)
    return None


def discover_c_compilers(explicit_ccs):
    if explicit_ccs:
        compilers = []
        seen_realpaths = set()
        for cand in explicit_ccs:
            resolved = resolve_executable(cand)
            if not resolved:
                raise SystemExit(f"C compiler not found: {cand}")
            real = os.path.realpath(resolved)
            if real not in seen_realpaths:
                seen_realpaths.add(real)
                compilers.append(cand)
        return compilers

    candidates = []
    if os.environ.get("CC"):
        candidates.append(os.environ["CC"])
    candidates.extend(["gcc", "clang"])
    compilers = []
    seen_realpaths = set()
    for cand in candidates:
        resolved = resolve_executable(cand)
        if resolved:
            real = os.path.realpath(resolved)
            if real not in seen_realpaths:
                seen_realpaths.add(real)
                compilers.append(cand)
    if not compilers:
        raise SystemExit("no C compiler found")
    return compilers


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("re2c")
    ap.add_argument("--cc", action="append", default=[], help="C compiler(s), default gcc and clang")
    ap.add_argument("--go", default=None, help="Go executable (default: go)")
    ap.add_argument("--language", choices=["all", "c", "go"], default="all")
    args = ap.parse_args()

    go_bin = args.go if args.go is not None else "go"
    go_resolved = resolve_executable(go_bin)
    if (args.language == "go" or args.go is not None) and not go_resolved:
        raise SystemExit(f"Go executable not found: {go_bin}")

    re2c_bin = str(Path(args.re2c).resolve())
    here = Path(__file__).resolve().parent
    test_root = here.parents[1]
    root = here.parents[2]
    failures = 0

    with tempfile.TemporaryDirectory(prefix="re2c-linear-") as tmp:
        tmp_path = Path(tmp)

        # 1. Explicit rejection of --skeleton with --vectorize-linear.
        skel_re = here / "vectorize_linear_unsupported_skeleton.re"
        if not expect_failure(
            "skeleton rejection",
            [re2c_bin, "--vectorize-linear", "--skeleton", str(skel_re), "-o", str(tmp_path / "skel.c")],
            "re2c: error: `vectorize:linear` is not supported with --skeleton",
        ):
            failures += 1

        # 2. Explicit rejection (-Werror) when bounds guard configuration is missing in C and Go.
        c_gen_nofill = tmp_path / "c_gen_nofill.re"
        c_gen_nofill.write_text(
            '/*!re2c\nre2c:yyfill:enable = 0;\n"abcdefgh" { return 1; }\n* { return 0; }\n*/\n'
        )
        c_gen_nocheck = tmp_path / "c_gen_nocheck.re"
        c_gen_nocheck.write_text(
            '/*!re2c\nre2c:yyfill:check = 0;\n"abcdefgh" { return 1; }\n* { return 0; }\n*/\n'
        )
        go_gen_nofill = tmp_path / "go_gen_nofill.re"
        go_gen_nofill.write_text(
            '/*!re2c\nre2c:yyfill:enable = 0;\n"abcdefgh" { return 1 }\n* { return 0 }\n*/\n'
        )
        go_gen_nocheck = tmp_path / "go_gen_nocheck.re"
        go_gen_nocheck.write_text(
            '/*!re2c\nre2c:yyfill:check = 0;\n"abcdefgh" { return 1 }\n* { return 0 }\n*/\n'
        )
        go_simple_nocheck = tmp_path / "go_simple_nocheck.re"
        go_simple_nocheck.write_text(
            '/*!re2c\nre2c:api = simple;\nre2c:yyfill:check = 0;\n"abcdefgh" { return 1 }\n* { return 0 }\n*/\n'
        )

        disabled_checks = [
            (
                "c generic no-YYFILL without YYLESSTHAN",
                [re2c_bin, "--vectorize-linear", "--api", "generic", "-Werror",
                 str(c_gen_nofill), "-o", str(tmp_path / "c_gen_nofill.c")],
                "YYFILL is disabled and YYLESSTHAN is not explicitly configured",
            ),
            (
                "c generic no-YYFILL-check without YYLESSTHAN",
                [re2c_bin, "--vectorize-linear", "--api", "generic", "-Werror",
                 str(c_gen_nocheck), "-o", str(tmp_path / "c_gen_nocheck.c")],
                "YYFILL check is disabled and YYLESSTHAN is not explicitly configured",
            ),
            (
                "go generic no-YYFILL without YYLESSTHAN",
                [re2c_bin, "--lang", "go", "--vectorize-linear", "--api", "generic", "-Werror",
                 str(go_gen_nofill), "-o", str(tmp_path / "go_gen_nofill.go")],
                "YYFILL is disabled and YYLESSTHAN is not explicitly configured",
            ),
            (
                "go generic no-YYFILL-check without YYLESSTHAN",
                [re2c_bin, "--lang", "go", "--vectorize-linear", "--api", "generic", "-Werror",
                 str(go_gen_nocheck), "-o", str(tmp_path / "go_gen_nocheck.go")],
                "YYFILL check is disabled and YYLESSTHAN is not explicitly configured",
            ),
            (
                "c simple no-YYFILL without YYLIMIT",
                [re2c_bin, "--vectorize-linear", "-Werror",
                 str(test_root / "linear_disabled_limit.re"), "-o", str(tmp_path / "c_simple_nolim.c")],
                "YYFILL is disabled and YYLIMIT is not explicitly configured",
            ),
            (
                "c simple no-YYFILL-check without YYLIMIT",
                [re2c_bin, "--vectorize-linear", "-Werror",
                 str(here / "vectorize_linear_fill_nocheck.re"), "-o", str(tmp_path / "c_simple_nocheck.c")],
                "YYFILL check is disabled and YYLIMIT is not explicitly configured",
            ),
            (
                "go simple no-YYFILL without YYLIMIT",
                [re2c_bin, "--lang", "go", "--vectorize-linear", "-Werror",
                 str(test_root / "codegen/go/vectorize_linear_disabled_limit.re"),
                 "-o", str(tmp_path / "go_simple_nolim.go")],
                "YYFILL is disabled and YYLIMIT is not explicitly configured",
            ),
            (
                "go simple no-YYFILL-check without YYLIMIT",
                [re2c_bin, "--lang", "go", "--vectorize-linear", "-Werror",
                 str(go_simple_nocheck), "-o", str(tmp_path / "go_simple_nocheck.go")],
                "YYFILL check is disabled and YYLIMIT is not explicitly configured",
            ),
        ]
        for label, cmd, want in disabled_checks:
            if not expect_failure(label, cmd, want):
                failures += 1

        # 3. Rejection of --vectorize-linear (CLI and config) on unsupported backends via supported_features.
        want_feat_err = "`vectorize-linear` feature is not supported for this backend"
        unsupported_checks = [
            (
                "unsupported backend CLI (--lang d)",
                [re2c_bin, "--lang", "d", "--vectorize-linear",
                 str(test_root / "codegen/d/unsupported_vectorize_linear.re"),
                 "-o", str(tmp_path / "unsup.d")],
                f"re2c: error: {want_feat_err}",
            ),
            (
                "unsupported backend config (--lang d)",
                [re2c_bin, "--lang", "d",
                 str(test_root / "codegen/d/unsupported_vectorize_linear_config.re"),
                 "-o", str(tmp_path / "unsup_cfg.d")],
                f"error: {want_feat_err}",
            ),
            (
                "empty supported_features CLI (--syntax)",
                [re2c_bin, "--vectorize-linear", "--syntax", "unsupported_vectorize_linear_none.inc",
                 "-I", str(test_root),
                 str(test_root / "unsupported_vectorize_linear_none.re"),
                 "-o", str(tmp_path / "unsup_none.c")],
                f"re2c: error: {want_feat_err}",
            ),
            (
                "empty supported_features config (--syntax)",
                [re2c_bin, "--syntax", "unsupported_vectorize_linear_config_none.inc",
                 "-I", str(test_root),
                 str(test_root / "unsupported_vectorize_linear_config_none.re"),
                 "-o", str(tmp_path / "unsup_cfg_none.c")],
                f"error: {want_feat_err}",
            ),
        ]
        for label, cmd, want in unsupported_checks:
            if not expect_failure(label, cmd, want):
                failures += 1

        if args.language in ("all", "c"):
            compilers = discover_c_compilers(args.cc)
            c_sources = sorted(
                here.rglob("vectorize_linear*.re"),
                key=lambda s: (len(s.relative_to(here).parts), str(s)),
            )
            runnable_c = [s for s in c_sources if "int main(" in s.read_text()]
            assert runnable_c, "no runnable C vectorize_linear tests found"

            san_cache = {cc: have_sanitizers(cc, tmp) for cc in compilers}
            wide_hits_hdr = tmp_path / "wide_hits_rt.h"
            wide_hits_hdr.write_text(
                "#ifndef RE2C_WIDE_HITS_RT_H\n"
                "#define RE2C_WIDE_HITS_RT_H\n"
                "extern unsigned long re2c_wide2_hits;\n"
                "extern unsigned long re2c_wide4_hits;\n"
                "extern unsigned long re2c_wide8_hits;\n"
                "#endif\n"
            )
            wide_hits_rt = tmp_path / "wide_hits_rt.c"
            wide_hits_rt.write_text(
                '#include "wide_hits_rt.h"\n'
                "#include <stdio.h>\n"
                "#include <stdlib.h>\n"
                "unsigned long re2c_wide2_hits = 0;\n"
                "unsigned long re2c_wide4_hits = 0;\n"
                "unsigned long re2c_wide8_hits = 0;\n"
                "__attribute__((destructor)) static void re2c_verify_wide_hits(void) {\n"
                "    if (re2c_wide2_hits + re2c_wide4_hits + re2c_wide8_hits == 0) {\n"
                '        fprintf(stderr, "DT-07 FAIL: zero wide reads executed at runtime\\n");\n'
                "        _Exit(97);\n"
                "    }\n"
                "#ifdef RE2C_EXPECT_WIDE2\n"
                "    if (re2c_wide2_hits == 0) {\n"
                '        fprintf(stderr, "DT-07 FAIL: code:yypeek2 emitted but never executed\\n");\n'
                "        _Exit(97);\n"
                "    }\n"
                "#endif\n"
                "#ifdef RE2C_EXPECT_WIDE4\n"
                "    if (re2c_wide4_hits == 0) {\n"
                '        fprintf(stderr, "DT-07 FAIL: code:yypeek4 emitted but never executed\\n");\n'
                "        _Exit(97);\n"
                "    }\n"
                "#endif\n"
                "#ifdef RE2C_EXPECT_WIDE8\n"
                "    if (re2c_wide8_hits == 0) {\n"
                '        fprintf(stderr, "DT-07 FAIL: code:yypeek8 emitted but never executed\\n");\n'
                "        _Exit(97);\n"
                "    }\n"
                "#endif\n"
                "}\n"
            )
            c_stx = (root / "include/syntax/c").read_text()
            default_hits_stx_name = None

            for src in runnable_c:
                rel = src.relative_to(here)
                tag = str(rel.with_suffix("")).replace("/", "_")
                first = src.read_text().splitlines()[0]
                switches = parse_switches(first, "// re2c $INPUT -o $OUTPUT")
                gen = tmp_path / f"{tag}.c"
                run([re2c_bin, "-I", str(src.parent), str(src), "-o", str(gen)] + switches)
                text = gen.read_text()

                if "sizeof(*(" in text:
                    print(f"c {rel}: unexpected sizeof(*(YYCURSOR)) guard in generated code")
                    failures += 1

                if src.name == "vectorize_linear_generic_api.re":
                    m = FORBIDDEN_GENERIC_IDENT_RE.search(text)
                    if m:
                        print(f"c {rel}: forbidden identifier {m.group(0)!r} leaked in generic API output")
                        failures += 1
                    for needle in (
                        "YYPEEK2()",
                        "YYPEEK4()",
                        "YYPEEK8()",
                        "YYLESSTHAN(",
                        "YYSHIFT(",
                        "opaque_peek2(&s)",
                        "opaque_peek4(&s)",
                        "opaque_peek8(&s)",
                        "(s.end - s.idx) <",
                        "s.idx +=",
                    ):
                        if needle not in text:
                            print(f"c {rel}: missing generic API pattern {needle!r}")
                            failures += 1
                elif "encoding_" not in src.name and "-Wno-vectorize-linear-disabled" not in switches:
                    if "<< 8" not in text:
                        print(f"c {rel}: missing multi-byte read shift in generated code")
                        failures += 1

                if src.name == "vectorize_linear_global_vars.re":
                    for needle in ("<< 8", "<< 16", "<< 56"):
                        if needle not in text:
                            print(f"c {rel}: missing overridden global-vars wide peek shift {needle!r}")
                            failures += 1

                if src.name == "vectorize_linear_parity_computed_gotos.re":
                    if "yytarget[" not in text:
                        print(f"c {rel}: missing computed-goto yytarget table in generated code")
                        failures += 1

                if src.name == "vectorize_linear_rules_reuse.re":
                    fn_markers = [
                        ("lex_use_block", True),
                        ("lex_use_directive", True),
                        ("lex_local_scalar", False),
                        ("lex_local_block", True),
                        ("lex_after_local", True),
                        ("lex_generic_unparen", True),
                        ("check_input", None),
                    ]
                    for m_idx in range(len(fn_markers) - 1):
                        fn_name, want_wide = fn_markers[m_idx]
                        next_name, _ = fn_markers[m_idx + 1]
                        start_pat = f"static int {fn_name}("
                        end_pat = f"static int {next_name}("
                        if start_pat not in text or end_pat not in text:
                            print(f"c {rel}: missing function marker {fn_name}")
                            failures += 1
                            continue
                        fn_body = text.split(start_pat, 1)[1].split(end_pat, 1)[0]
                        if want_wide and "<< 8" not in fn_body:
                            print(f"c {rel}: missing wide read in {fn_name}")
                            failures += 1
                        if want_wide is False and "<< 8" in fn_body:
                            print(f"c {rel}: unexpected wide read in {fn_name}")
                            failures += 1

                if src.name == "vectorize_linear_parity.re" and "static int tagged_1(" in text:
                    tagged_body = text.split("static int tagged_1(", 1)[1]
                    for needle in ("yyt1 = YYCURSOR;", "<< 8"):
                        if needle not in tagged_body:
                            print(f"c {rel}: missing {needle!r} in tagged_1")
                            failures += 1

                for idx, cc in enumerate(compilers):
                    flag_sets = [["-O2"]]
                    if san_cache[cc]:
                        flag_sets.append(["-O1", "-g", "-fsanitize=address,undefined", "-fno-sanitize-recover=all"])
                    for f in flag_sets:
                        exe = tmp_path / f"{tag}_{idx}_{Path(cc).name}_{f[0].lstrip('-')}"
                        run([cc, "-std=c11", "-Wall", "-Wextra", "-Werror"] + f + ["-o", str(exe), str(gen)])
                        out = subprocess.run(
                            [str(exe)],
                            stdout=subprocess.PIPE,
                            stderr=subprocess.STDOUT,
                            text=True,
                            env=dict(os.environ, ASAN_OPTIONS="detect_leaks=0"),
                        )
                        status = "ok" if out.returncode == 0 else "FAIL"
                        if status == "FAIL":
                            failures += 1
                            sys.stdout.write(out.stdout)
                        print("c %-48s %-6s %-50s %s" % (rel, Path(cc).name, " ".join(f), status))

                # DT-07: prove at runtime that emitted code:yypeek{2,4,8} templates actually execute
                # on every runnable non-generic C fixture where linear vectorization is active.
                if (
                    src.name != "vectorize_linear_generic_api.re"
                    and "encoding_" not in src.name
                    and "-Wno-vectorize-linear-disabled" not in switches
                ):
                    sw_prefix, custom_stx_arg, hit_switches_tpl, slot_idx = find_custom_syntax_switch(switches)
                    if custom_stx_arg is not None:
                        custom_stx = (src.parent / custom_stx_arg).read_text()
                        stx_name = f"{tag}_wide_hits.inc"
                        (tmp_path / stx_name).write_text(make_wide_hits_syntax(custom_stx, fallback_stx=c_stx))
                        hit_switches = list(hit_switches_tpl)
                        if sw_prefix.endswith("="):
                            hit_switches[slot_idx] = f"{sw_prefix}{stx_name}"
                        else:
                            hit_switches[slot_idx] = stx_name
                    else:
                        if default_hits_stx_name is None:
                            default_hits_stx_name = "default_wide_hits.inc"
                            (tmp_path / default_hits_stx_name).write_text(make_wide_hits_syntax(c_stx))
                        hit_switches = switches + ["--syntax", default_hits_stx_name]

                    gen_hits = tmp_path / f"{tag}_hits.c"
                    run(
                        [re2c_bin, "-I", str(tmp_path), "-I", str(src.parent), str(src), "-o", str(gen_hits)]
                        + hit_switches
                    )
                    hits_text = gen_hits.read_text()
                    expect_defs = [
                        f"-DRE2C_EXPECT_WIDE{w}=1"
                        for w in (2, 4, 8)
                        if f"++re2c_wide{w}_hits" in hits_text
                    ]
                    if not expect_defs:
                        print(f"c {rel}: DT-07 FAIL (no wide peek counters emitted)")
                        failures += 1
                    else:
                        hits_exe = tmp_path / f"{tag}_wide_hits_exe"
                        run(
                            [
                                compilers[0],
                                "-std=c11",
                                "-Wall",
                                "-Wextra",
                                "-Werror",
                                "-O2",
                                "-I",
                                str(tmp_path),
                                "-include",
                                "wide_hits_rt.h",
                            ]
                            + expect_defs
                            + ["-o", str(hits_exe), str(gen_hits), str(wide_hits_rt)]
                        )
                        hits_out = subprocess.run(
                            [str(hits_exe)],
                            stdout=subprocess.PIPE,
                            stderr=subprocess.STDOUT,
                            text=True,
                        )
                        hits_status = "ok" if hits_out.returncode == 0 else "FAIL"
                        if hits_status == "FAIL":
                            failures += 1
                            sys.stdout.write(hits_out.stdout)
                        print("c %-48s %-6s %-50s %s" % (rel, Path(compilers[0]).name, "wide-hits-rt", hits_status))

        if args.language in ("all", "go") and go_resolved:
            go_dir = tmp_path / "go"
            go_dir.mkdir(exist_ok=True)
            (go_dir / "go.mod").write_text("module re2c.local/check-linear\n\ngo 1.18\n")
            go_env = dict(os.environ, GOTOOLCHAIN="local")
            go_env.pop("GOWORK", None)

            go_root = root / "test/codegen/go"
            go_sources = sorted(go_root.glob("vectorize_linear*.re"))
            runnable_go = [s for s in go_sources if "func main()" in s.read_text()]
            assert runnable_go, "no runnable Go vectorize_linear tests found"

            for src in runnable_go:
                first = src.read_text().splitlines()[0]
                switches = parse_switches(first, "//go:generate re2go $INPUT -o $OUTPUT")
                gen = go_dir / f"{src.stem}.go"
                run([re2c_bin, "--lang", "go", "-I", str(src.parent), str(src), "-o", str(gen)] + switches)
                text = gen.read_text()

                if "Sizeof" in text or "int(^uint8(0))" in text:
                    print(f"go {src.name}: unexpected width check in generated code")
                    failures += 1

                if src.name == "vectorize_linear_generic_api.re":
                    m = FORBIDDEN_GENERIC_IDENT_RE.search(text)
                    if m:
                        print(f"go {src.name}: forbidden identifier {m.group(0)!r} leaked in generic API output")
                        failures += 1
                    for needle in (
                        "YYPEEK2()",
                        "YYPEEK4()",
                        "YYPEEK8()",
                        "YYLESSTHAN(",
                        "YYSHIFT(",
                        "s.peek2()",
                        "s.peek4()",
                        "s.peek8()",
                        "(s.end - s.idx) <",
                        "s.idx +=",
                    ):
                        if needle not in text:
                            print(f"go {src.name}: missing generic API pattern {needle!r}")
                            failures += 1
                elif "encoding_" not in src.name:
                    if not GO_MULTIBYTE_SHIFT_RE.search(text):
                        print(f"go {src.name}: missing multi-byte read shift in generated code")
                        failures += 1

                out = subprocess.run(
                    [go_resolved, "run", str(gen)],
                    cwd=str(go_dir),
                    env=go_env,
                    stdout=subprocess.PIPE,
                    stderr=subprocess.STDOUT,
                    text=True,
                )
                status = "ok" if out.returncode == 0 else "FAIL"
                if status == "FAIL":
                    failures += 1
                    sys.stdout.write(out.stdout)
                print("go %-47s %s" % (src.name, status))

    return 1 if failures else 0


if __name__ == "__main__":
    sys.exit(main())
