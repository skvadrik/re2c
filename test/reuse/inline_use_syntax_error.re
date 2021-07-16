// re2c $INPUT -o $OUTPUT

// rules block 'x'
/*!rules:re2c:x*/

// ok, different ways to specify use directive
/*!re2c !use:x ; !use:x	;	!use:x;
  !use:x  ;
	!use:x		;
!use:x;*/

// syntax error, use directive without a semicolon
/*!re2c
    !use:x
*/
