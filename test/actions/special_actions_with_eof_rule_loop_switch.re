// re2c $INPUT -o $OUTPUT -i --loop-switch

%{
  re2c:eof = 0;

  !entry     { /* entry ... */ }
  !pre_rule  { /* pre_rule ... */ }
  !post_rule { /* post_rule ... */ }

  [^] { return ^; }
  $   { return $; }
%}
