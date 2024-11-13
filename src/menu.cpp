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
    /// AGREGAMOS LA LETRA Y LAS IMAGENES
    if (!font.loadFromFile("./font/letragravityFalls.ttf"))
    {
        throw std::runtime_error("No se pudo cargar la fuente");
    }

    if (!tex.loadFromFile("./Imagenes/FondoMenu.jpg"))
    {
        throw std::runtime_error("No se pudo cargar la textura de los items del mapa.");
    }
    imagen.setTexture(tex);

    if (!sonidoInicio.openFromFile("./Imagenes/Sonidos/sonidoMenu.wav"))
    {
        throw std::runtime_error("Error al cargar el sonido de inicio");
    }
    sonidoInicio.setVolume(50);

    // Inicialización de los elementos para el ingreso de nombre
    textoSolicitudNombre.setFont(font);
    textoSolicitudNombre.setCharacterSize(30);
    textoSolicitudNombre.setFillColor(sf::Color::White);
    textoSolicitudNombre.setString("Ingresa tu nombre:");
    textoSolicitudNombre.setPosition(300, 250);

    textoNombreActual.setFont(font);
    textoNombreActual.setCharacterSize(20);
    textoNombreActual.setFillColor(sf::Color::White);
    textoNombreActual.setPosition(300, 300);

    cajaEntrada.setSize(sf::Vector2f(300, 40));
    cajaEntrada.setPosition(295, 295);
    cajaEntrada.setFillColor(sf::Color(0, 0, 0, 100));
    cajaEntrada.setOutlineThickness(2);
    cajaEntrada.setOutlineColor(sf::Color(143, 159, 97));

    // Cargar texturas para los círculos
    if (!texJuli.loadFromFile("./Imagenes/Creadores/ImagenJuli.jpg"))
    {
        throw std::runtime_error("No se pudo cargar la imagen del círculo 1");
    }
    if (!texLiz.loadFromFile("./Imagenes/Creadores/ImagenLiz.jpg"))
    {
        throw std::runtime_error("No se pudo cargar la imagen del círculo 2");
    }
    if (!texJuani.loadFromFile("./Imagenes/Creadores/ImagenJuani.jpg"))
    {
        throw std::runtime_error("No se pudo cargar la imagen del círculo 3");
    }

    ///LE DECLARAMOS LA FUENTE Y EL TAMAÑO AL MENU
    for (int i = 0; i < 3; ++i)
    {
        menu[i].setFont(font);
        menu[i].setCharacterSize(30);
    }

    menu[3].setFont(font);
    menu[3].setCharacterSize(25);
    menu[4].setFont(font);
    menu[4].setCharacterSize(80);

    ///DECLARAMOS LAS POSICIONES, LOS COLORES, EL CONTENIDO DE TEXTO
    menu[4].setPosition(sf::Vector2f(270, 50));
    menu[0].setPosition(sf::Vector2f(200, 200 + 0 * 50));
    menu[1].setPosition(sf::Vector2f(230, 200 + 1 * 50));
    menu[2].setPosition(sf::Vector2f(300, 200 + 2 * 50));
    menu[3].setPosition(sf::Vector2f(250, 400));

    menu[4].setFillColor(sf::Color(143, 159, 97));
    menu[0].setFillColor(sf::Color(143, 159, 97));
    menu[0].setStyle(sf::Text::Underlined);
    menu[1].setFillColor(sf::Color::White);
    menu[2].setFillColor(sf::Color::White);
    menu[3].setFillColor(sf::Color::White);

    menu[4].setString("MENU");
    menu[0].setString("INICIAR JUEGO NUEVO");
    menu[1].setString("CONTINUAR JUEGO");
    menu[2].setString("CONTROLES");
    menu[3].setString("DESARROLLADORES:");

    /// LE DAMOS LA FORMA CIRCULAR A LAS IMAGENES
    imagenJuli.setRadius(50.f);
    imagenLiz.setRadius(50.f);
    imagenJuani.setRadius(50.f);

    /// LE DAMOS LAS POSICIONES
    imagenJuli.setOrigin(50.f, 50.f);
    imagenLiz.setOrigin(50.f, 50.f);
    imagenJuani.setOrigin(50.f, 50.f);

    /// POSICIONAMOS LAS IMAGENES
    imagenJuli.setPosition(250, 500);
    imagenLiz.setPosition(400, 500);
    imagenJuani.setPosition(550, 500);

    /// LE DAMOS LA TEXTURA DE LA IMAGEN
    imagenJuli.setTexture(&texJuli);
    imagenLiz.setTexture(&texLiz);
    imagenJuani.setTexture(&texJuani);

    moveClock.restart();
    soundClock.restart();
}
bool menuInicio::gameStarted=false;
void menuInicio::draw(sf::RenderWindow& window)
{
    // Mostrar pantalla de ingreso de nombre
    if (ingresandoNombre)
    {
        window.draw(imagen);
        window.draw(cajaEntrada);
        window.draw(textoSolicitudNombre);
        textoNombreActual.setString(nombreJugador + "_"); // Añadido cursor
        window.draw(textoNombreActual);
        return;
    }


    if (menuControles.getIsOpen())
    {
        menuControles.draw(window);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            menuControles.handleClick(sf::Mouse::getPosition(window));
        }
        return;
    }

    window.draw(imagen);
    for(int i = 0; i < 5; i++)
    {
        window.draw(menu[i]);
    }

    window.draw(imagenJuli);
    window.draw(imagenLiz);
    window.draw(imagenJuani);

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool mouseInteracted = false;

    for(int i = 0; i < 3; i++)
    {
        if(menu[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            if(Opciones != i)
            {
                menu[Opciones].setFillColor(sf::Color::White);
                menu[Opciones].setStyle(sf::Text::Regular);

                Opciones = i;
                menu[i].setFillColor(sf::Color(143, 159, 97));
                menu[i].setStyle(sf::Text::Underlined);

                if (soundClock.getElapsedTime().asMilliseconds() > 100)
                {
                    sonidoInicio.play();
                    soundClock.restart();
                }
            }
            mouseInteracted = true;
        }

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
                // Simplemente marcamos que se seleccionó continuar partida
                seleccionoContinuar = true;
            }
            break;
        }
    }

    movimiento();
    VinculoLinks(window);
}

