# re2py $INPUT -o $OUTPUT

from collections import namedtuple

SemVer = namedtuple('SemVer', 'major minor patch')

NONE = -1

def parse(yyinput):
    yycursor = 0
%{
    re2c:yyfill:enable = 0;
    re2c:tags = 1;
    re2c:indent:top = 1;

    num = [0-9]+;

    @t1 num @t2 "." @t3 num @t4 ("." @t5 num)? [\x00] {
        major = int(yyinput[t1:t2])
        minor = int(yyinput[t3:t4])
        patch = int(yyinput[t5:yycursor - 1]) if t5 != NONE else 0
        return SemVer(major, minor, patch)
    }
    * { return None }
%}

assert parse(b"23.34\0") == SemVer(23, 34, 0)
assert parse(b"1.2.99999\0") == SemVer(1, 2, 99999)
assert parse(b"1.a\0") == None
