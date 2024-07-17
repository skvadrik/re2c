# re2py $INPUT -o $OUTPUT --header lexer/state.py

from lexer.state import State

%{header:on %}
class State:
    def __init__(self, str):
        self.yyinput = str
        self.yycursor = 0
        %{stags format = "\n        self.@@ = 0"; %}
%{header:off %}

def lex(yyrecord):
%{
    re2c:api = record;
    re2c:tags = 1;
    re2c:yyfill:enable = 0;
    re2c:indent:top = 1;
    re2c:header = "lexer/state.py";

    [a]* @t [b]* { return t }
%}

assert lex(State(b"ab\0")) == 1