void menuInicio::manejarEntradaNombre(sf::Event evento)
{
    if (!ingresandoNombre) return;

    if (evento.type == sf::Event::TextEntered)
    {
        // Solo procesar caracteres imprimibles y teclas especiales
        if (evento.text.unicode == '\b')
        {
            if (!nombreJugador.empty())
            {
                nombreJugador.pop_back();
            }
        }
        else if (evento.text.unicode == '\r' || evento.text.unicode == '\n')
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
                 nombreJugador.length() < 20)
        {
            nombreJugador += static_cast<char>(evento.text.unicode);
        }
    }

    // Permitir cancelar con Escape
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape)
    {
        ingresandoNombre = false;
        nombreJugador = "";
    }
}

void menuInicio::movimiento() {
    if (ingresandoNombre) return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if (moveClock.getElapsedTime().asMilliseconds() > 200) {
            menu[Opciones].setFillColor(sf::Color::White);
            menu[Opciones].setStyle(sf::Text::Regular);
            Opciones = (Opciones + 1) % 3;
            menu[Opciones].setFillColor(sf::Color(143, 159, 97));
            menu[Opciones].setStyle(sf::Text::Underlined);
            sonidoInicio.play();
            moveClock.restart();
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if (moveClock.getElapsedTime().asMilliseconds() > 200) {
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


bool menuInicio::IniciarJuego(sf::RenderWindow& window)
{
    if (!menuInicio::gameStarted)
    {
        if (Opciones == 0)   // Si seleccionó "INICIAR JUEGO NUEVO"
        {
            ingresandoNombre = true; // Esto activa el modo de entrada de nombre
            nombreJugador = ""; // Limpiar el nombre al iniciar
            estadoDelJuego.nuevaPartida(); // Reiniciar el estado de la partida
            return false;
        }
    }
    return false;
}

void menuInicio::VinculoLinks(sf::RenderWindow& window)
{
    if (ingresandoNombre) return;  // No procesar links durante ingreso de nombre

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
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


