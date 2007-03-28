/*!re2c

space_ = "a";
_space = "b";
s_pace = "c";
_      = "d";

space_  { return 'a'; }
_space  { return 'b'; }
s_pace  { return 'c'; }
_       { return 'd'; }
[^]     { return '\0'; }

*/
