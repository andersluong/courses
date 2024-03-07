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

class Fenwick {
public:
  // the fenwick tree is 1 element longer because we don't use index 0 (it's a dummy node)
  Fenwick(int const size) : fenwickTree(size + 1, 0) {}

  // adds delta to index and all its parent nodes
  void add(int index, int const delta) {
    index++;
    while (index < (int)fenwickTree.size()) {
      fenwickTree[index] += delta;
      // get parent node (going upwards in the tree)
      index += index & -index;
    }
  }

  // returns sum of values from 0 to index
  long long sum(int index) const {
    index++;
    long long sum = 0;
    while (index > 0) {
      sum += fenwickTree[index];
      // get parent node (going downwards in the tree)
      index -= index & -index;
    }
    return sum;
  }
private:
  std::vector<long> fenwickTree;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);

  unsigned lengthOfArray, numberOfOperations;
  std::cin >> lengthOfArray >> numberOfOperations;

  Fenwick fenwick = Fenwick(lengthOfArray);

  for (unsigned i = 0; i < numberOfOperations; i++) {
    char operation;
    int index;
    std::cin >> operation >> index;
    
    if (operation == '+') {
      // append value to index i
      int delta;
      std::cin >> delta;
      fenwick.add(index, delta);
    } else if (operation == '?') {
      // print sum of values from 0 to index i
      std::cout << fenwick.sum(index - 1) << "\n";
    }
  }
}
