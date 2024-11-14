#include "../menu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

menuInicio::menuInicio(sf::Music& musicaFondo) :
    Opciones(0),
    lastKeyPress(sf::Keyboard::Unknown),
    musicaFondoRef(&musicaFondo),
    ingresandoNombre(false),
    nombreJugador("")
{
    /// CARGA DE RECURSOS
    // Carga la fuente personalizada para el texto
    if (!font.loadFromFile("./font/letragravityFalls.ttf"))
    {
        throw std::runtime_error("No se pudo cargar la fuente");
    }

    // Carga la imagen de fondo del men�
    if (!tex.loadFromFile("./Imagenes/FondoMenu.jpg"))
    {
        throw std::runtime_error("No se pudo cargar la textura de los items del mapa.");
    }
    imagen.setTexture(tex);

    // Carga el efecto de sonido para la navegaci�n del men�
    if (!sonidoInicio.openFromFile("./Imagenes/Sonidos/sonidoMenu.wav"))
    {
        throw std::runtime_error("Error al cargar el sonido de inicio");
    }
    sonidoInicio.setVolume(50);

    // Configuraci�n de los elementos para el ingreso del nombre del jugador
    textoSolicitudNombre.setFont(font);
    textoSolicitudNombre.setCharacterSize(30);
    textoSolicitudNombre.setFillColor(sf::Color::White);
    textoSolicitudNombre.setString("Ingresa tu nombre:");
    textoSolicitudNombre.setPosition(300, 250);

    // Configuraci�n del texto donde se mostrar� el nombre que se est� ingresando
    textoNombreActual.setFont(font);
    textoNombreActual.setCharacterSize(20);
    textoNombreActual.setFillColor(sf::Color::White);
    textoNombreActual.setPosition(300, 300);

    // Configuraci�n de la caja de entrada visual para el nombre
    cajaEntrada.setSize(sf::Vector2f(300, 40));
    cajaEntrada.setPosition(295, 295);
    cajaEntrada.setFillColor(sf::Color(0, 0, 0, 100));
    cajaEntrada.setOutlineThickness(2);
    cajaEntrada.setOutlineColor(sf::Color(143, 159, 97));

    // Configuraci�n del bot�n para salir del men� de ingreso de nombre
    salirMenu.setFont(font);
    salirMenu.setCharacterSize(30);
    salirMenu.setString("X");
    salirMenu.setFillColor(sf::Color::Red);
    salirMenu.setPosition(20, 20);

    // Carga de las im�genes de los desarrolladores
    if (!texJuli.loadFromFile("./Imagenes/Creadores/ImagenJuli.jpg"))
    {
        throw std::runtime_error("No se pudo cargar la imagen del c�rculo 1");
    }
    if (!texLiz.loadFromFile("./Imagenes/Creadores/ImagenLiz.jpg"))
    {
        throw std::runtime_error("No se pudo cargar la imagen del c�rculo 2");
    }
    if (!texJuani.loadFromFile("./Imagenes/Creadores/ImagenJuani.jpg"))
    {
        throw std::runtime_error("No se pudo cargar la imagen del c�rculo 3");
    }

    // Configuraci�n de las opciones del men� principal
    for (int i = 0; i < 3; ++i)
    {
        menu[i].setFont(font);
        menu[i].setCharacterSize(30);
    }

    // Configuraci�n especial para el t�tulo y la secci�n de desarrolladores
    menu[3].setFont(font);
    menu[3].setCharacterSize(25);
    menu[4].setFont(font);
    menu[4].setCharacterSize(80);

    // Posicionamiento de los elementos del men�
    menu[4].setPosition(sf::Vector2f(270, 50));  // T�tulo
    menu[0].setPosition(sf::Vector2f(200, 200)); // Iniciar juego
    menu[1].setPosition(sf::Vector2f(230, 250)); // Continuar juego
    menu[2].setPosition(sf::Vector2f(300, 300)); // Controles
    menu[3].setPosition(sf::Vector2f(250, 400)); // Desarrolladores

    // Configuraci�n de colores y estilos del men�
    menu[4].setFillColor(sf::Color(143, 159, 97));
    menu[0].setFillColor(sf::Color(143, 159, 97));
    menu[0].setStyle(sf::Text::Underlined);
    menu[1].setFillColor(sf::Color::White);
    menu[2].setFillColor(sf::Color::White);
    menu[3].setFillColor(sf::Color::White);

    // Asignaci�n de textos a las opciones del men�
    menu[4].setString("MENU");
    menu[0].setString("INICIAR JUEGO NUEVO");
    menu[1].setString("CONTINUAR JUEGO");
    menu[2].setString("CONTROLES");
    menu[3].setString("DESARROLLADORES:");

    // Configuraci�n de las im�genes circulares de los desarrolladores
    imagenJuli.setRadius(50.f);
    imagenLiz.setRadius(50.f);
    imagenJuani.setRadius(50.f);

    // Configuraci�n del origen de las im�genes para centrarlas
    imagenJuli.setOrigin(50.f, 50.f);
    imagenLiz.setOrigin(50.f, 50.f);
    imagenJuani.setOrigin(50.f, 50.f);

    // Posicionamiento de las im�genes de los desarrolladores
    imagenJuli.setPosition(250, 500);
    imagenLiz.setPosition(400, 500);
    imagenJuani.setPosition(550, 500);

    // Asignaci�n de texturas a las im�genes de los desarrolladores
    imagenJuli.setTexture(&texJuli);
    imagenLiz.setTexture(&texLiz);
    imagenJuani.setTexture(&texJuani);

    // Inicializaci�n de los relojes para controlar tiempos
    moveClock.restart();
    soundClock.restart();
}

