const Num = enum { integer, floating, nan };

%{
    number = [1-9][0-9]*;
%}
