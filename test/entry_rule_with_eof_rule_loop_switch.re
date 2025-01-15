// re2c $INPUT -o $OUTPUT -i --loop-switch

%{
  re2c:eof = 0;

  ^   { /* init ... */ }
  [^] { return ^; }
  $   { return $; }
%}
