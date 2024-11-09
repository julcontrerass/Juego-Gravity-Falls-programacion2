#include "../segundoMapa.h"
#include "../primerMapa.h"
#include "../cuartoMapa.h"
#include "../tercerMapa.h"
#include <stdexcept>

SegundoMapa::SegundoMapa()
{
    // Inicializamos las zonas bloqueadas (árboles y agua)
    // .push_back(x,y,ancho,altura) sirve para agregar un nuevo dato al final de un vector
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 1367, 147));
    zonasBloqueadas.push_back(sf::FloatRect(1133, 0, 95,848));
    zonasBloqueadas.push_back(sf::FloatRect(1360, 0, 97,170));
    zonasBloqueadas.push_back(sf::FloatRect(1455, 0, 90,200));
    zonasBloqueadas.push_back(sf::FloatRect(1218, 0, 135, 180));
    zonasBloqueadas.push_back(sf::FloatRect(1490, 0, 213, 1088));
    zonasBloqueadas.push_back(sf::FloatRect(1200, 450, 110, 110));
    zonasBloqueadas.push_back(sf::FloatRect(1200, 680, 90, 120));
    zonasBloqueadas.push_back(sf::FloatRect(0, 1085, 1696, 19));
    zonasBloqueadas.push_back(sf::FloatRect(0, 1020, 928, 90));
    zonasBloqueadas.push_back(sf::FloatRect(900, 735, 108, 88));
    zonasBloqueadas.push_back(sf::FloatRect(1080, 650, 100,120));
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 230, 540));
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 160, 730));
    zonasBloqueadas.push_back(sf::FloatRect(1080, 201, 100,200));
    zonasBloqueadas.push_back(sf::FloatRect(950, 100, 200,90));
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 30, 1088));
    zonasBloqueadas.push_back(sf::FloatRect(0, 700, 110, 190));
    zonasBloqueadas.push_back(sf::FloatRect(518, 400, 245, 220));//
    zonasBloqueadas.push_back(sf::FloatRect(713, 600, 101, 84));
    zonasBloqueadas.push_back(sf::FloatRect(520, 600, 35, 75));
    zonasBloqueadas.push_back(sf::FloatRect(763, 315, 90, 260));
    zonasBloqueadas.push_back(sf::FloatRect(853,395, 40,177));
    zonasBloqueadas.push_back(sf::FloatRect(430, 315, 90, 260));
    zonasBloqueadas.push_back(sf::FloatRect(380, 391,44, 70));
    zonasBloqueadas.push_back(sf::FloatRect(270, 780, 5, 5));
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 0, 0));



    // Cargar la textura de fondo
    if (!tex.loadFromFile("./Imagenes/Mapas/SegundoMapa.png"))
    {
        throw std::runtime_error("No se pudo cargar la textura del mapa.");
    }
    // Cargar la textura de los items sobre el personaje
    if (!tex2.loadFromFile("./Imagenes/Mapas/ItemsSegMapa.png"))
    {
        throw std::runtime_error("No se pudo cargar la textura de los items del mapa.");
    }

    imagen.setTexture(tex);
    imagen2.setTexture(tex2);
    // Crear una vista que actúa como cámara
    camera.setSize(sf::Vector2f(800, 600));
}



void SegundoMapa::update(sf::RenderWindow &window)
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

//    cambiosDeMapa(window);

}


void SegundoMapa::draw(sf::RenderWindow &window)
{

    sf::View defaultView = window.getDefaultView();


    window.setView(camera);
    window.draw(imagen);
    window.draw(dipper);
    window.draw(imagen2);


    window.setView(defaultView);
    mochila.draw(window);


}

void SegundoMapa::setPersonajePosition(const sf::Vector2f& position)
{
    dipper.setPosition(position);
}


sf::Vector2f SegundoMapa::getDipperPosition() const {
    return dipper.getPosition();
}

