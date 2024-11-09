#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "dipper.h"
#include "colisiones.h"
#include "stan.h"
#include "cofre.h"
#include "segundoMapa.h"
#include "mochila.h"
#include "soos.h"
#include "wendy.h"
#include "cuchillo.h"
#include "mabbel.h"
#include "estadoDelJuego.h"

class PrimerMapa
{
private:
    sf::Sprite imagen,imagen2;
    sf::Texture tex,tex2;
    sf::View camera;
    sf::Music musicaJuego;
    Dipper dipper;
    Stan stan;
    Cofre cofre;
    SegundoMapa segundoMapa;
    std::vector<sf::FloatRect> zonasBloqueadas;
    Mochila mochila;
    sf::Clock _relojDialogo;
    Soos soos;
    Wendy wendy;
    Cuchillo cuchillo;
    bool desaparecioWendy,desaparecioSoos;
    Mabbel mabbel;

    estadoDelJuego estadoDelJuego;

public:
    PrimerMapa();
    void update(sf::RenderWindow &window);
    void handleCollisions();
    void draw(sf::RenderWindow &window);
    void setPersonajePosition(const sf::Vector2f& position);
    static bool dialogoIniciado;
    sf::Vector2f getDipperPosition() const;
};
