#!/usr/bin/env python3

"""
Code generation probes, meant to be run before a release (they are too slow
for the regular test suite). There are four independent probes:

owners
    For every backend, derive a syntax file from include/syntax/<lang> in
    which every line emitted by a `code:*` template is tagged with an owner
    comment, then run re2c with that syntax file on every test in test/ and
    examples/. Any control flow construct, `yych` access or cursor move found
    on an untagged line of generated code is reported: it means that the
    construct was emitted bypassing the code templates. Only the main output
    file is analyzed, not the header files written with --header or -t.

templates
    In every include/syntax/<lang>, a `code:*` template whose text contains
    a control flow construct, a `yych` access or a cursor move must be one of
    the structural templates in STRUCTURAL_TEMPLATES. This catches the case
    that the owners probe cannot see: a new template that owns a construct
    (such as a monolithic loop) that should be built from the structural
    templates.

opaque
    Generate a few reference lexers with `--api generic` for C (and for Go if
    it is installed) and compile them against an opaque state, so that none
    of YYCURSOR, YYLIMIT, YYMARKER, YYCTXMARKER and YYINPUT is in scope: only
    the generic API primitives (YYPEEK, YYSKIP, YYBACKUP, ...) are defined.

registry
    Check that every CODE_TEMPLATE declared in src/options/opt.h is used in
    src/, that every `case CodeKind::X:` renders the template named after X
    (or one listed for X in REGISTRY_KIND_ALIASES or REGISTRY_KIND_FAMILIES),
    and that the render switch has a case for every CodeKind value. The
    probe fails if it reads too few templates or render cases.

Exit status: 0 if all selected probes pass, 1 if a probe fails, 2 on usage
error or a missing program.
"""

import argparse
import concurrent.futures
import os
import re
import shutil
import subprocess
import sys
import tempfile
import textwrap


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# Test header prefix, file extension and language (the same as in
# run_tests.py.in).
HEADERS = [
    ('// re2c',             'c',     'c'),
    ('// re2d',             'd',     'd'),
    ('//go:generate re2go', 'go',    'go'),
    ('-- re2hs',            'hs',    'haskell'),
    ('// re2java',          'java',  'java'),
    ('// re2js',            'js',    'js'),
    ('(* re2ocaml',         'ml',    'ocaml'),
    ('# re2py',             'py',    'python'),
    ('// re2rust',          'rs',    'rust'),
    ('// re2swift',         'swift', 'swift'),
    ('// re2v',             'v',     'v'),
    ('// re2zig',           'zig',   'zig'),
]

ALIASES = [
    ('re2d',     're2c --lang d'),
    ('re2go',    're2c --lang go'),
    ('re2hs',    're2c --lang haskell'),
    ('re2java',  're2c --lang java'),
    ('re2js',    're2c --lang js'),
    ('re2ocaml', 're2c --lang ocaml'),
    ('re2py',    're2c --lang python'),
    ('re2rust',  're2c --lang rust'),
    ('re2swift', 're2c --lang swift'),
    ('re2v',     're2c --lang v'),
    ('re2zig',   're2c --lang zig'),
]

RE2C_PATTERN = re.compile(r'.*re2c[ ]*([ a-zA-Z0-9_./$-]+).*$')


# Exception lists -------------------------------------------------------------
#
# All of them are disabled by --no-allowlists. An entry that no longer
# applies makes the probe fail, so that it gets removed.

# Templates that are declared in src/options/opt.h but have no caller in src/.
# This list only exempts the missing caller; it never exempts a render case
# that calls the wrong template (see REGISTRY_KNOWN_MISMATCHES).
REGISTRY_ALLOWLIST = {
    # Released syntax configurations that must stay supported for backwards
    # compatibility, even though re2c never renders them.
    'var_global': 'released configuration, kept for compatibility',
    'const_local': 'released configuration, kept for compatibility',
    # No code generator emits CodeKind::SHIFTMTAG yet.
    'yyshiftmtag': 'no generator emits CodeKind::SHIFTMTAG',
}

# Render cases known to call a template not named after their kind: a pair
# of (CodeKind value, called template) and the reason. The pair must match
# exactly; any other mismatch in the same case is a failure.
REGISTRY_KNOWN_MISMATCHES = {
    ('SHIFTMTAG', 'yyshiftstag'): 'copy-paste bug, the case should call '
        'render_code_yyshiftmtag',
}

# Render cases that call a template whose name is not the name of their
# kind (names are compared after dropping the `yy` prefixes, so SKIP_PEEK
# matches yyskip_yypeek). Any other call must match exactly. These tables
# are not exceptions: they are applied even with --no-allowlists, which
# lists them, and an entry that no render case uses makes the probe fail.
# The conditions quoted below are those of the render switch in
# src/codegen/pass4_render.cc.

# Naming aliases: the template is named differently from the kind.
REGISTRY_KIND_ALIASES = {
    # Under `if (code->fncall.tailcall)`: a tail call renders code:tailcall,
    # the `else` branch renders code:fncall.
    'FNCALL': {'tailcall'},
    # The only call of `case CodeKind::REC_FUNCS`: REC_FUNCS is short for
    # code:recursive_functions.
    'REC_FUNCS': {'recursive_functions'},
}

# Template families: the case renders one of several variants of its
# template, selected by an option or by the code model.
REGISTRY_KIND_FAMILIES = {
    # Under `if (oneline)`: the one-line variant.
    'IF_THEN_ELSE': {'if_then_else_oneline'},
    # The only call of `case CodeKind::LINE_INFO_INPUT` and of `case
    # CodeKind::LINE_INFO_OUTPUT`: both line directives share code:line_info.
    'LINE_INFO_INPUT': {'line_info'},
    'LINE_INFO_OUTPUT': {'line_info'},
    # The only call of `case CodeKind::VAR`: variables are always local
    # (code:var_global has no caller).
    'VAR': {'var_local'},
    # The only call of `case CodeKind::CONST`: constants are always global
    # (code:const_local has no caller).
    'CONST': {'const_global'},
    # Under `if (rctx.opts->code_model == CodeModel::REC_FUNC)`: global
    # arrays (shared by the functions), the `else` branch local arrays.
    'ARRAY': {'array_global', 'array_local'},
}

# Lower bounds on what the registry probe reads from the sources (76
# templates and 45 render cases at the time of writing): fewer means that
# the sources were not parsed correctly, not that they are consistent.
REGISTRY_MIN_TEMPLATES = 50
REGISTRY_MIN_CASES = 30

# Opaque cases that are known not to compile, independently of the API (they
# fail the same way with the default API). An entry is accepted only if the
# compiler output mentions none of the state identifiers in
# OPAQUE_STATE_NAMES, and every error reported by the compiler matches one of
# the expected diagnostics: a pair of a message and the generated line that
# the error points to. Every expected diagnostic must occur.
OPAQUE_KNOWN_FAILURES = {
    # The bitmap array is emitted after the functions that use it (GCC and
    # Clang messages).
    ('c', 'recursive-functions', '-b'): {
        'reason': '`yybm` is defined after its uses',
        'diagnostics': [
            (r"^'yybm' undeclared \(first use in this function\)$"
                r"|^use of undeclared identifier 'yybm'$", r'\byybm\['),
        ],
    },
    # `code:array_global` lacks the array type: `var yybm = {`; the second
    # error is the closing brace of the array.
    ('go', 'recursive-functions', '-b'): {
        'reason': '`code:array_global` has no type',
        'diagnostics': [
            (r'^syntax error: unexpected \{, expected expression$',
                r'^var yybm = \{$'),
            (r'^syntax error: unexpected \} after top level declaration$',
                r'^\}$'),
        ],
    },
}

OPAQUE_STATE_NAMES = ['YYCURSOR', 'YYLIMIT', 'YYMARKER', 'YYCTXMARKER',
    'YYINPUT']

# Categories of constructs reported by the owners and templates probes.
CONTROL = 'control flow'
YYCH = 'yych access'
CURSOR = 'cursor move'

# Templates that legitimately own control flow, `yych` accesses or cursor
# moves (the template probe reports any other template that has them), with
# the categories of constructs that each of them may emit: a category
# emitted outside of this set is a failure, and so is a category that the
# template emits in no syntax file. The variables a template may use are
# declared in src/options/opt.h (CHAR is `yych`, CURSOR is `YYCURSOR`,
# COND/BRANCH/CASE/STMT/LABEL are the parts of a control flow construct).
STRUCTURAL_TEMPLATES = {
    # Conditional statements (variables COND, BRANCH, STMT).
    'if_then_else': ({CONTROL}, 'if/else (when/then/else in Haskell, OCaml)'),
    'if_then_else_oneline': ({CONTROL}, 'one-line if/else'),
    # Multi-way branches (variables EXPR, CASE, STMT, VAL).
    'switch': ({CONTROL},
        'switch, match ... with (OCaml), case ... of (Haskell)'),
    'switch_cases': ({CONTROL},
        'case arms: `| ... ->`, `=>`, `fallthrough`, `case`'),
    'switch_cases_oneline': ({CONTROL}, 'one-line case arms'),
    'switch_case_range': ({CONTROL}, '`case` labels'),
    'switch_case_default': ({CONTROL}, 'default arm, `else` in V and Zig'),
    # Loops and jumps (variables LABEL, STMT).
    'loop': ({CONTROL}, 'for/while/loop, labeled switch loop in Zig'),
    'continue': ({CONTROL}, 'continue'),
    'goto': ({CONTROL}, 'goto'),
    'cgoto': ({CONTROL}, 'computed goto'),
    # Function definitions: only Haskell type signatures, which use `->`
    # (variables ARGTYPE, TYPE).
    'fndef': ({CONTROL}, '`->` in Haskell type signatures'),
    # Debug hook (variable CHAR).
    'yydebug': ({YYCH}, 'passes `yych` to YYDEBUG'),
    # Input primitives (variables CHAR, CURSOR, MARKER, CTXMARKER, TAG). A
    # read through the cursor (`yych = *YYCURSOR`) is not a cursor move.
    'yypeek': ({YYCH}, 'reads `yych`'),
    'yyskip': ({CURSOR}, 'advances the cursor'),
    'yyskip_yypeek': ({CURSOR, YYCH}, 'advances the cursor, reads `yych`'),
    'yypeek_yyskip': ({CURSOR, YYCH}, 'reads `yych`, advances the cursor'),
    'yyskip_yybackup': ({CURSOR}, 'advances the cursor'),
    'yybackup_yyskip': ({CURSOR}, 'advances the cursor'),
    'yybackup_yypeek': ({YYCH}, 'reads `yych`'),
    'yyskip_yybackup_yypeek': ({CURSOR, YYCH},
        'advances the cursor, reads `yych`'),
    'yybackup_yypeek_yyskip': ({CURSOR, YYCH},
        'reads `yych`, advances the cursor'),
    'yyrestore': ({CURSOR}, 'moves the cursor back to the marker'),
    'yyrestorectx': ({CURSOR}, 'moves the cursor back to the context marker'),
    'yyrestoretag': ({CURSOR}, 'moves the cursor to a tag'),
    'yyshift': ({CURSOR}, 'shifts the cursor'),
    # Tag shift: `if` guards the negative tag value (variable NEG); the tag
    # is shifted, not the cursor.
    'yyshiftstag': ({CONTROL}, 'conditional shift of an s-tag'),
    # Bitmap and computed goto checks (variable CHAR).
    'yybm_filter': ({YYCH}, 'tests `yych`'),
    'yybm_match': ({YYCH}, 'indexes the bitmap with `yych`'),
    'yytarget_filter': ({YYCH}, 'tests `yych`'),
}


