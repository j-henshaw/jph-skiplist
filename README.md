# jph-skiplist
Primitive implementation of the [Skiplist](https://en.wikipedia.org/wiki/Skip_list) probabilistic data structure, written in C++. Originally designed for Dr. Afra Mashadi's CSS 342 class at UW Bothell during Winter 2021.

The skiplist achieves both search and insert functionality in O(log(n)) time. The basic idea is to create a grid-like linked structure, where each column represents a unique entry, and the heights of the columns are randomized upon insertion: Each time you create a new node, flip a coin, and if you get heads, build another node above you, connecting it to the elements on either side which achieve the same height...and so on. Thus, moving upwards along a column one step will bring you to a new row where, ostensibly, half of the entries 'did not make it.' This is how search (and insert—which relies on search in a linked structure) achieve O(log(n)) time.

This implementation is somewhat naïve and probably over-stores duplicate data, though it did receive full marks. Suite of tests and compilation scripts are included as well.
