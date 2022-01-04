// re2c $INPUT -o $OUTPUT
/*!re2c
    re2c:api = custom;
    re2c:flags:input = default;
    re2c:api:style = free-form;
    re2c:api:sigil = "";

    re2c:header = "all_configs.h";
    re2c:flags:type-header = "all_configs.h";
    re2c:flags:t = "all_configs.h";

    re2c:eof = -1;
    re2c:sentinel = 0;

    re2c:yyfill:enable = 0;
    re2c:yyfill:parameter = 0;
    re2c:yyfill:check = 0;

    re2c:tags = 0;
    re2c:flags:tags = 0;
    re2c:flags:T = 0;
    re2c:posix-captures = 0;
    re2c:flags:posix-captures = 0;
    re2c:flags:P = 0;
    re2c:tags:prefix = "";
    re2c:tags:expression = "";

    re2c:define:YYBACKUP = "";
    re2c:define:YYBACKUPCTX = "";
    re2c:define:YYCONDTYPE = "";
    re2c:define:YYCTYPE = "";
    re2c:define:YYCTXMARKER = "";
    re2c:define:YYCURSOR = "";
    re2c:define:YYDEBUG = "";
    re2c:define:YYFILL = "";
    re2c:define:YYFILL@len = "";
    re2c:define:YYFILL:naked = 0;
    re2c:define:YYGETCONDITION = "";
    re2c:define:YYGETCONDITION:naked = 0;
    re2c:define:YYGETSTATE = "";
    re2c:define:YYGETSTATE:naked = 0;
    re2c:define:YYLESSTHAN = "";
    re2c:define:YYLIMIT = "";
    re2c:define:YYMARKER = "";
    re2c:define:YYMTAGN = "";
    re2c:define:YYMTAGP = "";
    re2c:define:YYPEEK = "";
    re2c:define:YYRESTORE = "";
    re2c:define:YYRESTORECTX = "";
    re2c:define:YYRESTORETAG = "";
    re2c:define:YYSETCONDITION = "";
    re2c:define:YYSETCONDITION@cond = "";
    re2c:define:YYSETCONDITION:naked = 0;
    re2c:define:YYSETSTATE = "";
    re2c:define:YYSETSTATE:naked = 0;
    re2c:define:YYSETSTATE@state = "";
    re2c:define:YYSHIFT = "";
    re2c:define:YYSHIFTSTAG = "";
    re2c:define:YYSHIFTMTAG = "";
    re2c:define:YYSKIP = "";
    re2c:define:YYSTAGN = "";
    re2c:define:YYSTAGP = "";

    re2c:variable:yyctable = "";
    re2c:variable:yyaccept = "";
    re2c:variable:yytarget = "";
    re2c:variable:yystate = "";
    re2c:variable:yych = "";
    re2c:variable:yych:conversion = 0;
    re2c:yych:conversion = 0;
    re2c:variable:yych:emit = 0;
    re2c:yych:emit = 0;
    re2c:variable:yybm = "";
    re2c:variable:yybm:hex = 0;
    re2c:yybm:hex = 0;
    re2c:variable:yystable = "";

    re2c:cond:prefix = "";
    re2c:condprefix = "";
    re2c:cond:enumprefix = "";
    re2c:condenumprefix = "";
    re2c:cond:divider = "";
    re2c:cond:divider@cond = "";
    re2c:cond:goto = "";
    re2c:cond:goto@cond = "";

    re2c:state:abort = 0;
    re2c:state:nextlabel = 0;

    re2c:bit-vectors = 0;
    re2c:flags:bit-vectors = 0;
    re2c:flags:b = 0;
    re2c:debug-output = 0;
    re2c:flags:debug-output = 0;
    re2c:flags:d = 0;
    re2c:computed-gotos = 0;
    re2c:flags:computed-gotos = 0;
    re2c:flags:g = 0;
    re2c:computed-gotos:threshold = 0;
    re2c:cgoto:threshold = 0;
    re2c:nested-ifs = 0;
    re2c:flags:nested-ifs = 0;
    re2c:flags:s = 0;
    re2c:case-insensitive = 0;
    re2c:flags:case-insensitive = 0;
    re2c:case-inverted = 0;
    re2c:flags:case-inverted = 0;
    re2c:case-ranges = 0;
    re2c:flags:case-ranges = 0;
    re2c:unsafe = 0;
    re2c:flags:unsafe = 0;

    re2c:encoding:ebcdic = 0;
    re2c:flags:ecb = 0;
    re2c:flags:e = 0;
    re2c:encoding:utf32 = 0;
    re2c:flags:unicode = 0;
    re2c:flags:u = 0;
    re2c:encoding:ucs2 = 0;
    re2c:flags:wide-chars = 0;
    re2c:flags:w = 0;
    re2c:encoding:utf16 = 0;
    re2c:flags:utf-16 = 0;
    re2c:flags:x = 0;
    re2c:encoding:utf8 = 0;
    re2c:flags:utf-8 = 0;
    re2c:flags:8 = 0;

    re2c:flags:encoding-policy = ignore;
    re2c:encoding-policy = ignore;
    re2c:flags:encoding-policy = substitute;
    re2c:encoding-policy = substitute;
    re2c:flags:encoding-policy = fail;
    re2c:encoding-policy = fail;

    re2c:empty-class  = match-empty;
    re2c:flags:empty-class = match-empty;
    re2c:empty-class = match-none;
    re2c:flags:empty-class = match-none;
    re2c:empty-class = error;
    re2c:flags:empty-class = error;

    re2c:indent:string = "";
    re2c:indent:top = 0;

    re2c:label:prefix = "";
    re2c:labelprefix = "";
    re2c:label:yyfill = "";
    re2c:label:yyFillLabel = "";
    re2c:label:yyloop = "";
    re2c:label:yyNext = "";
    re2c:label:start = 0;
    re2c:startlabel = "";
    re2c:label:start = 0;
    re2c:startlabel = "";
*/
