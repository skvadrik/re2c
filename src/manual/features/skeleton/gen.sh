printf "%10s%10s%10s%10s\n\n" iters edges input keys
for i in `seq $1 $2`
do
    echo '/*!re2c * {} [0-9a-fA-F]{'$i'} {} */' | re2c -S -o example.c -
    input=`stat -c '%s' example.c.line1.input`
    keys=`stat -c '%s' example.c.line1.keys`
    printf "%10d%10d%10d%10d\n" $i $((256 * i)) $input $keys
done
