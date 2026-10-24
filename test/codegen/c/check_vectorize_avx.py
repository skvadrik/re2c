#!/usr/bin/env python3
"""Check AVX cleanup on x86-64 Linux, without executing AVX instructions.

Usage: python3 test/codegen/c/check_vectorize_avx.py /path/to/re2c
See test/codegen/README.vectorize-avx.md for prerequisites and the CMake test target.
Like re2c, this test is in the public domain.
"""

import argparse
import os
from pathlib import Path
import re
import subprocess
import tempfile


# An outer token loop lets GCC hoist constant broadcasts past both the vector
# entry guard and YYFILL. The classes cover singleton and multi-byte exits,
# multiple complement ranges, high bytes, and scalar fallback with lookahead.
SOURCE = r'''
#include <stddef.h>
#include <immintrin.h>
typedef struct { unsigned char *cur, *lim, *mar; } Input;
extern int fill(Input *, size_t);
extern int token(Input *, int);

int lex_tokens(Input *in) {
    for (;;) {
        int kind;
        /*!re2c
            re2c:api:style = free-form;
            re2c:YYCTYPE = "unsigned char";
            re2c:YYCURSOR = in->cur;
            re2c:YYLIMIT = in->lim;
            re2c:YYMARKER = in->mar;
            re2c:YYFILL = "if (fill(in, @@)) return -1;";
            re2c:vectorize:loops = 1;
            ["] ([^"\\\x00\n] | [\\][^\x00\n])* ["] { kind = 1; goto next; }
            [a-zA-Z_][a-zA-Z0-9_]* { kind = 2; goto next; }
            [ \t\r\n]+ { kind = 3; goto next; }
            "//" [^\n\x00]* { kind = 4; goto next; }
            [\x80-\xff]+ { kind = 5; goto next; }
            "#" [\x01-\x7e\xa0-\xbf]* { kind = 6; goto next; }
            "@" [\x01-\xff]* "!!" { kind = 7; goto next; }
            [0-9]+ ("." [0-9]+)? { kind = 8; goto next; }
            "'" [^']* "'" { kind = 9; goto next; }
            * { return 0; }
        */
    next:
        if (token(in, kind)) return kind;
    }
}

int lex_all(Input *in) {
    /*!re2c
        [^]+ { return 0; }
    */
}
'''


