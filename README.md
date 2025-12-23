# Self Balancing RBTree_Implementation

1. Project Overview
   This project is a high-performance C++ implementation of a Red-Black Tree, a self-balancing binary search tree that guarantees O(log n) time complexity for search, insertion, and deletion. The project includes a comprehensive benchmarking suite to compare performance against standard (unbalanced) Binary Search Trees.

2. Key Features
  CLRS Standard Logic: Implements the classic algorithms for insertion and deletion fixups as defined in Introduction to Algorithms.
  Memory Efficiency: Utilizes the Sentinel Node Pattern (Nil nodes) to reduce memory overhead and simplify edge-case handling.
  Modular Design: Implemented as a header-only library (.hpp) for easy integration into other C++ projects.

3. Performance Analysis
  The primary goal of this implementation was to solve the Linear Skewing problem found in normal BSTs.

  Comparative Results (Sorted Input N = 10,000)
          Metric                Normal BST                  RBTree                      Improvement
          Treeheight            10000                       26                          99.7%
          Insertion_TIME(us)    200342                      15693                       92.2%        
          SearchComplexity      O(n)                        O(log n)                    Logarithmic

