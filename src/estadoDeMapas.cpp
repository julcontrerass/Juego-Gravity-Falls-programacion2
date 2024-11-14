#include "../estadoDeMapas.h"
#include <iostream>
#include "../stan.h"

EstadoDeMapas::EstadoDeMapas() : timer(0), click(false), volverAlMenu(false)
{
    if (!musicaFondo.openFromFile("./Imagenes/Sonidos/musicaFondoJuego.wav"))
    {
        throw std::runtime_error("Error al cargar el sonido de inicio");
    }
    musicaFondo.setVolume(5);
    musicaFondo.setLoop(true);
}

void EstadoDeMapas::draw(sf::RenderWindow& window)
{
    switch (estadoDelJuego.getMapaActual())
    {
    case 0:
        primerMapa.update(window);
        primerMapa.draw(window);
        break;
    case 1:
        segundoMapa.update(window);
        segundoMapa.draw(window);
        break;
    case 2:
        tercerMapa.update(window);
        tercerMapa.draw(window);
        break;
    case 3:
        cuartoMapa.update(window);
        cuartoMapa.draw(window);
        break;
    case 4:
        quintoMapa.update(window);
        quintoMapa.draw(window);
        break;
    case 5:
        sextoMapa.update(window);
        sextoMapa.draw(window);
        break;
    case 6:
        septimoMapa.update(window);
        septimoMapa.draw(window);
        break;
    case 7:
        octavoMapa.update(window);
        octavoMapa.draw(window);
        break;
    case 8:
        novenoMapa.update(window);
        novenoMapa.draw(window);
        break;
    case 9:
        mapaFinal.update(window);
        mapaFinal.draw(window);
        break;
    }
}

void EstadoDeMapas::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::Closed)
    {
        window.close();
    }
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        volverAlMenu = true;
        musicaFondo.stop();
        inicioJuego(false);
    }
}

void EstadoDeMapas::update(sf::RenderWindow& window)
{
    if(timer>0)
    {
        timer--;
    }

    if (timer == 0)
    {
        click = false;
    }
    cambiarMapa(window);
}

