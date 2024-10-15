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

// %{ is not a block start, as it's not followed by a newline
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

// %{ is not a block start, as it's not followed by a newline
#define X \
  %{ * {} %}

// empty block
%{
%}

// %{ is not a block start, as it's not followed by a newline
%{%}

