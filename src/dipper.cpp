#include "dipper.h"

// Constructor de la clase Dipper
Dipper::Dipper()
    : _frame(0), _velocity(4, 4), _direccionMirada(0, 1), incremento (false)
{
    // Carga la textura del personaje desde un archivo
    if(!_texture.loadFromFile("./Imagenes/Personajes/dipper.png")){
        throw std::runtime_error("Error al cargar la imagen del personaje");
    }

     if (!sonidoBebida.openFromFile("./Imagenes/Sonidos/sonidoBebida.wav")) {
        throw std::runtime_error("Error al cargar el sonido de la bebida");
    }
    sonidoBebida.setVolume(30);

    // Asigna la textura al sprite
    _sprite.setTexture(_texture);

    // Define el rect�ngulo de textura inicial (primer frame de animaci�n)
    _sprite.setTextureRect({0, 0, 50, 55});

    // Centra el origen del sprite en la base del personaje
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
}

int Dipper::vidas = 5;

// M�todo para actualizar el estado del personaje en cada frame
void Dipper::update()
{
    // Reinicia la velocidad a cero en cada frame
    _velocity = {0, 0};

    if(timer>0){
        timer--;
    }

    if(timer == 0){
        incremento = false;
    }

    if(pocion.cantidadDePociones() > 0){
        if (timer == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
                incremento = true;
                pocion.restaPociones();
                timer= 400;
        }
    }

    if(bebida.cantidadDeBebidas()>0 && vidas < 5){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
            sonidoBebida.play();
            recuperarVidas();
            bebida.restaBebidas();
        }
    }



    // Reinicia la animaci�n si se ha completado un ciclo
    if (_frame >= 2) _frame = 0;

    // Comprueba la entrada del teclado para el movimiento hacia arriba
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (incremento){
            _velocity.y = -6;
        }else{
            _velocity.y = -4;
        }
          // Establece la velocidad vertical negativa (hacia arriba)
        _frame += 0.2f;    // Avanza la animaci�n
        _sprite.setTextureRect({int(_frame) * 50, 169, 50, 55});  // Actualiza el rect�ngulo de textura para la animaci�n hacia arriba
        _direccionMirada = {0, -1};  // Actualiza la direcci�n de la mirada
    }

    // Comprueba la entrada del teclado para el movimiento hacia abajo
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (incremento){
            _velocity.y = 6;
        }else{
            _velocity.y = 4;
        }  // Establece la velocidad vertical positiva (hacia abajo)
        _frame += 0.2f;   // Avanza la animaci�n
        _sprite.setTextureRect({0 + int(_frame) * 50, 0, 50, 55});  // Actualiza el rect�ngulo de textura para la animaci�n hacia abajo
        _direccionMirada = {0, 1};  // Actualiza la direcci�n de la mirada
    }

    // Comprueba la entrada del teclado para el movimiento hacia la izquierda
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (incremento){
            _velocity.x = -6;
        }else{
            _velocity.x = -4;
        }  // Establece la velocidad horizontal negativa (hacia la izquierda)
        _frame += 0.2f;    // Avanza la animaci�n
        _sprite.setTextureRect({0 + int(_frame) * 50, 57, 50, 55});  // Actualiza el rect�ngulo de textura para la animaci�n hacia la izquierda
        _direccionMirada = {-1, 0};  // Actualiza la direcci�n de la mirada
    }

    // Comprueba la entrada del teclado para el movimiento hacia la derecha
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (incremento){
            _velocity.x = 6;
        }else{
            _velocity.x = 4;
        }  // Establece la velocidad horizontal positiva (hacia la derecha)
        _frame += 0.2f;   // Avanza la animaci�n
        _sprite.setTextureRect({0 + int(_frame) * 50, 113, 50, 55});  // Actualiza el rect�ngulo de textura para la animaci�n hacia la derecha
        _direccionMirada = {1, 0};  // Actualiza la direcci�n de la mirada
    }

    // Aplica el movimiento al sprite
    _sprite.move(_velocity);


    //accion de dispara
    // Disparo con la tecla Space
    if (cuchillo.estadoDelCuchillo() || gancho.estadoDelGancho() || linterna.estadoDeLaLinterna()){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            disparar();
        }
    }



    // Cambiar tipo de disparo con la tecla C
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
        cambiarTipoDisparo();
    }

    // Actualizar disparos existentes
    for (auto it = _disparos.begin(); it != _disparos.end();) {
        it->update();
        if (!it->isAlive()) {
            it = _disparos.erase(it);
        } else {
            ++it;
        }
    }
}

// M�todo para obtener la posici�n actual del personaje
sf::Vector2f Dipper::getPosition() const
{
    return _sprite.getPosition();
}

// M�todo para dibujar el personaje en la ventana
void Dipper::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);
    // Dibuja todos los disparos activos
    for (const auto& disparo : _disparos) {
        target.draw(disparo, states);
    }
}

// M�todo para obtener los l�mites globales del sprite del personaje
sf::FloatRect Dipper::getBounds() const
{
    return _sprite.getGlobalBounds();
}

// M�todo para establecer la posici�n del personaje
void Dipper::setPosition(const sf::Vector2f& position)
{
    _sprite.setPosition(position);
}

void Dipper::setInitialTextureRect(int row)
{
    _sprite.setTextureRect({50, row * 0, 50, 55});
}

int Dipper::getVidas() const
{
    return vidas;
}

void Dipper::recuperarVidas() {
    if (Dipper::vidas < 5) {  // Usamos Dipper:: para acceder a la variable est�tica
        Dipper::vidas++;      // Incrementamos la variable est�tica
    }
}

void Dipper::perderVida() {
    if (Dipper::vidas > 0) {  // A�adimos una verificaci�n para no tener vidas negativas
        Dipper::vidas--;      // Decrementamos la variable est�tica
    }
}

void Dipper::disparar() {
    if (_disparoCooldown.getElapsedTime() >= _tiempoEntreDisparos) {
        sf::Vector2f posicionDisparo = _sprite.getPosition();
        // Ajusta la posici�n inicial del disparo seg�n la direcci�n
        posicionDisparo.y -= _sprite.getGlobalBounds().height / 2;

        _disparos.emplace_back(posicionDisparo, _direccionMirada, _tipoDisparoActual);
        _disparoCooldown.restart();
    }
}

void Dipper::cambiarTipoDisparo() {

    if (_tipoDisparoActual == TipoDisparo::BOLA_AZUL) {
        _tipoDisparoActual = TipoDisparo::CUCHILLO;
    } else if (_tipoDisparoActual == TipoDisparo::CUCHILLO) {
        _tipoDisparoActual = TipoDisparo::GANCHO;
    } else {
        _tipoDisparoActual = TipoDisparo::BOLA_AZUL;
    }
}









