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
#include <iostream>
#include <set>
#include <utility>
#include <vector>
#include <algorithm>

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
} // namespace UnionFind

// An edge representing a connection between two nodes
struct Edge {
  int weight;
  int from;
  int to;
};

// Comparator for the set
struct Comparator {
  bool operator()(Edge const& a, Edge const& b) const {
    if (a.from == b.from) {
      return a.to < b.to;
    }
    return a.from < b.from;
  }
};

int minSpanTree(std::vector<Edge>& graph, std::set<Edge, Comparator>& result, int const numberOfNodes) {
  int totalWeight = 0;
  std::vector<UnionFind::UnionSet> unions = UnionFind::createUnions(numberOfNodes);

  // sort the edges by weight
  std::sort(graph.begin(), graph.end(), [](Edge const& a, Edge const& b) {
    return a.weight < b.weight;
  });

  for (Edge edge : graph) {
    int from = edge.from;
    int to = edge.to;
    int weight = edge.weight;

    if (!UnionFind::same(from, to, unions)) {
      UnionFind::unionMerge(from, to, unions);
      result.insert(edge);
      totalWeight += weight;

      // break early if we have found a spanning tree
      if ((int)result.size() == numberOfNodes - 1) {
        break;
      }
    }
  }

  return totalWeight;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  while (true) {
    int numberOfNodes, numberOfEdges;
    std::cin >> numberOfNodes >> numberOfEdges;

    if (numberOfNodes == 0 && numberOfEdges == 0) {
      break;
    }

    std::vector<Edge> graph(numberOfEdges);

    // building up the graph
    for (int i = 0; i < numberOfEdges; i++) {
      int from, to, weight;
      std::cin >> from >> to >> weight;

      // sort from lowest to highest
      if (from > to) {
        std::swap(from, to);
      }
      
      Edge edge = Edge{weight, from, to};
      graph[i] = edge;
    }

    std::set<Edge, Comparator> result;
    int totalWeight = minSpanTree(graph, result, numberOfNodes);

    if ((int)result.size() != numberOfNodes - 1) {
      // If the result does not contain all the nodes, then it is impossible to create a spanning tree
      std::cout << "Impossible\n";
      continue;
    }

    // print the result
    std::cout << totalWeight << '\n';
    for (Edge edge : result) {
      std::cout << edge.from << ' ' << edge.to << '\n';
    }
  }
}

