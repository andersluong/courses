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
  int weight;
  int fromNode;
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

  std::vector<Edge*> linkedEdges;

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
      node.second->setCost(-1);
      node.second->setVisited(false);
      node.second->setPrevious(nullptr);
    }
  }
  std::map<int, Node*> nodes;
private:
};

void dijkstra(Graph &graph, Node* const startNode, Node* const endNode) {
  graph.resetData();
  // std::vector<Node*> path;
  // std::priority_queue<Node*, std::vector<Node*>, Compare> queue;
  std::set<std::pair<int, Node*>> queue;

  startNode->setCost(0);
  queue.insert({0, startNode});

  while (!queue.empty()) {
    Node* currentNode = queue.begin()->second;
    queue.erase(queue.begin());

    if (currentNode == endNode) {
      break;
    }

    if (currentNode->isVisited()) {
      continue;
    }

    currentNode->setVisited(true);

    for (auto edge : currentNode->getEdges()) {
      Node* neighbor = graph.getNode(edge->toNode);
      if (neighbor->isVisited()) {
        continue;
      }
      int newDistance = currentNode->getCost() + edge->weight;
      if (neighbor->getCost() == -1 || newDistance < neighbor->getCost()) {
        neighbor->setCost(newDistance);
        neighbor->setPrevious(currentNode);
        queue.insert({newDistance, neighbor});
      }
    }
  }
}

int countPaths(Graph& graph, Node* endNode) {
  int count = 0;
  for (auto edge : endNode->getEdges()) {
    Node* prevNode = graph.getNode(edge->toNode);
    if (prevNode->getCost() == 0) {
      // std::cout << "added path: " << edge->fromNode << " to " << edge->toNode << "\n";
      count++;
    }
    else if (prevNode->getCost() < endNode->getCost()) {
      count += countPaths(graph, prevNode);
    }
  }

  return count;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  while (true) {
    int numberOfNodes, numberOfEdges;
    std::cin >> numberOfNodes >> numberOfEdges;

    if (numberOfNodes == 0) {
      break;
    }

    Graph graph;

    // add start node
    Node* startNode = new Node();
    graph.addNode(1, startNode);

    // add end node
    Node* endNode = new Node();
    graph.addNode(2, endNode);

    for (int i = 0; i < numberOfEdges; i++) {
      int from, to, weight;
      std::cin >> from >> to >> weight;
      
      // add from node as well as the edge it's connecting to
      if (!graph.hasNode(from)) {
        Node* fromNode = new Node();
        graph.addNode(from, fromNode);
      }
      // add to node as well if it doesn't exist
      if (!graph.hasNode(to)) {
        Node* toNode = new Node();
        graph.addNode(to, toNode);
      }

      Node* fromNode = graph.getNode(from);
      Node* toNode = graph.getNode(to);
      Edge* edge = new Edge{weight, from, to};
      fromNode->addEdge(edge);
      Edge* reverseEdge = new Edge{weight, to, from};
      toNode->addEdge(reverseEdge);
    }

    // build the graph with costs
    dijkstra(graph, startNode, endNode);


    int count = countPaths(graph, endNode);
    std::cout << count << "\n";
  }
}

