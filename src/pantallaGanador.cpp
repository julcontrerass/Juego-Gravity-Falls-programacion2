#include "../../pantallaGanador.h"

PantallaGanador::PantallaGanador()
{
    // Cargar la fuente
    if (!font.loadFromFile("./Font/letragravityFalls.ttf"))
    {
        // Manejar el error si no se puede cargar la fuente
    }
    // Configurar el texto de fin de juego
    pantallaGanadorText.setFont(font);
    pantallaGanadorText.setString("Felicidades!");
    pantallaGanadorText.setCharacterSize(50);
    pantallaGanadorText.setFillColor(sf::Color::Red);
    pantallaGanadorText.setPosition(200, 250);

    espacio.setFont(font);
    espacio.setString("Presione espacio para ir al menú");
    espacio.setCharacterSize(20);
    espacio.setFillColor(sf::Color::White);
    espacio.setPosition(250, 400);
}

void PantallaGanador::draw(sf::RenderWindow& window)
{
    window.draw(pantallaGanadorText);
    window.draw(espacio);
}
