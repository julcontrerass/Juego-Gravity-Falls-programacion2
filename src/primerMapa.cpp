#include "../primerMapa.h"
#include <stdexcept>
#include <cmath>
#include <iostream>


PrimerMapa::PrimerMapa()
{
    ///INICIAMOS LAS ZONAS BLOQUEADAS QUE TIENEN LOS MAPAS
    /// EL .push_back(x,y,ancho,altura) SIREVE PARA AGREGAR UN NUEVO DATO AL FINAL DE UN VECTOR
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 1367, 147));
    zonasBloqueadas.push_back(sf::FloatRect(600, 0, 185, 600));
    zonasBloqueadas.push_back(sf::FloatRect(0, 550, 240, 75));
    zonasBloqueadas.push_back(sf::FloatRect(345, 550, 463, 75));
    zonasBloqueadas.push_back(sf::FloatRect(240, 585, 463, 75));
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 40, 600));
    zonasBloqueadas.push_back(sf::FloatRect(140, 0, 40, 600));
    zonasBloqueadas.push_back(sf::FloatRect(195,525, 50, 48));
    zonasBloqueadas.push_back(sf::FloatRect(560,500, 50, 48));
    zonasBloqueadas.push_back(sf::FloatRect(510,520, 50, 48));
    zonasBloqueadas.push_back(sf::FloatRect(195,0, 68, 180));
    zonasBloqueadas.push_back(sf::FloatRect(344,0, 50, 180));
    zonasBloqueadas.push_back(sf::FloatRect(488,0, 115, 168));
    zonasBloqueadas.push_back(sf::FloatRect(550,360, 115, 70));
    zonasBloqueadas.push_back(sf::FloatRect(265,0, 60,220));


    ///CREAMOS LOS VINCULOS CON LA MUSICA Y LAS IMAGENES
    if (!musicaJuego.openFromFile("./Imagenes/Sonidos/musicaFondoJuego.wav"))
    {
        throw std::runtime_error("Error al cargar el sonido de inicio");
    }

    musicaJuego.setLoop(true);
    musicaJuego.setVolume(20);
    // Cargar la textura de fondo
    if (!tex.loadFromFile("./Imagenes/Mapas/PrimerMapa.png"))
    {
        throw std::runtime_error("No se pudo cargar la textura del primer mapa.");
    }
    // Cargar la textura de los items sobre el personaje
    if (!tex2.loadFromFile("./Imagenes/Mapas/ItemsPrimMapa.png"))
    {
        throw std::runtime_error("No se pudo cargar la textura de los items del mapa.");
    }
    imagen.setTexture(tex);
    imagen2.setTexture(tex2);


    /// CREAMOS LA VISTA QUE ACTUA COMO CAMAPA
    camera.setSize(sf::Vector2f(800, 600));

    dipper.setPosition(sf::Vector2f(400, 275));
    stan.setPosition(sf::Vector2f(120, 450));
    wendy.setPosition(sf::Vector2f(366, 230));
    soos.setPosition(sf::Vector2f(420, 230));
    mabbel.setPosition(sf::Vector2f(500,230));


    dipper.setInitialTextureRect(0);  // 0 para abajo, 1 para izquierda, 2 para derecha, 3 para arriba

}
bool PrimerMapa::dialogoIniciado = false;

