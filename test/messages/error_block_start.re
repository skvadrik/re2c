// re2c $INPUT -o $OUTPUT

// ok, end of block
/*!re2c*/
%{%}

// ok, space
/*!re2c */
%{ %}

// ok, space
/*!re2c	*/
%{	%}

// ok, newline
/*!re2c
*/
%{
%}

// bad
/*!re2c"a"{} */