bool menuInicio::gameStarted=false;

// M�todo principal para dibujar el men� en la ventana
void menuInicio::draw(sf::RenderWindow& window)
{
    // Si estamos en modo de ingreso de nombre, mostrar esa pantalla
    if (ingresandoNombre)
    {
        window.draw(imagen);
        window.draw(cajaEntrada);
        window.draw(textoSolicitudNombre);
        textoNombreActual.setString(nombreJugador + "_"); // A�ade cursor visual
        window.draw(textoNombreActual);
        window.draw(salirMenu);

        // Manejo del clic para el bot�n de salir
        static bool clickMouse = false;
        bool click = sf::Mouse::isButtonPressed(sf::Mouse::Left);

        if (click && !clickMouse)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (salirMenu.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                ingresandoNombre = false;
                nombreJugador = "";
            }
        }
        clickMouse = click;
        return;
    }

    // Si el men� de controles est� abierto, mostrarlo
    if (menuControles.getIsOpen())
    {
        menuControles.draw(window);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            menuControles.handleClick(sf::Mouse::getPosition(window));
        }
        return;
    }

    // Dibuja los elementos b�sicos del men�
    window.draw(imagen);
    for(int i = 0; i < 5; i++)
    {
        window.draw(menu[i]);
    }

    // Dibuja las im�genes de los desarrolladores
    window.draw(imagenJuli);
    window.draw(imagenLiz);
    window.draw(imagenJuani);

    // Manejo de la interacci�n con el mouse
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool mouseInteracted = false;

    // Verifica la interacci�n del mouse con las opciones del men�
    for(int i = 0; i < 3; i++)
    {
        if(menu[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            if(Opciones != i)
            {
                // Cambia los estilos al pasar el mouse por encima
                menu[Opciones].setFillColor(sf::Color::White);
                menu[Opciones].setStyle(sf::Text::Regular);

                Opciones = i;
                menu[i].setFillColor(sf::Color(143, 159, 97));
                menu[i].setStyle(sf::Text::Underlined);

                // Reproduce el sonido de navegaci�n
                if (soundClock.getElapsedTime().asMilliseconds() > 100)
                {
                    sonidoInicio.play();
                    soundClock.restart();
                }
            }
            mouseInteracted = true;
        }

        // Manejo de la selecci�n de opciones
        if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && menu[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) ||
                (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && i == Opciones))
        {
            if (i == 2)
            {
                menuControles.open();
            }
            else if (i == 0)
            {
                IniciarJuego(window);
            }
            else if (i == 1)
            {
                seleccionoContinuar = true;
            }
            break;
        }
    }

    movimiento();
    VinculoLinks(window);
}

