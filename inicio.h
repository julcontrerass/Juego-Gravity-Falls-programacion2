#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "menu.h"

class Inicio {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text botonStart;
    bool textoVisible;
    sf::Clock tiempo;
    menuInicio menu;
    bool incioMenu;
    sf::FloatRect limitesDelTexto;
    sf::Music musicaFondo;
    bool startClicked;
    bool musicStarted;
    static constexpr float BLINK_INTERVAL = 0.5f;

public:
    Inicio();
    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void run(sf::RenderWindow& window);
    bool shouldStartGame() const { return incioMenu && menu.hasGameStarted();};
};
