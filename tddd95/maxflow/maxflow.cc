/**
* This solves the maximum flow in a graph problem using the Edmond-Karp algorithm.
* The algorithm is based on the Ford-Fulkerson algorithm, but uses a breadth-first search to find the
* shortest path from the source to the sink. This is done until no more paths can be found.
* The algorithm is O(V*E^2), where V is the number of vertices and E is the number of edges.
* The breadth-first search is O(V+E), since it will be called V times, and the augmenting path will
* be found in O(E) time. Then in Edmond-Karp, the algorithm ensures that the augmenting path is found
* after at most V times, since the flow is increased by at least 1 each time. This means that the algorithm
* will run in O(V*E^2) time.
*
* Author: Anders Luong (andlu434)
*/
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#include <algorithm>

static const int INF = 1000000000;

struct Edge;
class Node;
class Graph;

// An edge representing a connection between two nodes
struct Edge {
  Node* toNode;
  int capacity;
  int flow;
  Edge* companionEdge;
};

// A node representing a vertex in the graph
class Node {
public:
  Node(int const index): index{index} {}

  ~Node() {
    for (auto edge : edges) {
      delete edge;
    }
  }

  int getIndex() const {
    return index;
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

  void setPrevious(Edge* const newPrevious) {
    previous = newPrevious;
  }

  Edge* getPrevious() const {
    return previous;
  }

  void setVisited(bool const newVisited) {
    visited = newVisited;
  }

  bool isVisited() const {
    return visited;
  }

private:
  int index;
  std::vector<Edge*> edges;
  Edge* previous;
  int cost;
  bool visited;
};

// A graph of all nodes
class Graph {
public:
  Graph(int const size): nodes(size, nullptr) {}

  ~Graph() {
    for (auto node : nodes) {
      delete node;
    }
  }

  void addNode(int const index, Node* const node) {
    nodes[index] = node;
  }

  bool hasNode(int const index) const {
    return nodes[index] != nullptr;
  }

  Node* getNode(int const index) const {
    if (!hasNode(index)) {
      throw std::runtime_error("Node does not exist");
    }
    return nodes.at(index);
  }

  void addEdge(Edge* const edge) {
    edges.push_back(edge);
  }

  std::vector<Edge*> getEdges() const {
    return edges;
  }

  // resets the nodes in the graph to their initial state
  void resetData() {
    for (auto node : nodes) {
      node->setCost(-1);
      node->setVisited(false);
      node->setPrevious(nullptr);
    }
  }
private:
  std::vector<Edge*> edges;
  std::vector<Node*> nodes;
};

// Breadth-first search to find all possible paths from source to sink. This will be called multiple times
// until no more paths can be found.
bool bfs(Graph &graph, Node* const startNode, Node* const goalNode) {
  graph.resetData();
  std::queue<std::pair<Node*, int>> queue;

  queue.push({startNode, INF}); // source has infinite flow

  while (!queue.empty()) {
    Node* currentNode = queue.front().first;
    int flow = queue.front().second;
    queue.pop();

    if (currentNode->isVisited()) {
      continue;
    }

    if (startNode == goalNode) {
      return true;
    }

    currentNode->setVisited(true);

    for (auto edge : currentNode->getEdges()) {
      Node* neighbor = edge->toNode;
      if (neighbor->isVisited()) {
        continue;
      }

      if (edge->capacity > edge->flow && neighbor->getPrevious() == nullptr) {
        neighbor->setPrevious(edge);
        int newFlow = std::min(flow, edge->capacity - edge->flow);
        neighbor->setCost(newFlow);
        if (neighbor == goalNode) {
          return true;
        }
        queue.push({neighbor, newFlow});
      }
    }
  }
  return false;
}

int edmondKarp(Graph &graph, Node* const sourceNode, Node* const sinkNode) {
  int maxFlow = 0;
  while (bfs(graph, sourceNode, sinkNode)) {
    int pathFlow = sinkNode->getCost();
    maxFlow += pathFlow;

    // update edges
    Node* currentNode = sinkNode;
    while (currentNode != sourceNode) {
      Edge* previousEdge = currentNode->getPrevious();
      previousEdge->flow += pathFlow;
      previousEdge->companionEdge->flow -= pathFlow;
      currentNode = previousEdge->companionEdge->toNode;
    }
  }
  return maxFlow;
}

// Build up the path from the start node to the end node, as requrested by the course
std::vector<Node*> buildPath(Node* const startNode, Node* endNode) {
  std::vector<Node*> path;
  while (endNode != startNode) {
    path.push_back(endNode);
    endNode = endNode->getPrevious()->companionEdge->toNode;
  }
  path.push_back(startNode);
  std::reverse(path.begin(), path.end());
  return path;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  int numberOfNodes, numberOfEdges, sourceIndex, sinkIndex;
  std::cin >> numberOfNodes >> numberOfEdges >> sourceIndex >> sinkIndex;

  Graph graph(numberOfNodes);

  // add start node
  Node* sourceNode = new Node(sourceIndex);
  graph.addNode(sourceIndex, sourceNode);

  // add goal node - since source != sink, we can add it as new node
  Node* sinkNode = new Node(sinkIndex);
  graph.addNode(sinkIndex, sinkNode);

  // add all edges (both ways)
  for (int i = 0; i < numberOfEdges; i++) {
    int from, to, capacity;
    std::cin >> from >> to >> capacity;
    
    // add from node as well as the edge it's connecting to
    Node* fromNode;
    Node* toNode;
    if (!graph.hasNode(from)) {
      fromNode = new Node(from);
      graph.addNode(from, fromNode);
    } else {
      fromNode = graph.getNode(from);
    }
    if (!graph.hasNode(to)) {
      toNode = new Node(to);
      graph.addNode(to, toNode);
    } else {
      toNode = graph.getNode(to);
    }
    Edge* fromEdge = new Edge{toNode, capacity, 0, nullptr};
    Edge* toEdge = new Edge{fromNode, 0, 0, nullptr};
    fromEdge->companionEdge = toEdge;
    toEdge->companionEdge = fromEdge;
    fromNode->addEdge(fromEdge);
    toNode->addEdge(toEdge);
    graph.addEdge(fromEdge);
    graph.addEdge(toEdge);
  }

  int maximumFlow = edmondKarp(graph, sourceNode, sinkNode);
  int numberOfNodesInFlow = 0;
  std::vector<Edge*> chosenEdges;

  for (auto edge : graph.getEdges()) {
    if (edge->flow > 0) {
      numberOfNodesInFlow++;
      chosenEdges.push_back(edge);
    }
  }
  std::cout << numberOfNodes << " " << maximumFlow << " " << numberOfNodesInFlow << "\n";
  for (auto edge : chosenEdges) {
    Node* fromNode = edge->companionEdge->toNode;
    Node* toNode = edge->toNode;
    std::cout << fromNode->getIndex() << " " << toNode->getIndex() << " " << edge->flow << "\n";
  }
}

