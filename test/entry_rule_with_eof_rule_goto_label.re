// re2c $INPUT -o $OUTPUT -i

%{
  re2c:eof = 0;

  !entry { /* init ... */ }
  [^]    { return ^; }
  $      { return $; }
%}
