// re2c $INPUT -o $OUTPUT

/*!rules:re2c*/
/*!rules:re2c:_Yx1*/
/*!rules:re2c:Yx1*/
/*!rules:re2c:yX1*/
/*!rules:re2c:yX1_*/
/*!rules:re2c:_*/

%{rules%}
%{rules:_Zx1%}
%{rules:Zx1%}
%{rules:zX1%}
%{rules:zX1_%}
%{rules:__%}

// ok, end of block
/*!use:re2c*/
/*!use:re2c:_Yx1*/
%{use%}
%{use:_Zx1%}

// ok, space
/*!use:re2c */
/*!use:re2c:Yx1 */
%{use %}
%{use:Zx1 %}

// ok, space
/*!use:re2c	*/
/*!use:re2c:yX1_	*/
%{use	%}
%{use:zX1_	%}

// ok, newline
/*!use:re2c
*/
/*!use:re2c:_
*/
%{use
%}
%{use:__
%}

// bad, empty name
/*!use:re2c: */
