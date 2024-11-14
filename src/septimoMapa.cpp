#include "../septimoMapa.h"
#include "../sextoMapa.h"
#include <cmath>
#include <stdexcept>

SeptimoMapa::SeptimoMapa() : cofre(1)
{
    // Inicializamos las zonas bloqueadas (árboles y agua)
    // .push_back(x,y,ancho,altura) sirve para agregar un nuevo dato al final de un vector
    zonasBloqueadas.push_back(sf::FloatRect(760, 0, 40, 600));
    zonasBloqueadas.push_back(sf::FloatRect(0, 560, 800, 60));
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 800,116));
    zonasBloqueadas.push_back(sf::FloatRect(0, 0, 31,600));
    zonasBloqueadas.push_back(sf::FloatRect(503, 0, 16,325));
    zonasBloqueadas.push_back(sf::FloatRect(440, 280, 79,50));
    zonasBloqueadas.push_back(sf::FloatRect(303, 280, 53,56));
    zonasBloqueadas.push_back(sf::FloatRect(303, 280, 23,261));
    zonasBloqueadas.push_back(sf::FloatRect(0, 490, 326,100));
    zonasBloqueadas.push_back(sf::FloatRect(508, 0, 246,182));


    // Cargar la textura de fondo
    if (!tex.loadFromFile("./Imagenes/Mapas/SeptimoMapa.png"))
    {
        throw std::runtime_error("No se pudo cargar la textura del primer mapa.");
    }

    if (!font1.loadFromFile("./font/numeros.ttf")){
         throw std::runtime_error("No se pudo cargar la fuente de las vidas");
    }

    texVidas.setFont(font1);
    texVidas.setCharacterSize(30);
    texVidas.setFillColor(sf::Color::White);
    texVidas.setPosition(300,10);
    texVidasEnemigo.setFont(font1);
    texVidasEnemigo.setCharacterSize(70);
    texVidasEnemigo.setFillColor(sf::Color::White);
    texVidasEnemigo.setPosition(330,20);

    imagen.setTexture(tex);

    cofre.setPosition(sf::Vector2f(78, 406));
    libro3.setPosition(sf::Vector2f(78, 350));
    gancho.setPosition(sf::Vector2f(120,406));
    minotauro.setPosition(sf::Vector2f(150,264));
    soos.setPosition(sf::Vector2f(78,305));
    // Crear una vista que actúa como cámara
    camera.setSize(sf::Vector2f(800, 600));

    texVidas.setString("VIDAS DE MINOTAURO ");
}
bool SeptimoMapa::dialogoIniciado = false;


