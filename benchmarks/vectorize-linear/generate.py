#!/usr/bin/env python3
"""Generate matched C/Go scanners and deterministic fixtures; no external data writes."""
import argparse
import hashlib
import json
from pathlib import Path
import random
import re
import subprocess

ROOT = Path(__file__).resolve().parent
HEADERS = ["Content-Length:", "Content-Type:", "Transfer-Encoding:",
           "Authorization:", "Accept-Encoding:", "User-Agent:",
           "Cache-Control:", "Connection:"]
KEYWORDS = ["SELECT", "INSERT", "UPDATE", "DELETE", "FROM", "WHERE"]


def re2c_string(s):
    """A re2c string literal. JSON escaping coincides with re2c's only for printable ASCII
    without quotes or backslashes, which is all the literals here are."""
    assert s.isascii() and s.isprintable() and '"' not in s and "\\" not in s, s
    return json.dumps(s)


# Preserve the original SQL identifier rule: do not append delimiters to keywords.
RULES = {
    "http": [(re2c_string(s), re.escape(s), i + 1) for i, s in enumerate(HEADERS)]
    + [(r'[a-zA-Z-]+ ":"', r"[a-zA-Z-]+:", 9),
       (r'" " [^\r\n\x00]* "\r\n"', r" [^\r\n\x00]*\r\n", 10)],
    "sql": [(re2c_string(s), s, i + 1) for i, s in enumerate(KEYWORDS)]
    + [(r"[a-zA-Z_][a-zA-Z0-9_]*", r"[a-zA-Z_][a-zA-Z0-9_]*", 7),
       (r"[ ]+", r" +", 8)],
}