def log(*args):
    print(*args, flush=True)


def run(args, cwd=None, timeout=300, env=None):
    try:
        p = subprocess.run(args, cwd=cwd, env=env, timeout=timeout,
            stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        return p.returncode, p.stdout.decode('utf-8', 'replace')
    except subprocess.TimeoutExpired:
        return -1, 'timeout after %d seconds' % timeout


def truncated(text, limit=20, prefix='    '):
    """Indent the first `limit` lines of a program output."""
    lines = text.rstrip().split('\n') if text.strip() else []
    res = lines[:limit]
    if len(lines) > limit:
        res.append('[%d more lines]' % (len(lines) - limit))
    res.append('[%d lines in total]' % len(lines))
    return textwrap.indent('\n'.join(res), prefix)


# Syntax files ----------------------------------------------------------------

STX_TOKEN = re.compile(r'''
    (?P<comment>//[^\n]*)
  | (?P<space>\s+)
  | (?P<string>"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*')
  | (?P<word>[A-Za-z0-9_.:@<>-]+)
  | (?P<punct>.)
''', re.VERBOSE | re.DOTALL)

OWNER_MARK = ' <<owner:%s>>'
OWNER_RE = re.compile(r'<<owner:([a-z0-9_]+)>>')
LINE_MARK = '<<line>> '
LINE_RE = re.compile(r'^\s*<<line>> (.*)$')


def stx_tokens(text):
    pos = 0
    while pos < len(text):
        m = STX_TOKEN.match(text, pos)
        yield m.lastgroup, m.group()
        pos = m.end()


def stx_defs(text, prefix):
    """Find definitions of configurations starting with `prefix` in a syntax
    file: a list of triples of name (without `code:` or `re2c:`), a list of
    tokens on the right-hand side (comments and whitespace included) and the
    line number of the definition."""
    toks = list(stx_tokens(text))
    defs = []
    line = 1
    i = 0
    while i < len(toks):
        kind, val = toks[i]
        if kind == 'word' and val.startswith(prefix):
            j = i + 1
            while j < len(toks) and toks[j][0] in ('space', 'comment'):
                j += 1
            if j < len(toks) and toks[j] == ('punct', '='):
                k = j + 1
                while k < len(toks) and toks[k] != ('punct', ';'):
                    k += 1
                defs.append((val.split(':', 1)[1], toks[j + 1:k], line))
                line += sum(v.count('\n') for _, v in toks[i:k + 1])
                i = k + 1
                continue
        line += val.count('\n')
        i += 1
    return defs


def owner_syntax(text):
    """Derive a probe syntax file from a default syntax file: every `nl` in a
    `code:*` template is prefixed with an owner comment naming the template,
    and line directives are replaced with a marker that names the file."""
    out = ['re2c:line-dirs = 1;',
        'code:line_info = "%s" file nl;' % LINE_MARK]
    # Transitions between conditions are emitted using this configuration.
    for name, rhs, _ in stx_defs(text, 're2c:cond:goto'):
        body = [v for k, v in rhs if k not in ('space', 'comment')]
        if name == 'cond:goto' and body != ['""']:
            out.append('re2c:cond:goto = %s "%s";' % (' '.join(body),
                OWNER_MARK % 'cond_goto'))
    for name, rhs, _ in stx_defs(text, 'code:'):
        if name in ('line_info', 'fingerprint'):
            continue
        body = [v for k, v in rhs if k not in ('space', 'comment')]
        if body == ['<undefined>']:
            continue
        rhs = ['"%s" nl' % (OWNER_MARK % name)
            if k == 'word' and v == 'nl' else v
            for k, v in rhs if k != 'comment']
        out.append('code:%s = %s;' % (name, ''.join(rhs)))
    return '\n'.join(out) + '\n'


# Construct detection ---------------------------------------------------------
#
# The forms below are those emitted by include/syntax/<lang>; the template
# probe checks that only structural templates emit them.

CONTROL_KEYWORDS = ['if', 'else', 'elif', 'for', 'while', 'loop', 'switch',
    'match', 'goto', 'case', 'continue', 'break']

# Keywords of other languages. Swift `guard` and `repeat` are not emitted by
# the current syntax files; they are kept to detect a template that would
# start emitting them.
LANG_KEYWORDS = {
    'go': ['fallthrough'],
    'haskell': ['then', 'of', 'when'],
    'ocaml': ['then', 'with'],
    'swift': ['guard', 'repeat', 'fallthrough'],
}

# Match arms and guards that have no keyword. Haskell `| cond =` guards and
# V `=>` arms are not emitted by the current syntax files; they are kept to
# detect a template that would start emitting them.
LANG_ARMS = {
    # `pat ->` arms, `| cond =` guards
    'haskell': r'(?<![-<>=|])->|(?:^|\s)\|\s[^|=]*(?<![=<>/])=(?![=>])',
    # `| pat ->` arms
    'ocaml': r'(?:^|\s)\|\s.*?->',
    'rust': r'=>',
    'v': r'=>',
    'zig': r'=>',
}

# Cursor moves (in addition to ++, --, +=, -= and = on the cursor):
# assignment with `<-` and functional advance `cursor + n` / `cursor - n`.
LANG_MOVES = {
    'haskell': r'<-|[-+](?![-+=>])',
    'ocaml': r'<-|[-+](?![-+=>])',
}

GENERIC_MOVES = ['YYSKIP', 'YYSHIFT', 'YYRESTORE', 'YYRESTORECTX',
    'YYRESTORETAG']
CURSOR_NAMES = ['YYCURSOR', 'yycursor', '_yycursor']

IDENT_L = r'(?<![A-Za-z0-9_])'
IDENT_R = r'(?![A-Za-z0-9_])'


class Detector:
    """Find control flow, `yych` accesses and cursor moves in a line of
    generated code (or in the flattened text of a template)."""

    def __init__(self, lang, yych, cursors):
        kws = CONTROL_KEYWORDS + LANG_KEYWORDS.get(lang, [])
        self.control = re.compile('%s(%s)%s' % (IDENT_L, '|'.join(kws),
            IDENT_R))
        arms = LANG_ARMS.get(lang)
        self.arms = re.compile(arms) if arms else None
        self.yych = re.compile('%s(%s)%s' % (IDENT_L, '|'.join(
            re.escape(v) for v in sorted(yych)), IDENT_R))
        cur = '|'.join(re.escape(v) for v in sorted(cursors))
        ops = r'\+\+|--|\+=|-=|=(?!=)'
        if lang in LANG_MOVES:
            ops += '|' + LANG_MOVES[lang]
        self.move = re.compile(
            r'(?:\+\+|--)\s*(?:%s)%s' % (cur, IDENT_R)
            + r'|%s(?:%s)\s*(?:%s)' % (IDENT_L, cur, ops)
            + r'|%s(?:%s)%s' % (IDENT_L, '|'.join(GENERIC_MOVES), IDENT_R))

    def find(self, line):
        """Return a list of (kind, start, end) for all constructs."""
        res = []
        for m in self.control.finditer(line):
            res.append(('control flow `%s`' % m.group(1),) + m.span())
        if self.arms:
            for m in self.arms.finditer(line):
                arm = m.group().strip()
                arm = '=>' if arm == '=>' else '->' if arm == '->' \
                    else '| ... ' + ('->' if arm.endswith('->') else '=')
                res.append(('control flow `%s`' % arm,) + m.span())
        for m in self.yych.finditer(line):
            res.append(('`%s` access' % m.group(1),) + m.span())
        for m in self.move.finditer(line):
            res.append(('cursor move',) + m.span())
        return res


def category(kind):
    """The category of a construct found by Detector."""
    if kind.startswith('control flow '):
        return CONTROL
    return YYCH if kind.endswith(' access') else CURSOR


def summarize(found):
    """Keep one construct of each category (control, yych, cursor)."""
    kinds = []
    seen = set()
    for kind, _, _ in found:
        cat = category(kind)
        if cat not in seen:
            seen.add(cat)
            kinds.append(kind)
    return kinds


# Probe 1: owners -------------------------------------------------------------

CONF_STRING = re.compile(r'\bre2c:([A-Za-z0-9_:@-]+)\s*=\s*'
    r'("(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|[^;\s]+)')
DIRECTIVE_STRING = re.compile(r'\b(?:format|separator)\s*=\s*'
    r'("(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\')')

SPECIAL_ACTION = re.compile(r'(<![^>\n]*>|!entry|!pre_rule|!post_rule)'
    r'\s*(?:(?:=>|:=>)\s*[A-Za-z0-9_]+\s*)?\{')

# Configurations whose values are user code wrapped into the generated code.
USER_CONF = re.compile(r'^(?:define:|YY|variable:|label:|cond:)')
IDENTIFIER = re.compile(r'^[A-Za-z_][A-Za-z0-9_]*$')


def unquote(s):
    if s[:1] in '"\'':
        s = s[1:-1]
    return s.replace('\\n', '\n').replace('\\t', '\t').replace('\\"', '"') \
        .replace("\\'", "'").replace('\\\\', '\\')


class SourceInfo:
    """Names and user-provided code fragments configured in a test file."""

    def __init__(self, text):
        self.yych = {'yych'}
        self.cursors = set(CURSOR_NAMES)
        self.headers = []
        self.sigils = {'@@'}
        strings = []
        for m in CONF_STRING.finditer(text):
            name, val = m.group(1), unquote(m.group(2))
            conf = name.replace('define:', '').replace('variable:', '')
            if conf == 'yych':
                self.yych.add(val)
            elif conf == 'YYCURSOR':
                self.cursors.add(val)
            elif conf in ('header', 'flags:type-header', 'flags:t'):
                self.headers.append(val)
            elif conf == 'api:sigil' or '@' in conf:
                self.sigils.add(val)
            if m.group(2)[:1] in '"\'' and USER_CONF.match(name):
                strings.append(val)
        for m in DIRECTIVE_STRING.finditer(text):
            strings.append(unquote(m.group(1)))
        # Setup actions and special actions are user code that is emitted
        # without line directives.
        for m in SPECIAL_ACTION.finditer(text):
            depth = 0
            for i in range(m.end() - 1, len(text)):
                depth += {'{': 1, '}': -1}.get(text[i], 0)
                if depth == 0:
                    strings.append(text[m.end():i])
                    break
        # Sigils are replaced with arbitrary text in the generated code.
        sigil_re = '|'.join(re.escape(x) + r'(?:\{[A-Za-z0-9_]+\})?'
            for x in sorted(self.sigils, key=len, reverse=True) if x)
        self.fragments = []
        for val in strings:
            for line in val.split('\n'):
                line = line.strip()
                # Plain names (variables, labels) are not code: they are
                # used to detect constructs, not to exempt them.
                if not line or IDENTIFIER.match(line):
                    continue
                parts = re.split(sigil_re, line)
                if not ''.join(parts).strip():
                    continue
                self.fragments.append(re.compile('.*?'.join(re.escape(p)
                    for p in parts)))

    def user_spans(self, line):
        """Spans of the line covered by a complete user-provided string."""
        return [m.span() for f in self.fragments for m in f.finditer(line)
            if m.end() > m.start()]


def unowned_constructs(line, info, det):
    """Constructs on an untagged line that are not inside user text."""
    spans = info.user_spans(line)
    found = [(k, s, e) for k, s, e in det.find(line)
        if not any(us <= s and e <= ue for us, ue in spans)]
    return summarize(found)


def analyze_owners(text, outname, info, det):
    """Return a triple of the list of (line number, construct, line) for
    untagged lines of generated code, a flag that the output has line
    markers, and a flag that at least one generated line was inspected."""
    found = []
    generated = False
    seen_marker = False
    seen_generated = False
    for n, line in enumerate(text.split('\n'), 1):
        m = LINE_RE.match(line)
        if m:
            seen_marker = True
            generated = m.group(1).strip().strip('"').endswith(outname)
            continue
        s = line.strip()
        if not generated or not s:
            continue
        seen_generated = True
        if OWNER_RE.search(line):
            continue
        for kind in unowned_constructs(s, info, det):
            found.append((n, kind, s))
    return found, seen_marker, seen_generated


def parse_header(head, relpath, outpath):
    """Translate a test header into re2c arguments like run_tests.py does.
    Return (extension, language, arguments) or None for a non-test file."""
    for prefix, ext, lang in HEADERS:
        if head.startswith(prefix):
            break
    else:
        return None
    s = head
    for alias, repl in ALIASES:
        s = s.replace(alias, repl)
    s = RE2C_PATTERN.sub(r'\1', s)
    s = s.replace('$INPUT', relpath)
    s = s.replace('$OUTPUT', outpath)
    s = s.replace('$DEPFILE', outpath + '.d')
    args = s.split()
    for i, a in enumerate(args):
        if a == '--lang' and i + 1 < len(args):
            lang = args[i + 1]
    return ext, lang, args


def skip_reason(args):
    for a in args:
        if a in ('--skeleton', '--emit-dot'):
            return 'non-code target'
        if a in ('--help', '--version', '--vernum'):
            return 'no code generated'
        if a == '--syntax':
            return 'custom syntax file'
        if a.startswith('-') and not a.startswith('--') \
                and not a.startswith('-W'):
            flags = re.split(r'[otI]', a[1:], maxsplit=1)[0]
            if 'S' in flags or 'D' in flags:
                return 'non-code target'
            if any(c in flags for c in 'hvV?'):
                return 'no code generated'
    return None


def probe_args(args, outpath, scratch):
    """Rewrite test arguments for the probe: enable line directives and
    redirect all output files to the scratch directory."""
    res = []
    i = 0
    while i < len(args):
        a = args[i]
        i += 1
        if a == '--no-debug-info':
            continue
        if a in ('-o', '--output'):
            res += ['-o', outpath]
            i += 1
        elif a in ('-t', '--header', '--type-header'):
            res += ['--header', os.path.join(scratch, 'header')]
            i += 1
        elif a == '--depfile':
            res += ['--depfile', os.path.join(scratch, 'depfile')]
            i += 1
        elif a.startswith('-') and not a.startswith('--') \
                and not a.startswith('-W'):
            m = re.match(r'-([^otI]*)(.*)$', a)
            flags, rest = m.group(1).replace('i', ''), m.group(2)
            if rest[:1] == 'o':
                res += (['-' + flags] if flags else []) + ['-o', outpath]
                i += 0 if rest[1:] else 1
            elif rest[:1] == 't':
                res += (['-' + flags] if flags else []) \
                    + ['--header', os.path.join(scratch, 'header')]
                i += 0 if rest[1:] else 1
            elif flags or rest:
                res.append('-' + flags + rest)
        else:
            res.append(a)
    return res


def has_generated_code(path):
    try:
        with open(path, 'rb') as f:
            text = f.read().decode('utf-8', 'replace')
    except OSError:
        return False
    return re.search(r'[Gg]enerated by re2', text) is not None


def owners_task(ctx, relpath):
    """Run the owner probe on one test. Return a dict with 'status' (one of
    'analyzed', 'skipped', 'error'), 'lang', 'reason' and 'findings'."""
    res = {'file': relpath, 'lang': None, 'reason': None, 'findings': []}
    path = os.path.join(ctx['tree'], relpath)
    with open(path, 'rb') as f:
        text = f.read().decode('utf-8', 'replace')
    head = text.split('\n', 1)[0].strip()
    scratch = tempfile.mkdtemp(dir=ctx['scratch'])
    try:
        parsed = parse_header(head, relpath, '$OUTPUT')
        if parsed is None:
            res.update(status='skipped', reason='no test header')
            return res
        ext, lang, args = parsed
        res['lang'] = lang
        stem = os.path.splitext(path)[0]
        if os.path.basename(stem).startswith('error'):
            res.update(status='skipped', reason='error test')
            return res
        if not has_generated_code('%s.%s' % (stem, ext)):
            res.update(status='skipped',
                reason='expected output has no generated code')
            return res
        reason = skip_reason(args)
        if reason:
            res.update(status='skipped', reason=reason)
            return res
        if lang not in ctx['syntax']:
            res.update(status='skipped', reason='unknown language')
            return res

        outname = 'probe_output.' + ext
        outpath = os.path.join(scratch, outname)
        args = [a.replace('$OUTPUT', outpath) for a in args]
        args = probe_args(args, outpath, scratch)
        if outpath not in args:
            args += ['-o', outpath]
        cmd = [ctx['re2c']] + ctx['incpaths'] \
            + ['--syntax', ctx['syntax'][lang], '-W', '--no-version',
                '--no-generation-date'] + args
        # Headers set in the source file are relative to the output file.
        info = SourceInfo(text)
        for h in info.headers:
            if h and not os.path.isabs(h):
                os.makedirs(os.path.join(scratch, os.path.dirname(h)),
                    exist_ok=True)
        rc, out = run(cmd, cwd=ctx['tree'], timeout=120)
        if rc != 0 or not os.path.isfile(outpath):
            res.update(status='error', reason='re2c failed with the probe'
                ' syntax file (exit code %d)' % rc,
                findings=[(0, 're2c', out.strip())])
            return res
        with open(outpath, 'rb') as f:
            gen = f.read().decode('utf-8', 'replace')
        det = Detector(lang, info.yych, info.cursors)
        found, seen_marker, seen_generated = analyze_owners(gen, outname,
            info, det)
        if not seen_marker:
            res.update(status='error', reason='no line markers in output')
            return res
        if not seen_generated:
            res.update(status='skipped', reason='no_generated_region')
            return res
        res.update(status='analyzed', findings=found)
        if ctx['keep']:
            shutil.copy(outpath, os.path.join(ctx['keepdir'],
                relpath.replace(os.sep, '__') + '.' + ext))
        return res
    finally:
        shutil.rmtree(scratch, ignore_errors=True)


def copy_tests(dst):
    """Merge test/ and examples/ into one tree, as run_tests.py does."""
    for src in ('test', 'examples'):
        src = os.path.join(ROOT, src)
        for path, dirs, files in os.walk(src):
            dstpath = os.path.join(dst, os.path.relpath(path, src))
            os.makedirs(dstpath, exist_ok=True)
            for f in files:
                shutil.copy(os.path.join(path, f), dstpath)


def probe_owners(opts, tmp, tests=None, extra_syntax=None,
        expect_analyzed=None):
    """Probe 1. Return the number of failures and the list of failed tests.
    The self-test passes its own `tests` (a map from file name to contents),
    definitions that are appended to the probe syntax files and the expected
    number of analyzed files."""
    stxdir = os.path.join(ROOT, 'include', 'syntax')
    probedir = os.path.join(tmp, 'syntax')
    os.makedirs(probedir)
    syntax = {}
    for lang in sorted(os.listdir(stxdir)):
        with open(os.path.join(stxdir, lang), encoding='utf-8',
                errors='replace') as f:
            text = owner_syntax(f.read())
        if extra_syntax and lang in extra_syntax:
            text += extra_syntax[lang]
        # re2c looks for the syntax file in the include paths.
        syntax[lang] = 'codegen_probe_%s.syntax' % lang
        with open(os.path.join(probedir, syntax[lang]), 'w',
                encoding='utf-8') as f:
            f.write(text)

    tree = os.path.join(tmp, 'tests')
    if tests is None:
        copy_tests(tree)
    else:
        os.makedirs(tree)
        for name, text in tests.items():
            with open(os.path.join(tree, name), 'w', encoding='utf-8') as f:
                f.write(text)
    incpaths = ['-I', probedir, '-I', '.']
    for path, dirs, files in os.walk(tree):
        for d in sorted(dirs):
            incpaths += ['-I', os.path.relpath(os.path.join(path, d), tree)]
    incpaths += ['-I', os.path.join(ROOT, 'include'),
        '-I', os.path.join(ROOT, 'include', 'syntax')]
    relpaths = sorted(os.path.relpath(os.path.join(p, f), tree)
        for p, _, fs in os.walk(tree) for f in fs if f.endswith('.re'))

    scratch = os.path.join(tmp, 'scratch')
    os.makedirs(scratch)
    keepdir = os.path.join(tmp, 'outputs')
    if opts.keep:
        os.makedirs(keepdir)
    ctx = {'tree': tree, 're2c': opts.re2c, 'syntax': syntax,
        'incpaths': incpaths, 'scratch': scratch, 'keep': opts.keep,
        'keepdir': keepdir}

    with concurrent.futures.ThreadPoolExecutor(opts.jobs) as ex:
        results = list(ex.map(lambda r: owners_task(ctx, r), relpaths))

    analyzed = {}
    skipped = {}
    failed = []
    for r in results:
        if r['status'] == 'analyzed':
            analyzed[r['lang']] = analyzed.get(r['lang'], 0) + 1
            if r['findings']:
                failed.append(r)
        elif r['status'] == 'skipped':
            skipped[r['reason']] = skipped.get(r['reason'], 0) + 1
            if opts.verbose:
                log('  skipped (%s): %s' % (r['reason'], r['file']))
        else:
            failed.append(r)

    for r in failed:
        what = r['reason'] or '%d unowned construct(s)' % len(r['findings'])
        log('  FAIL [%s] %s: %s' % (r['lang'], r['file'], what))
        for n, kind, line in r['findings']:
            log('    line %d: %s: %s' % (n, kind, line))
    log('owners: %d .re files, %d analyzed, %d skipped, %d failed'
        % (len(results), sum(analyzed.values()), sum(skipped.values()),
            len(failed)))
    log('  analyzed per backend: ' + ', '.join('%s %d' % kv
        for kv in sorted(analyzed.items())))
    log('  skipped per reason: ' + (', '.join('%s %d' % kv
        for kv in sorted(skipped.items())) or 'none'))
    if opts.keep:
        log('  generated files kept in ' + keepdir)
    nanalyzed = sum(analyzed.values())
    if expect_analyzed is not None and nanalyzed != expect_analyzed:
        log('  FAIL expected %d analyzed file(s)' % expect_analyzed)
        return len(failed) + 1, failed
    return len(failed), failed


# Probe 4: templates ----------------------------------------------------------

def template_text(rhs):
    """Flatten the right-hand side of a template: string literals are kept,
    as well as references to `yych` and to API names (YY*); other variables
    and the template syntax are replaced with neutral placeholders."""
    parts = []
    for kind, val in rhs:
        if kind == 'string':
            parts.append(unquote(val))
        elif kind == 'word':
            keep = val == 'yych' or val.startswith('YY')
            parts.append(val if keep else '_')
        elif kind == 'punct':
            parts.append(' ')
    return ' '.join(parts)


def check_templates(syntaxes, structural):
    """Check the templates of syntax files (a map from language to a pair of
    file name and contents) against the structural templates (a map from
    template name to a pair of the admitted categories and a description).
    Return a triple of the number of audited templates, a map from
    structural template to a map from language to the categories that it
    emits, and a list of failure messages."""
    audited = 0
    used = {}
    failures = []
    for lang, (fname, text) in sorted(syntaxes.items()):
        det = Detector(lang, {'yych'}, CURSOR_NAMES)
        for name, rhs, line in stx_defs(text, 'code:'):
            body = [v for k, v in rhs if k not in ('space', 'comment')]
            if body == ['<undefined>']:
                continue
            audited += 1
            kinds = summarize(det.find(template_text(rhs)))
            if not kinds:
                continue
            if name not in structural:
                failures.append('%s:%d: code:%s emits %s but is not a '
                    'structural template' % (fname, line, name,
                        ', '.join(kinds)))
                continue
            admitted = structural[name][0]
            used.setdefault(name, {}).setdefault(lang, set()).update(
                category(k) for k in kinds)
            extra = [k for k in kinds if category(k) not in admitted]
            if extra:
                failures.append('%s:%d: code:%s emits %s outside of its '
                    'admitted categories (%s)' % (fname, line, name,
                        ', '.join(extra), ', '.join(sorted(admitted))))
    for name in sorted(structural):
        emitted = set()
        for cats in used.get(name, {}).values():
            emitted |= cats
        for cat in sorted(structural[name][0] - emitted):
            failures.append('structural template `%s` admits %s but emits it '
                'in no syntax file, remove it from the list' % (name, cat))
    return audited, used, failures


def read_syntaxes():
    stxdir = os.path.join(ROOT, 'include', 'syntax')
    res = {}
    for lang in sorted(os.listdir(stxdir)):
        with open(os.path.join(stxdir, lang), encoding='utf-8',
                errors='replace') as f:
            res[lang] = ('include/syntax/' + lang, f.read())
    return res


def probe_templates(opts):
    """Probe 4. Return the number of failures."""
    syntaxes = read_syntaxes()
    audited, used, failures = check_templates(syntaxes,
        STRUCTURAL_TEMPLATES)
    if opts.verbose:
        for name in sorted(used):
            log('  structural %s (%s): %s' % (name,
                ', '.join(sorted(STRUCTURAL_TEMPLATES[name][0])),
                ' '.join(sorted(used[name]))))
    for msg in failures:
        log('  FAIL ' + msg)
    log('templates: %d syntax files, %d templates audited, %d structural '
        'templates (%d template definitions with constructs, %d admitted '
        'categories), %d failed'
        % (len(syntaxes), audited, len(used),
            sum(len(v) for v in used.values()),
            sum(len(v[0]) for v in STRUCTURAL_TEMPLATES.values()),
            len(failures)))
    return len(failures)


# Probe 3: registry -----------------------------------------------------------

CPP_BLANK = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\\n])*"'
    r"|'(?:\\.|[^'\\\n])*'", re.DOTALL)
