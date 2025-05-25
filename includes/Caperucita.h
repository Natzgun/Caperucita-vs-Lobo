#ifndef CAPERUCITA_H
#define CAPERUCITA_H

#include <Character.h>

class Caperucita : public Character {
public:
    Caperucita(const sf::Texture& texture, float step = 1.f);
};

#endif // CAPERUCITA_H