// re2c $INPUT -o $OUTPUT -i
/*!re2c
re2c:api:style = functions;
re2c:define:YYLESSTHAN   = "lessthan";
re2c:define:YYFILL       = "fill";
re2c:define:YYPEEK       = "peek";
re2c:define:YYSKIP       = "skip";
re2c:define:YYBACKUP     = "backup";
re2c:define:YYRESTORE    = "restore";
re2c:define:YYBACKUPCTX  = "backupctx";
re2c:define:YYRESTORECTX = "restorectx";
re2c:define:YYRESTORETAG = "restoretag";
re2c:define:YYSTAGP      = "stagp";
re2c:define:YYSTAGN      = "stagn";
re2c:define:YYMTAGP      = "mtagp";
re2c:define:YYMTAGN      = "mtagn";
re2c:define:YYSHIFT      = "shift";
re2c:define:YYSHIFTSTAG  = "shiftstag";
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
