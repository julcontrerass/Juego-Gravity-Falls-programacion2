#pragma once
#include <SFML/Graphics.hpp>

class GameOver
{
public:
    GameOver();
    void draw(sf::RenderWindow& window);  // Cambiado de run a draw
private:
    sf::Font font;
    sf::Text gameOverText;
    sf::Text espacio;
};
