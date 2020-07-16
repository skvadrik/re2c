// re2c $INPUT -o $OUTPUT -i
#include <assert.h>
#include <stdio.h>
#include <string>
#include <vector>

typedef std::vector<std::pair<std::string, std::string> > unknown_t;

struct options_t
{
    std::string date;
    std::string path;
    std::string format;
    std::string limit;
    bool verbose;
};

static void show(const options_t &o, const unknown_t &u)
{
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

static void bad_arg(const char *k, const char *v, const char *e)
{
    fprintf(stderr, "bad argument '%.*s' to option %.*s\n",
        (int) (e - v), v, (int) (v - k), k);
}

static int lex(const char *s)
{
    options_t o;
    unknown_t u;
    const char *m, *k, *v;
    /*!stags:re2c format = 'const char *@@;'; */
loop:
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:define:YYCURSOR = s;
        re2c:define:YYMARKER = m;
        re2c:yyfill:enable = 0;
        re2c:flags:tags = 1;

        end    = "\x00";
        sp     = [ \t\n\r];
        eq     = "=";
        wsp    = sp*;
        char   = [^=] \ end;
        ochar  = char \ sp;
        pchar  = ochar \ [/];
        str    = ["] (char \ ["] | [\]["])* ["];
        opt    = ochar+;
        arg    = ochar* | str;
        date   = [0-9]{2} "/" [0-9]{2} "/" [0-9]{4};
        path   = pchar* ("/" pchar*)*;
        format = str;
        limit  = [0-9]+ [BKMG]?;

        *   { fprintf(stderr, "error: %s\n", s); return 1; }
        end { show(o, u); return 0; }
        wsp { goto loop; }

        "-v" | "--verbose"              { o.verbose = true; goto loop; }
        ("-l" | "--limit"  eq) @v limit { o.limit  = std::string(v, s); goto loop; }
        ("-f" | "--format" eq) @v str   { o.format = std::string(v, s); goto loop; }
        ("-d" | "--date"   eq) @v date  { o.date   = std::string(v, s); goto loop; }
        ("-p" | "--path"   eq) @v path  { o.path   = std::string(v, s); goto loop; }

        @k ("--" ("limit" | "format" | "date" | "path") | "-" [lfdp]) @v eq? arg {
            bad_arg(k, v, s);
            goto loop;
        }
        [-]{1,2} @k opt @v eq? arg {
            u.push_back(std::make_pair(std::string(k, v), std::string(v, s)));
            goto loop;
        }
    */
}

int main()
{
    assert(lex("-v --limit=8K -d08/08/1985 -p/usr/src/linux "
        "--format=\"%s\" --limit -f=3 --verbos --d\"19th May\"") == 0);
    return 0;
}
