#include "inicio.h"

Inicio::Inicio() :
    textoVisible(true),
    startClicked(false)
{
    if (!backgroundTexture.loadFromFile("./Imagenes/inicio.png")) {
        throw std::runtime_error("No se pudo cargar la textura del fondo de inicio");
    }
    backgroundSprite.setTexture(backgroundTexture);

    if (!font.loadFromFile("./font/numeros.ttf")) {
        throw std::runtime_error("No se pudo cargar la fuente");
    }

    botonStart.setFont(font);
    botonStart.setString("START");
    botonStart.setCharacterSize(50);
    botonStart.setFillColor(sf::Color::White);
    limitesDelTexto = botonStart.getLocalBounds();
    botonStart.setOrigin(limitesDelTexto.width / 2, limitesDelTexto.height / 2);
    botonStart.setPosition(400, 360);
    tiempo.restart();
}

void Inicio::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (botonStart.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                startClicked = true;
            }
        }
    }
}

void Inicio::update(sf::RenderWindow& window) {
    if (tiempo.getElapsedTime().asSeconds() >= BLINK_INTERVAL) {
        textoVisible = !textoVisible;
        botonStart.setFillColor(textoVisible ? sf::Color::White : sf::Color(128, 128, 128));
        tiempo.restart();
    }
}

void Inicio::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(botonStart);
}
