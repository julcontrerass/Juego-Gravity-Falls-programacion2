#include "GameOver.h"

GameOver::GameOver()
{
    // Cargar la fuente
    if (!font.loadFromFile("font/letragravityFalls.ttf"))
    {
        // Manejar el error si no se puede cargar la fuente
    }

    // Configurar el texto de fin de juego
    gameOverText.setFont(font);
    gameOverText.setString("Juego Finalizado");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(200, 250); // Posicionar en el centro de la ventana
    espacio.setFont(font);
    espacio.setString("Presione espacio para salir");
    espacio.setCharacterSize(20);
    espacio.setFillColor(sf::Color::White);
    espacio.setPosition(250, 400); // Posicionar en el centro de la ventana
}

void GameOver::run(sf::RenderWindow& window)
{
    sf::Event event;
    while (true) // Bucle para mostrar la pantalla de fin de juego
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close(); // Cerrar la ventana si se presiona 'Escape' o se cierra la ventana
        }

        window.clear();
        window.draw(gameOverText);
        window.draw(espacio);
        window.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // Esperar a que el jugador presione 'Enter'
            break;
    }
}
