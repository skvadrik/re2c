// Lexer rules for `--vectorize-linear` HTTP header benchmark (included by lin_00__http.re).
/*!rules:re2c:main
    "Content-Length:"           { TOKEN(1); }
    "Content-Type:"             { TOKEN(2); }
    "Transfer-Encoding:"        { TOKEN(3); }
    "Authorization:"            { TOKEN(4); }
    "Accept-Encoding:"          { TOKEN(5); }
    "User-Agent:"               { TOKEN(6); }
    "Cache-Control:"            { TOKEN(7); }
    "Connection:"               { TOKEN(8); }
    [a-zA-Z0-9-]+ ":"           { TOKEN(9); }
    " " [^\r\n\x00]* "\r"? "\n" { TOKEN(10); }
    *                           { TOKEN(11); }
*/
