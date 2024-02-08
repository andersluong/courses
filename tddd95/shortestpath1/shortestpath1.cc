#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>


struct Edge {
  Edge(int const weight, int const toNode) : weight{weight}, toNode{toNode} {}
  int weight;
  int toNode;
};

class Node {
public:
  Node (int cost = -1) : cost{cost} {}
  ~Node() {
    for (auto edge : edges) {
      delete edge;
    }
  }
  void addNeighbor(Edge *edge) {
    edges.insert(edge);
  }

  std::set<Edge*> getEdges() {
    return edges;
  }

  int cost;
  Node* previous;
  bool visited;
private:
  std::set<Edge*> edges;
};

class Graph {
public:
  ~Graph() {
    for (auto node : nodes) {
      delete node.second;
    }
  }

  void addNode(int const index, Node *node) {
    nodes[index] = node;
  }

  bool hasNode(int const index) {
    return nodes.find(index) != nodes.end();
  }

  Node* getNode(int const index) {
    if (!hasNode(index)) {
      throw std::runtime_error("Node does not exist");
    }
    return nodes[index];
  }

  // void updateNode(int const index, Node *node) {
  //   nodes[index] = node;
  // }

  std::map<int, Node*> getNodes() {
    return nodes;
  }
private:
  std::map<int, Node*> nodes;
};

struct Compare {
  bool operator() (Node* a, Node* b) {
    return a->cost > b->cost;
  }
};

void dijkstra(Graph &graph, Node* startNode) {
  // std::vector<Node*> path;
  std::priority_queue<Node*, std::vector<Node*>, Compare> queue;

  for (auto node : graph.getNodes()) {
    node.second->cost = -1;
    node.second->visited = false;
    node.second->previous = nullptr;
  }

  startNode->cost = 0;
  queue.push(startNode);

  while (!queue.empty()) {
    Node* currentNode = queue.top();
    queue.pop();

    if (currentNode->visited) {
      continue;
    }

    currentNode->visited = true;

    // if (currentNode == endNode) {
    //   while (currentNode != nullptr) {
    //     path.push_back(currentNode);
    //     currentNode = currentNode->previous;
    //   }
    //   return path;
    // }

    for (auto edge : currentNode->getEdges()) {
      Node* neighbor = graph.getNode(edge->toNode);
      if (neighbor->visited) {
        continue;
      }
      int newDistance = currentNode->cost + edge->weight;
      if (neighbor->cost == -1 || newDistance < neighbor->cost) {
        neighbor->cost = newDistance;
        neighbor->previous = currentNode;
        queue.push(neighbor);
      }
    }
  }
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
        fromNode->addNeighbor(edge);
        
        graph.addNode(from, fromNode);
      } else {
        Edge* edge = new Edge{weight, to};
        Node* fromNode = graph.getNode(from);
        fromNode->addNeighbor(edge);
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
        if (endNode->cost == -1) {
          std::cout << "Impossible" << "\n";
          continue;
        }
        std::cout << endNode->cost << "\n";
      } else {
        // end node doesn't exist, this solution is not possible
        std::cout << "Impossible" << "\n";
      }
    }
    std::cout << "\n";
  }
}