def check_flow(assembly, name, go=False):
    """Conservatively propagate dirty YMM state to calls, tail calls and returns."""
    instructions, labels = [], {}
    if go:
        marker = 'TEXT\t' + name + '(SB)'
        if marker not in assembly:
            raise RuntimeError('missing function ' + name)
        body = assembly.split(marker, 1)[1]
        body = re.split(r'\n\S.* STEXT ', body, maxsplit=1)[0]
        for line in body.splitlines():
            match = re.match(r'\s*0x[0-9a-f]+\s+(\d+)\s+\([^\n]*?\)\s+(\w+)\s*(.*)', line)
            if match:
                address, op, args = match.groups()
                if op not in ('FUNCDATA', 'PCDATA'):
                    labels.setdefault(str(int(address)), len(instructions))
                    instructions.append(op.lower() + ' ' + args)
        body = ''
    else:
        # Include outlined cold blocks, but not neighbouring functions or data.
        bodies = re.findall(r'^(' + re.escape(name) + r'(?:\.cold(?:\.\d+)?)?:[^\n]*\n.*?)\.cfi_endproc',
                            assembly, re.M | re.S)
        if not bodies:
            raise RuntimeError('missing function ' + name)
        body = '\n'.join(bodies)
    for line in body.splitlines():
        line = line.split('#', 1)[0].strip()
        if re.fullmatch(r'[.\w]+:', line):
            labels[line[:-1]] = len(instructions)
        elif line and not line.startswith('.'):
            instructions.append(line)

    # All local code labels referenced by table entries are conservative successors.
    table_targets = {labels[label] for line in assembly.splitlines()
                     if re.match(r'\s*\.(?:long|quad)\s', line)
                     for label in re.findall(r'\.L[\w.]+', line) if label in labels}
    if not instructions:
        raise RuntimeError('empty function ' + name)
    pending = [(labels.get(name, 0), False)]
    visited, dirty_exits, exits = set(), set(), set()
    while pending:
        index, dirty = pending.pop()
        if (index, dirty) in visited:
            continue
        visited.add((index, dirty))
        instruction = instructions[index]
        parts = instruction.split(None, 1)
        op = parts[0]
        target = parts[1] if len(parts) > 1 else ''
        if op in ('vzeroupper', 'vzeroall'):
            dirty = False
        elif '%ymm' in instruction or (go and re.search(r'\bY\d+\b', instruction)):
            dirty = True

        jump = op.startswith('j')
        indirect = jump and (target.startswith('*') or (go and re.fullmatch(r'[A-Z]+', target)))
        tail = jump and target not in labels and not indirect
        # These paths cannot return to user code; malformed-buffer panics are
        # outside the cleanup guarantee, as is the stack-growth restart path.
        noreturn = go and op == 'call' and any(x in target for x in (
            'runtime.panicBounds', 'runtime.panicIndex', 'runtime.panicSlice', 'runtime.morestack'))
        if (op.startswith(('call', 'ret')) and not noreturn) or tail:
            exits.add(index)
            if dirty:
                dirty_exits.add(index)
        if op.startswith('ret') or noreturn or op in ('ud2', 'hlt'):
            continue
        if indirect:
            if not table_targets:
                raise RuntimeError('unresolved indirect jump: ' + instruction)
            pending.extend((destination, dirty) for destination in table_targets)
        elif jump and not tail:
            pending.append((labels[target], dirty))
        elif tail and (target.startswith('.L') or (go and target.isdigit())):
            raise RuntimeError('unresolved local branch: ' + instruction)
        if op not in ('jmp', 'jmpq'):
            if index + 1 == len(instructions):
                raise RuntimeError('unexpected fallthrough in ' + name)
            pending.append((index + 1, dirty))

    ymm = sum(bool('%ymm' in instruction or (go and re.search(r'\bY\d+\b', instruction)))
              for instruction in instructions)
    if not exits or (name != 'lex_all' and not ymm):
        raise RuntimeError('probe did not exercise vector code and exits')
    return [instructions[index] for index in sorted(dirty_exits)], len(exits), ymm


def report(assembly, name, description, go=False):
    bad, exits, ymm = check_flow(assembly, name, go)
    print(f'{description} {name}: ymm={ymm}, exits={exits}, dirty={len(bad)}', flush=True)
    for instruction in bad:
        print('  ' + instruction, flush=True)
    if ymm:
        mutant = re.sub(r'\bvzero(?:upper|all)\b', 'nop', assembly, flags=re.I)
        if not check_flow(mutant, name, go)[0]:
            raise RuntimeError('negative control did not detect dirty exits: ' + description)
    return bool(bad)


def go_vector_functions(assembly):
    names = []
    for body in re.split(r'(?=^\S.* STEXT )', assembly, flags=re.M):
        if re.search(r'^\s*0x[0-9a-f]+\s+\d+\s+\([^\n]*?\)\s+\w+\s+[^\n]*\bY\d+\b',
                     body, re.M):
            match = re.search(r'\bTEXT\s+(.+?)\(SB\)', body)
            if not match:
                raise RuntimeError('Y registers outside a Go function')
            names.append(match.group(1))
    return names


def report_go(assembly, probe):
    names = go_vector_functions(assembly)
    # The all-byte class only advances the cursor; it needs no vector operands.
    if not names and probe != '004_simd_all_bytes':
        raise RuntimeError('no Go vector functions: ' + probe)
    print(f'{probe}: vector functions={len(names)}', flush=True)
    failed = False
    for name in names:
        failed |= report(assembly, name, probe, go=True)
    return failed


def replaces_vector_loop(path):
    if not path.is_file():
        return False
    return re.search(r'(?m)^code:vector_loop\s*=', path.read_text()) is not None


def generate_go(command, source, generated, options):
    subprocess.run(command + options + ['--lang', 'go', '--vectorize-loops', str(source),
                   '-o', str(generated)], check=True)


