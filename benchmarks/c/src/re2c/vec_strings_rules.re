// Lexer rules shared by vec_00__strings.re and vec_01__strings_fixed.re (and mirrored by the
// hand-written reference lexers in ../ref/vec_strings_ref.cc).
//
// A lexer for string literals and other C-like tokens. The hot loops are the reflexive loops
// inside string literals, comments, whitespace, identifiers and numbers: these are the loops that
// `re2c:vectorize:loops` targets.
/*!rules:re2c:main
    str = ["] ([^"\\\n\x00] | [\\][^\n\x00])* ["];
    chr = ['] ([^'\\\n\x00] | [\\][^\n\x00])* ['];
    line_comment = "//" [^\n\x00]*;
    block_comment = "/*" ([^*\x00] | "*"+ [^/*\x00])* "*"+ "/";
    ws = [ \t\r\n]+;
    id = [a-zA-Z_][a-zA-Z0-9_]*;
    num = [0-9][0-9a-zA-Z_.]*;

    str           { TOKEN(1); }
    chr           { TOKEN(2); }
    line_comment  { TOKEN(3); }
    block_comment { TOKEN(4); }
    ws            { TOKEN(5); }
    id            { TOKEN(6); }
    num           { TOKEN(7); }
    *             { TOKEN(8); }
*/
