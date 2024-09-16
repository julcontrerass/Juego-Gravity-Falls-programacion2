#ifndef SEGUNDO_MAPA_H
#define SEGUNDO_MAPA_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "personaje.h"

class SegundoMapa
{
public:
    SegundoMapa();
    void run(sf::RenderWindow &window);
    Personaje dipper;
    void setPersonajePosition(const sf::Vector2f& position);

private:
    void update(sf::RenderWindow &window);
    void handleCollisions();
    void draw(sf::RenderWindow &window);

    sf::Texture tex;
    sf::Sprite imagen;
    int vidas;
    sf::Text textVidas;
    sf::Clock invulnerableClock;
    sf::Time invulnerableTime;
    sf::Time invulnerableDuration;
    sf::View camera;

    std::vector<sf::FloatRect> zonasBloqueadas;
};

#endif // SEGUNDO_MAPA_H

