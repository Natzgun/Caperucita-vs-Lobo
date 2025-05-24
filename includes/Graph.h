#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include "Terrain.h"

class Graph {
private:
  Terrain &terrain;
  int width, height;

public:
  Graph(Terrain &t);
  vector<Node> getNeighbors(Node node);
};

#endif // GRAPH_H
