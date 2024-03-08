/**
* This uses Dijkstra's algorithm to find the shortest path from a start node to all other nodes in a graph.
* The time complexity is O((V + E) * log(V)) where V is the number of vertices and E is the number of edges.
* The log(V) comes from the priority queue for sorting the shortest costs.
* The solution to this problem is heavily inspired by lab 8 from the course TDDD86.
*
* Author: Anders Luong (andlu434)
*/
#include <iostream>
#include <set>
#include <utility>
#include <vector>
#include <map>
#include <algorithm>

// An edge representing a connection between two nodes
struct Edge {
  int toNode;
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

  // resets the nodes in the graph to their initial state
  void resetData() {
    for (auto node : nodes) {
      node.second->setVisited(false);
    }
  }
private:
  std::map<int, Node*> nodes;
};

bool dfs(Graph& graph, Node* const startNode) {
  startNode->setVisited(true);
  for (auto edge : startNode->getEdges()) {
    Node* nextNode = graph.getNode(edge->toNode);
    if (nextNode->isVisited()) {
      return true;
    }
    nextNode->setVisited(true);
    if (dfs(graph, nextNode)) {
      return true;
    }
    nextNode->setVisited(false);
  }
  return false;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  Graph graph;

  int numberOfConnections;
  std::cin >> numberOfConnections;

  std::map<std::string, int> nameToIndex;
  int index = 0;

  for (int i = 0; i < numberOfConnections; i++) {
    std::string fromCity;
    std::string toCity;
    std::cin >> fromCity >> toCity;

    if (nameToIndex.find(fromCity) == nameToIndex.end()) {
      nameToIndex[fromCity] = index;
      graph.addNode(index, new Node());
      index++;
    }

    if (nameToIndex.find(toCity) == nameToIndex.end()) {
      nameToIndex[toCity] = index;
      graph.addNode(index, new Node());
      index++;
    }

    Edge* edge = new Edge{nameToIndex[toCity]};
    Node* fromNode = graph.getNode(nameToIndex[fromCity]);
    fromNode->addEdge(edge);
  }

  std::string startCity;
  while (std::cin >> startCity) {
    std::cout << startCity << " ";
    Node* startNode = graph.getNode(nameToIndex[startCity]);
    if (dfs(graph, startNode)) {
      std::cout << "safe" << std::endl;
    } else {
      std::cout << "trapped" << std::endl;
    }
    graph.resetData();
  }

}

