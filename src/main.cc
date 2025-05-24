#include "AStar.h"
#include "Graph.h"
#include "Node.h"
#include "Terrain.h"
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  Terrain terrain(60, 30);
  // terrain.showTerrain();

  Graph graph(terrain);
  Node start{0, 0, 0};
  Node goal{29, 14, 0};

  vector<Node> path = AStar::findPath(graph, start, goal);

  for (auto n : path) {
    cout << "(" << n.x << "," << n.y << ") ";
  }
  cout << endl;

  return 0;
}
