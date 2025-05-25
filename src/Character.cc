#include <Character.h>

Character::Character(const sf::Texture& texture, float step)
    : mStep(step) {
    mSprite.setTexture(texture);
    mSprite.setOrigin(
        texture.getSize().x / 2.f,
        texture.getSize().y / 2.f
    );
}

void Character::setPosition(float x, float y) {
    mSprite.setPosition(x, y);
}

sf::Vector2f Character::getPosition() const {
    return mSprite.getPosition();
}

void Character::moveUp() {
    mSprite.move(0.f, -mStep);
}

void Character::moveDown() {
    mSprite.move(0.f, mStep);
}

void Character::moveLeft() {
    mSprite.move(-mStep, 0.f);
}

void Character::moveRight() {
    mSprite.move(mStep, 0.f);
}

void Character::draw(sf::RenderTarget& target) const {
    target.draw(mSprite);
}