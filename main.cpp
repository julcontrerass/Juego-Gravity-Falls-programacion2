#include <SFML/Graphics.hpp>
#include "Incio.h"  // Incluir el archivo de la pantalla de inicio
#include "PrimerMapa.h"  // Incluir el archivo de la nueva clase PrimerMapa

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Gravity Falls");
    window.setFramerateLimit(60);

    // Mostrar la pantalla de inicio antes de entrar al juego
    StartScreen startScreen;
    startScreen.run(window);  // Mostrar pantalla de inicio

    // Iniciar el primer mapa del juego
    PrimerMapa primerMapa;
    primerMapa.run(window);

    return 0;
}






