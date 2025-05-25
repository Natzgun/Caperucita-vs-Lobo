#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>

class Character {
public:
    explicit Character(const sf::Texture& texture, float step = 1.f);

    void setPosition(float x, float y);
    [[nodiscard]] sf::Vector2f getPosition() const;

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void draw(sf::RenderTarget& target) const;
private:
    sf::Sprite mSprite;
    float mStep;
};

#endif // CHARACTER_H