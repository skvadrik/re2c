#!/bin/bash

test $# -ne 1 && { echo "usage: ./__run.sh <path-to-re2c>"; exit 1; }
re2c="$1"


# code in braces
cat > 000_1.i.re << EOF
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
cat > 000_2.ci.re << EOF
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
    sfx="$1"; r="$2"; IFS=$' '

    # generate .re files from __patterns file
    f=`printf '%03d' $i`

    printf "/*!re2c\n  $r{}\n\t*{\n}\n*/"                  > ${f}_01.${sfx}.re
    printf "/*!re2c\n$r  {}\n*\t{\n}\n*/"                  > ${f}_02.${sfx}.re
    printf "/*!re2c\n$r\n{}\n*\n{\n}\n*/"                  > ${f}_03.${sfx}.re

    printf "/*!re2c\n  $r:=  ;\n\t*:=;\n*/"                > ${f}_04.${sfx}.re
    printf "/*!re2c\n$r  :=;\n*\t:=\t;\n*/"                > ${f}_05.${sfx}.re
    printf "/*!re2c\n$r := ;\n ;\n* := ;\n ;\n*/"          > ${f}_06.${sfx}.re

    printf "/*!re2c\n <x> $r {}\n< y,x>*{}\n*/"            > ${f}_07.c${sfx}.re
    printf "/*!re2c\n <x> $r := ;\n<y ,x>*:=;\n*/"         > ${f}_08.c${sfx}.re
    printf "/*!re2c\n <x> $r => z {}\n<y, x>*=>x{}\n*/"    > ${f}_09.c${sfx}.re
    printf "/*!re2c\n <x> $r => z := ;\n<y,x >*=>x:=;\n*/" > ${f}_10.c${sfx}.re

done < __patterns


# generate .c files from .re files
for f in *.re; do
    opts=-`echo $f | sed -E -e 's/[^.]+\.([^.]+)\.re/\1/' -e 's/--/ --/g'`
    $re2c $opts $f -W --no-generation-date --no-version -o${f%.re}.c 2>warnings \
        && cat warnings >> ${f%.re}.c && rm warnings \
        || echo "failed on $f"
done


echo "all done!"
