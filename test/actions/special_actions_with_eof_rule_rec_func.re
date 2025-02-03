// re2c $INPUT -o $OUTPUT -i --recursive-functions

%{
  re2c:YYFN = ["lex;int"];
  re2c:eof = 0;

  !entry     { /* entry ... */ }
  !pre_rule  { /* pre_rule ... */ }
  !post_rule { /* post_rule ... */ }

  [^] { return ^; }
  $   { return $; }
%}
