// Overrides default YYFILL implementation.

/*!rules:re2c
    // don't fail if YYFILL fails (because of the greedy garbage lexeme)
    re2c:define:YYFILL = "if (fill(in, @@) != 0) return 0;";
*/
