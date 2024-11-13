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
    MenuControles menuControles;
    sf::Texture texJuli, texLiz, texJuani;
    sf::CircleShape imagenJuli, imagenLiz, imagenJuani;

    // Nuevas variables para el ingreso de nombre
    bool ingresandoNombre;
    std::string nombreJugador;
    sf::Text textoSolicitudNombre;
    sf::Text textoNombreActual,salirMenu;
    sf::RectangleShape cajaEntrada;

    estadoDelJuego estadoDelJuego;

    bool seleccionoNuevaPartida = false;



public:
    menuInicio(sf::Music& musicaFondo);
    void draw(sf::RenderWindow& window);
    bool IniciarJuego(sf::RenderWindow& window);
    void VinculoLinks(sf::RenderWindow& window);
    bool hasGameStarted() const { return gameStarted; }
    void manejarEntradaNombre(sf::Event evento);
    const std::string& getNombreJugador() const { return nombreJugador; }
    static bool gameStarted;
    int getSelectedOption() const {return Opciones;}
    bool seleccionoContinuar = false;
    void movimiento();
};
