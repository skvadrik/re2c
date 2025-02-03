// re2c $INPUT -o $OUTPUT

// ok, end of block
/*!rules:re2c*/
/*!rules:re2c:_Yx1*/
%{rules%}
%{rules:_Zx1%}

// ok, space
/*!rules:re2c */
/*!rules:re2c:Yx1 */
%{rules %}
%{rules:Zx1 %}

// ok, space
/*!rules:re2c	*/
/*!rules:re2c:yX1_	*/
%{rules	%}
%{rules:zX1_	%}

// ok, newline
/*!rules:re2c
*/
/*!rules:re2c:_
*/
%{rules
%}
%{rules:__
%}

// bad, name starts with digit
/*!rules:re2c:1Yx */
