#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "primerMapa.h"
#include "segundoMapa.h"
#include "tercerMapa.h"
#include "cuartoMapa.h"
#include "quintoMapa.h"
#include "sextoMapa.h"
#include "septimoMapa.h"
#include "octavoMapa.h"
#include "novenoMapa.h"
#include "mapaFinal.h"
#include "dipper.h"
#include "estadoDelJuego.h"

// Clase que maneja el estado de los mapas en el juego
class EstadoDeMapas {
private:
    PrimerMapa primerMapa;
    SegundoMapa segundoMapa;
    TercerMapa tercerMapa;
    CuartoMapa cuartoMapa;
    QuintoMapa quintoMapa;
    SextoMapa sextoMapa;
    SeptimoMapa septimoMapa;
    OctavoMapa octavoMapa;
    NovenoMapa novenoMapa;
    MapaFinal mapaFinal;
    Dipper dipper;
    bool active;
    int timer;
    bool click;
    sf::Music musicaFondo;
    bool iniciado;
    estadoDelJuego estadoDelJuego;

public:
    EstadoDeMapas();
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void inicioJuego(bool iniciado);
    void cambiarMapa(sf::RenderWindow& window);
    bool volverAlMenu;


};
