// Override of `code:vector_loop` that tests the class complement (`xrange` list): exit bytes are
// found with equality comparisons for single code units (`.xrange.many` is false) and with range checks
// otherwise. The guard uses `need` and `YYLIMIT` instead of the opaque `lessthan` expression.
// If the complement is empty, nothing is loaded or compared: the loop only skips whole blocks.
code:vector_loop =
    topindent "if " YYCURSOR " + " need " <= " YYLIMIT " {" nl
    indent
    topindent "// class:" [range{0:-1}: " [" range_lo ", " range_hi "]"] nl
    [xrange{0:-1}: (.xrange.many
        ? topindent "yyxl" xrange_lo " := archsimd.BroadcastUint8x" size "(" xrange_lo ")" nl
          topindent "yyxs" xrange_lo " := archsimd.BroadcastUint8x" size "(" xrange_hi " - " xrange_lo ")" nl
        : topindent "yyxe" xrange_lo " := archsimd.BroadcastUint8x" size "(" xrange_lo ")" nl)]
    topindent "for {" nl
        indent
        [xrange{0}: topindent "yysimd0 := archsimd.LoadUint8x" size "(" YYINPUT "[" YYCURSOR ":" YYCURSOR " + " size "])" nl
            topindent "yysimd1 := archsimd.BroadcastUint8x" size "(0).Less(archsimd.BroadcastUint8x" size "(0))" nl]
        [xrange{0:-1}: (.xrange.many
            ? topindent "yyt" xrange_lo " := yysimd0.Sub(yyxl" xrange_lo ")" nl
              topindent "yysimd1 = yysimd1.Or(yyt" xrange_lo ".Min(yyxs" xrange_lo ").Equal(yyt" xrange_lo "))" nl
            : topindent "yysimd1 = yysimd1.Or(yysimd0.Equal(yyxe" xrange_lo "))" nl)]
        [xrange{0}: topindent "if yym := yysimd1.ToBits(); yym != 0 {" nl
            indent topindent YYCURSOR " += bits.TrailingZeros32(yym)" nl topindent "break" nl dedent
        topindent "}" nl]
        topindent YYCURSOR " += " size nl
        topindent "if " YYCURSOR " + " need " > " YYLIMIT " {" nl
            indent topindent "break" nl dedent
        topindent "}" nl
        dedent
    topindent "}" nl
    [xrange{0}: topindent "archsimd.ClearAVXUpperBits()" nl]
    dedent
    topindent "}" nl;
