#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "dipper.h"
#include "colisiones.h"
#include "mochila.h"
#include "cofre.h"
#include "libro3.h"
#include "gancho.h"
#include "minotauro.h"
#include "soos.h"
#include "estadoDelJuego.h"

class SeptimoMapa
{
private:
    sf::Sprite imagen,imagen2;
    sf::Texture tex,tex2;
    sf::View camera;
    sf::Font font1;
    sf::Text texVidas,texVidasEnemigo;
    Dipper dipper;
    std::vector<sf::FloatRect> zonasBloqueadas;
    Mochila mochila;
    Cofre cofre;
    Libro3 libro3;
    Gancho gancho;
    Minotauro minotauro;
    Soos soos;
    sf::Clock _relojDialogo;
    estadoDelJuego estadoDelJuego;




public:
    SeptimoMapa();
    void update(sf::RenderWindow &window);
    void handleCollisions();
    void draw(sf::RenderWindow &window);
    void setPersonajePosition(const sf::Vector2f& position);
    static bool dialogoIniciado;
    sf::Vector2f getDipperPosition() const;

};
