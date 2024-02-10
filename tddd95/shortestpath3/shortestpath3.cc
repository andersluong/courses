/**
* This uses Bellman-Ford algorithm to find the shortest path from a start node to all other nodes in a graph.
* The time complexity is O(V*E) where V is the number of vertices and E is the number of edges.
* Source of inspiration: https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/
*
* Author: Anders Luong (andlu434)
*/
#include <iostream>
#include <unordered_set>
#include <utility>
#include <vector>
#include <map>
#include <algorithm>

static const int INF = 100000000;
static const int NEG_INF = -INF;

struct Edge;
class Node;
class Graph;

// An edge representing a connection between two nodes
struct Edge {
  int weight;
  Node* fromNode;
  Node* toNode;
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

void bellmanFord(Graph &graph, Node* const startNode, int const numberOfNodes) {
  // reset data will set all nodes to have a cost of INT_MAX
  graph.resetData();
  startNode->setCost(0);

  // any node can have at most numberOfNodes - 1 edges, so we loop through that many times
  for (int i = 0; i < numberOfNodes - 1; i++) {
    bool isUpdated = false;
    for (auto edge : graph.getEdges()) {
      Node* neighbor = edge->toNode;
      if (neighbor->getCost() == NEG_INF) {
        continue;
      }
      int newCost = edge->fromNode->getCost() + edge->weight;
      if (edge->fromNode->getCost() != INF && newCost < neighbor->getCost()) {
        // prevent overflow with NEG_INF as maximum negative cost
        neighbor->setCost(std::max(NEG_INF, newCost));
        neighbor->setPrevious(edge->fromNode);
        isUpdated = true;
      }
    }
    if (!isUpdated) {
      // if no updates were made, we can break early
      break;
    }
  }

  // check for negative cycles
  std::unordered_set<Node*> negativeCycles;
  for (auto edge : graph.getEdges()) {
    if (edge->fromNode->getCost() == INF) {
      continue;
    }
    Node* neighbor = edge->toNode;
    int cost = edge->fromNode->getCost() + edge->weight;
    if (cost < neighbor->getCost()) {
      // if the cost is smaller, we have a negative cycle
      negativeCycles.insert(edge->toNode);
    }
  }

  while (!negativeCycles.empty()) {
    Node* node = *negativeCycles.begin();
    negativeCycles.erase(node);
    node->setCost(NEG_INF);
    for (auto edge : node->getEdges()) {
      if (edge->toNode->getCost() != NEG_INF) {
        negativeCycles.insert(edge->toNode);
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
    int numberOfNodes, numberOfEdges, numberOfQueries, startNodeIndex;
    std::cin >> numberOfNodes >> numberOfEdges >> numberOfQueries >> startNodeIndex;

    if (numberOfNodes == 0 && numberOfEdges == 0 && numberOfQueries == 0 && startNodeIndex == 0) {
      break;
    }

    Graph graph;

    // add start node
    Node* startNode = new Node();
    graph.addNode(startNodeIndex, startNode);

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
      Node* toNode = graph.getNode(to);
      Edge* edge = new Edge{weight, fromNode, toNode};
      fromNode->addEdge(edge);
      graph.addEdge(edge);
    }

    // build the graph with costs (including negative)
    bellmanFord(graph, startNode, numberOfNodes);

    // get queries
    for (int i = 0; i < numberOfQueries; i++) {
      int query;
      std::cin >> query;
      if (graph.hasNode(query)) {
        Node* endNode = graph.getNode(query);
        if (endNode->getCost() >= INF) {
          // end node doesn't exist, this solution is not possible
          std::cout << "Impossible" << "\n";
        } else if (endNode->getCost() <= NEG_INF) {
          // end node has a negative cycle
          std::cout << "-Infinity" << "\n";
        } else {
          // print cost
          std::cout << endNode->getCost() << "\n";
        }
      } else {
        // end node doesn't exist, this solution is not possible
        std::cout << "Impossible" << "\n";
      }
    }
    std::cout << "\n";
  }
}

