# re2py $INPUT -o $OUTPUT

from time import time

/*!rules:re2c:x
    re2c:api = custom;
    re2c:define:YYPEEK    = "str[cur]";
    re2c:define:YYSKIP    = "cur += 1";
    re2c:define:YYBACKUP  = "mar = cur";
    re2c:define:YYRESTORE = "cur = mar";
    re2c:yyfill:enable = 0;
    re2c:indent:top = 1;

    id = [a-zA-Z_][a-zA-Z0-9_]*;

    id { return True }
    *  { return False }
*/

def lex_switch_cases(str):
    cur = 0
    /*!use:re2c:x
        re2c:nested-ifs = 0;
    */

def lex_nested_ifs(str):
    cur = 0
    /*!use:re2c:x*/

STR = b"01234567890123456789012345678901234567890123456789012345678901234567890123456789\0"
TIMES = 1000000

start = time()
for i in range(TIMES):
    lex_nested_ifs(STR)
end = time()
print("nested ifs took {}".format(end - start))

start = time()
for i in range(TIMES):
    lex_switch_cases(STR)
end = time()
print("switch cases took {}".format(end - start))
