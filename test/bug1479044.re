#define NULL ((char*) 0)
#define YYCTYPE char
#define YYCURSOR p
#define YYLIMIT p
#define YYMARKER q
#define YYFILL(n)

#include <stdio.h>

char *scan281(char *p)
{
	char *q;
start:
/*!re2c

	( "adsl" | "adslppp" | "bdsl" | "cdsl" | "dslgw4pool" | "dslppp" | "edsl" | "fdsl" | "ldsl" | "pool" | "pppdsl" | "premiumC" | "vdsl" | "xsttldsl") [0-9a-k\-]+ ".".+ ".uswest.net"
	{
		return "dsl";
	}

	( "dhcp" | "dorms" | "rh" ).* "-" [0-9]+ "-" [0-9]+ "." .+ ".resnet.pitt.edu"
	{
		return "resnet";
	}

	[0-9]+ "-" [0-9]+ "-" [0-9]+ "-" [0-9]+ "." ("dhcp" | .* "modem" | "bothell") .* ".washington.edu"
	{
		return "edu";
	}

	[\001-\377]
	{
		goto start;
	}

	[\000]
	{
		return NULL;
	}
*/
}

int main(int argc, char **argv)
{
	int n = 0;
	char *largv[2];

	if (argc < 2)
	{
		argc = 2;
		argv = largv;
		argv[1] = "D-128-208-46-51.dhcp4.washington.edu";
	}
	while(++n < argc)
	{
		char *res = scan281(argv[n]);
		printf("%s\n", res ? res : "<NULL>");
	}
	return 0;
}