def compile_go(go, env, generated, binary):
    result = subprocess.run([go, 'build', '-gcflags=-S', '-o', str(binary), str(generated)],
                            env=env, text=True, capture_output=True)
    binary.with_suffix('.s').write_text(result.stderr)
    result.check_returncode()
    return result.stderr


def check_shipped_go(command, go, env, directory, source):
    probe = source.stem + '_shipped'
    generated = directory / (probe + '.go')
    generate_go(command, source, generated, [])
    text = generated.read_text()
    if 'archsimd.ClearAVXUpperBits()' not in text or 'yyn & 16' not in text:
        raise RuntimeError('shipped Go template was not used: ' + probe)
    return report_go(compile_go(go, env, generated, directory / probe), probe)


def check_shipped_cleanup_mutant(command, go, env, directory, root):
    shipped = (root / 'include/syntax/go').read_text()
    needle = '    topindent "archsimd.ClearAVXUpperBits()" nl\n'
    if shipped.count(needle) != 1:
        raise RuntimeError('shipped Go template cleanup site changed')
    mutant_syntax = directory / 'go_no_cleanup'
    mutant_syntax.write_text(shipped.replace(needle, '', 1))
    source = root / 'test/codegen/go/004_simd_xrange.re'
    if not source.is_file():
        raise RuntimeError('missing complement-range probe')
    probe = '004_simd_xrange_shipped_mutant'
    generated = directory / (probe + '.go')
    generate_go(command, source, generated,
                ['--syntax', mutant_syntax.name, '-I', str(directory)])
    text = generated.read_text()
    if 'archsimd.ClearAVXUpperBits()' in text or 'yyn & 16' not in text:
        raise RuntimeError('shipped-template cleanup mutant was not generated')
    if not report_go(compile_go(go, env, generated, directory / probe), probe):
        raise RuntimeError('shipped-template cleanup mutant was not detected')
    print('shipped-template cleanup mutant: detected', flush=True)


