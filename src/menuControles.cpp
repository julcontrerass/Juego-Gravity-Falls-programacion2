#include "../../menuControles.h"

MenuControles::MenuControles() : isOpen(false) {
    // Cargar la fuente
    if (!font.loadFromFile("./font/letragravityFalls.ttf")) {
        throw std::runtime_error("No se pudo cargar la fuente en MenuControles");
    }

    // Configurar el botón de salida (X)
    exitButton.setFont(font);
    exitButton.setString("X");
    exitButton.setCharacterSize(30);
    exitButton.setPosition(15, 20);
    exitButton.setFillColor(sf::Color::Black);

    // Cargar la imagen de fondo
    if (!backgroundTexture.loadFromFile("./Imagenes/Controles.png")) {
        throw std::runtime_error("No se pudo cargar la imagen de controles");
    }
    backgroundSprite.setTexture(backgroundTexture);
}

void MenuControles::draw(sf::RenderWindow& window) {
    if (!isOpen) return;

    window.draw(backgroundSprite);
    window.draw(exitButton);
}

bool MenuControles::handleClick(sf::Vector2i mousePos) {
    if (!isOpen) return false;

    // Obtener los límites del botón de salida
    sf::FloatRect exitBounds = exitButton.getGlobalBounds();


    if (exitBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        close();
        return true;
    }

    return false;
}

void MenuControles::open() {
    isOpen = true;
}

void MenuControles::close() {
    isOpen = false;
}
