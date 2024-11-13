#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "estadoDelJuego.h"
#include <vector>

class ContinuarPartida {
private:
    sf::Font font;
    sf::Text titulo;
    std::vector<sf::Text> partidas;
    std::vector<sf::Text> borradores;
    sf::Texture texFondo;
    sf::Sprite imagenFondo;
    sf::Sound sonidoSeleccion;
    sf::SoundBuffer bufferSonido;

    int opcionSeleccionada;
    sf::Clock moveClock;
    sf::Clock soundClock;
    sf::Keyboard::Key lastKeyPress;
    bool isOpen;
    estadoDelJuego estadoDelJuego;
    bool iniciarJuego = false;

public:
    ContinuarPartida();
    void draw(sf::RenderWindow& window);
    void movimiento(sf::RenderWindow& window);
    void open() { isOpen = true; }
    void close() { isOpen = false; }
    bool getIsOpen() const { return isOpen; }
    void cargarPartidas();
    bool debeIniciarJuego() const { return iniciarJuego; }
    void reiniciarInicioJuego() { iniciarJuego = false; }
};
