re2c lesson_001, (c) M. Boerger 2006

This lesson gets you started with re2c. In the end you will have an easy UPN
calculator for use at command line.

You will learn about the basic interface of re2c when scanning input strings. 
How to detect the end of the input and use that to stop scanning in order to
avoid problems.

Once you have successfully installed re2c you can use it to generate *.c files
from the *.re files presented in this lesson. Actually the expected *.c files 
are already present. So you should name them *.cc or something alike or just 
give them a different name like test.c. To do so you simply change into the 
directory and execute the following command:

  re2c calc_001.re > test.c

Then use your compiler to compile that code and run it.

When you want to debug the code it helps to make re2c generate working #line
information. To do so you simply specify the output file using the -o switch 
followed by the output filename:

  re2c -o test.c calc_001.re

The input files *.re each contain basic step by comments that explain what is
going on and what you can see in the examples.

In order to optimize the generated code we will use the -s command line switch
of re2c. This tells re2c to generate code that uses if statements rather 
then endless switch/case expressions where appropriate. Note that the file name
extension is actually '.s.re' to tell the test system to use the -s switch. To
invoke re2 you do the following:

  re2c -s -o test.c calc_006.s.re

Finally we use the -b switch to have the code use a decision table. The -b 
switch also contains the -s behavior. 

  re2c -b -o test.c calc_007.b.re
