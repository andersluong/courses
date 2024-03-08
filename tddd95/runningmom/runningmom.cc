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
  Node* from;
  Node* to;
};

// A node representing a vertex in the graph
class Node {
public:
  Node(std::string const& cityName, int const index) : cityName{cityName}, index{index}, cost{INF}, visited{false}, previous{nullptr} {}
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

  int index;
private:
  std::vector<Edge*> edges;
  Node* previous;
  int cost;
  bool visited;
  std::string cityName;
};

// A graph of all nodes
class Graph {
public:
  ~Graph() {
    for (auto node : nodes) {
      delete node.second;
    }
  }

  void addNode(int const index, std::string cityName, Node* const node) {
    nodes[index] = node;
    cityToIndex[cityName] = index;
  }

  bool hasNode(std::string const cityName) const {
    return cityToIndex.find(cityName) != cityToIndex.end();
  }

  Node* getNode(int const index) const {
    if (!hasNode(index)) {
      throw std::runtime_error("Node does not exist");
    }
    return nodes.at(cityToIndex.at(cityName));
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
  std::map<std::string, int> cityToIndex;
  std::map<int, Node*> nodes;
  std::vector<Edge*> edges;
};

bool dfs(Graph& graph, int const nodeIndex, std::vector<int>& visited) {
  if (visited[nodeIndex] == 1) {
    return true;
  }
  if (visited[nodeIndex] == 2) {
    return false;
  }
  visited[nodeIndex] = 1;
  for (auto edge : graph.getNode(nodeIndex)->getEdges()) {
    if (dfs(graph, edge->to->index, visited)) {
      return true;
    }
  }
  visited[nodeIndex] = 2;
  return false;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  Graph graph;

  int numberOfFlights;
  std::cin >> numberOfFlights;
  
  int index = 0;
  for (int i = 0; i < numberOfFlights; i++) {
    std::string from, to;
    std::cin >> from >> to;
    if (!graph.hasNode(to)) {
      graph.addNode(index, to, new Node(to, index));
      index++;
    }
    if (!graph.hasNode(from)) {
      graph.addNode(index, from, new Node(from, index));
      index++;
    }

    if (from == to) {
      // unnecessary to add an edge to itself
      continue;
    }
    int weight = -1;
    Node* fromNode = graph.getNode(from);
    Node* toNode = graph.getNode(to);
    Edge* edge = new Edge{weight, fromNode, toNode};
    fromNode->addEdge(edge);
    graph.addEdge(edge);
  }
  int numberOfNodes = graph.getNodes().size();
  std::vector<std::vector<int>> distances(numberOfNodes, std::vector<int>(numberOfNodes, INF));
  floydWarshall(graph, numberOfNodes, distances);

  std::string cityName;
  while (std::cin >> cityName) {
    std::cout << cityName << " ";
    if (graph.getNode(cityName)->getCost() == NEG_INF) {
      std::cout << "safe" << std::endl;
    } else {
      std::cout << "trapped" << std::endl;
    }
  }
}
