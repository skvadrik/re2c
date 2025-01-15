// re2c $INPUT -o $OUTPUT -i

%{
  re2c:eof = 0;

  ^   { /* init ... */ }
  [^] { return ^; }
  $   { return $; }
%}
