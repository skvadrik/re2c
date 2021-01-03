/*!include:re2c "common.re" */

static void print_headers(Output *out, const char *tok,
    const taglist_t *h1, const taglist_t *h2, const taglist_t *h3)
{
    if (!h3) return;

    print_headers(out, tok, h1->pred, h2->pred, h3->pred);
    outstr(out, "header: ");
    outs(out, tok + h1->dist, tok + h2->dist - 1);
    outc(out, ' ');
    outs(out, tok + h2->dist, tok + h3->dist);
    outc(out, '\n');
}

static int lex(input_t *in, Output *out)
{
    const char
        *s1, *v1, *v3, *m1, *rp1, *rt1,
        *s2, *v2, *v4, *m2, *rp2, *rt2;
    taglist_t *h1, *h2, *h3;

loop:
    in->tok = in->cur;
/*!re2c
    end            = "\x00";
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
    header_field   = #h1 tchar+ ":" #h2 ows (field_content | obs_fold)* ows #h3;
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

    *            { return 1; }
    end          { return 0; }
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
        print_headers(out, in->tok, h1, h2, h3);
        outc(out, '\n');

        taglistpool_clear(&in->tlp, in);
        goto loop;
    }
*/
}
