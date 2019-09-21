# research-of-sorting
it contains C++ implementations of various sorting algorithms together with scripts which provide a test suite to measure these algorithms performance and memory requirements

array.cpp - an array sort implementation

baseop.cpp - several base operations required by some sort methods

boost.cpp - a wrapper to use sort methods from the boost libraries: spreadsort, pdqsort, spinsort, flat\_stable\_sort

bsd.cpp - a wrapper to use sort methods from the bsd library: mergesort, heapsort, radixsort, sradixsort

bubble.cpp - a bubble sort implementation

check-stable.cpp - it used to check a method the stable feature

fillings.cpp - it provides various data filling methods

hash.cpp - a hash sort implementation

hashtree.cpp - three sort methods which use hashes which use binary trees instead of lists, the first method uses an unbalanced tree, the second - a tree (std::multiset) from the C++ standard library, the third - a tree (boost::container::multiset) from the boost library

insertion.cpp - an insertion sort implementation

method-test.cpp - it is used to check the correctness of a method

nsort.cpp - the main program to gather results of work with various data

nsort-all.cpp - the main program to gather results of work with all permutations

oms7.cpp - a wrapper to use several sort methods from a [repo](https://pastebin.com/M08sgZS6) - copy all required methods to a file named _oms7base.cpp_ and put it into _opt_ subdirectory

quick-dp.cpp - a dual pivots quick sort implementation

quick-hoare.cpp - a Hoare's quick sort implementation with the pivot in the middle

quick-lomuto.cpp - a Lomuto's quick sort implementation

quick-np.cpp - an implementation of the quick sort without pivots

radix.cpp - the LSD radix sort implementation

radix-msd.cpp - the MSD radix sort implementation

selection.cpp - a selection sort implementation

shell-plain.cpp - a Shell's sort implementation without tables

shell-tab.cpp - Shell's sort implementations with tables

std.cpp - a wrapper to use sort methods from the C++ standard library: qsort, sort\_heap, sort, stable\_sort

tim.cpp - a wrapper to use a Tim sort implementation from a [repo](https://github.com/gfx/cpp-TimSort) - put the required header file into _opt_ subdirectory

tree.cpp - two implementations of the binary tree sort using the boost and C++ standard libraries

trie.cpp - a trie sort implementation

The gathered performance results are placed into two interactive tables: the [first](https://litwr2.github.io/ros/table1.html) one contains data for particular large sorting arrays, the [second](https://litwr2.github.io/ros/table2.html) one contains data for tiny sorting arrays which iterate through all possible order of elements.

A static [table](https://litwr2.github.io/ros/table3.html) contains data about additional memory requirements for various sort methods.
