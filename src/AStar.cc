#include "AStar.h"
#include <algorithm>
#include <queue>
#include <unordered_map>

int heuristic(const Node &a, const Node &b) {
  return abs(a.x - b.x) + abs(a.y - b.y);
}

vector<Node> AStar::findPath(Graph &graph, Node start, Node goal) {
  using PQElement = pair<int, Node>; // (priority, node)
  priority_queue<PQElement, vector<PQElement>, greater<PQElement>> frontier;

  unordered_map<Node, Node> cameFrom;
  unordered_map<Node, int> costSoFar;

  frontier.emplace(0, start);
  cameFrom[start] = start;
  costSoFar[start] = 0;

  while (!frontier.empty()) {
    Node current = frontier.top().second;
    frontier.pop();

    if (current == goal)
      break;

    for (Node neighbor : graph.getNeighbors(current)) {
      int newCost = costSoFar[current] + neighbor.cost;
      if (!costSoFar.count(neighbor) || newCost < costSoFar[neighbor]) {
        costSoFar[neighbor] = newCost;
        int priority = newCost + heuristic(neighbor, goal);
        frontier.emplace(priority, neighbor);
        cameFrom[neighbor] = current;
      }
    }
  }

  // reconstruir camino
  vector<Node> path;
  Node current = goal;
  if (!cameFrom.count(current))
    return {}; // no path

  while (!(current == start)) {
    path.push_back(current);
    current = cameFrom[current];
  }
  path.push_back(start);
  reverse(path.begin(), path.end());
  return path;
}
