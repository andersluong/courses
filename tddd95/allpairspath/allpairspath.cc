/**
* This uses Floyd-Warshall algorithm to find the shortest path from a pair of nodes.
* The time complexity is O(n^3) because we have 3 for loops.
* Source of inspiration for algorithm: https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/
* Source of inspiration for negative cycle detection: https://cp-algorithms.com/graph/finding-negative-cycle-in-graph.html
*
* Author: Anders Luong (andlu434)
*/
#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <algorithm>

static const int INF = 1000000000;
static const int NEG_INF = -INF;

struct Edge;
class Node;
class Graph;

// An edge representing a connection between two nodes
struct Edge {
  int weight;
  int from;
  int to;
};

// A node representing a vertex in the graph
class Node {
public:
  ~Node() {
    for (auto edge : edges) {
      delete edge;
    }
  }

  void addEdge(Edge* const edge) {
    edges.push_back(edge);
  }

  std::vector<Edge*> getEdges() const {
    return edges;
  }

  void setCost(int const newCost) {
    cost = newCost;
  }

  int getCost() const {
    return cost;
  }

  void setPrevious(Node* const newPrevious) {
    previous = newPrevious;
  }

  Node* getPrevious() const {
    return previous;
  }

  void setVisited(bool const newVisited) {
    visited = newVisited;
  }

  bool isVisited() const {
    return visited;
  }

private:
  std::vector<Edge*> edges;
  Node* previous;
  int cost;
  bool visited;
};

// A graph of all nodes
class Graph {
public:
  ~Graph() {
    for (auto node : nodes) {
      delete node.second;
    }
  }

  void addNode(int const index, Node* const node) {
    nodes[index] = node;
  }

  bool hasNode(int const index) const {
    return nodes.find(index) != nodes.end();
  }

  Node* getNode(int const index) const {
    if (!hasNode(index)) {
      throw std::runtime_error("Node does not exist");
    }
    return nodes.at(index);
  }

  std::map<int, Node*> getNodes() const {
    return nodes;
  }

  // resets the nodes in the graph to their initial state
  void resetData() {
    for (auto node : nodes) {
      node.second->setCost(INF);
      node.second->setVisited(false);
      node.second->setPrevious(nullptr);
    }
  }

  void addEdge(Edge* const edge) {
    edges.push_back(edge);
  }

  std::vector<Edge*> getEdges() const {
    return edges;
  }
private:
  std::map<int, Node*> nodes;
  std::vector<Edge*> edges;
};

void floydWarshall(Graph& graph, int const numberOfNodes, std::vector<std::vector<int>> &distances) {
  // build up the distance matrix
  for (auto edge : graph.getEdges()) {
    if (edge->weight < distances[edge->from][edge->to]) {
      distances[edge->from][edge->to] = edge->weight;
    }
  }
  for (int i = 0; i < numberOfNodes; i++) {
    distances[i][i] = 0;
  }

  for (int intermediate = 0; intermediate < numberOfNodes; intermediate++) {
    for (int from = 0; from < numberOfNodes; from++) {
      for (int to = 0; to < numberOfNodes; to++) {
        int newDistance = distances[from][intermediate] + distances[intermediate][to];
        if (distances[from][intermediate] < INF && distances[intermediate][to] < INF && newDistance < distances[from][to]) {
          distances[from][to] = std::max(NEG_INF, newDistance);
        }
      }
    }
  }

  // check for negative cycles
  for (int from = 0; from < numberOfNodes; from++) {
    for (int to = 0; to < numberOfNodes; to++) {
      for (int intermediate = 0; intermediate < numberOfNodes; intermediate++) {
        if (distances[from][intermediate] < INF && distances[intermediate][intermediate] < 0 && distances[intermediate][to] < INF) {
          distances[from][to] = NEG_INF;
        }
      }
    }
  }
}

// Build up the path from the start node to the end node, as requested by the course
std::vector<Node*> buildPath(Node* const startNode, Node* endNode) {
  std::vector<Node*> path;
  while (endNode != startNode) {
    path.push_back(endNode);
    endNode = endNode->getPrevious();
  }
  path.push_back(startNode);
  std::reverse(path.begin(), path.end());
  return path;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  while (true) {
    int numberOfNodes, numberOfEdges, numberOfQueries;
    std::cin >> numberOfNodes >> numberOfEdges >> numberOfQueries;

    if (numberOfNodes == 0 && numberOfEdges == 0 && numberOfQueries == 0) {
      break;
    }

    Graph graph;

    // building up the graph
    for (int i = 0; i < numberOfEdges; i++) {
      int from, to, weight;
      std::cin >> from >> to >> weight;
      
      if (!graph.hasNode(to)) {
        graph.addNode(to, new Node());
      }
      if (!graph.hasNode(from)) {
        graph.addNode(from, new Node());
      }

      Node* fromNode = graph.getNode(from);
      // Node* toNode = graph.getNode(to);
      if (from == to) {
        // unnecessary to add an edge to itself
        continue;
      }
      Edge* edge = new Edge{weight, from, to};
      fromNode->addEdge(edge);
      graph.addEdge(edge);
    }

    // build the graph with costs (including negative)
    std::vector<std::vector<int>> distances(numberOfNodes, std::vector<int>(numberOfNodes, INF));
    floydWarshall(graph, numberOfNodes, distances);

    // get queries
    for (int i = 0; i < numberOfQueries; i++) {
      int fromQuery, toQuery;
      std::cin >> fromQuery >> toQuery;
      int cost = distances[fromQuery][toQuery];
      if (cost >= INF) {
        // node doesn't exist, this solution is not possible
        std::cout << "Impossible" << "\n";
      } else if (cost <= NEG_INF) {
        // node has a negative cycle
        std::cout << "-Infinity" << "\n";
      } else {
        // print cost
        std::cout << cost << "\n";
      }
    }
    std::cout << "\n";
  }
}

