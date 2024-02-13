/**
* This uses Bellman-Ford algorithm to find the shortest path from a start node to all other nodes in a graph.
* The time complexity is O(V*E) where V is the number of vertices and E is the number of edges.
* Source of inspiration: https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/
*
* Author: Anders Luong (andlu434)
*/
#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <unordered_set>

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

bool bellmanFord(Graph &graph, int const numberOfNodes) {
  // reset data will set all nodes to have a cost of INT_MAX
  graph.resetData();
  Node* startNode = graph.getNode(0);
  Node* endNode = graph.getNode(numberOfNodes - 1);
  startNode->setCost(-100);

  // any node can have at most numberOfNodes - 1 edges, so we loop through that many times
  Node* x;
  for (int i = 0; i < numberOfNodes - 1; i++) {
    x = nullptr;
    bool isUpdated = false;
    for (auto edge : graph.getEdges()) {
      Node* neighbor = edge->toNode;

      int newCost = edge->fromNode->getCost() + edge->weight;
      if (newCost >= 0) {
        // if the cost is positive, we can skip this edge
        continue;
      }
      if (edge->fromNode->getCost() == INF) {
        // if the cost is INF, we can skip this edge
        continue;
      }
      if (newCost < neighbor->getCost()) {
        // std::cout << "Updated cost: " << neighbor->getCost() << " to " << newCost << "\n";
        neighbor->setCost(newCost);
        neighbor->setPrevious(edge->fromNode);
        isUpdated = true;

        if (neighbor == endNode) {
          // if we reach the end node, we can break early
          return true;
        }
        x = neighbor;
      }
    }
    if (!isUpdated) {
      // if no updates were made, we can break early
      break;
    }
  }

  if (x == nullptr) {
    // if x is nullptr, then there is no negative cycle
    return false;
  }

  // check for negative cycles
  std::unordered_set<Node*> negativeCycles;
  for (auto edge : graph.getEdges()) {
    if (edge->fromNode->getCost() == INF) {
      continue;
    }
    Node* neighbor = edge->toNode;
    int cost = edge->fromNode->getCost() + edge->weight;
    if (cost < 0 && cost < neighbor->getCost()) {
      // if the cost is smaller, we have a negative cycle
      negativeCycles.insert(neighbor);
      neighbor->setCost(NEG_INF);

      if (neighbor == endNode) {
        return true;
      }
    }
  }

  while (!negativeCycles.empty()) {
    Node* node = *negativeCycles.begin();
    negativeCycles.erase(node);
    node->setCost(NEG_INF);
    for (auto edge : node->getEdges()) {
      if (edge->toNode->getCost() != NEG_INF) {
        negativeCycles.insert(edge->toNode);

        if (edge->toNode == endNode) {
          return true;
        }
      }
    }
  }
  return false;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  while (true) {
    int numberOfRooms;
    std::cin >> numberOfRooms;

    if (numberOfRooms == -1) {
      break;
    }

    Graph graph;

    // building up the graph
    for (int from = 0; from < numberOfRooms; from++) {
      int weight, doors;
      std::cin >> weight >> doors;

      if (!graph.hasNode(from)) {
        graph.addNode(from, new Node());
      }
      Node* fromNode = graph.getNode(from);
      for (int i = 0; i < doors; i++) {
        int to;
        std::cin >> to;
        if (!graph.hasNode(to-1)) {
          graph.addNode(to-1, new Node());
        }

        Node* toNode = graph.getNode(to-1);
        // Do negative weight so we flip the logic. Instead of always staying positive,
        // we want to stay with negative weight
        Edge* edge = new Edge{-weight, fromNode, toNode};
        fromNode->addEdge(edge);
        graph.addEdge(edge); 
      }
    }

    // print graph
    // for (auto node : graph.getNodes()) {
    //   std::cout << "Node: " << node.first + 1 << " has edges: ";
    //   for (auto edge : node.second->getEdges()) {
    //     std::cout << edge->toNode << ": " << edge->weight << " | ";
    //   }
    //   std::cout << std::endl;
    // }

    // build the graph with costs (including negative)
    bool result = bellmanFord(graph, numberOfRooms);
    // std::cout << graph.getNode(numberOfRooms - 1)->getCost() << std::endl;
    if (result) {
      std::cout << "winnable" << std::endl;
    } else {
      std::cout << "hopeless" << std::endl;
    }
  }
}

