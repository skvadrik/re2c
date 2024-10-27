/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i
#include <assert.h>
#include <stdio.h>
#include <string>
#include <vector>

typedef std::vector<std::pair<std::string, std::string> > unknown_t;

struct options_t {
    std::string date;
    std::string path;
    std::string format;
    std::string limit;
    bool verbose;
};

static void show(const options_t &o, const unknown_t &u) {
    fprintf(stderr, "\noptions:\n");
    fprintf(stderr, "  date:    %s\n", o.date.c_str());
    fprintf(stderr, "  path:    %s\n", o.path.c_str());
    fprintf(stderr, "  format:  %s\n", o.format.c_str());
    fprintf(stderr, "  limit:   %s\n", o.limit.c_str());
    fprintf(stderr, "  verbose: %s\n", o.verbose ? "yes" : "no");

    fprintf(stderr, "\nunknown:\n");
    unknown_t::const_iterator i = u.begin(), e = u.end();
    for (; i != e; ++i) {
        fprintf(stderr, "  %s: '%s'\n", i->first.c_str(), i->second.c_str());
    }
}

static void bad_arg(const char *k, const char *v, const char *e) {
    fprintf(stderr, "bad argument '%.*s' to option %.*s\n",
        (int) (e - v), v, (int) (v - k), k);
}

static int lex(const char *s) {
    options_t o;
    unknown_t u;
    const char *m, *k, *v;
    const char *yyt1;const char *yyt2;const char *yyt3;const char *yyt4;const char *yyt5;

    for (;;) {
    
{
	char yych;
	unsigned int yyaccept = 0;
	yych = *s;
	switch (yych) {
		case 0x00: goto yy1;
		case '\t':
		case '\n':
		case '\r':
		case ' ': goto yy4;
		case '-':
			yyt2 = s;
			goto yy6;
		default: goto yy2;
	}
yy1:
	++s;
	{ show(o, u); return 0; }
yy2:
	++s;
yy3:
	{ fprintf(stderr, "error: %s\n", s); return 1; }
yy4:
	yych = *++s;
	switch (yych) {
		case '\t':
		case '\n':
		case '\r':
		case ' ': goto yy4;
		default: goto yy5;
	}
yy5:
	{ continue; }
yy6:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
		case '=': goto yy3;
		case '-':
			yyt3 = s;
			goto yy10;
		case 'd':
			yyt3 = s;
			goto yy11;
		case 'f':
			yyt3 = s;
			goto yy13;
		case 'l':
			yyt3 = s;
			goto yy14;
		case 'p':
			yyt3 = s;
			goto yy15;
		case 'v':
			yyt3 = s;
			goto yy17;
		default:
			yyt3 = s;
			goto yy7;
	}
yy7:
	yych = *++s;
yy8:
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt4 = s;
			goto yy9;
		case '"':
			yyt4 = s;
			goto yy19;
		case '=':
			yyt4 = s;
			goto yy20;
		default: goto yy7;
	}
yy9:
	k = yyt3;
	v = yyt4;
	{
            u.push_back(std::make_pair(std::string(k, v), std::string(v, s)));
            continue;
        }
yy10:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt4 = s;
			goto yy9;
		case '"':
			yyt1 = s;
			yyt4 = s;
			goto yy21;
		case '=':
			yyt4 = s;
			goto yy20;
		case 'd':
			yyt1 = s;
			goto yy22;
		case 'f':
			yyt1 = s;
			goto yy23;
		case 'l':
			yyt1 = s;
			goto yy24;
		case 'p':
			yyt1 = s;
			goto yy25;
		case 'v':
			yyt1 = s;
			goto yy26;
		default:
			yyt3 = s;
			goto yy7;
	}
yy11:
	yych = *++s;
	yyt5 = s;
	switch (yych) {
		case '"': goto yy29;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy30;
		case '=': goto yy31;
		default: goto yy28;
	}
yy12:
	k = yyt2;
	v = yyt5;
	{
            bad_arg(k, v, s);
            continue;
        }