// Maneja la entrada de texto para el nombre del jugador
void menuInicio::manejarEntradaNombre(sf::Event evento)
{
    if (!ingresandoNombre) return;

    if (evento.type == sf::Event::TextEntered)
    {
        // Procesa las teclas especiales y caracteres
        if (evento.text.unicode == '\b') // Tecla de retroceso
        {
            if (!nombreJugador.empty())
            {
                nombreJugador.pop_back();
            }
        }
        else if (evento.text.unicode == '\r' || evento.text.unicode == '\n') // Enter
        {
            if (!nombreJugador.empty())
            {
                estadoDelJuego.setJugadorActual(nombreJugador);
                estadoDelJuego.guardarPartida();
                ingresandoNombre = false;
                estadoDelJuego.nuevaPartida();
                musicaFondoRef->stop();
                gameStarted = true;
            }
        }
        else if (evento.text.unicode < 128 && isprint(evento.text.unicode) &&
                 nombreJugador.length() < 20) // Caracteres normales
        {
            nombreJugador += static_cast<char>(evento.text.unicode);
        }
    }
}

// Maneja el movimiento entre opciones del men� usando el teclado
void menuInicio::movimiento()
{
    if (ingresandoNombre) return;

    // Navegaci�n con flechas o WASD
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (moveClock.getElapsedTime().asMilliseconds() > 200)
        {
            menu[Opciones].setFillColor(sf::Color::White);
            menu[Opciones].setStyle(sf::Text::Regular);
            Opciones = (Opciones + 1) % 3;
            menu[Opciones].setFillColor(sf::Color(143, 159, 97));
            menu[Opciones].setStyle(sf::Text::Underlined);
            sonidoInicio.play();
            moveClock.restart();
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (moveClock.getElapsedTime().asMilliseconds() > 200)
        {
            menu[Opciones].setFillColor(sf::Color::White);
            menu[Opciones].setStyle(sf::Text::Regular);
            Opciones = (Opciones - 1 + 3) % 3;
            menu[Opciones].setFillColor(sf::Color(143, 159, 97));
            menu[Opciones].setStyle(sf::Text::Underlined);
            sonidoInicio.play();
            moveClock.restart();
        }
    }
}

// Inicia un nuevo juego
bool menuInicio::IniciarJuego(sf::RenderWindow& window)
{
    if (!menuInicio::gameStarted)
    {
        if (Opciones == 0)   // Si seleccion� "INICIAR JUEGO NUEVO"
        {
            ingresandoNombre = true; // Activa la pantalla de ingreso de nombre
            nombreJugador = ""; // Limpia el nombre existente
            estadoDelJuego.nuevaPartida(); // Reinicia el estado del juego
            return false;
        }
    }
    return false;
}

// Maneja los enlaces a los perfiles de GitHub de los desarrolladores
void menuInicio::VinculoLinks(sf::RenderWindow& window)
{
    if (ingresandoNombre) return;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        // Abre el perfil de GitHub correspondiente al hacer clic en la imagen
        if (imagenJuli.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        {
            std::string link1 = "https://github.com/julcontrerass";
            system(("start " + link1).c_str());
        }
        else if (imagenLiz.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        {
            std::string link2 = "https://github.com/LizFl0res";
            system(("start " + link2).c_str());
        }

        else if (imagenJuani.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        {
            std::string link3 = "https://github.com/nemi1414";
            system(("start " + link3).c_str());
        }
    }
}