def check_analyzer():
    assembly = '''probe:
    vxorps %ymm0, %ymm0, %ymm0
    je probe.cold
    jne external
    jmpq *%rax
    .cfi_endproc
probe.cold:
    call cold_callback
    ret
.Lcase:
    call table_callback
    ret
    .cfi_endproc
.Ltable:
    .long .Lcase-.Ltable
'''
    bad = check_flow(assembly, 'probe')[0]
    if set(bad) != {'call cold_callback', 'call table_callback', 'ret', 'jne external'}:
        raise RuntimeError('cold/table/conditional-branch negative control failed')
    clean = assembly.replace('je probe.cold', 'vzeroupper\n    je probe.cold')
    if check_flow(clean, 'probe')[0]:
        raise RuntimeError('cold/table/conditional-branch positive control failed')
    try:
        check_flow(assembly.replace('.long .Lcase-.Ltable', ''), 'probe')
    except RuntimeError as error:
        if 'unresolved indirect jump' not in str(error):
            raise
    else:
        raise RuntimeError('unresolved table was silently accepted')
    assembly = '''TEXT\tmain.probe(SB), ABIInternal, $0-0
    0x0000 00000 (probe.go:1) JMP 10
    0x0005 00005 (probe.go:2) CALL runtime.stringtoslicebyte(SB)
    0x000a 00010 (probe.go:3) VMOVDQU (AX), Y0
    0x000f 00015 (probe.go:4) JNE 5
    0x0014 00020 (probe.go:5) VZEROUPPER
    0x0017 00023 (probe.go:6) RET
'''
    if check_flow(assembly, 'main.probe', go=True)[0] != ['call runtime.stringtoslicebyte(SB)']:
        raise RuntimeError('Go backedge/call negative control failed')
    clean = assembly.replace('JNE 5', 'VZEROUPPER\n    0x0012 00018 (probe.go:4) JNE 5')
    if check_flow(clean, 'main.probe', go=True)[0]:
        raise RuntimeError('Go backedge/call positive control failed')
    scalar = '''main.scalar STEXT size=1
    0x0000 00000 (probe.go:1) TEXT\tmain.scalar(SB), ABIInternal, $0-0
    0x0000 00000 (probe.go:1) RET
'''
    first = 'main.probe STEXT size=24\n' + clean
    extra = 'other.extra STEXT size=24\n' + assembly.replace('main.probe', 'other.extra')
    combined = first + scalar + extra
    if go_vector_functions(combined) != ['main.probe', 'other.extra']:
        raise RuntimeError('Go extra-function discovery failed')
    if not report_go(combined, 'synthetic'):
        raise RuntimeError('Go extra-function dirty exit was silently accepted')
    if report_go(first + scalar, 'synthetic'):
        raise RuntimeError('Go function boundary positive control failed')
    if go_vector_functions(scalar):
        raise RuntimeError('Go scalar function was classified as vector code')
    for probe in ['synthetic', '004_simd_xrange']:
        try:
            report_go(scalar, probe)
        except RuntimeError as error:
            if 'no Go vector functions' not in str(error):
                raise
        else:
            raise RuntimeError('empty Go vector coverage was silently accepted')
    if report_go(scalar, '004_simd_all_bytes'):
        raise RuntimeError('Go all-byte positive control failed')
    if not report_go(extra, '004_simd_all_bytes'):
        raise RuntimeError('Go all-byte extra function was silently accepted')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('re2c', type=Path)
    parser.add_argument('--syntax', type=Path)
    parser.add_argument('--cc', action='append', help='compiler (default: gcc and clang)')
    parser.add_argument('--go', default='go', help='Go 1.27+ executable')
    parser.add_argument('--language', choices=['all', 'c', 'go'], default='all')
    parser.add_argument('--output-dir', type=Path)
    args = parser.parse_args()
    check_analyzer()
    with tempfile.TemporaryDirectory(prefix='re2c-avx-') as temporary:
        directory = args.output_dir or Path(temporary)
        directory.mkdir(parents=True, exist_ok=True)
        directory = directory.resolve()
        root = Path(__file__).resolve().parents[3]
        source = directory / 'probe.re'
        source.write_text(SOURCE)
        command = [str(args.re2c.resolve()), '--no-generation-date', '-i',
                   '-Wno-unreachable-rules']
        failed = False
        if args.language in ('all', 'c'):
            for variant, syntax in [('default', args.syntax),
                                    ('fixed', root / 'benchmarks/c/src/re2c/vec_fixed.syntax')]:
                options = [] if syntax is None else ['--syntax', syntax.name, '-I', str(syntax.resolve().parent)]
                generated = directory / (variant + '.c')
                subprocess.run(command + options + [str(source), '-o', str(generated)], check=True)
                for number, compiler in enumerate(args.cc or ['gcc', 'clang']):
                    for level in ['O0', 'O1', 'O2', 'Os']:
                        output = directory / f'{variant}-compiler{number}-{level}.s'
                        subprocess.run([compiler, '-' + level, '-mavx2',
                                        '-S', str(generated), '-o', str(output)], check=True)
                        assembly = output.read_text()
                        for name in ['lex_tokens', 'lex_all']:
                            failed |= report(assembly, name, f'{variant} {compiler} -{level}')
        if args.language in ('all', 'go'):
            env = dict(os.environ, GOEXPERIMENT='simd', GOARCH='amd64', GOOS='linux', GOWORK='off')
            probes = sorted((root / 'test/codegen/go').glob('004_simd*.re'))
            if not probes:
                raise RuntimeError('no Go vector probes')
            print(f'Go probes={len(probes)}', flush=True)
            overrides = []
            for source in probes:
                probe = source.stem
                syntax = source.with_suffix('.inc')
                options = ['--syntax', syntax.name, '-I', str(syntax.parent)] if syntax.exists() else []
                if replaces_vector_loop(syntax):
                    overrides.append(source)
                generated = directory / (probe + '.go')
                generate_go(command, source, generated, options)
                failed |= report_go(compile_go(args.go, env, generated, directory / probe), probe)
            if not any(path.name == '004_simd_xrange.re' for path in overrides):
                raise RuntimeError('complement-range probe is not checked with the shipped template')
            print(f'Go shipped-template probes={len(overrides)}', flush=True)
            for source in overrides:
                failed |= check_shipped_go(command, args.go, env, directory, source)
            check_shipped_cleanup_mutant(command, args.go, env, directory, root)
        return int(failed)


if __name__ == '__main__':
    raise SystemExit(main())
