#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "dipper.h"
#include "colisiones.h"
#include "wendy.h"
#include "libro1.h"
#include "cofre.h"
#include "mochila.h"
#include "bebidaDeVida.h"
#include "cuchillo.h"
#include "gnomo.h"
#include "estadoDelJuego.h"


class TercerMapa
{
private:
    sf::Sprite imagen;
    sf::Texture tex;
    sf::View camera;
    sf::Font font1;
    sf::Text texVidas,texVidasEnemigo;
    sf::Music golpe;
    Dipper dipper;
    Wendy wendy;
    Libro1 libro1;
    Cofre cofre;
    std::vector<sf::FloatRect> zonasBloqueadas;
    Mochila mochila;
    BebidaDeVida bebida;
    Gnomo gnomo;
    sf::Clock _relojDialogo;
    estadoDelJuego estadoDelJuego;


public:
    TercerMapa();
    void update(sf::RenderWindow &window);
    void handleCollisions();
    void draw(sf::RenderWindow &window);
    void setPersonajePosition(const sf::Vector2f& position);
    static bool dialogoIniciado;
    sf::Vector2f getDipperPosition() const;
};
