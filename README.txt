Pavel's Poker AI
================

Effectiveness
-------------

The actual AI is pretty sucky. I don't expect it to do that well,
given that the strategy is extremely naive. It's implementation
is the real "treat".

Running
-------

To compile, make sure that **all** of the files that came in the
original folder are in the folder where compilation occurs. This is
*crucial*. Even files you thought were unnecessary sometimes turn out to
be oh-so-crucial.

After that is done, you should be able to just compile ``HandPavel.cpp``,
which should include all of the other files necessary.

Reading
-------

For the sake of the sanity of the reader, it is suggested that all files
beginning with `l_` never, ever be looked at. They range from horrible
to despicable to alright, but mostly the first two and rarely the latter.

If you must, the proper order to read them in is: ``l_c.h``, ``l_c.cc``,
``l_i.cc``, ``l_p.cc``, ``l_e.cc``, ``l_l.cc``. It is to be noted that the
last of those, ``l_l.cc`` , will cause most C programmers to bang their head
repeatedly against the table. Several cases of bleeding to death have been
reported.

After reading these, and after the impulsive vomitting has ceased, it should
be reasonably safe to read ``algorithm-overview.txt``. It describes the
basic algorithm in an easy-to-read format: Lisp code. This choice is, of
course, purely coincidental and provided for your convenience. Other than
that, the file has no purpose at all. Just explain the algorithm. That's all.

Design
------

    A novice programmer was once assigned to code a simple financial package.

    The novice worked furiously for many days, but when his master reviewed his
    program, he discovered that it contained a screen editor, a set of
    generalized graphics routines, an artificial intelligence interface, but
    not the slightest mention of anything financial.

    When the master asked about this, the novice became indignant. ``Don't be
    so impatient,'' he said, ``I'll put in the financial stuff eventually.''

                                        `The Tao of Programming`, koan 5.4

Thus is the program designed.
