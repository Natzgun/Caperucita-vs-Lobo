#include "Game.h"

Game::Game(Terrain &t, Graph &g, Node start, Node goal, Node loboStart)
    : terrain(t), graph(g),
      window(sf::VideoMode(t.getWidth() * tileSize, t.getHeight() * tileSize),
             "Caperucita vs. Lobo"),
      caperucita(start), goal(goal), lobo(loboStart) {}

void Game::run() {
  while (window.isOpen()) {
    processInput();
    update();
    render();
  }
}

void Game::processInput() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      window.close();
    if (event.type == sf::Event::KeyPressed) {
      int dx = 0, dy = 0;
      if (event.key.code == sf::Keyboard::W)
        dy = -1;
      if (event.key.code == sf::Keyboard::S)
        dy = 1;
      if (event.key.code == sf::Keyboard::A)
        dx = -1;
      if (event.key.code == sf::Keyboard::D)
        dx = 1;

      int nx = caperucita.x + dx;
      int ny = caperucita.y + dy;
      if (nx >= 0 && ny >= 0 && nx < terrain.getWidth() &&
          ny < terrain.getHeight()) {
        if (terrain.getTerrainAt(nx, ny) != OBSTRACLE)
          caperucita.x = nx, caperucita.y = ny;
      }
    }
  }
}

void Game::update() {
  if (loboClock.getElapsedTime().asSeconds() >= loboSpeed) {
    loboClock.restart();
    vector<Node> path = AStar::findPath(graph, lobo, caperucita);
    if (path.size() > 1) {
      lobo = path[1];
    }
  }

  if (lobo == caperucita) {
    printf("El lobo atrapó a Caperucita pipipi 🐺 💀\n");
    window.close();
  }

  if (caperucita == goal) {
    printf("¡Caperucita llegó a la casa de la abuela! Daaaaaaaa 🏠🎉\n");
    window.close();
  }
}

void Game::render() {
  window.clear();

  for (int y = 0; y < terrain.getHeight(); ++y) {
    for (int x = 0; x < terrain.getWidth(); ++x) {
      TypeTerrain tt = terrain.getTerrainAt(x, y);
      sf::Color color;
      switch (tt) {
      case SAFE_PATH:
        color = sf::Color::Green;
        break;
      case DANGER_PATH:
        color = sf::Color(255, 140, 0);
        break; // narancia
      case OBSTRACLE:
        color = sf::Color::Black;
        break;
      }
      drawTile(x, y, color);
    }
  }

  drawTile(goal.x, goal.y, sf::Color::Blue);
  drawTile(caperucita.x, caperucita.y, sf::Color::Red);
  drawTile(lobo.x, lobo.y, sf::Color::Magenta);
  drawTile(lobo.x, lobo.y, sf::Color::Blue);

  window.display();
}

void Game::drawTile(int x, int y, sf::Color color) {
  sf::RectangleShape rect(sf::Vector2f(tileSize, tileSize));
  rect.setPosition(x * tileSize, y * tileSize);
  rect.setFillColor(color);
  rect.setOutlineColor(sf::Color::White);
  rect.setOutlineThickness(1);
  window.draw(rect);
}
