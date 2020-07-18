#!/bin/bash

# code in braces
cat > 000_1.re << EOF
// re2c \$INPUT -o \$OUTPUT -i
/*!re2c
 "01" {}
 "02" {{{}}}
 "03" {"}"}
 "04" {'}'}
 "05" {/*}*/}
 "06" {/*}
        */}
 "07" {//}
      }
 *{}
*/
EOF

# condition lists
cat > 000_2.re << EOF
// re2c \$INPUT -o \$OUTPUT -ci
/*!re2c
 <*>        "01" {}
 <  *  >    "02" {}
 <x>        "03" {}
 <x,y0>     "04" {}
 <x,y0,z11> "05" {}
 <  x  >    "06" {}
 <x, y>     "07" {}
 <x ,y>     "08" {}
 <x , y>    "09" {}
 <!x>            {}
 <  !  y>        {}
 <! y0, z11>     {}
 <>              {}
 <*> *           {}
*/
EOF

i=0
while true; do
    read l || break
    i=$((i + 1))

    # re2c options followed by regexp
    IFS=$'\t'; set $l;
    test $# -lt 2 && { echo "bad line: $l"; exit 1; }
    l='// re2c $INPUT -o $OUTPUT -'
    o=`echo "$1" | sed 's/--/ --/g'`
    r="$2"
    IFS=$' '

    # generate .re files from __patterns file
    f=`printf '%03d' $i`

    printf "${l}${o}\n/*!re2c\n  $r{}\n\t*{\n}\n*/"                   > ${f}_01.re
    printf "${l}${o}\n/*!re2c\n$r  {}\n*\t{\n}\n*/"                   > ${f}_02.re
    printf "${l}${o}\n/*!re2c\n$r\n{}\n*\n{\n}\n*/"                   > ${f}_03.re

    printf "${l}${o}\n/*!re2c\n  $r:=  ;\n\t*:=;\n*/"                 > ${f}_04.re
    printf "${l}${o}\n/*!re2c\n$r  :=;\n*\t:=\t;\n*/"                 > ${f}_05.re
    printf "${l}${o}\n/*!re2c\n$r := ;\n ;\n* := ;\n ;\n*/"           > ${f}_06.re

    printf "${l}c${o}\n/*!re2c\n <x> $r {}\n< y,x>*{}\n*/"            > ${f}_07.re
    printf "${l}c${o}\n/*!re2c\n <x> $r := ;\n<y ,x>*:=;\n*/"         > ${f}_08.re
    printf "${l}c${o}\n/*!re2c\n <x> $r => z {}\n<y, x>*=>x{}\n*/"    > ${f}_09.re
    printf "${l}c${o}\n/*!re2c\n <x> $r => z := ;\n<y,x >*=>x:=;\n*/" > ${f}_10.re
done < __patterns

echo "all done!"
