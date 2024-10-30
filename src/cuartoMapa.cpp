#include "cuartoMapa.h"
#include "../segundoMapa.h"
#include "../quintoMapa.h"

#include <stdexcept>

CuartoMapa::CuartoMapa()

{
    // Inicializamos las zonas bloqueadas (árboles y agua)
    // .push_back(x,y,ancho,altura) sirve para agregar un nuevo dato al final de un vector
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 1147, 100));
    zonasBloqueadas.push_back(sf::FloatRect(734, 100, 250, 63));
    zonasBloqueadas.push_back(sf::FloatRect(1140, 0, 89, 33));
    zonasBloqueadas.push_back(sf::FloatRect(1229, 0, 317, 117));
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 102, 1020));
    zonasBloqueadas.push_back(sf::FloatRect(1400, 0, 155, 780));
    zonasBloqueadas.push_back(sf::FloatRect(1330, 350, 65, 300));
    zonasBloqueadas.push_back(sf::FloatRect(330, 370, 160, 95));
    zonasBloqueadas.push_back(sf::FloatRect(1470, 767, 51, 200));
    zonasBloqueadas.push_back(sf::FloatRect(1444, 900, 102, 45));
    zonasBloqueadas.push_back(sf::FloatRect(0, 1000, 1546, 111));
    zonasBloqueadas.push_back(sf::FloatRect(320, 930, 200, 65));
    zonasBloqueadas.push_back(sf::FloatRect(832, 930, 700, 80));
    zonasBloqueadas.push_back(sf::FloatRect(300, 670, 400, 80));
    zonasBloqueadas.push_back(sf::FloatRect(700, 480, 129, 300));
    zonasBloqueadas.push_back(sf::FloatRect(812, 357, 210, 330));
    zonasBloqueadas.push_back(sf::FloatRect(694, 475, 169, 205));
    zonasBloqueadas.push_back(sf::FloatRect(1000, 410, 263, 230));
    zonasBloqueadas.push_back(sf::FloatRect(833, 687, 79, 100));


    // Cargar la textura de fondo
    if (!tex.loadFromFile("./Imagenes/Mapas/CuartoMapa.png"))
    {
        throw std::runtime_error("No se pudo cargar la textura del mapa.");
    }

    imagen.setTexture(tex);

    // Crear una vista que actúa como cámara
    camera.setSize(sf::Vector2f(800, 600));

    pocion.setPosition(sf::Vector2f(530,525));
}

void CuartoMapa::update(sf::RenderWindow &window)
{
    dipper.update();
    handleCollisions();
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


}


void CuartoMapa::draw(sf::RenderWindow &window)
{
    sf::View defaultView = window.getDefaultView();

    window.setView(camera);
    window.draw(imagen);
    window.draw(dipper);

    if(!pocion.pocionesRecolectadas(1)){
        window.draw(pocion);
    }

    window.setView(defaultView);
    mochila.draw(window);

}

void CuartoMapa::setPersonajePosition(const sf::Vector2f& position)
{
    dipper.setPosition(position);
}
sf::Vector2f CuartoMapa::getDipperPosition() const {
    return dipper.getPosition();
}

void CuartoMapa::handleCollisions()
{
    if (dipper.isCollision(pocion))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            pocion.recolectado(1);
        }
    }
}

