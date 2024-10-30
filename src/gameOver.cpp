#include "../gameOver.h"

GameOver::GameOver()
{
    // Cargar la fuente
    if (!font.loadFromFile("./Font/letragravityFalls.ttf"))
    {
        // Manejar el error si no se puede cargar la fuente
    }
    // Configurar el texto de fin de juego
    gameOverText.setFont(font);
    gameOverText.setString("Juego Finalizado");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(200, 250);

    espacio.setFont(font);
    espacio.setString("Presione espacio para salir");
    espacio.setCharacterSize(20);
    espacio.setFillColor(sf::Color::White);
    espacio.setPosition(250, 400);
}

void GameOver::draw(sf::RenderWindow& window)
{
    window.draw(gameOverText);
    window.draw(espacio);
}
