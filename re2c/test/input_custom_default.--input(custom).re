bool lex (const char * cursor, const char * const limit)
{
    const char * marker;
    const char * ctxmarker;
#   define YYCTYPE            char
#   define RE2C_PEEK()        *cursor
#   define RE2C_SKIP()        ++cursor
#   define RE2C_BACKUP()      marker = cursor
#   define RE2C_BACKUP_CTX()  ctxmarker = cursor
#   define RE2C_RESTORE()     cursor = marker
#   define RE2C_RESTORE_CTX() cursor = ctxmarker
#   define RE2C_LESS_THAN(n)  limit - cursor < n
#   define YYFILL(n)          {}
    /*!re2c
        "int buffer " / "[" [0-9]+ "]" { return true; }
        *                              { return false; }
    */
}

int main ()
{
    char buffer [] = "int buffer [1024]";
    return !lex (buffer, buffer + sizeof (buffer));
}
