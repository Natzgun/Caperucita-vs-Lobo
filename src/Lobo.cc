#include "Lobo.h"

Lobo::Lobo(const std::string &texturePath, float x, float y) {
  if (!texture.loadFromFile(texturePath)) {
    throw std::runtime_error("No se pudo cargar la textura: " + texturePath);
  }
  sprite.setTexture(texture);
  sprite.setPosition(x, y);
}

void Lobo::setPosition(float x, float y) { sprite.setPosition(x, y); }

sf::Vector2f Lobo::getPosition() const { return sprite.getPosition(); }

void Lobo::draw(sf::RenderWindow &window) const { window.draw(sprite); }
