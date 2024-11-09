#include "../mapaFinal.h"
#include <stdexcept>
#include <cmath>

MapaFinal::MapaFinal()

{
    // Inicializamos las zonas bloqueadas (árboles y agua)
    // .push_back(x,y,ancho,altura) sirve para agregar un nuevo dato al final de un vector
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 1523, 92));
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 96, 1030));
    zonasBloqueadas.push_back(sf::FloatRect(0, 1000, 1536, 43));
    zonasBloqueadas.push_back(sf::FloatRect(1424, 0, 102, 1024));
    zonasBloqueadas.push_back(sf::FloatRect(1379, 468, 157, 557));
    zonasBloqueadas.push_back(sf::FloatRect(1312, 470, 108, 206));
    zonasBloqueadas.push_back(sf::FloatRect(594, 0, 309, 230));
    zonasBloqueadas.push_back(sf::FloatRect(860, 0, 178, 165));
    zonasBloqueadas.push_back(sf::FloatRect(284, 856, 260, 150));
    zonasBloqueadas.push_back(sf::FloatRect(207, 363, 672, 109));
    zonasBloqueadas.push_back(sf::FloatRect(207, 363, 118, 290));
    zonasBloqueadas.push_back(sf::FloatRect(207, 566, 469, 111));
    zonasBloqueadas.push_back(sf::FloatRect(781, 495, 284, 230));
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 391, 140));
    zonasBloqueadas.push_back(sf::FloatRect(458, 0, 51, 448));
    zonasBloqueadas.push_back(sf::FloatRect(458, 303, 109, 6));


    // Cargar la textura de fondo
    if (!tex.loadFromFile("./Imagenes/Mapas/MapaFinal.png"))
    {
        throw std::runtime_error("No se pudo cargar la textura del mapa.");
    }

    if (!font1.loadFromFile("./font/numeros.ttf"))
    {
        throw std::runtime_error("No se pudo cargar la fuente de las vidas");
    }

    texVidas.setFont(font1);
    texVidas.setCharacterSize(30);
    texVidas.setFillColor(sf::Color::White);
    texVidas.setPosition(270,66);
    texVidasEnemigo.setFont(font1);
    texVidasEnemigo.setCharacterSize(70);
    texVidasEnemigo.setFillColor(sf::Color::White);
    texVidasEnemigo.setPosition(290,80);

    imagen.setTexture(tex);

    bill.setPosition(sf::Vector2f(1100,244));

    // Crear una vista que actúa como cámara
    camera.setSize(sf::Vector2f(800, 600));

    texVidas.setString("VIDAS DE BILL ");

}



