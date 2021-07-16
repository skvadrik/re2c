// re2c $INPUT -o $OUTPUT

// ok, different ways to specify include directive
/*!re2c !include "include006.re.inc"	; !include	"include006.re.inc" ;
    !include "include006.re.inc";
	!include	"include006.re.inc"	;
!include "include006.re.inc";*/

// syntax error at line 11, include directive without a semicolon
/*!re2c
    !include "include006.re.inc"
*/
