/**
* This uses Kruskals algorithm to find the minimum spanning tree.
* The time complexity is O(nlogn) where n is the number of edges. This is because of the sorting of the edges
* and the main loop which is O(n) multiplied with the union-find operations which is O(logn) = O(nlogn).
* The algorithm is pretty simple: sort so you have the weight in ascending order, then iterate through the edges
* and add them to the result if they do not form a cycle. This is done by using the union-find data structure.
* Source of inspiration: https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/
*
* Author: Anders Luong (andlu434)
*/
#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// From lab 1 - UnionFind
namespace UnionFind {
  struct UnionSet {
    int parent;
    int size;
  };

  std::vector<UnionSet> createUnions(int const size) {
    std::vector<UnionSet> unions(size);
    for (int i = 0; i < size; i++) {
      unions[i].parent = i;
      unions[i].size = 1;
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

struct Position {
  double x;
  double y;
};

// An edge representing a connection between two nodes
struct Edge {
  double weight;
  int from;
  int to;
};

double minSpanTree(std::vector<Edge>& graph, int const numberOfNodes) {
  double totalWeight = 0;
  std::vector<UnionFind::UnionSet> unions = UnionFind::createUnions(numberOfNodes);

  // sort the edges by weight
  std::sort(graph.begin(), graph.end(), [](Edge const& a, Edge const& b) {
    return a.weight < b.weight;
  });

  for (Edge edge : graph) {
    int from = edge.from;
    int to = edge.to;
    double weight = edge.weight;

    if (!UnionFind::same(from, to, unions)) {
      UnionFind::unionMerge(from, to, unions);
      totalWeight += weight;
    }
  }

  return totalWeight;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int numberOfTestCases;
  std::cin >> numberOfTestCases;

  for (int i = 0; i < numberOfTestCases; i++) {
    int numberOfIslands;
    std::cin >> numberOfIslands;

    std::vector<Edge> graph;

    // building up the graph
    std::vector<Position> islandPositions(numberOfIslands);
    for (int i = 0; i < numberOfIslands; i++) {
      double positionX, positionY;
      std::cin >> positionX >> positionY;
      islandPositions[i] = Position{positionX, positionY};
    }

    for (int island1 = 0; island1 < numberOfIslands - 1; island1++) {
      for (int island2 = island1 + 1; island2 < numberOfIslands; island2++) {
        // weight is Euclidean distance
        double weight = std::sqrt(
          std::pow(islandPositions[island1].x - islandPositions[island2].x, 2) +
          std::pow(islandPositions[island1].y - islandPositions[island2].y, 2)
        );
        graph.push_back(Edge{weight, island1, island2});
      }
    }

    std::cout << std::fixed << std::setprecision(4) << minSpanTree(graph, numberOfIslands) << '\n';
  }
}

