# re2py $INPUT -o $OUTPUT

# This example shows how to combine reusable re2c blocks: two blocks
# ('colors' and 'fish') are merged into one. The 'salmon' rule occurs
# in both blocks; the 'fish' block takes priority because it is used
# earlier. Default rule * occurs in all three blocks; the local (not
# inherited) definition takes priority.

from enum import Enum

class Ans(Enum):
    COLOR = 1
    FISH = 2
    DUNNO = 3

%{rules:colors
    *                            { raise "ah" }
    "red" | "salmon" | "magenta" { return Ans.COLOR }
%}

%{rules:fish
    *                            { raise "oh" }
    "haddock" | "salmon" | "eel" { return Ans.FISH }
%}

def lex(yyinput):
    yycursor = 0
%{
    re2c:yyfill:enable = 0;
    re2c:indent:top = 1;

    !use:fish;
    !use:colors;
    * { return Ans.DUNNO } // overrides inherited '*' rules
%}

assert lex(b"salmon") == Ans.FISH
assert lex(b"what?") == Ans.DUNNO
