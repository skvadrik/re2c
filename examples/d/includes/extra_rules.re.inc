// floating-point numbers
frac  = [0-9]* "." [0-9]+ | [0-9]+ ".";
exp   = 'e' [+-]? [0-9]+;
float = frac exp? | [0-9]+ exp;

float { return Result.OK; }
