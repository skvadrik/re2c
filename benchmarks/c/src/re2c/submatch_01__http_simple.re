#include "re2c/base.h"

namespace re2c_submatch_01__http_simple {

/*!rules:re2c:main
    eol            = "\n";
    sp             = " ";
    htab           = "\t";
    ows            = (sp | htab)*;
    char           = [-._~%!$&'()*+,;=a-zA-Z0-9];
    tchar          = [-._~%!$&'*+#^`|a-zA-Z0-9];
    vchar          = [\x1f-\x7e\x80-\xff];
    scheme         = [-+.a-zA-Z0-9]+;
    userinfo       = (char | [:])+;
    host           = (char | [:[\]])+;
    port           = [0-9]*;
    path           = (char | [:@/])*;
    query          = (char | [:@?/])*;
    obs_fold       = eol (sp | htab)+;
    field_content  = vchar ((sp | htab)+ vchar)?;
    header_field   = #h1 tchar+ ":" ows (field_content | obs_fold)* #h2 ows;
    authority      = (userinfo "@")? host (":" port)?;
    absolute_uri   = scheme ":" ("//" (userinfo "@")? host (":" port)?)? path ("?" query)?;
    origin_form    = "/" path ("?" query)?;
    http_version   = "HTTP/" [0-9] "." [0-9];
    request_target = authority | absolute_uri | origin_form | "*";
    method         = tchar+;
    request_line   = @m1 method @m2 sp @rt1 request_target @rt2 sp @v3 http_version @v4 eol;
    status_code    = [0-9]{3};
    reason_phrase  = (htab | sp | vchar)*;
    status_line    = @v1 http_version @v2 sp @s1 status_code @s2 sp @rp1 reason_phrase @rp2 eol;
    start_line     = (request_line | status_line);
    message_head   = start_line (header_field eol)* eol;

    *            { return -1; }
    message_head {
        if (s1) {
            OUT("version: ", v1, v2);
            OUT("status: ", s1, s2);
            OUT("reason: ", rp1, rp2);
        }
        if (m1) {
            OUT("method: ", m1, m2);
            OUT("request: ", rt1, rt2);
            OUT("version: ", v3, v4);
        }
        count += print_headers(YYTOKEN, h1, h2);
        OUTC('\n');
        TLP_CLEAR();
        goto loop;
    }
*/

static long print_headers(const char *tok, const taglist_t *h1, const taglist_t *h2) {
    if (!h2) return 0;
    long count = print_headers(tok, h1->pred, h2->pred);
    OUT("header: ", tok + h1->dist, tok + h2->dist);
    return count;
}

/*!include:re2c "base.re" */

} // namespace re2c_submatch_01__http_simple
