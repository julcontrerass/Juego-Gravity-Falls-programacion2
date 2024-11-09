#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "dipper.h"
#include "colisiones.h"
#include "mochila.h"
#include "libro2.h"
#include "cofre.h"
#include "bebidaDeVida.h"
#include "linterna.h"
#include "estadoDelJuego.h"


class QuintoMapa
{
private:
    sf::Sprite imagen,imagen2;
    sf::Texture tex,tex2;
    sf::Font font1,font2;
    sf::Text texVidas,texVidasEnemigo;
    sf::View camera;
    Dipper dipper;
    std::vector<sf::FloatRect> zonasBloqueadas;
    Mochila mochila;
    Libro2 libro2;
    Cofre cofre;
    BebidaDeVida bebida;
    Linterna linterna;
    sf::Vector2f dipperPos;
    estadoDelJuego estadoDelJuego;

public:
    QuintoMapa();
//    void run(sf::RenderWindow &window);
    void update(sf::RenderWindow &window);
    void handleCollisions();
    void draw(sf::RenderWindow &window);
    void setPersonajePosition(const sf::Vector2f& position);
    sf::Vector2f getDipperPosition() const;

//    void cambiosDeMapa(sf::RenderWindow &window);
};
