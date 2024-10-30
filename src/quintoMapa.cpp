#include "quintoMapa.h"
#include "../novenoMapa.h"
#include "../cuartoMapa.h"
#include <stdexcept>

QuintoMapa::QuintoMapa() : cofre(1)
{
    // Inicializamos las zonas bloqueadas (árboles y agua)
    // .push_back(x,y,ancho,altura) sirve para agregar un nuevo dato al final de un vector
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 800, 206));
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 20, 600));
    zonasBloqueadas.push_back(sf::FloatRect(0, 557, 311, 60));
    zonasBloqueadas.push_back(sf::FloatRect(489, 557, 400, 60));
    zonasBloqueadas.push_back(sf::FloatRect(781, 0, 20, 600));
    zonasBloqueadas.push_back(sf::FloatRect(92, 287, 87, 196));
    zonasBloqueadas.push_back(sf::FloatRect(349, 0, 94, 238));
    zonasBloqueadas.push_back(sf::FloatRect(653, 0, 147, 234));
    zonasBloqueadas.push_back(sf::FloatRect(523, 0, 39,240));
    zonasBloqueadas.push_back(sf::FloatRect(0, 630, 800,14));



    // Cargar la textura de fondo
    if (!tex.loadFromFile("./Imagenes/Mapas/QuintoMapa.png"))
    {
        throw std::runtime_error("No se pudo cargar la textura del primer mapa.");
    }
    if (!tex2.loadFromFile("./Imagenes/Mapas/ItemsQuintMapa.png"))
    {
        throw std::runtime_error("No se pudo cargar la textura del primer mapa.");
    }


    imagen.setTexture(tex);
    imagen2.setTexture(tex2);

    bebida.setPosition(sf::Vector2f(650,310));


    // Crear una vista que actúa como cámara
    camera.setSize(sf::Vector2f(800, 600));
}



//void QuintoMapa::run(sf::RenderWindow &window)
//{
//    // Game loop (finaliza cuando cierra la ventana)
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
//                window.close();  // Cerrar la ventana si se presiona 'Escape' o se cierra la ventana
//        }
//
//        update(window);  // Pasamos window a update para poder cambiar de mapa
//        window.clear();
//        draw(window);
//        window.display();
//    }
//}

void QuintoMapa::update(sf::RenderWindow &window)
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
    handleCollisions();


}


void QuintoMapa::draw(sf::RenderWindow &window)
{
    sf::View defaultView = window.getDefaultView();

    window.setView(camera);
    window.draw(imagen);
    window.draw(dipper);
    if(!bebida.bebidasRecolectadas(1)){
            window.draw(bebida);
    }
    window.setView(defaultView);
    mochila.draw(window);

}

void QuintoMapa::setPersonajePosition(const sf::Vector2f& position)
{
    dipper.setPosition(position);
}

sf::Vector2f QuintoMapa::getDipperPosition() const {
    return dipper.getPosition();
}
//void QuintoMapa::cambiosDeMapa(sf::RenderWindow &window)
//{
//    // verificamos si el personaje está en la posición para cambiar al segundo mapa
//    dipperPos = dipper.getPosition();
//    ///LLAMAMOS AL CUARTO MAPA
//    if (dipperPos.x >= 330 && dipperPos.x <= 472 && dipperPos.y >= 520 && dipperPos.y <= 600)
//    {
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//        {
//            CuartoMapa cuartoMapa;
//            cuartoMapa.setPersonajePosition(sf::Vector2f(1182, 60));
//            cuartoMapa.run(window);
//            return;
//        }
//    }
//    // verificamos si el personaje está en la posición para cambiar al segundo mapa
//    sf::Vector2f dipperPos = dipper.getPosition();
//    if (dipperPos.x >= 0 && dipperPos.x <= 83 && dipperPos.y >= 300 && dipperPos.y <= 400)
//    {
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//        {
//            NovenoMapa novenoMapa;
//            novenoMapa.setPersonajePosition(sf::Vector2f(1125, 195));
//            novenoMapa.run(window);
//            return;
//        }
//    }
//}


void QuintoMapa::handleCollisions()
{
    if (dipper.isCollision(bebida))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            bebida.recolectado(1);
        }
    }
}


