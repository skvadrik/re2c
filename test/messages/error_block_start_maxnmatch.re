// re2c $INPUT -o $OUTPUT

// ok, end of block
/*!maxnmatch:re2c*/
%{maxnmatch%}

// ok, space
/*!maxnmatch:re2c */
%{maxnmatch %}

// ok, space
/*!maxnmatch:re2c	*/
%{maxnmatch	%}

// ok, newline
/*!maxnmatch:re2c
*/
%{maxnmatch
%}

// bad
/*!maxnmatch:re2cx */
