#include "../inicio.h"

Inicio::Inicio() :
    textoVisible(true),
    incioMenu(false),
    startClicked(false),
    musicStarted(false),
    menu(musicaFondo)
{
    if (!backgroundTexture.loadFromFile("./Imagenes/inicio.png")) {
        throw std::runtime_error("No se pudo cargar la textura del fondo de inicio");
    }
    backgroundSprite.setTexture(backgroundTexture);

    if (!musicaFondo.openFromFile("./Imagenes/Sonidos/musica.wav")) {
        throw std::runtime_error("Error al cargar la música de inicio");
    }
    musicaFondo.setVolume(20);
    musicaFondo.setLoop(true);

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
    if (!incioMenu && event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (botonStart.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                startClicked = true;
            }
        }
    }
}

void Inicio::update(sf::RenderWindow& window) {
    if (!incioMenu) {
        // Parpadeo más lento del texto START
        if (tiempo.getElapsedTime().asSeconds() >= BLINK_INTERVAL) {
            textoVisible = !textoVisible;
            botonStart.setFillColor(textoVisible ? sf::Color::White : sf::Color(128, 128, 128));
            tiempo.restart();
        }

        if (startClicked) {
            incioMenu = true;
            startClicked = false;
        }
    }
}

void Inicio::draw(sf::RenderWindow& window) {
    if (!incioMenu) {
        window.draw(backgroundSprite);
        window.draw(botonStart);
    } else {
        menu.draw(window);
    }
}

void Inicio::run(sf::RenderWindow& window) {
    if (!musicStarted) {
        musicaFondo.play();
        musicStarted = true;
    }

    update(window);
    draw(window);
}

