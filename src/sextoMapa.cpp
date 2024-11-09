#include "../sextoMapa.h"
#include "../tercerMapa.h"
#include "../SeptimoMapa.h"

#include <stdexcept>

SextoMapa::SextoMapa()
{
    // Inicializamos las zonas bloqueadas (árboles y agua)
    // .push_back(x,y,ancho,altura) sirve para agregar un nuevo dato al final de un vector
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 652, 147));
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 137, 1024));
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 1536, 77));
    zonasBloqueadas.push_back(sf::FloatRect(1434, 0, 102, 1024));
    zonasBloqueadas.push_back(sf::FloatRect(1100, 440,  419, 283));
    zonasBloqueadas.push_back(sf::FloatRect(1370, 645, 166, 363));
    zonasBloqueadas.push_back(sf::FloatRect(982, 950, 554, 84));
    zonasBloqueadas.push_back(sf::FloatRect(0, 1020, 1536, 24));
    zonasBloqueadas.push_back(sf::FloatRect(0, 890, 295, 141));
    zonasBloqueadas.push_back(sf::FloatRect(369, 430, 485, 114));
    zonasBloqueadas.push_back(sf::FloatRect(559, 430, 294, 497));
    zonasBloqueadas.push_back(sf::FloatRect(439, 530, 121, 143));
    zonasBloqueadas.push_back(sf::FloatRect(792, 370, 65, 65));
    zonasBloqueadas.push_back(sf::FloatRect(865, 817, 50, 104));
    zonasBloqueadas.push_back(sf::FloatRect(360, 895, 292,30));
    zonasBloqueadas.push_back(sf::FloatRect(360, 922, 207,200));
    zonasBloqueadas.push_back(sf::FloatRect(504, 102, 91,95));
    zonasBloqueadas.push_back(sf::FloatRect(175, 700, 33,20));
    zonasBloqueadas.push_back(sf::FloatRect(175, 818, 33,60));
    zonasBloqueadas.push_back(sf::FloatRect(1358, 184, 50,20));
    zonasBloqueadas.push_back(sf::FloatRect(1358, 320, 60,20));




    // Cargar la textura de fondo
    if (!tex.loadFromFile("./Imagenes/Mapas/SextoMapa.png"))
    {
        throw std::runtime_error("No se pudo cargar la textura del primer mapa.");
    }

    imagen.setTexture(tex);

    // Crear una vista que actúa como cámara
    camera.setSize(sf::Vector2f(800, 600));
}

void SextoMapa::update(sf::RenderWindow &window)
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


}


void SextoMapa::draw(sf::RenderWindow &window)
{
    defaultView = window.getDefaultView();

    window.setView(camera);
    window.draw(imagen);
    window.draw(dipper);

    window.setView(defaultView);
    mochila.draw(window);

}

void SextoMapa::setPersonajePosition(const sf::Vector2f& position)
{
    dipper.setPosition(position);
}

sf::Vector2f SextoMapa::getDipperPosition() const {
    return dipper.getPosition();
}


