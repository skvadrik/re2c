/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i --posix-captures --dump-adfa --fixed-tags toplevel

{
	YYCTYPE yych;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			yyt1 = YYCURSOR;
			yyt2 = YYCURSOR;
			goto yy2;
		default:
			yyt1 = YYCURSOR;
			yyt2 = NULL;
			yyt3 = NULL;
			goto yy1;
	}
yy1:
	yynmatch = 2;
	yypmatch[0] = yyt1;
	yypmatch[2] = yyt2;
	yypmatch[3] = yyt3;
	yypmatch[1] = YYCURSOR;
	{}
yy2:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			yyt2 = YYCURSOR;
			goto yy2;
		default:
			yyt3 = YYCURSOR;
			goto yy1;
	}
}

debug/adfa.re:3:11: warning: rule matches empty string [-Wmatch-empty-string]
digraph DFA {
  rankdir=LR
  node[shape=Mrecord fontname=fixed]
  edge[arrowhead=vee fontname=fixed]

  n [shape=point]  n -> n0 [style=dotted label=""]
  n0 [height=0.2 width=0.2 label="F(1) " ]
  n0 -> n1 [label="/1&uarr; 2&darr; 3&darr; " style=dotted]
  n0 -> n2 [label="97/1&uarr; 2&uarr; " ]
  n0 -> n1 [label="/1&uarr; 2&darr; 3&darr; " style=dotted]
  n1 [height=0.2 width=0.2 label="/(1) /(0) /(2) /(3)" style=filled fillcolor=lightgray]
  n2 [height=0.2 width=0.2 label="F(1) " ]
  n2 -> n3 [label="" style=dotted]
  n3 [height=0.2 width=0.2 label="" ]
  n3 -> n1 [label="/3&uarr; " style=dotted]
  n3 -> n2 [label="97/2&uarr; " ]
  n3 -> n1 [label="/3&uarr; " style=dotted]
}
