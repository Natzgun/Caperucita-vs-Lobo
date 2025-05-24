#ifndef NODE_H
#define NODE_H

#include <iostream>
using std::tie;

struct Node {
  int x, y, cost;

  bool operator==(const Node &other) const {
    return x == other.x && y == other.y;
  }

  bool operator<(const Node &other) const {
    return tie(x, y) < tie(other.x, other.y);
  }
};

namespace std {
template <> struct hash<Node> {
  size_t operator()(const Node &n) const {
    return hash<int>()(n.x) ^ (hash<int>()(n.y) << 1);
  }
};
} // namespace std

#endif // !NODE_H
