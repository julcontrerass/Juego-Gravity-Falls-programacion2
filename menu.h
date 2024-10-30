#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "primerMapa.h"
#include "menuControles.h"

class menuInicio {
private:
    int Opciones;
    sf::Font font;
    sf::Text menu[5];
    sf::Texture tex;
    sf::Sprite imagen;
    sf::Music sonidoInicio;
    sf::Clock moveClock;
    sf::Clock soundClock;
    sf::Keyboard::Key lastKeyPress;
    sf::Music* musicaFondoRef;
    PrimerMapa primerMapa;
    bool gameStarted;
    MenuControles menuControles;
    sf::Texture texJuli, texLiz, texJuani;
    sf::CircleShape imagenJuli, imagenLiz, imagenJuani;

public:
    menuInicio(sf::Music& musicaFondo);
    void draw(sf::RenderWindow& window);
    void movimiento();
    bool IniciarJuego(sf::RenderWindow& window); // Cambiar a bool
    void VinculoLinks(sf::RenderWindow& window);
    bool hasGameStarted() const { return gameStarted; } // Nuevo método
};