CALL_RE = re.compile(r'\b(?:render|gen)_code_([a-z0-9_]+)\b')
LABEL_RE = re.compile(r'\bcase\s+((?:[A-Za-z0-9_]+::)*[A-Za-z0-9_]+)'
    r'\s*:(?!:)|\bdefault\s*:')
TERMINATOR_RE = re.compile(r'\b(?:break|return\b[^;]*)\s*;[\s}]*$')


def blank_cpp(text):
    """Replace comments and string literals with spaces (keeping lines)."""
    return CPP_BLANK.sub(lambda m: re.sub(r'[^\n]', ' ', m.group()), text)


def matching(text, pos, open_ch, close_ch):
    """Position after the bracket that closes the one at `pos`."""
    depth = 0
    for i in range(pos, len(text)):
        if text[i] == open_ch:
            depth += 1
        elif text[i] == close_ch:
            depth -= 1
            if depth == 0:
                return i + 1
    return len(text)


def switch_cases(text):
    """Find `switch` statements on CodeKind in C++ code (with comments and
    strings blanked). Return a list of switches, each a list of branches
    (line number, kinds, calls, terminated): consecutive labels share one
    branch, a branch extends from its labels to the next label at the top
    level of the switch body (nested braces are skipped), and `calls` are
    the templates rendered by the branch, including the branches that it
    falls through to if it does not end with `break` or `return`."""
    switches = []
    for m in re.finditer(r'\bswitch\s*\(', text):
        end = matching(text, m.end() - 1, '(', ')')
        brace = re.compile(r'\s*\{').match(text, end)
        if not brace:
            continue
        start = brace.end()
        stop = matching(text, brace.end() - 1, '{', '}') - 1
        labels = []
        depth = 0
        i = start
        while i < stop:
            c = text[i]
            if c == '{':
                depth += 1
            elif c == '}':
                depth -= 1
            elif depth == 0 and c in 'cd':
                lm = LABEL_RE.match(text, i)
                if lm and (i == 0 or not re.match(r'[A-Za-z0-9_]',
                        text[i - 1])):
                    kind = lm.group(1) or ''
                    kind = kind[len('CodeKind::'):] \
                        if kind.startswith('CodeKind::') else None
                    labels.append((i, lm.end(), kind))
                    i = lm.end()
                    continue
            i += 1
        if not any(k for _, _, k in labels):
            continue
        branches = []
        for n, (s, e, kind) in enumerate(labels):
            nxt = labels[n + 1][0] if n + 1 < len(labels) else stop
            body = text[e:nxt]
            if branches and not branches[-1]['body'].strip():
                b = branches[-1]
                b['kinds'].append(kind)
                b['body'] = body
            else:
                branches.append({'line': text.count('\n', 0, s) + 1,
                    'kinds': [kind], 'body': body})
        for b in branches:
            b['own'] = CALL_RE.findall(b['body'])
            b['terminated'] = bool(TERMINATOR_RE.search(b['body']))
        res = []
        for n, b in enumerate(branches):
            calls = list(b['own'])
            j = n
            while not branches[j]['terminated'] and j + 1 < len(branches):
                j += 1
                calls += branches[j]['own']
            kinds = [k for k in b['kinds'] if k]
            if kinds:
                res.append((b['line'], kinds, calls, b['terminated']))
        switches.append(res)
    return switches


