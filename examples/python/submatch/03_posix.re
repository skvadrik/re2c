# re2py $INPUT -o $OUTPUT

from collections import namedtuple

SemVer = namedtuple('SemVer', 'major minor patch')

# Maximum number of capturing groups among all rules.
/*!maxnmatch:re2c*/
NONE = -1

def parse(str):
    cur = 0

    # A list for capturing parentheses (twice the number of groups).
    yypmatch = [None] * (YYMAXNMATCH * 2)

    /*!re2c
        re2c:define:YYPEEK      = "str[cur]";
        re2c:define:YYSKIP      = "cur += 1";
        re2c:define:YYBACKUP    = "mar = cur";
        re2c:define:YYRESTORE   = "cur = mar";
        re2c:define:YYSETSTAGP  = "@@{tag} = cur";
        re2c:define:YYSETSTAGN  = "@@{tag} = NONE";
        re2c:define:YYSHIFTSTAG = "@@{tag} += @@{shift}";
        re2c:yyfill:enable = 0;
        re2c:posix-captures = 1;
        re2c:indent:top = 1;

        num = [0-9]+;

        (num) "." (num) ("." num)? [\x00] {
            # `yynmatch` is the number of capturing groups
            assert yynmatch == 4

            # Even `yypmatch` values are for opening parentheses, odd values
            # are for closing parentheses, the first group is the whole match.
            major = int(str[yypmatch[2]:yypmatch[3]])
            minor = int(str[yypmatch[4]:yypmatch[5]])
            patch = 0 if yypmatch[6] == NONE else int(str[yypmatch[6] + 1:yypmatch[7]])
            return SemVer(major, minor, patch)
        }
        * { return None }
    */

assert parse(b"23.34\0") == SemVer(23, 34, 0)
assert parse(b"1.2.99999\0") == SemVer(1, 2, 99999)
assert parse(b"1.a\0") == None
