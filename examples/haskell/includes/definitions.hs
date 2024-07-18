data Number = INum | FNum | NNaN deriving (Eq)

%{
    number = [1-9][0-9]*;
%}