def code_kinds(constants_h):
    m = re.search(r'enum\s+class\s+CodeKind\s*(?::\s*\w+\s*)?\{(.*?)\}',
        blank_cpp(constants_h), re.DOTALL)
    if not m:
        return []
    return [v.split('=')[0].strip() for v in m.group(1).split(',')
        if v.strip()]


def template_kind_name(template):
    return '_'.join(p[2:] if p.startswith('yy') else p
        for p in template.split('_'))


def template_matches_kind(template, kind):
    return template_kind_name(template) == kind.lower()


def check_registry(opt_h, sources, kinds, render_file, allowlist,
        known_mismatches, names, min_templates=0, min_cases=0):
    """Check the template registry. `sources` maps file names in src/ to
    their contents, `kinds` lists the CodeKind values, `render_file` is the
    file with the render switch and `names` maps a CodeKind value to the
    templates that its render case may call besides the one named after it.
    Return a dict with the declared templates, the called templates, the
    templates allowed to have no caller, the number of checked render cases,
    the CodeKind values without a render case, the render cases without a
    direct template call, the known mismatches found, the applied `names`
    entries (pairs of a CodeKind value and a template, and a message), and
    the failure messages."""
    m = re.search(r'^#define RE2C_CODE_TEMPLATES\b(?:.*\\\n)*.*$',
        blank_cpp(opt_h), re.MULTILINE)
    templates = re.findall(r'\bCODE_TEMPLATE\(\s*([a-z0-9_]+)\s*,',
        m.group() if m else '')
    called = set()
    for text in sources.values():
        called.update(CALL_RE.findall(blank_cpp(text)))
    res = {'templates': templates, 'called': called, 'allowed': [],
        'ncases': 0, 'uncovered': [], 'delegating': [], 'known': [],
        'named': [], 'failures': []}
    failures = res['failures']

    # The sources must have been read: a missing or truncated template list
    # would make the checks below pass on nothing.
    if not m:
        failures.append('src/options/opt.h: no `#define RE2C_CODE_TEMPLATES`'
            ' block found')
    elif len(templates) < min_templates:
        failures.append('src/options/opt.h: only %d CODE_TEMPLATE entries in'
            ' RE2C_CODE_TEMPLATES, expected at least %d'
            % (len(templates), min_templates))

    # (a) Every template has a caller, or is allowed not to have one.
    for t in templates:
        if t in called:
            if t in allowlist:
                failures.append('template `%s` is in the allowlist but has '
                    'a caller, remove it from the allowlist' % t)
        elif t in allowlist:
            res['allowed'].append(t)
        else:
            failures.append('template `%s` has no render_code_%s or '
                'gen_code_%s call in src/' % (t, t, t))

    # (b) Every render case calls the template named after its kind, or one
    # of the templates listed for its kind in `names`. This is never
    # exempted by the allowlist of (a).
    matched = set()
    applied = set()
    covered = set()
    for path in sorted(sources):
        if not re.search(r'\bcase\s+CodeKind::', sources[path]):
            continue
        for sw in switch_cases(blank_cpp(sources[path])):
            renders = any(calls for _, _, calls, _ in sw)
            for line, ks, calls, _ in sw:
                if path == render_file and renders:
                    covered.update(ks)
                    if not calls:
                        res['delegating'].append('/'.join(ks))
                if not calls:
                    continue
                res['ncases'] += 1
                for c in calls:
                    if any(template_matches_kind(c, k) for k in ks):
                        continue
                    msg = '%s:%d: case CodeKind::%s calls render_code_%s' \
                        % (path, line, '/'.join(ks), c)
                    keys = [(k, c) for k in ks if c in names.get(k, ())]
                    if keys:
                        applied.update(keys)
                        res['named'].append((keys[0], msg))
                        continue
                    keys = [(k, c) for k in ks if (k, c) in known_mismatches]
                    if keys:
                        matched.update(keys)
                        res['known'].append('%s (%s)' % (msg,
                            known_mismatches[keys[0]]))
                    else:
                        failures.append(msg)
    for key in sorted(known_mismatches):
        if key not in matched:
            failures.append('known mismatch case CodeKind::%s calls '
                'render_code_%s no longer occurs, remove it from the list'
                % key)
    for k in sorted(names):
        for t in sorted(names[k]):
            if (k, t) not in applied:
                failures.append('no render case CodeKind::%s calls '
                    'render_code_%s, remove it from the list of aliases '
                    'and families' % (k, t))
    if res['ncases'] < min_cases:
        failures.append('only %d render cases found, expected at least %d'
            % (res['ncases'], min_cases))

    # Every CodeKind value has a case in the render switch.
    if not kinds:
        failures.append('src/constants.h: no `enum class CodeKind` found')
    for k in kinds:
        if k not in covered:
            res['uncovered'].append(k)
            failures.append('%s: CodeKind::%s has no case in the render '
                'switch' % (render_file, k))
    return res


