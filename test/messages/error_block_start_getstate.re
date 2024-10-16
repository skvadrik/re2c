// re2c $INPUT -o $OUTPUT -f

// ok, end of block
/*!getstate:re2c*/
%{getstate:re2c%}

// ok, space
/*!getstate:re2c */
%{getstate:re2c %}

// ok, space
/*!getstate:re2c	*/
%{getstate:re2c	%}

// ok, newline
/*!getstate:re2c
*/
%{getstate:re2c
%}

// bad
/*!getstate:re2cx */
