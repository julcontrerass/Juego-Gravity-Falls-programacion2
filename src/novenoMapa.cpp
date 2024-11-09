#include "../../novenoMapa.h"
#include "../../quintoMapa.h"
#include <stdexcept>
#include <cmath>

NovenoMapa::NovenoMapa() : cofre(2)
{
    // Inicializamos las zonas bloqueadas (árboles y agua)
    // .push_back(x,y,ancho,altura) sirve para agregar un nuevo dato al final de un vector
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 2000, 236));
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 46, 1024));
    zonasBloqueadas.push_back(sf::FloatRect(1486, 0, 46, 1024));
    zonasBloqueadas.push_back(sf::FloatRect(0, 990, 1536, 47));
    zonasBloqueadas.push_back(sf::FloatRect(360, 560, 790, 170));
    zonasBloqueadas.push_back(sf::FloatRect(163, 361, 12, 11));
    zonasBloqueadas.push_back(sf::FloatRect(429, 512, 51, 45));

    // Cargar la textura de fondo
    if (!tex.loadFromFile("./Imagenes/Mapas/NovenoMapa.png"))
    {
        throw std::runtime_error("No se pudo cargar la textura del primer mapa.");
    }
    //Textura items
    if (!tex2.loadFromFile("./Imagenes/Mapas/ItemsNovMapa.png"))
    {
        throw std::runtime_error("No se pudo cargar la textura del primer mapa.");
    }

    if (!font1.loadFromFile("./font/numeros.ttf")){
         throw std::runtime_error("No se pudo cargar la fuente de las vidas");
    }
    if (!font2.loadFromFile("./font/numeros.ttf")){
         throw std::runtime_error("No se pudo cargar la fuente de las vidas");
    }

    imagen.setTexture(tex);
    imagen2.setTexture(tex2);

    libro2.setPosition(sf::Vector2f(600, 350));
    cofre.setPosition(sf::Vector2f(600, 300));
    pocion.setPosition(sf::Vector2f(650, 350));
    linterna.setPosition(sf::Vector2f(650, 300));
    gideon.setPosition(sf::Vector2f(800, 400));
    mabbel.setPosition(sf::Vector2f(700,300));

    texVidas.setFont(font1);
    texVidas.setCharacterSize(30);
    texVidas.setFillColor(sf::Color::White);
    texVidas.setPosition(300,10);
    texVidasEnemigo.setFont(font1);
    texVidasEnemigo.setCharacterSize(70);
    texVidasEnemigo.setFillColor(sf::Color::White);
    texVidasEnemigo.setPosition(330,20);

    imagen.setTexture(tex);

    // Crear una vista que actúa como cámara
    camera.setSize(sf::Vector2f(800, 600));

    texVidas.setString("VIDAS DE GIDEON");

}

bool NovenoMapa::dialogoIniciado = false;

