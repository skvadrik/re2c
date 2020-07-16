// re2c $INPUT -o $OUTPUT -cg
/*!re2c

<*>		"1"	:=> r1
<*>		"2"	:=> r1
<r1>	"a" :=> r2
<r1,r2>	"b" :=> r2
<>			:=> r1

*/
