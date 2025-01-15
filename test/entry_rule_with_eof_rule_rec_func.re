// re2c $INPUT -o $OUTPUT -i --recursive-functions

%{
  re2c:YYFN = ["lex;int"];
  re2c:eof = 0;

  ^   { /* init ... */ }
  [^] { return ^; }
  $   { return $; }
%}
