int main() {
	printf("some code that will be stripped");

/*!re2c

<state1>"abc"	{ return 1; }
<state2>"abc"	{ return 2; }
<state1>"foo"	{ return 3; }

*/

	printf("here too\n");
}
