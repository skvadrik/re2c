#!/usr/bin/env python3
"""Generate linear-vectorization scanners and deterministic fixtures (seed 586)."""
import argparse
import hashlib
import json
from pathlib import Path
import random
import re
import shutil
import subprocess

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
    + [(r'[a-zA-Z0-9-]+ ":"', r"[a-zA-Z0-9-]+:", 9),
       (r'" " [^\r\n\x00]* "\r"? "\n"', r" [^\r\n\x00]*\r?\n", 10)],
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


def build_fixtures():
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
    for case in fixtures:
        case['traces'] = [oracle(text, case['family']) for text in case['records']]
    return fixtures


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--re2go", required=True, help="Path to re2go binary (generates Go scanners)")
    parser.add_argument("--out", default="generated", help="Output directory")
    args = parser.parse_args()

    re2go_bin = shutil.which(args.re2go) or args.re2go
    re2go_path = Path(re2go_bin).resolve()
    if not re2go_path.is_file():
        raise SystemExit(f"re2go binary not found: {args.re2go}")

    out = Path(args.out).resolve()
    out.mkdir(parents=True, exist_ok=True)
    assert oracle('SELECT SELECTED FROMAGE', 'sql') == [[1, 6], [8, 1], [7, 8], [8, 1], [7, 7]]
    assert oracle('Content-Type: x\r\nX-Test-2:', 'http') == [[2, 13], [10, 4], [9, 9]]

    fixtures = build_fixtures()
    manifest = {
        "seed": 586,
        "records": {case["name"]: len(case["records"]) for case in fixtures},
        "commands": [],
        "sha256": {},
    }
    controls = {}

    for family in RULES:
        for linear in (0, 1):
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
    re2c:YYLIMIT = "len(yyinput)";
    re2c:vectorize:linear = {linear};
    "\\x00" {{ return 0, yycursor - 1 }}
    {rules}
    */
}}
'''
            path = out / f"{name}.re"
            path.write_text(source)
            go_path = path.with_suffix('.go')
            flags = ["--api", "simple", "-W", "-i", "--no-generation-date", "--no-version"]
            subprocess.run([str(re2go_path), *flags, str(path), "-o", str(go_path)], check=True)
            manifest["commands"].append([re2go_path.name, *flags, path.name, "-o", go_path.name])
        texts = [(out / f'{family}_{v}.go').read_text().replace(f'{family}_{v}', 'lex') for v in (0, 1)]
        controls[f'go_{family}_identical'] = texts[0] == texts[1]
    (out / "variants.go").write_text('''package generated
type Variant struct { Name, Family string; Lex func(string, int) (int, int) }
var Variants = []Variant{
    {"http_0", "http", http_0}, {"http_1", "http", http_1},
    {"sql_0", "sql", sql_0}, {"sql_1", "sql", sql_1},
}
''')

    (out / 'fixtures.json').write_text(json.dumps(fixtures, indent=1) + '\n')
    (out / 'codegen-checks.json').write_text(json.dumps(controls, indent=2) + '\n')
    assert controls == {"go_http_identical": False, "go_sql_identical": True}, controls

    for path in sorted(out.rglob('*')):
        if path.name != 'manifest.json' and path.is_file():
            manifest['sha256'][str(path.relative_to(out))] = hashlib.sha256(path.read_bytes()).hexdigest()
    manifest['sha256'][re2go_path.name] = hashlib.sha256(re2go_path.read_bytes()).hexdigest()
    (out / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n')


if __name__ == '__main__':
    main()
