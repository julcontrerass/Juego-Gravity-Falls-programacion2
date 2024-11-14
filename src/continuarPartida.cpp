#include "../continuarPartida.h"
#include "../menu.h"
#include <vector>
#include <iostream>
#include <algorithm>

// Constructor de la clase ContinuarPartida - Inicializa el menú de continuación de partida
ContinuarPartida::ContinuarPartida() :
    opcionSeleccionada(0),        // Índice de la opción seleccionada actualmente
    lastKeyPress(sf::Keyboard::Unknown), // Última tecla presionada
    isOpen(false),                // Estado del menú (abierto/cerrado)
    volver(false)                 // Flag para volver al menú principal
{
    // Carga la fuente personalizada para el texto
    if (!font.loadFromFile("./font/letragravityFalls.ttf"))
    {
        throw std::runtime_error("No se pudo cargar la fuente");
    }

    // Carga la imagen de fondo del menú
    if (!texFondo.loadFromFile("./Imagenes/FondoMenu.jpg"))
    {
        throw std::runtime_error("No se pudo cargar la textura del fondo");
    }

    // Carga el efecto de sonido para la navegación del menú
    if (!bufferSonido.loadFromFile("./Imagenes/Sonidos/sonidoMenu.wav"))
    {
        throw std::runtime_error("Error al cargar el sonido de selección");
    }

    // Configura la imagen de fondo
    imagenFondo.setTexture(texFondo);

    // Configura el sonido de selección
    sonidoSeleccion.setBuffer(bufferSonido);
    sonidoSeleccion.setVolume(50);

    // Configura el título del menú
    titulo.setFont(font);
    titulo.setString("SELECCIONAR PARTIDA");
    titulo.setCharacterSize(35);
    titulo.setFillColor(sf::Color(143, 159, 97));  // Color verde personalizado
    titulo.setPosition(150, 70);

    // Configura el botón de salir
    salirMenu.setFont(font);
    salirMenu.setCharacterSize(30);
    salirMenu.setString("X");
    salirMenu.setFillColor(sf::Color::Red);
    salirMenu.setPosition(20, 20);

    // Carga las partidas guardadas
    cargarPartidas();
}

// Carga y configura visualmente las partidas guardadas
void ContinuarPartida::cargarPartidas()
{
    std::vector<std::string> nombresPartidas;
    estadoDelJuego.cargarPartida(nombresPartidas);  // Obtiene los nombres de las partidas guardadas
    partidas.clear();     // Limpia el vector de textos de partidas
    borradores.clear();   // Limpia el vector de botones de borrado

    // Crea los elementos visuales para cada partida guardada
    float yOffset = 200;  // Posición vertical inicial
    for (const auto& nombre : nombresPartidas)
    {
        // Configura el texto del nombre de la partida
        sf::Text partida;
        partida.setFont(font);
        partida.setCharacterSize(30);
        partida.setString(nombre);
        partida.setPosition(300, yOffset);
        partida.setFillColor(sf::Color::White);
        partidas.push_back(partida);

        // Configura el botón de borrar para esta partida
        sf::Text borrador;
        borrador.setFont(font);
        borrador.setCharacterSize(30);
        borrador.setString("X");
        borrador.setPosition(500, yOffset);
        borrador.setFillColor(sf::Color::Red);
        borradores.push_back(borrador);

        yOffset += 50;  // Incrementa la posición vertical para la siguiente partida
    }

    // Resalta la primera partida si existe alguna
    if (!partidas.empty())
    {
        partidas[0].setFillColor(sf::Color(143, 159, 97));
        partidas[0].setStyle(sf::Text::Underlined);
    }
}

// Dibuja el menú y maneja la interacción con el mouse
void ContinuarPartida::draw(sf::RenderWindow& window)
{
    if (!isOpen) return;  // No dibuja nada si el menú está cerrado

    // Dibuja los elementos básicos
    window.draw(imagenFondo);
    window.draw(titulo);
    window.draw(salirMenu);

    // Obtiene la posición actual del mouse
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    // Dibuja y maneja la interacción con las partidas y botones de borrado
    for (size_t i = 0; i < partidas.size(); ++i)
    {
        window.draw(partidas[i]);
        window.draw(borradores[i]);

        // Efecto hover al pasar el mouse sobre las partidas
        if (partidas[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            partidas[i].setFillColor(sf::Color(143, 159, 97));
        }
        else if (static_cast<int>(i) != opcionSeleccionada)
        {
            partidas[i].setFillColor(sf::Color::White);
        }

        // Efecto hover al pasar el mouse sobre los botones de borrado
        if (borradores[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            borradores[i].setFillColor(sf::Color::Yellow);
        }
        else
        {
            borradores[i].setFillColor(sf::Color::Red);
        }
    }

    // Manejo de clics del mouse
    static bool mouseWasPressed = false;
    bool mouseIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    // Procesa el clic cuando se presiona el botón
    if (mouseIsPressed && !mouseWasPressed)
    {
        // Verifica clics en las partidas
        for (size_t i = 0; i < partidas.size(); ++i)
        {
            if (partidas[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                // Carga y inicia la partida seleccionada
                std::string nombreJugador = partidas[i].getString().toAnsiString();
                estadoDelJuego.cargarPartida(nombreJugador);
                estadoDelJuego.setJugadorActual(nombreJugador);
                estadoDelJuego.continuarPartida();
                estadoMapas.inicioJuego(true);
                menuInicio::gameStarted = true;
                iniciarJuego = true;
                close();
                return;
            }
        }

        // Verifica clics en los botones de borrado
        for (size_t i = 0; i < borradores.size(); ++i)
        {
            if (borradores[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                std::string nombreJugador = partidas[i].getString().toAnsiString();
                if (!nombreJugador.empty())
                {
                    estadoDelJuego.borrarPartida(nombreJugador);
                    cargarPartidas();  // Recarga la lista después de borrar
                    break;
                }
            }
        }
    }

    // Manejo del botón de salir
    static bool clickMouse = false;
    bool click = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (click && !clickMouse)
    {
        // Verifica si se hizo clic en el botón de "Volver al Menú"
        if (salirMenu.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            volver = true;
            estadoMapas.inicioJuego(false);
            menuInicio::gameStarted = false;
            close();
        }
    }
    clickMouse = click;
}

// Maneja el movimiento de la selección mediante teclado
void ContinuarPartida::movimiento(sf::RenderWindow& window)
{
    if (!isOpen || partidas.empty()) return;

    bool keyPressed = false;
    sf::Keyboard::Key currentKey = sf::Keyboard::Unknown;

    // Detecta las teclas de navegación (flecha arriba/abajo o W/S)
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

    // Procesa el movimiento si se presionó una tecla válida y pasó suficiente tiempo
    if (keyPressed && currentKey != lastKeyPress && moveClock.getElapsedTime().asMilliseconds() > 200)
    {
        // Actualiza la selección según la tecla presionada
        if (currentKey == sf::Keyboard::Down)
        {
            opcionSeleccionada = (opcionSeleccionada + 1) % partidas.size();
        }
        else
        {
            opcionSeleccionada = (opcionSeleccionada - 1 + partidas.size()) % partidas.size();
        }

        // Actualiza los colores y estilos de las partidas
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

        // Reproduce el sonido de selección y reinicia el temporizador
        sonidoSeleccion.play();
        moveClock.restart();
        lastKeyPress = currentKey;
    }
}
