/* autogen */
// re2c:define:YYSETCONDITION = "setcondition (#);";
// re2c:define:YYSETCONDITION@cond = #;
// re2c:define:YYSETCONDITION:naked = 0;

/*!re2c
    re2c:define:YYSETCONDITION = "setcondition (#);";
    re2c:define:YYSETCONDITION@cond = #;
    re2c:define:YYSETCONDITION:naked = 0;

    <c1> "a" => c2 { code1 }
    <c2> "b" => c1 { code2 }
    <*> * { def }

*/
