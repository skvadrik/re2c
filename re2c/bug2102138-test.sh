#!/bin/sh

make && \
for n in $(find test -name '*2102138*.re'|sed 's,.re,,'); do
	./run_tests.sh ${n}.re
	test -f ${n}.c.temp && mv -f ${n}.c.temp ${n}.c
	gcc ${n}.c -o ${n}.o
	./${n}.o >${n}.out
	if $(diff -du ${n}.txt ${n}.out >${n}.out.diff); then
	  echo "OK"
	  rm -f ${n}.out ${n}.out.diff
	else
	  echo "FAIL"
	fi
done