def oracle(text, family):
    patterns = [(re.compile(pattern), kind) for _, pattern, kind in RULES[family]]
    out, pos = [], 0
    while pos < len(text):
        length, kind = 1, 11 if family == "http" else 9
        best = 0
        for pattern, candidate in patterns:
            match = pattern.match(text, pos)
            if match and match.end() - pos > best:
                best = length = match.end() - pos
                kind = candidate
        out.append([kind, length])
        pos += length
    return out


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--re2c", required=True)
    parser.add_argument("--re2go", required=True)
    args = parser.parse_args()
    out = ROOT / "generated"
    out.mkdir(exist_ok=True)
    (out / 'c').mkdir(exist_ok=True)
    manifest = {"seed": 586, "records": 1024, "commands": [], "sha256": {}}
    assert oracle('SELECT SELECTED FROMAGE', 'sql') == [[1, 6], [8, 1], [7, 8], [8, 1], [7, 7]]
    assert oracle('Content-Type: x\r\nX-Test:', 'http') == [[2, 13], [10, 4], [9, 7]]
    declarations, variants = [], []
    for family in RULES:
        for linear in (0, 1):
            for checked in (0, 1):
                name = f"{family}_{linear}_{checked}"
                rules = '\n'.join(f'{rule} {{ *length = in->cur - in->tok; return {kind}; }}'
                                  for rule, _, kind in RULES[family])
                rules += f'\n* {{ *length = in->cur - in->tok; return {11 if family == "http" else 9}; }}'
                source = f'''#include "scanner.h"
/*!max:re2c*/
_Static_assert(YYMAXFILL <= PAD, "increase padding");
int {name}(Input *in, size_t *length) {{
    in->tok = in->mar = in->cur;
    /*!re2c
    re2c:YYCTYPE = "unsigned char";
    re2c:api:style = free-form;
    re2c:YYCURSOR = in->cur;
    re2c:YYMARKER = in->mar;
    re2c:YYLIMIT = in->lim;
    re2c:YYFILL = "if (fill(in, @@)) return -1;";
    re2c:yyfill:enable = {checked};
    re2c:vectorize:linear = {linear};
    "\\x00" {{ *length = 0; return 0; }}
    {rules}
    */
}}
'''
                path = out / 'c' / f"{name}.re"
                path.write_text(source)
                command = [str(Path(args.re2c).resolve()), "-W", "-i", "--no-generation-date",
                           "--no-version", str(path), "-o", str(path.with_suffix('.c'))]
                subprocess.run(command, check=True)
                manifest["commands"].append(command)
                declarations.append(f"int {name}(Input*, size_t*);")
                variants.append(f'{{"{name}", {name}, {str(bool(checked)).lower()}, "{family}"}}')
            name = f"{family}_{linear}"
            rules = '\n'.join(f'{rule} {{ return {kind}, yycursor }}' for rule, _, kind in RULES[family])
            rules += f'\n* {{ return {11 if family == "http" else 9}, yycursor }}'
            source = f'''package generated

func {name}(yyinput string, yycursor int) (int, int) {{
    var yymarker int
    _ = yymarker
    /*!re2c
    re2c:YYCTYPE = byte;
    re2c:yyfill:enable = 0;
    re2c:vectorize:linear = {linear};
    "\\x00" {{ return 0, yycursor - 1 }}
    {rules}
    */
}}
'''
            path = out / f"{name}.re"
            path.write_text(source)
            command = [str(Path(args.re2go).resolve()), "--api", "simple", "-W", "-i",
                       "--no-generation-date", "--no-version", str(path), "-o", str(path.with_suffix('.go'))]
            subprocess.run(command, check=True)
            manifest["commands"].append(command)
    (out / "variants.h").write_text('\n'.join(declarations) +
        '\nstatic const Variant variants[] = {\n' + ',\n'.join(variants) + '\n};\n')
    (out / "variants.go").write_text('''package generated
type Variant struct { Name, Family string; Lex func(string, int) (int, int) }
var Variants = []Variant{
    {"http_0", "http", http_0}, {"http_1", "http", http_1},
    {"sql_0", "sql", sql_0}, {"sql_1", "sql", sql_1},
}
''')
    rng = random.Random(586)
    fixtures = []
    for known in (True, False):
        names = [rng.choice(HEADERS) if known else
                 'X-' + ''.join(rng.choice('abcdefghijklmnopqrstuvwxyz') for _ in range(rng.randrange(4, 24))) + ':'
                 for _ in range(1024)]
        values = [' ' + ''.join(rng.choice('abcdefghijklmnopqrstuvwxyz0123456789')
                              for _ in range(rng.randrange(1, 40))) + '\r\n' for _ in names]
        for mode in ('isolated', 'names', 'values'):
            records = names if mode == 'isolated' else [''.join(
                name + (value if mode == 'values' else '') for name, value in zip(names, values))]
            fixtures.append(dict(name=f'http_{"known" if known else "unknown"}_{mode}', family='http', records=records))
    words = KEYWORDS + ['SELECTED', 'FROMAGE', 'WHEREAS', 'table_42', 'x', '123', ',']
    fixtures.append(dict(name='sql_original', family='sql', records=[
        ' '.join(rng.choice(words) for _ in range(4096))]))
    # Small adversarial inputs are correctness-only, not additional benchmark regimes.
    for family, pool in [('http', HEADERS), ('sql', KEYWORDS)]:
        records = ['']
        for word in pool:
            records.extend(word[:i] for i in range(len(word) + 1))
            records.extend([word + 'X', word[:-1] + '?'])
        fixtures.append(dict(name=family + '_edges', family=family, records=records))
    cdata = []
    for ci, case in enumerate(fixtures):
        case['traces'] = [oracle(text, case['family']) for text in case['records']]
        for ri, (text, trace) in enumerate(zip(case['records'], case['traces'])):
            cdata.append(f'static const unsigned char data_{ci}_{ri}[] = {json.dumps(text)}' + ' "\\0"' * 64 + ';')
            tokens = [f'{{{k},{n}}}' for k, n in trace] + ['{0,0}']
            cdata.append(f'static const Token trace_{ci}_{ri}[] = {{' + ','.join(tokens) + '};')
        cdata.append(f'static const Record records_{ci}[] = {{' + ','.join(
            f'{{data_{ci}_{ri},{len(text)},trace_{ci}_{ri},{len(case["traces"][ri])}}}'
            for ri, text in enumerate(case['records'])) + '};')
    cdata.append('static const Fixture fixtures[] = {' + ','.join(
        f'{{"{case["name"]}","{case["family"]}",records_{ci},{len(case["records"])}}}'
        for ci, case in enumerate(fixtures)) + '};')
    (out / 'fixtures.h').write_text('\n'.join(cdata) + '\n')
    (out / 'fixtures.json').write_text(json.dumps(fixtures, indent=1) + '\n')
    controls = {}
    for family in RULES:
        for checked in (0, 1):
            texts = [(out / 'c' / f'{family}_{v}_{checked}.c').read_text().replace(
                f'{family}_{v}_{checked}', 'lex') for v in (0, 1)]
            controls[f'c_{family}_checked{checked}_identical'] = texts[0] == texts[1]
        texts = [(out / f'{family}_{v}.go').read_text().replace(f'{family}_{v}', 'lex') for v in (0, 1)]
        controls[f'go_{family}_identical'] = texts[0] == texts[1]
    (out / 'codegen-checks.json').write_text(json.dumps(controls, indent=2) + '\n')
    # The benchmark only measures something if the option changes the HTTP scanners (literal
    # header names form linear chains) and leaves the SQL scanners untouched (no chain: the
    # keywords are covered by the identifier rule). Fail loudly otherwise.
    for key, expected in sorted(controls.items()):
        want = key.split('_')[1] == 'sql'
        assert expected == want, f'{key}: {expected}, expected {want}'
    manifest['source_sha256'] = {p.name: hashlib.sha256(p.read_bytes()).hexdigest()
                                 for p in sorted(ROOT.iterdir()) if p.is_file()}
    for path in sorted(out.rglob('*')):
        if path.name != 'manifest.json' and path.is_file():
            manifest['sha256'][str(path.relative_to(out))] = hashlib.sha256(path.read_bytes()).hexdigest()
    for gen in (args.re2c, args.re2go):
        manifest['sha256'][str(Path(gen).resolve())] = hashlib.sha256(Path(gen).read_bytes()).hexdigest()
    (out / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n')


if __name__ == '__main__':
    main()