def read_registry_sources():
    """Return the contents of src/options/opt.h, of src/constants.h and a
    map from the other source files in src/ to their contents."""
    with open(os.path.join(ROOT, 'src', 'options', 'opt.h'),
            encoding='utf-8', errors='replace') as f:
        opt_h = f.read()
    with open(os.path.join(ROOT, 'src', 'constants.h'),
            encoding='utf-8', errors='replace') as f:
        constants_h = f.read()
    sources = {}
    for path, _, files in os.walk(os.path.join(ROOT, 'src')):
        for name in files:
            if name == 'opt.h' and os.path.basename(path) == 'options':
                continue
            if os.path.splitext(name)[1] in ('.h', '.cc', '.re', '.ypp'):
                p = os.path.join(path, name)
                with open(p, encoding='utf-8', errors='replace') as f:
                    sources[os.path.relpath(p, ROOT)] = f.read()
    return opt_h, constants_h, sources


def registry_names():
    """Merge the aliases and the families of render case templates."""
    names = {}
    for table in (REGISTRY_KIND_ALIASES, REGISTRY_KIND_FAMILIES):
        for k, ts in table.items():
            names.setdefault(k, set()).update(ts)
    return names


RENDER_FILE = os.path.join('src', 'codegen', 'pass4_render.cc')


def probe_registry(opts):
    """Probe 3. Return the number of failures."""
    opt_h, constants_h, sources = read_registry_sources()
    kinds = code_kinds(constants_h)
    lists = not opts.no_allowlists
    res = check_registry(opt_h, sources, kinds, RENDER_FILE,
        REGISTRY_ALLOWLIST if lists else {},
        REGISTRY_KNOWN_MISMATCHES if lists else {},
        registry_names(), REGISTRY_MIN_TEMPLATES, REGISTRY_MIN_CASES)
    for t in res['allowed']:
        log('  allowed without caller: %s (%s)' % (t, REGISTRY_ALLOWLIST[t]))
    for msg in res['known']:
        log('  known mismatch ' + msg)
    aliases = [msg for (k, t), msg in res['named']
        if t in REGISTRY_KIND_ALIASES.get(k, ())]
    families = [msg for (k, t), msg in res['named']
        if t not in REGISTRY_KIND_ALIASES.get(k, ())]
    if opts.no_allowlists or opts.verbose:
        for msg in aliases:
            log('  alias applied: ' + msg)
        for msg in families:
            log('  family applied: ' + msg)
    log('  info: %d render branches (%d CodeKind values) without a direct '
        'render_code_*/gen_code_* call: %s' % (len(res['delegating']),
            sum(len(d.split('/')) for d in res['delegating']),
            ', '.join(res['delegating']) or 'none'))
    for msg in res['failures']:
        log('  FAIL ' + msg)
    templates = res['templates']
    log('registry: %d templates, %d with callers, %d allowed without callers'
        ' (%s), %d/%d CodeKind values covered by the render switch, %d '
        'render cases checked, %d alias(es) and %d family call(s) applied, '
        '%d known mismatch(es), %d failed'
        % (len(templates), len([t for t in templates if t in res['called']]),
            len(res['allowed']), ', '.join(res['allowed']) or 'none',
            len(kinds) - len(res['uncovered']), len(kinds), res['ncases'],
            len(aliases), len(families), len(res['known']),
            len(res['failures'])))
    return len(res['failures'])


# Probe 2: opaque -------------------------------------------------------------

# Rules shared by all reference lexers: backtracking, fixed and variable
# trailing context, and (with tags) s-tags, m-tags and fixed tags.
OPAQUE_RULES = '''
        [a-z]+ "!"   { return 1; }
        [a-z]        { return 2; }
        "ab" / "cd"  { return 3; }
        [0-9]+ / [a-z]+ "." { return 4; }
'''
OPAQUE_TAG_RULES = '''
        [0-9]+ @t1 "." @t2 [0-9]* @t3 "e" {
            USE(t1); USE(t2); USE(t3); return 5; }
        "x" @t3 [0-9]{3}   { USE(t3); return 6; }
        (#m1 "q" #m2 "w")+ { USE(m1); USE(m2); return 7; }
'''
OPAQUE_EOF_RULE = '''
        $ { return -1; }
'''

# The state is an incomplete type: the lexer can only use the generic API.
OPAQUE_C = '''\
#include <stddef.h>

struct state;
typedef long pos_t;

unsigned char st_peek(struct state *st);
void st_skip(struct state *st);
void st_backup(struct state *st);
void st_restore(struct state *st);
void st_backupctx(struct state *st);
void st_restorectx(struct state *st);
int st_lessthan(struct state *st, size_t n);
int st_fill(struct state *st, size_t n);
int st_fill_eof(struct state *st);
void st_shift(struct state *st, long n);
pos_t st_pos(struct state *st);
void st_restoretag(struct state *st, pos_t t);
pos_t st_shifttag(struct state *st, pos_t t, long n);
void st_mtag(struct state *st, pos_t *t, long n);

#define YYCTYPE unsigned char
#define YYPEEK() st_peek(st)
#define YYSKIP() st_skip(st)
#define YYBACKUP() st_backup(st)
#define YYRESTORE() st_restore(st)
#define YYBACKUPCTX() st_backupctx(st)
#define YYRESTORECTX() st_restorectx(st)
#define YYLESSTHAN(n) st_lessthan(st, n)
#define YYFILL(n) %(fill)s
#define YYSHIFT(n) st_shift(st, n)
#define YYSTAGP(t) t = st_pos(st)
#define YYSTAGN(t) t = -1
#define YYRESTORETAG(t) st_restoretag(st, t)
#define YYSHIFTSTAG(t, n) t = st_shifttag(st, t, n)
#define YYMTAGP(t) st_mtag(st, &t, 1)
#define YYMTAGN(t) st_mtag(st, &t, 0)
#define YYSHIFTMTAG(t, n) st_mtag(st, &t, n)
#define USE(t) (void)(t)
%(body)s
'''

