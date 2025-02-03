// re2c $INPUT -o $OUTPUT

// ok, end of block
/*!stags:re2c*/
%{stags%}

// ok, space
/*!stags:re2c */
%{stags %}

// ok, space
/*!stags:re2c	*/
%{stags	%}

// ok, newline
/*!stags:re2c
*/
%{stags
%}

// bad
/*!stags:re2cx */