void SeptimoMapa::update(sf::RenderWindow &window)
{
    dipper.update();
    handleCollisions();
    minotauro.update(dipper.getPosition());


    if (estadoDelJuego.getEstadoCofres(1)){
        soos.update();
    }

    // Manejo de colisiones con paredes para Dipper
    sf::Vector2f oldPositionDipper = dipper.getPosition();
    sf::Vector2f newPositionDipper = dipper.getPosition();
    sf::FloatRect newBoundsDipper = dipper.getBounds();
    newBoundsDipper.left = newPositionDipper.x - newBoundsDipper.width / 2;
    newBoundsDipper.top = newPositionDipper.y - newBoundsDipper.height / 2;

    // Manejo de colisiones con paredes para Gnomo
    sf::Vector2f antiguaPosicionminot = minotauro.getPosition();
    sf::Vector2f nuevaPosicionMinotauro = minotauro.getPosition();
    sf::FloatRect nuevoLimMinotauro = minotauro.getBounds();
    nuevoLimMinotauro.left = nuevaPosicionMinotauro.x - nuevoLimMinotauro.width / 2;
    nuevoLimMinotauro.top = nuevaPosicionMinotauro.y - nuevoLimMinotauro.height / 2;

    bool collisionDipper = false;
    bool collisionMino = false;
    sf::Vector2f correctionDipper(0.f, 0.f);
    sf::Vector2f correccionMinotauro(0.f, 0.f);

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
        if (nuevoLimMinotauro.intersects(zona))
        {
            collisionMino = true;

            if (antiguaPosicionminot.x < zona.left && nuevaPosicionMinotauro.x + nuevoLimMinotauro.width / 2 > zona.left)
                correccionMinotauro.x = zona.left - (nuevaPosicionMinotauro.x + nuevoLimMinotauro.width / 2);
            else if (antiguaPosicionminot.x > zona.left + zona.width && nuevaPosicionMinotauro.x - nuevoLimMinotauro.width / 2 < zona.left + zona.width)
                correccionMinotauro.x = (zona.left + zona.width) - (nuevaPosicionMinotauro.x - nuevoLimMinotauro.width / 2);

            if (antiguaPosicionminot.y < zona.top && nuevaPosicionMinotauro.y + nuevoLimMinotauro.height / 2 > zona.top)
                correccionMinotauro.y = zona.top - (nuevaPosicionMinotauro.y + nuevoLimMinotauro.height / 2);
            else if (antiguaPosicionminot.y > zona.top + zona.height && nuevaPosicionMinotauro.y - nuevoLimMinotauro.height / 2 < zona.top + zona.height)
                correccionMinotauro.y = (zona.top + zona.height) - (nuevaPosicionMinotauro.y - nuevoLimMinotauro.height / 2);
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
    if (collisionMino)
    {
        if (std::abs(correccionMinotauro.x) > std::abs(correccionMinotauro.y))
            nuevaPosicionMinotauro.x += correccionMinotauro.x;
        else
            nuevaPosicionMinotauro.y += correccionMinotauro.y;

        minotauro.setPosition(nuevaPosicionMinotauro);
    }

    // Sistema de daño por disparos
    static sf::Clock invulnerabilityTimer;
    static bool isInvulnerable = false;
    static const float invulnerabilityDuration = 1.5f;

    if (isInvulnerable && invulnerabilityTimer.getElapsedTime().asSeconds() >= invulnerabilityDuration) {
        isInvulnerable = false;
    }

    if (estadoDelJuego.getVidasEnemigos("minotauro") > 0)
    {
        for (auto& disparo : minotauro.getDisparos())
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
            if (disparo.isAlive() && !isInvulnerable && minotauro.getBounds().intersects(disparo.getBounds()))
            {
                estadoDelJuego.modificarVidasEnemigos("minotauro");
                isInvulnerable = true;
                invulnerabilityTimer.restart();
                disparo.kill();
                break;
            }
        }
    }

    // Actualizar la cámara
    camera.setCenter(dipper.getPosition());
    sf::Vector2f cameraCenter = camera.getCenter();
    cameraCenter.x = std::max(400.f, std::min(cameraCenter.x, static_cast<float>(tex.getSize().x) - 400.f));
    cameraCenter.y = std::max(300.f, std::min(cameraCenter.y, static_cast<float>(tex.getSize().y) - 300.f));
    camera.setCenter(cameraCenter);

    // Verificar si el cofre está abierto para iniciar el movimiento de Soos
    static bool movimientoSoosIniciado = false;
    if (estadoDelJuego.getEstadoCofres(1) && !movimientoSoosIniciado && estadoDelJuego.getVidasEnemigos("minotauro")== 0)
    {
        soos.iniciarMovimientoAutomatico();
        movimientoSoosIniciado = true;

    }

    //dialogo
    sf::Vector2f dipperPos = dipper.getPosition();
    sf::Vector2f soosPos = soos.getPosition();
    float distancia = std::sqrt(
        std::pow(dipperPos.x - soosPos.x, 2) +
        std::pow(dipperPos.y - soosPos.y, 2)
    );

    if (!dialogoIniciado){
        if (distancia < 200 && !soos.dialogoPermanentementeCompletado()) {
            soos.iniciarDialogo();
            dialogoIniciado = true;
            if (soos.dialogoPermanentementeCompletado()){
                dialogoIniciado = false;
            }
        }
    }
    // Actualizar el diálogo con el tiempo transcurrido
    soos.actualizarDialogo(_relojDialogo.restart().asSeconds());
}


void SeptimoMapa::draw(sf::RenderWindow &window)
{
    sf::View defaultView = window.getDefaultView();

    window.setView(camera);
    window.draw(imagen);
    window.draw(dipper);
    window.draw(cofre);
    if (!estadoDelJuego.getEstadoPersonajes("soos"))
    {
       window.draw(soos);
    }
    if(estadoDelJuego.getEstadoCofres(1)){
        if (!estadoDelJuego.getEstadoLibros(3)){
            window.draw(libro3);
        }
        if(!estadoDelJuego.getEstadosItems("gancho")){
            window.draw(gancho);
        }
    }
    if (estadoDelJuego.getVidasEnemigos("minotauro") > 0)
    {
        window.draw(minotauro);
    }


    window.setView(defaultView);
    mochila.draw(window);
    window.draw(texVidas);

    sf::String dibujoVidas[5] = {"*","**","***","****","*****"};;


    for (int i=0; i<estadoDelJuego.getVidasEnemigos("minotauro");i++){
        if (i+1 == estadoDelJuego.getVidasEnemigos("minotauro")){
                texVidasEnemigo.setString(dibujoVidas[i]);
        }
    }
    if(estadoDelJuego.getVidasEnemigos("minotauro") > 0){
        window.draw(texVidasEnemigo);
    }

}

void SeptimoMapa::setPersonajePosition(const sf::Vector2f& position)
{
    dipper.setPosition(position);
}

sf::Vector2f SeptimoMapa::getDipperPosition() const {
    return dipper.getPosition();
}


void SeptimoMapa::handleCollisions()
{
    if (dipper.isCollision(cofre))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !estadoDelJuego.getEstadoCofres(1))
        {
            cofre.sonidoCofre.play();
            cofre.cambiarTextura();
        }
    }
    if (dipper.isCollision(libro3))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && estadoDelJuego.getEstadoCofres(1))
        {
            estadoDelJuego.modificarEstadosLibros(3);
        }
    }
    if (dipper.isCollision(gancho))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && estadoDelJuego.getEstadoCofres(1))
        {
            estadoDelJuego.modificarEstadosItems("gancho");
        }
    }
}
