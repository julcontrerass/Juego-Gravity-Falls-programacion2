#include "incio.h"

StartScreen::StartScreen() {
    loadResources();
}

void StartScreen::loadResources() {
    // Cargar el fondo de pantalla
    if (!backgroundTexture.loadFromFile("images/start.png")) {
        throw std::runtime_error("Error al cargar la imagen de fondo");
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Cargar la fuente
    if (!font.loadFromFile("font/numeros.ttf")) { // Cambia por la fuente que uses
        throw std::runtime_error("Error al cargar la fuente");
    }

    // Configurar el texto del botón de inicio
    startButtonText.setFont(font);
    startButtonText.setString("START");
    startButtonText.setCharacterSize(50);
    startButtonText.setFillColor(sf::Color::White);
    startButtonText.setPosition(338, 360); // Posición en la pantalla

    // Configurar el texto de instrucciones
    instructionsText.setFont(font);
    instructionsText.setString("Ayuda a conseguir los 3 libros para \n"
                               "derrotar a los bosses y salvar al \n"
                               "pueblo de Gravity Falls");
    instructionsText.setCharacterSize(25);
    instructionsText.setFillColor(sf::Color::Yellow);
    instructionsText.setPosition(180, 450); // Posición en la pantalla

    // Cargar y configurar la música de la pantalla de inicio
    if (!startScreenMusic.openFromFile("musica.wav")) { // Cambia por el nombre del archivo
        throw std::runtime_error("Error al cargar la música de inicio");
    }
    startScreenMusic.setLoop(true); // Para que la música se repita en bucle
}

void StartScreen::run(sf::RenderWindow& window) {
    // Reproducir la música de inicio
    startScreenMusic.play();

    sf::Clock clock; // Reloj para manejar el efecto de parpadeo
    bool isTextVisible = true; // Variable para alternar la visibilidad del texto

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                if (isStartButtonClicked(window)) {
                    startScreenMusic.stop();  // Detener la música cuando inicie el juego
                    return; // Salir de la pantalla de inicio
                }
            }
        }

        // Actualizar el parpadeo del texto
        float elapsed = clock.getElapsedTime().asSeconds();
        if (elapsed >= 0.3f) { // Cada 0.5 segundos
            isTextVisible = !isTextVisible;
            startButtonText.setFillColor(isTextVisible ? sf::Color::White : sf::Color(169, 169, 169));
            clock.restart();
        }

        window.clear();
        draw(window);
        window.display();
    }
}

void StartScreen::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(startButtonText);
    window.draw(instructionsText);
}

bool StartScreen::isStartButtonClicked(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::FloatRect startButtonBounds = startButtonText.getGlobalBounds();

    return startButtonBounds.contains(static_cast<sf::Vector2f>(mousePos));
}
