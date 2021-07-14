// re2c $INPUT -o $OUTPUT -c

/*!re2c re2c:yyfill:enable = 0; */

// types:re2c
/*!types:re2c */

// types:re2c format = "static const int @@{cond} = @@{num};\n";
/*!types:re2c
    format = "static const int @@{cond} = @@{num};\n";
*/

// types:re2c (all on one line) format = "\t@@,\n";
enum YYCONDTYPE {/*!types:re2c format = "\t@@,\n"; */};

// types:re2c (all on one line) format = "\t@@,\n"; separator = "\n";
enum YYCONDTYPE {/*!types:re2c format = "\t@@,"; separator = "\n"; */};

// types:re2c (multiple lines) format = "\t@@,\n";
enum YYCONDTYPE {
/*!types:re2c
    format = "\t@@,\n";
*/
};

// types:re2c (multiple lines) format = "\t@@,\n"; separator = "\n";
enum YYCONDTYPE {
/*!types:re2c
    format = "\t@@,";
    separator = "\n";
*/
};

// types:re2c format = "static const int @@;\n";
/*!types:re2c
    format = "static const int @@";
    separator = "; ";
*/

// unnamed global block (conditions C1, C2)
/*!re2c
    re2c:startlabel = "Lstart";
    <C1> [a]  => C2 { goto Lstart; }
    <C2> [b] :=> C1
    <*>  *          { return; }
*/

// local block 'x' (conditions C1, C3)
/*!local:re2c:x
    re2c:condprefix = 'Lx_';
    <C1> [a]  => C3 { goto Lx_C3; }
    <C3> [b] :=> C1
    <*>  *          { return x; }
*/
