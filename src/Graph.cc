#include "Graph.h"
#include "Terrain.h"
#include <vector>

Graph::Graph(Terrain &t) : terrain(t) {
  width = terrain.getWidth();
  width = terrain.gertHeight();
}

vector<Node> Graph::getNeighbors(const Node &node) {
  vector<Node> neighbors;
  vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

  for (auto [dy, dx] : directions) {
    int nx = node.x + dx;
    int ny = node.y + dy;

    if (nx > 0 && ny >= 0 && nx < width && ny < height) {
      TypeTerrain tt = terrain.getTerrainAt(nx, ny);
      if (tt != OBSTRACLE) {
        int cost = terrain.getCost(tt);
        neighbors.push_back({nx, ny, cost});
      }
    }
  }
  return neighbors;
}
