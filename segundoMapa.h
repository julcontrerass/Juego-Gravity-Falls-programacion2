#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "dipper.h"
#include "colisiones.h"
#include "mochila.h"
#include "estadoDelJuego.h"

class SegundoMapa
{
private:
    sf::Sprite imagen,imagen2,mcgucket;
    sf::Texture tex,tex2,tex3;
    sf::Font font;
    sf::Text texto;
    sf::View camera;
    Dipper dipper;
    std::vector<sf::FloatRect> zonasBloqueadas;
    Mochila mochila;
    estadoDelJuego estadoDelJuego;


public:
    SegundoMapa();
    void update(sf::RenderWindow &window);
    void handleCollisions();
    void draw(sf::RenderWindow &window);
    void setPersonajePosition(const sf::Vector2f& position);
    sf::Vector2f getDipperPosition() const;

};

