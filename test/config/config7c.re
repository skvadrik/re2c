// re2c $INPUT -o $OUTPUT -g
/*!re2c

re2c:cgoto:threshold = 7;
re2c:cgoto:relative = 1;

a = [aA];
b = [bB];
c = [cC];
d = [dD];

(a|b|c|d|"e"|'f'|[gG])  { return 1; }

.|"\n"				{ return -1; }

*/
