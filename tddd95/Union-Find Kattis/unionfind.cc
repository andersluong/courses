/**
 * Union find algorithm
 * Do operations on set of elements. All elements start off as their own set because they are
 * disjoint from each other. When element needs to be in union with another element, merge
 * them together with a common root. When checking if two elements are in the same set, check
 * if they have the same root. Only finding the root is in O(log n) time. Other operations are
 * in O(1) time.
 *
 * source of inspiration: https://yuminlee2.medium.com/union-find-algorithm-ffa9cd7d2dba
 *
 * Author: Anders Luong
*/
#include <iostream>
#include <vector>

// Namespace where all the union find functions are stored
namespace UnionFind {

struct UnionSet {
  int parent;
  int size;
};

// Initialize the union find data structure
std::vector<UnionSet> initUnionFind(int const numberOfElements) {
  std::vector<UnionSet> unions;

  for (int i = 0; i < numberOfElements; i++) {
    UnionSet u { i, 1 };
    unions.push_back(u);
  }

  return unions;
}

// Find the root of the set that an element is in
int find(int const a, std::vector<UnionSet> & unions) {
  // If the parent of a is itself, then a is the root
  if (unions[a].parent == a) {
    return a;
  }

  // Find the root of the parent of a
  int root = find(unions[a].parent, unions);

  // Flatten out the tree so that all non-root nodes point directly to the root
  unions[a].parent = root;

  return root;
}

// Merge two sets together if they are not already in the same set
void unionMerge(int a, int b, std::vector<UnionSet>& unions) {
  // Find the roots of a and b
  int rootA = find(a, unions);
  int rootB = find(b, unions);

  if (rootA == rootB) {
    // They have the same root, so they are in the same set already
    return;
  }

  // Merge the smaller set into the larger set
  if (unions[rootA].size < unions[rootB].size) {
    unions[rootA].parent = rootB;
    unions[rootB].size += 1;
  } else {
    unions[rootB].parent = rootA;
    unions[rootA].size += 1;
  }
}

// Check if two elements are in the same set
bool same(int const a, int const b, std::vector<UnionSet>& unions) {
  // If the roots of a and b are the same, then they are in the same set
  return find(a, unions) == find(b, unions);
}

}; // namespace UnionFind

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);


  int numberOfElements, numberOfOperations;
  std::cin >> numberOfElements >> numberOfOperations;

  // Initialize the unions
  auto unions = UnionFind::initUnionFind(numberOfElements);

  // Perform the operations
  for (int i = 0; i < numberOfOperations; i++) {
    char operation;
    int a, b;
    std::cin >> operation >> a >> b;

    if (operation == '=') {
      // Merge the two union sets
      UnionFind::unionMerge(a, b, unions);
    } else if (operation == '?') {
      // Check if the two elements are in the same set
      if (UnionFind::same(a, b, unions)) {
        std::cout << "yes\n";
      } else {
        std::cout << "no\n";
      }
    }
  }

}

