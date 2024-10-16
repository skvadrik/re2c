// re2c $INPUT -o $OUTPUT

// ok, end of block
/*!types:re2c*/
/*!conditions:re2c*/
%{types%}
%{conditions%}

// ok, space
/*!types:re2c */
/*!conditions:re2c */
%{types %}
%{conditions %}

// ok, space
/*!types:re2c	*/
/*!conditions:re2c	*/
%{types	%}
%{conditions	%}

// ok, newline
/*!types:re2c
*/
/*!conditions:re2c
*/
%{types
%}
%{conditions
%}

// bad (cyrillic 'с')
/*!types:re2с */