void EstadoDeMapas::cambiarMapa(sf::RenderWindow &window)
{
    ///CREAMOS LOS CAMBIOS DE MAPA DEL PRIMER MAPA
    sf::Vector2f dipperPosprimerMapa = primerMapa.getDipperPosition();

    ///segundo mapa
    if (!click && estadoDelJuego.getMapaActual() == 0 && dipperPosprimerMapa.x >= 250 && dipperPosprimerMapa.x <= 400 && dipperPosprimerMapa.y >= 483 && dipperPosprimerMapa.y <= 600)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            estadoDelJuego.modificarMapa(1);
            segundoMapa.setPersonajePosition(sf::Vector2f(640, 670));  // Posición inicial en el segundo mapa
            dipper.setInitialTextureRect(0);
            timer = 20;
            click = true;
        }
    }
    /// octavo mapa
    if (!click && estadoDelJuego.getMapaActual() == 0 && dipperPosprimerMapa.x >= 170 && dipperPosprimerMapa.x <= 280 && dipperPosprimerMapa.y >= 0 && dipperPosprimerMapa.y <= 250)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            estadoDelJuego.modificarMapa(7);
            octavoMapa.setPersonajePosition(sf::Vector2f(350, 555));  // Posición inicial en el octavo mapa
            timer = 20;
            click = true;
        }
    }
    ///CREAMOS LOS CAMBIOS DE MAPA DEL SEGUNDO MAPA
    sf::Vector2f dipperPosSegundoMapa = segundoMapa.getDipperPosition();

    //primer mapa
    if (!click && estadoDelJuego.getMapaActual() == 1 && dipperPosSegundoMapa.x >= 579 && dipperPosSegundoMapa.x <= 712 && dipperPosSegundoMapa.y >= 570 && dipperPosSegundoMapa.y <= 672)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            estadoDelJuego.modificarMapa(0);
            primerMapa.setPersonajePosition(sf::Vector2f(300, 550));  // Posición inicial en el segundo mapa
            timer = 20;
            click = true;
            dipper.setInitialTextureRect(3);
        }
    }
    // tercer mapa
    if (!click && estadoDelJuego.getMapaActual() == 1 && dipperPosSegundoMapa.x >= 1330 && dipperPosSegundoMapa.x <= 1500 && dipperPosSegundoMapa.y >= 0 && dipperPosSegundoMapa.y <= 219)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space ))
        {
            estadoDelJuego.modificarMapa(2);
            tercerMapa.setPersonajePosition(sf::Vector2f(1330, 930));  // Posición inicial en el octavo mapa
            dipper.setInitialTextureRect(3);
            timer = 20;
            click = true;
            dipper.setInitialTextureRect(3);
        }
    }
    // cuarto mapa
    if (!click && estadoDelJuego.getMapaActual() == 1 && dipperPosSegundoMapa.x >= 0 && dipperPosSegundoMapa.x <= 109 && dipperPosSegundoMapa.y >= 866 && dipperPosSegundoMapa.y <= 979)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            estadoDelJuego.modificarMapa(3);
            cuartoMapa.setPersonajePosition(sf::Vector2f(1400, 860));  // Posición inicial en el octavo mapa
            dipper.setInitialTextureRect(1);
            timer = 20;
            click = true;
        }
    }
    ///CREAMOS LOS CAMBIOS DE MAPA DEL TERCER MAPA
    sf::Vector2f dipperPosTercerMapa = tercerMapa.getDipperPosition();

    //segundo mapa
    if (!click && estadoDelJuego.getMapaActual() == 2 && dipperPosTercerMapa.x >= 1300 && dipperPosTercerMapa.x <= 1400 && dipperPosTercerMapa.y >= 900 && dipperPosTercerMapa.y <= 2000)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            estadoDelJuego.modificarMapa(1);
            segundoMapa.setPersonajePosition(sf::Vector2f(1420, 200));  // Posición inicial en el segundo mapa
            timer = 20;
            click = true;
        }
    }

    // sexto mapa
    if (!click && estadoDelJuego.getMapaActual() == 2 && dipperPosTercerMapa.x >= 1434 && dipperPosTercerMapa.x <= 1492 && dipperPosTercerMapa.y >= 213 && dipperPosTercerMapa.y <= 280)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            estadoDelJuego.modificarMapa(5);
            sextoMapa.setPersonajePosition(sf::Vector2f(173, 780));  // Posición inicial en el octavo mapa
            timer = 20;
            click = true;
        }
    }

    ///CREAMOS LOS CAMBIOS DE MAPA DEL CUARTO MAPA
    sf::Vector2f dipperPosCuartoMapa = cuartoMapa.getDipperPosition();
    //segundo mapa
    if (!click && estadoDelJuego.getMapaActual() == 3 && dipperPosCuartoMapa.x >= 1400 && dipperPosCuartoMapa.x <= 1500 && dipperPosCuartoMapa.y >= 800 && dipperPosCuartoMapa.y <= 900)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            estadoDelJuego.modificarMapa(1);
            segundoMapa.setPersonajePosition(sf::Vector2f(95, 950));  // Posición inicial en el segundo mapa
            timer = 20;
            click = true;
        }
    }
    // quinto mapa
    if (!click && estadoDelJuego.getMapaActual() == 3 && dipperPosCuartoMapa.x >= 1161 && dipperPosCuartoMapa.x <= 1234 && dipperPosCuartoMapa.y >= 0 && dipperPosCuartoMapa.y <= 96)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            estadoDelJuego.modificarMapa(4);
            quintoMapa.setPersonajePosition(sf::Vector2f(400, 600));  // Posición inicial en el octavo mapa
            timer = 20;
            click = true;
        }
    }
    ///CREAMOS LOS CAMBIOS DE MAPA DEL QUINTO MAPA
    sf::Vector2f dipperPosQuintoMapa = quintoMapa.getDipperPosition();
    //cuarto mapa
    if (!click && estadoDelJuego.getMapaActual() == 4 && dipperPosQuintoMapa.x >= 297 && dipperPosQuintoMapa.x <= 515 && dipperPosQuintoMapa.y >= 523 && dipperPosQuintoMapa.y <= 600)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            estadoDelJuego.modificarMapa(3);
            cuartoMapa.setPersonajePosition(sf::Vector2f(1182, 100));  // Posición inicial en el segundo mapa
            timer = 20;
            click = true;
        }
    }
    // noveno mapa
    if (!click && estadoDelJuego.getMapaActual() == 4 && dipperPosQuintoMapa.x >= 0 && dipperPosQuintoMapa.x <= 77 && dipperPosQuintoMapa.y >= 271 && dipperPosQuintoMapa.y <= 400)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            estadoDelJuego.modificarMapa(8);
            novenoMapa.setPersonajePosition(sf::Vector2f(1160, 300));  // Posición inicial en el octavo mapa
            timer = 20;
            click = true;
        }
    }

    ///CREAMOS LOS CAMBIOS DE MAPA DEL SEXTO MAPA
    sf::Vector2f dipperPosSextoMapa = sextoMapa.getDipperPosition();
    //tercer mapa
    if (!click && estadoDelJuego.getMapaActual() == 5 && dipperPosSextoMapa.x >= 130 && dipperPosSextoMapa.x <= 190 && dipperPosSextoMapa.y >= 725 && dipperPosSextoMapa.y <= 800)
    {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            estadoDelJuego.modificarMapa(2);
            tercerMapa.setPersonajePosition(sf::Vector2f(1434, 237));  // Posición inicial en el segundo mapa
            timer = 20;
            click = true;
        }
    }
    // septimo mapa
    if (!click && estadoDelJuego.getMapaActual() == 5 && dipperPosSextoMapa.x >= 1353 && dipperPosSextoMapa.x <= 1434 && dipperPosSextoMapa.y >= 222 && dipperPosSextoMapa.y <= 300)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            estadoDelJuego.modificarMapa(6);
            septimoMapa.setPersonajePosition(sf::Vector2f(708, 274));  // Posición inicial en el octavo mapa
            timer = 20;
            click = true;
        }
    }

    ///CREAMOS LOS CAMBIOS DE MAPA DEL SEPTIMO MAPA
    sf::Vector2f dipperPosSeptimoMapa = septimoMapa.getDipperPosition();
    //segundo mapa
    if (!click && estadoDelJuego.getMapaActual() == 6 && dipperPosSeptimoMapa.x >= 651 && dipperPosSeptimoMapa.x <= 800 && dipperPosSeptimoMapa.y >= 220 && dipperPosSeptimoMapa.y <= 400)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            estadoDelJuego.modificarMapa(5);
            sextoMapa.setPersonajePosition(sf::Vector2f(1373, 243));  // Posición inicial en el segundo mapa
            timer = 20;
            click = true;
        }
    }

    ///CREAMOS LOS CAMBIOS DE MAPA DEL OCTAVO MAPA
    sf::Vector2f dipperPosOctavoMapa = octavoMapa.getDipperPosition();
    //primer mapa
    if (!click && estadoDelJuego.getMapaActual() == 7 && dipperPosOctavoMapa.x >= 0 && dipperPosOctavoMapa.x <= 800 && dipperPosOctavoMapa.y >= 530 && dipperPosOctavoMapa.y <= 600)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            estadoDelJuego.modificarMapa(0);
            primerMapa.setPersonajePosition(sf::Vector2f(196, 137));  // Posición inicial en el segundo mapa
            timer = 20;
            click = true;
        }
    }
    //mapa final
    if ( estadoDelJuego.getEstadoPersonajes("stan") && !click && estadoDelJuego.getMapaActual() == 7 && dipperPosOctavoMapa.x >= 556 && dipperPosOctavoMapa.x <= 724 && dipperPosOctavoMapa.y >= 406 && dipperPosOctavoMapa.y <= 510)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            estadoDelJuego.modificarMapa(9);
            mapaFinal.setPersonajePosition(sf::Vector2f(368, 475));  // Posición inicial en el segundo mapa
            timer = 20;
            click = true;
        }
    }
    ///CREAMOS LOS CAMBIOS DE MAPA DEL NOVENO MAPA
    sf::Vector2f dipperPosNovenoMapa = novenoMapa.getDipperPosition();
    //quinto mapa
    if ( !click && estadoDelJuego.getMapaActual() == 8 && dipperPosNovenoMapa.x >= 1102 && dipperPosNovenoMapa.x <= 1220 && dipperPosNovenoMapa.y >= 183 && dipperPosNovenoMapa.y <= 273)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            estadoDelJuego.modificarMapa(4);
            quintoMapa.setPersonajePosition(sf::Vector2f(30, 350));  // Posición inicial en el segundo mapa
            timer = 20;
            click = true;
        }
    }

}

void EstadoDeMapas::inicioJuego(bool active)
{
    iniciado = active;
    if (iniciado)
    {
        musicaFondo.play();  // La música comienza aquí
    }
    else
    {
        musicaFondo.stop();
    }
}

//void EstadoDeMapas::modificarMapa(){
//    mapaActual = 0;
//}

