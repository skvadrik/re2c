# re2py $INPUT -o $OUTPUT

from collections import namedtuple

SemVer = namedtuple('SemVer', 'major minor patch')

NONE = -1

def parse(yyinput):
    yycursor = 0
%{
    re2c:yyfill:enable = 0;
    re2c:captvars = 1;
    re2c:indent:top = 1;

    num = [0-9]+;

    (num) "." (num) ("." num)? [\x00] {
        major = int(yyinput[yytl1:yytr1])
        minor = int(yyinput[yytl2:yytr2])
        patch = 0 if yytl3 == NONE else int(yyinput[yytl3 + 1:yytr3])
        return SemVer(major, minor, patch)
    }
    * { return None }
%}

assert parse(b"23.34\0") == SemVer(23, 34, 0)
assert parse(b"1.2.99999\0") == SemVer(1, 2, 99999)
assert parse(b"1.a\0") == None
