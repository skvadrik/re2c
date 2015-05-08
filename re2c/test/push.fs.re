uint32_t push()
{
    // The scanner starts here
    #define YYLIMIT         limit
    #define YYCURSOR        cursor
    #define YYMARKER        marker
    #define YYCTYPE         uint8_t

    #define SKIP(x)         { start = cursor; goto yy0; }
    #define SEND(x)         { send(x); SKIP();          }
    #define YYFILL(n)       { goto fill;                }

    #define YYGETSTATE()    state
    #define YYSETSTATE(x)   { state = (x);  }

start:

    /*!re2c      
    	re2c:startlabel = 1;
        eol = "\n";
        eof = "\000";
        digit = [0-9];
        integer = digit+;
        alpha = [A-Za-z_];
        any = [\000-\377];
        space = [ \h\t\v\f\r];

        "if"                    { SEND(kIf);             }
        "for"                   { SEND(kFor);            }
        "else"                  { SEND(kElse);           }
        "goto"                  { SEND(kGoto);           }
        "break"                 { SEND(kBreak);          }
        "while"                 { SEND(kWhile);          }
        "return"                { SEND(kReturn);         }
        alpha (alpha|digit)*    { SEND(kIdentifier);     }
        integer                 { SEND(kDecimalConstant);}

        "="                     { SEND(kEqual);          }
        "("                     { SEND(kLeftParen);      }
        ")"                     { SEND(kRightParen);     }
        "-"                     { SEND(kMinus);          }
        "+"                     { SEND(kPlus);           }
        "*"                     { SEND(kStar);           }
        "/"                     { SEND(kSlash);          }

        eol                     { SKIP();                }
        space                   { SKIP();                }
        eof                     { send(kEOF); return 1;  }
        any                     { SEND(kUnknown);        }
    */

fill:
    return 0;
}
