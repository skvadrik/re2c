[-Wswapped-range]
--------------------------

``-Wswapped-range`` warning is reported in cases when a character class contains
a range which lower bound is greater than the upper bound. For some strange
reason older versions of re2c did not consider this an error and silently
swapped range bounds. Consider the following example (swapped.re):

.. code-block:: cpp

    /*!re2c
        *     { return "*"; }
        [a-Z] { return "is it what you wanted?"; }
    */

Re2c interprets this code as ``[Z-a]``, but generates a warning:

.. code-block:: none

    $ re2c -Wswapped-range swapped.re -o swapped.c
    swapped.re:3:5: warning: range lower bound (0x61) is greater than upper bound (0x5A), swapping [-Wswapped-range]

Use ``[-Werror-swapped-range]`` to make it an error.


