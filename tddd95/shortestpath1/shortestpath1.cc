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
      node.second->setCost(-1);
      node.second->setVisited(false);
      node.second->setPrevious(nullptr);
    }
  }
private:
  std::map<int, Node*> nodes;
};

void dijkstra(Graph &graph, Node* const startNode) {
  graph.resetData();
  // std::vector<Node*> path;
  // std::priority_queue<Node*, std::vector<Node*>, Compare> queue;
  std::set<std::pair<int, Node*>> queue;

  startNode->setCost(0);
  queue.insert({0, startNode});

  while (!queue.empty()) {
    Node* currentNode = queue.begin()->second;
    queue.erase(queue.begin());

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

// Build up the path from the start node to the end node, as requrested by the course
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

    for (int i = 0; i < numberOfEdges; i++) {
      int from, to, weight;
      std::cin >> from >> to >> weight;
      
      // add from node as well as the edge it's connecting to
      if (!graph.hasNode(from)) {
        Node* fromNode = new Node();
        Edge* edge = new Edge{weight, to};
        fromNode->addEdge(edge);
        
        graph.addNode(from, fromNode);
      } else {
        Edge* edge = new Edge{weight, to};
        Node* fromNode = graph.getNode(from);
        fromNode->addEdge(edge);
        // graph.updateNode(from, fromNode);
      }

      // add to node as well if it doesn't exist
      if (!graph.hasNode(to)) {
        Node* toNode = new Node();
        graph.addNode(to, toNode);
      }
    }

    // build the graph with costs
    dijkstra(graph, startNode);

    // get queries
    for (int i = 0; i < numberOfQueries; i++) {
      int query;
      std::cin >> query;
      if (graph.hasNode(query)) {
        Node* endNode = graph.getNode(query);
        if (endNode->getCost() == -1) {
          // end node exists but is not reachable
          std::cout << "Impossible" << "\n";
          continue;
        }
        std::cout << endNode->getCost() << "\n";
      } else {
        // end node doesn't exist, this solution is not possible
        std::cout << "Impossible" << "\n";
      }
    }
    std::cout << "\n";
  }
}