yy13:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt5 = s;
			goto yy12;
		case '"':
			yyt1 = s;
			yyt5 = s;
			goto yy32;
		case '=':
			yyt5 = s;
			goto yy31;
		default:
			yyt5 = s;
			goto yy27;
	}
yy14:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt5 = s;
			goto yy12;
		case '"':
			yyt5 = s;
			goto yy29;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			yyt1 = s;
			yyt5 = s;
			goto yy33;
		case '=':
			yyt5 = s;
			goto yy31;
		default:
			yyt5 = s;
			goto yy27;
	}
yy15:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt1 = s;
			goto yy16;
		case '"':
			yyt1 = s;
			yyt5 = s;
			goto yy36;
		case '=':
			yyt5 = s;
			goto yy31;
		default:
			yyt1 = s;
			goto yy35;
	}
yy16:
	v = yyt1;
	{ o.path   = std::string(v, s); continue; }
yy17:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ': goto yy18;
		default: goto yy8;
	}
yy18:
	{ o.verbose = true; continue; }
yy19:
	yyaccept = 0;
	yych = *(m = ++s);
	switch (yych) {
		case 0x00:
			yyt4 = s;
			goto yy9;
		case '\t':
		case '\n':
		case '\r':
		case ' ': goto yy37;
		case '"':
			yyt4 = s;
			goto yy19;
		case '=':
			yyt4 = s;
			goto yy20;
		default: goto yy19;
	}
yy20:
	yych = *++s;
	switch (yych) {
		case '"': goto yy41;
		default: goto yy40;
	}
yy21:
	yyaccept = 1;
	yych = *(m = ++s);
	switch (yych) {
		case 0x00:
			yyt3 = yyt1;
			yyt4 = s;
			goto yy9;
		case '\t':
		case '\n':
		case '\r':
		case ' ': goto yy37;
		case '"':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy19;
		case '=':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy20;
		default: goto yy21;
	}
yy22:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy9;
		case '"':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy19;
		case '=':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy20;
		case 'a': goto yy42;
		default:
			yyt3 = yyt1;
			goto yy7;
	}
yy23:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy9;
		case '"':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy19;
		case '=':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy20;
		case 'o': goto yy43;
		default:
			yyt3 = yyt1;
			goto yy7;
	}
yy24:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy9;
		case '"':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy19;
		case '=':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy20;
		case 'i': goto yy44;
		default:
			yyt3 = yyt1;
			goto yy7;
	}
yy25:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy9;
		case '"':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy19;
		case '=':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy20;
		case 'a': goto yy45;
		default:
			yyt3 = yyt1;
			goto yy7;
	}
yy26:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy9;
		case '"':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy19;
		case '=':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy20;
		case 'e': goto yy46;
		default:
			yyt3 = yyt1;
			goto yy7;
	}
yy27:
	yych = *++s;
yy28:
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ': goto yy12;
		case '"':
			yyt4 = s;
			goto yy47;
		case '=':
			yyt4 = s;
			goto yy20;
		default: goto yy27;
	}
yy29:
	yyaccept = 2;
	yych = *(m = ++s);
	switch (yych) {
		case 0x00: goto yy12;
		case '\t':
		case '\n':
		case '\r':
		case ' ': goto yy48;
		case '=':
			yyt4 = s;
			goto yy20;
		default: goto yy29;
	}
yy30:
	yych = *++s;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy49;
		default: goto yy28;
	}
yy31:
	yych = *++s;
	switch (yych) {
		case '"': goto yy52;
		default: goto yy51;
	}
yy32:
	yyaccept = 2;
	yych = *(m = ++s);
	switch (yych) {
		case 0x00: goto yy12;
		case '\t':
		case '\n':
		case '\r':
		case ' ': goto yy53;
		case '"': goto yy54;
		case '=':
			yyt4 = s;
			goto yy20;
		default: goto yy32;
	}
yy33:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ': goto yy34;
		case '"':
			yyt4 = s;
			goto yy47;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy33;
		case '=':
			yyt4 = s;
			goto yy20;
		case 'B':
		case 'G':
		case 'K':
		case 'M': goto yy56;
		default: goto yy27;
	}
