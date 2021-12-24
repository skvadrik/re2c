// re2c $INPUT -o $OUTPUT

// re2c block that starts with %{ on a new line
%{
    * { return "%{ * {} %}"; } /* %{ %} */ // %{ %}
%}

// re2c block that starts with %{ on a new line with spaces
	  %{
    * := return "%{ * {} %}"; /* %{ %} */ // %{ %}
%}

// not a block, just a %{ in a string
const char *s = "%{ * {} %}";

// re2c erroneously thinks %{ in a string is a block start
const char *s = "begin...\
%{ * {} %}...end";

// not a block, just a %{ in a multiline comment
/* %{ * {} %} */

// re2c erroneously thinks %{ in a comment is a block start
/*
%{
 * {}
%}
*/

// not a block, just a %{ in a oneline comment
// %{ * {} %}

// re2c erroneously thinks %{ in a macro is a block start
#define X \
  %{ * {} %}
