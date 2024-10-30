#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "dipper.h"
#include "colisiones.h"
#include "mochila.h"
#include "libro2.h"
#include "cofre.h"
#include "quintoMapa.h"
#include "pocionDeVelocidad.h"
#include "linterna.h"
#include "gideon.h"
#include "mabbel.h"

class NovenoMapa
{
private:
    sf::Sprite imagen,imagen2;
    sf::Texture tex,tex2;
    sf::View camera;
    sf::Font font1,font2;
    sf::Text texVidas,texVidasEnemigo;
    Dipper dipper;
    std::vector<sf::FloatRect> zonasBloqueadas;
    Mochila mochila;
    Libro2 libro2;
    Cofre cofre;
    PocionDeVelocidad pocion;
    Linterna linterna;
    Gideon gideon;
    Mabbel mabbel;
    sf::Clock _relojDialogo;


public:
    NovenoMapa();
    void update(sf::RenderWindow &window);
    void handleCollisions();
    void draw(sf::RenderWindow &window);
    void setPersonajePosition(const sf::Vector2f& position);
    sf::Vector2f getDipperPosition() const;
    static bool dialogoIniciado;
};