yy34:
	v = yyt1;
	{ o.limit  = std::string(v, s); continue; }
yy35:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ': goto yy16;
		case '"':
			yyt4 = s;
			goto yy57;
		case '=':
			yyt4 = s;
			goto yy20;
		default: goto yy35;
	}
yy36:
	yyaccept = 3;
	yych = *(m = ++s);
	switch (yych) {
		case 0x00: goto yy16;
		case '\t':
		case '\n':
		case '\r':
		case ' ': goto yy48;
		case '=':
			yyt4 = s;
			goto yy20;
		default: goto yy36;
	}
yy37:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '=': goto yy38;
		case '"': goto yy58;
		default: goto yy37;
	}
yy38:
	s = m;
	switch (yyaccept) {
		case 0:
			yyt4 = s;
			goto yy9;
		case 1:
			yyt3 = yyt1;
			yyt4 = s;
			goto yy9;
		case 2: goto yy12;
		case 3: goto yy16;
		case 4: goto yy9;
		default: goto yy55;
	}
yy39:
	yych = *++s;
yy40:
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
		case '=': goto yy9;
		default: goto yy39;
	}
yy41:
	yyaccept = 4;
	yych = *(m = ++s);
	switch (yych) {
		case 0x00:
		case '=': goto yy9;
		case '\t':
		case '\n':
		case '\r':
		case ' ': goto yy37;
		default: goto yy41;
	}
yy42:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy9;
		case '"':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy19;
		case '=':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy20;
		case 't': goto yy59;
		default:
			yyt3 = yyt1;
			goto yy7;
	}
yy43:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy9;
		case '"':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy19;
		case '=':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy20;
		case 'r': goto yy60;
		default:
			yyt3 = yyt1;
			goto yy7;
	}
yy44:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy9;
		case '"':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy19;
		case '=':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy20;
		case 'm': goto yy61;
		default:
			yyt3 = yyt1;
			goto yy7;
	}
yy45:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy9;
		case '"':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy19;
		case '=':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy20;
		case 't': goto yy62;
		default:
			yyt3 = yyt1;
			goto yy7;
	}
yy46:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy9;
		case '"':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy19;
		case '=':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy20;
		case 'r': goto yy63;
		default:
			yyt3 = yyt1;
			goto yy7;
	}
yy47:
	yyaccept = 2;
	yych = *(m = ++s);
	switch (yych) {
		case 0x00: goto yy12;
		case '\t':
		case '\n':
		case '\r':
		case ' ': goto yy37;
		case '"':
			yyt4 = s;
			goto yy47;
		case '=':
			yyt4 = s;
			goto yy20;
		default: goto yy47;
	}
yy48:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '=': goto yy38;
		case '"': goto yy64;
		default: goto yy48;
	}
yy49:
	yych = *++s;
	switch (yych) {
		case '/': goto yy65;
		default: goto yy28;
	}
yy50:
	yych = *++s;
yy51:
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
		case '=': goto yy12;
		default: goto yy50;
	}
yy52:
	yyaccept = 2;
	yych = *(m = ++s);
	switch (yych) {
		case 0x00:
		case '=': goto yy12;
		case '\t':
		case '\n':
		case '\r':
		case ' ': goto yy48;
		default: goto yy52;
	}
yy53:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '=': goto yy38;
		case '"': goto yy66;
		default: goto yy53;
	}
yy54:
	yyaccept = 5;
	yych = *(m = ++s);
	switch (yych) {
		case 0x00: goto yy55;
		case '\t':
		case '\n':
		case '\r':
		case ' ': goto yy53;
		case '"': goto yy54;
		case '=':
			yyt4 = s;
			goto yy20;
		default: goto yy32;
	}
yy55:
	v = yyt1;
	{ o.format = std::string(v, s); continue; }
yy56:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ': goto yy34;
		default: goto yy28;
	}
yy57:
	yyaccept = 3;
	yych = *(m = ++s);
	switch (yych) {
		case 0x00: goto yy16;
		case '\t':
		case '\n':
		case '\r':
		case ' ': goto yy37;
		case '"':
			yyt4 = s;
			goto yy57;
		case '=':
			yyt4 = s;
			goto yy20;
		default: goto yy57;
	}
