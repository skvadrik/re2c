// re2c $INPUT -o $OUTPUT -i --loop-switch

%{
  re2c:eof = 0;

  !entry { /* init ... */ }
  [^]    { return ^; }
  $      { return $; }
%}
