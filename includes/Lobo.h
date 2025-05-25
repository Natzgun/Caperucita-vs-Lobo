#ifndef LOBO_H
#define LOBO_H

#include <Character.h>

class Lobo : public Character {
public:
    Lobo(const sf::Texture& texture, float step = 1.f);
};

#endif // LOBO_H