yy58:
	yyaccept = 4;
	yych = *(m = ++s);
	switch (yych) {
		case 0x00:
		case '=': goto yy9;
		case '"': goto yy58;
		default: goto yy37;
	}
yy59:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy9;
		case '"':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy19;
		case '=':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy20;
		case 'e': goto yy67;
		default:
			yyt3 = yyt1;
			goto yy7;
	}
yy60:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy9;
		case '"':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy19;
		case '=':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy20;
		case 'm': goto yy68;
		default:
			yyt3 = yyt1;
			goto yy7;
	}
yy61:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy9;
		case '"':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy19;
		case '=':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy20;
		case 'i': goto yy69;
		default:
			yyt3 = yyt1;
			goto yy7;
	}
yy62:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy9;
		case '"':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy19;
		case '=':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy20;
		case 'h': goto yy70;
		default:
			yyt3 = yyt1;
			goto yy7;
	}
yy63:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy9;
		case '"':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy19;
		case '=':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy20;
		case 'b': goto yy71;
		default:
			yyt3 = yyt1;
			goto yy7;
	}
yy64:
	yyaccept = 2;
	yych = *(m = ++s);
	switch (yych) {
		case 0x00:
		case '=': goto yy12;
		case '"': goto yy64;
		default: goto yy48;
	}
yy65:
	yych = *++s;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy72;
		default: goto yy28;
	}
yy66:
	yyaccept = 5;
	yych = *(m = ++s);
	switch (yych) {
		case 0x00:
		case '=': goto yy55;
		case '"': goto yy66;
		default: goto yy53;
	}
yy67:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt5 = s;
			goto yy12;
		case '"':
			yyt3 = yyt1;
			yyt5 = s;
			goto yy29;
		case '=':
			yyt5 = s;
			goto yy73;
		default:
			yyt3 = yyt1;
			yyt5 = s;
			goto yy27;
	}
yy68:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy9;
		case '"':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy19;
		case '=':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy20;
		case 'a': goto yy74;
		default:
			yyt3 = yyt1;
			goto yy7;
	}
yy69:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy9;
		case '"':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy19;
		case '=':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy20;
		case 't': goto yy75;
		default:
			yyt3 = yyt1;
			goto yy7;
	}
yy70:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt5 = s;
			goto yy12;
		case '"':
			yyt3 = yyt1;
			yyt5 = s;
			goto yy29;
		case '=':
			yyt5 = s;
			goto yy76;
		default:
			yyt3 = yyt1;
			yyt5 = s;
			goto yy27;
	}
yy71:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy9;
		case '"':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy19;
		case '=':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy20;
		case 'o': goto yy77;
		default:
			yyt3 = yyt1;
			goto yy7;
	}
yy72:
	yych = *++s;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy78;
		default: goto yy28;
	}
yy73:
	yych = *++s;
	switch (yych) {
		case '"': goto yy52;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy79;
		default: goto yy51;
	}
yy74:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy9;
		case '"':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy19;
		case '=':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy20;
		case 't': goto yy80;
		default:
			yyt3 = yyt1;
			goto yy7;
	}
yy75:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt5 = s;
			goto yy12;
		case '"':
			yyt3 = yyt1;
			yyt5 = s;
			goto yy29;
		case '=':
			yyt5 = s;
			goto yy81;
		default:
			yyt3 = yyt1;
			yyt5 = s;
			goto yy27;
	}
yy76:
	yych = *++s;
	yyt1 = s;
	switch (yych) {
		case '"': goto yy84;
		default: goto yy83;
	}
yy77:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy9;
		case '"':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy19;
		case '=':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy20;
		case 's': goto yy85;
		default:
			yyt3 = yyt1;
			goto yy7;
	}
yy78:
	yych = *++s;
	switch (yych) {
		case '/': goto yy86;
		default: goto yy28;
	}
yy79:
	yych = *++s;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy87;
		default: goto yy51;
	}
