#include "../octavoMapa.h"
#include <stdexcept>
#include <cmath>

OctavoMapa::OctavoMapa()
{
    // Inicializamos las zonas bloqueadas (árboles y agua)
    // .push_back(x,y,ancho,altura) sirve para agregar un nuevo dato al final de un vector
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 36, 600));
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 800, 240));
    zonasBloqueadas.push_back(sf::FloatRect(770, 0, 45, 600));
    zonasBloqueadas.push_back(sf::FloatRect(364, 300, 72,5));
    zonasBloqueadas.push_back(sf::FloatRect(0, 640, 807,11));

    // Cargar la textura de fondo
    if (!tex.loadFromFile("./Imagenes/Mapas/OctavoMapa.png"))
    {
        throw std::runtime_error("No se pudo cargar la textura del primer mapa.");
    }
    if (!tex2.loadFromFile("./Imagenes/Mapas/ItemsOctavoMapa.png"))
    {
        throw std::runtime_error("No se pudo cargar la textura del primer mapa.");
    }

    imagen.setTexture(tex);
    imagen2.setTexture(tex2);

    stan.setPosition(sf::Vector2f(148,450));

    // Crear una vista que actúa como cámara
    camera.setSize(sf::Vector2f(800, 600));
}


void OctavoMapa::update(sf::RenderWindow &window)
{
    dipper.update();
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

    // Limitar la cámara a los bordes del mapa
    sf::Vector2f cameraCenter = camera.getCenter();
    cameraCenter.x = std::max(400.f, std::min(cameraCenter.x, static_cast<float>(tex.getSize().x) - 400.f));
    cameraCenter.y = std::max(300.f, std::min(cameraCenter.y, static_cast<float>(tex.getSize().y) - 300.f));
    camera.setCenter(cameraCenter);

    if (estadoDelJuego.getEstadoPersonajes("stan"))
    {
        sf::Vector2f dipperPos = dipper.getPosition();
        sf::Vector2f stanPos = stan.getPosition();
        float distancia = std::sqrt(
                              std::pow(dipperPos.x - stanPos.x, 2) +
                              std::pow(dipperPos.y - stanPos.y, 2)
                          );

        if (distancia < 200)
        {
            stan.iniciarDialogo();
        }
    }

}


void OctavoMapa::draw(sf::RenderWindow &window)
{
    sf::View defaultView = window.getDefaultView();

    window.setView(camera);
    window.draw(imagen);
    window.draw(dipper);
    window.draw(imagen2);
    if(estadoDelJuego.getEstadoPersonajes("stan"))
    {
        window.draw(stan);
    }

    window.setView(defaultView);
    mochila.draw(window);
}

void OctavoMapa::setPersonajePosition(const sf::Vector2f& position)
{
    dipper.setPosition(position);
}
sf::Vector2f OctavoMapa::getDipperPosition() const
{
    return dipper.getPosition();
}


