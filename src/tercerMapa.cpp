#include "../tercerMapa.h"
#include <stdexcept>
#include <cmath>
#include <iostream>

TercerMapa::TercerMapa() : cofre(0)

{
    // Inicializamos las zonas bloqueadas (árboles y agua)
    // .push_back(x,y,ancho,altura) sirve para agregar un nuevo dato al final de un vector
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 2000, 180));
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 100, 1367));
    zonasBloqueadas.push_back(sf::FloatRect(348, 0, 201, 745));
    zonasBloqueadas.push_back(sf::FloatRect(212, 420, 188, 250));
    zonasBloqueadas.push_back(sf::FloatRect(270, 350, 73, 61));
    zonasBloqueadas.push_back(sf::FloatRect(240, 670, 101, 64));
    zonasBloqueadas.push_back(sf::FloatRect(1480, 0, 58, 1024));
    zonasBloqueadas.push_back(sf::FloatRect(1434, 330, 102, 680));
    zonasBloqueadas.push_back(sf::FloatRect(1304, 410, 232, 340));
    zonasBloqueadas.push_back(sf::FloatRect(1245, 410, 117, 127));
    zonasBloqueadas.push_back(sf::FloatRect(1394, 360, 92, 38));
    zonasBloqueadas.push_back(sf::FloatRect(0, 950, 1200, 95));
    zonasBloqueadas.push_back(sf::FloatRect(491, 920, 766, 117));
    zonasBloqueadas.push_back(sf::FloatRect(0, 991, 1500, 117));
    zonasBloqueadas.push_back(sf::FloatRect(750,434, 417, 230));
    zonasBloqueadas.push_back(sf::FloatRect(795,374, 300,55));
    zonasBloqueadas.push_back(sf::FloatRect(1125,390, 39,70));
    zonasBloqueadas.push_back(sf::FloatRect(913,669, 198,60));
    zonasBloqueadas.push_back(sf::FloatRect(719,700, 41,8));



    // Cargar la textura de fondo
    if (!tex.loadFromFile("./Imagenes/Mapas/TercerMapa.png"))
    {
        throw std::runtime_error("No se pudo cargar la textura del mapa.");
    }

    if (!font1.loadFromFile("./font/numeros.ttf")){
         throw std::runtime_error("No se pudo cargar la fuente de las vidas");
    }
    if (!golpe.openFromFile("./Imagenes/Sonidos/golpeDipper.wav")) {
        throw std::runtime_error("Error al cargar el sonido de giddeon golpeado");
    }

    golpe.setVolume(20);


    imagen.setTexture(tex);

    wendy.setPosition(sf::Vector2f(173, 256));
    libro1.setPosition(sf::Vector2f(250, 300));
    cofre.setPosition(sf::Vector2f(250, 256));
    bebida.setPosition(sf::Vector2f(290, 256));
    gnomo.setPosition(sf::Vector2f(173,300));


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

    texVidas.setString("VIDAS DE GNOMO ");
}

bool TercerMapa::dialogoIniciado = false;