yy80:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt5 = s;
			goto yy12;
		case '"':
			yyt3 = yyt1;
			yyt5 = s;
			goto yy29;
		case '=':
			yyt5 = s;
			goto yy88;
		default:
			yyt3 = yyt1;
			yyt5 = s;
			goto yy27;
	}
yy81:
	yych = *++s;
	switch (yych) {
		case '"': goto yy52;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			yyt1 = s;
			goto yy89;
		default: goto yy51;
	}
yy82:
	yych = *++s;
yy83:
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
		case '=': goto yy16;
		default: goto yy82;
	}
yy84:
	yyaccept = 3;
	yych = *(m = ++s);
	switch (yych) {
		case 0x00:
		case '=': goto yy16;
		case '\t':
		case '\n':
		case '\r':
		case ' ': goto yy48;
		default: goto yy84;
	}
yy85:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy9;
		case '"':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy19;
		case '=':
			yyt3 = yyt1;
			yyt4 = s;
			goto yy20;
		case 'e':
			yyt3 = yyt1;
			goto yy17;
		default:
			yyt3 = yyt1;
			goto yy7;
	}
yy86:
	yych = *++s;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy90;
		default: goto yy28;
	}
yy87:
	yych = *++s;
	switch (yych) {
		case '/': goto yy91;
		default: goto yy51;
	}
yy88:
	yych = *++s;
	switch (yych) {
		case '"':
			yyt1 = s;
			goto yy92;
		default: goto yy51;
	}
yy89:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
		case '=': goto yy34;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy89;
		case 'B':
		case 'G':
		case 'K':
		case 'M': goto yy93;
		default: goto yy50;
	}
yy90:
	yych = *++s;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy94;
		default: goto yy28;
	}
yy91:
	yych = *++s;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy95;
		default: goto yy51;
	}
yy92:
	yyaccept = 2;
	yych = *(m = ++s);
	switch (yych) {
		case 0x00:
		case '=': goto yy12;
		case '\t':
		case '\n':
		case '\r':
		case ' ': goto yy53;
		case '"': goto yy96;
		default: goto yy92;
	}
yy93:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
		case '=': goto yy34;
		default: goto yy50;
	}
yy94:
	yych = *++s;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy97;
		default: goto yy28;
	}
yy95:
	yych = *++s;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy98;
		default: goto yy51;
	}
yy96:
	yyaccept = 5;
	yych = *(m = ++s);
	switch (yych) {
		case 0x00:
		case '=': goto yy55;
		case '\t':
		case '\n':
		case '\r':
		case ' ': goto yy53;
		case '"': goto yy96;
		default: goto yy92;
	}
yy97:
	yych = *++s;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy99;
		default: goto yy28;
	}
yy98:
	yych = *++s;
	switch (yych) {
		case '/': goto yy101;
		default: goto yy51;
	}
yy99:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ': goto yy100;
		default: goto yy28;
	}
yy100:
	v = s;
	v -= 10;
	{ o.date   = std::string(v, s); continue; }
yy101:
	yych = *++s;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy102;
		default: goto yy51;
	}
yy102:
	yych = *++s;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy103;
		default: goto yy51;
	}
yy103:
	yych = *++s;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy104;
		default: goto yy51;
	}
yy104:
	yych = *++s;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy105;
		default: goto yy51;
	}
yy105:
	yych = *++s;
	switch (yych) {
		case 0x00:
		case '\t':
		case '\n':
		case '\r':
		case ' ':
		case '=': goto yy100;
		default: goto yy50;
	}
}

    }
}

int main() {
    assert(lex("-v --limit=8K -d08/08/1985 -p/usr/src/linux "
        "--format=\"%s\" --limit -f=3 --verbos --d\"19th May\"") == 0);
    return 0;
}
c/submatch/parse_options.re:68:12: warning: rule matches empty string [-Wmatch-empty-string]
c/submatch/parse_options.re:80:35: warning: tag `k` has 2nd degree of nondeterminism [-Wnondeterministic-tags]
c/submatch/parse_options.re:80:35: warning: tag `v` has 2nd degree of nondeterminism [-Wnondeterministic-tags]