OPAQUE_C_LOCAL = '''
int lex(struct state *st)
{
    pos_t t1, t2, t3, m1, m2;
    /*!stags:re2c format = "pos_t @@;\\n"; */
    /*!mtags:re2c format = "pos_t @@;\\n"; */
    /*!re2c
        re2c:api = generic;
        %(conf)s
        %(rules)s
        * { return 0; }
    */
}
'''

OPAQUE_C_GLOBAL = '''
static pos_t t1, t2, t3, m1, m2;
static unsigned int yyaccept;
/*!stags:re2c format = "static pos_t @@;\\n"; */
/*!mtags:re2c format = "static pos_t @@;\\n"; */
/*!re2c
    re2c:api = generic;
    re2c:YYFN = ["lex;int", "st;struct state *"];
    %(conf)s
    %(rules)s
    * { return 0; }
*/
'''

OPAQUE_GO = '''\
package main

// The state is an interface: the lexer can only use the generic API.
type state interface {
	peek() byte
	skip()
	backup()
	restore()
	backupctx()
	restorectx()
	lessthan(n int) bool
	fill(n int)
	fillEOF() int
	shift(n int)
	pos() int
	restoretag(t int)
	shifttag(t int, n int) int
	mtag(t *int, n int)
}

func USE(t int) {}

func main() {}
%(body)s
'''

OPAQUE_GO_CONF = '''
        re2c:api = generic;
        re2c:api:style = free-form;
        re2c:YYCTYPE = byte;
        re2c:YYPEEK = "st.peek()";
        re2c:YYSKIP = "st.skip()";
        re2c:YYBACKUP = "st.backup()";
        re2c:YYRESTORE = "st.restore()";
        re2c:YYBACKUPCTX = "st.backupctx()";
        re2c:YYRESTORECTX = "st.restorectx()";
        re2c:YYLESSTHAN = "st.lessthan(@@{len})";
        re2c:YYSHIFT = "st.shift(@@{shift})";
        re2c:YYSTAGP = "@@{tag} = st.pos()";
        re2c:YYSTAGN = "@@{tag} = -1";
        re2c:YYRESTORETAG = "st.restoretag(@@{tag})";
        re2c:YYSHIFTSTAG = "@@{tag} = st.shifttag(@@{tag}, @@{shift})";
        re2c:YYMTAGP = "st.mtag(&@@{tag}, 1)";
        re2c:YYMTAGN = "st.mtag(&@@{tag}, 0)";
        re2c:YYSHIFTMTAG = "st.mtag(&@@{tag}, @@{shift})";
'''

OPAQUE_GO_LOCAL = '''
func lex(st state) int {
	var t1, t2, t3, m1, m2 int
	/*!stags:re2c format = "var @@ int\\n_ = @@\\n"; */
	/*!mtags:re2c format = "var @@ int\\n_ = @@\\n"; */
	_, _, _, _, _ = t1, t2, t3, m1, m2
	/*!re2c
		%(conf)s
		%(rules)s
		* { return 0 }
	*/
}
'''

OPAQUE_GO_GLOBAL = '''
var t1, t2, t3, m1, m2 int
var yyaccept int
/*!stags:re2c format = "var @@ int\\n"; */
/*!mtags:re2c format = "var @@ int\\n"; */
/*!re2c
	re2c:YYFN = ["lex;int", "st;state"];
	%(conf)s
	%(rules)s
	* { return 0 }
*/
'''

# Compiler diagnostics: `file:line[:column]: [severity:] message`.
DIAGNOSTIC_RE = re.compile(r'^(?P<file>[^\s:]+):(?P<line>\d+):(?:\d+:)?\s*'
    r'(?:(?P<sev>fatal error|error|warning|note):\s*)?(?P<msg>.*)$')

# Other lines of compiler output that mention errors without reporting one
# (the error count printed by Clang). Any other line that mentions an error
# but is not a diagnostic makes a known failure fail.
ERROR_SUMMARY_RE = re.compile(r'^\d+ errors? generated\.$')

# Comments and string literals of generated C and Go code.
GEN_BLANK = re.compile(CPP_BLANK.pattern + r'|`[^`]*`', re.DOTALL)


def opaque_source(lang, model, tags, eof):
    """Return the source of a reference lexer."""
    rules = OPAQUE_RULES + (OPAQUE_TAG_RULES if tags else '') \
        + (OPAQUE_EOF_RULE if eof else '')
    conf = ['re2c:eof = 0;'] if eof else []
    if lang == 'go':
        rules = rules.replace('; }', ' }')
        conf.insert(0, OPAQUE_GO_CONF.strip())
        conf.append('re2c:YYFILL = "%s";' % ('st.fillEOF() == 0' if eof
            else 'st.fill(@@)'))
        body = OPAQUE_GO_GLOBAL if model == 'recursive-functions' \
            else OPAQUE_GO_LOCAL
        body = body % {'conf': '\n\t\t'.join(conf), 'rules': rules}
        return OPAQUE_GO % {'body': body}
    body = OPAQUE_C_GLOBAL if model == 'recursive-functions' \
        else OPAQUE_C_LOCAL
    body = body % {'conf': '\n        '.join(conf), 'rules': rules}
    fill = 'st_fill_eof(st)' if eof else 'st_fill(st, n)'
    return OPAQUE_C % {'fill': fill, 'body': body}


def opaque_cases(langs):
    cases = []
    for lang in langs:
        for model in ('goto-label', 'loop-switch', 'recursive-functions'):
            flags = ['', '-b', '-s']
            if lang == 'c' and model == 'goto-label':
                flags.append('-g')
            for flag in flags:
                for tags in (False, True):
                    # re2c does not support the end-of-input rule with
                    # bitmaps and computed gotos.
                    for eof in ((False,) if flag in ('-b', '-g')
                            else (False, True)):
                        cases.append((lang, model, flag, tags, eof))
    return cases


def opaque_name(case):
    lang, model, flag, tags, eof = case
    return '%s --%s%s%s%s' % (lang, model, ' ' + flag if flag else '',
        ' --tags' if tags else '', ' (eof rule)' if eof else ' (YYFILL)')


def opaque_task(ctx, case, syntax=None):
    """Generate and compile one reference lexer, optionally with a syntax
    file (used by the self-test). Return a triple of status ('ok', 're2c' or
    'compile'), program output and generated code."""
    lang, model, flag, tags, eof = case
    d = tempfile.mkdtemp(dir=ctx['scratch'])
    try:
        ext = 'go' if lang == 'go' else 'c'
        src = os.path.join(d, 'lexer.re')
        out = os.path.join(d, 'lexer.' + ext)
        with open(src, 'w', encoding='utf-8') as f:
            f.write(opaque_source(lang, model, tags, eof))
        cmd = [ctx['re2c'], '--lang', lang, '--' + model, src, '-o', out,
            '-W', '--no-version', '--no-generation-date']
        if syntax:
            with open(os.path.join(d, 'probe.syntax'), 'w',
                    encoding='utf-8') as f:
                f.write(syntax)
            cmd += ['-I', d, '--syntax', 'probe.syntax']
        if flag:
            cmd.append(flag)
        if tags:
            cmd.append('--tags')
        rc, msg = run(cmd, timeout=120)
        if rc != 0:
            return 're2c', msg, ''
        with open(out, encoding='utf-8', errors='replace') as f:
            gen = f.read()
        # Untranslated diagnostics with ASCII quotes.
        env = dict(os.environ, LC_ALL='C', LANG='C')
        if lang == 'go':
            # Stand-alone file outside of any module, no network access.
            env.update(GOTOOLCHAIN='local', GOPROXY='off', GOFLAGS='')
            rc, msg = run([ctx['go'], 'build', '-o', os.devnull, out],
                cwd=d, env=env)
        else:
            rc, msg = run([ctx['cc'], '-std=c99', '-fsyntax-only',
                '-Werror=implicit-function-declaration', out], cwd=d,
                env=env)
        return ('compile' if rc != 0 else 'ok'), msg, gen
    finally:
        shutil.rmtree(d, ignore_errors=True)


def match_known_failure(entry, msg, gen):
    """Check a compiler output against a known failure. Return None if it
    matches, otherwise the reason why it does not."""
    state_re = re.compile(r'\b(%s)\b' % '|'.join(OPAQUE_STATE_NAMES))
    state = state_re.search(msg)
    if state:
        return 'the compiler output mentions `%s`' % state.group(1)
    # The compiler may stop before it reaches a use of the state (the Go
    # compiler stops on syntax errors), so look for it in the code as well.
    state = state_re.search(GEN_BLANK.sub(' ', gen))
    if state:
        return 'the generated code mentions `%s`' % state.group(1)
    lines = gen.split('\n')
    seen = set()
    for line in msg.split('\n'):
        m = DIAGNOSTIC_RE.match(line)
        if not m:
            if re.search('error', line, re.IGNORECASE) \
                    and not ERROR_SUMMARY_RE.match(line.strip()):
                return 'unparsed compiler error: %s' % line.strip()
            continue
        if m.group('sev') in ('warning', 'note'):
            continue
        n = int(m.group('line'))
        code = lines[n - 1].strip() if 0 < n <= len(lines) else ''
        for i, (diag, src) in enumerate(entry['diagnostics']):
            if re.search(diag, m.group('msg').strip()) \
                    and re.search(src, code):
                seen.add(i)
                break
        else:
            return 'unexpected diagnostic: %s (generated line %d: %s)' \
                % (line.strip(), n, code)
    for i, (diag, src) in enumerate(entry['diagnostics']):
        if i not in seen:
            return 'expected diagnostic did not occur: %s on %s' % (diag,
                src)
    return None


