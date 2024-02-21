/**
* This uses Dijkstra's algorithm to find the shortest path from a start node to all other nodes in a graph.
* Almost the same as shortest path 1, but with added logic for waiting time.
* The time complexity is O((V + E) * log(V)) where V is the number of vertices and E is the number of edges.
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

static const int INF = 1000000000;
static const int NEG_INF = -INF;

struct Edge;
class Node;
class Graph;

// An edge representing a connection between two nodes
struct Edge {
  int weight;
  Node* toNode;
  int blockStart;
  Edge* companionEdge;
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

void dijkstra(Graph &graph, Node* const startNode, Node* const goalNode) {
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

    if (startNode == goalNode) {
      return;
    }

    currentNode->setVisited(true);

    for (auto edge : currentNode->getEdges()) {
      Node* neighbor = edge->toNode;
      if (neighbor->isVisited()) {
        continue;
      }

      // Added logic for waiting time
      // int addedWaitTime = 0;
      // if (currentNode->getCost() <= edge->startTime) {
      //   // to access the neighbor, we need to wait since the start time hasn't started yet
      //   addedWaitTime = edge->startTime - currentNode->getCost();
      // } else if (edge->P == 0) {
      //   // this node cannot be accesed anymore
      //   continue;
      // } else if ((currentNode->getCost() - edge->startTime) % edge->P > 0) {
      //   // we need to wait for the next time slot to access the neighbor
      //   addedWaitTime = edge->P - ((currentNode->getCost() - edge->startTime) % edge->P);
      // }
      int addedWaitTime = 0;
      if (currentNode->getCost() >= edge->blockStart && currentNode->getCost() < edge->blockStart + edge->weight) {
        // We want to enter while George is on this intersection, so we have to wait for him to finish
        addedWaitTime = edge->blockStart + edge->weight - currentNode->getCost();
      }
      // std::cout << "added wait time: " << addedWaitTime << " for edge weight: " << edge->weight << " with cost: " << currentNode->getCost() << std::endl;

      int newDistance = currentNode->getCost() + edge->weight + addedWaitTime;
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
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  int numberOfNodes, numberOfEdges;
  std::cin >> numberOfNodes >> numberOfEdges;

  int startNodeIndex, goalNodeIndex, startingTime, numberOfNodesGeorge;
  std::cin >> startNodeIndex >> goalNodeIndex >> startingTime >> numberOfNodesGeorge;

  Graph graph;

  // add start node
  Node* startNode = new Node();
  graph.addNode(startNodeIndex, startNode);

  // add goal node
  Node* goalNode;
  if (startNodeIndex != goalNodeIndex) {
    goalNode = new Node();
  } else {
    goalNode = startNode;
  }
  graph.addNode(goalNodeIndex, goalNode);

  std::vector<Node*> georgeNodes;
  for (int i = 0; i < numberOfNodesGeorge; i++) {
    int nodeIndex;
    std::cin >> nodeIndex;
    Node* node;
    if (!graph.hasNode(nodeIndex)) {
      node = new Node();
      graph.addNode(nodeIndex, node);
    } else {
      node = graph.getNode(nodeIndex);
    }
    georgeNodes.push_back(node);
  }

  // add all edges (both ways)
  for (int i = 0; i < numberOfEdges; i++) {
    int from, to, weight;
    std::cin >> from >> to >> weight;
    
    // add from node as well as the edge it's connecting to
    Node* fromNode;
    Node* toNode;
    if (!graph.hasNode(from)) {
      fromNode = new Node();
      graph.addNode(from, fromNode);
    } else {
      fromNode = graph.getNode(from);
    }
    if (!graph.hasNode(to)) {
      toNode = new Node();
      graph.addNode(to, toNode);
    } else {
      toNode = graph.getNode(to);
    }
    Edge* fromEdge = new Edge{weight, toNode, NEG_INF, nullptr};
    Edge* toEdge = new Edge{weight, fromNode, NEG_INF, nullptr};
    fromEdge->companionEdge = toEdge;
    toEdge->companionEdge = fromEdge;
    fromNode->addEdge(fromEdge);
    toNode->addEdge(toEdge);
  }

  int traversedTime = -startingTime;
  for (unsigned i = 0; i < georgeNodes.size() - 1; i++) {
    // let him traverse
    Node* fromNode = georgeNodes[i];
    Node* toNode = georgeNodes[i+1];
    for (Edge* edge : fromNode->getEdges()) {
      if (edge->toNode == toNode) {
        edge->blockStart = traversedTime;
        edge->companionEdge->blockStart = traversedTime;
        traversedTime += edge->weight;
        break;
      }
    }
  }

  // build the graph with costs
  dijkstra(graph, startNode, goalNode);
  std::cout << graph.getNode(goalNodeIndex)->getCost() << "\n";
}

