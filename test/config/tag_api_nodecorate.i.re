/*!re2c
re2c:decorate = 0;
re2c:define:YYLESSTHAN   = "lim - cur < @@";
re2c:define:YYFILL       = "fill(@@);";
re2c:define:YYPEEK       = "*cur";
re2c:define:YYSKIP       = "++cur;";
re2c:define:YYBACKUP     = "mar = cur;";
re2c:define:YYRESTORE    = "cur = mar;";
re2c:define:YYBACKUPCTX  = "ctx = cur;";
re2c:define:YYRESTORECTX = "cur = ctx;";
re2c:define:YYRESTORETAG = "cur = @@;";
re2c:define:YYSTAGP      = "@@ = cur;";
re2c:define:YYSTAGN      = "@@ = NULL;";
re2c:define:YYMTAGP      = "mtag(&@@, cur);";
re2c:define:YYMTAGN      = "mtag(&@@, NULL);";
re2c:define:YYSHIFT      = "cur += @@;";
re2c:define:YYSHIFTSTAG  = "@@1 += @@2;";
*/

// stags, default API
/*!re2c
re2c:flags:tags = 1;
re2c:flags:input = default;
(@x [a])* @y @z [a] { a }
*                   { * }
*/

// stags, generic API
/*!re2c
re2c:flags:tags = 1;
re2c:flags:input = custom;
(@x [a])* @y @z [a] { a }
*                   { * }
*/

// mtags, default API
/*!re2c
re2c:flags:tags = 1;
re2c:flags:input = default;
(#x [a])* #y #z [a] { a }
*                   { * }
*/

// mtags, generic API
/*!re2c
re2c:flags:tags = 1;
re2c:flags:input = custom;
(#x [a])* #y #z [a] { a }
*                   { * }
*/

// trailing context, default API
/*!re2c
re2c:flags:input = default;
re2c:flags:tags = 1;
[a]* / [a]+              { a }
[b]* / [b]               { b }
[c]* / @x @y [c] @z [c]+ { c }
*/

// trailing context, generic API
/*!re2c
re2c:flags:input = custom;
re2c:flags:tags = 1;
[a]* / [a]+              { a }
[b]* / [b]               { b }
[c]* / @x @y [c] @z [c]+ { c }
*/

// trailing context (old-style), default API
/*!re2c
re2c:flags:input = default;
re2c:flags:tags = 0;
[a]* / [a]+ { a }
[b]* / [b]  { b }
*/

// trailing context (old-style), generic API
/*!re2c
re2c:flags:input = custom;
re2c:flags:tags = 0;
[a]* / [a]+ { a }
[b]* / [b]  { b }
*/
