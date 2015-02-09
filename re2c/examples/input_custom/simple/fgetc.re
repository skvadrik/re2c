#include <stdio.h>

char peek (FILE * f)
{
    char c = fgetc (f);
    ungetc (c, f);
    return c;
}

bool lex (FILE * f, const long limit)
{
    long marker;
    long ctxmarker;
#   define YYCTYPE            char
#   define RE2C_PEEK()        peek (f)
#   define RE2C_SKIP()        fgetc (f)
#   define RE2C_BACKUP()      marker = ftell (f)
#   define RE2C_BACKUP_CTX()  ctxmarker = ftell (f)
#   define RE2C_RESTORE()     fseek (f, marker, SEEK_SET)
#   define RE2C_RESTORE_CTX() fseek (f, ctxmarker, SEEK_SET)
#   define RE2C_LESS_THAN(n)  limit - ftell (f) < n
#   define YYFILL(n)          {}
    /*!re2c
        "int buffer " / "[" [0-9]+ "]" { return true; }
        *                              { return false; }
    */
}

int main ()
{
    const char buffer [] = "int buffer [1024]";
    const char fn [] = "input.txt";

    FILE * f = fopen (fn, "w");
    fwrite (buffer, 1, sizeof (buffer), f);
    fclose (f);

    f = fopen (fn, "rb");
    int result = !lex (f, sizeof (buffer));
    fclose (f);

    return result;
}
