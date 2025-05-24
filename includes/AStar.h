#ifndef ASTAR_H
#define ASTAR_H

#include "Graph.h"
#include "Node.h"
#include <vector>

using namespace std;

class AStar {
public:
  static vector<Node> findPath(Graph &graph, Node start, Node goal);
};

int heuristic(const Node &a, const Node &b);

#endif // ASTAR_H
