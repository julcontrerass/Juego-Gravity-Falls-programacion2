#include <SFML/Graphics.hpp>
#include "inicio.h"
#include "estadoDeMapas.h"
#include "dipper.h"
#include "gameOver.h"
#include "dipper.h"
#include "estadoDelJuego.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Juego Gravity Falls");
    window.setFramerateLimit(60);

    Inicio inicio;
    EstadoDeMapas estadoJuego;
    GameOver gameOver;
    estadoDelJuego estadoDelJuego;
    bool isGameOver = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }

            if (!inicio.shouldStartGame()) {
                inicio.handleEvent(event, window);
            } else if (!isGameOver) {
                estadoJuego.handleEvent(event, window);
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                window.close();
            }
        }

        window.clear();

        if (!inicio.shouldStartGame()) {
            inicio.run(window);
            if (inicio.shouldStartGame()) {
                estadoJuego.inicioJuego(true);
            }
        } else {
            if (estadoDelJuego.getVidasDipper() == 0) {
                isGameOver = true;
            }

            if (!isGameOver) {
                estadoJuego.update(window);
                estadoJuego.draw(window);
            } else {
                gameOver.draw(window);
            }
        }

        window.display();
    }
    return 0;
}
