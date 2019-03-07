/*!re2c

<>			=> r1 { return NULL; }
<*>		"1"	=> r1 { return "1"; }
<*>		"2"	=> r1 { return "2"; }
<r1>	"a" => r2 { return "a"; }
<r1,r2>	"b" => r2 { return "b"; }

*/
