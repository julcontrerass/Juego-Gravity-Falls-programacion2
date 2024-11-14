#include "../../pantallaGanador.h"

PantallaGanador::PantallaGanador()
{
    // Cargar la fuente
    if (!font.loadFromFile("./Font/letragravityFalls.ttf"))
    {
        throw std::runtime_error("No se pudo cargar la fuente para el texto de pantalla ganada");
    }
    // Configurar el texto de fin de juego
    pantallaGanadorText.setFont(font);
    pantallaGanadorText.setString("Felicidades!");
    pantallaGanadorText.setCharacterSize(50);
    pantallaGanadorText.setFillColor(sf::Color(143, 159, 97));
    pantallaGanadorText.setPosition(280, 200);

    espacio.setFont(font);
    espacio.setString("Presione espacio para ir al menú");
    espacio.setCharacterSize(20);
    espacio.setFillColor(sf::Color(143, 159, 97));
    espacio.setPosition(250, 300);
}

void PantallaGanador::draw(sf::RenderWindow& window)
{
    window.draw(pantallaGanadorText);
    window.draw(espacio);
}
