import qualified Test.QuickCheck as Q
import           Data.List (intercalate)
import           Control.Monad (forM_, when, replicateM)

    {-!re2c

        crlf  = "\n";
        sp    = " ";
        htab  = "\t";
        ows   = (sp | htab)*;
        rws   = (sp | htab)+;
        bws   = ows;
        digit = [0-9];
        alpha = [a-zA-Z];
        hexdigit    = [0-9a-fA-F];
        unreserved  = alpha | digit | [-._~];
        pct_encoded = "%" hexdigit{2};
        sub_delims  = [!$&'()*+,;=];
        pchar       = unreserved | pct_encoded | sub_delims | [:@];
        vchar = [\x1f-\x7e];
        tchar = [-!#$%&'*+.^_`|~] | digit | alpha;
        token = tchar+;
        octet = [^\x00];


        obs_fold       = crlf (sp | htab)+;
        obs_text       = [\x80-\xff];
        field_name     = token;
        field_vchar    = vchar | obs_text;
        field_content  = field_vchar ((sp | htab)+ field_vchar)?;
        field_value    = (field_content | obs_fold)*;
        header_field   = #h1 field_name #h2 ":" ows field_value ows #h3;
        method         = token;
        segment        = pchar*;
        scheme         = alpha (alpha | digit | [-+.])*;
        userinfo       = (unreserved | pct_encoded | sub_delims | ":")*;
        dec_octet
            = digit
            | [\x31-\x39] digit
            | "1" digit{2}
            | "2" [\x30-\x34] digit
            | "25" [\x30-\x35];
        ipv4address    = dec_octet "." dec_octet "." dec_octet "." dec_octet;
        h16            = hexdigit{1,4};
        ls32           = h16 ":" h16 | ipv4address;
        ipv6address
            =                            (h16 ":"){6} ls32
            |                       "::" (h16 ":"){5} ls32
            | (               h16)? "::" (h16 ":"){4} ls32
            | ((h16 ":"){0,1} h16)? "::" (h16 ":"){3} ls32
            | ((h16 ":"){0,2} h16)? "::" (h16 ":"){2} ls32
            | ((h16 ":"){0,3} h16)? "::"  h16 ":"     ls32
            | ((h16 ":"){0,4} h16)? "::"              ls32
            | ((h16 ":"){0,5} h16)? "::"              h16
            | ((h16 ":"){0,6} h16)? "::";
        ipvfuture      = "v" hexdigit+ "." (unreserved | sub_delims | ":" )+;
        ip_literal     = "[" ( ipv6address | ipvfuture ) "]";
        reg_name       = (unreserved | pct_encoded | sub_delims)*;
        host           = ip_literal | ipv4address | reg_name;
        port           = digit*;
        authority      = (userinfo "@")? host (":" port)?;
        query          = (pchar | [/?])*;
        path_abempty   = ("/" pchar*)*;
        path_absolute  = "/" (pchar+ ("/" pchar*)*)?;
        path_rootless  = pchar+ ("/" pchar*)*;
        path_empty     = "";
        hier_part
            = "//" authority path_abempty
            | (path_absolute | path_rootless | path_empty);
        absolute_uri   = scheme ":" hier_part ("?" query)?;
        absolute_path  = ("/" segment)*;
        origin_form    = absolute_path ("?" query)?;
        http_name      = "HTTP";
        http_version   = http_name "/" digit "." digit;
        request_target = origin_form | absolute_uri | authority | "*";
        request_line   = @m1 method @m2 sp @rt1 request_target @rt2 sp @v3 http_version @v4 crlf;
        status_code    = digit{3};
        reason_phrase  = (htab | sp | vchar | obs_text)*;
        status_line    = @v1 http_version @v2 sp @s1 status_code @s2 sp @rp1 reason_phrase @rp2 crlf;
        start_line     = (request_line | status_line);
        message_body   = octet*;
        message_head   = start_line (header_field crlf)* crlf;
    -}

type Scheme = String
type User = String
type Password = String
type Host = String
type Port = String
type Path = String
type Query = String
data RequestTarget
    = OriginForm Path Query
    | AbsoluteURI Scheme User Password Host Port Path Query
    | Authority User Password Host Port
    | Asterisk
type ReasonPhrase = String
type HTTPVersion = String
type Method = String
type StatusCode = Int
data StartLine
    = RequestLine Method RequestTarget HTTPVersion
    | StatusLine HTTPVersion StatusCode ReasonPhrase
data HeaderField = HeaderField String
data HTTPMsg = HTTPMsg StartLine [HeaderField]


instance Show RequestTarget where
    show (OriginForm p q) = p ++ (if q == "" then "" else "?" ++ q)
    show (AbsoluteURI sc us pw ho pr pa q) = concat
        [ sc
        , ":"
        , if ho == "" then "" else "//"
        , us
        , if us == "" then "" else ":"
        , pw
        , if pw == "" then "" else "@"
        , ho
        , if pr == "" then "" else ":"
        , pr
        , pa
        , if q == "" then "" else "?"
        , q
        ]
    show (Authority us pw ho pr) = concat
        [ us
        , if us == "" then "" else ":"
        , pw
        , if pw == "" then "" else "@"
        , ho
        , if pr == "" then "" else ":"
        , pr
        ]
    show Asterisk = "*"
instance Show StartLine where
    show (RequestLine m rt v) = m ++ " " ++ show rt ++ " " ++ v ++ "\n"
    show (StatusLine v sc rp) = v ++ " " ++ show sc ++ " " ++ rp ++ "\n"
instance Show HeaderField where show (HeaderField hf) = hf
instance Show HTTPMsg where
    show (HTTPMsg sl hfs) = show sl ++ unlines (map show hfs) ++ "\n"


instance Q.Arbitrary HTTPMsg where
    arbitrary = do
        scheme   <- Q.elements ["http", "https", "ftp", "file"]
        user     <- lstr
        password <- anstr
        host     <- Q.frequency [(10, ipv4), (10, hostname), (1, ipv6)]
        port     <- mayb $ show <$> (Q.choose (0, 10000) :: Q.Gen Int)
        path     <- filepath
        query    <- mayb anstr
        request_target <- Q.frequency
            [ (1, pure $ OriginForm path query)
            , (1, pure $ OriginForm path "")

            , (1, pure $ Authority user password host port)
            , (1, pure $ Authority user password host "")
            , (1, pure $ Authority ""   ""       host port)
            , (1, pure $ Authority ""   ""       host "")

            , (1, pure $ AbsoluteURI scheme user  password host port path query)
            , (2, pure $ AbsoluteURI scheme ""    ""       host port path query)
            , (1, pure $ AbsoluteURI scheme ""    ""       ""   ""   path query)

            , (1, pure Asterisk)
            ]
        reason_phrase <- Q.listOf (Q.elements (alphanum ++ space)) :: Q.Gen [Char]
        method <- Q.elements
            [ "OPTIONS"
            , "GET"
            , "HEAD"
            , "POST"
            , "PUT"
            , "DELETE"
            , "TRACE"
            , "CONNECT"
            , "PATCH"
            ]
        status_code <- Q.choose (100, 999) :: Q.Gen Int
        http_version <- do
            n1 <- Q.choose (0, 9) :: Q.Gen Int
            n2 <- Q.choose (0, 9) :: Q.Gen Int
            return $ "HTTP/" ++ show n1 ++ "." ++ show n2
        start_line <- Q.frequency
            [ (1, pure $ RequestLine method request_target http_version)
            , (1, pure $ StatusLine http_version status_code reason_phrase)
            ]
        -- copy-pasted from https://en.wikipedia.org/wiki/List_of_HTTP_header_fields
        header_fields <- Q.listOf1 $ HeaderField <$> Q.elements
            -- request examples
            [ "Accept: text/plain"
            , "Accept-Charset: utf-8"
            , "Accept-Encoding: gzip, deflate"
            , "Accept-Language: en-US"
            , "Accept-Datetime: Thu, 31 May 2007 20:35:00 GMT"
            , "Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ=="
            , "Cache-Control: no-cache"
            , "Connection: keep-alive"
            , "Connection: Upgrade"
            , "Cookie: $Version=1; Skin=new;"
            , "Content-Length: 348"
            , "Content-MD5: Q2hlY2sgSW50ZWdyaXR5IQ=="
            , "Content-Type: application/x-www-form-urlencoded"
            , "Date: Tue, 15 Nov 1994 08:12:31 GMT"
            , "Expect: 100-continue"
            , "Forwarded: for=192.0.2.60;proto=http;by=203.0.113.43"
            , "Forwarded: for=192.0.2.43, for=198.51.100.17"
            , "From: user@example.com"
            , "Host: en.wikipedia.org:8080"
            , "Host: en.wikipedia.org"
            , "If-Match: \"737060cd8c284d8af7ad3082f209582d\""
            , "If-Modified-Since: Sat, 29 Oct 1994 19:43:31 GMT"
            , "If-None-Match: \"737060cd8c284d8af7ad3082f209582d\""
            , "If-Range: \"737060cd8c284d8af7ad3082f209582d\""
            , "If-Unmodified-Since: Sat, 29 Oct 1994 19:43:31 GMT"
            , "Max-Forwards: 10"
            , "Origin: http://www.example-social-network.com"
            , "Pragma: no-cache"
            , "Proxy-Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ=="
            , "Range: bytes=500-999"
            , "Referer: http://en.wikipedia.org/wiki/Main_Page"
            , "TE: trailers, deflate"
            , "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:12.0) Gecko/20100101 Firefox/12.0"
            , "Upgrade: HTTPS/1.3, IRC/6.9, RTA/x11, websocket"
            , "Via: 1.0 fred, 1.1 example.com (Apache/1.1)"
            , "Warning: 199 Miscellaneous warning"
            , "X-Requested-With: XMLHttpRequest"
            , "DNT: 1 (Do Not Track Enabled)"
            , "DNT: 0 (Do Not Track Disabled)"
            , "X-Forwarded-For: client1, proxy1, proxy2"
            , "X-Forwarded-For: 129.78.138.66, 129.78.64.103"
            , "X-Forwarded-Host: en.wikipedia.org:8080"
            , "X-Forwarded-Host: en.wikipedia.org"
            , "X-Forwarded-Proto: https"
            , "Front-End-Https: on"
            , "X-HTTP-Method-Override: DELETE"
            , "X-Att-Deviceid: GT-P7320/P7320XXLPG"
            , "x-wap-profile: http://wap.samsungmobile.com/uaprof/SGH-I777.xml"
            , "Proxy-Connection: keep-alive"
            , "X-UIDH: ..."
            , "X-Csrf-Token: i8XNjC4b8KVok4uw5RftR38Wgp2BFwql"
            , "X-Request-ID: f058ebd6-02f7-4d3f-942e-904344e8cde5"
            -- response examples
            , "Access-Control-Allow-Origin: *"
            , "Accept-Patch: text/example;charset=utf-8"
            , "Accept-Ranges: bytes"
            , "Age: 12"
            , "Allow: GET, HEAD"
            , "Alt-Svc: http/1.1=\"http2.example.com:8001\"; ma=7200"
            , "Cache-Control: max-age=3600"
            , "Connection: close"
            , "Content-Disposition: attachment; filename=\"fname.ext\""
            , "Content-Encoding: gzip"
            , "Content-Language: da"
            , "Content-Length: 51"
            , "Content-Location: /index.htm"
            , "Content-MD5: Q2hlY2sgSW50ZWdyaXR5IQ=="
            , "Content-Range: bytes 21010-47021/47022"
            , "Content-Type: text/html; charset=utf-8"
            , "Date: Tue, 15 Nov 1994 08:12:31 GMT"
            , "ETag: \"737060cd8c284d8af7ad3082f209582d\""
            , "Expires: Thu, 01 Dec 1994 16:00:00 GMT"
            , "Last-Modified: Tue, 15 Nov 1994 12:45:26 GMT"
            , "Link: </feed>; rel=\"alternate\""
            , "Location: http://www.w3.org/pub/WWW/People.html"
            , "P3P: CP=\"This is not a P3P policy! See http://www.google.com/support/accounts/bin/answer.py?hl=en&answer=151657 for more info.\""
            , "Pragma: no-cache"
            , "Proxy-Authenticate: Basic"
            , "Public-Key-Pins: max-age=2592000; pin-sha256=\"E9CZ9INDbd+2eRQozYqqbQ2yXLVKB9+xcprMF+44U1g=\";"
            , "Refresh: 5; url=http://www.w3.org/pub/WWW/People.html"
            , "Retry-After: 120"
            , "Retry-After: Fri, 07 Nov 2014 23:59:59 GMT"
            , "Server: Apache/2.4.1 (Unix)"
            , "Set-Cookie: UserID=JohnDoe; Max-Age=3600; Version=1"
            , "Strict-Transport-Security: max-age=16070400; includeSubDomains"
            , "Trailer: Max-Forwards"
            , "Transfer-Encoding: chunked"
            , "Tk: ?"
            , "Upgrade: HTTPS/1.3, IRC/6.9, RTA/x11, websocket"
            , "Vary: *"
            , "Vary: Accept-Language"
            , "Via: 1.0 fred, 1.1 example.com (Apache/1.1)"
            , "Warning: 199 Miscellaneous warning"
            , "WWW-Authenticate: Basic"
            , "X-Frame-Options: deny"
            , "Status: 200 OK"
            , "X-XSS-Protection: 1; mode=block"
            , "X-WebKit-CSP: default-src 'self'"
            , "X-Content-Type-Options: nosniff"
            , "X-Powered-By: PHP/5.4.0"
            , "X-UA-Compatible: IE=EmulateIE7"
            , "X-UA-Compatible: IE=edge"
            , "X-UA-Compatible: Chrome=1"
            , "X-Content-Duration: 42.666"
            , "Upgrade-Insecure-Requests: 1"
            , "X-Request-ID: f058ebd6-02f7-4d3f-942e-904344e8cde5"
            ]
        return $ HTTPMsg start_line header_fields


lalpha :: [Char]
lalpha = ['a'..'z']

ualpha :: [Char]
ualpha = ['A'..'Z']

alpha :: [Char]
alpha = lalpha ++ ualpha

digit :: [Char]
digit = ['0'..'9']

hexdigit :: [Char]
hexdigit = ['a'..'f'] ++ ['A'..'F'] ++ digit

alphanum :: [Char]
alphanum = alpha ++ digit

space :: [Char]
space = [' ', '\t']

lstr :: Q.Gen String
lstr = Q.listOf1 (Q.elements lalpha) :: Q.Gen [Char]

anstr :: Q.Gen String
anstr = Q.listOf1 (Q.elements alphanum) :: Q.Gen [Char]

ipv4 :: Q.Gen String
ipv4 = do
    let octet = show <$> (Q.choose (0,255) :: Q.Gen Int)
    intercalate "." <$> replicateM 4 octet

ipv6 :: Q.Gen String
ipv6 = do
    let hexgroup = do
            k <- Q.choose (1, 4) :: Q.Gen Int
            replicateM k (Q.elements hexdigit)
    n <- Q.choose (0, 8) :: Q.Gen Int
    m <- Q.choose (1, n) :: Q.Gen Int
    hh <- replicateM n hexgroup
    return $ (++ "]") . ("[" ++) $ case n of
        8 -> intercalate ":" hh
        _ -> concat [intercalate ":" (take m hh), "::", intercalate ":" (drop m hh)]

hostname :: Q.Gen String
hostname = do
    subdomains <- Q.listOf1 (take 10 <$> lstr)
    return $ intercalate "." $ take 5 subdomains

filepath :: Q.Gen String
filepath = do
    subdirs <- Q.listOf1 lstr
    return $ concat $ map ("/" ++) $ take 10 subdirs

mayb :: Q.Gen String -> Q.Gen String
mayb gen = Q.oneof [gen, pure ""]

main :: IO ()
main = do
    let f = "http.dat"
    writeFile f ""
    forM_ [0 .. 170000 :: Int] $ \i -> do
        when (i `mod` 1000 == 0) $ print i
        msg <- Q.generate (Q.arbitrary :: Q.Gen HTTPMsg)
        appendFile f $ show msg
