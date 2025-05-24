#ifndef GAME_H
#define GAME_H

#include "AStar.h"
#include "Graph.h"
#include "Node.h"
#include "Terrain.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

class Game {
private:
  float tileSize = 20.0f;
  sf::RenderWindow window;
  Terrain &terrain;
  Graph &graph;

  Node caperucita;
  Node lobo;
  Node goal;

  sf::Clock loboClock;
  float loboSpeed = 0.15f;

  void processInput();
  void update();
  void render();
  void drawTile(int x, int y, sf::Color color);

public:
  Game(Terrain &t, Graph &g, Node start, Node goal, Node loboStart);
  void run();
};

#endif // GAME_H
