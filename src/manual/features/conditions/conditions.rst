Conditions
----------

.. toctree::
    :hidden:

You can precede regular expressions with a list of condition names when
using the ``-c`` switch. ``re2c`` will then generate a scanner block for
each condition, and each of the generated blocks will have its own
precondition. The precondition is given by the interface define
``YYGETCONDITON()`` and must be of type ``YYCONDTYPE``.

There are two special rule types. First, the rules of the condition ``<*>``
are merged to all conditions (note that they have a lower priority than
other rules of that condition). And second, the empty condition list
allows to provide a code block that does not have a scanner part,
meaning it does not allow any regular expressions. The condition value
referring to this special block is always the one with the enumeration
value 0. This way the code of this special rule can be used to
initialize a scanner. It is in no way necessary to have these rules: but
sometimes it is helpful to have a dedicated uninitialized condition
state.

Non empty rules allow to specify the new condition, which makes them
transition rules. Besides generating calls for the 
``YYSETCONDTITION`` define, no other special code is generated.

There is another kind of special rule that allows to prepend code to any
code block of all rules of a certain set of conditions or to all code
blocks of all rules. This can be helpful when some operation is common
among rules. For instance, this can be used to store the length of the
scanned string. These special setup rules start with an exclamation mark
followed by either a list of conditions ``<! condition, ... >`` or a star
``<!*>``. When ``re2c`` generates the code for a rule whose state does not have a
setup rule and a starred setup rule is present, the starred setup code will be
used as setup code.

