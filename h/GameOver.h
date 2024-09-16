#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SFML/Graphics.hpp>

class GameOver
{
public:
    GameOver();
    void run(sf::RenderWindow& window);

private:
    sf::Font font;
    sf::Text gameOverText;
    sf::Text espacio;
};

#endif
