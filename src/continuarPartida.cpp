#include "../continuarPartida.h"
#include "../menu.h"
#include <vector>
#include <iostream>
#include <algorithm>

ContinuarPartida::ContinuarPartida() :
    opcionSeleccionada(0),
    lastKeyPress(sf::Keyboard::Unknown),
    isOpen(false),volver(false)
{
    if (!font.loadFromFile("./font/letragravityFalls.ttf"))
    {
        throw std::runtime_error("No se pudo cargar la fuente");
    }

    if (!texFondo.loadFromFile("./Imagenes/FondoMenu.jpg"))
    {
        throw std::runtime_error("No se pudo cargar la textura del fondo");
    }

    if (!bufferSonido.loadFromFile("./Imagenes/Sonidos/sonidoMenu.wav"))
    {
        throw std::runtime_error("Error al cargar el sonido de selección");
    }

    imagenFondo.setTexture(texFondo);
    sonidoSeleccion.setBuffer(bufferSonido);
    sonidoSeleccion.setVolume(50);

    titulo.setFont(font);
    titulo.setString("SELECCIONAR PARTIDA");
    titulo.setCharacterSize(35);
    titulo.setFillColor(sf::Color(143, 159, 97));
    titulo.setPosition(150, 70);

    salirMenu.setFont(font);
    salirMenu.setCharacterSize(30);
    salirMenu.setString("X");
    salirMenu.setFillColor(sf::Color::Red);
    salirMenu.setPosition(20, 20);

    cargarPartidas();
}

void ContinuarPartida::cargarPartidas()
{
    std::vector<std::string> nombresPartidas;
    estadoDelJuego.cargarPartida(nombresPartidas);  // Asumiendo que este método llena el vector
    partidas.clear();
    borradores.clear();

    // Crear los textos para mostrar en pantalla
    float yOffset = 200;
    for (const auto& nombre : nombresPartidas)
    {
        // Crear texto para el nombre de la partida
        sf::Text partida;
        partida.setFont(font);
        partida.setCharacterSize(30);
        partida.setString(nombre);
        partida.setPosition(300, yOffset);
        partida.setFillColor(sf::Color::White);
        partidas.push_back(partida);

        // Crear texto para el botón de borrar
        sf::Text borrador;
        borrador.setFont(font);
        borrador.setCharacterSize(30);
        borrador.setString("X");
        borrador.setPosition(500, yOffset);
        borrador.setFillColor(sf::Color::Red);
        borradores.push_back(borrador);

        yOffset += 50;
    }

    if (!partidas.empty())
    {
        partidas[0].setFillColor(sf::Color(143, 159, 97));
        partidas[0].setStyle(sf::Text::Underlined);
    }
}

void ContinuarPartida::draw(sf::RenderWindow& window)
{
    if (!isOpen) return;

    window.draw(imagenFondo);
    window.draw(titulo);

    window.draw(salirMenu);

    // Obtener la posición actual del mouse
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    // Dibujar partidas y borradores
    for (size_t i = 0; i < partidas.size(); ++i)
    {
        window.draw(partidas[i]);
        window.draw(borradores[i]);

        // Highlight al pasar el mouse por encima
        if (partidas[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            partidas[i].setFillColor(sf::Color(143, 159, 97));
        }
        else if (static_cast<int>(i) != opcionSeleccionada)
        {
            partidas[i].setFillColor(sf::Color::White);
        }

        // Highlight para el botón de borrar
        if (borradores[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            borradores[i].setFillColor(sf::Color::Yellow);
        }
        else
        {
            borradores[i].setFillColor(sf::Color::Red);
        }
    }

    // Manejo de clics
    static bool mouseWasPressed = false;
    bool mouseIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (mouseIsPressed && !mouseWasPressed)    // Solo procesar cuando el botón se acaba de presionar
    {
        // Verificar clic en partidas
        for (size_t i = 0; i < partidas.size(); ++i)
        {
            if (partidas[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                std::string nombreJugador = partidas[i].getString().toAnsiString();
                estadoDelJuego.cargarPartida(nombreJugador);
                estadoDelJuego.setJugadorActual(nombreJugador);
                estadoDelJuego.continuarPartida();
                menuInicio::gameStarted = true;
                iniciarJuego = true;
                close();
                return;
            }
        }

        // Verificar clic en borradores
        for (size_t i = 0; i < borradores.size(); ++i)
        {
            if (borradores[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                std::string nombreJugador = partidas[i].getString().toAnsiString();
                if (!nombreJugador.empty())
                {
                    estadoDelJuego.borrarPartida(nombreJugador);
                    cargarPartidas();  // Recargar la lista después de borrar
                    break;  // Salir del loop después de borrar
                }
            }
        }
    }
    static bool clickMouse = false;
    bool click = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (click && !clickMouse)
    {
        // Check if the mouse clicked on the "Return to Menu" button
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (salirMenu.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            // Return to the main menu
            volver = true;
            estadoMapas.inicioJuego(false);
            menuInicio::gameStarted = false;
            close();
        }
    }
    clickMouse = click;
}


void ContinuarPartida::movimiento(sf::RenderWindow& window)
{
    if (!isOpen || partidas.empty()) return;

    bool keyPressed = false;
    sf::Keyboard::Key currentKey = sf::Keyboard::Unknown;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        currentKey = sf::Keyboard::Down;
        keyPressed = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        currentKey = sf::Keyboard::Up;
        keyPressed = true;
    }

    if (keyPressed && currentKey != lastKeyPress && moveClock.getElapsedTime().asMilliseconds() > 200)
    {
        // Actualizar la selección
        if (currentKey == sf::Keyboard::Down)
        {
            opcionSeleccionada = (opcionSeleccionada + 1) % partidas.size();
        }
        else
        {
            opcionSeleccionada = (opcionSeleccionada - 1 + partidas.size()) % partidas.size();
        }

        // Actualizar colores
        for (size_t i = 0; i < partidas.size(); ++i)
        {
            if (i == static_cast<size_t>(opcionSeleccionada))
            {
                partidas[i].setFillColor(sf::Color(143, 159, 97));
                partidas[i].setStyle(sf::Text::Underlined);
            }
            else
            {
                partidas[i].setFillColor(sf::Color::White);
                partidas[i].setStyle(sf::Text::Regular);
            }
        }

        sonidoSeleccion.play();
        moveClock.restart();
        lastKeyPress = currentKey;
    }
}

