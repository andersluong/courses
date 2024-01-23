// https://www.geeksforgeeks.org/binary-indexed-tree-or-fenwick-tree-2/?ref=header_search
#include <iostream>
#include <vector>

void add(std::vector<int> &fenwickTree, int index, int const delta) {
  index++;
  while (index <= fenwickTree.size()) {
    fenwickTree[index] += delta;
    index += index & -index;
  }
}

int sum(std::vector<int> &fenwickTree, int index) {
  index++;
  int sum = 0;
  while (index > 0) {
    sum += fenwickTree[index];
    index -= index & -index;
  }
  return sum;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);

  int lengthOfArray, numberOfOperations;
  std::cin >> lengthOfArray >> numberOfOperations;

  std::vector<int> fenwickTree(lengthOfArray + 1, 0);

  for (int i = 0; i < numberOfOperations; i++) {
    char operation;
    int index;
    std::cin >> operation >> index;
    
    if (operation == '+') {
      // append value to index i
      int delta;
      std::cin >> delta;
      add(fenwickTree, index, delta);
      for (auto const& value : fenwickTree) {
        std::cout << value << " ";
      }
      std::cout << "\n";
    } else if (operation == '?') {
      // print sum of values from 0 to index i
      std::cout << sum(fenwickTree, index) << "\n";
    }
  }
  std::cout << "\n";
}
