/*!re2c

re2c:yybm:hex = 1;

letter  = [a-zA-Z];
digit   = [0-9];
number  = "0" | ("-"? [1-9] digit*);
name    = letter (letter|digit)*;
config  = "re2c:" (letter|"_") (letter|digit|"_"|":")*;

config	{ return 0; }
name	{ return 1; }
number	{ return 2; }

.|"\n"	{ return -1; }

*/
