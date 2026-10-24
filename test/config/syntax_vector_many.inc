code:vector_loop =
    topindent (.many ? "many ranges" : "one range") nl
    [range: topindent range_lo "-" range_hi (.range.many ? " interval" : " singleton")
        (.many ? " (many)" : " (one)") nl
        [xrange: topindent xrange_lo "-" xrange_hi
            (.xrange.many ? " interval" : " singleton")
            (.range.many ? " in interval" : " in singleton") nl]
        topindent (.range.many ? "interval again" : "singleton again") nl]
    [xrange: topindent xrange_lo "-" xrange_hi (.xrange.many ? " interval" : " singleton")
        (.many ? " (many)" : " (one)") nl]
    topindent (.many ? "many ranges again" : "one range again") nl;