def probe_opaque(opts, tmp):
    """Probe 2. Return the number of failures."""
    langs = ['c'] + (['go'] if opts.go else [])
    scratch = os.path.join(tmp, 'opaque')
    os.makedirs(scratch)
    ctx = {'re2c': opts.re2c, 'cc': opts.cc, 'go': opts.go,
        'scratch': scratch}
    known_failures = {} if opts.no_allowlists else OPAQUE_KNOWN_FAILURES
    cases = opaque_cases(langs)
    with concurrent.futures.ThreadPoolExecutor(opts.jobs) as ex:
        results = list(ex.map(lambda c: opaque_task(ctx, c), cases))

    failed = 0
    compiled = {}
    known = 0
    for case, (status, msg, gen) in zip(cases, results):
        lang, model, flag = case[:3]
        entry = known_failures.get((lang, model, flag))
        key = '%s %s' % (lang, model)
        if status == 'ok' and not entry:
            compiled[key] = compiled.get(key, 0) + 1
            if opts.verbose:
                log('  ok ' + opaque_name(case))
            continue
        why = match_known_failure(entry, msg, gen) \
            if entry and status == 'compile' else None
        if entry and status == 'compile' and why is None:
            known += 1
            log('  known failure %s: %s, compiler output:\n%s'
                % (opaque_name(case), entry['reason'], truncated(msg)))
            continue
        failed += 1
        if status == 'ok':
            what = 'known failure (%s) compiles now, remove it from the ' \
                'list of known failures' % entry['reason']
        elif status == 're2c':
            what = 're2c failed'
        elif entry:
            what = 'compilation failed, not as the known failure (%s): %s' \
                % (entry['reason'], why)
        else:
            what = 'compilation failed'
        log('  FAIL %s: %s, %s output:\n%s' % (opaque_name(case), what,
            're2c' if status == 're2c' else 'compiler', truncated(msg)))
    log('opaque: %d cases, %d compiled, %d known failures, %d failed%s'
        % (len(cases), sum(compiled.values()), known, failed,
            '' if opts.go else ' (go not found, Go cases skipped)'))
    log('  compiled per language and code model: ' + ', '.join('%s %d' % kv
        for kv in sorted(compiled.items())))
    return failed


# Self-test -------------------------------------------------------------------

SELFTEST_RE = """// re2c $INPUT -o $OUTPUT
/*!re2c
    re2c:yyfill:enable = 0;
    re2c:YYCTYPE = char;
    [a]+ { return 1; }
    *    { return 0; }
*/
"""

# Probe 1: an untagged redefinition of `code:yyskip`, appended to the derived
# syntax file. It stands for code emitted bypassing the templates (the probe
# tags every template of the reference syntax file, so the only way to get
# untagged code without changing re2c is to inject it after derivation).
SELFTEST_UNOWNED = ('code:yyskip = topindent "if (1) {}" nl '
    'topindent "++" YYCURSOR ";" nl;\n')

# Probe 2: a template that uses YYCURSOR with the generic API.
SELFTEST_LEAK = 'code:yyskip = topindent "++" YYCURSOR ";" nl;\n'

# Probe 4: a monolithic template planted in the reference syntax file before
# derivation. The owners probe tags its lines like any other template.
SELFTEST_VECTOR_LOOP = '''
code:vector_loop =
    topindent "for (;;) {" nl indent
        topindent "++" YYCURSOR ";" nl
    dedent topindent "}" nl;
'''

# Probe 4: a structural template that owns `yych` accesses only, planted
# with a loop in the reference syntax file (a redefinition that replaces the
# original one).
SELFTEST_YYDEBUG_LOOP = '''
code:yydebug = topindent "for (;;) {}" nl;
'''

# Probe 2: compiler outputs of a known failure (as printed by the Go compiler
# and by Clang), and generated code in which a state identifier is either
# only in a comment and a string, or used.
SELFTEST_GO_GEN = '''package main
// YYCURSOR is not in scope.
var msg = "YYCURSOR is not in scope"
var yybm = {
	0, 1,
}
%s
'''
SELFTEST_GO_MSG = '''# command-line-arguments
./"/tmp/lexer.go":4: syntax error: unexpected {, expected expression
./"/tmp/lexer.go":6: syntax error: unexpected } after top level declaration
'''
SELFTEST_C_GEN = '''int lex(unsigned char yych)
{
    if (yybm[0+yych] & 128) {
        return 1;
    }
    return 0;
}
'''
SELFTEST_C_MSG = '''lexer.c:3:9: error: use of undeclared identifier 'yybm'
    3 |     if (yybm[0+yych] & 128) {
      |         ^
%s1 error generated.
'''

SELFTEST_OPT_H = """
#define RE2C_CODE_TEMPLATES \\
    CODE_TEMPLATE(foo, ({}), ({}), ({})) \\
    CODE_TEMPLATE(bar, ({}), ({}), ({})) \\
    %s
"""

# Probe 3: a render case that calls a sibling of the template admitted for
# its kind (code:var_global instead of code:var_local), and the positive
# counterpart that only calls the admitted template.
SELFTEST_VAR_OPT_H = """
#define RE2C_CODE_TEMPLATES \\
    CODE_TEMPLATE(var_local, ({}), ({}), ({})) \\
    CODE_TEMPLATE(var_global, ({}), ({}), ({}))
"""

SELFTEST_VAR_RENDER = """
static void render(RenderContext& rctx, const Code* code) {
    switch (code->kind) {
    case CodeKind::VAR: {
        if (rctx.local) {
            rctx.opts->render_code_var_local(rctx.os);
        } else {
            rctx.opts->render_code_%s(rctx.os);
        }
        break;
    }
    }
}
"""

SELFTEST_RENDER = """
static void render(RenderContext& rctx, const Code* code) {
    switch (code->kind) {
    case CodeKind::FOO:
        rctx.opts->render_code_foo(rctx.os);
        break;
    case CodeKind::BAR: {
        rctx.opts->render_code_%s(rctx.os);
        break;
    }
    }
}
"""


