+++++++++++
User manual
+++++++++++

Syntax
======
.. include:: /manual/syntax/syntax.rst_
.. include:: /manual/syntax/example.rst

Regular expressions
===================
.. include:: /manual/regexps/regular_expressions.rst_

User interface
==============
.. include:: /manual/api/interface.rst_
.. include:: /manual/api/api.rst_

Directives
==========
.. include:: /manual/directives/directives.rst_

Options
=======
.. include:: /manual/options/options.rst_
.. include:: /manual/options/debug.rst_
.. include:: /manual/options/internal.rst_

Configurations
==============
.. include:: /manual/configurations/configurations.rst_

EOF handling
============
.. include:: /manual/eof/eof.rst_
.. include:: /manual/eof/01_sentinel.rst_
.. literalinclude:: /manual/eof/01_sentinel.re
    :language: c
.. include:: /manual/eof/02_bounds_checking.rst_
.. literalinclude:: /manual/eof/02_bounds_checking.re
    :language: c
.. include:: /manual/eof/03_eof_rule.rst_
.. literalinclude:: /manual/eof/03_eof_rule.re
    :language: c
.. include:: /manual/eof/04_generic_api.rst_
.. literalinclude:: /manual/eof/04_generic_api.re
    :language: c

Buffer refilling
================
.. include:: /manual/fill/fill.rst_
.. include:: /manual/fill/01_fill.rst_
.. literalinclude:: /manual/fill/01_fill.re
    :language: c
.. include:: /manual/fill/02_fill.rst_
.. literalinclude:: /manual/fill/02_fill.re
    :language: c

Include files
=============
.. include:: /manual/includes/includes.rst_

Header files
============
.. include:: /manual/headers/headers.rst_

Submatch extraction
===================
.. include:: /manual/submatch/submatch.rst_
.. include:: /manual/submatch/submatch_example_stags.rst_
.. literalinclude:: /manual/submatch/stags.re
    :language: c
.. include:: /manual/submatch/submatch_example_posix.rst_
.. literalinclude:: /manual/submatch/posix.re
    :language: c
.. include:: /manual/submatch/submatch_example_mtags.rst_
.. literalinclude:: /manual/submatch/mtags.re
    :language: cpp

Storable state
==============
.. include:: /manual/state/state.rst_
.. literalinclude:: /manual/state/push.re
    :language: c

Reusable blocks
===============
.. include:: /manual/reuse/reuse.rst_
.. literalinclude:: /manual/reuse/reuse.re
    :language: c

Encoding support
================
.. include:: /manual/encodings/encodings.rst_

Start conditions
================
.. include:: /manual/conditions/conditions.rst_

Skeleton programs
=================
.. include:: /manual/skeleton/skeleton.rst_
.. include:: /manual/skeleton/skeleton_example.rst

Visualization and debug
=======================
.. include:: /manual/dot/dot.rst_
.. include:: /manual/dot/example.rst

Warnings
========
.. include:: /manual/warnings/warnings_general.rst_
.. include:: /manual/warnings/warnings_list.rst_
.. include:: /manual/warnings/undefined_control_flow/wundefined_control_flow.rst
.. include:: /manual/warnings/unreachable_rules/wunreachable_rules.rst
.. include:: /manual/warnings/condition_order/wcondition_order.rst
.. include:: /manual/warnings/useless_escape/wuseless_escape.rst
.. include:: /manual/warnings/swapped_range/wswapped_range.rst
.. include:: /manual/warnings/empty_character_class/wempty_character_class.rst
.. include:: /manual/warnings/match_empty_string/wmatch_empty_string.rst
.. include:: /manual/warnings/sentinel_in_midrule/wsentinel_in_midrule.rst

More examples
=============
.. include:: /examples/examples.rst
