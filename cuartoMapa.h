#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "dipper.h"
#include "colisiones.h"
#include "mochila.h"
#include "pocionDeVelocidad.h"
#include "estadoDelJuego.h"

class CuartoMapa
{
private:
    sf::Sprite imagen;
    sf::Texture tex;
    sf::View camera;
    Dipper dipper;
    std::vector<sf::FloatRect> zonasBloqueadas;
    Mochila mochila;
    PocionDeVelocidad pocion;
    estadoDelJuego estadoDelJuego;
public:
    CuartoMapa();
    void update(sf::RenderWindow &window);
    void handleCollisions();
    void draw(sf::RenderWindow &window);
    void setPersonajePosition(const sf::Vector2f& position);
    sf::Vector2f getDipperPosition() const;
};
