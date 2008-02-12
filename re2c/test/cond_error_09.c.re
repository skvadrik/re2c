/*!re2c

<a>"a"	{ return 1; }
<b>"b"	{ return 2; }
<!a> { printf("foo"); }
<!a> := printf("bar");

*/
