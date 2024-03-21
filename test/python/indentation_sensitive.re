# re2py $INPUT -o $OUTPUT

/*!re2c
    re2c:indent:top = 1;

    * { *** }

    [a] {
        aaa
    }

    [b] {
        bbb 1
          bbb 2
        bbb 3
    }

    [c] {ccc 1
ccc 2
  ccc 3}

    [d] {  ddd 1
  ddd 2
    ddd 3  }

[e] := eee
[f] :=
  fff 1
    fff 2
  fff 3
[g] :=ggg 1
  ggg 2
    ggg 3

[h] :=
[i] :=  
[j] :=

[k] :=
  
[l] {}
    [m] { }
    [n] {
        
    }
[o] :=

  ooo
[p] :=
  ppp
  
*/
