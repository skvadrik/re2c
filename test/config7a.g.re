/*!re2c

re2c:cgoto:threshold = 8;

a = [aA];
b = [bB];
c = [cC];
d = [dD];

(a|b|c|d|"e"|'f'|[gG])  { return 1; }

.|"\n"				{ return -1; }

*/