def self_test(opts, tmp):
    """Check that each probe accepts a good input and rejects a bad one.
    Return the number of witnesses that behave unexpectedly."""
    quiet = argparse.Namespace(**vars(opts))
    quiet.verbose = False
    quiet.keep = False
    results = []

    def witness(name, ok, detail):
        results.append(ok)
        log('self-test: %s: %s (%s)' % (name, 'OK' if ok else 'UNEXPECTED',
            detail))

    # Probe 1: the failure must come from findings, not from re2c errors.
    tests = {'selftest.re': SELFTEST_RE,
        'selftest.c': '/* Generated by re2c */'}
    for name, extra, expect in (('owners, positive', None, False),
            ('owners, negative', SELFTEST_UNOWNED, True)):
        d = tempfile.mkdtemp(dir=tmp)
        nfail, failed = probe_owners(quiet, d, tests=tests,
            extra_syntax={'c': extra} if extra else None, expect_analyzed=1)
        kinds = sorted(set(k for r in failed for _, k, _ in r['findings']))
        if expect:
            ok = nfail == 1 and len(failed) == 1 \
                and failed[0]['status'] == 'analyzed' \
                and kinds == ['control flow `if`', 'cursor move']
        else:
            ok = nfail == 0
        witness(name, ok, '%d failure(s), findings: %s, expected %s' % (
            nfail, ', '.join(kinds) or 'none', 'control flow `if` and '
            'cursor move in an analyzed file' if expect else 'none'))

    # Probe 4: the planted template goes through the owner derivation, which
    # tags it, and the template probe must report it.
    syntaxes = read_syntaxes()
    for name, plant, expect in (('templates, positive', '', False),
            ('templates, negative', SELFTEST_VECTOR_LOOP, True)):
        fname, text = syntaxes['c']
        planted = dict(syntaxes, c=(fname, text + plant))
        _, _, failures = check_templates(planted, STRUCTURAL_TEMPLATES)
        for f in failures:
            log('    ' + f)
        if expect:
            owned = '<<owner:vector_loop>>' in owner_syntax(text + plant)
            ok = owned and len(failures) == 1 \
                and 'code:vector_loop emits control flow `for`, cursor ' \
                    'move but is not a structural template' in failures[0]
            detail = 'derived syntax tags vector_loop: %s, %d failure(s), ' \
                'expected exactly code:vector_loop' % (owned, len(failures))
        else:
            ok = not failures
            detail = '%d failure(s), expected none' % len(failures)
        witness(name, ok, detail)

    # Probe 4: a structural template that emits a category of constructs
    # outside of its admitted categories.
    fname, text = syntaxes['c']
    planted = dict(syntaxes, c=(fname, text + SELFTEST_YYDEBUG_LOOP))
    _, _, failures = check_templates(planted, STRUCTURAL_TEMPLATES)
    for f in failures:
        log('    ' + f)
    expected = 'code:yydebug emits control flow `for` outside of its ' \
        'admitted categories (yych access)'
    witness('templates, category', len(failures) == 1
        and failures[0].startswith(fname + ':')
        and failures[0].endswith(expected), '%d failure(s), expected '
            'exactly: %s' % (len(failures), expected))

    # Probe 2.
    ctx = {'re2c': opts.re2c, 'cc': opts.cc, 'go': None, 'scratch': tmp}
    case = ('c', 'goto-label', '', False, False)
    for name, syntax, expect in (('opaque, positive', None, False),
            ('opaque, negative', SELFTEST_LEAK, True)):
        status, msg, _ = opaque_task(ctx, case, syntax)
        if status == 're2c' or (status == 'compile' and not expect):
            log(truncated(msg))
        if status == 'compile' and expect:
            log(textwrap.indent('\n'.join(l for l in msg.split('\n')
                if 'YYCURSOR' in l), '    '))
        if expect:
            ok = status == 'compile' and 'YYCURSOR' in msg
        else:
            ok = status == 'ok'
        witness(name, ok, 'status %s, expected %s' % (status,
            'a compilation error about YYCURSOR' if expect else 'ok'))

    # Probe 2: a known failure is accepted only if the generated code does
    # not use a state identifier (outside of comments and strings), and if
    # every line of the compiler output that mentions an error is parsed.
    go_entry = OPAQUE_KNOWN_FAILURES[('go', 'recursive-functions', '-b')]
    c_entry = OPAQUE_KNOWN_FAILURES[('c', 'recursive-functions', '-b')]
    for name, entry, msg, gen, expected in (
            ('opaque known failure, positive', go_entry, SELFTEST_GO_MSG,
                SELFTEST_GO_GEN % '', None),
            ('opaque known failure, state in the code', go_entry,
                SELFTEST_GO_MSG, SELFTEST_GO_GEN % 'func f() { YYCURSOR++ }',
                'the generated code mentions `YYCURSOR`'),
            ('opaque known failure, error count', c_entry,
                SELFTEST_C_MSG % '', SELFTEST_C_GEN, None),
            ('opaque known failure, unparsed error', c_entry,
                SELFTEST_C_MSG % "lexer.c(3): error C2065: 'yybm': "
                    "undeclared identifier\n", SELFTEST_C_GEN,
                "unparsed compiler error: lexer.c(3): error C2065: 'yybm': "
                    "undeclared identifier")):
        why = match_known_failure(entry, msg, gen)
        witness(name, why == expected, 'got: %s, expected: %s' % (
            why or 'accepted', expected or 'accepted'))

    # Probe 3: `bar` is allowed to have no caller, which must not exempt the
    # case that renders the wrong template.
    enum = ['FOO', 'BAR']
    for name, extra, call, allow, expect in (
            ('registry, positive', '', 'bar', {}, False),
            ('registry, negative', 'CODE_TEMPLATE(baz, ({}), ({}), ({}))',
                'foo', {'bar': ''}, True)):
        render = SELFTEST_RENDER % call
        res = check_registry(SELFTEST_OPT_H % extra, {'render.cc': render},
            enum, 'render.cc', allow, {}, {})
        for f in res['failures']:
            log('    ' + f)
        expected = ['template `baz` has no render_code_baz or gen_code_baz '
            'call in src/', 'render.cc:7: case CodeKind::BAR calls '
            'render_code_foo'] if expect else []
        witness(name, res['failures'] == expected, '%d failure(s), expected '
            '%s' % (len(res['failures']), '; '.join(expected) or 'none'))

    # Probe 3: a call to a template of the same prefix that the families
    # table does not admit for the kind (exact matching, no prefix match).
    names = {'VAR': REGISTRY_KIND_FAMILIES['VAR']}
    for name, call, expect in (('registry family, positive', 'var_local',
                False),
            ('registry family, negative', 'var_global', True)):
        res = check_registry(SELFTEST_VAR_OPT_H, {'render.cc':
            SELFTEST_VAR_RENDER % call}, ['VAR'], 'render.cc',
            {'var_global': ''} if not expect else {}, {}, names)
        for f in res['failures']:
            log('    ' + f)
        named = sorted(set(msg for _, msg in res['named']))
        expected = ['render.cc:4: case CodeKind::VAR calls '
            'render_code_var_global'] if expect else []
        ok = res['failures'] == expected and named == ['render.cc:4: case '
            'CodeKind::VAR calls render_code_var_local']
        witness(name, ok, '%d failure(s), family applied to var_local: %s, '
            'expected %s' % (len(res['failures']), bool(named),
                '; '.join(expected) or 'none'))

    # Probe 3: the real sources with the template block renamed, truncated
    # to 10 templates, or without the CodeKind enum must fail, rather than
    # pass on nothing.
    opt_h, constants_h, sources = read_registry_sources()
    block = re.search(r'^#define RE2C_CODE_TEMPLATES\b(?:.*\\\n)*.*$',
        opt_h, re.MULTILINE).group()
    cut = [m.start() for m in re.finditer(r'\bCODE_TEMPLATE\(', block)][10]
    truncated_opt_h = opt_h.replace(block, block[:cut].rstrip(' \\\n'))
    kinds = code_kinds(constants_h)
    for name, alt_opt_h, alt_kinds, expected in (
            ('registry, no template block', opt_h.replace(
                '#define RE2C_CODE_TEMPLATES',
                '#define RE2C_CODE_TEMPLATE_LIST'), kinds,
                ['src/options/opt.h: no `#define RE2C_CODE_TEMPLATES` block '
                    'found']),
            ('registry, truncated template block', truncated_opt_h, kinds,
                ['src/options/opt.h: only %d CODE_TEMPLATE entries in '
                    'RE2C_CODE_TEMPLATES, expected at least %d'
                    % (10, REGISTRY_MIN_TEMPLATES)]),
            ('registry, no CodeKind enum', opt_h, code_kinds(
                constants_h.replace('enum class CodeKind',
                    'enum class CodeKindRenamed')),
                ['src/constants.h: no `enum class CodeKind` found'])):
        res = check_registry(alt_opt_h, sources, alt_kinds, RENDER_FILE,
            REGISTRY_ALLOWLIST, REGISTRY_KNOWN_MISMATCHES, registry_names(),
            REGISTRY_MIN_TEMPLATES, REGISTRY_MIN_CASES)
        # Only the failures about the read sources matter here (with fewer
        # templates, the allowlist may not apply).
        found = [f for f in res['failures'] if f.startswith('src/options/'
            'opt.h:') or f.startswith('src/constants.h:')]
        for f in res['failures']:
            log('    ' + f)
        witness(name, found == expected, '%d failure(s), expected %s'
            % (len(res['failures']), '; '.join(expected)))

    # Probe 3: the render switch truncated before `case CodeKind::ASSIGN`
    # must fail on the lower bound of render cases.
    render = sources[RENDER_FILE]
    cut = render.index('case CodeKind::ASSIGN:', render.index(
        'static void render(RenderContext'))
    alt = dict(sources)
    alt[RENDER_FILE] = render[:cut] + '}\n}\n'
    res = check_registry(opt_h, alt, kinds, RENDER_FILE, REGISTRY_ALLOWLIST,
        {}, {}, REGISTRY_MIN_TEMPLATES, REGISTRY_MIN_CASES)
    expected = 'only %d render cases found, expected at least %d' \
        % (res['ncases'], REGISTRY_MIN_CASES)
    log('    ' + expected if expected in res['failures'] else
        '    (no failure about the number of render cases)')
    witness('registry, truncated render switch', res['ncases'] <
        REGISTRY_MIN_CASES and expected in res['failures'], '%d render '
            'case(s) left, %d failure(s) (also templates without a caller '
            'and CodeKind values without a case), expected among them: %s'
            % (res['ncases'], len(res['failures']), expected))

    return results.count(False)


# Main ------------------------------------------------------------------------

PROBES = ['owners', 'templates', 'opaque', 'registry']


def parse_args():
    parser = argparse.ArgumentParser(description='Code generation probes '
        '(owner tags, structural templates, opaque generic API, template '
        'registry).')
    parser.add_argument('--re2c', default='__build/re2c',
        help='re2c executable (default: %(default)s)')
    parser.add_argument('--cc', default=os.environ.get('CC', 'cc'),
        help='C compiler (default: $CC or cc)')
    parser.add_argument('--go', default=None,
        help='Go toolchain (default: go if found in PATH, otherwise the Go '
            'cases are skipped)')
    parser.add_argument('--jobs', type=int, default=os.cpu_count() or 1,
        help='number of parallel jobs (default: %(default)s)')
    parser.add_argument('--self-test', action='store_true',
        help='check that each probe accepts a good and rejects a bad input')
    parser.add_argument('--only', choices=PROBES,
        help='run only one probe')
    parser.add_argument('--keep', action='store_true',
        help='keep temporary files (including probed outputs)')
    parser.add_argument('--no-allowlists', action='store_true',
        help='debug: do not apply the lists of templates allowed to have no '
            'caller, of known render case mismatches and of known opaque '
            'compilation failures, and list the applied render case aliases '
            'and families')
    parser.add_argument('--verbose', action='store_true',
        help='list skipped files, compiled cases and structural templates')
    return parser.parse_args()


def find_program(path, what):
    found = shutil.which(path)
    if not found and not os.path.isabs(path):
        found = shutil.which(os.path.join(ROOT, path))
    if not found:
        log('error: %s not found: %s' % (what, path))
        sys.exit(2)
    return os.path.abspath(found)


def main():
    opts = parse_args()
    if opts.jobs < 1:
        log('error: --jobs must be positive')
        return 2
    probes = [opts.only] if opts.only else PROBES
    if opts.self_test or 'owners' in probes or 'opaque' in probes:
        opts.re2c = find_program(opts.re2c, 're2c')
    if opts.self_test or 'opaque' in probes:
        opts.cc = find_program(opts.cc, 'C compiler')
        if opts.go:
            opts.go = find_program(opts.go, 'Go toolchain')
        else:
            opts.go = shutil.which('go')

    tmp = tempfile.mkdtemp(prefix='re2c_codegen_probes_')
    try:
        if opts.self_test:
            nfail = self_test(opts, tmp)
            log('self-test: %s' % ('PASS' if nfail == 0
                else '%d witness(es) failed' % nfail))
            return 0 if nfail == 0 else 1

        status = {}
        for p in probes:
            if p == 'owners':
                status[p] = probe_owners(opts, os.path.join(tmp, p))[0]
            elif p == 'templates':
                status[p] = probe_templates(opts)
            elif p == 'opaque':
                status[p] = probe_opaque(opts, tmp)
            else:
                status[p] = probe_registry(opts)
        log('summary: ' + ', '.join('%s %s' % (p, 'PASS' if n == 0
            else 'FAIL') for p, n in status.items()))
        return 0 if all(n == 0 for n in status.values()) else 1
    finally:
        if opts.keep:
            log('temporary files kept in ' + tmp)
        else:
            shutil.rmtree(tmp, ignore_errors=True)


if __name__ == '__main__':
    sys.exit(main())
