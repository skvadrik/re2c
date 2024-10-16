// re2c $INPUT -o $OUTPUT

// ok, end of block
/*!max:re2c*/
%{max%}

// ok, space
/*!max:re2c */
%{max %}

// ok, space
/*!max:re2c	*/
%{max	%}

// ok, newline
/*!max:re2c
*/
%{max
%}

// bad
/*!max:re2c1 */
