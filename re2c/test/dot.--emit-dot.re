int main(){
	printf("some code that will be stripped");

/*!re2c

"abc"	{ return 1; }
"efg"	{ return 2; }
[^]	{ return 3; }

*/

	printf("here too");
}
