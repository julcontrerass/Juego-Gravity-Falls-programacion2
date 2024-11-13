#include <SFML/Graphics.hpp>
#include "inicio.h"
#include "menu.h"
#include "estadoDeMapas.h"
#include "gameOver.h"
#include "estadoDelJuego.h"
#include "continuarPartida.h"
#include "bill.h"
#include "pantallaGanador.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Juego Gravity Falls");
    window.setFramerateLimit(60);

    // Estados del juego
    Inicio inicio;
    sf::Music musicaFondo;
    if (!musicaFondo.openFromFile("./Imagenes/Sonidos/musica.wav"))
    {
        throw std::runtime_error("Error al cargar la m·sica de inicio");
    }
    musicaFondo.setVolume(20);
    musicaFondo.setLoop(true);
    musicaFondo.play();

    menuInicio menu(musicaFondo);
    EstadoDeMapas estadoJuego;
    GameOver gameOver;
    estadoDelJuego estadoDelJuego;
    ContinuarPartida continuarPartida;
    Bill bill;
    PantallaGanador pantallaGanador;

    enum class EstadoJuego
    {
        INICIO,
        MENU,
        SELECCION_PARTIDA,
        JUGAR,
        FIN_JUEGO,
        PARTIDA_GANADA
    };

    EstadoJuego estadoActual = EstadoJuego::INICIO;
    bool seleccionoNuevaPartida = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            switch(estadoActual)
            {
            case EstadoJuego::INICIO:
                inicio.handleEvent(event, window);
                if (inicio.shouldStartGame())
                {
                    estadoActual = EstadoJuego::MENU;
                }
                break;

            case EstadoJuego::MENU:
                menu.manejarEntradaNombre(event);  // Solo llamar una vez
                if (menuInicio::gameStarted)  // Si gameStarted es true (despuΘs de presionar Enter)
                {
                    estadoActual = EstadoJuego::JUGAR;
                    estadoJuego.inicioJuego(true);
                    menuInicio::gameStarted = false;  // Resetear el flag
                }
                menu.draw(window);
                break;

            case EstadoJuego::SELECCION_PARTIDA:
                continuarPartida.draw(window);
                if (continuarPartida.debeIniciarJuego())
                {
                    estadoActual = EstadoJuego::JUGAR;
                    estadoJuego.inicioJuego(false);
                    continuarPartida.reiniciarInicioJuego();
                    menuInicio::gameStarted = true;
                }
                break;

            case EstadoJuego::JUGAR:
                estadoJuego.handleEvent(event, window);
                break;

            case EstadoJuego::FIN_JUEGO:
                if (event.type == sf::Event::KeyPressed &&
                        event.key.code == sf::Keyboard::Space)
                {
                    estadoActual = EstadoJuego::MENU;
                }
                break;
            case EstadoJuego::PARTIDA_GANADA:
                if (event.type == sf::Event::KeyPressed &&
                        event.key.code == sf::Keyboard::Space)
                {
                    estadoActual = EstadoJuego::MENU;
                }
                break;
            }
            continuarPartida.cargarPartidas();
;        }

        window.clear();

        // Verificar si se seleccion≤ continuar partida en el men·
        if (estadoActual == EstadoJuego::MENU && menu.seleccionoContinuar)
        {
            estadoActual = EstadoJuego::SELECCION_PARTIDA;
            continuarPartida.open();
            menu.seleccionoContinuar = false;
        }

        // Update y Draw seg·n el estado actual
        switch(estadoActual)
        {
        case EstadoJuego::INICIO:
            inicio.update(window);
            inicio.draw(window);
            break;

        case EstadoJuego::MENU:
            menu.draw(window);
            break;

        case EstadoJuego::SELECCION_PARTIDA:
            continuarPartida.draw(window);
            break;

        case EstadoJuego::JUGAR:
            if (estadoDelJuego.getVidasDipper() == 0)
            {
                estadoActual = EstadoJuego::FIN_JUEGO;
            }
            if(estadoDelJuego.getVidasEnemigos("bill") == 0){
                estadoActual=EstadoJuego::PARTIDA_GANADA;
            }
            if (estadoJuego.volverAlMenu)
            {
                estadoActual = EstadoJuego::MENU;
                menuInicio::gameStarted = false;
                estadoJuego.volverAlMenu = false;

            }
            estadoJuego.update(window);
            estadoJuego.draw(window);
            musicaFondo.stop();
            break;

        case EstadoJuego::FIN_JUEGO:
            gameOver.draw(window);
            break;
        case EstadoJuego::PARTIDA_GANADA:
            pantallaGanador.draw(window);
            break;
        }


        window.display();
    }

    return 0;
}