void NovenoMapa::update(sf::RenderWindow &window)
{
    dipper.update();
    handleCollisions();
    gideon.update(dipper.getPosition());

    if(estadoDelJuego.getEstadoCofres(2)){
        mabbel.update();
    }

     // Manejo de colisiones con paredes para Dipper
    sf::Vector2f oldPositionDipper = dipper.getPosition();
    sf::Vector2f newPositionDipper = dipper.getPosition();
    sf::FloatRect newBoundsDipper = dipper.getBounds();
    newBoundsDipper.left = newPositionDipper.x - newBoundsDipper.width / 2;
    newBoundsDipper.top = newPositionDipper.y - newBoundsDipper.height / 2;

    // Manejo de colisiones con paredes para Gnomo
    sf::Vector2f antiguaPosicionGideon = gideon.getPosition();
    sf::Vector2f nuevaPosicionGideon = gideon.getPosition();
    sf::FloatRect nuevoLimGideon = gideon.getBounds();
    nuevoLimGideon.left = nuevaPosicionGideon.x - nuevoLimGideon.width / 2;
    nuevoLimGideon.top = nuevaPosicionGideon.y - nuevoLimGideon.height / 2;


    bool collisionDipper = false;
    bool collisionGideon = false;
    sf::Vector2f correctionDipper(0.f, 0.f);
    sf::Vector2f correccionGideon(0.f, 0.f);

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

        // Colisiones para Gnomo
        if (nuevoLimGideon.intersects(zona))
        {
            collisionGideon = true;

            if (antiguaPosicionGideon.x < zona.left && nuevaPosicionGideon.x + nuevoLimGideon.width / 2 > zona.left)
                correccionGideon.x = zona.left - (nuevaPosicionGideon.x + nuevoLimGideon.width / 2);
            else if (antiguaPosicionGideon.x > zona.left + zona.width && nuevaPosicionGideon.x - nuevoLimGideon.width / 2 < zona.left + zona.width)
                correccionGideon.x = (zona.left + zona.width) - (nuevaPosicionGideon.x - nuevoLimGideon.width / 2);

            if (antiguaPosicionGideon.y < zona.top && nuevaPosicionGideon.y + nuevoLimGideon.height / 2 > zona.top)
                correccionGideon.y = zona.top - (nuevaPosicionGideon.y + nuevoLimGideon.height / 2);
            else if (antiguaPosicionGideon.y > zona.top + zona.height && nuevaPosicionGideon.y - nuevoLimGideon.height / 2 < zona.top + zona.height)
                correccionGideon.y = (zona.top + zona.height) - (nuevaPosicionGideon.y - nuevoLimGideon.height / 2);
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

    // Aplicar correcciones para minotauro
    if (collisionGideon)
    {
        if (std::abs(correccionGideon.x) > std::abs(correccionGideon.y))
            nuevaPosicionGideon.x += correccionGideon.x;
        else
            nuevaPosicionGideon.y += correccionGideon.y;

        gideon.setPosition(nuevaPosicionGideon);
    }

    // Sistema de daño por disparos
    static sf::Clock invulnerabilityTimer;
    static bool isInvulnerable = false;
    static const float invulnerabilityDuration = 1.5f;

    if (isInvulnerable && invulnerabilityTimer.getElapsedTime().asSeconds() >= invulnerabilityDuration) {
        isInvulnerable = false;
    }

    if (estadoDelJuego.getVidasEnemigos("gideon") >0)
    {
        for (auto& disparo : gideon.getDisparos())
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
            if (disparo.isAlive() && !isInvulnerable && gideon.getBounds().intersects(disparo.getBounds()))
            {
                estadoDelJuego.modificarVidasEnemigos("gideon", -1);
                isInvulnerable = true;
                invulnerabilityTimer.restart();
                disparo.kill();
                break;
            }
        }
    }



    // Actualizar la cámara
    camera.setCenter(dipper.getPosition());

    // Limitar la cámara a los bordes del mapa
    sf::Vector2f cameraCenter = camera.getCenter();
    cameraCenter.x = std::max(400.f, std::min(cameraCenter.x, static_cast<float>(tex.getSize().x) - 400.f));
    cameraCenter.y = std::max(300.f, std::min(cameraCenter.y, static_cast<float>(tex.getSize().y) - 300.f));
    camera.setCenter(cameraCenter);

    // Verificar si el cofre está abierto para iniciar el movimiento de Wendy
    static bool movimientoMabbelIniciado = false;
    if (estadoDelJuego.getEstadoCofres(2) && !movimientoMabbelIniciado && estadoDelJuego.getVidasEnemigos("gideon") == 0)
    {
        mabbel.iniciarMovimientoAutomatico();
        movimientoMabbelIniciado = true;
    }

    //dialogo
    sf::Vector2f dipperPos = dipper.getPosition();
    sf::Vector2f mabbelPos = mabbel.getPosition();
    float distancia = std::sqrt(
        std::pow(dipperPos.x - mabbelPos.x, 2) +
        std::pow(dipperPos.y - mabbelPos.y, 2)
    );
    if (!dialogoIniciado){
        if (distancia < 200 && !mabbel.dialogoPermanentementeCompletado()) {
            mabbel.iniciarDialogo();
            dialogoIniciado = true;
            if (mabbel.dialogoPermanentementeCompletado()){
                dialogoIniciado = false;
            }
        }
    }

    // Actualizar el diálogo con el tiempo transcurrido
    mabbel.actualizarDialogo(_relojDialogo.restart().asSeconds());

}


void NovenoMapa::draw(sf::RenderWindow &window)
{
    sf::View defaultView = window.getDefaultView();

    window.setView(camera);
    window.draw(imagen);
    window.draw(dipper);
    window.draw(imagen2);
    if (!estadoDelJuego.getEstadoPersonajes("mabbel"))
    {
        window.draw(mabbel);
    }
    if(estadoDelJuego.getEstadoCofres(2))
    {
        if (!estadoDelJuego.getEstadoLibros(2))
        {
            window.draw(libro2);
        }
        if(!estadoDelJuego.getEstadoPociones(0)){
            window.draw(pocion);
        }
        if(!estadoDelJuego.getEstadosItems("linterna")){
            window.draw(linterna);
        }
    }
    if (estadoDelJuego.getVidasEnemigos("gideon")>0)
    {
        window.draw(gideon);
    }
    window.draw(cofre);
    window.setView(defaultView);
    mochila.draw(window);
    window.draw(texVidas);

    sf::String dibujoVidas[5] = {"*","**","***","****","*****"};;


    for (int i=0; i<estadoDelJuego.getVidasEnemigos("gideon");i++){
        if (i+1 == estadoDelJuego.getVidasEnemigos("gideon")){
                texVidasEnemigo.setString(dibujoVidas[i]);
        }
    }

    if(estadoDelJuego.getVidasEnemigos("gideon")>0){
        window.draw(texVidasEnemigo);
    }


}

void NovenoMapa::setPersonajePosition(const sf::Vector2f& position)
{
    dipper.setPosition(position);
}
sf::Vector2f NovenoMapa::getDipperPosition() const {
    return dipper.getPosition();
}


void NovenoMapa::handleCollisions()
{
    if (dipper.isCollision(cofre))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !estadoDelJuego.getEstadoCofres(2))
        {
            cofre.sonidoCofre.play();
            cofre.cambiarTextura();
            // El estado se guarda automáticamente en el array
        }
    }
    if (dipper.isCollision(libro2))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && estadoDelJuego.getEstadoCofres(2))
        {
            estadoDelJuego.modificarEstadosLibros(2);
        }
    }
    if(dipper.isCollision(pocion)){
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && estadoDelJuego.getEstadoCofres(2))
        {
            estadoDelJuego.modificarEstadosPociones(0);
        }
    }
    if(dipper.isCollision(linterna)){
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && estadoDelJuego.getEstadoCofres(2))
        {
            estadoDelJuego.modificarEstadosItems("linterna");
        }
    }
}

