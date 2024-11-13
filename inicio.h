#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Inicio {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Text botonStart;
    sf::Font font;
    sf::FloatRect limitesDelTexto;
    sf::Clock tiempo;
    bool textoVisible;
    bool startClicked;
    const float BLINK_INTERVAL = 0.5f;

public:
    Inicio();
    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    bool shouldStartGame() const { return startClicked; }
};