void MapaFinal::update(sf::RenderWindow &window)
{
    dipper.update();
    bill.update(dipper.getPosition());

    // Manejo de colisiones con paredes para Dipper
    sf::Vector2f oldPositionDipper = dipper.getPosition();
    sf::Vector2f newPositionDipper = dipper.getPosition();
    sf::FloatRect newBoundsDipper = dipper.getBounds();
    newBoundsDipper.left = newPositionDipper.x - newBoundsDipper.width / 2;
    newBoundsDipper.top = newPositionDipper.y - newBoundsDipper.height / 2;

    // Manejo de colisiones con paredes para bill
    sf::Vector2f oldPositionBill = bill.getPosition();
    sf::Vector2f newPositionBill = bill.getPosition();
    sf::FloatRect newBoundsBill = bill.getBounds();
    newBoundsBill.left = newPositionBill.x - newBoundsBill.width / 2;
    newBoundsBill.top = newPositionBill.y - newBoundsBill.height / 2;

    bool collisionDipper = false;
    bool collisionBill = false;
    sf::Vector2f correctionDipper(0.f, 0.f);
    sf::Vector2f correctionBill(0.f, 0.f);

    // Colisiones con zonas bloqueadas para ambos
    for (const auto& zona : zonasBloqueadas)
    {
        // Colisiones para Dipper
        if (newBoundsDipper.intersects(zona))
        {
            collisionDipper = true;

            if (oldPositionDipper.x < zona.left && newPositionDipper.x + newBoundsDipper.width / 2 > zona.left)
                correctionDipper.x = zona.left - (newPositionDipper.x + newBoundsDipper.width / 2);
            else if (oldPositionDipper.x > zona.left + zona.width && newPositionDipper.x - newBoundsDipper.width / 2 < zona.left + zona.width)
                correctionDipper.x = (zona.left + zona.width) - (newPositionDipper.x - newBoundsDipper.width / 2);

            if (oldPositionDipper.y < zona.top && newPositionDipper.y + newBoundsDipper.height / 2 > zona.top)
                correctionDipper.y = zona.top - (newPositionDipper.y + newBoundsDipper.height / 2);
            else if (oldPositionDipper.y > zona.top + zona.height && newPositionDipper.y - newBoundsDipper.height / 2 < zona.top + zona.height)
                correctionDipper.y = (zona.top + zona.height) - (newPositionDipper.y - newBoundsDipper.height / 2);
        }

        //Colisiones para Bill
        if (newBoundsBill.intersects(zona))
        {
            collisionBill = true;

            if (oldPositionBill.x < zona.left && newPositionBill.x + newBoundsBill.width / 2 > zona.left)
                correctionBill.x = zona.left - (newPositionBill.x + newBoundsBill.width / 2);
            else if (oldPositionBill.x > zona.left + zona.width && newPositionBill.x - newBoundsBill.width / 2 < zona.left + zona.width)
                correctionBill.x = (zona.left + zona.width) - (newPositionBill.x - newBoundsBill.width / 2);

            if (oldPositionBill.y < zona.top && newPositionBill.y + newBoundsBill.height / 2 > zona.top)
                correctionBill.y = zona.top - (newPositionBill.y + newBoundsBill.height / 2);
            else if (oldPositionBill.y > zona.top + zona.height && newPositionBill.y - newBoundsBill.height / 2 < zona.top + zona.height)
                correctionBill.y = (zona.top + zona.height) - (newPositionBill.y - newBoundsBill.height / 2);
        }
    }

    // Aplicar correcciones para Dipper
    if (collisionDipper)
    {
        if (std::abs(correctionDipper.x) > std::abs(correctionDipper.y))
            newPositionDipper.x += correctionDipper.x;
        else
            newPositionDipper.y += correctionDipper.y;

        dipper.setPosition(newPositionDipper);
    }

    //Aplicar correcciones para Bill
    if (collisionBill)
    {
        if (std::abs(correctionBill.x) > std::abs(correctionBill.y))
            newPositionBill.x += correctionBill.x;
        else
            newPositionBill.y += correctionBill.y;

        bill.setPosition(newPositionBill);
    }

    // Sistema de daño por disparos
    static sf::Clock invulnerabilityTimer;
    static bool isInvulnerable = false;
    static const float invulnerabilityDuration = 1.5f;

    if (isInvulnerable && invulnerabilityTimer.getElapsedTime().asSeconds() >= invulnerabilityDuration)
    {
        isInvulnerable = false;
    }

    if (estadoDelJuego.getVidasEnemigos("bill")>0)
    {
        for (auto& disparo : bill.getDisparos())
        {
            if (disparo.isAlive() && !isInvulnerable && dipper.getBounds().intersects(disparo.getBounds()))
            {
                estadoDelJuego.modificarVidasDipper(-1);
                isInvulnerable = true;
                invulnerabilityTimer.restart();
                disparo.kill();
                break;
            }
        }
        for (auto& disparo : dipper.getDisparos())
        {
            if (disparo.isAlive() && !isInvulnerable && bill.getBounds().intersects(disparo.getBounds()))
            {
                estadoDelJuego.modificarVidasEnemigos("bill",-1);
                isInvulnerable = true;
                invulnerabilityTimer.restart();
                // Añadir esta comprobación aquí
                if (estadoDelJuego.getVidasEnemigos("bill") == 0)
                {
                    bill.iniciarAnimacionMuerte();
                }
            }
        }
    }

    // Actualizar la cámara
    camera.setCenter(dipper.getPosition());
    sf::Vector2f cameraCenter = camera.getCenter();
    cameraCenter.x = std::max(400.f, std::min(cameraCenter.x, static_cast<float>(tex.getSize().x) - 400.f));
    cameraCenter.y = std::max(300.f, std::min(cameraCenter.y, static_cast<float>(tex.getSize().y) - 300.f));
    camera.setCenter(cameraCenter);

}

void MapaFinal::draw(sf::RenderWindow &window)
{
    sf::View defaultView = window.getDefaultView();


    window.setView(camera);
    window.draw(imagen);
    window.draw(dipper);

    window.draw(bill);


    window.setView(defaultView);
    window.draw(texVidas);

    sf::String dibujoVidas[5] = {"*","**","***","****","*****"};;


    for (int i=0; i<estadoDelJuego.getVidasEnemigos("bill"); i++)
    {
        if (i+1 == estadoDelJuego.getVidasEnemigos("bill"))
        {
            texVidasEnemigo.setString(dibujoVidas[i]);
        }
    }
    if(estadoDelJuego.getVidasEnemigos("bill")>0)
    {
        window.draw(texVidasEnemigo);
    }
    mochila.draw(window);


}



void MapaFinal::setPersonajePosition(const sf::Vector2f& position)
{
    dipper.setPosition(position);
}


