#ifndef CAPERUCITA_H
#define CAPERUCITA_H

#include <SFML/Graphics.hpp>
#include <string>

class Caperucita {
public:
    Caperucita(const std::string& texturePath, float x, float y);

    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;

    void draw(sf::RenderWindow& window) const;

private:
    sf::Sprite sprite;
    sf::Texture texture;
};

#endif // CAPERUCITA_H
