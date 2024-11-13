#pragma once
#include <SFML/Graphics.hpp>


class MenuControles {
private:
    sf::Font font;
    sf::Text exitButton;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    bool isOpen;

public:
    MenuControles();
    void draw(sf::RenderWindow& window);
    bool handleClick(sf::Vector2i mousePos);
    bool getIsOpen() const { return isOpen; }
    void open();
    void close();
};
