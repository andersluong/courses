#include <iostream>
#include <vector>

namespace Fenwick {
// adds delta to index and all its parent nodes
void add(std::vector<int> &fenwickTree, int index, int const delta) {
  index++;
  while (index < (int)fenwickTree.size()) {
    fenwickTree[index] += delta;
    // get parent node (going upwards in the tree)
    index += index & -index;
  }
}

// returns sum of values from 0 to index
long sum(std::vector<int> const& fenwickTree, int index) {
  index++;
  long sum = 0;
  while (index > 0) {
    sum += fenwickTree[index];
    // get parent node (going downwards in the tree)
    index -= index & -index;
  }
  return sum;
}

} // namespace Fenwick

int main() {
  unsigned numberOfElements;
  std::cin >> numberOfElements;
  std::vector<int> indexes(numberOfElements + 1, 0);
  // initialize fenwick tree with 1's representing the number of swaps needed
  std::vector<int> fenwickTree(numberOfElements + 1, 0);

  // read indexes and put them in an array where the value tells us where the number is located
  for (int i = 0; i < (int)numberOfElements; i++) {
    int index;
    std::cin >> index;
    indexes[index] = i;
    Fenwick::add(fenwickTree, i, 1);
  }

  // for (auto x : fenwickTree) {
  //   std::cout << x << " ";
  // }
  // std::cout << "\n";

  unsigned startIndex = 1;
  unsigned endIndex = numberOfElements;

  for (int i = 0; i < (int)numberOfElements; i++) {
    if (i % 2 == 0) {
      // first index from left, and alternating
      Fenwick::add(fenwickTree, indexes[startIndex], -1);
      std::cout << Fenwick::sum(fenwickTree, indexes[startIndex]) << "\n";
      // std::cout << "from left: ";
      // for (auto x : fenwickTree) {
      //   std::cout << x << " ";
      // }
      // std::cout << "\n";
      startIndex++;
    } else {
      // then from right
      Fenwick::add(fenwickTree, indexes[endIndex], -1);
      std::cout << Fenwick::sum(fenwickTree, numberOfElements - 1) - Fenwick::sum(fenwickTree, indexes[endIndex]) << "\n";
      // std::cout << "from right: ";
      // for (auto x : fenwickTree) {
      //   std::cout << x << " ";
      // }
      // std::cout << "\n";
      endIndex--;
    }
  }
}
