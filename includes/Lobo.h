#ifndef LOBO_H
#define LOBO_H

#include <Character.h>

class Lobo {
public:
  Lobo(const std::string &texturePath, float x, float y);

  void setPosition(float x, float y);
  sf::Vector2f getPosition() const;

  void draw(sf::RenderWindow &window) const;

private:
  sf::Sprite sprite;
  sf::Texture texture;
};

#endif // LOBO_H
