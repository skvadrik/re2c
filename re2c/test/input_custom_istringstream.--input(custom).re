#include <sstream>

bool lex (std::istringstream & is, const std::streampos limit)
{
    std::streampos marker;
    std::streampos ctxmarker;
#   define YYCTYPE            char
#   define RE2C_PEEK()        is.peek ()
#   define RE2C_SKIP()        is.ignore ()
#   define RE2C_BACKUP()      marker = is.tellg ()
#   define RE2C_BACKUP_CTX()  ctxmarker = is.tellg ()
#   define RE2C_RESTORE()     is.seekg (marker)
#   define RE2C_RESTORE_CTX() is.seekg (ctxmarker)
#   define RE2C_LESS_THAN(n)  limit - is.tellg () < n
#   define YYFILL(n)          {}
    /*!re2c
        "int buffer " / "[" [0-9]+ "]" { return true; }
        *                              { return false; }
    */
}

int main ()
{
    const char buffer [] = "int buffer [1024]";
    std::istringstream is (buffer);
    return !lex (is, sizeof (buffer));
}