void TercerMapa::update(sf::RenderWindow &window)
{
    dipper.update();
    handleCollisions();
    gnomo.update(dipper.getPosition());

    // Actualizar Wendy si el cofre está abierto
    if (estadoDelJuego.getEstadoCofres(0)) {
        wendy.update();  // Llamamos al método actualizar de Wendy
    }

    // Resto del código de update...
    sf::Vector2f oldPositionDipper = dipper.getPosition();
    sf::Vector2f newPositionDipper = dipper.getPosition();
    sf::FloatRect newBoundsDipper = dipper.getBounds();
    newBoundsDipper.left = newPositionDipper.x - newBoundsDipper.width / 2;
    newBoundsDipper.top = newPositionDipper.y - newBoundsDipper.height / 2;

    sf::Vector2f oldPositionGnomo = gnomo.getPosition();
    sf::Vector2f newPositionGnomo = gnomo.getPosition();
    sf::FloatRect newBoundsGnomo = gnomo.getBounds();
    newBoundsGnomo.left = newPositionGnomo.x - newBoundsGnomo.width / 2;
    newBoundsGnomo.top = newPositionGnomo.y - newBoundsGnomo.height / 2;

    bool collisionDipper = false;
    bool collisionGnomo = false;
    sf::Vector2f correctionDipper(0.f, 0.f);
    sf::Vector2f correctionGnomo(0.f, 0.f);

    for (const auto& zona : zonasBloqueadas)
    {
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

        if (newBoundsGnomo.intersects(zona))
        {
            collisionGnomo = true;

            if (oldPositionGnomo.x < zona.left && newPositionGnomo.x + newBoundsGnomo.width / 2 > zona.left)
                correctionGnomo.x = zona.left - (newPositionGnomo.x + newBoundsGnomo.width / 2);
            else if (oldPositionGnomo.x > zona.left + zona.width && newPositionGnomo.x - newBoundsGnomo.width / 2 < zona.left + zona.width)
                correctionGnomo.x = (zona.left + zona.width) - (newPositionGnomo.x - newBoundsGnomo.width / 2);

            if (oldPositionGnomo.y < zona.top && newPositionGnomo.y + newBoundsGnomo.height / 2 > zona.top)
                correctionGnomo.y = zona.top - (newPositionGnomo.y + newBoundsGnomo.height / 2);
            else if (oldPositionGnomo.y > zona.top + zona.height && newPositionGnomo.y - newBoundsGnomo.height / 2 < zona.top + zona.height)
                correctionGnomo.y = (zona.top + zona.height) - (newPositionGnomo.y - newBoundsGnomo.height / 2);
        }
    }

    if (collisionDipper)
    {
        if (std::abs(correctionDipper.x) > std::abs(correctionDipper.y))
            newPositionDipper.x += correctionDipper.x;
        else
            newPositionDipper.y += correctionDipper.y;

        dipper.setPosition(newPositionDipper);
    }

    if (collisionGnomo)
    {
        if (std::abs(correctionGnomo.x) > std::abs(correctionGnomo.y))
            newPositionGnomo.x += correctionGnomo.x;
        else
            newPositionGnomo.y += correctionGnomo.y;

        gnomo.setPosition(newPositionGnomo);
    }

    static sf::Clock invulnerabilityTimer;
    static bool isInvulnerable = false;
    static const float invulnerabilityDuration = 1.5f;

    if (isInvulnerable && invulnerabilityTimer.getElapsedTime().asSeconds() >= invulnerabilityDuration) {
        isInvulnerable = false;
    }

    if (estadoDelJuego.getVidasEnemigos("gnomo"))
    {
        for (auto& disparo : gnomo.getDisparos())
        {
            if (disparo.isAlive() && !isInvulnerable && dipper.getBounds().intersects(disparo.getBounds()))
            {
                golpe.play();
                estadoDelJuego.modificarVidasDipper(-1);
                isInvulnerable = true;
                invulnerabilityTimer.restart();
                disparo.kill();
                break;
            }
        }
        for (auto& disparo : dipper.getDisparos())
        {
            if (disparo.isAlive() && !isInvulnerable && gnomo.getBounds().intersects(disparo.getBounds()))
            {
                estadoDelJuego.modificarVidasEnemigos("gnomo");
                isInvulnerable = true;
                invulnerabilityTimer.restart();
                disparo.kill();
                break;
            }
        }
    }

    camera.setCenter(dipper.getPosition());
    sf::Vector2f cameraCenter = camera.getCenter();
    cameraCenter.x = std::max(400.f, std::min(cameraCenter.x, static_cast<float>(tex.getSize().x) - 400.f));
    cameraCenter.y = std::max(300.f, std::min(cameraCenter.y, static_cast<float>(tex.getSize().y) - 300.f));
    camera.setCenter(cameraCenter);


    // Verificar si el cofre está abierto para iniciar el movimiento de Wendy
    static bool movimientoWendyIniciado = false;
    if (estadoDelJuego.getEstadoCofres(0) && !movimientoWendyIniciado && estadoDelJuego.getVidasEnemigos("gnomo")== 0)
    {
        wendy.iniciarMovimientoAutomatico();
        movimientoWendyIniciado = true;
    }

    //dialogo
    sf::Vector2f dipperPos = dipper.getPosition();
    sf::Vector2f wendyPos = wendy.getPosition();
    float distancia = std::sqrt(
        std::pow(dipperPos.x - wendyPos.x, 2) +
        std::pow(dipperPos.y - wendyPos.y, 2)
    );
    if (!dialogoIniciado){
        if (distancia < 200 && !wendy.dialogoPermanentementeCompletado()) {
            wendy.iniciarDialogo();
            dialogoIniciado = true;
            if (wendy.dialogoPermanentementeCompletado()){
                dialogoIniciado = false;
            }
        }
    }

    // Actualizar el diálogo con el tiempo transcurrido
    wendy.actualizarDialogo(_relojDialogo.restart().asSeconds());

}

void TercerMapa::draw(sf::RenderWindow &window)
{
    sf::View defaultView = window.getDefaultView();
    window.setView(camera);
    window.draw(imagen);
    window.draw(dipper);
     if (!estadoDelJuego.getEstadoPersonajes("wendy"))
    {
        window.draw(wendy);
    }
    if(estadoDelJuego.getEstadoCofres(0)){
        if (!estadoDelJuego.getEstadoLibros(1)){
            window.draw(libro1);
        }
        if(!estadoDelJuego.getEstadoBebidas(0)){
            window.draw(bebida);
        }
    }
    if (estadoDelJuego.getVidasEnemigos("gnomo") > 0)
    {
        window.draw(gnomo);
    }
    window.draw(cofre);
    window.setView(defaultView);
    mochila.draw(window);
    window.draw(texVidas);
    sf::String dibujoVidas[5] = {"*","**","***","****","*****"};

    for (int i=0; i<estadoDelJuego.getVidasEnemigos("gnomo");i++){
        if (i+1 == estadoDelJuego.getVidasEnemigos("gnomo")){
            texVidasEnemigo.setString(dibujoVidas[i]);
        }
    }
    if(estadoDelJuego.getVidasEnemigos("gnomo") > 0){
        window.draw(texVidasEnemigo);
    }

}

void TercerMapa::setPersonajePosition(const sf::Vector2f& position)
{
    dipper.setPosition(position);
}

void TercerMapa::handleCollisions()
{
    if (dipper.isCollision(cofre))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !estadoDelJuego.getEstadoCofres(0))
        {
            cofre.sonidoCofre.play();
            cofre.cambiarTextura();
        }
    }
    if (dipper.isCollision(libro1))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && estadoDelJuego.getEstadoCofres(0))
        {
            estadoDelJuego.modificarEstadosLibros(1);
        }
    }
    if (dipper.isCollision(bebida))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && estadoDelJuego.getEstadoCofres(0))
        {
            estadoDelJuego.modificarEstadosBebidas(0);
            estadoDelJuego.contadorDeBebidas();
        }
    }
}

sf::Vector2f TercerMapa::getDipperPosition() const {
    return dipper.getPosition();
}

