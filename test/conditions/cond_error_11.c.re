// re2c $INPUT -o $OUTPUT -c
/*!re2c

<a>"a"	{ return 1; }
<b>"b"	{ return 2; }
<!a> { printf("foo"); }
<!b> := printf("bar");
<!*> := printf("baz");

*/
