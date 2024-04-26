# re2py $INPUT -o $OUTPUT

from collections import namedtuple

SemVer = namedtuple('SemVer', 'major minor patch')

NONE = -1

def parse(str):
    cur = 0
    /*!re2c
        re2c:define:YYPEEK      = "str[cur]";
        re2c:define:YYSKIP      = "cur += 1";
        re2c:define:YYBACKUP    = "mar = cur";
        re2c:define:YYRESTORE   = "cur = mar";
        re2c:define:YYSETSTAGP  = "@@{tag} = cur";
        re2c:define:YYSETSTAGN  = "@@{tag} = NONE";
        re2c:define:YYSHIFTSTAG = "@@{tag} += @@{shift}";
        re2c:yyfill:enable = 0;
        re2c:tags = 1;
        re2c:indent:top = 1;

        num = [0-9]+;

        @t1 num @t2 "." @t3 num @t4 ("." @t5 num)? [\x00] {
            major = int(str[t1:t2]);
            minor = int(str[t3:t4]);
            patch = int(str[t5:cur - 1]) if t5 != NONE else 0
            return SemVer(major, minor, patch)
        }
        * { return None }
    */

assert parse(b"23.34\0") == SemVer(23, 34, 0)
assert parse(b"1.2.99999\0") == SemVer(1, 2, 99999)
assert parse(b"1.a\0") == None
