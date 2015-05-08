char *scan(char *p)
{
/*!re2c
        re2c:define:YYCTYPE  = "unsigned char";
        re2c:define:YYCURSOR = p;
        re2c:yyfill:enable   = 0;
        re2c:yych:conversion = 1;
        re2c:indent:top      = 1;
        [0-9]+          {return p;}
        [\000-\377]     {return (char*)0;}
*/
}

