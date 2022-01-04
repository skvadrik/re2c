// re2rust $INPUT -o $OUTPUT

// expect label 'woot
/*!local:re2c re2c:label:yyloop = "'woot"; [a] {} * {} */

// expect label 'yyl (reset as the previous block is local)
/*!re2c [a] {} * {} */

// expect no label
/*!re2c re2c:label:yyloop = ""; [a] {} * {} */
