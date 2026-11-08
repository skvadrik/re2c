#!/usr/bin/env python3
"""Check AVX/SSE register hygiene on x86-64 Linux, without executing AVX instructions.

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

int lex_generic(Input *in) {
    /*!re2c
        re2c:api = generic;
        re2c:api:style = free-form;
        re2c:api:sigil = "@@";
        re2c:YYCTYPE = "unsigned char";
        re2c:YYPEEK = "*in->cur";
        re2c:YYPEEK16 = "_mm_loadu_si128((const __m128i *)in->cur)";
        re2c:YYPEEK32 = "_mm256_loadu_si256((const __m256i *)in->cur)";
        re2c:YYSKIP = "++in->cur;";
        re2c:YYBACKUP = "in->mar = in->cur;";
        re2c:YYRESTORE = "in->cur = in->mar;";
        re2c:YYSHIFT = "in->cur += @@;";
        re2c:YYLESSTHAN = "(size_t)(in->lim - in->cur) < (size_t)(@@)";
        re2c:YYFILL = "if (fill(in, @@)) return -1;";
        re2c:vectorize:loops = 1;
        [a-zA-Z_][a-zA-Z0-9_]* { return 1; }
        * { return 0; }
    */
}
'''


REG_ALIASES = {
    'rax': 'rax', 'eax': 'rax', 'ax': 'rax', 'al': 'rax', 'ah': 'rax',
    'rbx': 'rbx', 'ebx': 'rbx', 'bx': 'rbx', 'bl': 'rbx', 'bh': 'rbx',
    'rcx': 'rcx', 'ecx': 'rcx', 'cx': 'rcx', 'cl': 'rcx', 'ch': 'rcx',
    'rdx': 'rdx', 'edx': 'rdx', 'dx': 'rdx', 'dl': 'rdx', 'dh': 'rdx',
    'rsi': 'rsi', 'esi': 'rsi', 'si': 'rsi', 'sil': 'rsi',
    'rdi': 'rdi', 'edi': 'rdi', 'di': 'rdi', 'dil': 'rdi',
    'rbp': 'rbp', 'ebp': 'rbp', 'bp': 'rbp', 'bpl': 'rbp',
    'rsp': 'rsp', 'esp': 'rsp', 'sp': 'rsp', 'spl': 'rsp',
}
for _reg_idx in range(8, 16):
    for _reg_sfx in ('', 'd', 'w', 'b'):
        REG_ALIASES[f'r{_reg_idx}{_reg_sfx}'] = f'r{_reg_idx}'

CALLER_SAVED = ('rax', 'rcx', 'rdx', 'rsi', 'rdi', 'r8', 'r9', 'r10', 'r11')

GO_XMM_SIMD_RE = re.compile(
    r'\bv?(?:pcmpeqb|pcmpgtb|psubb|pmovmskb|movdqu|movou|pbroadcastb)\b[^\n]*\bX(?:[0-9]|1[0-5])\b',
    re.I,
)


def _split_att_operands(text):
    operands, current, depth = [], [], 0
    for ch in text:
        if ch == '(':
            depth += 1
            current.append(ch)
        elif ch == ')':
            depth = max(0, depth - 1)
            current.append(ch)
        elif ch == ',' and depth == 0:
            operands.append(''.join(current).strip())
            current = []
        else:
            current.append(ch)
    tail = ''.join(current).strip()
    if tail:
        operands.append(tail)
    return operands


def _canon_reg(operand):
    if operand.startswith('%'):
        return REG_ALIASES.get(operand[1:].lower())
    return None


def check_flow(assembly, name, go=False, expect_ymm=True):
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

    raw_tables = {}
    cur_table = None
    for raw_line in assembly.splitlines():
        stripped = raw_line.split('#', 1)[0].strip()
        if re.fullmatch(r'[.\w]+:', stripped):
            cur_table = stripped[:-1]
        elif cur_table is not None and re.match(r'\.(?:long|quad)\s', stripped):
            target_labels = [lbl for lbl in re.findall(r'\.L[\w.]+', stripped)
                             if lbl != cur_table and lbl in labels]
            if target_labels:
                raw_tables.setdefault(cur_table, set()).update(labels[lbl] for lbl in target_labels)
        elif stripped and (not stripped.startswith('.')
                           or stripped.startswith(('.section', '.text', '.data', '.bss', '.cfi_'))):
            cur_table = None
    tables_by_name = {tbl: frozenset(targets) for tbl, targets in raw_tables.items() if targets}
    table_targets = set().union(*tables_by_name.values()) if tables_by_name else set()
    if go:
        table_targets |= {labels[off] for off in re.findall(
            r'\brel\s+\d+\+\d+\s+t=R_ADDR\s+' + re.escape(name) + r'\+(\d+)\b', assembly)
            if off in labels}
    if not instructions:
        raise RuntimeError('empty function ' + name)
    pending = [(labels.get(name, 0), False, ())]
    visited, dirty_exits, exits = set(), set(), set()
    while pending:
        index, dirty, reg_state = pending.pop()
        if (index, dirty, reg_state) in visited:
            continue
        visited.add((index, dirty, reg_state))
        instruction = instructions[index]
        if instruction.startswith('notrack '):
            instruction = instruction[len('notrack '):].lstrip()
        parts = instruction.split(None, 1)
        op = parts[0]
        target = parts[1] if len(parts) > 1 else ''
        if op in ('vzeroupper', 'vzeroall'):
            dirty = False
        elif '%ymm' in instruction or (go and re.search(r'\bY\d+\b', instruction)):
            dirty = True

        reg_map = dict(reg_state)
        if not go and tables_by_name:
            ops = _split_att_operands(target)
            if op in ('leaq', 'lea') and len(ops) == 2:
                dst = _canon_reg(ops[1])
                if dst:
                    tbl_match = re.match(r'^\$?([.\w]+)(?:\(%rip\))?$', ops[0])
                    if tbl_match and tbl_match.group(1) in tables_by_name:
                        reg_map[dst] = tbl_match.group(1)
                    else:
                        reg_map.pop(dst, None)
            elif op in ('movq', 'mov') and len(ops) == 2:
                src, dst = _canon_reg(ops[0]), _canon_reg(ops[1])
                if dst:
                    if src and src in reg_map:
                        reg_map[dst] = reg_map[src]
                    else:
                        sym = ops[0].split('(', 1)[0].strip()
                        if sym in tables_by_name:
                            reg_map[dst] = sym
                        else:
                            reg_map.pop(dst, None)
            elif op in ('addq', 'add') and len(ops) == 2:
                src, dst = _canon_reg(ops[0]), _canon_reg(ops[1])
                if dst:
                    if src in reg_map and dst not in reg_map:
                        reg_map[dst] = reg_map[src]
                    elif src in reg_map and dst in reg_map and reg_map[src] != reg_map[dst]:
                        reg_map.pop(dst, None)
            elif op.startswith('call'):
                for reg in CALLER_SAVED:
                    reg_map.pop(reg, None)
            elif op in ('cltq', 'cdqe'):
                reg_map.pop('rax', None)
            elif op in ('cqto', 'cltd', 'cdq'):
                reg_map.pop('rdx', None)
            elif not op.startswith(('cmp', 'test', 'push', 'j', 'ret', 'nop', 'vzero', 'ud2', 'hlt', 'endbr')):
                if op.startswith('xchg') and len(ops) == 2:
                    for opnd in ops:
                        reg = _canon_reg(opnd)
                        if reg:
                            reg_map.pop(reg, None)
                elif ops:
                    dst = _canon_reg(ops[-1])
                    if dst:
                        reg_map.pop(dst, None)
        next_reg_state = tuple(sorted(reg_map.items()))

        jump = op.startswith('j')
        indirect = jump and (target.startswith('*') or (go and (re.fullmatch(r'[A-Z]+', target) or target.startswith('('))))
        tail = jump and target not in labels and not indirect
        noreturn = go and op == 'call' and any(x in target for x in (
            'runtime.panicBounds', 'runtime.panicIndex', 'runtime.panicSlice', 'runtime.morestack'))
        if (op.startswith(('call', 'ret')) and not noreturn) or tail:
            exits.add(index)
            if dirty:
                dirty_exits.add(index)
        if op.startswith('ret') or noreturn or op in ('ud2', 'hlt'):
            continue
        if indirect:
            resolved_targets = None
            if not go and tables_by_name:
                sym = target.lstrip('*').split('(', 1)[0].strip()
                if sym in tables_by_name:
                    resolved_targets = tables_by_name[sym]
                else:
                    jmp_regs = [REG_ALIASES[r.lower()] for r in re.findall(r'%([a-zA-Z0-9]+)', target)
                                if r.lower() in REG_ALIASES]
                    matched = {reg_map[r] for r in jmp_regs if r in reg_map}
                    if len(matched) == 1:
                        resolved_targets = tables_by_name[next(iter(matched))]
            destinations = resolved_targets if resolved_targets is not None else table_targets
            if not destinations:
                raise RuntimeError('unresolved indirect jump: ' + instruction)
            pending.extend((destination, dirty, next_reg_state) for destination in destinations)
        elif jump and not tail:
            pending.append((labels[target], dirty, next_reg_state))
        elif tail and (target.startswith('.L') or (go and target.isdigit())):
            raise RuntimeError('unresolved local branch: ' + instruction)
        if op not in ('jmp', 'jmpq'):
            if index + 1 == len(instructions):
                raise RuntimeError('unexpected fallthrough in ' + name)
            pending.append((index + 1, dirty, next_reg_state))

    ymm = sum(bool('%ymm' in instruction or (go and re.search(r'\bY\d+\b', instruction)))
              for instruction in instructions)
    xmm = sum(bool(GO_XMM_SIMD_RE.search(instruction) if go else ('%xmm' in instruction))
              for instruction in instructions)
    if not exits:
        raise RuntimeError('probe did not exercise exits')
    if expect_ymm and name != 'lex_all' and not ymm:
        raise RuntimeError('probe did not exercise YMM vector code in ' + name)
    if not expect_ymm:
        if ymm != 0:
            raise RuntimeError(f'width-16 probe unexpectedly touched YMM registers ({ymm}) in {name}')
        if name != 'lex_all' and not xmm:
            raise RuntimeError('width-16 probe did not exercise 128-bit vector code in ' + name)
    return [instructions[index] for index in sorted(dirty_exits)], len(exits), ymm


def report(assembly, name, description, go=False, expect_ymm=True):
    bad, exits, ymm = check_flow(assembly, name, go, expect_ymm=expect_ymm)
    print(f'{description} {name}: ymm={ymm}, exits={exits}, dirty={len(bad)}', flush=True)
    for instruction in bad:
        print('  ' + instruction, flush=True)
    if ymm:
        mutant = re.sub(r'\bvzero(?:upper|all)\b', 'nop', assembly, flags=re.I)
        if not check_flow(mutant, name, go, expect_ymm=expect_ymm)[0]:
            raise RuntimeError('negative control did not detect dirty exits: ' + description)
    return bool(bad)


def go_vector_functions(assembly):
    names = []
    for body in re.split(r'(?=^\S.* STEXT )', assembly, flags=re.M):
        if re.search(r'^\s*0x[0-9a-f]+\s+(\d+)\s+\([^\n]*?\)\s+\w+\s+[^\n]*\bY\d+\b',
                     body, re.M):
            match = re.search(r'\bTEXT\s+(.+?)\(SB\)', body)
            if not match:
                raise RuntimeError('Y registers outside a Go function')
            names.append(match.group(1))
    return names


def go_xmm_vector_functions(assembly):
    names = []
    for body in re.split(r'(?=^\S.* STEXT )', assembly, flags=re.M):
        if re.search(
            r'^\s*0x[0-9a-f]+\s+\d+\s+\([^\n]*?\)\s+V?(?:PCMPEQB|PCMPGTB|PSUBB|PMOVMSKB|MOVDQU|MOVOU|PBROADCASTB)\b[^\n]*\bX(?:[0-9]|1[0-5])\b',
            body,
            re.M | re.I,
        ):
            match = re.search(r'\bTEXT\s+(.+?)\(SB\)', body)
            if not match:
                raise RuntimeError('XMM SIMD registers outside a Go function')
            names.append(match.group(1))
    return names


def report_go(assembly, probe):
    names = go_vector_functions(assembly)
    if not names and probe != '004_simd_all_bytes':
        raise RuntimeError('no Go vector functions: ' + probe)
    print(f'{probe}: vector functions={len(names)}', flush=True)
    failed = False
    for name in names:
        failed |= report(assembly, name, probe, go=True)
    return failed


def generate_go(command, source, generated, options):
    header = source.open().readline()
    extra = [flag for flag in ('--loop-switch', '--recursive-functions', '-f', '--storable-state', '--eager-skip')
             if flag in header.split()]
    subprocess.run(command + extra + options + ['--lang', 'go', '--arch', 'x86', '--vectorize-loops', str(source),
                   '-o', str(generated)], check=True)


def compile_go(go, env, generated, binary):
    gomod = generated.parent / 'go.mod'
    if not gomod.exists():
        gomod.write_text('module avxprobe\n\ngo 1.27\n')
        (generated.parent / 'go.work').write_text('go 1.27\n\nuse .\n')
    result = subprocess.run([go, 'build', '-gcflags=-S', '-o', str(binary), str(generated)],
                            cwd=generated.parent, env=env, text=True, capture_output=True)
    binary.with_suffix('.s').write_text(result.stderr)
    result.check_returncode()
    return result.stderr


def check_shipped_cleanup_mutant(command, go, env, directory, root):
    mutant_syntax = directory / 'go_no_cleanup'
    mutant_syntax.write_text('code:vec32_cleanup = "";\n')
    source = root / 'test/codegen/go/004_simd.re'
    probe = '004_simd_cleanup_mutant'
    generated = directory / (probe + '.go')
    generate_go(command, source, generated,
                ['--vectorize-size', '32', '--syntax', mutant_syntax.name, '-I', str(directory)])
    text = generated.read_text()
    if 'archsimd.ClearAVXUpperBits()' in text:
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

    multi_table = '''multi_table:
    leaq .LJTI0_0(%rip), %rcx
    movslq (%rcx,%rax,4), %rax
    addq %rcx, %rax
    jmpq *%rax
.Lpre_fill:
    callq fill@PLT
    ret
.Lvec:
    vxorps %ymm0, %ymm0, %ymm0
    leaq .LJTI0_1(%rip), %rcx
    movslq (%rcx,%rax,4), %rax
    addq %rcx, %rax
    jmpq *%rax
.Lpost_clean:
    vzeroupper
    callq token@PLT
    ret
    .cfi_endproc
    .section .rodata,"a",@progbits
.LJTI0_0:
    .long .Lpre_fill-.LJTI0_0
    .long .Lvec-.LJTI0_0
.LJTI0_1:
    .long .Lpost_clean-.LJTI0_1
'''
    if check_flow(multi_table, 'multi_table')[0]:
        raise RuntimeError('per-table indirect jump positive control failed')
    dirty_call_ret = multi_table.replace('    vzeroupper\n', '')
    if set(check_flow(dirty_call_ret, 'multi_table')[0]) != {'callq token@PLT', 'ret'}:
        raise RuntimeError('per-table indirect jump dirty call/ret control failed')
    dirty_tail = multi_table.replace('    vzeroupper\n    callq token@PLT\n    ret', '    jmp tail_target')
    if set(check_flow(dirty_tail, 'multi_table')[0]) != {'jmp tail_target'}:
        raise RuntimeError('per-table indirect jump dirty tail-call control failed')

    scalar_c = '''w16_probe:\n    movl %edi, %eax\n    ret\n    .cfi_endproc\n'''
    try:
        check_flow(scalar_c, 'w16_probe', expect_ymm=False)
        raise RuntimeError('scalar C fallback was not rejected in width-16 mode')
    except RuntimeError as exc:
        if '128-bit vector code' not in str(exc):
            raise
    xmm_c = '''w16_probe:\n    pcmpeqb %xmm0, %xmm1\n    ret\n    .cfi_endproc\n'''
    if check_flow(xmm_c, 'w16_probe', expect_ymm=False)[0]:
        raise RuntimeError('valid XMM C probe failed in width-16 mode')

    go_scalar_zero_only = (
        'main.w16 STEXT nosplit size=16\n'
        '\t0x0000 00000 (x.go:1)\tTEXT\tmain.w16(SB), NOSPLIT|ABIInternal, $0-0\n'
        '\t0x0000 00000 (x.go:2)\tMOVUPS\tX15, (SP)\n'
        '\t0x0005 00005 (x.go:3)\tRET\n'
    )
    if go_xmm_vector_functions(go_scalar_zero_only):
        raise RuntimeError('Go zero-register MOVUPS X15 falsely matched as SIMD')
    try:
        check_flow(go_scalar_zero_only, 'main.w16', go=True, expect_ymm=False)
        raise RuntimeError('Go scalar fallback was not rejected in width-16 mode')
    except RuntimeError as exc:
        if '128-bit vector code' not in str(exc):
            raise
    go_simd_w16 = go_scalar_zero_only.replace('MOVUPS\tX15, (SP)', 'VPCMPEQB\tX0, X1, X2')
    if go_xmm_vector_functions(go_simd_w16) != ['main.w16']:
        raise RuntimeError('Go width-16 SIMD function was not detected')
    if check_flow(go_simd_w16, 'main.w16', go=True, expect_ymm=False)[0]:
        raise RuntimeError('valid Go width-16 SIMD probe failed')


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
        directory = (args.output_dir or Path(temporary)).resolve()
        directory.mkdir(parents=True, exist_ok=True)
        root = Path(__file__).resolve().parents[3]
        source = directory / 'probe.re'
        source.write_text(SOURCE)
        command = [str(args.re2c.resolve()), '--no-generation-date', '-i', '-Wno-unreachable-rules']
        failed = False
        if args.language in ('all', 'c'):
            options = [] if args.syntax is None else ['--syntax', args.syntax.name, '-I', str(args.syntax.resolve().parent)]
            for vec_size in (16, 32):
                for model_tag, model_flags in [('', []), ('-loop-switch', ['--loop-switch']), ('-eager-skip', ['--eager-skip'])]:
                    vname = f'w{vec_size}{model_tag}'
                    generated = directory / (vname + '.c')
                    subprocess.run(command + ['--arch', 'x86', '--vectorize-size', str(vec_size)]
                                   + model_flags + options + [str(source), '-o', str(generated)], check=True)
                    gen_text = generated.read_text()
                    if '_mm256_zeroupper' in gen_text or 'volatile' in gen_text:
                        raise RuntimeError('C generated output must not contain explicit _mm256_zeroupper or volatile')
                    for number, compiler in enumerate(args.cc or ['gcc', 'clang']):
                        levels = (
                            [('O2', ['-O2', '-mavx2']), ('O0-vzu', ['-O0', '-mavx2', '-mvzeroupper']), ('O1-vzu', ['-O1', '-mavx2', '-mvzeroupper'])]
                            if vec_size == 32
                            else [('O2', ['-O2', '-msse2']), ('O0', ['-O0', '-msse2'])]
                        )
                        for ltag, cflags in levels:
                            output = directory / f'{vname}-compiler{number}-{ltag}.s'
                            subprocess.run([compiler] + cflags + ['-S', str(generated), '-o', str(output)], check=True)
                            assembly = output.read_text()
                            for name in ['lex_tokens', 'lex_all', 'lex_generic']:
                                failed |= report(assembly, name, f'{vname} {compiler} {ltag}', expect_ymm=(vec_size == 32))
        if args.language in ('all', 'go'):
            env = dict(os.environ, GOEXPERIMENT='simd', GOARCH='amd64', GOOS='linux')
            env.pop('GOWORK', None)
            probes = sorted((root / 'test/codegen/go').glob('004_simd*.re'))
            if not probes:
                raise RuntimeError('no Go vector probes')
            for source_re in probes:
                probe = source_re.stem
                syntax = source_re.with_suffix('.inc')
                options = ['--syntax', syntax.name, '-I', str(syntax.parent)] if syntax.exists() else []
                generated = directory / (probe + '.go')
                generate_go(command, source_re, generated, options)
                failed |= report_go(compile_go(args.go, env, generated, directory / probe), probe)
            # Width 16 in Go: zero YMM registers, zero ClearAVXUpperBits, positive 128-bit XMM SIMD
            w16_go = directory / '004_simd_w16_probe.go'
            generate_go(command, root / 'test/codegen/go/004_simd.re', w16_go, ['--vectorize-size', '16'])
            if 'ClearAVXUpperBits' in w16_go.read_text():
                raise RuntimeError('Go width 16 must not emit ClearAVXUpperBits')
            w16_asm = compile_go(args.go, env, w16_go, directory / '004_simd_w16_probe')
            if go_vector_functions(w16_asm):
                raise RuntimeError('Go width 16 unexpectedly used YMM registers')
            w16_names = go_xmm_vector_functions(w16_asm)
            if not w16_names:
                raise RuntimeError('Go width 16 did not emit 128-bit XMM SIMD functions')
            for name in w16_names:
                failed |= report(w16_asm, name, '004_simd_w16_probe', go=True, expect_ymm=False)
            check_shipped_cleanup_mutant(command, args.go, env, directory, root)
        return int(failed)


if __name__ == '__main__':
    raise SystemExit(main())
