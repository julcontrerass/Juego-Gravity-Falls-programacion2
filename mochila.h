#pragma once
#include <SFML/Graphics.hpp>

#include "bebidaDeVida.h"
#include "pocionDeVelocidad.h"
#include "gancho.h"
#include "cuchillo.h"
#include "linterna.h"
#include "libro1.h"
#include "libro2.h"
#include "libro3.h"
#include "dipper.h"
#include "estadoDelJuego.h"



class Mochila
{
private:
    sf::RectangleShape background;
    sf::Font font;
    sf::Text txtVidas;
    sf::Text txtArmas;
    sf::Text txtBebidas, cantBebidas,cantPociones;
    sf::Text txtLibros;
    BebidaDeVida bebidaDeVida;
    PocionDeVelocidad posionVelocidad;
    Gancho gancho;
    Cuchillo cuchillo;
    Linterna linterna;
    Libro1 libro1;
    Libro2 libro2;
    Libro3 libro3;
//    Dipper dipper;
    estadoDelJuego estadoDelJuego;


public:
    Mochila();
    void draw(sf::RenderWindow& window);
};
