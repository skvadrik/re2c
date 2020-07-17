// re2c $INPUT -o $OUTPUT -ig
/*!re2c
    BINDCHR   = [:][a-zA-Z0-9_]+;
    QUESTION  = [?];
    COMMENTS  = ("/*"([^*]+|[*]+[^/*])*[*]*"*/"|"--"[^\r\n]*);
    SPECIALS  = [:?"'];
    MULTICHAR = ([:]{2,}|[?]{2,});
    ANYNOEOF  = [\001-\377];

    (["](([\\]ANYNOEOF)|ANYNOEOF\["\\])*["]) { RET(PDO_PARSER_TEXT); }
    (['](([\\]ANYNOEOF)|ANYNOEOF\['\\])*[']) { RET(PDO_PARSER_TEXT); }
    MULTICHAR                                { RET(PDO_PARSER_TEXT); }
    BINDCHR                                  { RET(PDO_PARSER_BIND); }
    QUESTION                                 { RET(PDO_PARSER_BIND_POS); }
    SPECIALS                                 { SKIP_ONE(PDO_PARSER_TEXT); }
    COMMENTS                                 { RET(PDO_PARSER_TEXT); }
    (ANYNOEOF\SPECIALS)+                     { RET(PDO_PARSER_TEXT); }

    // default rule added to enable skeleton test
    * {}
*/
