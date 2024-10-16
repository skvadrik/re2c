// re2c $INPUT -o $OUTPUT

// ok, end of block
/*!ignore:re2c*/
%{ignore%}

// ok, space
/*!ignore:re2c */
%{ignore %}

// ok, space
/*!ignore:re2c	*/
%{ignore	%}

// ok, newline
/*!ignore:re2c
*/
%{ignore
%}

// bad
/*!ignore:re2cx */
