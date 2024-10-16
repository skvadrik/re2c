// re2c $INPUT -o $OUTPUT

// ok, end of block
/*!mtags:re2c*/
%{mtags%}

// ok, space
/*!mtags:re2c */
%{mtags %}

// ok, space
/*!mtags:re2c	*/
%{mtags	%}

// ok, newline
/*!mtags:re2c
*/
%{mtags
%}

// bad
/*!mtags:re2cx */
