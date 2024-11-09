#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "dipper.h"
#include "colisiones.h"
#include "mochila.h"
#include "bill.h"
#include "estadoDelJuego.h"


class MapaFinal
{
private:
    sf::Sprite imagen;
    sf::Texture tex;
    sf::Font font1;
    sf::Text texVidas,texVidasEnemigo;
    sf::View camera;
    Dipper dipper;
    std::vector<sf::FloatRect> zonasBloqueadas;
    Mochila mochila;
    Bill bill;
    estadoDelJuego estadoDelJuego;


public:
    MapaFinal();
    void update(sf::RenderWindow &window);
    void handleCollisions();
    void draw(sf::RenderWindow &window);
    void setPersonajePosition(const sf::Vector2f& position);
};
