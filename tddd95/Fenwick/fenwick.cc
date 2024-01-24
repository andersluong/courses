/**
  * Fenwick Tree 
  * The implementation of Fenwick Tree is based on the article from GeeksForGeeks
  * https://www.geeksforgeeks.org/binary-indexed-tree-or-fenwick-tree-2/?ref=header_search
  *
  * Fenwick Tree builds upon a tree structure that adds values to parent nodes so that half
  * of the elements don't need to be visited. We just traverse up the tree which gives us
  * O(log n) time complexity for both adding and summing values.
  *
  * Author: Anders Luong (andlu434)
*/
#include <iostream>
#include <vector>

// adds delta to index and all its parent nodes
void add(std::vector<long> &fenwickTree, int index, int const delta) {
  index++;
  while (index < (int)fenwickTree.size()) {
    fenwickTree[index] += delta;
    // get parent node (going upwards in the tree)
    index += index & -index;
  }
}

// returns sum of values from 0 to index
long long sum(std::vector<long> const& fenwickTree, int index) {
  index++;
  long long sum = 0;
  while (index > 0) {
    sum += fenwickTree[index];
    // get parent node (going downwards in the tree)
    index -= index & -index;
  }
  return sum;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);

  unsigned lengthOfArray, numberOfOperations;
  std::cin >> lengthOfArray >> numberOfOperations;

  // the fenwick tree is 1 element longer because we don't use index 0 (it's a dummy node)
  std::vector<long> fenwickTree(lengthOfArray + 1, 0);

  for (unsigned i = 0; i < numberOfOperations; i++) {
    char operation;
    int index;
    std::cin >> operation >> index;
    
    if (operation == '+') {
      // append value to index i
      int delta;
      std::cin >> delta;
      add(fenwickTree, index, delta);
    } else if (operation == '?') {
      // print sum of values from 0 to index i
      std::cout << sum(fenwickTree, index - 1) << "\n";
    }
  }
}