void PrimerMapa::update(sf::RenderWindow &window)
{
    dipper.update();
    stan.update();
    sf::Vector2f oldPosition = dipper.getPosition();
    sf::Vector2f newPosition = dipper.getPosition();
    sf::FloatRect newBounds = dipper.getBounds();
    newBounds.left = newPosition.x - newBounds.width / 2;
    newBounds.top = newPosition.y - newBounds.height / 2;

    bool collision = false;
    sf::Vector2f correction(0.f, 0.f);

    for (const auto& zona : zonasBloqueadas)
    {
        if (newBounds.intersects(zona))
        {
            collision = true;

            // Calcula la corrección necesaria en cada eje
            if (oldPosition.x < zona.left && newPosition.x + newBounds.width / 2 > zona.left)
                correction.x = zona.left - (newPosition.x + newBounds.width / 2);
            else if (oldPosition.x > zona.left + zona.width && newPosition.x - newBounds.width / 2 < zona.left + zona.width)
                correction.x = (zona.left + zona.width) - (newPosition.x - newBounds.width / 2);

            if (oldPosition.y < zona.top && newPosition.y + newBounds.height / 2 > zona.top)
                correction.y = zona.top - (newPosition.y + newBounds.height / 2);
            else if (oldPosition.y > zona.top + zona.height && newPosition.y - newBounds.height / 2 < zona.top + zona.height)
                correction.y = (zona.top + zona.height) - (newPosition.y - newBounds.height / 2);
        }
    }

    if (collision)
    {
        // Aplica la corrección, priorizando el eje con mayor corrección
        if (std::abs(correction.x) > std::abs(correction.y))
            newPosition.x += correction.x;
        else
            newPosition.y += correction.y;

        dipper.setPosition(newPosition);
    }


    // Actualizar la cámara
    camera.setCenter(dipper.getPosition());

    /// Limitamos la cámara a los bordes del mapa
    sf::Vector2f cameraCenter = camera.getCenter();
    cameraCenter.x = std::max(400.f, std::min(cameraCenter.x, static_cast<float>(tex.getSize().x) - 400.f));
    cameraCenter.y = std::max(300.f, std::min(cameraCenter.y, static_cast<float>(tex.getSize().y) - 300.f));
    camera.setCenter(cameraCenter);


    /// vemos si el jugador está cerca de Stan y el diálogo no está completado para inicializarlo
     sf::Vector2f dipperPos = dipper.getPosition();
    sf::Vector2f stanPos = stan.getPosition();
    float distancia = std::sqrt(
                          std::pow(dipperPos.x - stanPos.x, 2) +
                          std::pow(dipperPos.y - stanPos.y, 2)
                      );

    // Modifica la lógica del diálogo
    const float DISTANCIA_DIALOGO = 100.0f; // Ajusta este valor según necesites

    if (distancia < DISTANCIA_DIALOGO) {
        if (!dialogoIniciado || (estadoDelJuego.tresLibros() && stan.dialogoPermanentementeCompletado())) {
            stan.iniciarDialogo();
            dialogoIniciado = true;
        }
    } else {
        dialogoIniciado = false;
    }

    // Actualizar el diálogo con el tiempo transcurrido
    stan.actualizarDialogo(_relojDialogo.restart().asSeconds());

    //MOVIMIENTOS

    static bool movimientoStanIniciado = false;
    if (!movimientoStanIniciado && stan.segundoDialogoCompletado() && estadoDelJuego.tresLibros())
    {
        std::cout << "Iniciando movimiento automático de Stan después del segundo diálogo" << std::endl;
        stan.iniciarMovimientoAutomatico();
        movimientoStanIniciado = true;
    }

    if (stan.dialogoCompletado())
    {
        estadoDelJuego.modificarEstadosItems("cuchillo");
    }
}


void PrimerMapa::draw(sf::RenderWindow &window)
{
    sf::View defaultView = window.getDefaultView();

    window.setView(camera);
    window.draw(imagen);
    if (!estadoDelJuego.getEstadoPersonajes("stan"))
    {
        window.draw(stan);
    }
    window.draw(dipper);
    window.draw(imagen2);

    if(estadoDelJuego.getEstadoPersonajes("wendy"))
    {
        window.draw(wendy);
    }
    if(estadoDelJuego.getEstadoPersonajes("soos"))
    {
        window.draw(soos);
    }

    if(estadoDelJuego.getEstadoPersonajes("mabbel"))
    {
        window.draw(mabbel);
    }


    window.setView(defaultView);
    mochila.draw(window);

}

void PrimerMapa::setPersonajePosition(const sf::Vector2f& position)
{
    dipper.setPosition(position);
}
sf::Vector2f PrimerMapa::getDipperPosition() const
{
    return dipper.getPosition();
}
