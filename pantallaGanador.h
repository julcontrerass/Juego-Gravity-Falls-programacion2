#pragma once
#include <SFML/Graphics.hpp>
#include "estadoDelJuego.h"

class PantallaGanador{
public:
    PantallaGanador();

    void draw(sf::RenderWindow& window);
private:
    sf::Font font;
    sf::Text pantallaGanadorText;
    sf::Text espacio;
};
