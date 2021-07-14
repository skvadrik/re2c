// re2c $INPUT -o $OUTPUT
#include <assert.h>
#include <vector>
#include <string>

static const int ROOT = -1;

struct Mtag {
    int pred;
    const char *tag;
};

typedef std::vector<Mtag> MtagTree;
typedef std::vector<std::string> Words;

static void mtag(int *pt, const char *t, MtagTree *tree)
{
    Mtag m = {*pt, t};
    *pt = (int)tree->size();
    tree->push_back(m);
}

static void unfold(const MtagTree &tree, int x, int y, Words &words)
{
    if (x == ROOT) return;
    unfold(tree, tree[x].pred, tree[y].pred, words);
    const char *px = tree[x].tag, *py = tree[y].tag;
    words.push_back(std::string(px, py - px));
}

#define YYMTAGP(t) mtag(&t, YYCURSOR, &tree)
#define YYMTAGN(t) mtag(&t, NULL,     &tree)
static bool lex(const char *YYCURSOR, Words &words)
{
    const char *YYMARKER;
    /*!mtags:re2c format = "int @@ = ROOT;\n"; */
    MtagTree tree;
    int x, y;

    /*!re2c
    re2c:yyfill:enable = 0;
    re2c:flags:tags = 1;
    re2c:define:YYCTYPE = char;

    (#x [a-z]+ #y [;])+ {
        words.clear();
        unfold(tree, x, y, words);
        return true;
    }
    * { return false; }
    */
}

int main()
{
    Words w;
    assert(lex("one;two;three;", w) && w == Words({"one", "two", "three"}));
    return 0;
}
