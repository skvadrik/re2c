/* $Id$ */
#ifndef _scanner_h
#define	_scanner_h

#include <iosfwd>
#include "token.h"

class Scanner {
  private:
    std::istream&	in;
    char		*bot, *tok, *ptr, *cur, *pos, *lim, *top, *eof;
    uint		tchar, tline, cline;
  private:
    char *fill(char*);
    Scanner(const Scanner&); //unimplemented
    Scanner& operator=(const Scanner&); //unimplemented
  public:
    Scanner(std::istream&);
    int echo(std::ostream&);
    int scan();
    void fatal(char*);
    SubStr token();
    uint line();
};

inline SubStr Scanner::token(){
    return SubStr(tok, cur - tok);
}

inline uint Scanner::line(){
    return cline;
}

#endif
