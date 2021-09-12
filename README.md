Implementation of the AVL Binary Search Tree. AVL is balanced Binary Search Tree (BST),
where difference in height between left and right nodes, for each node,
can not be more than 1. Operations like insert, delete and search nodes in BST have
cost that is proportional to tree height, O(h) or logN, where N is number of nodes
in tree, O(logN). The cost of these operations can become O(N). By balancing the
tree after every insertion, we can make sure that the cost remains O(logN).

CMake is used for project build. For building tests for testAVL.cpp,
Catch2 repo from GitHub (https://github.com/catchorg/Catch2)
is pulled in local project skipList. Doxygen is used for project documentation.

To build project and project documentation, go to root directory:
<pre>
$ cd root
$ mkdir build
$ cd build
$ cmake ..
$ make
$ make doc

To run tests:
$ cd test
$ ./tests
</pre>
To check valgrind: valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./tests

Benchmark results for insert and search:
<pre>
-------------------------------------------------------------------------------
AVL insert and search - Benchmark
-------------------------------------------------------------------------------
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Add 100.000 nodes in tree                      100             1     1.30494 m
                                         675.99 ms    662.261 ms    694.834 ms
                                         81.341 ms    63.7082 ms    100.218 ms

Search 100 nodes in tree of 100.000
nodes                                          100             5    16.3555 ms
                                          33.35 us    32.9377 us    33.9122 us
                                         2.4404 us    1.92014 us    3.15254 us
</pre>
